#pragma once

#include "iwindow.hpp"

#include "../geometry/vector.hpp"
#include "input.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>

namespace engine::os {

  /// @todo title should be std::string
  /// @todo clear_color should be graphics::color
  class Window : public IWindow {
  public:
    Window();
    Window(unsigned int width, unsigned int height);
    Window(unsigned int width, unsigned int height, const char* title);
    Window(unsigned int width, unsigned int height, const char* title, Window& parent);

    // Mutators
    void lock_mouse_cursor() const;
    void release_mouse_cursor() const;
    void hide_mouse_cursor() const;

    void set_as_current();
    void init_gui();
    void update();
    void clear_screen() const;
    void toggle_fullscreen();

    void on_should_close(const std::function<void()>& callback) const;

    void on_key(const std::function<void(KeyCode, KeyAction, const ActivatedModifiers&)>& callback) const;
    void on_mouse_click(const std::function<void(MouseCode, MouseAction, const ActivatedModifiers&)>& callback) const;
    void on_mouse_move(const std::function<void(float, float)>& callback) const;
    void on_mouse_scroll(const std::function<void(float, float)>& callback) const;

    // Accessors
    [[nodiscard]] auto title() const -> std::string override;
    [[nodiscard]] auto is_closing() const -> bool override;
    [[nodiscard]] auto width() const -> unsigned int override;
    [[nodiscard]] auto height() const -> unsigned int override;

    [[nodiscard]] auto is_key_down(KeyCode keycode) const -> bool;

  private:
    Window(unsigned int width, unsigned int height, const char* title, Window* parent);

    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> _window;
    std::string _title;
    unsigned int _width  = 0;
    unsigned int _height = 0;
    geometry::Vector<4> _clear_color;

    mutable std::vector<std::function<void()>> _on_should_close_callbacks;
    mutable std::vector<std::function<void(KeyCode, KeyAction, const ActivatedModifiers&)>> _on_key_callbacks;
    mutable std::vector<std::function<void(MouseCode, MouseAction, const ActivatedModifiers&)>> _on_mouse_click_callbacks;
    mutable std::vector<std::function<void(float, float)>> _on_mouse_move_callbacks;
    mutable std::vector<std::function<void(float, float)>> _on_mouse_scroll_callbacks;
  };

}
