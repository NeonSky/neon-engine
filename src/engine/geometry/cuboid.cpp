#include "cuboid.hpp"

#include "angle.hpp"

#include <utility>

using namespace engine::geometry;

Cuboid::Cuboid()
        : Cuboid(Transform()) {}

Cuboid::Cuboid(Transform transform)
        : _transform(std::move(std::move(transform))) {}

auto Cuboid::transform() -> Transform& {
  return _transform;
}

auto Cuboid::left_face() -> Rectangle {
  Transform t                = _transform;
  Matrix<3> m                = t.orientation().rotation().matrix() * Matrix<3>().rotate(Angle(pi / 2.0F), Orientation::world_up);
  t.orientation().rotation() = Rotation(m);
  t.position() += t.forward() * t.scale().x() / 2.0F;
  return Rectangle((const Rigidbody&) t, t.scale().z(), t.scale().y());
}

auto Cuboid::right_face() -> Rectangle {
  Transform t                = _transform;
  Matrix<3> m                = t.orientation().rotation().matrix() * Matrix<3>().rotate(Angle(-pi / 2.0F), Orientation::world_up);
  t.orientation().rotation() = Rotation(m);
  t.position() += t.forward() * t.scale().x() / 2.0F;
  return Rectangle((const Rigidbody&) t, t.scale().z(), t.scale().y());
}

auto Cuboid::bottom_face() -> Rectangle {
  Transform t = _transform;
  t.orientation().rotation().pitch() += Angle(-pi / 2.0F, Angle::Unit::RADIANS);
  t.position() += t.forward() * t.scale().y() / 2.0F;
  return Rectangle((const Rigidbody&) t, t.scale().x(), t.scale().z());
}

auto Cuboid::top_face() -> Rectangle {
  Transform t = _transform;
  t.orientation().rotation().pitch() += Angle(pi / 2.0F, Angle::Unit::RADIANS);
  t.position() += t.forward() * t.scale().y() / 2.0F;
  return Rectangle((const Rigidbody&) t, t.scale().x(), t.scale().z());
}

auto Cuboid::back_face() -> Rectangle {
  Transform t                = _transform;
  Matrix<3> m                = t.orientation().rotation().matrix() * Matrix<3>().rotate(Angle(pi), Orientation::world_up);
  t.orientation().rotation() = Rotation(m);
  t.position() += t.forward() * t.scale().z() / 2.0F;
  return Rectangle((const Rigidbody&) t, t.scale().x(), t.scale().y());
}

auto Cuboid::front_face() -> Rectangle {
  Transform t = _transform;
  t.position() += t.forward() * _transform.scale().z() / 2.0F;
  return Rectangle((const Rigidbody&) t, t.scale().x(), t.scale().y());
}
