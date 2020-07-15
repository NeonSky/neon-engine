#pragma once

#include "../geometry/transform.hpp"
#include "shader.hpp"

#include <glad/glad.h>
#include <tiny_gltf.h>

#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>

namespace engine::graphics {

  enum class GLTFFileFormat {
    ASCII,
    BINARY,
  };

  class GLTFModel {
  public:
    GLTFModel(const std::string& model_path,
              const geometry::Transform& transform,
              bool invert           = true,
              GLTFFileFormat format = GLTFFileFormat::ASCII);
    ~GLTFModel();

    void render(const glm::mat4& projection_view);

  private:
    geometry::Transform _transform;
    engine::graphics::Shader _shader;
    bool _invert;
    tinygltf::Model _model;
    int _vao;

    void bind_model();
    void bind_model_nodes(const std::map<int, GLuint>& vbos, tinygltf::Node& node);
    auto bind_mesh(std::map<int, GLuint> vbos, tinygltf::Mesh& mesh) -> std::map<int, GLuint>;
    void draw_mesh(tinygltf::Mesh& mesh);
    void draw_model_nodes(tinygltf::Node& node);
    void draw_model();
  };
}
