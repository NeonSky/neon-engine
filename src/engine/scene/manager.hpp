#pragma once

#include "../graphics/renderer.hpp"
#include "api.hpp"
#include "factory.hpp"
#include "scene.hpp"

#include <memory>
#include <set>
#include <vector>

namespace engine::scene {

  /// @brief Manager stores, enables/disables, updates, and renders scenes.
  ///
  /// @todo Add support to send objects between scenes e.g. camera. Or maybe cameras should not belong to scenes? Still, moving other objects between scenes would be neat.
  /// @todo Give the user their own logger.
  class Manager {
  public:
    Manager(const os::InputManager& input_manager, graphics::Renderer& renderer, std::vector<std::unique_ptr<IFactory>> scene_factories);

    /// @brief Updates the physics and game logic of all active scenes.
    void update(float delta_time);

    /// @brief Renders the models of all active scenes.
    void render();

    /// @brief Renders the GUI of all active scenes.
    void gui();

  private:
    /// @{
    /// Private state.
    SceneAPI _api;
    graphics::Renderer& _renderer;
    std::vector<std::unique_ptr<IScene>> _scenes;
    std::set<unsigned int> _active_scenes;
    /// @}
  };

}
