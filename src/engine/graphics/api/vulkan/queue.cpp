#include "queue.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

Queue::Queue(VkDevice& device, uint32_t queue_family_index) {
  vkGetDeviceQueue(device, queue_family_index, 0, &_queue);
}

void Queue::submit(VkSubmitInfo& submit_info, VkFence fence) {
  uint32_t submit_count = 1;
  if (vkQueueSubmit(_queue, submit_count, &submit_info, fence) != VK_SUCCESS)
    LOG_ERROR("Failed to submit queue data.");
}

void Queue::wait_until_idle() {
  vkQueueWaitIdle(_queue);
}

VkResult Queue::present(VkPresentInfoKHR& present_info) {
  return vkQueuePresentKHR(_queue, &present_info);
}
