#include "../engine/debug/debug_camera.hpp"
#include "../engine/debug/debug_drawer.hpp"
#include "../engine/debug/logger.hpp"
#include "../engine/geometry/matrix.hpp"
#include "../engine/geometry/ray.hpp"
#include "../engine/graphics/cuboid.hpp"
#include "../engine/graphics/gltf_model.hpp"
#include "../engine/gui/window.hpp"

#include "rubiks_cube.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>

// #include <entt/entt.hpp>
#include <entt/entity/registry.hpp>

using namespace engine;
using namespace app;

struct position {
  float x;
  float y;
};

struct velocity {
  float dx;
  float dy;
};

void update(entt::registry& registry) {
  auto view = registry.view<position, velocity>();

  for (auto entity : view) {
    // gets only the components that are going to be used ...

    auto& vel = view.get<velocity>(entity);

    vel.dx = 0.;
    vel.dy = 0.;

    // ...
  }
}

void update(std::uint64_t dt,
            entt::registry& registry) {
  registry.view<position, velocity>().each([dt](auto& pos, auto& vel) {
    // gets all the components of the view at once ...

    pos.x += vel.dx * dt;
    pos.y += vel.dy * dt;

    // ...
  });
}

auto main() -> int {
  srand(time(nullptr));

  debug::Logger::set_profile(debug::Logger::Profile::DEBUG);
  LOG_INFO("Program started.");
  auto start = std::chrono::system_clock::now();

  std::unique_ptr<gui::Window> window = std::make_unique<gui::Window>(1920, 1080, "Application");

  int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  if (status == 0) {
    LOG_ERROR("Failed to init GLAD");
    glfwTerminate();
    return -1;
  }

  LOG_INFO("OpenGL version: " + std::string((const char*) glGetString(GL_VERSION)));
  LOG_INFO("OpenGL renderer: " + std::string((const char*) glGetString(GL_RENDERER)));
  LOG_INFO("OpenGL vendor: " + std::string((const char*) glGetString(GL_VENDOR)));

  CHECK_GL_ERROR();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  window->init_gui();

  CHECK_GL_ERROR();

  entt::registry registry;
  std::uint64_t dt = 16;

  for (auto i = 0; i < 10; ++i) {
    auto entity = registry.create();
    registry.emplace<position>(entity, i * 1.F, i * 1.F);
    if (i % 2 == 0) {
      registry.emplace<velocity>(entity, i * .1F, i * .1F);
    }
  }

  graphics::GLTFModel model("cube/Cube.gltf", geometry::Transform(geometry::Vector<3>(-1.0F, 1.0F, -1.0F)));
  debug::DebugCamera camera(window.get(), geometry::Rigidbody(geometry::Vector<3>(1.0F, 5.0F, -20.0F)));
  debug::DebugDrawer dd;
  CHECK_GL_ERROR();

  graphics::Cuboid cuboid1(geometry::Transform(geometry::Vector<3>(0.5F, 0.5F, 0.5F), geometry::Orientation(), geometry::Vector<3>(1.0F, 1.0F, 1.0F)),
                           graphics::Color(0.6F, 1.0F, 1.0F));

  graphics::Cuboid cuboid2(geometry::Transform(geometry::Vector<3>(3.5F, 1.0F, 3.5F), geometry::Orientation(), geometry::Vector<3>(1.0F, 2.0F, 1.0F)),
                           graphics::Color(0.6F, 1.0F, 0.6F));

  graphics::Cuboid cuboid3(geometry::Transform(geometry::Vector<3>(6.0F, 0.25F, 1.5F), geometry::Orientation(), geometry::Vector<3>(2.0F, 0.5F, 1.0F)),
                           graphics::Color(1.0F, 0.6F, 0.6F));

  RubiksCube rubik(geometry::Transform(geometry::Vector<3>(-4.5F, 2, -4.5F)));

  float time = 0.0F;

  auto time_before_frame = std::chrono::system_clock::now();

  window->add_on_key_callback([&rubik](GLFWwindow* w, [[maybe_unused]] int n) mutable {
    bool shift_down = (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) != 0);
    if (glfwGetKey(w, GLFW_KEY_KP_4) != 0)
      rubik.rotate_left(shift_down);
    if (glfwGetKey(w, GLFW_KEY_KP_6) != 0)
      rubik.rotate_right(shift_down);
    if (glfwGetKey(w, GLFW_KEY_KP_2) != 0)
      rubik.rotate_bot(shift_down);
    if (glfwGetKey(w, GLFW_KEY_KP_8) != 0)
      rubik.rotate_top(shift_down);
    if (glfwGetKey(w, GLFW_KEY_KP_5) != 0)
      rubik.rotate_back(shift_down);
    if (glfwGetKey(w, GLFW_KEY_KP_0) != 0)
      rubik.rotate_front(shift_down);
  });

  CHECK_GL_ERROR();
  while (!window->is_closing()) {

    CHECK_GL_ERROR();
    update(dt, registry);
    update(registry);

    window->clear_screen();
    glUseProgram(0);

    CHECK_GL_ERROR();
    geometry::Matrix<4> view_projection = camera.projection_matrix() * camera.view_matrix();

    model.render(view_projection);

    auto t    = geometry::Transform();
    t.scale() = {10.0F, 10.0F, 10.0F};

    // Coordinate axis
    dd.draw_transform(t);

    // Grid
    for (int x = -10; x <= 10; x++)
      dd.draw_line(geometry::Vector<3>((float) x, 0, 10), geometry::Vector<3>((float) x, 0, -10));
    for (int z = -10; z <= 10; z++)
      dd.draw_line(geometry::Vector<3>(10, 0, (float) z), geometry::Vector<3>(-10, 0, (float) z));

    dd.render(view_projection);

    cuboid1.transform().orientation() = geometry::Rotation(0, 0, time);
    cuboid2.transform().orientation() = geometry::Rotation(0, time, 0);
    cuboid3.transform().orientation() = geometry::Rotation(time, 0, 0);

    cuboid1.render(view_projection, true);
    cuboid2.render(view_projection, true);
    cuboid3.render(view_projection, true);

    rubik.transform().orientation() = geometry::Rotation(0, time, 0);

    rubik.render(view_projection);

    window->update();
    CHECK_GL_ERROR();

    time += 0.02F;

    auto time_spent_on_frame = std::chrono::system_clock::now() - time_before_frame;
    if (time_spent_on_frame.count() < 1000.0F / 60.0F) {
      std::chrono::duration<double, std::milli> time_left_on_frame((1000.0 / 60.0) - time_spent_on_frame.count());
      std::this_thread::sleep_for(time_left_on_frame);
    }
    time_before_frame = std::chrono::system_clock::now();
    // std::time_t tnow  = std::chrono::system_clock::to_time_t(time_before_frame);
    // LOG_DEBUG(std::ctime(&tnow));
  }

  auto end = std::chrono::system_clock::now();
  LOG_INFO("Program terminated.");

  std::chrono::duration<double> elapsed_seconds = end - start;
  LOG_INFO("Uptime: " + std::to_string(elapsed_seconds.count()) + " seconds.");
}
