#pragma once

#include "vector.hpp"

namespace engine::geometry {

  /// @brief Orientation defines the reference orientation of the world.
  ///
  /// @see https://www.wikiwand.com/en/Orientation_(geometry)
  struct Orientation {

    /// @brief The reference right direction of the world.
    static const Vector<4> world_right;

    /// @brief The reference up direction of the world.
    static const Vector<4> world_up;

    /// @brief The reference forward direction of the world.
    static const Vector<4> world_forward;
  };
}
