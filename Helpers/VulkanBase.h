#pragma once
#include "VulkanIncludes.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

namespace SeaTone {
	const uint32_t WIDTH = 1280;
	const uint32_t HEIGHT = 720;

	//// Set to "true" to enable Vulkan's validation layers (see vulkandebug.cpp for details)
	//#define ENABLE_VALIDATION false

	//// Set to "true" to use staging buffers for uploading vertex and index data to device local memory
	//// See "prepareVertices" for details on what's staging and on why to use it
	//#define USE_STAGING true

	class VulkanBase {
	public:
		VulkanBase(bool enableValidation = false);
		virtual ~VulkanBase();

		void clearup();

		void run();

		void renderLoop();

		bool initVulkan();

		bool initWindow();
	private:
		// 1.Create a VkInstance
		bool createInstance();

		// Debug info
		void setupDebugMessenger();

		// surface
		void createSurface();

		// 2.Select a supported graphics card (VkPhysicalDevice)
		void pickPhysicalDevice();

		// 3.Create a VkDevice and VkQueue for drawing and presentation
		void createLogicalDevice();
		
		void createSwapChain();

		void createImageViews();

		void createFramebuffers();

		void createCommandPool();

		void createCommandBuffer();

		void createGraphicsPipeline();

		void createSyncObjects();

		void drawFrame();

		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	private:
		bool							m_enableValidationLayers	=	false;
		GLFWwindow*						m_window					=	nullptr;
		VkInstance						m_instance					=	VK_NULL_HANDLE;

		VkDebugUtilsMessengerEXT		m_debugMessenger			=	nullptr;
		VkSurfaceKHR					m_surface					=	nullptr;

		VkPhysicalDevice				m_physicalDevice			=	VK_NULL_HANDLE;
		VulkanDevice*					m_vulkanDevice				=	nullptr;
		VkDevice						m_device					=	nullptr;

		VkQueue							m_graphicsQueue				=	VK_NULL_HANDLE;
		VkQueue							m_presentQueue				=	VK_NULL_HANDLE;

		VulkanSwapChain*				m_vulkanSwapChain			=	nullptr;

		VkSwapchainKHR					m_swapChain					=	nullptr;
		std::vector<VkImage>			m_swapChainImages;
		VkFormat						m_swapChainImageFormat		=	VK_FORMAT_UNDEFINED;
		VkExtent2D						m_swapChainExtent;
		std::vector<VkImageView>		m_swapChainImageViews;
		std::vector<VkFramebuffer>		m_swapChainFramebuffers;

		VkRenderPass					m_renderPass;
		VkPipelineLayout				m_pipelineLayout;
		VkPipeline						m_graphicsPipeline;

		VkCommandPool					m_commandPool;
		VkCommandBuffer					m_commandBuffer;

		// 同步对象
		VkSemaphore						m_imageAvailableSemaphore;
		VkSemaphore						m_renderFinishedSemaphore;
		VkFence							m_inFlightFence;
	};
}