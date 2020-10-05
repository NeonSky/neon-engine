#pragma once

#include "physical_device.hpp"
#include "queue.hpp"

#include <vulkan/vulkan.h>

namespace engine::graphics::api::vulkan {

  void create_buffer(PhysicalDevice& physical_device,
                     VkDevice& device,
                     VkDeviceSize size,
                     VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags properties,
                     VkBuffer& buffer,
                     VkDeviceMemory& bufferMemory);

  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, Queue& queue, VkDevice& device, VkCommandPool& commandPool);

}
