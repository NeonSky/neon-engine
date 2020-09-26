#pragma once

#include "../../architecture/ecs.hpp"

namespace engine::graphics::system {

  struct GlobalTransformUpdater : public architecture::IEntitySystem {
    void update(architecture::ECS& _ecs) override;
  };

}
