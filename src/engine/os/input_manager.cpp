#include "input_manager.hpp"

#include <algorithm>

using namespace engine::os;

void InputManager::add_window(Window& window) {
  _windows.push_back(window);

  window.on_key([this, &window](KeyCode code, KeyAction action, const ActivatedModifiers& mods) {
    for (auto& c : _on_key_callbacks)
      c(window, code, action, mods);
  });

  window.on_mouse_click([this, &window](MouseCode code, MouseAction action, const ActivatedModifiers& mods) {
    for (auto& c : _on_mouse_click_callbacks)
      c(window, code, action, mods);
  });

  window.on_mouse_move([this, &window](float x, float y) {
    for (auto& c : _on_mouse_move_callbacks)
      c(window, x, y);
  });

  window.on_mouse_scroll([this, &window](float x, float y) {
    for (auto& c : _on_mouse_scroll_callbacks)
      c(window, x, y);
  });
}

void InputManager::remove_window(Window& window) {
  for (unsigned int i = 0; i < _windows.size(); i++) {
    if (&_windows[i].get() == &window) {
      _windows.erase(_windows.begin() + i);
      break;
    }
  }
}

void InputManager::on_key(const std::function<void(const Window&, KeyCode, KeyAction, const ActivatedModifiers&)>& callback) const {
  _on_key_callbacks.push_back(callback);
}

void InputManager::on_mouse_click(const std::function<void(const Window&, MouseCode, MouseAction, const ActivatedModifiers&)>& callback) const {
  _on_mouse_click_callbacks.push_back(callback);
}

void InputManager::on_mouse_move(const std::function<void(const Window&, float, float)>& callback) const {
  _on_mouse_move_callbacks.push_back(callback);
}

void InputManager::on_mouse_scroll(const std::function<void(const Window&, float, float)>& callback) const {
  _on_mouse_scroll_callbacks.push_back(callback);
}

auto InputManager::is_key_down(KeyCode keycode) const -> bool {
  for (auto& w : _windows)
    if (w.get().is_key_down(keycode))
      return true;
  return false;
}
