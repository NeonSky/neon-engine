#include "logger.hpp"

#include <glad/glad.h>
#include <string>

using namespace engine::debug;

// https://www.khronos.org/opengl/wiki/OpenGL_Error#Meaning_of_errors
auto checkGLError(const char* file, int line) -> bool {
  bool was_error = false;
  for (GLenum gl_err = glGetError(); gl_err != GL_NO_ERROR; gl_err = glGetError()) {
    LOG_ERROR("OpenGL error #" + std::to_string(gl_err) + " in " + file + " at line: " + std::to_string(line));
    was_error = true;
  }
  return was_error;
}

void Logger::set_profile(Logger::Profile profile) {
  switch (profile) {
  case Profile::DEBUG:
    apply_debug_profile();
    break;
  case Profile::DEV:
    apply_dev_profile();
    break;
  case Profile::RELEASE:
    apply_release_profile();
    break;
  }
}

void Logger::apply_debug_profile() {
  spdlog::set_level(spdlog::level::debug);
}

void Logger::apply_dev_profile() {
  spdlog::set_level(spdlog::level::info);
}

void Logger::apply_release_profile() {
  spdlog::set_level(spdlog::level::err);
}
