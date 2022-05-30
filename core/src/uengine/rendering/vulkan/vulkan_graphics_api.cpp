#include "vulkan_graphics_api.h"

#include "uengine/core/assertion.h"

#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

#include <map>
#include <vector>
#include <optional>

namespace ue 
{
#pragma region Debug

#ifdef UE_DEBUG

	static VkDebugUtilsMessengerEXT _messenger;

	static std::vector<const char*> _layers = 
	{
		"VK_LAYER_KHRONOS_validation"
	};

	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
		VkDebugUtilsMessageTypeFlagsEXT message_type,
		const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
		void* user_data) 
	{

		switch (message_severity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			UE_CORE_TRACE(callback_data->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			UE_CORE_INFO(callback_data->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			UE_CORE_WARNING(callback_data->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			UE_CORE_ERROR(callback_data->pMessage);
			break;
		}

		return VK_FALSE;
	}

	static VkResult create_debug_utils_messeger_ext(
		VkInstance instance, 
		const VkDebugUtilsMessengerCreateInfoEXT* create_info, 
		const VkAllocationCallbacks* allocator, 
		VkDebugUtilsMessengerEXT* debug_messenger) 
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr)
			return func(instance, create_info, allocator, debug_messenger);
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	static void destroy_debug_utils_messenger_ext(
		VkInstance instance, 
		VkDebugUtilsMessengerEXT debug_messenger, 
		const VkAllocationCallbacks* allocator) 
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr)
			func(instance, debug_messenger, allocator);
	}

#endif // UE_DEBUG

#pragma endregion

	struct queue_family_infices 
	{
		std::optional<unsigned int> graphics_family;
	};

	static queue_family_infices get_queue_families(const VkPhysicalDevice& physical_device) 
	{
		queue_family_infices indices;

		unsigned int queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
		std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

		unsigned int i = 0;
		for (const auto& queue_family : queue_families) 
		{
			if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphics_family = i;
				break;
			}

			i++;
		}

		return indices;
	}

	static int rate_device_suitability(const VkPhysicalDevice& physical_device)
	{
		if (!get_queue_families(physical_device).graphics_family.has_value())
			return 0;

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(physical_device, &features);

		if (!features.geometryShader)
			return 0;

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(physical_device, &properties);

		int score = 0;

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 100;

		score += properties.limits.maxImageDimension2D;

		return score;
	}

	static VkInstance _instance;
	static VkPhysicalDevice _physical_device;
	static VkDevice _device;
	static VkQueue _graphics_queue;

	static bool vulkan_initialized = false;

	void vulkan_graphics_api::init()
	{
		if (vulkan_initialized)
			return;

#ifdef UE_DEBUG

		// Validation layers support.
		unsigned int layer_count = 0;
		vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
		std::vector<VkLayerProperties> avaible_layers(layer_count);
		vkEnumerateInstanceLayerProperties(&layer_count, avaible_layers.data());
		bool layers_avaible = true;
		for (const char* layer_name : _layers)
		{
			bool layer_found = false;

			for (const auto& layer_properties : avaible_layers)
			{
				if (!strcmp(layer_name, layer_properties.layerName))
				{
					layer_found = true;
					break;
				}
			}

			if (!layer_found)
				layers_avaible = false;
		}
		UE_CORE_ASSERT(layers_avaible, "Not all layers avaible.");

#endif // UE_DEBUG

		// Info.
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		
		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;
#ifdef UE_DEBUG
		create_info.enabledLayerCount = static_cast<uint32_t>(_layers.size());
		create_info.ppEnabledLayerNames = _layers.data();
#else
		create_info.enabledLayerCount = 0;
#endif // UE_DEBUG

		// Extensions.
		unsigned int extension_count = 0;
		const char** required_extensions = glfwGetRequiredInstanceExtensions(&extension_count);
		std::vector<const char*> extensions(required_extensions, required_extensions + extension_count);
#ifdef UE_DEBUG
		extensions.push_back("VK_EXT_debug_utils");
#endif // UE_DEBUG

		create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		create_info.ppEnabledExtensionNames = extensions.data();

		// Instance.
		if (vkCreateInstance(&create_info, nullptr, &_instance) != VK_SUCCESS)
			UE_CORE_ASSERT(false, "Failed to initialize Vulkan.");

		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
		std::vector<VkExtensionProperties> extension_properties(extension_count);
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extension_properties.data());

		UE_CORE_INFO("Vulkan extensions:");
		for (auto extension : extension_properties)
			UE_CORE_INFO("\t{0}", extension.extensionName);

#ifdef UE_DEBUG

		// Debug messenger.
		VkDebugUtilsMessengerCreateInfoEXT messenger_create_info{};
		messenger_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		messenger_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		messenger_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT 
			| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT 
			| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		messenger_create_info.pfnUserCallback = debug_callback;

		if (create_debug_utils_messeger_ext(_instance, &messenger_create_info, nullptr, &_messenger) != VK_SUCCESS)
			UE_CORE_ASSERT(false, "Failed to set up vulkan debug messenger.");

#endif // UE_DEBUG

		// Physical devise.
		unsigned int device_count = 0;
		vkEnumeratePhysicalDevices(_instance, &device_count, nullptr);
		UE_CORE_ASSERT(device_count != 0, "Failed to find Vulkan compatible devices.");
		std::vector<VkPhysicalDevice> devices(device_count);
		vkEnumeratePhysicalDevices(_instance, &device_count, devices.data());

		std::multimap<int, VkPhysicalDevice> rating;
		for (const auto& device : devices) 
		{
			int score = rate_device_suitability(device);
			rating.insert(std::make_pair(score, device));
		}
		if (rating.rbegin()->first > 0)
			_physical_device = rating.rbegin()->second;
		else
			UE_CORE_ASSERT(_physical_device != nullptr, "Failed to find Vulkan suitable device.");

		// Logical device.
		queue_family_infices indices = get_queue_families(_physical_device);
		VkDeviceQueueCreateInfo queue_create_info{};
		queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueFamilyIndex = indices.graphics_family.value();
		queue_create_info.queueCount = 1;
		float queue_priority = 1.0f;
		queue_create_info.pQueuePriorities = &queue_priority;

		VkPhysicalDeviceFeatures device_features{};
		VkDeviceCreateInfo device_create_info{};
		device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_info.pQueueCreateInfos = &queue_create_info;
		device_create_info.queueCreateInfoCount = 1;
		device_create_info.pEnabledFeatures = &device_features;
		device_create_info.enabledExtensionCount = 0;
#ifdef UE_DEBUG
		device_create_info.enabledLayerCount = static_cast<uint32_t>(_layers.size());
		device_create_info.ppEnabledLayerNames = _layers.data();
#else
		device_create_info.enabledLayerCount = 0;
#endif // UE_DEBUG
		if (vkCreateDevice(_physical_device, &device_create_info, nullptr, &_device) != VK_SUCCESS)
			UE_CORE_ASSERT(false, "Failed to create logical device.");

		vkGetDeviceQueue(_device, indices.graphics_family.value(), 0, &_graphics_queue);

		vulkan_initialized = true;
	}

	void vulkan_graphics_api::terminate()
	{
		if (!vulkan_initialized)
			return;

#ifdef UE_DEBUG
		destroy_debug_utils_messenger_ext(_instance, _messenger, nullptr);
#endif // UE_DEBUG
		vkDestroyDevice(_device, nullptr);
		vkDestroyInstance(_instance, nullptr);
	}
}