#include "application.hpp"

#include "../../../debug/logger.hpp"

#include "context.hpp"

// NOTE: OpenGL headers.
#include <glad/glad.h>

using namespace engine::graphics::api::opengl;

Application::Application() {

  LOG_INFO("OpenGL version: " + std::string((const char*) glGetString(GL_VERSION)));
  LOG_INFO("OpenGL renderer: " + std::string((const char*) glGetString(GL_RENDERER)));
  LOG_INFO("OpenGL vendor: " + std::string((const char*) glGetString(GL_VENDOR)));

  GLint extension_count = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count);
  LOG_INFO(std::to_string(extension_count) + " OpenGL extensions found.");
  for (int i = 0; i < extension_count; i++)
    LOG_INFO("Extension " + std::to_string(i + 1) + ": " + std::string((const char*) glGetStringi(GL_EXTENSIONS, i)));

  LOG_INFO("Primary GLSL version: " + std::string((const char*) glGetString(GL_SHADING_LANGUAGE_VERSION)));

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback([](GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            [[maybe_unused]] GLsizei length,
                            const GLchar* message,
                            [[maybe_unused]] const void* userParam) {
    // Ignore notifications for now.
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
      return;

    // https://www.khronos.org/opengl/wiki/Debug_Output
    LOG_WARNING("Received OpenGL debug message!");

    std::string source_name = "Unknown.";
    if (source == GL_DEBUG_SOURCE_API)
      source_name = "Call(s) to the OpenGL API.";
    else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM)
      source_name = "Call(s) to a window-system API.";
    else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER)
      source_name = "The shading language compiler.";
    else if (source == GL_DEBUG_SOURCE_THIRD_PARTY)
      source_name = "Some application associated with OpenGL.";
    else if (source == GL_DEBUG_SOURCE_APPLICATION)
      source_name = "The user application.";

    LOG_WARNING("Source: " + source_name);

    std::string type_name = "Unknown.";
    if (type == GL_DEBUG_TYPE_ERROR)
      type_name = "Error.";
    else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
      type_name = "Deprecated behavior.";
    else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
      type_name = "Undefined behavior.";
    else if (type == GL_DEBUG_TYPE_PORTABILITY)
      type_name = "Portability.";
    else if (type == GL_DEBUG_TYPE_PERFORMANCE)
      type_name = "Performance.";
    else if (type == GL_DEBUG_TYPE_MARKER)
      type_name = "Marker.";
    else if (type == GL_DEBUG_TYPE_PUSH_GROUP)
      type_name = "Push group.";
    else if (type == GL_DEBUG_TYPE_POP_GROUP)
      type_name = "Pop group.";

    LOG_WARNING("Type: " + type_name);
    LOG_WARNING("ID: " + std::to_string((int) id));

    std::string severity_name = "Unknown";
    if (severity == GL_DEBUG_SEVERITY_HIGH)
      severity_name = "High --- All OpenGL Errors, shader compilation/linking errors, or highly-dangerous undefined behavior.";
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM)
      severity_name = "Medium --- Major performance warnings, shader compilation/linking warnings, or the use of deprecated functionality.";
    else if (severity == GL_DEBUG_SEVERITY_LOW)
      severity_name = "Low --- Redundant state change performance warning, or unimportant undefined behavior.";
    else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
      severity_name = "Notification --- Anything that isn't an error or performance issue.";

    LOG_WARNING("Severity: " + severity_name);
    LOG_WARNING("Message: " + std::string(message));

    if (severity == GL_DEBUG_SEVERITY_HIGH)
      LOG_ERROR("Throwing error because of high severity.");
  },
                         nullptr);
}

auto Application::create_context() -> std::unique_ptr<IContext> {
  return std::make_unique<Context>();
}
