#include "api.hpp"

using namespace engine;
using namespace engine::scene;

SceneAPI::SceneAPI(const os::InputManager& input_manager)
        : _input_manager(std::ref(input_manager)) {}

auto SceneAPI::input_manager() const -> const os::InputManager& {
  return _input_manager;
}
