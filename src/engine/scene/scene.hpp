#pragma once

#include "api.hpp"

namespace engine::scene {

  /// @todo Consider only exposing update() to the user.
  class IScene : public graphics::IRenderable {
  public:
    IScene(SceneAPI& api);

    virtual void update(float delta_time) = 0;
    virtual void render()                 = 0;
    virtual void gui()                    = 0;

  protected:
    SceneAPI& _api;
  };

}
