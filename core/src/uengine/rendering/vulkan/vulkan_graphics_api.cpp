#include "vulkan_graphics_api.h"

#include "uengine/core/assertion.h"

#include <GLFW/glfw3.h>

namespace ue 
{
	vulkan_graphics_api::~vulkan_graphics_api()
	{
		vkDestroyInstance(_instance, nullptr);
	}

	void vulkan_graphics_api::init()
	{
		VkApplicationInfo app_info;
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		
		VkInstanceCreateInfo create_info;
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		unsigned int extension_count = 0;
		const char** extensions;

		extensions = glfwGetRequiredInstanceExtensions(&extension_count);

		create_info.enabledExtensionCount = extension_count;
		create_info.ppEnabledExtensionNames = extensions;
		create_info.enabledLayerCount = 0;

		if (vkCreateInstance(&create_info, nullptr, &_instance) != VK_SUCCESS) 
		{
			UE_CORE_ASSERT(false, "Failed to initialize Vulkan.");
		}

		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
		std::vector<VkExtensionProperties> extension_properties(extension_count);
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extension_properties.data());

		UE_CORE_INFO("Vulkan extensions:");
		for (auto extension : extension_properties)
			UE_CORE_INFO("\t{0}", extension.extensionName);
	}
}