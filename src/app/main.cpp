#include "../engine/debug/logger.hpp"
#include "../engine/gui/window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <string>


int main() {
  srand(time(NULL));

  engine::debug::Logger::set_profile(engine::debug::Logger::Profile::DEBUG);
  LOG_INFO("Program started.");
  auto start = std::chrono::system_clock::now();

  engine::gui::Window *window;
  try {
    window = new engine::gui::Window(1920, 1080, "Application");
  } catch(const std::exception& e) {
    LOG_ERROR(e.what());
    return -1;
  }

  int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  if (!status) {
    LOG_ERROR("Failed to init GLAD");
    glfwTerminate();
    return -1;
  }

  LOG_INFO("OpenGL version: " + std::string((const char*)glGetString(GL_VERSION)));
  LOG_INFO("OpenGL renderer: " + std::string((const char*)glGetString(GL_RENDERER)));
  LOG_INFO("OpenGL vendor: " + std::string((const char*)glGetString(GL_VENDOR)));

  CHECK_GL_ERROR();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  window->init_gui();

  CHECK_GL_ERROR();
  while (!window->is_closing()) {

    window->clear_screen();
    glUseProgram(0);
    window->update();

    CHECK_GL_ERROR();
  }

  auto end = std::chrono::system_clock::now();
  LOG_INFO("Program terminated.");

  std::chrono::duration<double> elapsed_seconds = end - start;
  LOG_INFO("Uptime: " + std::to_string(elapsed_seconds.count()) + " seconds.");
}

