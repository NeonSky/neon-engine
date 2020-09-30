#pragma once

#include "../../geometry/matrix.hpp"
#include "../api/context.hpp"

namespace engine::graphics::component {

  /// @todo Make context const?
  struct RenderInfo {
    geometry::Matrix<4> view_projection;
    std::reference_wrapper<api::IContext> context;
  };

}
