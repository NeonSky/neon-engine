#pragma once

#include "scene/factory.hpp"
#include "scene/manager.hpp"
#include "time/update_scheduler.hpp"

#include <memory>
#include <vector>

namespace engine {

  /// @todo Add to config: log_level, windows
  class NeonEngine {
  public:
    struct Config {
      float ups        = 100.0F;
      float render_fps = 60.0F;
      float gui_fps    = 30.0F;
    };

    NeonEngine(Config config);

    /// At first, only the scene at index 0 will be enabled.
    // void set_scenes(std::vector<std::unique_ptr<scene::IScene>> scenes);
    void set_scenes(std::vector<std::unique_ptr<scene::IFactory>> scenes);

    void start();
    void stop();

    [[nodiscard]] auto is_running() const -> bool;

  private:
    Config _config;
    bool _is_running = false;

    std::unique_ptr<os::WindowManager> _wm;
    std::unique_ptr<graphics::Renderer> _renderer;
    std::unique_ptr<scene::Manager> _scene_manager;
    std::unique_ptr<time::UpdateScheduler> _game_loop;
  };

}
