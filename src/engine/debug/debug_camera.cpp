#include "debug_camera.hpp"

#include "../../engine/debug/logger.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>

using namespace engine::debug;

DebugCamera::DebugCamera(engine::gui::Window* window)
        : _window(window) {}

DebugCamera::DebugCamera(engine::gui::Window* window, const engine::geometry::Transform& transform)
        : _camera(engine::graphics::Camera(transform)),
          _window(window) {

  _window->add_on_key_callback([this](GLFWwindow* w, [[maybe_unused]] int n) { on_key(w); });
  _window->add_on_mouse_move_callback([this](GLFWwindow* w, float x, float y) { on_cursor(w, x, y); });
  _window->add_on_mouse_scroll_callback([this](GLFWwindow* w, float x, float y) { on_scroll(w, x, y); });
}

// Mutators
auto DebugCamera::transform() -> engine::geometry::Transform& {
  return _camera.transform();
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

// Privates
void DebugCamera::on_key(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_W) != 0)
    _camera.move(engine::graphics::Direction::FORWARD);
  if (glfwGetKey(window, GLFW_KEY_S) != 0)
    _camera.move(engine::graphics::Direction::BACKWARD);
  if (glfwGetKey(window, GLFW_KEY_D) != 0)
    _camera.move(engine::graphics::Direction::RIGHT);
  if (glfwGetKey(window, GLFW_KEY_A) != 0)
    _camera.move(engine::graphics::Direction::LEFT);
  if (glfwGetKey(window, GLFW_KEY_E) != 0)
    _camera.move(engine::graphics::Direction::UP);
  if (glfwGetKey(window, GLFW_KEY_Q) != 0)
    _camera.move(engine::graphics::Direction::DOWN);

  if (glfwGetKey(window, GLFW_KEY_F) != 0)
    _camera.transform().orientation().flip();

  if (glfwGetKey(window, GLFW_KEY_P) != 0) {
    if (_projection_type == engine::graphics::ProjectionType::PERSPECTIVE)
      _projection_type = engine::graphics::ProjectionType::ORTHOGRAPHIC;
    else
      _projection_type = engine::graphics::ProjectionType::PERSPECTIVE;
  }

  if (glfwGetKey(window, GLFW_KEY_T) != 0) {
    _free_look_mode = !_free_look_mode;
    if (_free_look_mode)
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

void DebugCamera::on_cursor(GLFWwindow* window, float xpos, float ypos) {
  int width  = 0;
  int height = 0;
  glfwGetWindowSize(window, &width, &height);

  // Viewport Space [0:width, 0:height]
  float x = xpos;
  float y = ((float) height) - ypos; // In OpenGL, (0, 0) is top-left. We want (0, 0) to be bot-left.

  // Normalized Device Space [-1:1, -1:1, -1:1]
  geometry::Vector<3> ndc(2.0F * (x / (float) width) - 1.0F, 2.0F * (y / (float) height) - 1.0F, -1.0F); // z = -1.0f since cursor points along camera's forward direction.

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

void DebugCamera::on_scroll([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] float xoffset, float yoffset) {
  _zoom = std::clamp(_zoom + yoffset, engine::debug::DebugCamera::zoom_min, engine::debug::DebugCamera::zoom_max);
  _camera.set_zoom(_zoom);
}
