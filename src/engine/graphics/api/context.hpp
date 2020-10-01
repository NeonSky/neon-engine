#pragma once

#include "../../architecture/interface.hpp"

#include <memory>

namespace engine::graphics::api {

  /// @todo Create VAO class.
  struct IContext : public architecture::Interface {
    virtual auto gen_vao() -> unsigned int            = 0;
    virtual auto vao(unsigned int id) -> unsigned int = 0;
    virtual auto is_vao(unsigned int id) -> bool      = 0;
  };

  enum class GraphicsAPI {
    OPENGL,
    VULKAN,
  };

  /// @brief Creates a new graphics context that uses the graphics API specified by \p api.
  auto create_context(GraphicsAPI api) -> std::unique_ptr<IContext>;

}
