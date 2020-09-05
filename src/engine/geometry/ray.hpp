#pragma once

#include "vector.hpp"

namespace engine::geometry {

  /// @brief Ray represents a vector originating from a point.
  ///
  /// It can also be seen as half of a line.
  ///
  /// @see https://www.wikiwand.com/en/Line_(geometry)
  struct Ray {
    /// @{
    /// State.
    Point<3> origin;         //< The origin/tail of this ray.
    UnitVector<3> direction; //< The direction of this ray.
    /// @}

    /// @brief Serializes the current state to JSON.
    [[nodiscard]] auto to_json() const -> debug::JSON {
      return {
        {"origin", origin.to_json()},
        {"direction", direction.to_json()}};
    };
  };

}
