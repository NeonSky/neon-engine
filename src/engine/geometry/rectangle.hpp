#pragma once

#include "transform.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace engine::geometry {

  class Rectangle {
  public:
    Rectangle();
    Rectangle(const Transform& transform, float width = 1.0F, float height = 1.0F);

    // Accessors
    [[nodiscard]] auto transform() const -> Transform;
    [[nodiscard]] auto width() const -> float;
    [[nodiscard]] auto height() const -> float;

    [[nodiscard]] auto topleft() const -> glm::vec3;
    [[nodiscard]] auto topright() const -> glm::vec3;
    [[nodiscard]] auto botleft() const -> glm::vec3;
    [[nodiscard]] auto botright() const -> glm::vec3;

  private:
    Transform _transform;
    float _width;
    float _height;

    glm::vec3 _topleft;
    glm::vec3 _topright;
    glm::vec3 _botleft;
    glm::vec3 _botright;

    // Mutators
    void update_corners();
  };
}
