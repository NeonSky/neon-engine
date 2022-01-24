#pragma once

#include "../context.hpp"

#include "surface.hpp"
#include "swap_chain.hpp"

#include <vulkan/vulkan.h>

#include <experimental/memory>
#include <memory>

namespace engine::graphics::api::vulkan {

  class Context : public IContext {
  public:
    Context(VkInstance& instance, VkSurfaceKHR surface);
    ~Context();

    auto gen_vao() -> unsigned int override;
    auto vao(unsigned int id) -> unsigned int override;
    auto is_vao(unsigned int id) -> bool override;

  private:
    VkInstance& _instance;
    VkSurfaceKHR _surface;

    // VkDevice& _device;

    // std::vector<std::experimental::observer_ptr<os::IWindow>> _windows;
    // std::unique_ptr<Surface> _surface;
    // std::unique_ptr<SwapChain> _swap_chain;

    // VkRenderPass _renderPass;
    // VkDescriptorSetLayout _descriptorSetLayout;
    // VkPipelineLayout _pipelineLayout;
    // VkPipeline _graphicsPipeline;

    // VkCommandPool _commandPool;

    // VkImage _depthImage;
    // VkDeviceMemory _depthImageMemory;
    // VkImageView _depthImageView;

    // VkImage _textureImage;
    // VkDeviceMemory _textureImageMemory;
    // VkImageView _textureImageView;
    // VkSampler _textureSampler;

    // std::vector<VkBuffer> _uniformBuffers;
    // std::vector<VkDeviceMemory> _uniformBuffersMemory;

    // VkDescriptorPool _descriptorPool;
    // std::vector<VkDescriptorSet> _descriptorSets;

    // std::vector<VkCommandBuffer> _commandBuffers;

    // std::vector<VkSemaphore> _imageAvailableSemaphores;
    // std::vector<VkSemaphore> _renderFinishedSemaphores;
    // std::vector<VkFence> _inFlightFences;
    // std::vector<VkFence> _imagesInFlight;
  };

}
