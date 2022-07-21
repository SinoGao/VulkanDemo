#pragma once
#include "VulkanIncludes.h"
#include "VulkanTypes.h"
namespace SeaTone {
	namespace utils {
		// 创建Instance实例，所有操作都在实例下进行
		VkInstance createInstance(bool enableValidationLayers);

		void DestoryInstance(VkInstance instance);

		bool checkValidationLayerSupport();

		std::vector<const char*> getRequiredExtensions(bool enableValidationLayers);

		VkPhysicalDevice pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

		std::tuple<VkPipelineLayout, VkPipeline> createGraphicsPipeline(VkDevice device, VkRenderPass renderPass, const std::string& vertfilename, const std::string& fragfilename);
	}









	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

	void createRenderPass(VkDevice device, VkFormat swapChainImageFormat, VkRenderPass* renderPass);


}