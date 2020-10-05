#include "obj_model.hpp"

#include "../../../debug/logger.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

using namespace engine::graphics::api::vulkan;

OBJModel::OBJModel(std::string file_path) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file_path.c_str()))
    LOG_ERROR(warn + err);

  std::unordered_map<Vertex, uint32_t> unique_vertices{};

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex{};

      vertex.pos = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]};

      vertex.texCoord = {
        attrib.texcoords[2 * index.texcoord_index + 0],
        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]};

      vertex.color = {1.0f, 1.0f, 1.0f};

      if (unique_vertices.count(vertex) == 0) {
        unique_vertices[vertex] = static_cast<uint32_t>(_vertices.size());
        _vertices.push_back(vertex);
      }

      _indices.push_back(unique_vertices[vertex]);
    }
  }
}

auto OBJModel::vertices() -> std::vector<Vertex>& {
  return _vertices;
}

auto OBJModel::indices() -> std::vector<uint32_t>& {
  return _indices;
}
