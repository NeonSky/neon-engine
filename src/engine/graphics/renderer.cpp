#include "renderer.hpp"

#include "../geometry/transform.hpp"
#include "../scene/component/root.hpp"
#include "component/render_info.hpp"
#include "system/cuboid_renderer.hpp"
#include "system/global_transform_updater.hpp"
#include "system/line_renderer.hpp"
#include "system/rectangle_renderer.hpp"

#include <glad/glad.h>

#include <stack>

using namespace engine;
using namespace engine::graphics;

Renderer::Renderer(os::WindowManager& wm)
        : _wm(wm) {

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

  _wm.on_window_created([this]([[maybe_unused]] unsigned int window_id) {
    _wm.set_render_target(window_id);
    _render_contexts.push_back(api::create_context(api::GraphicsAPI::OPENGL));
    _wm.set_render_target(_current_context);
  });

  _wm.on_window_closed([this](unsigned int window_id) {
    _render_contexts.erase(_render_contexts.begin() + window_id);
  });

  for (unsigned int i = 0; i < _wm.window_count(); i++) {
    _wm.set_render_target(i);
    _render_contexts.push_back(api::create_context(api::GraphicsAPI::OPENGL));
  }

  _wm.set_render_target(0);

  _render_systems.push_back(std::make_unique<system::GlobalTransformUpdater>());
  _render_systems.push_back(std::make_unique<system::LineRenderer>());
  _render_systems.push_back(std::make_unique<system::RectangleRenderer>());
  _render_systems.push_back(std::make_unique<system::CuboidRenderer>());
}

void Renderer::render(architecture::ECS& ecs,
                      unsigned int window_id,
                      geometry::Matrix<4> view_projection) {
  if (!_wm.is_target_available(window_id)) {
    LOG_WARNING("Can't render to window with ID " + std::to_string(window_id) + " since that target is currently not available.");
    return;
  }
  _wm.set_render_target(window_id);
  _current_context = window_id;

  _wm.clear_target();

  // Ensure root has updated RenderInfo
  auto root = ecs.view<scene::component::Root>()[0];
  ecs.emplace_or_replace<component::RenderInfo>(root, view_projection, current_context());

  for (auto& system : _render_systems)
    system->update(ecs);

  _wm.refresh_target();
}

auto Renderer::current_context() -> api::IContext& {
  return *_render_contexts[_current_context];
}

auto Renderer::context_count() const -> unsigned int {
  return _render_contexts.size();
}
