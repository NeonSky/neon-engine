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
    LOG_ERROR("Unknown angle unit provided.");
  }
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
