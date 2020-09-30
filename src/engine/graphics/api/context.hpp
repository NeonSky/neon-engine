#pragma once

#include "../../architecture/interface.hpp"

#include <memory>

namespace engine::graphics::api {

  /// @todo Create VAO class.
  struct IContext : public architecture::Interface {
    virtual unsigned int gen_vao()            = 0;
    virtual unsigned int vao(unsigned int id) = 0;
    virtual bool is_vao(unsigned int id)      = 0;
  };

  enum class GraphicsAPI {
    OPENGL,
    VULKAN,
  };

  /// @brief Creates a new graphics context that uses the graphics API specified by \p api.
  auto create_context(GraphicsAPI api) -> std::unique_ptr<IContext>;

  int test();

}
