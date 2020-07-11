#pragma once

#include <stb_image.h>
#include <stb_image_write.h>

#include <memory>
#include <string>

namespace engine::graphics {

  class Image {
  public:
    Image(std::string img_path);
    ~Image();

    const unsigned char* data() const;
    unsigned int width() const;
    unsigned int height() const;

  private:
    std::unique_ptr<unsigned char> _data;
    int _width;
    int _height;
    int _components;

  };
}
