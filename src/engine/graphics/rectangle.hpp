#pragma once

#include "color.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include "../geometry/rectangle.hpp"
#include "../geometry/transform.hpp"

#include <memory>

namespace engine::graphics {

  class Rectangle {
  public:
    Rectangle(Renderer& renderer, const geometry::Rectangle& rectangle, const Color& color);

    // Mutators
    void compile();
    auto transform() -> geometry::Transform&;
    void render(const geometry::Matrix<4>& view_projection_matrix);

  private:
    std::reference_wrapper<Renderer> _renderer;
    const geometry::Rectangle _model;
    geometry::Transform _transform;
    GLuint _vao;
    GLuint _index_buffer;
    GLuint _pos_buffer;
    const Color _color;
    std::unique_ptr<Shader> _shader;
  };

}
