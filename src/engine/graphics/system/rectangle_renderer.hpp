#pragma once

#include "../../architecture/ecs.hpp"

#include "../api/context.hpp"
#include "../component/rectangle.hpp"
#include "../shader.hpp"

namespace engine::graphics::system {

  class RectangleRenderer : public architecture::IEntitySystem {
  public:
    RectangleRenderer();

    void update(architecture::ECS& ecs) override;

  private:
    graphics::Shader _shader;

    static void compile_rectangle(api::IContext& ctx, component::Rectangle& rectangle);
  };

}
