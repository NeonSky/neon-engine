#include "index_buffer.hpp"

#include "buffer.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

IndexBuffer::IndexBuffer(PhysicalDevice& physical_device, VkDevice& device, std::vector<uint32_t> indices, Queue& queue, VkCommandPool& commandPool)
        : _device(device) {

  VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  create_buffer(physical_device, _device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(_device, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, indices.data(), (size_t) bufferSize);
  vkUnmapMemory(_device, stagingBufferMemory);

  create_buffer(physical_device, _device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _buffer, _memory);

  copy_buffer(stagingBuffer, _buffer, bufferSize, queue, _device, commandPool);

  vkDestroyBuffer(_device, stagingBuffer, nullptr);
  vkFreeMemory(_device, stagingBufferMemory, nullptr);
}

IndexBuffer::~IndexBuffer() {
  vkDestroyBuffer(_device, _buffer, nullptr);
  vkFreeMemory(_device, _memory, nullptr);
}

void IndexBuffer::bind(VkCommandBuffer& command_buffer) {
  vkCmdBindIndexBuffer(command_buffer, _buffer, 0, VK_INDEX_TYPE_UINT32);
}

auto IndexBuffer::buffer() -> VkBuffer& {
  return _buffer;
}
