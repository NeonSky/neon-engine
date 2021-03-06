#include "transform.hpp"

#include "scale.hpp"
#include "translation.hpp"

using namespace engine::geometry;

Transform::Transform()
        : Transform(Vector<3>()) {}

Transform::Transform(const Vector<3>& position)
        : Transform(position, Orientation()) {}

Transform::Transform(const Vector<3>& position, const Orientation& orientation)
        : Transform(position, orientation, Vector<3>(1.0F, 1.0F, 1.0F)) {}

Transform::Transform(const Vector<3>& position, const Orientation& orientation, const Vector<3>& scale)
        : Rigidbody(position, orientation),
          _scale(scale) {}

auto Transform::scale() const -> const Vector<3>& {
  return _scale;
}

auto Transform::operator==(const Transform& other) const -> bool {
  return (_position == other._position) && (_orientation == other._orientation) && (_scale == other._scale);
}

auto Transform::operator!=(const Transform& other) const -> bool {
  return !((*this) == other);
}

auto Transform::matrix() const -> Matrix<4> {
  return translation_matrix(_position) * Matrix<4>(_orientation.rotation().matrix() * scale_matrix(_scale));
}

auto Transform::scale() -> Vector<3>& {
  return _scale;
}

auto Transform::to_json(bool debug) const -> debug::JSON {
  debug::JSON json;
  json["position"]    = _position.to_json();
  json["orientation"] = _orientation.to_json(debug);
  json["scale"]       = _scale.to_json();
  return json;
}
