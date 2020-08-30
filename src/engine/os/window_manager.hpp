#pragma once

#include "input_manager.hpp"
#include "window.hpp"

#include <memory>
#include <vector>

namespace engine::os {

  /// Each window has its own OpenGL context, but all windows share the same context objects.
  /// @see https://www.khronos.org/opengl/wiki/OpenGL_Context
  class WindowManager {
  public:
    WindowManager();
    ~WindowManager();

    /// @name Mutators
    /// @{

    void create_window();
    void destroy_window(unsigned int window_id);

    /// @brief Sets the OpenGL context of this thread to the one associated with the window that has ID \p window_id.
    ///
    /// A context must only be made current on a single thread at a time and each thread can have only a single current context at a time.
    void set_render_target(unsigned int window_id);

    void clear_target();

    /// @brief Swaps front/back buffers of the current render target, and also polls for input events.
    void refresh_target();

    /// @}
    /// @name Accessors
    /// @{

    [[nodiscard]] auto input_manager() const -> const InputManager&;
    [[nodiscard]] auto is_target_available(unsigned int window_id) const -> bool;
    [[nodiscard]] auto render_target() const -> const Window&;
    [[nodiscard]] auto window_count() const -> unsigned int;

    /// @}
    /// @name Events
    /// @{

    void on_window_created(const std::function<void(unsigned int)>& callback) const;
    void on_window_closed(const std::function<void(unsigned int)>& callback) const;
    void on_all_windows_closed(const std::function<void()>& callback) const;

    /// @}

  private:
    /// @{
    /// Private state.
    static unsigned int _instances;       //< Amount of instances of this class.
    unsigned int _current;                //< Current render target.
    std::unique_ptr<Window> _base_window; //< Owns the base OpenGL context from which other windows share/derive.
    std::vector<std::unique_ptr<Window>> _windows;
    InputManager _input_manager;

    mutable std::vector<std::function<void(unsigned int)>> _on_window_created_callbacks;
    mutable std::vector<std::function<void(unsigned int)>> _on_window_closed_callbacks;
    mutable std::vector<std::function<void()>> _on_all_windows_closed_callbacks;
    /// @}

    void poll_errors();
  };
}
