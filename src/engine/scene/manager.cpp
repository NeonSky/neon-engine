#include "manager.hpp"

using namespace engine::scene;

Manager::Manager(const os::InputManager& input_manager,
                 graphics::Renderer& renderer,
                 std::vector<std::unique_ptr<IFactory>> scene_factories)
        : _api(input_manager, renderer),
          _renderer(renderer) {

  for (auto& scene_factory : scene_factories)
    _scenes.push_back(scene_factory->create(_api));

  _active_scenes.insert(0);
}

void Manager::update(float delta_time) {
  for (const auto& scene_index : _active_scenes)
    _scenes[scene_index]->update(delta_time);
}

void Manager::render() {
  for (unsigned int i = 0; i < _renderer.context_count(); i++)
    for (const auto& scene_index : _active_scenes)
      _renderer.render(*_scenes[scene_index], i);
}

void Manager::gui() {
  for (const auto& scene_index : _active_scenes)
    _scenes[scene_index]->gui();
}
