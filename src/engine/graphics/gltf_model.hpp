#pragma once

#include "../geometry/matrix.hpp"
#include "../geometry/transform.hpp"
#include "../graphics/renderer.hpp"
#include "shader.hpp"

#include <glad/glad.h>
#include <tiny_gltf.h>

#include <map>
#include <string>

namespace engine::graphics {

  enum class GLTFFileFormat {
    ASCII,
    BINARY,
  };

  class GLTFModel {
  public:
    GLTFModel(engine::graphics::Renderer& renderer,
              const std::string& model_path,
              geometry::Transform transform,
              bool invert           = true,
              GLTFFileFormat format = GLTFFileFormat::ASCII);

    void render(const geometry::Matrix<4>& projection_view);

  private:
    std::reference_wrapper<engine::graphics::Renderer> _renderer;
    geometry::Transform _transform;
    engine::graphics::Shader _shader;
    bool _invert;
    tinygltf::Model _model;
    int _vao = 0;

    void bind_model();
    void bind_model_nodes(const std::map<int, GLuint>& vbos, tinygltf::Node& node);
    auto bind_mesh(std::map<int, GLuint> vbos, tinygltf::Mesh& mesh) -> std::map<int, GLuint>;
    void draw_mesh(tinygltf::Mesh& mesh);
    void draw_model_nodes(tinygltf::Node& node);
    void draw_model();
  };
}
