#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include "../geometry/rectangle.hpp"
#include "../geometry/transform.hpp"

#include <memory>

namespace engine::graphics {

  class Rectangle {
  public:
    Rectangle(const geometry::Rectangle& rectangle, const Texture* texture = nullptr);

    // Mutators
    auto transform() -> geometry::Transform&;
    void render(const geometry::Matrix<4>& view_projection_matrix);

  private:
    geometry::Transform _transform;
    GLuint _vao;
    const Texture* _texture;
    std::unique_ptr<Shader> _shader;
  };

}
