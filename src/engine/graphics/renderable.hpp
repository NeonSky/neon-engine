#pragma once

namespace engine::graphics {

  struct IRenderable {
    virtual void render() = 0;
  };

}
