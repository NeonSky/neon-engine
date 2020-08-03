#include "camera.hpp"
#include "../debug/logger.hpp"

#include <algorithm>
#include <utility>

using namespace engine::graphics;

// FIXME
bool firstMouse = true;
float lastX;
float lastY;
float yaw   = 0.0F;
float pitch = 0.0F;

Camera::Camera() : Camera(geometry::Transform()) {}
Camera::Camera(geometry::Transform transform)
        : _transform(transform) {

  yaw   = _transform.yaw();
  pitch = _transform.pitch();
}

auto Camera::transform() -> geometry::Transform& {
  return _transform;
}

void Camera::move(Direction move_dir) {
  geometry::Vector<3> displacement_dir;
  switch (move_dir) {
  case Direction::FORWARD:
    displacement_dir = +_transform.forward();
    break;
  case Direction::BACKWARD:
    displacement_dir = -_transform.forward();
    break;
  case Direction::RIGHT:
    displacement_dir = +_transform.right();
    break;
  case Direction::LEFT:
    displacement_dir = -_transform.right();
    break;
  case Direction::UP:
    displacement_dir = +_transform.up();
    break;
  case Direction::DOWN:
    displacement_dir = -_transform.up();
    break;
  default:
    LOG_ERROR("Direction type not supported: " + std::to_string(move_dir));
  }
  _transform.position += _movement_speed * displacement_dir;
}

void Camera::set_zoom(float zoom_level) {
  // FIXME: name constant
  _perspective.fov.set(45.0F - zoom_level, geometry::Angle::Unit::DEGREES);
}

void Camera::lookat_mouse(float mouse_xpos, float mouse_ypos) {
  if (firstMouse) {
    lastX      = mouse_xpos;
    lastY      = mouse_ypos;
    firstMouse = false;
  }

  float xoffset = mouse_xpos - lastX;
  float yoffset = mouse_ypos - lastY;
  lastX         = mouse_xpos;
  lastY         = mouse_ypos;

  float sensitivity = 0.003F;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw -= xoffset;
  pitch += yoffset;

  pitch = std::clamp(pitch, -geometry::pi / 2.0F, geometry::pi / 2.0F);

  _transform.set_rotation(yaw, pitch, 0.0F);
}

auto Camera::view_matrix() const -> geometry::Matrix<4> {
  geometry::Matrix<4> base_vectors_in_world_space = geometry::Matrix<3>{
    (std::array<float, 3>) geometry::Vector<3>(_transform.right()),  // (R_x, R_y, R_z)
    (std::array<float, 3>) geometry::Vector<3>(_transform.up()),     // (U_x, U_y, U_z)
    (std::array<float, 3>) geometry::Vector<3>(_transform.forward()) // (F_x, F_y, F_z)
  };

  return base_vectors_in_world_space.translate(-_transform.position);
}

auto Camera::projection_matrix(ProjectionType projection_type) const -> geometry::Matrix<4> {
  switch (projection_type) {
  case ProjectionType::PERSPECTIVE:
    return perspective_projection_matrix();
  case ProjectionType::ORTHOGRAPHIC:
    return orthographic_projection_matrix();
  default:
    LOG_ERROR("Projection type not supported: " + std::to_string(projection_type));
  }
}

auto Camera::perspective_projection_matrix() const -> geometry::Matrix<4> {
  float f = _perspective.far;
  float n = _perspective.near;

  float horizontal_fov = _perspective.aspect_ratio * (_perspective.fov.radians() / 2.0F);
  float r              = std::tan(horizontal_fov) * n;
  float l              = -r;

  float vertical_fov = (_perspective.fov.radians() / 2.0F);
  float t            = std::tan(vertical_fov) * n;
  float b            = -t;

  return {
    {2.0F * n / (r - l), 0.0F, -((r + l) / (r - l)), 0.0F},
    {0.0F, 2.0F * n / (t - b), -((t + b) / (t - b)), 0.0F},
    {0.0F, 0.0F, (f + n) / (f - n), -(2.0F * f * n) / (f - n)},
    {0.0F, 0.0F, 1.0F, 0.0F},
  };
}

auto Camera::orthographic_projection_matrix() const -> geometry::Matrix<4> {
  geometry::Matrix<4> scale_matrix;
  scale_matrix[0][0] = 2.0F / (_orthographic.right - _orthographic.left);
  scale_matrix[1][1] = 2.0F / (_orthographic.top - _orthographic.bot);
  scale_matrix[2][2] = 2.0F / (_orthographic.far - _orthographic.near);

  geometry::Vector<3> translation(
    -(_orthographic.left + _orthographic.right) / 2.0F,
    -(_orthographic.bot + _orthographic.top) / 2.0F,
    -(_orthographic.near + _orthographic.far) / 2.0F);

  return scale_matrix.translate(translation);
}
