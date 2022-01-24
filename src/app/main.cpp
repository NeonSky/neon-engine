// #include "../engine/debug/logger.hpp"
// #include "../engine/graphics/api/vulkan/application.hpp"

// using namespace engine::graphics::api::vulkan;

// int main() {
//   engine::debug::Logger::set_profile(engine::debug::Logger::Profile::DEBUG);

//   Application app;

//   try {
//     app.run();
//   } catch (const std::exception& e) {
//     std::cerr << e.what() << std::endl;
//     return EXIT_FAILURE;
//   }

//   return EXIT_SUCCESS;
// }

//
//
//
//
//

#include "../engine/engine.hpp"

#include "scenes/rubik.hpp"

using namespace engine;
using namespace app;

#include <thread>

void run_engine() {
  // Configure and create an engine instance.
  NeonEngine::Config config;
  NeonEngine engine_instance(config);

  // Add game scenes.
  std::vector<std::unique_ptr<scene::IFactory>> scenes;
  scenes.push_back(std::make_unique<scene::Factory<scenes::Rubik>>());
  engine_instance.set_scenes(std::move(scenes));

  // Start engine.
  engine_instance.start();
}

auto main() -> int {
  LOG_INFO("App started.");
  std::thread engine_thread(&run_engine);

  // Do whatever.
  LOG_INFO("App idle...");
  engine_thread.join();

  // Stop engine.
  // engine_instance.stop();
  LOG_INFO("App terminated.");
}
