#pragma once

#include "../../architecture/ecs.hpp"
#include "../component/line_segment.hpp"
#include "../shader.hpp"

#include "../../geometry/matrix.hpp"

#include <algorithm>
#include <vector>

namespace engine::graphics::system {

  class LineRenderer : public architecture::IEntitySystem {
  public:
    LineRenderer();

    // Mutators
    void render(const geometry::Matrix<4>& view_projection);
    void add_line(component::LineSegment&& line);
    void clear();

    void update(architecture::ECS& ecs) override;

  private:
    graphics::Shader _shader;
    std::vector<component::LineSegment> _line_queue;

    float _min_line_width;
    float _max_line_width;
  };

}
