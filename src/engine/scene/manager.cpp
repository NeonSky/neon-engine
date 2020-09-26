#include "manager.hpp"

#include "node.hpp"

#include "component/root.hpp"

using namespace engine::scene;

Manager::Manager(const os::InputManager& input_manager,
                 graphics::Renderer& renderer,
                 std::vector<std::unique_ptr<IFactory>> scene_factories)
        : _api(input_manager, renderer),
          _renderer(renderer) {

  for (auto& scene_factory : scene_factories)
    _scenes.emplace_back(_api, *scene_factory);
}

void Manager::update(float delta_time) {
  for (auto& scene : _scenes)
    scene.update(delta_time);
}

void Manager::render() {
  for (auto& scene : _scenes) {
    if (_api.camera != nullptr) {
      _renderer.render(scene.ecs(), 0, _api.camera->view_projection());
      _renderer.render(scene.ecs(), 1, _api.camera->view_projection());
    }
  }
}

void Manager::gui() {
}
