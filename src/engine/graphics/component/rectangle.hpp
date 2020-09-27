#pragma once

#include "../../geometry/rectangle.hpp"
#include "../color.hpp"

namespace engine::graphics::component {

  struct Rectangle {
    geometry::Rectangle geometry;
    Color color      = Color(1.0F, 1.0F, 1.0F);
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ibo = 0;
  };

}
