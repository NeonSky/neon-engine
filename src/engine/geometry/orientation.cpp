#include "orientation.hpp"

using namespace engine::geometry;

const Vector<3> Orientation::world_right   = Vector<3>(1.0F, 0.0F, 0.0F);
const Vector<3> Orientation::world_up      = Vector<3>(0.0F, 1.0F, 0.0F);
const Vector<3> Orientation::world_forward = Vector<3>(0.0F, 0.0F, 1.0F);

Orientation::Orientation() = default;
Orientation::Orientation(Rotation rotation)
        : _rotation(rotation) {}

auto Orientation::rotation() -> Rotation& {
  return _rotation;
}

void Orientation::flip(Vector<3> axis) {
  Matrix<3> m = Matrix<4>(_rotation.matrix()).rotate(Angle(pi, Angle::Unit::RADIANS), axis).submatrix<3, 3>();
  _rotation   = Rotation(m, Angle::Unit::RADIANS);
}

auto Orientation::operator==(const Orientation& other) const -> bool {
  return _rotation.matrix() == other._rotation.matrix();
}

auto Orientation::operator!=(const Orientation& other) const -> bool {
  return !((*this) == other);
}

auto Orientation::rotation() const -> const Rotation& {
  return _rotation;
}

auto Orientation::right() const -> Vector<3> {
  return _rotation.matrix() * Orientation::world_right;
}

auto Orientation::up() const -> Vector<3> {
  return _rotation.matrix() * Orientation::world_up;
}

auto Orientation::forward() const -> Vector<3> {
  return _rotation.matrix() * Orientation::world_forward;
}

auto Orientation::to_json(bool debug) const -> debug::JSON {
  debug::JSON json;
  json["rotation"] = _rotation.to_json(debug);

  if (debug) {
    json["debug"]["right"]   = right().to_json();
    json["debug"]["up"]      = up().to_json();
    json["debug"]["forward"] = forward().to_json();
  }

  return json;
}
