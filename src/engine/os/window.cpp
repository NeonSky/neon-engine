#include "window.hpp"
#include "../debug/logger.hpp"

#include "../graphics/api/opengl/context.hpp"
#include "../graphics/api/vulkan/application.hpp"
#include "../graphics/api/vulkan/context.hpp"

#include <glad/glad.h>

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <stdexcept>

using namespace engine::os;

Window::Window()
        : Window(1280, 720) {}

Window::Window(unsigned int width, unsigned int height)
        : Window(width, height, "Application") {}

Window::Window(unsigned int width, unsigned int height, const char* title)
        : Window(width, height, title, nullptr, nullptr) {}

Window::Window(unsigned int width, unsigned int height, const char* title, Window& parent, graphics::api::IApplication& app)
        : Window(width, height, title, &parent, &app) {}

Window::Window(unsigned int width, unsigned int height, const char* title, Window* parent, graphics::api::IApplication* app)
        : _title(title),
          _width(width),
          _height(height),
          _clear_color(0.2F, 0.2F, 0.2F, 1.0F) {

  // NOTE: Additional calls to glfwInit() after successful initialization but before termination will return GLFW_TRUE immediately.
  if (glfwInit() == GLFW_FALSE)
    LOG_CRITICAL("Failed to initialize GLFW.");

  GLFWwindow* glfw_window_parent = nullptr;
  if (parent != nullptr)
    glfw_window_parent = parent->_window.get();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  _window = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>(
    // glfwCreateWindow((int) width, (int) height, title, nullptr, glfw_window_parent),
    glfwCreateWindow((int) width, (int) height, title, nullptr, nullptr),
    [](GLFWwindow* window) {
      glfwDestroyWindow(window);
    });

  if (_window == nullptr)
    LOG_CRITICAL("Failed to create GLFW window.");

  // GLFWwindow* prev_context = glfwGetCurrentContext();
  // glfwMakeContextCurrent(_window.get());

  // Vertical synchronization
  // glfwSwapInterval(1);

  // Multisample anti-aliasing (MSAA). OpenGL needs to be initialized first though.
  // CHECK_GL_ERROR();
  // glEnable(GL_MULTISAMPLE);
  // glfwWindowHint(GLFW_SAMPLES, 4); // 4 subsamples per screen coordinate
  // CHECK_GL_ERROR();

  // Any callbacks are owned by `this`
  glfwSetWindowUserPointer(_window.get(), reinterpret_cast<void*>(this));

  glfwSetWindowCloseCallback(_window.get(), []([[maybe_unused]] GLFWwindow* window) {
    auto* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    for (auto& c : w->_on_should_close_callbacks)
      c();
  });

  glfwSetKeyCallback(_window.get(), [](GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, int mods) {
    auto* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    ActivatedModifiers modifiers;
    modifiers.shift     = (bool) (mods & 0x01);
    modifiers.control   = (bool) (mods & 0x02);
    modifiers.alt       = (bool) (mods & 0x04);
    modifiers.super     = (bool) (mods & 0x08);
    modifiers.caps_lock = (bool) (mods & 0x10);
    modifiers.num_lock  = (bool) (mods & 0x20);

    for (auto& c : w->_on_key_callbacks)
      c(key, static_cast<KeyAction>(action), modifiers);
  });

  glfwSetMouseButtonCallback(_window.get(), [](GLFWwindow* window, int button, int action, int mods) {
    auto* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    ActivatedModifiers modifiers;
    modifiers.shift     = (bool) (mods & 0x01);
    modifiers.control   = (bool) (mods & 0x02);
    modifiers.alt       = (bool) (mods & 0x04);
    modifiers.super     = (bool) (mods & 0x08);
    modifiers.caps_lock = (bool) (mods & 0x10);
    modifiers.num_lock  = (bool) (mods & 0x20);

    for (auto& c : w->_on_mouse_click_callbacks)
      c(button, static_cast<MouseAction>(action), modifiers);
  });

  glfwSetCursorPosCallback(_window.get(), [](GLFWwindow* window, double xpos, double ypos) {
    auto* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    for (auto& c : w->_on_mouse_move_callbacks)
      c(xpos, ypos);
  });

  glfwSetScrollCallback(_window.get(), [](GLFWwindow* window, double xoffset, double yoffset) {
    auto* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    for (auto& c : w->_on_mouse_scroll_callbacks)
      c(xoffset, yoffset);
  });

  if (parent != nullptr) {
    // _graphics_context = std::make_unique<graphics::api::opengl::Context>();

    LOG_DEBUG("ASD");
    auto* a = dynamic_cast<graphics::api::vulkan::Application*>(app);
    if (a != nullptr) {
      _graphics_context = a->create_context([this](VkInstance& instance) {
        VkSurfaceKHR surface;
        // glfwSetWindowAttrib(_window.get(), GLFW_CLIENT_API, GLFW_NO_API);
        if (glfwCreateWindowSurface(instance, _window.get(), nullptr, &surface) != VK_SUCCESS)
          LOG_ERROR("Failed to create window surface.");
        return surface;
      });
      a->run();
    }
  }

  // glfwMakeContextCurrent(prev_context);
}

void Window::lock_mouse_cursor() const {
  glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::release_mouse_cursor() const {
  glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::hide_mouse_cursor() const {
  glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::set_as_current() {
  // glfwMakeContextCurrent(_window.get());
}

/// @todo Document "(void) io;" usage.
void Window::init_gui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void) io;
  ImGui::StyleColorsDark();

  std::string glsl_version = "#version 420";
  ImGui_ImplGlfw_InitForOpenGL(_window.get(), true);
  ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void Window::update() {
  glfwSwapBuffers(_window.get());
  glfwPollEvents();
}

void Window::clear_screen() const {
  glClearColor(_clear_color.r(), _clear_color.g(), _clear_color.b(), _clear_color.a());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::toggle_fullscreen() {
  GLFWmonitor* primary = glfwGetPrimaryMonitor();
  glfwSetWindowMonitor(_window.get(), primary, 0, 0, 1920, 1080, 60);
}

void Window::on_should_close(const std::function<void()>& callback) const {
  _on_should_close_callbacks.push_back(callback);
}

auto Window::graphics_context() const -> graphics::api::IContext& {
  return *_graphics_context;
}

auto Window::title() const -> std::string {
  return _title;
}

auto Window::is_closing() const -> bool {
  return glfwWindowShouldClose(_window.get()) != 0;
}

auto Window::width() const -> unsigned int {
  return _width;
}

auto Window::height() const -> unsigned int {
  return _height;
}

auto Window::is_key_down(int keycode) const -> bool {
  int status = glfwGetKey(_window.get(), keycode);
  return (status == GLFW_PRESS || status == GLFW_REPEAT);
}

void Window::on_key(const std::function<void(KeyCode, KeyAction, const ActivatedModifiers&)>& callback) const {
  _on_key_callbacks.push_back(callback);
}

void Window::on_mouse_click(const std::function<void(MouseCode, MouseAction, const ActivatedModifiers&)>& callback) const {
  _on_mouse_click_callbacks.push_back(callback);
}

void Window::on_mouse_move(const std::function<void(float, float)>& callback) const {
  _on_mouse_move_callbacks.push_back(callback);
}

void Window::on_mouse_scroll(const std::function<void(float, float)>& callback) const {
  _on_mouse_scroll_callbacks.push_back(callback);
}
