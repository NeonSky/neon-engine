#pragma once

#include "../architecture/ecs.hpp"

#include "../os/window_manager.hpp"
#include "opengl/context.hpp"
#include "renderable.hpp"

#include <memory>
#include <vector>

namespace engine::graphics {

  /// @brief Renderer renders given scenes to one or multiple windows.
  ///
  /// @todo render() should take a list of window targets so it can call renderable.render() once and then copy the pixels/result to all windows.
  /// @todo render() should maybe have option to not clear/update.
  /// @todo replace opengl contexts with generic contexts containing references to their windows.
  /// @todo rename to RenderSystem
  /// @TODO Listen to debug callback: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageCallback.xhtml
  class Renderer {
  public:
    Renderer(os::WindowManager& wm);

    void render(architecture::ECS& ecs, unsigned int window_id, geometry::Matrix<4> view_projection);

    auto current_context() -> opengl::Context&;
    [[nodiscard]] auto context_count() const -> unsigned int;

  private:
    os::WindowManager& _wm;
    unsigned int _current_context = 0;
    std::vector<opengl::Context> _render_contexts;
    std::vector<std::unique_ptr<architecture::IEntitySystem>> _render_systems;
  };
};
