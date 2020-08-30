#pragma once

#include "../graphics/renderer.hpp"
#include "../os/input_manager.hpp"

namespace engine::scene {

  /// The API exposed to the scenes.
  ///
  /// @todo Consider making an interface.
  /// @todo Consider moving to another directory and changing the name.
  class SceneAPI {
  public:
    SceneAPI(const os::InputManager& input_manager, graphics::Renderer& renderer);

    [[nodiscard]] auto input_manager() const -> const os::InputManager&;
    [[nodiscard]] auto renderer() -> graphics::Renderer&;

  private:
    std::reference_wrapper<const os::InputManager> _input_manager;
    std::reference_wrapper<graphics::Renderer> _renderer;
  };

}
