#include "rubiks_cube_system.hpp"

#include "rubiks_cube.hpp"

#include "../engine/graphics/component/global_transform.hpp"
#include "../engine/graphics/component/render_info.hpp"

using namespace app;
using namespace engine;

void RubiksCubeSystem::update(architecture::ECS& ecs) {
  auto& render_info = ecs.get<graphics::component::RenderInfo>(ecs.view<graphics::component::RenderInfo>()[0]);
  // auto& ctx         = render_info.context.get();

  for (auto entity : ecs.view<RubiksCube>())
    ecs.get<RubiksCube>(entity).render(render_info.view_projection * ecs.get<graphics::component::GlobalTransform>(entity).matrix);
  // ecs.get<RubiksCube>(entity).render(ctx, render_info.view_projection);
}
