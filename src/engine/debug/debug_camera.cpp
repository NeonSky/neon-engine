#include "debug_camera.hpp"

#include "../../engine/debug/logger.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <algorithm>

using namespace engine::debug;

DebugCamera::DebugCamera(engine::gui::Window* window)
        : window(window) {}

DebugCamera::DebugCamera(engine::gui::Window* window, const engine::geometry::Transform& transform)
        : camera(engine::graphics::Camera(transform)),
          window(window) {
  this->window->add_on_key_callback([this](GLFWwindow* w, [[maybe_unused]] int n) { on_key(w); });
  this->window->add_on_mouse_move_callback([this](GLFWwindow* w, float x, float y) { on_cursor(w, x, y); });
  this->window->add_on_mouse_scroll_callback([this](GLFWwindow* w, float x, float y) { on_scroll(w, x, y); });
}

// Mutators
void DebugCamera::set_transform(const engine::geometry::Transform& transform) {
  this->camera.transform = transform;
};

// Accessors
auto DebugCamera::transform() const -> engine::geometry::Transform {
  return this->camera.transform;
}

auto DebugCamera::view_matrix() const -> glm::mat4 {
  return this->camera.view_matrix();
}

auto DebugCamera::projection_matrix() const -> glm::mat4 {
  return this->camera.projection_matrix(this->projection_type);
}

auto DebugCamera::mouse_ray() const -> glm::vec3 {
  return this->_mouse_ray;
}

// Privates
void DebugCamera::on_key(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_W) != 0)
    this->camera.move(engine::graphics::Direction::FORWARD);
  if (glfwGetKey(window, GLFW_KEY_S) != 0)
    this->camera.move(engine::graphics::Direction::BACKWARD);
  if (glfwGetKey(window, GLFW_KEY_D) != 0)
    this->camera.move(engine::graphics::Direction::RIGHT);
  if (glfwGetKey(window, GLFW_KEY_A) != 0)
    this->camera.move(engine::graphics::Direction::LEFT);
  if (glfwGetKey(window, GLFW_KEY_E) != 0)
    this->camera.move(engine::graphics::Direction::UP);
  if (glfwGetKey(window, GLFW_KEY_Q) != 0)
    this->camera.move(engine::graphics::Direction::DOWN);

  if (glfwGetKey(window, GLFW_KEY_P) != 0) {
    if (this->projection_type == engine::graphics::ProjectionType::PERSPECTIVE)
      this->projection_type = engine::graphics::ProjectionType::ORTHOGRAPHIC;
    else
      this->projection_type = engine::graphics::ProjectionType::PERSPECTIVE;
  }

  if (glfwGetKey(window, GLFW_KEY_T) != 0) {
    this->free_look_mode = !this->free_look_mode;
    if (this->free_look_mode)
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

void DebugCamera::on_cursor(GLFWwindow* window, float xpos, float ypos) {
  int width;
  int height;
  glfwGetWindowSize(window, &width, &height);

  // Viewport Space [0:width, 0:height]
  float x = xpos;
  float y = ((float) height) - ypos; // In OpenGL, (0, 0) is top-left. We want (0, 0) to be bot-left.

  // Normalized Device Space [-1:1, -1:1, -1:1]
  glm::vec3 ndc(2.0F * (x / (float) width) - 1.0F, 2.0F * (y / (float) height) - 1.0F, -1.0F); // z = -1.0f since cursor points along camera's forward direction.

  // Homogeneous Clip Space [-1:1, -1:1, -1:1, -1:1]
  glm::vec4 clip_coords(ndc.x, ndc.y, ndc.z, 1.0F);

  // View Space (Eye Space) [-inf:inf, -inf:inf, -inf:inf, -inf:inf]
  glm::vec4 view_coords(glm::vec3(glm::inverse(projection_matrix()) * clip_coords), 0.0F);

  // World Space [-inf:inf, -inf:inf, -inf:inf, -inf:inf]
  glm::vec4 world_coords = glm::inverse(view_matrix()) * view_coords;

  // Normalized 3D vector form
  this->_mouse_ray = glm::normalize(glm::vec3(world_coords));

  if (this->free_look_mode)
    this->camera.lookat_mouse(x, y);
}

void DebugCamera::on_scroll([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] float xoffset, float yoffset) {
  this->zoom = std::clamp(this->zoom + yoffset, engine::debug::DebugCamera::zoom_min, engine::debug::DebugCamera::zoom_max);
  this->camera.set_zoom(this->zoom);
}
