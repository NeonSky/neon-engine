#include "context.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

Context::Context(VkInstance& instance, VkSurfaceKHR surface)
        : _instance(instance),
          _surface(surface) {
  // if (glfwCreateWindowSurface(_instance, window, nullptr, &_surface) != VK_SUCCESS)
  //   LOG_ERROR("Failed to create window surface.");
}

Context::~Context() {
  vkDestroySurfaceKHR(_instance, _surface, nullptr);
}

auto Context::gen_vao() -> unsigned int {
  LOG_WARNING("Not implemented.");
  return 0;
}

auto Context::vao(unsigned int id) -> unsigned int {
  LOG_WARNING("Not implemented.");
  return 0;
}

auto Context::is_vao(unsigned int id) -> bool {
  LOG_WARNING("Not implemented.");
  return true;
}
