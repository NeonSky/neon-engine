#pragma once

#include "physical_device.hpp"
#include "surface.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace engine::graphics::api::vulkan {

  class SwapChain {
  public:
    SwapChain(PhysicalDevice& physical_device, VkDevice& device, Surface& surface, VkExtent2D target_extent);
    ~SwapChain();

    // void resize_image_count(VkDevice& device, uint32_t image_count);
    void update_image_views();

    void test1();
    void test2();

    auto image_views() -> std::vector<VkImageView>&;
    auto framebuffers() -> std::vector<VkFramebuffer>&;

    auto chain() -> VkSwapchainKHR&; // Remove

    auto size() -> unsigned int;
    auto image_format() -> VkFormat;
    auto image_extent() -> VkExtent2D;

  private:
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D target_extent);

    VkDevice& _device;

    VkSwapchainKHR _chain;
    std::vector<VkImage> _images;
    VkFormat _image_format;
    VkExtent2D _extent; // resolution of the swap chain images

    std::vector<VkImageView> _image_views;
    std::vector<VkFramebuffer> _framebuffers;
  };

}
