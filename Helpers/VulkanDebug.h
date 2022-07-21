#pragma once
#include "VulkanIncludes.h"
namespace SeaTone {
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	VkDebugUtilsMessengerEXT setupDebugging(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportCallbackEXT callBack);
	void freeDebugCallback(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger);
}