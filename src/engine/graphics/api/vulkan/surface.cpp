#include "surface.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

Surface::Surface(VkInstance& instance, GLFWwindow* window) : _instance(instance) {
  if (glfwCreateWindowSurface(_instance, window, nullptr, &_surface) != VK_SUCCESS)
    LOG_ERROR("Failed to create window surface.");
}

Surface::~Surface() {
  vkDestroySurfaceKHR(_instance, _surface, nullptr);
}

auto Surface::surface() -> VkSurfaceKHR& {
  return _surface;
}
