#pragma once

#include "../../architecture/interface.hpp"

#include "context.hpp"

namespace engine::graphics::api {

  struct IApplication : public architecture::Interface {

    /// @brief Creates a new graphics context.
    // virtual auto create_context() -> std::unique_ptr<IContext> = 0;
  };

  enum class Backend {
    OPENGL,
    VULKAN,
  };

  /// @brief Creates a new graphics application that uses the backend specified by \p backend.
  auto create_application(Backend backend) -> std::unique_ptr<IApplication>;

}
