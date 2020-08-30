#include "manager.hpp"

using namespace engine::scene;

Manager::Manager(const os::InputManager& input_manager, graphics::Renderer& renderer, std::vector<std::unique_ptr<IFactory>> scenes)
        : _api(input_manager, renderer),
          _renderer(renderer) {

  for (auto& scene : scenes)
    _scenes.push_back(scene->create(_api));

  _active_scenes.insert(0);
}

void Manager::update(float delta_time) {
  for (auto& scene_index : _active_scenes)
    _scenes[scene_index]->update(delta_time);
}

void Manager::render() {
  for (unsigned int i = 0; i < _renderer.context_count(); i++)
    for (auto& scene_index : _active_scenes)
      _renderer.render(*_scenes[scene_index], i);
}

void Manager::gui() {
  for (auto& scene_index : _active_scenes)
    _scenes[scene_index]->gui();
}
