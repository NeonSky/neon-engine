#include "window_manager.hpp"

// Include extension loader library (glad) to expose latest OpenGL version and features.
#include <glad/glad.h>

// Include GLFW, but not its default OpenGL headers.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace engine;
using namespace engine::os;

unsigned int WindowManager::_instances = 0;

WindowManager::WindowManager()
        : _current(0) {

  _instances++;
  if (_instances > 1)
    // NOTE: The problem is that they would affect each other since they share the same GLFW state machine.
    LOG_ERROR("Multiple WindowManager instances is currently not supported.");

  glfwSetErrorCallback([](int error_code, const char* description) {
    LOG_WARNING("GLFW error (code " + std::to_string(error_code) + "): " + description);
  });

  // NOTE: Additional calls to glfwInit() after successful initialization but before termination will return GLFW_TRUE immediately.
  if (glfwInit() == GLFW_FALSE)
    LOG_CRITICAL("Failed to initialize GLFW.");

  // Create the first window and set it as ours first render target.
  // GLFW needs to have a OpenGL context before glad can inject OpenGL features to GLFW.
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  _base_window = std::make_unique<Window>(1, 1);
  _base_window->set_as_current();

  // Have glad inject the latest OpenGL features to GLFW.
  if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0)
    LOG_CRITICAL("Failed to setup glad.");

  glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

  create_window();
  create_window();

  set_render_target(_current);

  LOG_INFO("GLFW version: " + std::string(glfwGetVersionString()));
}

WindowManager::~WindowManager() {
  _instances--;
  glfwMakeContextCurrent(nullptr);
  glfwTerminate();
}

/// @todo Move gui to another package.
void WindowManager::create_window() {
  _windows.push_back(std::make_unique<Window>(1920, 1080, "Application", *_base_window));
  unsigned int id = _windows.size() - 1;

  _input_manager.add_window(*_windows[id]);

  _windows[id]->on_should_close([this, id]() {
    LOG_INFO("Closing window with ID " + std::to_string(id) + ".");
    _input_manager.remove_window(*_windows[id]);
    destroy_window(id);
  });
  // _windows.back()->init_gui();
}

void WindowManager::destroy_window(unsigned int window_id) {
  _input_manager.remove_window(*_windows[window_id]);

  _windows.erase(_windows.begin() + window_id);

  if (window_id < _current)
    _current--;
  else if (window_id == _current)
    _current = 0;

  for (auto& c : _on_window_closed_callbacks)
    c(window_id);

  if (_windows.empty())
    for (auto& c : _on_all_windows_closed_callbacks)
      c();
}

void WindowManager::set_render_target(unsigned int window_id) {
  _current = window_id;
  _windows[_current]->set_as_current();
}

void WindowManager::clear_target() {
  _windows[_current]->clear_screen();
}

void WindowManager::refresh_target() {
  _windows[_current]->update();
}

auto WindowManager::input_manager() const -> const InputManager& {
  return _input_manager;
}

auto WindowManager::is_target_available(unsigned int window_id) const -> bool {
  return window_id < _windows.size();
}

auto WindowManager::render_target() const -> const Window& {
  return *_windows[_current];
}

auto WindowManager::window_count() const -> unsigned int {
  return _windows.size();
}

void WindowManager::on_window_created(const std::function<void(unsigned int)>& callback) const {
  _on_window_created_callbacks.push_back(callback);
}

void WindowManager::on_window_closed(const std::function<void(unsigned int)>& callback) const {
  _on_window_closed_callbacks.push_back(callback);
}

void WindowManager::on_all_windows_closed(const std::function<void()>& callback) const {
  _on_all_windows_closed_callbacks.push_back(callback);
}
