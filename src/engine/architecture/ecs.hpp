#pragma once

#include <entt/entt.hpp>

namespace engine::architecture {
  using ECS                       = entt::registry;
  using EntityID                  = entt::entity;
  constexpr EntityID NullEntityID = entt::null;

  struct IEntitySystem {
    virtual ~IEntitySystem() = 0;

    virtual void update(ECS& ecs) = 0;
  };

  struct IEntityComponent {
    virtual ~IEntityComponent() = 0;
  };
}
