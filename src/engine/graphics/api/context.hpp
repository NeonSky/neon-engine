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

}
