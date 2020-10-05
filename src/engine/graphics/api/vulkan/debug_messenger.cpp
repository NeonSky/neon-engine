#include "debug_messenger.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

VKAPI_ATTR VkBool32 VKAPI_CALL callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                        void* pUserData) {

  if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    LOG_WARNING("Validation layer: " + std::string(pCallbackData->pMessage));
  } else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    LOG_WARNING("Validation layer: " + std::string(pCallbackData->pMessage));
  } else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    LOG_INFO("Validation layer: " + std::string(pCallbackData->pMessage));
  } else
    LOG_DEBUG("Validation layer: " + std::string(pCallbackData->pMessage));

  return VK_FALSE;
}

DebugMessenger::DebugMessenger(VkInstance& instance)
        : _instance(instance) {

  VkDebugUtilsMessengerCreateInfoEXT create_info{};
  create_info.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  create_info.pfnUserCallback = callback;

  // if (CreateDebugUtilsMessengerEXT(_instance, &create_info, nullptr, &_messenger) != VK_SUCCESS)
  //   LOG_ERROR("Failed to create debug messenger!");

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    VkResult res = func(_instance, &create_info, nullptr, &_messenger);
    if (res != VK_SUCCESS)
      LOG_ERROR("Failed to create debug messenger!");
  } else
    LOG_ERROR("Failed to create debug messenger!");
}

DebugMessenger::~DebugMessenger() {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr)
    func(_instance, _messenger, nullptr);
}
