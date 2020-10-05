#pragma once

#include "physical_device.hpp"
#include "queue.hpp"
#include "vertex.hpp"

#include <vulkan/vulkan.h>

namespace engine::graphics::api::vulkan {

  class VertexBuffer {
  public:
    VertexBuffer(PhysicalDevice& physical_device, VkDevice& device, std::vector<Vertex>& vertex_data, Queue& queue, VkCommandPool& commandPool);
    ~VertexBuffer();

    auto buffer() -> VkBuffer&;

  private:
    VkDevice& _device;

    VkBuffer _buffer;
    VkDeviceMemory _memory;
  };

}
