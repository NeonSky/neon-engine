#pragma once

#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

namespace engine::graphics::api::vulkan {
  class Surface {
  public:
    Surface(VkInstance& instance, GLFWwindow* window);
    ~Surface();

    auto surface() -> VkSurfaceKHR&;

  private:
    VkSurfaceKHR _surface;
    VkInstance& _instance;
  };
}
