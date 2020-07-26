#pragma once

#include "../geometry/matrix.hpp"
#include "../graphics/camera.hpp"
#include "../gui/window.hpp"

namespace engine::debug {

  class DebugCamera {
  public:
    DebugCamera(gui::Window* window);
    DebugCamera(gui::Window* window, const geometry::Transform& transform);

    // Mutators
    auto transform() -> geometry::Transform&;

    // Accessors
    [[nodiscard]] auto view_matrix() const -> geometry::Matrix<4>;
    [[nodiscard]] auto projection_matrix() const -> geometry::Matrix<4>;
    [[nodiscard]] auto mouse_ray() const -> geometry::Vector<3>;

  private:
    static constexpr float zoom_min = 0.0F;
    static constexpr float zoom_max = 45.0F;

    graphics::Camera _camera;
    gui::Window* _window;

    geometry::Vector<3> _mouse_ray;
    graphics::ProjectionType _projection_type = graphics::ProjectionType::PERSPECTIVE;
    bool _free_look_mode                      = false;
    float _zoom                               = 0.0F;

    // Mutators
    void on_key(GLFWwindow* window);
    void on_cursor(GLFWwindow* window, float xpos, float ypos);
    void on_scroll(GLFWwindow* window, float xoffset, float yoffset);
  };
}
