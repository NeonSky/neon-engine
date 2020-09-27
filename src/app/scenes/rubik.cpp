#include "rubik.hpp"

#include "../rubiks_cube.hpp"

#include "../../engine/debug/debug_drawer.hpp"
#include "../../engine/debug/logger.hpp"
#include "../../engine/geometry/line_segment.hpp"
#include "../../engine/graphics/component/cuboid.hpp"
#include "../../engine/graphics/component/line_segment.hpp"

using namespace app::scenes;
using namespace engine;

Rubik::Rubik(engine::scene::SceneAPI& api,
             engine::scene::Node& root)
        : _api(api),
          _root(root),
          _lines(_root.add_child()),
          _cuboid1(_root.add_child()),
          _cuboid2(_root.add_child()),
          _cuboid3(_root.add_child()),
          _rubiks_cube(_root.add_child()) {

  _camera     = std::make_unique<debug::DebugCamera>(_api.input_manager(), geometry::Rigidbody(geometry::Vector<3>(1.0F, 5.0F, -20.0F)));
  _api.camera = (graphics::Camera*) _camera.get();

  std::vector<graphics::component::LineSegment> line_segments;

  // Draw grid
  for (int x = -10; x <= 10; x++)
    line_segments.push_back({

      .geometry = geometry::LineSegment(geometry::Point<3>((float) x, 0, 10),
                                        geometry::Point<3>((float) x, 0, -10)),
      .width    = 2.0F,
    });

  for (int z = -10; z <= 10; z++)
    line_segments.push_back({
      .geometry = geometry::LineSegment(geometry::Point<3>(10, 0, (float) z),
                                        geometry::Point<3>(-10, 0, (float) z)),
      .width    = 2.0F,
    });

  // Draw coordinate axis
  line_segments.push_back({
    .geometry = geometry::LineSegment(geometry::Point<3>(),
                                      geometry::Point<3>(10, 0, 0)),
    .color    = graphics::Color(1.0F, 0.0F, 0.0F),
    .width    = 5.0F,
  });

  line_segments.push_back({
    .geometry = geometry::LineSegment(geometry::Point<3>(),
                                      geometry::Point<3>(0, 10, 0)),
    .color    = graphics::Color(0.0F, 1.0F, 0.0F),
    .width    = 5.0F,
  });
  line_segments.push_back({
    .geometry = geometry::LineSegment(geometry::Point<3>(),
                                      geometry::Point<3>(0, 0, 10)),
    .color    = graphics::Color(0.0F, 0.0F, 1.0F),
    .width    = 5.0F,
  });

  _lines.add_component<graphics::component::LineSegments>(line_segments);

  _cuboid1.add_component<geometry::Transform>(geometry::Vector<3>(0.5F, 0.5F, 0.5F),
                                              geometry::Orientation(),
                                              geometry::Vector<3>(1.0F, 1.0F, 1.0F));
  _cuboid1.add_component<graphics::component::Cuboid>(geometry::Transform(),
                                                      graphics::Color(0.6F, 1.0F, 1.0F));

  _cuboid2.add_component<geometry::Transform>(geometry::Vector<3>(3.5F, 1.0F, 3.5F),
                                              geometry::Orientation(),
                                              geometry::Vector<3>(1.0F, 2.0F, 1.0F));
  _cuboid2.add_component<graphics::component::Cuboid>(geometry::Transform(),
                                                      graphics::Color(0.6F, 1.0F, 0.6F));

  _cuboid3.add_component<geometry::Transform>(geometry::Vector<3>(6.0F, 0.25F, 1.5F),
                                              geometry::Orientation(),
                                              geometry::Vector<3>(2.0F, 0.5F, 1.0F));
  _cuboid3.add_component<graphics::component::Cuboid>(geometry::Transform(),
                                                      graphics::Color(1.0F, 0.6F, 0.6F));

  _rubiks_cube.add_component<geometry::Transform>(geometry::Vector<3>(-4.5F, 2, 4.5F));
  _rubiks_cube.add_component<RubiksCube>(_rubiks_cube);

  const auto& input = _api.input_manager();
  input.on_key([&]([[maybe_unused]] const os::Window& window,
                   engine::os::KeyCode keycode,
                   engine::os::KeyAction action,
                   const engine::os::ActivatedModifiers& mods) {
    if (action == os::KeyAction::PRESS) {
      auto& cube = _rubiks_cube.component<RubiksCube>();

      if (keycode == GLFW_KEY_KP_4)
        cube.rotate_left(mods.shift);
      if (keycode == GLFW_KEY_KP_6)
        cube.rotate_right(mods.shift);
      if (keycode == GLFW_KEY_KP_2)
        cube.rotate_bot(mods.shift);
      if (keycode == GLFW_KEY_KP_8)
        cube.rotate_top(mods.shift);
      if (keycode == GLFW_KEY_KP_5)
        cube.rotate_back(mods.shift);
      if (keycode == GLFW_KEY_KP_0)
        cube.rotate_front(mods.shift);
    }
  });
}

void Rubik::update(float delta_time) {
  static float time = 0.0F;
  time += delta_time;

  _rubiks_cube.component<geometry::Transform>().orientation() = geometry::Rotation(0, time, 0);

  _cuboid1.component<geometry::Transform>().orientation() = geometry::Rotation(0, 0, time);
  _cuboid2.component<geometry::Transform>().orientation() = geometry::Rotation(0, time, 0);
  _cuboid3.component<geometry::Transform>().orientation() = geometry::Rotation(time, 0, 0);
}
