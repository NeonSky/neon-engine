#pragma once

#include "../architecture/ecs.hpp"
#include "../debug/logger.hpp"

#include <vector>

namespace engine::scene {

  /// @brief Node acts is if we use a normal scene graph to the user.
  ///
  /// This is the class that the user interacts with.
  /// @todo Maybe create an interface to hide includes and constructor from the user.
  /// @todo Don't allow access to parent node when node is root.
  class Node {
  public:
    Node(architecture::ECS& ecs, architecture::EntityID id);

    auto add_child() -> Node&;

    template <typename T, typename... Args>
    void add_component(Args&&... args) {
      _ecs.get().emplace<T>(_id, std::forward<Args>(args)...);
    }

    template <typename T>
    auto component() -> T& {
      return _ecs.get().get<T>(_id);
    }

  private:
    std::reference_wrapper<architecture::ECS> _ecs; // FIXME: Replace with an interface that provides basic node operations, not a mutable reference to whole ECS world.
    architecture::EntityID _id;                     // the entity that this OOP object wraps
    std::vector<std::unique_ptr<Node>> _children;   // NOTE: Careful, this is duplicated data since component::Node already stores the hierarchy of the nodes. However, Node objects need to be managed and stored in static memory somehow so this is a good enough trade-off to bridge the engine's ECS and the user's OOP world.
  };

}
