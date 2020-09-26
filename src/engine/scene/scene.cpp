#include "scene.hpp"

#include "component/node.hpp"
#include "component/root.hpp"

using namespace engine::scene;

Scene::Scene(SceneAPI& api, IFactory& script_factory) {
  architecture::EntityID root_id = _ecs.create();
  _ecs.emplace<component::Root>(root_id);
  _ecs.emplace<component::Node>(root_id);

  _root   = std::make_unique<Node>(_ecs, root_id);
  _script = script_factory.create(api, *_root);
}

void Scene::update(float delta_time) {
  _script->update(delta_time);
}

auto Scene::ecs() -> architecture::ECS& {
  return _ecs;
}
