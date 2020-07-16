#pragma once

#include "../graphics/camera.hpp"
#include "../gui/window.hpp"

namespace engine::debug {

  class DebugCamera {
  public:
    DebugCamera(engine::gui::Window* window);
    DebugCamera(engine::gui::Window* window, const engine::geometry::Transform& transform);

    // Mutators
    auto transform() -> engine::geometry::Transform&;

    // Accessors
    [[nodiscard]] auto view_matrix() const -> glm::mat4;
    [[nodiscard]] auto projection_matrix() const -> glm::mat4;
    [[nodiscard]] auto mouse_ray() const -> glm::vec3;

  private:
    static constexpr float zoom_min = 0.0F;
    static constexpr float zoom_max = 45.0F;

    engine::graphics::Camera _camera;
    engine::gui::Window* _window;

    glm::vec3 _mouse_ray                              = glm::vec3(0.0F);
    engine::graphics::ProjectionType _projection_type = engine::graphics::ProjectionType::PERSPECTIVE;
    bool _free_look_mode                              = false;
    float _zoom                                       = 0.0F;

    // Mutators
    void on_key(GLFWwindow* window);
    void on_cursor(GLFWwindow* window, float xpos, float ypos);
    void on_scroll(GLFWwindow* window, float xoffset, float yoffset);
  };
}
