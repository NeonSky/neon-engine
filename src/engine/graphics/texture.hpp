#pragma once

#include <glad/glad.h>
#include <string>

namespace engine::graphics {

  class Texture {
  public:
    Texture(const std::string& img_path);

    // Accessors
    [[nodiscard]] auto id() const -> GLuint;

  private:
    GLuint _texture;
  };
}
