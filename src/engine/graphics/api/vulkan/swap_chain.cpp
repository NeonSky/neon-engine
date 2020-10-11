#include "swap_chain.hpp"

#include "../../../debug/logger.hpp"

using namespace engine::graphics::api::vulkan;

SwapChain::SwapChain(PhysicalDevice& physical_device, VkDevice& device, Surface& surface, VkExtent2D target_extent) : _device(device) {
  SwapChainSupportDetails swap_chain_support = physical_device.query_swap_chain_support(surface.surface());

  VkSurfaceFormatKHR surface_format = choose_swap_surface_format(swap_chain_support.formats);
  _image_format                     = surface_format.format;
  VkPresentModeKHR presentMode      = choose_swap_present_mode(swap_chain_support.presentModes);
  _extent                           = choose_swap_extent(swap_chain_support.capabilities, target_extent);

  uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;
  if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount) {
    image_count = swap_chain_support.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR create_info{};
  create_info.sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface = surface.surface();

  create_info.minImageCount    = image_count;
  create_info.imageFormat      = surface_format.format;
  create_info.imageColorSpace  = surface_format.colorSpace;
  create_info.imageExtent      = _extent;
  create_info.imageArrayLayers = 1; // the amount of layers each image consists of
  create_info.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  QueueFamilyIndices indices    = physical_device.find_queue_families(surface.surface());
  uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

  if (indices.graphicsFamily != indices.presentFamily) {
    create_info.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices   = queueFamilyIndices;
  } else {
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  }

  create_info.preTransform   = swap_chain_support.capabilities.currentTransform;
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  create_info.presentMode    = presentMode;
  create_info.clipped        = VK_TRUE;

  if (vkCreateSwapchainKHR(device, &create_info, nullptr, &_chain) != VK_SUCCESS)
    LOG_ERROR("Failed to create swap chain.");

  vkGetSwapchainImagesKHR(device, _chain, &image_count, nullptr);
  _images.resize(image_count);
  vkGetSwapchainImagesKHR(device, _chain, &image_count, _images.data());
}

void SwapChain::test1() {
  for (auto framebuffer : _framebuffers)
    vkDestroyFramebuffer(_device, framebuffer, nullptr);
}

void SwapChain::test2() {
  for (auto imageView : _image_views)
    vkDestroyImageView(_device, imageView, nullptr);

  vkDestroySwapchainKHR(_device, _chain, nullptr);
}

SwapChain::~SwapChain() {
  // LOG_DEBUG("Destroying swap chain...");
  // // vkDestroyImageView(_device, depthImageView, nullptr);
  // // vkDestroyImage(_device, depthImage, nullptr);
  // // vkFreeMemory(_device, depthImageMemory, nullptr);

  // for (auto framebuffer : _framebuffers)
  //   vkDestroyFramebuffer(_device, framebuffer, nullptr);

  // // vkFreeCommandBuffers(_device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

  // // vkDestroyPipeline(_device, graphicsPipeline, nullptr);
  // // vkDestroyPipelineLayout(_device, pipelineLayout, nullptr);
  // // vkDestroyRenderPass(_device, renderPass, nullptr);

  // for (auto imageView : _image_views)
  //   vkDestroyImageView(_device, imageView, nullptr);

  // vkDestroySwapchainKHR(_device, _chain, nullptr);

  // LOG_DEBUG("Swap chain destroyed");
  // // for (size_t i = 0; i < _images.size(); i++) {
  // //   vkDestroyBuffer(_device, uniformBuffers[i], nullptr);
  // //   vkFreeMemory(_device, uniformBuffersMemory[i], nullptr);
  // // }

  // // vkDestroyDescriptorPool(_device, descriptorPool, nullptr);
}

// void SwapChain::resize_image_count(VkDevice& device, uint32_t image_count) {
//   vkGetSwapchainImagesKHR(device, _chain, &image_count, nullptr);
//   _images.resize(image_count);
//   vkGetSwapchainImagesKHR(device, _chain, &image_count, _images.data());
// }

void SwapChain::update_image_views() {
  _image_views.resize(_images.size());

  for (uint32_t i = 0; i < _images.size(); i++)
    _image_views[i] = createImageView(_images[i], _image_format, VK_IMAGE_ASPECT_COLOR_BIT);
}

VkImageView SwapChain::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) {
  VkImageViewCreateInfo view_info{};
  view_info.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view_info.image                           = image;
  view_info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
  view_info.format                          = format;
  view_info.subresourceRange.aspectMask     = aspectFlags;
  view_info.subresourceRange.baseMipLevel   = 0;
  view_info.subresourceRange.levelCount     = 1;
  view_info.subresourceRange.baseArrayLayer = 0;
  view_info.subresourceRange.layerCount     = 1;

  VkImageView image_view;
  if (vkCreateImageView(_device, &view_info, nullptr, &image_view) != VK_SUCCESS)
    LOG_ERROR("Failed to create image view.");

  return image_view;
}

auto SwapChain::image_views() -> std::vector<VkImageView>& {
  return _image_views;
}

auto SwapChain::framebuffers() -> std::vector<VkFramebuffer>& {
  return _framebuffers;
}

auto SwapChain::chain() -> VkSwapchainKHR& {
  return _chain;
}

auto SwapChain::size() -> unsigned int {
  return _images.size();
}

auto SwapChain::image_format() -> VkFormat {
  return _image_format;
}

auto SwapChain::image_extent() -> VkExtent2D {
  return _extent;
}

VkSurfaceFormatKHR SwapChain::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
  for (const auto& availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

VkPresentModeKHR SwapChain::choose_swap_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
  for (const auto& availablePresentMode : availablePresentModes) {
    if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return availablePresentMode;
    }
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D target_extent) {
  if (capabilities.currentExtent.width != UINT32_MAX) {
    return capabilities.currentExtent;
  } else {
    target_extent.width  = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, target_extent.width));
    target_extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, target_extent.height));

    return target_extent;
  }
}
