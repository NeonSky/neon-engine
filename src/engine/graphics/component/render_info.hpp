#pragma once

#include "../../geometry/matrix.hpp"
#include "../opengl/context.hpp"

namespace engine::graphics::component {

  struct RenderInfo {
    geometry::Matrix<4> view_projection;
    std::reference_wrapper<opengl::Context> context; // TODO: Make const?
  };

}
