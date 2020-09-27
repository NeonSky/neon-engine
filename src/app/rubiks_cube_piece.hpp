#pragma once

#include "../engine/geometry/transform.hpp"
#include "../engine/graphics/color.hpp"
#include "../engine/scene/node.hpp"

#include <vector>

namespace app {

  class RubiksCubePiece {
  public:
    struct ColorConfiguration {
      engine::graphics::Color left;
      engine::graphics::Color right;
      engine::graphics::Color bot;
      engine::graphics::Color top;
      engine::graphics::Color back;
      engine::graphics::Color front;
    };

    RubiksCubePiece(engine::scene::Node& node, engine::geometry::Transform transform, ColorConfiguration color_config);
  };

}
