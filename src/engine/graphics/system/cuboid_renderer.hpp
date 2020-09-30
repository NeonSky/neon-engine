#pragma once

#include "../../architecture/ecs.hpp"

#include "../api/context.hpp"
#include "../component/cuboid.hpp"
#include "../shader.hpp"

namespace engine::graphics::system {

  class CuboidRenderer : public architecture::IEntitySystem {
  public:
    CuboidRenderer();

    void update(architecture::ECS& ecs) override;

  private:
    graphics::Shader _shader;
    bool _draw_corners = false;

    static void compile_cuboid(api::IContext& ctx, component::Cuboid& cuboid);
  };

}
