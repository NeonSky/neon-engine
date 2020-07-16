#include "camera.hpp"
#include "../debug/logger.hpp"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace engine::graphics;

// FIXME
bool firstMouse = true;
float lastX;
float lastY;
float yaw   = 0.0F;
float pitch = 0.0F;

Camera::Camera() : Camera(geometry::Transform()) {}
Camera::Camera(const geometry::Transform& transform)
        : _transform(transform) {

  yaw   = _transform.yaw();
  pitch = _transform.pitch();
}

auto Camera::transform() -> geometry::Transform& {
  return _transform;
}

void Camera::move(Direction move_dir) {
  glm::vec3 displacement_dir;
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
  _perspective.fov = 45.0F - zoom_level;
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

  pitch = std::clamp(pitch, -glm::half_pi<float>(), glm::half_pi<float>());

  _transform.set_rotation(yaw, pitch, 0.0F);
}

auto Camera::view_matrix() const -> glm::mat4 {

  glm::mat3 base_vectors_in_world_space(
    _transform.right(),  // (R_x, R_y, R_z)
    _transform.up(),     // (U_x, U_y, U_z)
    _transform.forward() // (F_x, F_y, F_z)
  );

  // NOTE: transpose = inverse, since the matrix is an orthonormal base.
  glm::mat3 inverse_base = glm::transpose(base_vectors_in_world_space);

  return glm::mat4(inverse_base) * glm::translate(-_transform.position);
}

auto Camera::projection_matrix(ProjectionType projection_type) const -> glm::mat4 {
  switch (projection_type) {
  case ProjectionType::PERSPECTIVE:
    return glm::perspectiveLH(
      glm::radians(_perspective.fov),
      _perspective.aspect_ratio,
      _perspective.near,
      _perspective.far);
  case ProjectionType::ORTHOGRAPHIC:
    return glm::ortho(
      _orthographic.left,
      _orthographic.right,
      _orthographic.bot,
      _orthographic.top,
      _orthographic.near,
      _orthographic.far);
  default:
    LOG_ERROR("Projection type not supported: " + std::to_string(projection_type));
  }
}
