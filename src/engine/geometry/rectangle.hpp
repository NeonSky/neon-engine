#pragma once

#include "transform.hpp"
#include "vector.hpp"

namespace engine::geometry {

  /// @todo Transform contains scale, so either remove width/height or don't take transform.
  /// @todo Don't expose the transform like this, because update_corners ends up desynced.
  class Rectangle {
  public:
    Rectangle();
    Rectangle(Transform transform, float width = 1.0F, float height = 1.0F);

    // Accessors
    [[nodiscard]] auto transform() const -> Transform;
    [[nodiscard]] auto width() const -> float;
    [[nodiscard]] auto height() const -> float;

    [[nodiscard]] auto botleft() const -> Vector<3>;
    [[nodiscard]] auto botright() const -> Vector<3>;
    [[nodiscard]] auto topleft() const -> Vector<3>;
    [[nodiscard]] auto topright() const -> Vector<3>;

    [[nodiscard]] auto to_json() const -> debug::JSON;

  private:
    Transform _transform;
    float _width;
    float _height;

    Vector<3> _botleft{};
    Vector<3> _botright{};
    Vector<3> _topleft{};
    Vector<3> _topright{};

    // Mutators
    void update_corners();
  };
}
