#pragma once
#include "VulkanIncludes.h"
namespace SeaTone {
	class VulkanSwapChain {
	private:
		GLFWwindow*					window			=	nullptr;
		VkInstance					instance		=	VK_NULL_HANDLE;
		VkDevice					device			=	VK_NULL_HANDLE;
		VkPhysicalDevice			physicalDevice	=	VK_NULL_HANDLE;
		VkSurfaceKHR				surface			=	nullptr;
		
	public:
		VkSwapchainKHR				swapChain		=	VK_NULL_HANDLE;
		std::vector<VkImage>		swapChainImages;
		VkFormat					swapChainImageFormat;
		VkExtent2D					swapChainExtent;
		std::vector<VkImageView>	swapChainImageViews;
		std::vector<VkFramebuffer>	swapChainFramebuffers;
	public:
		VulkanSwapChain(GLFWwindow* window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
		~VulkanSwapChain();

		void destroySwapChain();

		bool create();
		void createImageViews();
		void createFramebuffers(VkRenderPass renderPass);
	private:
	};
}