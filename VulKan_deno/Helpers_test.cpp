//#include <vulkan/vulkan.hpp>
#include <stdlib.h>
#include <iostream>
#include "../Helpers/VulkanBase.h"
int main() {
	//std::cout << "Hell world" << std::endl;
	SeaTone::VulkanBase app(true);
	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}