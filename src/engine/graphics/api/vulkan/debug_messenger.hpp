#pragma once

#include <vulkan/vulkan.h>

namespace engine::graphics::api::vulkan {

  class DebugMessenger {
  public:
    DebugMessenger();
    DebugMessenger(VkInstance& instance);
    ~DebugMessenger();

  private:
    VkInstance& _instance;
    VkDebugUtilsMessengerEXT _messenger;
  };

}
