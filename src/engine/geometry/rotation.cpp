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

auto Rotation::pitch() -> Angle& { return _pitch; }
auto Rotation::yaw() -> Angle& { return _yaw; }
auto Rotation::roll() -> Angle& { return _roll; }

auto Rotation::operator==(const Rotation& other) const -> bool {
  return (_pitch == other._pitch) && (_yaw == other._yaw) && (_roll == other._roll);
}

auto Rotation::operator!=(const Rotation& other) const -> bool {
  return !((*this) == other);
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
