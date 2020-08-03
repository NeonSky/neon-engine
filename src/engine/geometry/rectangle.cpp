#include "rectangle.hpp"

#include <utility>

#include "matrix.hpp"

using namespace engine::geometry;

Rectangle::Rectangle()
        : Rectangle(Transform()) {}

Rectangle::Rectangle(Transform transform, float width, float height)
        : _transform(transform),
          _width(width),
          _height(height) {
  update_corners();
}

// Accessors
auto Rectangle::transform() const -> Transform { return _transform; }
auto Rectangle::width() const -> float { return _width; }
auto Rectangle::height() const -> float { return _height; }

auto Rectangle::topleft() const -> Vector<3> { return _topleft; }
auto Rectangle::topright() const -> Vector<3> { return _topright; }
auto Rectangle::botleft() const -> Vector<3> { return _botleft; }
auto Rectangle::botright() const -> Vector<3> { return _botright; }

// Mutators
void Rectangle::update_corners() {
  Vector<3> xoffset = (_width / 2.0F) * Vector<3>(Transform::world_right);
  Vector<3> yoffset = (_height / 2.0F) * Vector<3>(Transform::world_up);

  _topleft  = Matrix<4>(_transform.matrix()) * Vector<4>(+xoffset + yoffset, 1.0F);
  _topright = Matrix<4>(_transform.matrix()) * Vector<4>(-xoffset + yoffset, 1.0F);
  _botleft  = Matrix<4>(_transform.matrix()) * Vector<4>(+xoffset - yoffset, 1.0F);
  _botright = Matrix<4>(_transform.matrix()) * Vector<4>(-xoffset - yoffset, 1.0F);
}
