#pragma once

#include "../../architecture/ecs.hpp"

#include "../component/rectangle.hpp"
#include "../opengl/context.hpp"
#include "../shader.hpp"

namespace engine::graphics::system {

  class RectangleRenderer : public architecture::IEntitySystem {
  public:
    RectangleRenderer();

    void update(architecture::ECS& ecs) override;

  private:
    graphics::Shader _shader;

    static void compile_rectangle(opengl::Context& ctx, component::Rectangle& rectangle);
  };

}
