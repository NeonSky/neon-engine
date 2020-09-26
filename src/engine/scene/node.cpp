#include "node.hpp"

#include "component/node.hpp"

using namespace engine::scene;

Node::Node(architecture::ECS& ecs, architecture::EntityID id)
        : _ecs(ecs),
          _id(id) {}

auto Node::add_child() -> Node& {
  // ECS side
  auto ecs_child = _ecs.get().create();
  _ecs.get().emplace<component::Node>(ecs_child, _id);
  _ecs.get().get<component::Node>(_id).children.insert(ecs_child);

  // OOP side
  _children.push_back(std::make_unique<Node>(_ecs.get(), ecs_child));
  return *_children.back();
}
