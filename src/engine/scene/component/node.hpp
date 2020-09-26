#pragma once

#include "../../architecture/ecs.hpp"

#include <set>

namespace engine::scene::component {

  /// @brief Node represents a node in a scene hierarchy.
  struct Node {
    architecture::EntityID parent = architecture::NullEntityID;
    std::set<architecture::EntityID> children;
  };

}
