#pragma once

#include <vulkan/vulkan.h>

namespace engine::graphics::api::vulkan {

  class Queue {
  public:
    Queue(VkDevice& device, uint32_t queue_family_index);

    void submit(VkSubmitInfo& submit_info, VkFence fence);
    void wait_until_idle();

  private:
    VkQueue _queue;
  };

}
