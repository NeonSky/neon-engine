// #include "../engine/debug/logger.hpp"
// #include "../engine/gui/window.hpp"

// #include <GLFW/glfw3.h>
// #include <glad/glad.h>
// #include <imgui.h>
// #include <imgui_impl_glfw.h>
// #include <imgui_impl_opengl3.h>

// #include <chrono>
// #include <cstdlib>
// #include <ctime>
// #include <string>

// #include <tiny_gltf.h>
// #include <entt/entt.hpp>
// // #include <entt/entity/registry.hpp>

// struct position {
//   float x;
//   float y;
// };

// struct velocity {
//   float dx;
//   float dy;
// };

// void update(entt::registry &registry) {
//   auto view = registry.view<position, velocity>();

//   for(auto entity: view) {
//     // gets only the components that are going to be used ...

//     auto &vel = view.get<velocity>(entity);

//     vel.dx = 0.;
//     vel.dy = 0.;

//     // ...
//   }
// }

// void update(std::uint64_t dt, entt::registry &registry) {
//   registry.view<position, velocity>().each([dt](auto &pos, auto &vel) {
//                                              // gets all the components of the view at once ...

//                                              pos.x += vel.dx * dt;
//                                              pos.y += vel.dy * dt;

//                                              // ...
//                                            });
// }

// int main() {
//   srand(time(NULL));

//   engine::debug::Logger::set_profile(engine::debug::Logger::Profile::DEBUG);
//   LOG_INFO("Program started.");
//   auto start = std::chrono::system_clock::now();

//   engine::gui::Window *window;
//   try {
//     window = new engine::gui::Window(1920, 1080, "Application");
//   } catch(const std::exception& e) {
//     LOG_ERROR(e.what());
//     return -1;
//   }

//   int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
//   if (!status) {
//     LOG_ERROR("Failed to init GLAD");
//     glfwTerminate();
//     return -1;
//   }

//   LOG_INFO("OpenGL version: " + std::string((const char*)glGetString(GL_VERSION)));
//   LOG_INFO("OpenGL renderer: " + std::string((const char*)glGetString(GL_RENDERER)));
//   LOG_INFO("OpenGL vendor: " + std::string((const char*)glGetString(GL_VENDOR)));

//   CHECK_GL_ERROR();

//   glEnable(GL_DEPTH_TEST);
//   glEnable(GL_CULL_FACE);

//   glEnable(GL_BLEND);
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//   window->init_gui();

//   CHECK_GL_ERROR();

//   entt::registry registry;
//   std::uint64_t dt = 16;

//   for(auto i = 0; i < 10; ++i) {
//     auto entity = registry.create();
//     registry.emplace<position>(entity, i * 1.f, i * 1.f);
//     if(i % 2 == 0) { registry.emplace<velocity>(entity, i * .1f, i * .1f); }
//   }

//   while (!window->is_closing()) {

//     update(dt, registry);
//     update(registry);

//     window->clear_screen();
//     glUseProgram(0);
//     window->update();

//     CHECK_GL_ERROR();
//   }

//   auto end = std::chrono::system_clock::now();
//   LOG_INFO("Program terminated.");

//   std::chrono::duration<double> elapsed_seconds = end - start;
//   LOG_INFO("Uptime: " + std::to_string(elapsed_seconds.count()) + " seconds.");
// }

