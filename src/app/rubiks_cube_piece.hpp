#pragma once

#include "../engine/graphics/color.hpp"
#include "../engine/graphics/cuboid.hpp"
#include "../engine/graphics/rectangle.hpp"
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

    auto transform() -> engine::geometry::Transform&;

  private:
    engine::geometry::Transform _transform;
  };

}
