#pragma once

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

namespace engine::graphics::api::vulkan {

  /// @brief PhysicalDevice represents a single complete implementation of Vulkan (e.g. a modern GPU).
  class PhysicalDevice {
  public:
    PhysicalDevice(VkInstance& instance);

    VkDevice create_logical_device(VkDeviceCreateInfo& create_info);

    QueueFamilyIndices find_queue_families(VkSurfaceKHR surface);
    QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface);
    SwapChainSupportDetails query_swap_chain_support(VkSurfaceKHR surface);
    SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface);

    VkFormatProperties format_properties(VkFormat format);
    VkPhysicalDeviceMemoryProperties memory_properties();

  private:
    VkPhysicalDevice _device = VK_NULL_HANDLE;

    bool is_suitable(VkPhysicalDevice device);
    bool check_extension_support(VkPhysicalDevice device);
  };

}
