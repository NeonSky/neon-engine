#include "rotation.hpp"

#include <math.h>

using namespace engine::geometry;

Rotation::Rotation()
        : Rotation(Angle(), Angle(), Angle()) {}

Rotation::Rotation(float pitch, float yaw, float roll, Angle::Unit angle_unit)
        : _pitch(Angle(pitch, angle_unit)),
          _yaw(Angle(yaw, angle_unit)),
          _roll(Angle(roll, angle_unit)) {}

Rotation::Rotation(Angle pitch, Angle yaw, Angle roll)
        : _pitch(pitch),
          _yaw(yaw),
          _roll(roll) {}

/// @internal See the general rotation matrix used in matrix() to grasp these assignments.
/// @see https://www.wikiwand.com/en/Gimbal_lock
/// @see https://www.wikiwand.com/en/List_of_trigonometric_identities
Rotation::Rotation(Matrix<3> matrix, Angle::Unit angle_unit) {
  // : _pitch(Angle(std::atan2(-matrix[2][1], matrix[2][2]), angle_unit)),
  //   _yaw(Angle(std::asin(matrix[2][0]), angle_unit)),
  //   _roll(Angle(std::atan2(-matrix[1][0], matrix[0][0]), angle_unit)) {

  // Since yaw is the second axis rotation applied, it can gimbal lock roll.

  // sin(a \plusminus b) = sin(a) cos(b) \plusminus cos(a) sin(b)
  // cos(a \plusminus b) = cos(a) cos(b) \minusplus sin(a) sin(b)

  // Gimbal lock case 1: https://www.wolframalpha.com/input/?i=%7B%7Bcos%28z%29%2C+sin%28z%29%2C+0%7D%2C+%7B-sin%28z%29%2C+cos%28z%29%2C+0%7D%2C+%7B0%2C+0%2C+1%7D%7D+*+%7B%7Bcos%28pi+%2F+2%29%2C+0%2C+-sin%28pi+%2F+2%29%7D%2C+%7B0%2C+1%2C+0%7D%2C+%7Bsin%28pi+%2F+2%29%2C+0%2C+cos%28pi+%2F+2%29%7D%7D+*+%7B%7B1%2C+0%2C+0%7D%2C+%7B0%2C+cos%28x%29%2C+sin%28x%29%7D%2C+%7B0%2C+-sin%28x%29%2C+cos%28x%29%7D%7D&lang=ja
  if (matrix[2][0] == 1.0F) {
    _pitch = Angle(); // Gimbal locked, so value doesn't matter.
    _yaw   = Angle(pi / 2.0F);

    // = atan(sin(z + x) / cos(z + x)) - x
    // = atan(tan(z + x)) - x
    // = (z + x) - x
    // = z
    _roll = Angle(std::atan2(matrix[0][1], matrix[1][1]) - _pitch.radians());
  }
  // Gimbal lock case 2: https://www.wolframalpha.com/input/?i=%7B%7Bcos%28z%29%2C+sin%28z%29%2C+0%7D%2C+%7B-sin%28z%29%2C+cos%28z%29%2C+0%7D%2C+%7B0%2C+0%2C+1%7D%7D+*+%7B%7Bcos%28-pi+%2F+2%29%2C+0%2C+-sin%28-pi+%2F+2%29%7D%2C+%7B0%2C+1%2C+0%7D%2C+%7Bsin%28-pi+%2F+2%29%2C+0%2C+cos%28-pi+%2F+2%29%7D%7D+*+%7B%7B1%2C+0%2C+0%7D%2C+%7B0%2C+cos%28x%29%2C+sin%28x%29%7D%2C+%7B0%2C+-sin%28x%29%2C+cos%28x%29%7D%7D&lang=ja
  else if (matrix[2][0] == -1.0F) {
    _pitch = Angle(); // Gimbal locked, so value doesn't matter.
    _yaw   = Angle(-pi / 2.0F);

    // = atan(sin(z - x) / cos(z - x)) + x
    // = atan(tan(z - x)) + x
    // = (z - x) + x
    // = z
    _roll = Angle(std::atan2(matrix[0][1], matrix[1][1]) + _pitch.radians());
  }
  // No gimbal lock (yay!)
  else {
    _pitch = Angle(std::atan2(-matrix[2][1], matrix[2][2]), angle_unit);
    _yaw   = Angle(std::asin(matrix[2][0]), angle_unit);
    _roll  = Angle(std::atan2(-matrix[1][0], matrix[0][0]), angle_unit);
  }
}

auto Rotation::pitch() -> Angle& { return _pitch; }
auto Rotation::yaw() -> Angle& { return _yaw; }
auto Rotation::roll() -> Angle& { return _roll; }

auto Rotation::operator==(const Rotation& other) const -> bool {
  return (_pitch == other._pitch) && (_yaw == other._yaw) && (_roll == other._roll);
}

auto Rotation::operator!=(const Rotation& other) const -> bool {
  return !((*this) == other);
}

auto Rotation::modulo(const Angle& modulo) const -> Rotation {
  return Rotation(_pitch.modulo(modulo), _yaw.modulo(modulo), _roll.modulo(modulo));
}

auto Rotation::pitch() const -> const Angle& { return _pitch; }
auto Rotation::yaw() const -> const Angle& { return _yaw; }
auto Rotation::roll() const -> const Angle& { return _roll; }

auto Rotation::matrix() const -> Matrix<3> {

  // Abbreviations
  float cx = std::cos(_pitch.radians());
  float sx = std::sin(_pitch.radians());
  float cy = std::cos(_yaw.radians());
  float sy = std::sin(_yaw.radians());
  float cz = std::cos(_roll.radians());
  float sz = std::sin(_roll.radians());

  // Derivation of the following matrix: https://tinyurl.com/y6cdl9xj
  return {
    {cy * cz, cz * sx * sy + cx * sz, sx * sz - cx * cz * sy},
    {-cy * sz, cx * cz - sx * sy * sz, cz * sx + cx * sy * sz},
    {sy, -cy * sx, cx * cy},
  };
}

auto Rotation::matrix_slow() const -> Matrix<3> {

  // Right-handed matrices: https://www.wikiwand.com/en/Rotation_matrix
  //
  // Since we use a left-handed coordinate system we have to negate the angles.
  // This changes the right-handed rotation matrices in the following ways:
  //   cos(-t) = cos(t)
  //   sin(-t) = -sin(t)
  //
  // Alternatively, you can take the inverse of the matrices which is the transpose since they are orthonormal.
  //
  // It might seem weird that y- and z-rotation has to be inverted as well.
  // But remember, pos (1, 1, 1) means different things for the different systems.

  float x = _pitch.radians();
  Matrix<3> rot_x{
    {1, 0, 0},
    {0, std::cos(x), std::sin(x)},
    {0, -std::sin(x), std::cos(x)},
  };

  float y = _yaw.radians();
  Matrix<3> rot_y{
    {std::cos(y), 0, -std::sin(y)},
    {0, 1, 0},
    {std::sin(y), 0, std::cos(y)},
  };

  float z = _roll.radians();
  Matrix<3> rot_z{
    {std::cos(z), std::sin(z), 0},
    {-std::sin(z), std::cos(z), 0},
    {0, 0, 1},
  };

  return (rot_z * rot_y * rot_x);
}

auto Rotation::to_json(bool debug) const -> debug::JSON {
  debug::JSON json;
  json["pitch"] = _pitch.radians();
  json["yaw"]   = _yaw.radians();
  json["roll"]  = _roll.radians();

  if (debug) {
    json["debug"]["matrix"] = matrix().to_json();
  }

  return json;
}
