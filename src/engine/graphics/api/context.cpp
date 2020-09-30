#include "context.hpp"

#include "opengl/context.hpp"

namespace engine::graphics::api {

  auto create_context(GraphicsAPI api) -> std::unique_ptr<IContext> {
    switch (api) {
    case GraphicsAPI::OPENGL:
      return std::make_unique<opengl::Context>();
      break;
    default:
      LOG_CRITICAL("The chosen graphics api is currently not supported.");
    }
  }

}
