#pragma once

#include "../graphics/camera.hpp"
#include "../gui/window.hpp"

namespace engine::debug {

  class DebugCamera {
  public:
    DebugCamera(engine::gui::Window* window);
    DebugCamera(engine::gui::Window* window, engine::geometry::Transform transform);
    ~DebugCamera();

    // Mutators
    void set_transform(engine::geometry::Transform transform);

    // Accessors
    [[nodiscard]] auto transform() const -> engine::geometry::Transform;
    [[nodiscard]] auto view_matrix() const -> glm::mat4;
    [[nodiscard]] auto projection_matrix() const -> glm::mat4;
    [[nodiscard]] auto mouse_ray() const -> glm::vec3;

  private:
    static constexpr float zoom_min = 0.0F;
    static constexpr float zoom_max = 45.0F;

    engine::graphics::Camera camera;
    engine::gui::Window* window;

    glm::vec3 _mouse_ray;
    engine::graphics::ProjectionType projection_type = engine::graphics::ProjectionType::PERSPECTIVE;
    bool free_look_mode                              = false;
    float zoom                                       = 0.0F;

    // Mutators
    void on_key(GLFWwindow* window);
    void on_cursor(GLFWwindow* window, float xpos, float ypos);
    void on_scroll(GLFWwindow* window, float xoffset, float yoffset);
  };
}
