#include "physical_device.hpp"

#include "../../../debug/logger.hpp"

#include <set>

using namespace engine::graphics::api::vulkan;

const std::vector<const char*> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

PhysicalDevice::PhysicalDevice(VkInstance& instance) {
  // Query available drivers
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

  if (device_count == 0)
    LOG_CRITICAL("Failed to find any GPU with Vulkan support.");

  // Store handles to the available devices
  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

  // Pick any device that is considered suitable
  for (const auto& device : devices) {
    if (is_suitable(device)) {
      _device = device;
      break;
    }
  }

  if (_device == VK_NULL_HANDLE)
    LOG_CRITICAL("Failed to find a suitable GPU!");
}

VkDevice PhysicalDevice::create_logical_device(VkDeviceCreateInfo& create_info) {
  VkDevice logical_device;
  if (vkCreateDevice(_device, &create_info, nullptr, &logical_device) != VK_SUCCESS)
    LOG_ERROR("Failed to create logical device!");

  return logical_device;
}

QueueFamilyIndices PhysicalDevice::find_queue_families(VkSurfaceKHR surface) {
  return find_queue_families(_device, surface);
}

QueueFamilyIndices PhysicalDevice::find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface) {
  QueueFamilyIndices indices;

  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

  int i = 0;
  for (const auto& queue_family : queue_families) {
    if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      indices.graphicsFamily = i;

    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);

    if (present_support)
      indices.presentFamily = i;

    if (indices.isComplete())
      break;

    i++;
  }

  return indices;
}

SwapChainSupportDetails PhysicalDevice::query_swap_chain_support(VkSurfaceKHR surface) {
  return query_swap_chain_support(_device, surface);
}

SwapChainSupportDetails PhysicalDevice::query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface) {
  SwapChainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);

  if (format_count != 0) {
    details.formats.resize(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
  }

  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

  if (present_mode_count != 0) {
    details.presentModes.resize(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.presentModes.data());
  }

  return details;
}

uint32_t PhysicalDevice::find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties mem_properties = memory_properties();

  for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
    if ((typeFilter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
      return i;

  LOG_ERROR("Failed to find suitable memory type.");
}

VkFormatProperties PhysicalDevice::format_properties(VkFormat format) {
  VkFormatProperties properties;
  vkGetPhysicalDeviceFormatProperties(_device, format, &properties);
  return properties;
}

VkPhysicalDeviceMemoryProperties PhysicalDevice::memory_properties() {
  VkPhysicalDeviceMemoryProperties properties;
  vkGetPhysicalDeviceMemoryProperties(_device, &properties);
  return properties;
}

bool PhysicalDevice::is_suitable(VkPhysicalDevice device) {
  // QueueFamilyIndices indices = find_queue_families(device);
  // if (!indices.isComplete())
  //   return false;

  // if (!check_extension_support(device))
  //   return false;

  // SwapChainSupportDetails swap_chain_support = query_swap_chain_support(device);
  // bool swap_chain_adequate                   = !swap_chain_support.formats.empty() && !swap_chain_support.presentModes.empty();
  // if (!swap_chain_adequate)
  //   return false;

  // VkPhysicalDeviceFeatures supported_features;
  // vkGetPhysicalDeviceFeatures(device, &supported_features);
  // if (!supported_features.samplerAnisotropy)
  //   return false;

  return true;
}

bool PhysicalDevice::check_extension_support(VkPhysicalDevice device) {
  uint32_t extension_count;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extension_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, availableExtensions.data());

  std::set<std::string> requiredExtensions(device_extensions.begin(), device_extensions.end());

  for (const auto& extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}
