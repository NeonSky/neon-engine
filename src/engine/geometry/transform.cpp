#include "transform.hpp"

#include "angle.hpp"

#include <utility>

using namespace engine::geometry;

const Vector<4> Transform::world_right   = Vector<4>(1.0F, 0.0F, 0.0F, 0.0F);
const Vector<4> Transform::world_up      = Vector<4>(0.0F, 1.0F, 0.0F, 0.0F);
const Vector<4> Transform::world_forward = Vector<4>(0.0F, 0.0F, 1.0F, 0.0F);

Transform::Transform()
        : Transform(Vector<3>()) {}

Transform::Transform(const Vector<3>& position)
        : Transform(position, Vector<3>()) {}

Transform::Transform(const Vector<3>& position, const Vector<3>& rotation)
        : Transform(position, rotation, Vector<3>(1.0F, 1.0F, 1.0F)) {}

Transform::Transform(Vector<3> position, Vector<3> rotation, Vector<3> scale)
        : _position(position),
          _rotation(rotation),
          _scale(scale) {}

void Transform::set_rotation(float yaw, float pitch, float roll) {
  _rotation = Vector<3>(pitch, yaw, roll);
}

// TODO: Needs more tests.
void Transform::flip_rotation() {
  Matrix<4> m = rotation_matrix().rotate(Angle(pi, Angle::Unit::RADIANS), engine::geometry::Transform::world_up);

  // NOTE: we negate each angle due to rotation_matrix() negating the angles.
  float yaw   = -std::atan2(-m[0][2], m[2][2]);
  float pitch = -std::asin(m[1][2]);
  float roll  = -std::atan2(-m[1][0], m[1][1]);

  set_rotation(yaw, pitch, roll);
}

[[nodiscard]] auto Transform::position() const -> const Vector<3>& {
  return _position;
}

[[nodiscard]] auto Transform::rotation() const -> const Vector<3>& {
  return _rotation;
}

[[nodiscard]] auto Transform::scale() const -> const Vector<3>& {
  return _scale;
}

auto Transform::operator+(const Transform& other) const -> Transform {
  return Transform(_position + other._position, _rotation + other._rotation, _scale + other._scale);
}

auto Transform::matrix() const -> Matrix<4> {
  // Scale -> Rotate -> Translate
  return (Matrix<4>().scale(_scale) * rotation_matrix()).translate(_position);
}

auto Transform::forward() const -> Vector<3> {
  return rotation_matrix() * engine::geometry::Transform::world_forward;
}

auto Transform::up() const -> Vector<3> {
  return rotation_matrix() * engine::geometry::Transform::world_up;
}

auto Transform::right() const -> Vector<3> {
  return rotation_matrix() * engine::geometry::Transform::world_right;
}

[[nodiscard]] auto Transform::yaw() const -> float {
  return _rotation.y();
};

[[nodiscard]] auto Transform::pitch() const -> float {
  return _rotation.x();
};

[[nodiscard]] auto Transform::roll() const -> float {
  return _rotation.z();
};

[[nodiscard]] auto Transform::position() -> Vector<3>& {
  return _position;
}

[[nodiscard]] auto Transform::rotation() -> Vector<3>& {
  return _rotation;
}

[[nodiscard]] auto Transform::scale() -> Vector<3>& {
  return _scale;
}

/// @image html geometry/img1.png
/// @see Image source: https://tinyurl.com/y6fo7ps7
/// @see https://www.wikiwand.com/en/Rotation_matrix
/// @see https://www.wikiwand.com/en/Euler_angles
/// @see https://www.wikiwand.com/simple/Pitch,_yaw,_and_roll
auto Transform::rotation_matrix_slow() const -> Matrix<4> {

  // Right-handed matrices: https://www.wikiwand.com/en/Rotation_matrix
  //
  // Since we use a left-handed coordinate system we have to negate the angles.
  // This changes the right-handed rotation matrices in the following ways:
  //   cos(-t) = cos(t)
  //   sin(-t) = -sin(t)

  float x = _rotation.x();
  Matrix<3> rot_x{
    {1, 0, 0},
    {0, std::cos(x), std::sin(x)},
    {0, -std::sin(x), std::cos(x)},
  };

  float y = _rotation.y();
  Matrix<3> rot_y{
    {std::cos(y), 0, -std::sin(y)},
    {0, 1, 0},
    {std::sin(y), 0, std::cos(y)},
  };

  float z = _rotation.z();
  Matrix<3> rot_z{
    {std::cos(z), std::sin(z), 0},
    {-std::sin(z), std::cos(z), 0},
    {0, 0, 1},
  };

  return Matrix<4>(rot_y * rot_x * rot_z);
}

auto Transform::rotation_matrix() const -> Matrix<4> {
  float cx = std::cos(_rotation.x());
  float sx = std::sin(_rotation.x());
  float cy = std::cos(_rotation.y());
  float sy = std::sin(_rotation.y());
  float cz = std::cos(_rotation.z());
  float sz = std::sin(_rotation.z());

  // https://www.wolframalpha.com/input/?i=%7B%7Bcos%28y%29%2C+0%2C+-sin%28y%29%7D%2C+%7B0%2C+1%2C+-0%7D%2C+%7Bsin%28y%29%2C+0%2C+cos%28y%29%7D%7D+*+%7B%7B1%2C+0%2C+0%7D%2C+%7B0%2C+cos%28x%29%2C+sin%28x%29%7D%2C+%7B0%2C+-sin%28x%29%2C+cos%28x%29%7D%7D+*+%7B%7Bcos%28z%29%2C+sin%28z%29%2C+0%7D%2C+%7B-sin%28z%29%2C+cos%28z%29%2C+0%7D%2C+%7B0%2C+0%2C+1%7D%7D
  return {
    {cy * cz - sx * sy * sz, cz * sx * sy + cy * sz, -cx * sy, 0},
    {-cx * sz, cx * cz, sx, 0},
    {cz * sy + cy * sx * sz, sy * sz - cy * cz * sx, cx * cy, 0},
    {0, 0, 0, 1},
  };
}
