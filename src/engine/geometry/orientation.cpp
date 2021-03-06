#include "orientation.hpp"

using namespace engine::geometry;

const UnitVector<3> Orientation::world_right   = UnitVector<3>(1.0F, 0.0F, 0.0F);
const UnitVector<3> Orientation::world_up      = UnitVector<3>(0.0F, 1.0F, 0.0F);
const UnitVector<3> Orientation::world_forward = UnitVector<3>(0.0F, 0.0F, 1.0F);

Orientation::Orientation() = default;
Orientation::Orientation(Rotation rotation)
        : _rotation(rotation) {}

auto Orientation::rotation() -> Rotation& {
  return _rotation;
}

void Orientation::flip(UnitVector<3> axis) {
  _rotation = Rotation(Angle(pi), axis) * _rotation;
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

auto Orientation::right() const -> UnitVector<3> {
  return (UnitVector<3>) (_rotation.matrix() * Orientation::world_right);
}

auto Orientation::up() const -> UnitVector<3> {
  return (UnitVector<3>) (_rotation.matrix() * Orientation::world_up);
}

auto Orientation::forward() const -> UnitVector<3> {
  return (UnitVector<3>) (_rotation.matrix() * Orientation::world_forward);
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
