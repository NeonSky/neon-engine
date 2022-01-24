#include "application.hpp"

#include "opengl/application.hpp"
#include "vulkan/application.hpp"

namespace engine::graphics::api {

  auto create_application(Backend backend) -> std::unique_ptr<IApplication> {
    switch (backend) {
    case Backend::OPENGL:
      return std::make_unique<opengl::Application>();
    case Backend::VULKAN:
      return std::make_unique<vulkan::Application>();
    default:
      LOG_CRITICAL("The requested graphics backend is currently not supported.");
    }
  }

}
