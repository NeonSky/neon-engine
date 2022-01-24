#include "../application.hpp"

namespace engine::graphics::api::opengl {

  class Application : public IApplication {
  public:
    Application();

    /// @brief Creates a new graphics context.
    auto create_context() -> std::unique_ptr<IContext>;
  };

}
