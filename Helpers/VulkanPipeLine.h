#pragma once
#include "VulkanIncludes.h"
#include "VulkanTypes.h"
namespace SeaTone {
	class VulkanPipeLine {
	public:
		VkPhysicalDevice                            physicalDevice		=	VK_NULL_HANDLE;
		VkDevice									logicalDevice		=	VK_NULL_HANDLE;
		VkCommandPool								commandPool			=	nullptr;
		VkQueue                                     graphicsQueue		=	VK_NULL_HANDLE;

	public:
		VkBuffer									vertexBuffer		=	nullptr;
		VkDeviceMemory								vertexBufferMemory	=	nullptr;
		VkBuffer									indexBuffer			=	nullptr;
		VkDeviceMemory								indexBufferMemory	=	nullptr;

	public:
		VulkanPipeLine(std::tuple<VkPhysicalDevice, VkDevice, VkCommandPool, VkQueue> param);
		~VulkanPipeLine();

		void Destory();

		void createVertexBuffer(const std::vector<VulkanVertex> verts);
		void createIndexBuffer(const std::vector<uint16_t> indices);
	private:
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}