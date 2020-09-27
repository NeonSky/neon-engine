#pragma once

#include "../architecture/interface.hpp"

#include "api.hpp"
#include "node.hpp"

namespace engine::scene {

  struct IScript : public architecture::Interface {
    IScript();
    IScript(SceneAPI& api, Node& root);

    virtual void update(float delta_time) = 0;
  };

}
