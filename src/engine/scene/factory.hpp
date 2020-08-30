#pragma once

#include "scene.hpp"

#include <memory>
#include <vector>

namespace engine::scene {

  struct IFactory {
    virtual auto create(SceneAPI& api) -> std::unique_ptr<IScene> = 0;
  };

  template <typename T>
  struct Factory : IFactory {
    virtual auto create(SceneAPI& api) -> std::unique_ptr<IScene> override {
      return std::make_unique<T>(api);
    }
  };

}
