#pragma once

#include "../graphics/camera.hpp"
#include "../os/input_manager.hpp"

namespace engine::debug {

  class DebugCamera {
  public:
    DebugCamera(const os::InputManager& input_manager);
    DebugCamera(const os::InputManager& input_manager, const geometry::Rigidbody& rigidbody);

    // Mutators
    auto rigidbody() -> geometry::Rigidbody&;

    // Accessors
    [[nodiscard]] auto view_matrix() const -> geometry::Matrix<4>;
    [[nodiscard]] auto projection_matrix() const -> geometry::Matrix<4>;
    [[nodiscard]] auto mouse_ray() const -> geometry::Vector<3>;

  private:
    static constexpr float zoom_min = 0.0F;
    static constexpr float zoom_max = 45.0F;

    graphics::Camera _camera;
    const os::InputManager& _input_manager;

    geometry::Vector<3> _mouse_ray;
    graphics::ProjectionType _projection_type = graphics::ProjectionType::PERSPECTIVE;
    bool _free_look_mode                      = false;
    float _zoom                               = 0.0F;

    // Mutators
    void on_key(const os::Window& window, os::KeyCode keycode, os::KeyAction action);
    void on_mouse_move(const os::Window& window, float xpos, float ypos);
    void on_mouse_scroll(const os::Window& window, float xoffset, float yoffset);
  };
}
