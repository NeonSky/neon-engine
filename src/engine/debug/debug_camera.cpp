#include "debug_camera.hpp"

#include "../../engine/debug/logger.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>

using namespace engine::debug;

DebugCamera::DebugCamera(const os::InputManager& input_manager)
        : _input_manager(input_manager) {}

DebugCamera::DebugCamera(const os::InputManager& input_manager, const geometry::Rigidbody& rigidbody)
        : _camera(graphics::Camera(rigidbody)),
          _input_manager(input_manager) {

  _input_manager.on_key([this](const os::Window& w, os::KeyCode k, os::KeyAction a, [[maybe_unused]] const os::ActivatedModifiers& mods) {
    on_key(w, k, a);
  });

  _input_manager.on_mouse_move([this](const os::Window& w, float x, float y) {
    on_mouse_move(w, x, y);
  });

  _input_manager.on_mouse_scroll([this](const os::Window& w, float x, float y) {
    on_mouse_scroll(w, x, y);
  });
}

// Mutators
auto DebugCamera::rigidbody() -> geometry::Rigidbody& {
  return _camera.rigidbody();
}

// Accessors
auto DebugCamera::view_matrix() const -> geometry::Matrix<4> {
  return _camera.view_matrix();
}

auto DebugCamera::projection_matrix() const -> geometry::Matrix<4> {
  return _camera.projection_matrix(_projection_type);
}

auto DebugCamera::mouse_ray() const -> geometry::Vector<3> {
  return _mouse_ray;
}

void DebugCamera::on_key(const os::Window& window, os::KeyCode keycode, os::KeyAction action) {
  if (keycode == GLFW_KEY_W)
    _camera.move(graphics::Direction::FORWARD);
  if (keycode == GLFW_KEY_S)
    _camera.move(graphics::Direction::BACKWARD);
  if (keycode == GLFW_KEY_D)
    _camera.move(graphics::Direction::RIGHT);
  if (keycode == GLFW_KEY_A)
    _camera.move(graphics::Direction::LEFT);
  if (keycode == GLFW_KEY_E)
    _camera.move(graphics::Direction::UP);
  if (keycode == GLFW_KEY_Q)
    _camera.move(graphics::Direction::DOWN);

  if (keycode == GLFW_KEY_F && action == os::KeyAction::PRESS)
    _camera.rigidbody().orientation().flip();

  if (keycode == GLFW_KEY_P && action == os::KeyAction::PRESS) {
    if (_projection_type == graphics::ProjectionType::PERSPECTIVE)
      _projection_type = graphics::ProjectionType::ORTHOGRAPHIC;
    else
      _projection_type = graphics::ProjectionType::PERSPECTIVE;
  }

  if (keycode == GLFW_KEY_T && action == os::KeyAction::PRESS) {
    _free_look_mode = !_free_look_mode;
    if (_free_look_mode)
      window.lock_mouse_cursor();
    else
      window.release_mouse_cursor();
  }
}

void DebugCamera::on_mouse_move(const os::Window& window, float xpos, float ypos) {
  // Viewport Space [0:width, 0:height]
  float x = xpos;
  float y = ((float) window.height()) - ypos; // In OpenGL, (0, 0) is bot-left. We want (0, 0) to be top-left. TODO: Do we?

  // Normalized Device Space [-1:1, -1:1, -1:1]
  geometry::Vector<3> ndc(2.0F * (x / (float) window.width()) - 1.0F,
                          2.0F * (y / (float) window.height()) - 1.0F,
                          -1.0F); // z = -1.0f since cursor points along camera's forward direction.

  // Homogeneous Clip Space [-1:1, -1:1, -1:1, -1:1]
  geometry::Vector<4> clip_coords(ndc.x(), ndc.y(), ndc.z(), 1.0F);

  // View Space (Eye Space) [-inf:inf, -inf:inf, -inf:inf, -inf:inf]
  geometry::Vector<4> view_coords(geometry::Vector<3>(projection_matrix().inverse() * clip_coords), 0.0F);

  // World Space [-inf:inf, -inf:inf, -inf:inf, -inf:inf]
  geometry::Vector<4> world_coords = view_matrix().inverse() * view_coords;

  // Normalized 3D vector form
  _mouse_ray = geometry::Vector<3>(world_coords).normalized();

  if (_free_look_mode)
    _camera.lookat_mouse(x, y);
}

void DebugCamera::on_mouse_scroll([[maybe_unused]] const os::Window& window, [[maybe_unused]] float xoffset, float yoffset) {
  _zoom = std::clamp(_zoom + yoffset, debug::DebugCamera::zoom_min, debug::DebugCamera::zoom_max);
  _camera.set_zoom(_zoom);
}
