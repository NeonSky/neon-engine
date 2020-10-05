#pragma once

#include "physical_device.hpp"
#include "queue.hpp"

#include <vulkan/vulkan.h>

namespace engine::graphics::api::vulkan {

  class IndexBuffer {
  public:
    IndexBuffer(PhysicalDevice& physical_device, VkDevice& device, std::vector<uint32_t> indices, Queue& queue, VkCommandPool& commandPool);
    ~IndexBuffer();

    void bind(VkCommandBuffer& command_buffer);

    auto buffer() -> VkBuffer&;

  private:
    VkDevice& _device;

    VkBuffer _buffer;
    VkDeviceMemory _memory;
  };

}
