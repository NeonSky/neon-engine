#pragma once

#include "window.hpp"

#include <functional>
#include <vector>

namespace engine::os {

  /// @todo Have InputManager listen to window manager and its windows instead of having add_window() and remove_window()
  class InputManager {
  public:
    void add_window(Window& window);
    void remove_window(Window& window);

    void on_key(const std::function<void(const Window&, KeyCode, KeyAction, const ActivatedModifiers&)>& callback) const;
    void on_mouse_click(const std::function<void(const Window&, MouseCode, MouseAction, const ActivatedModifiers&)>& callback) const;
    void on_mouse_move(const std::function<void(const Window&, float, float)>& callback) const;
    void on_mouse_scroll(const std::function<void(const Window&, float, float)>& callback) const;

    auto is_key_down(KeyCode keycode) const -> bool;

  private:
    mutable std::vector<std::function<void(const Window&, KeyCode, KeyAction, const ActivatedModifiers&)>> _on_key_callbacks;
    mutable std::vector<std::function<void(const Window&, MouseCode, MouseAction, const ActivatedModifiers&)>> _on_mouse_click_callbacks;
    mutable std::vector<std::function<void(const Window&, float, float)>> _on_mouse_move_callbacks;
    mutable std::vector<std::function<void(const Window&, float, float)>> _on_mouse_scroll_callbacks;

    std::vector<std::reference_wrapper<Window>> _windows;
  };

}
