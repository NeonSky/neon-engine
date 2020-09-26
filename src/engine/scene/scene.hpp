#pragma once

#include "api.hpp"
#include "factory.hpp"
#include "node.hpp"
#include "script.hpp"

#include "../architecture/ecs.hpp"

namespace engine::scene {

  /// Scenes are completely separate from one another but objects may be moved between scenes.
  class Scene {
  public:
    Scene(SceneAPI& api, IFactory& script_factory);

    void update(float delta_time);

    auto ecs() -> architecture::ECS&;

  private:
    architecture::ECS _ecs;
    std::unique_ptr<Node> _root;
    std::unique_ptr<IScript> _script;
    bool _enabled = true;
  };

}
