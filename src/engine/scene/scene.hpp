#pragma once

#include "api.hpp"

namespace engine::scene {

  /// @todo Consider only exposing update() to the user.
  // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
  class IScene : public graphics::IRenderable {
  public:
    IScene(SceneAPI& api);
    virtual ~IScene() = 0;

    virtual void update(float delta_time) = 0;
    virtual void gui()                    = 0;

  protected:
    SceneAPI& _api;
  };

}
