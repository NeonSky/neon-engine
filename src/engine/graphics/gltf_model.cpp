#include "gltf_model.hpp"

#include "../debug/json.hpp"
#include "../debug/logger.hpp"

#include "image.hpp"

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_INCLUDE_JSON
#define TINYGLTF_NO_INCLUDE_STB_IMAGE
#define TINYGLTF_NO_INCLUDE_STB_IMAGE_WRITE
#include <tiny_gltf.h>

#include <boost/dll/runtime_symbol_info.hpp>
#include <utility>

using namespace engine::graphics;

#define BUFFER_OFFSET(i) ((char*) (i))

GLTFModel::GLTFModel(engine::graphics::Renderer& renderer,
                     const std::string& model_path,
                     geometry::Transform transform,
                     bool invert,
                     GLTFFileFormat format)
        : _renderer(renderer),
          _transform(std::move(transform)),
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

  _vao = _renderer.get().current_context().gen_vao();

  bind_model();
}

void GLTFModel::bind_model() {
  glBindVertexArray(_renderer.get().current_context().vao(_vao));

  std::map<int, GLuint> vbos;

  const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
  for (int node : scene.nodes) {
    if (!((node >= 0) && (node < (int) _model.nodes.size())))
      LOG_ERROR("Nodes are incorrect.");
    bind_model_nodes(vbos, _model.nodes[node]);
  }

  glBindVertexArray(0);

  // cleanup vbos
  for (auto& [key, val] : vbos)
    glDeleteBuffers(1, &val);
}

void GLTFModel::bind_model_nodes(const std::map<int, GLuint>& vbos, tinygltf::Node& node) {
  if ((node.mesh >= 0) && (node.mesh < (int) _model.meshes.size())) {
    bind_mesh(vbos, _model.meshes[node.mesh]);
  }

  for (int i : node.children) {
    if (!((i >= 0) && (i < (int) _model.nodes.size())))
      LOG_ERROR("Nodes are incorrect.");
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

    GLuint vbo = 0;
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

        GLuint texid = 0;
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
          LOG_DEBUG("FIXME");
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
  glBindVertexArray(_renderer.get().current_context().vao(_vao));

  const tinygltf::Scene& scene = _model.scenes[_model.defaultScene];
  for (int node : scene.nodes) {
    draw_model_nodes(_model.nodes[node]);
  }

  glBindVertexArray(0);
}

void GLTFModel::render(const geometry::Matrix<4>& projection_view) {
  if (!_renderer.get().current_context().is_vao(_vao))
    bind_model();

  geometry::Matrix<4> model(_transform.matrix());
  if (_invert) {
    model[0][0] *= -1;
    model[1][1] *= -1;
    model[2][2] *= -1;
  }

  geometry::Matrix<4> mvp = projection_view * model;
  geometry::Vector<3> sun_position(3.0F, 10.0F, -5.0F);
  geometry::Vector<3> sun_color(1.0F, 1.0F, 1.0F);

  _shader.use();
  _shader.set_uniform_mat4("MVP", mvp);
  _shader.set_uniform_vec3("sun_position", sun_position);
  _shader.set_uniform_vec3("sun_color", sun_color);
  draw_model();
}
