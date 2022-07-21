#pragma once
#include "VulkanIncludes.h"
namespace SeaTone {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR            capabilities;
        std::vector<VkSurfaceFormatKHR>     formats;
        std::vector<VkPresentModeKHR>       presentModes;
    };

    //struct graphicsPipelineDetails
    //{
    //    VkRenderPass                    renderPass;
    //    VkPipelineLayout                pipelineLayout;
    //    VkPipeline						graphicsPipeline;
    //};

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
}