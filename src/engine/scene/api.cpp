#include "api.hpp"

using namespace engine;
using namespace engine::scene;

SceneAPI::SceneAPI(const os::InputManager& input_manager, graphics::Renderer& renderer)
        : _input_manager(std::ref(input_manager)),
          _renderer(std::ref(renderer)) {}

auto SceneAPI::input_manager() const -> const os::InputManager& {
  return _input_manager;
}

auto SceneAPI::renderer() -> graphics::Renderer& {
  return _renderer;
}
