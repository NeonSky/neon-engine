#pragma once

#include "buffer.hpp"
#include "debug_messenger.hpp"
#include "index_buffer.hpp"
#include "obj_model.hpp"
#include "physical_device.hpp"
#include "queue.hpp"
#include "surface.hpp"
#include "vertex_buffer.hpp"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace engine::graphics::api::vulkan {

  class Application {
  public:
    void run();

  private:
    std::unique_ptr<PhysicalDevice> _physical_device;
    std::unique_ptr<DebugMessenger> _debug_messenger;
    std::unique_ptr<OBJModel> _viking_room;
    std::unique_ptr<VertexBuffer> _vertex_buffer;
    std::unique_ptr<IndexBuffer> _index_buffer;
    std::unique_ptr<Queue> _graphics_queue;
    std::unique_ptr<Surface> _surface;
    std::unique_ptr<Surface> _surface2;

    GLFWwindow* window;
    GLFWwindow* window2;

    VkInstance instance;

    VkDevice device;

    // VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkSwapchainKHR swapChain2;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    bool framebufferResized  = false;
    bool framebufferResized2 = false;

    void initWindow();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void framebufferResizeCallback2(GLFWwindow* window, int width, int height);
    void swap_windows();

    void initVulkan();
    void mainLoop();

    void cleanupSwapChain();

    void cleanup();

    void recreateSwapChain();

    void createInstance();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    void setupDebugMessenger();

    void createSurface();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createSwapChain();

    void createImageViews();

    void createRenderPass();

    void createDescriptorSetLayout();

    void createGraphicsPipeline();

    void createFramebuffers();

    void createCommandPool();

    void createDepthResources();

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    VkFormat findDepthFormat();

    bool hasStencilComponent(VkFormat format);

    void createTextureImage();

    void createTextureImageView();

    void createTextureSampler();

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    void loadModel();

    void createVertexBuffer();

    void createIndexBuffer();

    void createUniformBuffers();

    void createDescriptorPool();

    void createDescriptorSets();

    // void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

    VkCommandBuffer beginSingleTimeCommands();

    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createCommandBuffers();

    void createSyncObjects();

    void updateUniformBuffer(uint32_t currentImage);

    void drawFrame();

    VkShaderModule createShaderModule(const std::vector<char>& code);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    std::vector<const char*> getRequiredExtensions();

    bool checkValidationLayerSupport();

    static std::vector<char> readFile(const std::string& filename);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
  };

}
