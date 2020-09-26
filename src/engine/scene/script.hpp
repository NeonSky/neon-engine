#pragma once

#include "api.hpp"
#include "node.hpp"

namespace engine::scene {

  // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
  struct IScript {
    IScript();
    IScript(SceneAPI& api, Node& root);
    virtual ~IScript() = 0;

    virtual void update(float delta_time) = 0;
  };

}
