#pragma once

#include <stb_image.h>
#include <stb_image_write.h>

#include <memory>
#include <string>

namespace engine::graphics {

  class Image {
  public:
    Image(const std::string& img_path);

    [[nodiscard]] auto data() const -> const unsigned char*;
    [[nodiscard]] auto width() const -> unsigned int;
    [[nodiscard]] auto height() const -> unsigned int;

  private:
    std::unique_ptr<unsigned char> _data;
    int _width      = 0;
    int _height     = 0;
    int _components = 0;
  };
}
