#pragma once

#include "vector.hpp"

namespace engine::geometry {

  /// @brief Plane models an infinite plane in 3D space.
  ///
  /// @see https://www.wikiwand.com/en/Plane_(geometry)
  struct Plane {
    Point<3> point;       //< A point on the plane.
    UnitVector<3> normal; //< The normal vector of the plane.
  };

}
