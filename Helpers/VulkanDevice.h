#pragma once
#include "VulkanIncludes.h"
namespace SeaTone {
	struct VulkanDevice {
		// 外部传入
		VkInstance								instance;
		VkPhysicalDevice						physicalDevice;
		VkSurfaceKHR							surface;

		VkDevice								logicalDevice;
		VkPhysicalDeviceProperties				properties;
		VkPhysicalDeviceFeatures				features;
		VkPhysicalDeviceFeatures				enabledFeatures;
		VkPhysicalDeviceMemoryProperties		memoryProperties;
		std::vector<VkQueueFamilyProperties>	queueFamilyProperties;
		std::vector<std::string>				supportedExtensions;

		VkCommandPool							commandPool					= VK_NULL_HANDLE;
		VkCommandBuffer							commandBuffer				= VK_NULL_HANDLE;
		bool									enableDebugMarkers			= false;

		struct
		{
			uint32_t graphics;
			uint32_t compute;
			uint32_t transfer;
			uint32_t present;
		} queueFamilyIndices;
		operator VkDevice() const
		{
			return logicalDevice;
		};

		explicit VulkanDevice(VkInstance instance, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
		~VulkanDevice();

		void destroyDevice();

		uint32_t        getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32* memTypeFound = nullptr) const;
		uint32_t        getQueueFamilyIndex(VkQueueFlagBits queueFlags) const;
		VkResult        createLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures, std::vector<const char*> enabledExtensions, void* pNextChain, bool useSwapChain = true, VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
		VkCommandPool   createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		VkCommandBuffer	createCommandBuffer();
		bool            extensionSupported(std::string extension);
	};
}