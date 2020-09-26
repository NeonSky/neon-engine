#pragma once

#include "../../engine/scene/script.hpp"

#include "../../engine/debug/debug_camera.hpp"

namespace app::scenes {

  class Rubik : public engine::scene::IScript {
  public:
    Rubik(engine::scene::SceneAPI& api, engine::scene::Node& root);

    void update(float delta_time) override;

  private:
    engine::scene::SceneAPI& _api;
    engine::scene::Node& _root;

    engine::scene::Node& _lines;
    engine::scene::Node& _cuboid1;
    engine::scene::Node& _cuboid2;
    engine::scene::Node& _cuboid3;
    engine::scene::Node& _rubiks_cube;

    std::unique_ptr<engine::debug::DebugCamera> _camera;
  };

}
