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

  _wm.clear_target();

  // Ensure root has updated RenderInfo
  auto root = ecs.view<scene::component::Root>()[0];
  ecs.emplace_or_replace<component::RenderInfo>(root, view_projection, _wm.render_target().graphics_context());

  for (auto& system : _render_systems)
    system->update(ecs);

  _wm.refresh_target();
}
