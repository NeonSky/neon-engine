#include "engine.hpp"

#include "debug/logger.hpp"

#include <chrono>
#include <thread>

using namespace engine;

NeonEngine::NeonEngine(Config config)
        : _config(config) {

  srand(std::time(nullptr));
  debug::Logger::set_profile(debug::Logger::Profile::DEBUG);

  _wm = std::make_unique<os::WindowManager>();
  _wm->on_all_windows_closed([this] {
    LOG_INFO("Stopping engine because all windows have been closed.");
    _is_running = false;
  });

  _renderer = std::make_unique<graphics::Renderer>(*_wm);
}

void NeonEngine::set_scenes(std::vector<std::unique_ptr<scene::IFactory>> scenes) {
  _scene_manager = std::make_unique<scene::Manager>(_wm->input_manager(), *_renderer, std::move(scenes));

  std::vector<time::UpdateScheduler::Schedule> schedules;
  schedules.push_back({std::bind(&scene::Manager::update, _scene_manager.get(), std::placeholders::_1), std::chrono::nanoseconds((int) (1000000000.0F / _config.ups)), true});
  schedules.push_back({std::bind(&scene::Manager::render, _scene_manager.get()), std::chrono::nanoseconds((int) (1000000000.0F / _config.render_fps)), false});
  schedules.push_back({std::bind(&scene::Manager::gui, _scene_manager.get()), std::chrono::nanoseconds((int) (1000000000.0F / _config.gui_fps)), false});

  _game_loop = std::make_unique<time::UpdateScheduler>(std::move(schedules));
}

void NeonEngine::start() {
  _is_running = true;
  LOG_INFO("Engine started.");

  // Lock thread to ensure thread-safe game loop.
  static std::mutex mux;
  const std::lock_guard<std::mutex> lock(mux);

  _game_loop->run(_is_running);

  LOG_INFO("Engine stopped.");
}

void NeonEngine::stop() {
  LOG_INFO("Stopping engine...");
  _is_running = false;
}

auto NeonEngine::is_running() const -> bool {
  return _is_running;
}
