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
  std::stack<unsigned int> subtree_done_at;
  subtree_done_at.push(0);

  // DFS of scene hierarchy matrices.
  std::stack<geometry::Matrix<4>> matrices;
  matrices.push(geometry::Matrix<4>());

  // DFS.
  std::stack<architecture::EntityID> dfs;
  dfs.push(architecture::NullEntityID);
  dfs.push(root);

  while (dfs.top() != architecture::NullEntityID) {
    auto cur = dfs.top();
    dfs.pop();

    // while loop because sometimes we finish multiple subtrees at once.
    while (dfs.size() == subtree_done_at.top()) {
      matrices.pop();
      subtree_done_at.pop();
    }

    if (auto* c = ecs.try_get<geometry::Transform>(cur); c != nullptr) {
      matrices.push(matrices.top() * c->matrix());
      subtree_done_at.push(dfs.size() - 1); // Tree will be one less because we pop the next sibling from dfs.

      ecs.get<component::GlobalTransform>(cur).matrix = matrices.top();
    }

    for (auto c : ecs.get<scene::component::Node>(cur).children)
      dfs.push(c);
  }
}
