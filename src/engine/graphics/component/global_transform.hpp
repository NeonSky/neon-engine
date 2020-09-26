#pragma once

#include "../../geometry/transform.hpp"

namespace engine::graphics::component {

  /// @todo replace matrix with transform?
  struct GlobalTransform {
    geometry::Matrix<4> matrix;
  };

}
