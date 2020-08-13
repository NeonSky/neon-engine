#include "transform.hpp"

#include "angle.hpp"
#include "orientation.hpp"

#include <utility>

using namespace engine::geometry;

Transform::Transform()
        : Transform(Vector<3>()) {}

Transform::Transform(const Vector<3>& position)
        : Transform(position, Orientation()) {}

Transform::Transform(const Vector<3>& position, const Orientation& orientation)
        : Transform(position, orientation, Vector<3>(1.0F, 1.0F, 1.0F)) {}

Transform::Transform(const Vector<3>& position, const Orientation& orientation, const Vector<3>& scale)
        : _position(position),
          _orientation(orientation),
          _scale(scale) {}

[[nodiscard]] auto Transform::position() const -> const Vector<3>& {
  return _position;
}

[[nodiscard]] auto Transform::orientation() const -> const Orientation& {
  return _orientation;
}

[[nodiscard]] auto Transform::scale() const -> const Vector<3>& {
  return _scale;
}

auto Transform::operator==(const Transform& other) const -> bool {
  return (_position == other._position) && (_orientation == other._orientation) && (_scale == other._scale);
}

auto Transform::operator!=(const Transform& other) const -> bool {
  return !((*this) == other);
}

auto Transform::matrix() const -> Matrix<4> {
  return (Matrix<4>(_orientation.rotation().matrix()) * Matrix<4>().scale(_scale)).translate(_position);
}

[[nodiscard]] auto Transform::position() -> Vector<3>& {
  return _position;
}

[[nodiscard]] auto Transform::orientation() -> Orientation& {
  return _orientation;
}

[[nodiscard]] auto Transform::scale() -> Vector<3>& {
  return _scale;
}

auto Transform::right() const -> Vector<3> {
  return _orientation.right();
}

auto Transform::up() const -> Vector<3> {
  return _orientation.up();
}

auto Transform::forward() const -> Vector<3> {
  return _orientation.forward();
}

auto Transform::to_json(bool debug) const -> debug::JSON {
  debug::JSON json;
  json["position"]    = _position.to_json();
  json["orientation"] = _orientation.to_json(debug);
  json["scale"]       = _scale.to_json();
  return json;
}
