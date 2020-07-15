#include "gltf_model.hpp"

#include "../debug/logger.hpp"

#include "image.hpp"
#include <nlohmann/json.hpp>

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_INCLUDE_JSON
#define TINYGLTF_NO_INCLUDE_STB_IMAGE
#define TINYGLTF_NO_INCLUDE_STB_IMAGE_WRITE
#include <tiny_gltf.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace engine::graphics;

#define BUFFER_OFFSET(i) ((char*) (i))

GLTFModel::GLTFModel(const std::string& model_path,
                     const geometry::Transform& transform,
                     bool invert,
                     GLTFFileFormat format)
        : _transform(transform),
          _shader(Shader("gltf.vert", "gltf.frag")),
          _invert(invert) {

  std::string res_path  = boost::dll::program_location().parent_path().string() + "/../res/models/";
  std::string full_path = res_path + model_path;

  tinygltf::TinyGLTF loader;

  std::string err;
  std::string warn;
  bool ok = false;
  if (format == GLTFFileFormat::ASCII)
    ok = loader.LoadASCIIFromFile(&_model, &err, &warn, full_path);
  else
    ok = loader.LoadBinaryFromFile(&_model, &err, &warn, full_path);

  if (!warn.empty())
    LOG_WARNING(warn);
  if (!err.empty())
    LOG_ERROR(err);
  if (!ok)
    LOG_ERROR("Failed to load .glTF model: " + full_path);

  bind_model();
}

GLTFModel::~GLTFModel() = default;

void GLTFModel::bind_model() {
  std::map<int, GLuint> vbos;
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
  for (int node : scene.nodes) {
    assert((node >= 0) && (node < (int) _model.nodes.size()));
    bind_model_nodes(vbos, _model.nodes[node]);
  }

  glBindVertexArray(0);

  // cleanup vbos
  for (auto& [key, val] : vbos)
    glDeleteBuffers(1, &val);

  _vao = vao;
}

void GLTFModel::bind_model_nodes(const std::map<int, GLuint>& vbos, tinygltf::Node& node) {
  if ((node.mesh >= 0) && (node.mesh < (int) _model.meshes.size())) {
    bind_mesh(vbos, _model.meshes[node.mesh]);
  }

  for (int i : node.children) {
    assert((i >= 0) && (i < (int) _model.nodes.size()));
    bind_model_nodes(vbos, _model.nodes[i]);
  }
}

auto GLTFModel::bind_mesh(std::map<int, GLuint> vbos, tinygltf::Mesh& mesh) -> std::map<int, GLuint> {
  for (size_t i = 0; i < _model.bufferViews.size(); ++i) {
    const tinygltf::BufferView& bufferView = _model.bufferViews[i];
    if (bufferView.target == 0) { // TODO impl drawarrays
      LOG_WARNING("bufferView.target is zero.");
      continue; // Unsupported bufferView.
    }

    const tinygltf::Buffer& buffer = _model.buffers[bufferView.buffer];
    // std::cout << "bufferview.target " << bufferView.target << std::endl;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    vbos[i] = vbo;
    glBindBuffer(bufferView.target, vbo);

    // std::cout << "buffer.data.size = " << buffer.data.size()
    //           << ", bufferview.byteOffset = " << bufferView.byteOffset
    //           << std::endl;

    glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
  }

  for (const auto& primitive : mesh.primitives) {
    tinygltf::Accessor indexAccessor = _model.accessors[primitive.indices];

    for (const auto& attrib : primitive.attributes) {
      tinygltf::Accessor accessor = _model.accessors[attrib.second];
      int byteStride =
        accessor.ByteStride(_model.bufferViews[accessor.bufferView]);
      glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

      int size = 1;
      if (accessor.type != TINYGLTF_TYPE_SCALAR) {
        size = accessor.type;
      }

      int vaa = -1;
      if (attrib.first == "POSITION")
        vaa = 0;
      if (attrib.first == "NORMAL")
        vaa = 1;
      if (attrib.first == "TEXCOORD_0")
        vaa = 2;
      if (vaa > -1) {
        glEnableVertexAttribArray(vaa);
        glVertexAttribPointer(vaa, size, accessor.componentType, accessor.normalized ? GL_TRUE : GL_FALSE, byteStride, BUFFER_OFFSET(accessor.byteOffset));
      } else
        LOG_WARNING("vaa missing: " + attrib.first);
    }

    if (!_model.textures.empty()) {
      // fixme: Use material's baseColor
      tinygltf::Texture& tex = _model.textures[0];

      if (tex.source > -1) {

        GLuint texid;
        glGenTextures(1, &texid);

        tinygltf::Image& image = _model.images[tex.source];

        glBindTexture(GL_TEXTURE_2D, texid);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        GLenum format = GL_RGBA;

        if (image.component == 1) {
          format = GL_RED;
        } else if (image.component == 2) {
          format = GL_RG;
        } else if (image.component == 3) {
          format = GL_RGB;
        } else {
          // ???
        }

        GLenum type = GL_UNSIGNED_BYTE;
        if (image.bits == 8) {
          // ok
        } else if (image.bits == 16) {
          type = GL_UNSIGNED_SHORT;
        } else {
          // ???
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, format, type, &image.image.at(0));
      }
    }
  }

  return vbos;
}

void GLTFModel::draw_mesh(tinygltf::Mesh& mesh) {
  for (const auto& primitive : mesh.primitives) {
    tinygltf::Accessor indexAccessor = _model.accessors[primitive.indices];

    glDrawElements(primitive.mode, indexAccessor.count, indexAccessor.componentType, BUFFER_OFFSET(indexAccessor.byteOffset));
  }
}

void GLTFModel::draw_model_nodes(tinygltf::Node& node) {
  if ((node.mesh >= 0) && (node.mesh < (int) _model.meshes.size())) {
    draw_mesh(_model.meshes[node.mesh]);
  }
  for (int i : node.children) {
    draw_model_nodes(_model.nodes[i]);
  }
}

void GLTFModel::draw_model() {
  glBindVertexArray(_vao);

  const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
  for (int node : scene.nodes) {
    draw_model_nodes(_model.nodes[node]);
  }

  glBindVertexArray(0);
}

void GLTFModel::render(const glm::mat4& projection_view) {
  glm::mat4 model = _transform.matrix();
  if (_invert) {
    model[0][0] *= -1;
    model[1][1] *= -1;
    model[2][2] *= -1;
  }

  glm::mat4 mvp          = projection_view * model;
  glm::vec3 sun_position = glm::vec3(3.0, 10.0, -5.0);
  auto sun_color         = glm::vec3(1.0);

  _shader.use();
  _shader.set_uniform_mat4("MVP", &mvp[0][0]);
  _shader.set_uniform_vec3("sun_position", &sun_position[0]);
  _shader.set_uniform_vec3("sun_color", &sun_color[0]);
  draw_model();
}
