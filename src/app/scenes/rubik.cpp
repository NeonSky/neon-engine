#include "rubik.hpp"

#include "../../engine/debug/logger.hpp"

using namespace app::scenes;
using namespace engine;

Rubik::Rubik(scene::SceneAPI& api) : IScene(api) {

  _camera = std::make_unique<debug::DebugCamera>(_api.input_manager(), geometry::Rigidbody(geometry::Vector<3>(1.0F, 5.0F, -20.0F)));

  _rubiks_cube = std::make_unique<RubiksCube>(_api.renderer(), geometry::Transform(geometry::Vector<3>(-4.5F, 2, 4.5F)));
  _gltf_stone  = std::make_unique<graphics::GLTFModel>(_api.renderer(), "cube/Cube.gltf", geometry::Transform(geometry::Vector<3>(-1.0F, 1.0F, -1.0F)));

  _cuboid1 = std::make_unique<graphics::Cuboid>(_api.renderer(), geometry::Transform(geometry::Vector<3>(0.5F, 0.5F, 0.5F), geometry::Orientation(), geometry::Vector<3>(1.0F, 1.0F, 1.0F)), graphics::Color(0.6F, 1.0F, 1.0F));
  _cuboid2 = std::make_unique<graphics::Cuboid>(_api.renderer(), geometry::Transform(geometry::Vector<3>(3.5F, 1.0F, 3.5F), geometry::Orientation(), geometry::Vector<3>(1.0F, 2.0F, 1.0F)), graphics::Color(0.6F, 1.0F, 0.6F));
  _cuboid3 = std::make_unique<graphics::Cuboid>(_api.renderer(), geometry::Transform(geometry::Vector<3>(6.0F, 0.25F, 1.5F), geometry::Orientation(), geometry::Vector<3>(2.0F, 0.5F, 1.0F)), graphics::Color(1.0F, 0.6F, 0.6F));

  auto& input = _api.input_manager();
  input.on_key([&]([[maybe_unused]] const os::Window& window,
                   engine::os::KeyCode keycode,
                   engine::os::KeyAction action,
                   const engine::os::ActivatedModifiers& mods) {
    if (action == os::KeyAction::PRESS) {

      if (keycode == GLFW_KEY_KP_4)
        _rubiks_cube->rotate_left(mods.shift);
      if (keycode == GLFW_KEY_KP_6)
        _rubiks_cube->rotate_right(mods.shift);
      if (keycode == GLFW_KEY_KP_2)
        _rubiks_cube->rotate_bot(mods.shift);
      if (keycode == GLFW_KEY_KP_8)
        _rubiks_cube->rotate_top(mods.shift);
      if (keycode == GLFW_KEY_KP_5)
        _rubiks_cube->rotate_back(mods.shift);
      if (keycode == GLFW_KEY_KP_0)
        _rubiks_cube->rotate_front(mods.shift);
    }
  });
}

void Rubik::update(float delta_time) {
  _time += delta_time;

  _rubiks_cube->transform().orientation() = geometry::Rotation(0, _time, 0);

  _cuboid1->transform().orientation() = geometry::Rotation(0, 0, _time);
  _cuboid2->transform().orientation() = geometry::Rotation(0, _time, 0);
  _cuboid3->transform().orientation() = geometry::Rotation(_time, 0, 0);
}

void Rubik::render() {
  geometry::Matrix<4> view_projection = _camera->projection_matrix() * _camera->view_matrix();

  _dd.set_line_width(2.0F);
  for (int x = -10; x <= 10; x++)
    _dd.draw_line(geometry::Vector<3>((float) x, 0, 10), geometry::Vector<3>((float) x, 0, -10));
  for (int z = -10; z <= 10; z++)
    _dd.draw_line(geometry::Vector<3>(10, 0, (float) z), geometry::Vector<3>(-10, 0, (float) z));
  _dd.render(view_projection);

  _dd.set_line_width(5.0F);
  _dd.draw_transform(geometry::Transform(geometry::Vector<3>(), geometry::Orientation(), geometry::Vector<3>(10.0F, 10.0F, 10.0F)));
  _dd.render(view_projection);

  _rubiks_cube->render(view_projection);
  _gltf_stone->render(view_projection);

  _cuboid1->render(view_projection, true);
  _cuboid2->render(view_projection, true);
  _cuboid3->render(view_projection, true);
}

void Rubik::gui() {
}
