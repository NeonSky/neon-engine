#include "transform.hpp"

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
        : position(position),
          rotation(rotation),
          scale(scale) {}

void Transform::set_rotation(float yaw, float pitch, float roll) {
  this->rotation = Vector<3>(pitch, yaw, roll);
}

// TODO: Needs more tests.
void Transform::flip_rotation() {
  Matrix<4> m = rotation_matrix().rotate(pi, engine::geometry::Transform::world_up);

  // NOTE: we negate each angle due to rotation_matrix() negating the angles.
  float yaw   = -std::atan2(-m[0][2], m[2][2]);
  float pitch = -std::asin(m[1][2]);
  float roll  = -std::atan2(-m[1][0], m[1][1]);

  set_rotation(yaw, pitch, roll);
}

auto Transform::operator+(const Transform& other) const -> Transform {
  return Transform(this->position + other.position, this->rotation + other.rotation, this->scale + other.scale);
}

auto Transform::matrix() const -> Matrix<4> {
  // Scale -> Rotate -> Translate
  return (Matrix<4>().scale(scale) * rotation_matrix()).translate(position);
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

auto Transform::yaw() const -> float {
  return rotation.y();
};

auto Transform::pitch() const -> float {
  return rotation.x();
};

auto Transform::roll() const -> float {
  return rotation.z();
};

// https://www.wikiwand.com/en/Euler_angles
// https://www.wikiwand.com/simple/Pitch,_yaw,_and_roll
//
// Here we apply y-rotation (yaw), then x-rotation (pitch), and finally z-rotation (roll).
auto Transform::rotation_matrix_slow() const -> Matrix<4> {

  // Right-handed matrices: https://www.wikiwand.com/en/Rotation_matrix
  //
  // Since we use a left-handed coordinate system we have to negate the angles.
  // This changes the right-handed rotation matrices in the following ways:
  //   cos(-t) = cos(t)
  //   sin(-t) = -sin(t)

  float x = rotation.x();
  Matrix<3> rot_x{
    {1, 0, 0},
    {0, std::cos(x), std::sin(x)},
    {0, -std::sin(x), std::cos(x)},
  };

  float y = rotation.y();
  Matrix<3> rot_y{
    {std::cos(y), 0, -std::sin(y)},
    {0, 1, 0},
    {std::sin(y), 0, std::cos(y)},
  };

  float z = rotation.z();
  Matrix<3> rot_z{
    {std::cos(z), std::sin(z), 0},
    {-std::sin(z), std::cos(z), 0},
    {0, 0, 1},
  };

  return Matrix<4>(rot_y * rot_x * rot_z);
}

auto Transform::rotation_matrix() const -> Matrix<4> {
  float cx = std::cos(rotation.x());
  float sx = std::sin(rotation.x());
  float cy = std::cos(rotation.y());
  float sy = std::sin(rotation.y());
  float cz = std::cos(rotation.z());
  float sz = std::sin(rotation.z());

  // https://www.wolframalpha.com/input/?i=%7B%7Bcos%28y%29%2C+0%2C+-sin%28y%29%7D%2C+%7B0%2C+1%2C+-0%7D%2C+%7Bsin%28y%29%2C+0%2C+cos%28y%29%7D%7D+*+%7B%7B1%2C+0%2C+0%7D%2C+%7B0%2C+cos%28x%29%2C+sin%28x%29%7D%2C+%7B0%2C+-sin%28x%29%2C+cos%28x%29%7D%7D+*+%7B%7Bcos%28z%29%2C+sin%28z%29%2C+0%7D%2C+%7B-sin%28z%29%2C+cos%28z%29%2C+0%7D%2C+%7B0%2C+0%2C+1%7D%7D
  return {
    {cy * cz - sx * sy * sz, cz * sx * sy + cy * sz, -cx * sy, 0},
    {-cx * sz, cx * cz, sx, 0},
    {cz * sy + cy * sx * sz, sy * sz - cy * cz * sx, cx * cy, 0},
    {0, 0, 0, 1},
  };
}
