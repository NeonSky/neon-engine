#pragma once

#include "transform.hpp"
#include "vector.hpp"

namespace engine::geometry {

  class Rectangle {
  public:
    Rectangle();
    Rectangle(Transform transform, float width = 1.0F, float height = 1.0F);

    // Accessors
    [[nodiscard]] auto transform() const -> Transform;
    [[nodiscard]] auto width() const -> float;
    [[nodiscard]] auto height() const -> float;

    [[nodiscard]] auto topleft() const -> Vector<3>;
    [[nodiscard]] auto topright() const -> Vector<3>;
    [[nodiscard]] auto botleft() const -> Vector<3>;
    [[nodiscard]] auto botright() const -> Vector<3>;

  private:
    Transform _transform;
    float _width;
    float _height;

    Vector<3> _topleft{};
    Vector<3> _topright{};
    Vector<3> _botleft{};
    Vector<3> _botright{};

    // Mutators
    void update_corners();
  };
}
