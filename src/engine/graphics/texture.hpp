#pragma once

#include <glad/glad.h>
#include <string>

namespace engine::graphics {

  class Texture {
  public:
    Texture(std::string img_path);
    ~Texture();

    // Accessors
    [[nodiscard]] auto id() const -> GLuint;

  private:
    GLuint _texture;
  };
}
