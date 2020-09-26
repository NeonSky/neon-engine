#pragma once

#include "api.hpp"
#include "node.hpp"
#include "script.hpp"

#include <memory>
#include <vector>

namespace engine::scene {

  /// @todo rename to script factory.
  // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
  struct IFactory {
    virtual ~IFactory() = default;

    virtual auto create(SceneAPI& api, Node& node) -> std::unique_ptr<IScript> = 0;
  };

  template <typename T>
  struct Factory : IFactory {
    auto create(SceneAPI& api, Node& node) -> std::unique_ptr<IScript> override {
      return std::make_unique<T>(api, node);
    }
  };

}
