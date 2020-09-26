#pragma once

#include "../../geometry/line_segment.hpp"
#include "../color.hpp"

namespace engine::graphics::component {

  struct LineSegment {
    geometry::LineSegment<3> geometry;
    Color color = Color(1.0F, 1.0F, 1.0F);
    float width = 1.0F;
  };

  struct LineSegments {
    std::vector<LineSegment> line_segments;
  };

}
