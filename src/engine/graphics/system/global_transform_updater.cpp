#include "global_transform_updater.hpp"

#include "../component/global_transform.hpp"

#include "../../scene/component/node.hpp"
#include "../../scene/component/root.hpp"

#include <stack>

using namespace engine;
using namespace engine::graphics::system;

void GlobalTransformUpdater::update(architecture::ECS& ecs) {
  architecture::EntityID root = ecs.view<scene::component::Root>()[0];

  // Ensure all entities with Transform also have GlobalTransform.
  for (auto e : ecs.view<geometry::Transform>(entt::exclude<component::GlobalTransform>))
    ecs.emplace<component::GlobalTransform>(e);

  // Keep track of when to pop matrices.
  std::stack<architecture::EntityID> next_tree_at;
  next_tree_at.push(architecture::NullEntityID);

  // DFS of scene hierarchy matrices.
  std::stack<geometry::Matrix<4>> matrices;
  matrices.push(geometry::Matrix<4>());

  // DFS.
  std::stack<architecture::EntityID> dfs;
  dfs.push(architecture::NullEntityID);
  dfs.push(root);

  while (!dfs.empty()) {
    auto cur = dfs.top();
    dfs.pop();

    if (cur == architecture::NullEntityID)
      break;

    if (cur == next_tree_at.top()) {
      matrices.pop();
      next_tree_at.pop();
    }

    if (auto* c = ecs.try_get<geometry::Transform>(cur); c != nullptr) {
      matrices.push(matrices.top() * c->matrix());
      next_tree_at.push(dfs.top());

      ecs.get<component::GlobalTransform>(cur).matrix = matrices.top();
    }

    for (auto c : ecs.get<scene::component::Node>(cur).children)
      dfs.push(c);
  }
}
