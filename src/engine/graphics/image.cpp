#include "image.hpp"

#include "../debug/logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace engine::graphics;

Image::Image(std::string img_path) {
  stbi_set_flip_vertically_on_load(1); // Match OpenGL

  std::string res_path  = boost::dll::program_location().parent_path().string() + "/res/img/";
  std::string full_path = res_path + img_path;
  _data                 = std::make_unique<unsigned char>(*stbi_load(full_path.c_str(), &_width, &_height, &_components, STBI_rgb_alpha));

  if (_data == nullptr)
    LOG_ERROR("Failed to load image: " + full_path);
}

Image::~Image() = default;

auto Image::data() const -> const unsigned char* {
  return _data.get();
}

auto Image::width() const -> unsigned int {
  return _width;
}

auto Image::height() const -> unsigned int {
  return _height;
}
