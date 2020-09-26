#pragma once

#include "../../architecture/ecs.hpp"

#include "../component/cuboid.hpp"
#include "../opengl/context.hpp"
#include "../shader.hpp"

namespace engine::graphics::system {

  class CuboidRenderer : public architecture::IEntitySystem {
  public:
    CuboidRenderer();

    void update(architecture::ECS& ecs) override;

  private:
    graphics::Shader _shader;
    bool _draw_corners = true;

    void compile_cuboid(opengl::Context& ctx, component::Cuboid& cuboid);
  };

}
