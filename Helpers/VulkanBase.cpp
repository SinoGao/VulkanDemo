#include "VulkanBase.h"
#include "VulkanDebug.h"
#include "VulkanTypes.h"
#include "VulkanUtils.h"

namespace SeaTone {
	VulkanBase::VulkanBase(bool enableValidation) : m_window(nullptr),
		m_enableValidationLayers(enableValidation),
		m_instance(nullptr),
		m_debugMessenger(nullptr),
		m_surface(nullptr)
	{
	}

	VulkanBase::~VulkanBase()
	{
	}
	
	void VulkanBase::clearup()
	{
		vkDestroySemaphore(m_device, m_renderFinishedSemaphore, nullptr);
		vkDestroySemaphore(m_device, m_imageAvailableSemaphore, nullptr);
		vkDestroyFence(m_device, m_inFlightFence, nullptr);

		//
		if (m_graphicsPipeline) {
			vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);
		}
		if (m_pipelineLayout) {
			vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
		}
		if (m_renderPass) {
			vkDestroyRenderPass(m_device, m_renderPass, nullptr);
		}
		
		m_vulkanSwapChain->destroySwapChain();

		m_vulkanDevice->destroyDevice();

		if (m_enableValidationLayers) {
			freeDebugCallback(m_instance, m_debugMessenger);
		}

		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);

		utils::DestoryInstance(m_instance);

		glfwDestroyWindow(m_window);

		glfwTerminate();
	}
	
	void VulkanBase::run()
	{
		// 创建窗口，初始化
		initWindow();

		// 初始化vulkan
		initVulkan();

		// 消息循环
		renderLoop();
		
		// 释放工作
		clearup();
	}

	void VulkanBase::renderLoop()
	{
		while (!glfwWindowShouldClose(m_window)) {
			glfwPollEvents();
			drawFrame();
		}
		vkDeviceWaitIdle(m_device);
	}

	bool VulkanBase::initVulkan()
	{
		// 1.
		createInstance();

		if (m_debugMessenger) {
			setupDebugMessenger();
		}

		createSurface();
		pickPhysicalDevice();
		createLogicalDevice();
		createSwapChain();
		createImageViews();
		createRenderPass(m_device, m_swapChainImageFormat, &m_renderPass);

		//
		createGraphicsPipeline();

		createFramebuffers();

		createCommandPool();
		createCommandBuffer();
		createSyncObjects();
		return true;
	}

	bool VulkanBase::initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow(WIDTH, HEIGHT, "Seatone Vulkan", nullptr, nullptr);
		assert(m_window != NULL);
		return (m_window != NULL);
	}

	bool VulkanBase::createInstance()
	{
		m_instance = utils::createInstance(m_enableValidationLayers);
		return (m_instance != VK_NULL_HANDLE);
	}

	void VulkanBase::setupDebugMessenger()
	{
		VkDebugReportFlagsEXT debugReportFlags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		m_debugMessenger = setupDebugging(m_instance, debugReportFlags, VK_NULL_HANDLE);
	}

	void VulkanBase::createSurface()
	{
		if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	void VulkanBase::pickPhysicalDevice()
	{
		m_physicalDevice = utils::pickPhysicalDevice(m_instance, m_surface);
	}

	void VulkanBase::createLogicalDevice()
	{
		m_vulkanDevice = new VulkanDevice(m_instance, m_physicalDevice, m_surface);

		VkPhysicalDeviceFeatures enabledFeatures{};
		VkResult res = m_vulkanDevice->createLogicalDevice(enabledFeatures, deviceExtensions, nullptr);
		if (res != VK_SUCCESS) {
			assert(false);
		}

		// TODO：是否需要迁移？ 
		m_device = m_vulkanDevice->logicalDevice;
		m_vulkanDevice->queueFamilyIndices.graphics;
		vkGetDeviceQueue(m_device, m_vulkanDevice->queueFamilyIndices.graphics, 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, m_vulkanDevice->queueFamilyIndices.present, 0, &m_presentQueue);
	}

	void VulkanBase::createSwapChain()
	{
		m_vulkanSwapChain = new VulkanSwapChain(m_window, m_instance, m_device, m_physicalDevice, m_surface);
		m_vulkanSwapChain->create();

		m_swapChain = m_vulkanSwapChain->swapChain;
		// TODO:更换用法
		m_swapChainImages = m_vulkanSwapChain->swapChainImages;
		m_swapChainImageFormat = m_vulkanSwapChain->swapChainImageFormat;
		m_swapChainExtent = m_vulkanSwapChain->swapChainExtent;
	}

	void VulkanBase::createImageViews()
	{
		m_vulkanSwapChain->createImageViews();
		m_swapChainImageViews = m_vulkanSwapChain->swapChainImageViews;
	}

	void VulkanBase::createFramebuffers() {
		m_vulkanSwapChain->createFramebuffers(m_renderPass);
		m_swapChainFramebuffers = m_vulkanSwapChain->swapChainFramebuffers;
	}

	void VulkanBase::createCommandPool()
	{
		// vulkan已经闯将cmd pool，直接使用
		m_commandPool = m_vulkanDevice->commandPool;
	}

	void VulkanBase::createCommandBuffer() {
		m_commandBuffer = m_vulkanDevice->commandBuffer;
	}

	void VulkanBase::createGraphicsPipeline()
	{
		auto [pipelineLayout, graphicsPipeline] = utils::createGraphicsPipeline(m_device, m_renderPass, "shaders/15_vert.spv", "shaders/15_frag.spv");
		m_pipelineLayout = pipelineLayout;
		m_graphicsPipeline = graphicsPipeline;
	}

	void VulkanBase::createSyncObjects()
	{
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		if (vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS ||
			vkCreateFence(m_device, &fenceInfo, nullptr, &m_inFlightFence) != VK_SUCCESS) {
			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}

	void VulkanBase::drawFrame()
	{
		vkWaitForFences(m_device, 1, &m_inFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(m_device, 1, &m_inFlightFence);

		uint32_t imageIndex;
		vkAcquireNextImageKHR(m_device, m_swapChain, UINT64_MAX, m_imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

		vkResetCommandBuffer(m_commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
		recordCommandBuffer(m_commandBuffer, imageIndex);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphore };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffer;

		VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphore };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_inFlightFence) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { m_swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		vkQueuePresentKHR(m_presentQueue, &presentInfo);
	}
	void VulkanBase::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_renderPass;
		renderPassInfo.framebuffer = m_swapChainFramebuffers[imageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_swapChainExtent;

		VkClearValue clearColor = { {{1.0f, 1.0f, 1.0f, 1.0f}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)m_swapChainExtent.width;
		viewport.height = (float)m_swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = m_swapChainExtent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		vkCmdDraw(commandBuffer, 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}