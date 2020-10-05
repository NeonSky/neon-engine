#pragma once

#include "vertex.hpp"

#include <string>
#include <vector>

namespace engine::graphics::api::vulkan {

  /// @brief OBJModel represents an OBJ model.
  class OBJModel {
  public:
    OBJModel(std::string file_path);

    auto vertices() -> std::vector<Vertex>&;
    auto indices() -> std::vector<uint32_t>&;

  private:
    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;
  };

}
