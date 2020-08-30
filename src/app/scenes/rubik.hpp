#pragma once

#include "../../engine/debug/debug_camera.hpp"
#include "../../engine/debug/debug_drawer.hpp"
#include "../../engine/graphics/gltf_model.hpp"
#include "../../engine/scene/scene.hpp"
#include "../rubiks_cube.hpp"

namespace app::scenes {

  class Rubik : public engine::scene::IScene {
  public:
    Rubik(engine::scene::SceneAPI& api);

    virtual void update(float delta_time) override;
    virtual void render() override;
    virtual void gui() override;

  private:
    std::unique_ptr<engine::debug::DebugCamera> _camera;
    std::unique_ptr<RubiksCube> _rubiks_cube;
    std::unique_ptr<engine::graphics::GLTFModel> _gltf_stone;
    std::unique_ptr<engine::graphics::Cuboid> _cuboid1;
    std::unique_ptr<engine::graphics::Cuboid> _cuboid2;
    std::unique_ptr<engine::graphics::Cuboid> _cuboid3;
    std::unique_ptr<engine::graphics::Rectangle> _test;

    engine::debug::DebugDrawer _dd;
    float _time = 0.0F;
  };

}
