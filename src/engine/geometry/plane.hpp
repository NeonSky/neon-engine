#pragma once

#include "rectangle.hpp"

namespace engine::geometry {

  struct Plane {
    Vector<3> point_on_plane;
    Vector<3> normal;

    Plane()
            : normal(Vector<3>(0.0F, 1.0F, 0.0F)) {}

    Plane(const Rectangle& rectangle)
            : point_on_plane(rectangle.botleft()),
              normal(rectangle.rigidbody().forward()) {}
  };

}
