#include "rigidbody.hpp"

#include "translation.hpp"

using namespace engine::geometry;

Rigidbody::Rigidbody()
        : Rigidbody(Vector<3>()) {}

Rigidbody::Rigidbody(const Vector<3>& position)
        : Rigidbody(position, Orientation()) {}

Rigidbody::Rigidbody(const Vector<3>& position, const Orientation& orientation)
        : _position(position),
          _orientation(orientation) {}

auto Rigidbody::position() const -> const Vector<3>& {
  return _position;
}

auto Rigidbody::orientation() const -> const Orientation& {
  return _orientation;
}

auto Rigidbody::operator==(const Rigidbody& other) const -> bool {
  return (_position == other._position) && (_orientation == other._orientation);
}

auto Rigidbody::operator!=(const Rigidbody& other) const -> bool {
  return !((*this) == other);
}

auto Rigidbody::matrix() const -> Matrix<4> {
  return translation_matrix(_position) * Matrix<4>(_orientation.rotation().matrix());
}

auto Rigidbody::position() -> Vector<3>& {
  return _position;
}

auto Rigidbody::orientation() -> Orientation& {
  return _orientation;
}

auto Rigidbody::right() const -> UnitVector<3> {
  return _orientation.right();
}

auto Rigidbody::up() const -> UnitVector<3> {
  return _orientation.up();
}

auto Rigidbody::forward() const -> UnitVector<3> {
  return _orientation.forward();
}

auto Rigidbody::to_json(bool debug) const -> debug::JSON {
  debug::JSON json;
  json["position"]    = _position.to_json();
  json["orientation"] = _orientation.to_json(debug);
  return json;
}
