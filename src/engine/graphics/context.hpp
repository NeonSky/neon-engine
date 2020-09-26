#pragma once

#include "context_implementation.hpp"

#include <memory>

namespace engine::graphics {

  class Context {
  public:
    Context();

  private:
    std::unique_ptr<IContextImplementation> _implementation;
  };

}
