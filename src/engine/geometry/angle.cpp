#include "angle.hpp"

#include "../debug/logger.hpp"

using namespace engine::geometry;

Angle::Angle() = default;

Angle::Angle(float angle, Unit unit) {
  set(angle, unit);
}

void Angle::set(float angle, Unit unit) {
  switch (unit) {
  case Unit::TURNS:
    _angle_in_radians = angle * tau;
    break;
  case Unit::RADIANS:
    _angle_in_radians = angle;
    break;
  case Unit::DEGREES:
    _angle_in_radians = angle * (pi / 180.0F);
    break;
  case Unit::GRADIANS:
    _angle_in_radians = angle * (pi / 200.0F);
    break;
  default:
    LOG_ERROR("Unknown unit was provided."); // LCOV_EXCL_BR_LINE
  }
}

auto Angle::operator==(const Angle& other) const -> bool {
  float tolerance = 0.00001F;
  return std::abs(_angle_in_radians - other._angle_in_radians) < tolerance;
}

auto Angle::operator!=(const Angle& other) const -> bool {
  return !((*this) == other);
}

auto Angle::operator+(const Angle& other) const -> Angle {
  return Angle(_angle_in_radians + other._angle_in_radians);
}

auto Angle::operator-(const Angle& other) const -> Angle {
  return Angle(_angle_in_radians - other._angle_in_radians);
}

auto Angle::operator*(float scalar) const -> Angle {
  return Angle(_angle_in_radians * scalar);
}

auto Angle::operator/(float scalar) const -> Angle {
  return Angle(_angle_in_radians / scalar);
}

auto Angle::modulo(const Angle& modulo) const -> Angle {
  // The sign of the steps represents which direction we need to shift in, while
  // the magnitude determines the count of steps.
  //
  // NOTE: for negative radians() steps will be rounded further from zero, while
  // positive radians() will be rounded towards 0. This causes positive radians()
  // to stop right before 0, while negative radians() gains an extra step over 0.
  float full_steps_to_min_positive = -floor(radians() / modulo.radians());

  // Here we weight the steps by our modulo.
  float radians_to_min_positive = modulo.radians() * full_steps_to_min_positive;

  // To create the wrapped angle, we shift radians() by the weighted steps.
  float wrapped_angle_in_radians = radians() + radians_to_min_positive;

  return Angle(wrapped_angle_in_radians);
}

auto Angle::turns() const -> float {
  return _angle_in_radians / tau;
}

auto Angle::radians() const -> float {
  return _angle_in_radians;
}

auto Angle::degrees() const -> float {
  return _angle_in_radians * (180.0F / pi);
}

auto Angle::gradians() const -> float {
  return _angle_in_radians * (200.0F / pi);
}
