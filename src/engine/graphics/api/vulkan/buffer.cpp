#include "buffer.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

VkCommandBuffer begin_single_time_commands(VkDevice& device, VkCommandPool& commandPool) {
  VkCommandBufferAllocateInfo alloc_info{};
  alloc_info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool        = commandPool;
  alloc_info.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  vkAllocateCommandBuffers(device, &alloc_info, &command_buffer);

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(command_buffer, &begin_info);

  return command_buffer;
}

void end_single_time_commands(VkCommandBuffer commandBuffer, Queue& queue, VkDevice& device, VkCommandPool& commandPool) {
  vkEndCommandBuffer(commandBuffer);

  VkSubmitInfo submit_info{};
  submit_info.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers    = &commandBuffer;

  queue.submit(submit_info, VK_NULL_HANDLE);
  queue.wait_until_idle();

  vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

namespace engine::graphics::api::vulkan {

  void create_buffer(PhysicalDevice& physical_device,
                     VkDevice& device,
                     VkDeviceSize size,
                     VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags properties,
                     VkBuffer& buffer,
                     VkDeviceMemory& bufferMemory) {

    VkBufferCreateInfo buffer_info{};
    buffer_info.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_info.size        = size;
    buffer_info.usage       = usage;
    buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &buffer_info, nullptr, &buffer) != VK_SUCCESS)
      LOG_ERROR("Failed to create buffer.");

    VkMemoryRequirements mem_requirements;
    vkGetBufferMemoryRequirements(device, buffer, &mem_requirements);

    VkMemoryAllocateInfo alloc_info{};
    alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize  = mem_requirements.size;
    alloc_info.memoryTypeIndex = physical_device.find_memory_type(mem_requirements.memoryTypeBits, properties);

    if (vkAllocateMemory(device, &alloc_info, nullptr, &bufferMemory) != VK_SUCCESS)
      LOG_ERROR("Failed to allocate buffer memory.");

    vkBindBufferMemory(device, buffer, bufferMemory, 0);
  }

  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, Queue& queue, VkDevice& device, VkCommandPool& commandPool) {
    VkCommandBuffer commandBuffer = begin_single_time_commands(device, commandPool);

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    end_single_time_commands(commandBuffer, queue, device, commandPool);
  }
}
