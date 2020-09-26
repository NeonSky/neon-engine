#pragma once

#include "api.hpp"
#include "component/node.hpp"
#include "factory.hpp"
#include "scene.hpp"

#include "../architecture/ecs.hpp"
#include "../graphics/renderer.hpp"

#include <memory>
#include <set>
#include <vector>

namespace engine::scene {

  /// @brief Manager stores, enables/disables, updates, and renders scenes.
  ///
  /// @todo Give the user their own logger.
  /// @todo Don't load all scenes at start. Have config and let user decide when they load/unload.
  class Manager {
  public:
    Manager(const os::InputManager& input_manager,
            graphics::Renderer& renderer,
            std::vector<std::unique_ptr<IFactory>> scene_factories);

    /// @brief Updates the physics and game logic of all active scenes.
    void update(float delta_time);

    /// @brief Renders the models of all active scenes.
    void render();

    /// @brief Renders the GUI of all active scenes.
    void gui();

  private:
    /// @{
    /// Private state.
    std::vector<Scene> _scenes;
    SceneAPI _api;
    graphics::Renderer& _renderer;
    /// @}
  };

}
