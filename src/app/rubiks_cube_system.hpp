#pragma once

#include "../engine/architecture/ecs.hpp"

namespace app {

  class RubiksCubeSystem : public engine::architecture::IEntitySystem {
  public:
    void update(engine::architecture::ECS& ecs) override;
  };

}
