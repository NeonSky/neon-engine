#include "vertex_buffer.hpp"

#include "buffer.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

VertexBuffer::VertexBuffer(PhysicalDevice& physical_device, VkDevice& device, std::vector<Vertex>& vertex_data, Queue& queue, VkCommandPool& commandPool)
        : _device(device) {

  VkDeviceSize buffer_size = sizeof(vertex_data[0]) * vertex_data.size();

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  create_buffer(physical_device, device, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, staging_buffer, staging_buffer_memory);

  void* data;
  vkMapMemory(device, staging_buffer_memory, 0, buffer_size, 0, &data);
  memcpy(data, vertex_data.data(), (size_t) buffer_size);
  vkUnmapMemory(device, staging_buffer_memory);

  create_buffer(physical_device, device, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _buffer, _memory);

  copy_buffer(staging_buffer, _buffer, buffer_size, queue, _device, commandPool);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);
}

VertexBuffer::~VertexBuffer() {
  vkDestroyBuffer(_device, _buffer, nullptr);
  vkFreeMemory(_device, _memory, nullptr);
}

auto VertexBuffer::buffer() -> VkBuffer& {
  return _buffer;
}
