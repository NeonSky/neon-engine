#pragma once

#include "../graphics/api/application.hpp"
#include "../graphics/api/context.hpp"

#include "../geometry/vector.hpp"
#include "input.hpp"

#include <functional>
#include <vector>

class GLFWwindow;

namespace engine::os {

  /// @todo title should be std::string
  /// @todo clear_color should be graphics::color
  /// @todo remove glad include from .cpp file.
  class Window {
  public:
    Window();
    Window(unsigned int width, unsigned int height);
    Window(unsigned int width, unsigned int height, const char* title);
    // Window(unsigned int width, unsigned int height, const char* title, Window& parent);
    Window(unsigned int width, unsigned int height, const char* title, Window& parent, graphics::api::IApplication& app);

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

    [[nodiscard]] auto graphics_context() const -> graphics::api::IContext&;

    // Accessors
    [[nodiscard]] auto title() const -> std::string;
    [[nodiscard]] auto is_closing() const -> bool;
    [[nodiscard]] auto width() const -> unsigned int;
    [[nodiscard]] auto height() const -> unsigned int;

    [[nodiscard]] auto is_key_down(KeyCode keycode) const -> bool;

  private:
    Window(unsigned int width, unsigned int height, const char* title, Window* parent, graphics::api::IApplication* app);

    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> _window;
    mutable std::unique_ptr<graphics::api::IContext> _graphics_context;
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
