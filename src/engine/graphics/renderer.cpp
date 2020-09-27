#include "renderer.hpp"

#include "../geometry/transform.hpp"
#include "../scene/component/root.hpp"
#include "component/render_info.hpp"
#include "system/cuboid_renderer.hpp"
#include "system/global_transform_updater.hpp"
#include "system/line_drawer.hpp"
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

  _wm.on_window_created([this]([[maybe_unused]] unsigned int window_id) {
    _wm.set_render_target(window_id);
    _render_contexts.emplace_back();
    _wm.set_render_target(_current_context);
  });

  _wm.on_window_closed([this](unsigned int window_id) {
    _render_contexts.erase(_render_contexts.begin() + window_id);
  });

  for (unsigned int i = 0; i < _wm.window_count(); i++) {
    _wm.set_render_target(i);
    _render_contexts.emplace_back();
  }

  _wm.set_render_target(0);

  _render_systems.push_back(std::make_unique<system::GlobalTransformUpdater>());
  _render_systems.push_back(std::make_unique<system::LineDrawer>());
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

auto Renderer::current_context() -> opengl::Context& {
  return _render_contexts[_current_context];
}

auto Renderer::context_count() const -> unsigned int {
  return _render_contexts.size();
}
