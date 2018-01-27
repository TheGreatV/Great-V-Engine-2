#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#include <iostream>

#define VK_USE_PLATFORM_WIN32_KHR 1

#include <../../Vulkan/Include/vulkan/vulkan.h>

void main()
{
	// shaders loader
	auto loadShaderSource = [](const String& filename)
	{
		FILE* file = nullptr;

		auto loadResult = fopen_s(&file, filename.c_str(), "rb");

		if (loadResult != 0)
		{
			throw Exception("failed to load file");
		}

		fseek(file, 0, FILE_END);

		auto size = ftell(file);

		if (size % 4 != 0)
		{
			throw Exception(); // TODO
		}

		rewind(file);

		std::vector<uint32_t> result(size);
		fread((void*)result.data(), 1, size, file);

		fclose(file);

		return Move(result);
	};

	auto instanceHandle = GetModuleHandleA(NULL);

	std::string windowClassName = "window";
	WNDCLASSA windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = windowClassName.c_str();
		windowClass.hInstance = instanceHandle;
		windowClass.lpfnWndProc = DefWindowProcA;
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if (!RegisterClassA(&windowClass))
		{
			throw Exception();
		}
	}

	auto createWindow = [&](String t, int x, int y, int w, int h)
	{
		auto style = (WS_OVERLAPPEDWINDOW | WS_VISIBLE) & ~WS_THICKFRAME;

		// ClientToScreen(handle, &p); ErrorTest();
		RECT rect;
		{
			rect.left = x;
			rect.right = x + w;
			rect.top = y;
			rect.bottom = y + h;
		}
		if (!AdjustWindowRect(&rect, style, NULL))
		{
			throw Exception();
		}

		HWND windowHandle = CreateWindowA(
			windowClassName.c_str(),
			t.c_str(), // "window",
			style,
			rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
			NULL,
			NULL,
			instanceHandle,
			NULL
			);

		if (!windowHandle)
		{
			throw Exception();
		}

		return windowHandle;
	};
	auto getDeviceContext = [&](HWND windowHandle)
	{
		auto deviceContextHandle = GetDC(windowHandle);

		if (!deviceContextHandle)
		{
			throw Exception();
		}

		PIXELFORMATDESCRIPTOR pixelFormatDescriptorInfo;
		{
			memset(&pixelFormatDescriptorInfo, 0, sizeof(pixelFormatDescriptorInfo));

			pixelFormatDescriptorInfo.nSize = sizeof(pixelFormatDescriptorInfo);
			pixelFormatDescriptorInfo.nVersion = 1;
			pixelFormatDescriptorInfo.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pixelFormatDescriptorInfo.iPixelType = PFD_TYPE_RGBA;
			pixelFormatDescriptorInfo.cColorBits = 32;
			pixelFormatDescriptorInfo.cDepthBits = 32;
			pixelFormatDescriptorInfo.cStencilBits = 0;

			auto pixelFormat = ChoosePixelFormat(deviceContextHandle, &pixelFormatDescriptorInfo);
			if (!pixelFormat)
			{
				throw Exception();
			}

			if (!SetPixelFormat(deviceContextHandle, pixelFormat, &pixelFormatDescriptorInfo))
			{
				throw Exception();
			}
		}
		
		return deviceContextHandle;
	};

	auto windowHandle = createWindow("Vulkan", 50, 50, 800, 600);
	auto deviceContextHandle = getDeviceContext(windowHandle);


	// vulkan stuff
	VkInstance vk_instance;
	{
		Size count;
		vkEnumerateInstanceLayerProperties(&count, nullptr);
		Vector<VkLayerProperties> properties(count);
		vkEnumerateInstanceLayerProperties(&count, properties.data());

		Vector<const char*> layerNames = {
			"VK_LAYER_LUNARG_api_dump",
			"VK_LAYER_LUNARG_core_validation",
			"VK_LAYER_LUNARG_device_simulation",
			"VK_LAYER_LUNARG_monitor",
			"VK_LAYER_LUNARG_object_tracker",
			"VK_LAYER_LUNARG_parameter_validation",
			"VK_LAYER_LUNARG_screenshot",
			// "VK_LAYER_LUNARG_standard_validation",
			"VK_LAYER_GOOGLE_threading",
			"VK_LAYER_GOOGLE_unique_objects",
			// "VK_LAYER_LUNARG_vktrace",
			"VK_LAYER_RENDERDOC_Capture",
		};

		Vector<const char*> extensionNames = {
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		};

		VkApplicationInfo vk_applicationInfo;
		{
			vk_applicationInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			vk_applicationInfo.pNext = nullptr;
			vk_applicationInfo.pApplicationName = "Application name";
			vk_applicationInfo.applicationVersion = 1;
			vk_applicationInfo.pEngineName = "Engine name";
			vk_applicationInfo.engineVersion = 1;
			vk_applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 65);
		}
		VkInstanceCreateInfo vk_instanceCreateInfo;
		{
			vk_instanceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			vk_instanceCreateInfo.pNext = nullptr;
			vk_instanceCreateInfo.flags = 0;
			vk_instanceCreateInfo.pApplicationInfo = &vk_applicationInfo;
			vk_instanceCreateInfo.enabledLayerCount = layerNames.size();
			vk_instanceCreateInfo.ppEnabledLayerNames = layerNames.data();
			vk_instanceCreateInfo.enabledExtensionCount = extensionNames.size();
			vk_instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();
		}

		auto result = vkCreateInstance(&vk_instanceCreateInfo, nullptr, &vk_instance);
		if (result != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create vk instance");
		}

		auto vk_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(vk_instance, "vkCreateDebugReportCallbackEXT");

		VkDebugReportCallbackEXT vk_debugReportCallbackEXT;
		{
			VkDebugReportCallbackCreateInfoEXT vk_debugReportCallbackCreateInfoEXT;
			{
				vk_debugReportCallbackCreateInfoEXT.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
				vk_debugReportCallbackCreateInfoEXT.pNext = nullptr;
				vk_debugReportCallbackCreateInfoEXT.flags =
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT |
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT |
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT;
				vk_debugReportCallbackCreateInfoEXT.pfnCallback = [](
					VkDebugReportFlagsEXT                       flags,
					VkDebugReportObjectTypeEXT                  objectType,
					uint64_t                                    object,
					size_t                                      location,
					int32_t                                     messageCode,
					const char*                                 pLayerPrefix,
					const char*                                 pMessage,
					void*                                       pUserData) -> VkBool32
				{
					std::cout << "(";
					if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0) std::cout << "INFO";
					if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0) std::cout << "WARNING";
					if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0) std::cout << "PERFORMANCE";
					if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0) std::cout << "DEBUG";
					if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0) std::cout << "ERROR";
					std::cout << ")";
					std::cout << "{" << pLayerPrefix << "} " << pMessage << std::endl;
					return VK_FALSE;
				};
				vk_debugReportCallbackCreateInfoEXT.pUserData = nullptr;
			}
			if (vk_vkCreateDebugReportCallbackEXT(vk_instance, &vk_debugReportCallbackCreateInfoEXT, nullptr, &vk_debugReportCallbackEXT) != VkResult::VK_SUCCESS)
			{
				throw Exception("failed to create debug collback");
			}
		}
	}

	VkPhysicalDevice vk_physicalDevice;
	{
		uint32_t vk_physicalDevicesCount;
		if (vkEnumeratePhysicalDevices(vk_instance, &vk_physicalDevicesCount, nullptr) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get physical devices count");
		}
		Vector<VkPhysicalDevice> vk_physicalDevices(vk_physicalDevicesCount);
		if (vkEnumeratePhysicalDevices(vk_instance, &vk_physicalDevicesCount, vk_physicalDevices.data()) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get physical devices");
		}
		if (vk_physicalDevices.empty())
		{
			throw Exception("no physical devices");
		}
		vk_physicalDevice = vk_physicalDevices[0];
	}
	Vector<VkQueueFamilyProperties> vk_physicalDeviceQueueFamilyProperties;
	{
		uint32_t vk_physicalDeviceQueueFamilyPropertiesCount;
		vkGetPhysicalDeviceQueueFamilyProperties(vk_physicalDevice, &vk_physicalDeviceQueueFamilyPropertiesCount, nullptr);

		vk_physicalDeviceQueueFamilyProperties.resize(vk_physicalDeviceQueueFamilyPropertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(vk_physicalDevice, &vk_physicalDeviceQueueFamilyPropertiesCount, vk_physicalDeviceQueueFamilyProperties.data());
	}
	VkPhysicalDeviceMemoryProperties vk_physicalDeviceMemoryProperties;
	{
		vkGetPhysicalDeviceMemoryProperties(vk_physicalDevice, &vk_physicalDeviceMemoryProperties);
	}

	VkDevice vk_device;
	{
		Vector<const char*> layerNames = {
			"VK_LAYER_LUNARG_api_dump",
			"VK_LAYER_LUNARG_screenshot",
			"VK_LAYER_RENDERDOC_Capture",
			"VK_LAYER_LUNARG_standard_validation",
		};
		Vector<const char*> extensionNames = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};

		Vector<VkDeviceQueueCreateInfo> vk_deviceQueueCreateInfos(1);
		Vector<Vector<float>> vk_deviceQueuesPriorities(vk_deviceQueueCreateInfos.size(), Vector<float>(1, 0.0f));
		{
			for (size_t i = 0; i < vk_deviceQueueCreateInfos.size(); ++i)
			{
				auto &vk_deviceQueueCreateInfo = vk_deviceQueueCreateInfos[i];
				auto &vk_deviceQueuePriorities = vk_deviceQueuesPriorities[i];

				vk_deviceQueueCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				vk_deviceQueueCreateInfo.pNext = nullptr;
				vk_deviceQueueCreateInfo.flags = 0;
				vk_deviceQueueCreateInfo.queueFamilyIndex = i;
				vk_deviceQueueCreateInfo.queueCount = vk_deviceQueuePriorities.size();
				vk_deviceQueueCreateInfo.pQueuePriorities = vk_deviceQueuePriorities.data();
			}
		}

		VkPhysicalDeviceFeatures vk_physicalDeviceFeatures;
		{
			vk_physicalDeviceFeatures.robustBufferAccess = VK_FALSE;
			vk_physicalDeviceFeatures.fullDrawIndexUint32 = VK_FALSE;
			vk_physicalDeviceFeatures.imageCubeArray = VK_FALSE;
			vk_physicalDeviceFeatures.independentBlend = VK_FALSE;
			vk_physicalDeviceFeatures.geometryShader = VK_FALSE;
			vk_physicalDeviceFeatures.tessellationShader = VK_FALSE;
			vk_physicalDeviceFeatures.sampleRateShading = VK_FALSE;
			vk_physicalDeviceFeatures.dualSrcBlend = VK_FALSE;
			vk_physicalDeviceFeatures.logicOp = VK_FALSE;
			vk_physicalDeviceFeatures.multiDrawIndirect = VK_FALSE;
			vk_physicalDeviceFeatures.drawIndirectFirstInstance = VK_FALSE;
			vk_physicalDeviceFeatures.depthClamp = VK_FALSE;
			vk_physicalDeviceFeatures.depthBiasClamp = VK_FALSE;
			vk_physicalDeviceFeatures.fillModeNonSolid = VK_FALSE;
			vk_physicalDeviceFeatures.depthBounds = VK_FALSE;
			vk_physicalDeviceFeatures.wideLines = VK_FALSE;
			vk_physicalDeviceFeatures.largePoints = VK_FALSE;
			vk_physicalDeviceFeatures.alphaToOne = VK_FALSE;
			vk_physicalDeviceFeatures.multiViewport = VK_FALSE;
			vk_physicalDeviceFeatures.samplerAnisotropy = VK_FALSE;
			vk_physicalDeviceFeatures.textureCompressionETC2 = VK_FALSE;
			vk_physicalDeviceFeatures.textureCompressionASTC_LDR = VK_FALSE;
			vk_physicalDeviceFeatures.textureCompressionBC = VK_FALSE;
			vk_physicalDeviceFeatures.occlusionQueryPrecise = VK_FALSE;
			vk_physicalDeviceFeatures.pipelineStatisticsQuery = VK_FALSE;
			vk_physicalDeviceFeatures.vertexPipelineStoresAndAtomics = VK_FALSE;
			vk_physicalDeviceFeatures.fragmentStoresAndAtomics = VK_FALSE;
			vk_physicalDeviceFeatures.shaderTessellationAndGeometryPointSize = VK_FALSE;
			vk_physicalDeviceFeatures.shaderImageGatherExtended = VK_FALSE;
			vk_physicalDeviceFeatures.shaderStorageImageExtendedFormats = VK_FALSE;
			vk_physicalDeviceFeatures.shaderStorageImageMultisample = VK_FALSE;
			vk_physicalDeviceFeatures.shaderStorageImageReadWithoutFormat = VK_FALSE;
			vk_physicalDeviceFeatures.shaderStorageImageWriteWithoutFormat = VK_FALSE;
			vk_physicalDeviceFeatures.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;
			vk_physicalDeviceFeatures.shaderSampledImageArrayDynamicIndexing = VK_FALSE;
			vk_physicalDeviceFeatures.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;
			vk_physicalDeviceFeatures.shaderStorageImageArrayDynamicIndexing = VK_FALSE;
			vk_physicalDeviceFeatures.shaderClipDistance = VK_FALSE;
			vk_physicalDeviceFeatures.shaderCullDistance = VK_FALSE;
			vk_physicalDeviceFeatures.shaderFloat64 = VK_FALSE;
			vk_physicalDeviceFeatures.shaderInt64 = VK_FALSE;
			vk_physicalDeviceFeatures.shaderInt16 = VK_FALSE;
			vk_physicalDeviceFeatures.shaderResourceResidency = VK_FALSE;
			vk_physicalDeviceFeatures.shaderResourceMinLod = VK_FALSE;
			vk_physicalDeviceFeatures.sparseBinding = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidencyBuffer = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidencyImage2D = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidencyImage3D = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidency2Samples = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidency4Samples = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidency8Samples = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidency16Samples = VK_FALSE;
			vk_physicalDeviceFeatures.sparseResidencyAliased = VK_FALSE;
			vk_physicalDeviceFeatures.variableMultisampleRate = VK_FALSE;
			vk_physicalDeviceFeatures.inheritedQueries = VK_FALSE;
		}

		VkDeviceCreateInfo vk_deviceCreateInfo;
		{
			vk_deviceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			vk_deviceCreateInfo.pNext = nullptr;
			vk_deviceCreateInfo.flags = 0;
			vk_deviceCreateInfo.queueCreateInfoCount = vk_deviceQueueCreateInfos.size();
			vk_deviceCreateInfo.pQueueCreateInfos = vk_deviceQueueCreateInfos.data();
			vk_deviceCreateInfo.enabledLayerCount = layerNames.size();
			vk_deviceCreateInfo.ppEnabledLayerNames = layerNames.data();
			vk_deviceCreateInfo.enabledExtensionCount = extensionNames.size();
			vk_deviceCreateInfo.ppEnabledExtensionNames = extensionNames.data();
			vk_deviceCreateInfo.pEnabledFeatures = &vk_physicalDeviceFeatures;
		};

		if (vkCreateDevice(vk_physicalDevice, &vk_deviceCreateInfo, nullptr, &vk_device) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create device");
		}
	}

	VkSurfaceKHR vk_surfaceKHR;
	{
		VkWin32SurfaceCreateInfoKHR vk_win32SurfaceCreateInfoKHR;
		{
			vk_win32SurfaceCreateInfoKHR.sType = VkStructureType::VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			vk_win32SurfaceCreateInfoKHR.pNext = nullptr;
			vk_win32SurfaceCreateInfoKHR.flags = 0;
			vk_win32SurfaceCreateInfoKHR.hinstance = instanceHandle;
			vk_win32SurfaceCreateInfoKHR.hwnd = windowHandle;
		}
		if (vkCreateWin32SurfaceKHR(vk_instance, &vk_win32SurfaceCreateInfoKHR, nullptr, &vk_surfaceKHR) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create surface");
		}

		VkBool32 isSupported;
		if (vkGetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, vk_surfaceKHR, &isSupported) != VkResult::VK_SUCCESS || isSupported == VK_FALSE)
		{
			throw Exception("surface not supported");
		}
	}
	Vector<VkSurfaceFormatKHR> vk_surfaceFormats;
	{
		uint32_t vk_surfaceFormatsCount;
		if (vkGetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice, vk_surfaceKHR, &vk_surfaceFormatsCount, nullptr) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get surface formats count");
		}

		vk_surfaceFormats.resize(vk_surfaceFormatsCount);
		if (vkGetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice, vk_surfaceKHR, &vk_surfaceFormatsCount, vk_surfaceFormats.data()) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get surface formats");
		}
	}
	VkSurfaceCapabilitiesKHR vk_surfaceCapabilitiesKHR;
	{
		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physicalDevice, vk_surfaceKHR, &vk_surfaceCapabilitiesKHR) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get surface capabilities");
		}
	}

	VkSwapchainKHR vk_swapchainKHR;
	{
		VkSwapchainCreateInfoKHR vk_SwapchainCreateInfoKHR;
		{
			vk_SwapchainCreateInfoKHR.sType = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			vk_SwapchainCreateInfoKHR.pNext = nullptr;
			vk_SwapchainCreateInfoKHR.flags = 0;
			vk_SwapchainCreateInfoKHR.surface = vk_surfaceKHR;
			vk_SwapchainCreateInfoKHR.minImageCount = 2;
			vk_SwapchainCreateInfoKHR.imageFormat = vk_surfaceFormats[0].format;
			vk_SwapchainCreateInfoKHR.imageColorSpace = vk_surfaceFormats[0].colorSpace;
			vk_SwapchainCreateInfoKHR.imageExtent = VkExtent2D{
				vk_surfaceCapabilitiesKHR.currentExtent.width,
				vk_surfaceCapabilitiesKHR.currentExtent.height
			};
			vk_SwapchainCreateInfoKHR.imageArrayLayers = 1;
			vk_SwapchainCreateInfoKHR.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			vk_SwapchainCreateInfoKHR.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
			vk_SwapchainCreateInfoKHR.queueFamilyIndexCount = 0;
			vk_SwapchainCreateInfoKHR.pQueueFamilyIndices = nullptr;
			vk_SwapchainCreateInfoKHR.preTransform = VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			vk_SwapchainCreateInfoKHR.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			vk_SwapchainCreateInfoKHR.presentMode = VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR;
			vk_SwapchainCreateInfoKHR.clipped = VK_TRUE;
			vk_SwapchainCreateInfoKHR.oldSwapchain = VK_NULL_HANDLE;
		}
		if (vkCreateSwapchainKHR(vk_device, &vk_SwapchainCreateInfoKHR, nullptr, &vk_swapchainKHR) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create swapchain");
		}
	}
	Vector<VkImage> vk_swapchainImages;
	{
		uint32_t vk_swapchainImagesCount;
		if (vkGetSwapchainImagesKHR(vk_device, vk_swapchainKHR, &vk_swapchainImagesCount, nullptr) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get swapchain images count");
		}

		vk_swapchainImages.resize(vk_swapchainImagesCount);
		if (vkGetSwapchainImagesKHR(vk_device, vk_swapchainKHR, &vk_swapchainImagesCount, vk_swapchainImages.data()) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to get swapchain images");
		}
	}

	VkRenderPass vk_renderPass;
	{
		VkAttachmentDescription vk_attachmentDescription;
		{
			vk_attachmentDescription.flags = 0;
			vk_attachmentDescription.format = vk_surfaceFormats[0].format;
			vk_attachmentDescription.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
			vk_attachmentDescription.loadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR;
			vk_attachmentDescription.storeOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE;
			vk_attachmentDescription.stencilLoadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			vk_attachmentDescription.stencilStoreOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
			vk_attachmentDescription.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
			vk_attachmentDescription.finalLayout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		VkAttachmentReference vk_attachmentReference;
		{
			vk_attachmentReference.attachment = 0;
			vk_attachmentReference.layout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
		VkSubpassDescription vk_subpassDescription;
		{
			vk_subpassDescription.flags = 0;
			vk_subpassDescription.pipelineBindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
			vk_subpassDescription.inputAttachmentCount = 0;
			vk_subpassDescription.pInputAttachments = nullptr;
			vk_subpassDescription.colorAttachmentCount = 1;
			vk_subpassDescription.pColorAttachments = &vk_attachmentReference;
			vk_subpassDescription.pResolveAttachments = nullptr;
			vk_subpassDescription.pDepthStencilAttachment = nullptr;
			vk_subpassDescription.preserveAttachmentCount = 0;
			vk_subpassDescription.pPreserveAttachments = nullptr;
		}

		VkRenderPassCreateInfo vk_renderPassCreateInfo;
		{
			vk_renderPassCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			vk_renderPassCreateInfo.pNext = nullptr;
			vk_renderPassCreateInfo.flags = 0;
			vk_renderPassCreateInfo.attachmentCount = 1;
			vk_renderPassCreateInfo.pAttachments = &vk_attachmentDescription;
			vk_renderPassCreateInfo.subpassCount = 1;
			vk_renderPassCreateInfo.pSubpasses = &vk_subpassDescription;
			vk_renderPassCreateInfo.dependencyCount = 0;
			vk_renderPassCreateInfo.pDependencies = nullptr;
		}

		if (vkCreateRenderPass(vk_device, &vk_renderPassCreateInfo, nullptr, &vk_renderPass) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create render pass");
		}
	}

	Vector<VkImageView> vk_imageViews(vk_swapchainImages.size());
	Vector<VkFramebuffer> vk_framebuffers(vk_swapchainImages.size());
	{
		for (uint32_t i = 0; i < vk_swapchainImages.size(); ++i)
		{
			auto &vk_imageView = vk_imageViews[i];
			{
				VkImageViewCreateInfo vk_imageViewCreateInfo;
				{
					vk_imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					vk_imageViewCreateInfo.pNext = nullptr;
					vk_imageViewCreateInfo.flags = 0;
					vk_imageViewCreateInfo.image = vk_swapchainImages[i];
					vk_imageViewCreateInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
					vk_imageViewCreateInfo.format = vk_surfaceFormats[0].format;
					vk_imageViewCreateInfo.components = {
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B,
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A
					};
					vk_imageViewCreateInfo.subresourceRange;
					{
						vk_imageViewCreateInfo.subresourceRange.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
						vk_imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
						vk_imageViewCreateInfo.subresourceRange.levelCount = 1;
						vk_imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
						vk_imageViewCreateInfo.subresourceRange.layerCount = 1;
					}
				}

				if (vkCreateImageView(vk_device, &vk_imageViewCreateInfo, nullptr, &vk_imageView) != VkResult::VK_SUCCESS)
				{
					throw Exception("failed to create image view");
				}
			}

			auto &vk_framebuffer = vk_framebuffers[i];
			{
				VkFramebufferCreateInfo vk_framebufferCreateInfo;
				{
					vk_framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
					vk_framebufferCreateInfo.pNext = nullptr;
					vk_framebufferCreateInfo.flags = 0;
					vk_framebufferCreateInfo.renderPass = vk_renderPass;
					vk_framebufferCreateInfo.attachmentCount = 1;
					vk_framebufferCreateInfo.pAttachments = &vk_imageView;
					vk_framebufferCreateInfo.width = vk_surfaceCapabilitiesKHR.currentExtent.width;
					vk_framebufferCreateInfo.height = vk_surfaceCapabilitiesKHR.currentExtent.height;
					vk_framebufferCreateInfo.layers = 1;
				}

				if (vkCreateFramebuffer(vk_device, &vk_framebufferCreateInfo, nullptr, &vk_framebuffer) != VkResult::VK_SUCCESS)
				{
					throw Exception("failed to create framebuffer");
				}
			}
		}
	}

	VkBuffer vk_buffer;
	{
		Vector<float> source = {
			-0.5f, +0.5f,
			+0.5f, +0.5f,
			+0.0f, -0.5f
		};

		VkBufferCreateInfo vk_bufferCreateInfo;
		{
			vk_bufferCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			vk_bufferCreateInfo.pNext = nullptr;
			vk_bufferCreateInfo.flags = 0;
			vk_bufferCreateInfo.size = sizeof(float)* source.size();
			vk_bufferCreateInfo.usage = VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			vk_bufferCreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
			vk_bufferCreateInfo.queueFamilyIndexCount = 0;
			vk_bufferCreateInfo.pQueueFamilyIndices = nullptr;
		}

		if (vkCreateBuffer(vk_device, &vk_bufferCreateInfo, nullptr, &vk_buffer) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create buffer");
		}

		VkDeviceMemory vk_deviceMemory;
		{
			VkMemoryRequirements vk_memoryRequirements;
			vkGetBufferMemoryRequirements(vk_device, vk_buffer, &vk_memoryRequirements);

			VkMemoryAllocateInfo vk_memoryAllocateInfo;
			{
				vk_memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				vk_memoryAllocateInfo.pNext = nullptr;
				vk_memoryAllocateInfo.allocationSize = vk_memoryRequirements.size;
				vk_memoryAllocateInfo.memoryTypeIndex = [&]()
				{
					for (size_t i = 0; i < vk_physicalDeviceMemoryProperties.memoryTypeCount; ++i)
					{
						auto bit = ((uint32_t)1 << i);
						if ((vk_memoryRequirements.memoryTypeBits & bit) != 0)
						{
							// if((vk_physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == flags)
							if ((vk_physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0)
							{
								return i;
							}
						}
					}

					throw Exception("failed to get correct memory type");
				}();
			}

			if (vkAllocateMemory(vk_device, &vk_memoryAllocateInfo, nullptr, &vk_deviceMemory) != VkResult::VK_SUCCESS)
			{
				throw Exception("failed to allocate device memory");
			}

			void* data;
			if (vkMapMemory(vk_device, vk_deviceMemory, 0, sizeof(float)* source.size(), 0, &data) != VkResult::VK_SUCCESS)
			{
				throw Exception("failed to map device memory");
			}

			memcpy(data, source.data(), sizeof(float)* source.size());

			vkUnmapMemory(vk_device, vk_deviceMemory);
		}

		if (vkBindBufferMemory(vk_device, vk_buffer, vk_deviceMemory, 0) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to bind buffer memory");
		}
	}

	VkShaderModule vk_shaderModuleVertex;
	{
		auto source = loadShaderSource("Media/Shaders/Vulkan/Example_RawVulkan/triangle.spir-v.vertex-shader");

		VkShaderModuleCreateInfo vk_shaderModuleCreateInfo;
		{
			vk_shaderModuleCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			vk_shaderModuleCreateInfo.pNext = nullptr;
			vk_shaderModuleCreateInfo.flags = 0;
			vk_shaderModuleCreateInfo.codeSize = source.size();
			vk_shaderModuleCreateInfo.pCode = source.data();
		}

		if (vkCreateShaderModule(vk_device, &vk_shaderModuleCreateInfo, nullptr, &vk_shaderModuleVertex) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create vertex shader");
		}
	}
	VkShaderModule vk_shaderModuleFragment;
	{
		auto source = loadShaderSource("Media/Shaders/Vulkan/Example_RawVulkan/triangle.spir-v.fragment-shader");

		VkShaderModuleCreateInfo vk_shaderModuleCreateInfo;
		{
			vk_shaderModuleCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			vk_shaderModuleCreateInfo.pNext = nullptr;
			vk_shaderModuleCreateInfo.flags = 0;
			vk_shaderModuleCreateInfo.codeSize = source.size();
			vk_shaderModuleCreateInfo.pCode = source.data();
		}

		if (vkCreateShaderModule(vk_device, &vk_shaderModuleCreateInfo, nullptr, &vk_shaderModuleFragment) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create vertex shader");
		}
	}

	VkPipelineLayout vk_pipelineLayout;
	{
		VkPipelineLayoutCreateInfo vk_pipelineLayoutCreateInfo;
		{
			vk_pipelineLayoutCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			vk_pipelineLayoutCreateInfo.pNext = nullptr;
			vk_pipelineLayoutCreateInfo.flags = 0;
			vk_pipelineLayoutCreateInfo.setLayoutCount = 0;
			vk_pipelineLayoutCreateInfo.pSetLayouts = nullptr;
			vk_pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
			vk_pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
		}

		if (vkCreatePipelineLayout(vk_device, &vk_pipelineLayoutCreateInfo, nullptr, &vk_pipelineLayout) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create pipelane layout");
		}
	}
	VkPipelineCache vk_PipelineCache;
	{
		VkPipelineCacheCreateInfo vk_pipelineCacheCreateInfo;
		{
			vk_pipelineCacheCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
			vk_pipelineCacheCreateInfo.pNext = nullptr;
			vk_pipelineCacheCreateInfo.flags = 0;
			vk_pipelineCacheCreateInfo.initialDataSize = 0;
			vk_pipelineCacheCreateInfo.pInitialData = nullptr;
		}

		if (vkCreatePipelineCache(vk_device, &vk_pipelineCacheCreateInfo, nullptr, &vk_PipelineCache) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create pipeline cache");
		}
	}

	VkViewport vk_viewport{
		0.0f, 0.0f,
		(float)vk_surfaceCapabilitiesKHR.currentExtent.width,
		(float)vk_surfaceCapabilitiesKHR.currentExtent.height,
		0.0f, 1.0f
	};
	VkRect2D vk_scissor{
		{0, 0},
		{vk_surfaceCapabilitiesKHR.currentExtent.width, vk_surfaceCapabilitiesKHR.currentExtent.height}
	};
	VkPipeline vk_pipeline;
	{
		Vector<VkPipelineShaderStageCreateInfo> vk_pipelineShaderStageCreateInfos(2);
		{
			vk_pipelineShaderStageCreateInfos[0].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vk_pipelineShaderStageCreateInfos[0].pNext = nullptr;
			vk_pipelineShaderStageCreateInfos[0].flags = 0;
			vk_pipelineShaderStageCreateInfos[0].stage = VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
			vk_pipelineShaderStageCreateInfos[0].module = vk_shaderModuleVertex;
			vk_pipelineShaderStageCreateInfos[0].pName = "main";
			vk_pipelineShaderStageCreateInfos[0].pSpecializationInfo = nullptr;

			vk_pipelineShaderStageCreateInfos[1].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vk_pipelineShaderStageCreateInfos[1].pNext = nullptr;
			vk_pipelineShaderStageCreateInfos[1].flags = 0;
			vk_pipelineShaderStageCreateInfos[1].stage = VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
			vk_pipelineShaderStageCreateInfos[1].module = vk_shaderModuleFragment;
			vk_pipelineShaderStageCreateInfos[1].pName = "main";
			vk_pipelineShaderStageCreateInfos[1].pSpecializationInfo = nullptr;
		}

		VkVertexInputBindingDescription vk_vertexInputBindingDescription;
		{
			vk_vertexInputBindingDescription.binding = 0;
			vk_vertexInputBindingDescription.stride = sizeof(float)* 2;
			vk_vertexInputBindingDescription.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;
		}
		VkVertexInputAttributeDescription vk_vertexInputAttributeDescription;
		{
			vk_vertexInputAttributeDescription.location = 0;
			vk_vertexInputAttributeDescription.binding = 0;
			vk_vertexInputAttributeDescription.format = VkFormat::VK_FORMAT_R32G32_SFLOAT;
			vk_vertexInputAttributeDescription.offset = 0;
		}
		VkPipelineVertexInputStateCreateInfo vk_pipelineVertexInputStateCreateInfo;
		{
			vk_pipelineVertexInputStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vk_pipelineVertexInputStateCreateInfo.pNext = nullptr;
			vk_pipelineVertexInputStateCreateInfo.flags = 0;
			vk_pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
			vk_pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &vk_vertexInputBindingDescription;
			vk_pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 1;
			vk_pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = &vk_vertexInputAttributeDescription;
		}

		VkPipelineInputAssemblyStateCreateInfo vk_pipelineInputAssemblyStateCreateInfo;
		{
			vk_pipelineInputAssemblyStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			vk_pipelineInputAssemblyStateCreateInfo.pNext = nullptr;
			vk_pipelineInputAssemblyStateCreateInfo.flags = 0;
			vk_pipelineInputAssemblyStateCreateInfo.topology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			vk_pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;
		}

		VkPipelineViewportStateCreateInfo vk_pipelineViewportStateCreateInfo;
		{
			vk_pipelineViewportStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			vk_pipelineViewportStateCreateInfo.pNext = nullptr;
			vk_pipelineViewportStateCreateInfo.flags = 0;
			vk_pipelineViewportStateCreateInfo.viewportCount = 1;
			vk_pipelineViewportStateCreateInfo.pViewports = &vk_viewport;
			vk_pipelineViewportStateCreateInfo.scissorCount = 1;
			vk_pipelineViewportStateCreateInfo.pScissors = &vk_scissor;
		}

		VkPipelineRasterizationStateCreateInfo vk_pipelineRasterizationStateCreateInfo;
		{
			vk_pipelineRasterizationStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			vk_pipelineRasterizationStateCreateInfo.pNext = nullptr;
			vk_pipelineRasterizationStateCreateInfo.flags = 0;
			vk_pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
			vk_pipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
			vk_pipelineRasterizationStateCreateInfo.polygonMode = VkPolygonMode::VK_POLYGON_MODE_FILL;
			vk_pipelineRasterizationStateCreateInfo.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
			vk_pipelineRasterizationStateCreateInfo.frontFace = VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;
			vk_pipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
			vk_pipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
			vk_pipelineRasterizationStateCreateInfo.depthBiasClamp = 0.0f;
			vk_pipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;
			vk_pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
		}

		VkPipelineMultisampleStateCreateInfo vk_pipelineMultisampleStateCreateInfo;
		{
			vk_pipelineMultisampleStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			vk_pipelineMultisampleStateCreateInfo.pNext = nullptr;
			vk_pipelineMultisampleStateCreateInfo.flags = 0;
			vk_pipelineMultisampleStateCreateInfo.rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
			vk_pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
			vk_pipelineMultisampleStateCreateInfo.minSampleShading = 0;
			vk_pipelineMultisampleStateCreateInfo.pSampleMask = nullptr;
			vk_pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
			vk_pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;
		}

		VkPipelineDepthStencilStateCreateInfo vk_pipelineDepthStencilStateCreateInfo;
		{
			vk_pipelineDepthStencilStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			vk_pipelineDepthStencilStateCreateInfo.pNext = nullptr;
			vk_pipelineDepthStencilStateCreateInfo.flags = 0;
			vk_pipelineDepthStencilStateCreateInfo.depthTestEnable = VK_FALSE;
			vk_pipelineDepthStencilStateCreateInfo.depthWriteEnable = VK_FALSE;
			vk_pipelineDepthStencilStateCreateInfo.depthCompareOp = VkCompareOp::VK_COMPARE_OP_ALWAYS;
			vk_pipelineDepthStencilStateCreateInfo.depthBoundsTestEnable = VK_FALSE;
			vk_pipelineDepthStencilStateCreateInfo.stencilTestEnable = VK_FALSE;
			vk_pipelineDepthStencilStateCreateInfo.front;
			{
				vk_pipelineDepthStencilStateCreateInfo.front.failOp = VkStencilOp::VK_STENCIL_OP_KEEP;
				vk_pipelineDepthStencilStateCreateInfo.front.passOp = VkStencilOp::VK_STENCIL_OP_KEEP;
				vk_pipelineDepthStencilStateCreateInfo.front.depthFailOp = VkStencilOp::VK_STENCIL_OP_KEEP;
				vk_pipelineDepthStencilStateCreateInfo.front.compareOp = VkCompareOp::VK_COMPARE_OP_ALWAYS;
				vk_pipelineDepthStencilStateCreateInfo.front.compareMask = 0;
				vk_pipelineDepthStencilStateCreateInfo.front.writeMask = 0;
				vk_pipelineDepthStencilStateCreateInfo.front.reference = 0;
			}
			vk_pipelineDepthStencilStateCreateInfo.back;
			{
				vk_pipelineDepthStencilStateCreateInfo.back.failOp = VkStencilOp::VK_STENCIL_OP_KEEP;
				vk_pipelineDepthStencilStateCreateInfo.back.passOp = VkStencilOp::VK_STENCIL_OP_KEEP;
				vk_pipelineDepthStencilStateCreateInfo.back.depthFailOp = VkStencilOp::VK_STENCIL_OP_KEEP;
				vk_pipelineDepthStencilStateCreateInfo.back.compareOp = VkCompareOp::VK_COMPARE_OP_ALWAYS;
				vk_pipelineDepthStencilStateCreateInfo.back.compareMask = 0;
				vk_pipelineDepthStencilStateCreateInfo.back.writeMask = 0;
				vk_pipelineDepthStencilStateCreateInfo.back.reference = 0;
			}
			vk_pipelineDepthStencilStateCreateInfo.minDepthBounds = 0.0f;
			vk_pipelineDepthStencilStateCreateInfo.maxDepthBounds = 0.0f;
		}

		VkPipelineColorBlendAttachmentState vk_pipelineColorBlendAttachmentState;
		{
			vk_pipelineColorBlendAttachmentState.blendEnable = VK_FALSE;
			vk_pipelineColorBlendAttachmentState.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
			vk_pipelineColorBlendAttachmentState.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
			vk_pipelineColorBlendAttachmentState.colorBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
			vk_pipelineColorBlendAttachmentState.srcAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
			vk_pipelineColorBlendAttachmentState.dstAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
			vk_pipelineColorBlendAttachmentState.alphaBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
			vk_pipelineColorBlendAttachmentState.colorWriteMask =
				VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT |
				VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT |
				VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT;
		}
		VkPipelineColorBlendStateCreateInfo vk_pipelineColorBlendStateCreateInfo;
		{
			vk_pipelineColorBlendStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			vk_pipelineColorBlendStateCreateInfo.pNext = nullptr;
			vk_pipelineColorBlendStateCreateInfo.flags = 0;
			vk_pipelineColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
			vk_pipelineColorBlendStateCreateInfo.logicOp = VkLogicOp::VK_LOGIC_OP_CLEAR;
			vk_pipelineColorBlendStateCreateInfo.attachmentCount = 1;
			vk_pipelineColorBlendStateCreateInfo.pAttachments = &vk_pipelineColorBlendAttachmentState;
			vk_pipelineColorBlendStateCreateInfo.blendConstants;
			{
				vk_pipelineColorBlendStateCreateInfo.blendConstants[0] = 1.0f;
				vk_pipelineColorBlendStateCreateInfo.blendConstants[1] = 1.0f;
				vk_pipelineColorBlendStateCreateInfo.blendConstants[2] = 1.0f;
				vk_pipelineColorBlendStateCreateInfo.blendConstants[3] = 1.0f;
			}
		}

		Vector<VkDynamicState> vk_dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo vk_pipelineDynamicStateCreateInfo;
		{
			vk_pipelineDynamicStateCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			vk_pipelineDynamicStateCreateInfo.pNext = nullptr;
			vk_pipelineDynamicStateCreateInfo.flags = 0;
			vk_pipelineDynamicStateCreateInfo.dynamicStateCount = vk_dynamicStates.size();
			vk_pipelineDynamicStateCreateInfo.pDynamicStates = vk_dynamicStates.data();
		}

		VkGraphicsPipelineCreateInfo vk_graphicsPipelineCreateInfo;
		{
			vk_graphicsPipelineCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			vk_graphicsPipelineCreateInfo.pNext = nullptr;
			vk_graphicsPipelineCreateInfo.flags = 0;
			vk_graphicsPipelineCreateInfo.stageCount = vk_pipelineShaderStageCreateInfos.size();
			vk_graphicsPipelineCreateInfo.pStages = vk_pipelineShaderStageCreateInfos.data();
			vk_graphicsPipelineCreateInfo.pVertexInputState = &vk_pipelineVertexInputStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pInputAssemblyState = &vk_pipelineInputAssemblyStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pTessellationState = VK_NULL_HANDLE;
			vk_graphicsPipelineCreateInfo.pViewportState = &vk_pipelineViewportStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pRasterizationState = &vk_pipelineRasterizationStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pMultisampleState = &vk_pipelineMultisampleStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pDepthStencilState = &vk_pipelineDepthStencilStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pColorBlendState = &vk_pipelineColorBlendStateCreateInfo;
			vk_graphicsPipelineCreateInfo.pDynamicState = &vk_pipelineDynamicStateCreateInfo;
			vk_graphicsPipelineCreateInfo.layout = vk_pipelineLayout;
			vk_graphicsPipelineCreateInfo.renderPass = vk_renderPass;
			vk_graphicsPipelineCreateInfo.subpass = 0;
			vk_graphicsPipelineCreateInfo.basePipelineIndex = 0;
			vk_graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		}

		if (vkCreateGraphicsPipelines(vk_device, vk_PipelineCache, 1, &vk_graphicsPipelineCreateInfo, nullptr, &vk_pipeline) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create pipeline");
		}
	}

	VkQueue vk_queue;
	{
		vkGetDeviceQueue(vk_device, 0, 0, &vk_queue);
	}
	VkCommandPool vk_commandPool;
	{
		VkCommandPoolCreateInfo vk_commandPoolCreateInfo;
		{
			vk_commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			vk_commandPoolCreateInfo.pNext = nullptr;
			vk_commandPoolCreateInfo.flags = VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			vk_commandPoolCreateInfo.queueFamilyIndex = 0;
		}

		if (vkCreateCommandPool(vk_device, &vk_commandPoolCreateInfo, nullptr, &vk_commandPool) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create command pool");
		}

		if (vkResetCommandPool(vk_device, vk_commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to reset command pool");
		}
	}
	Vector<VkCommandBuffer> vk_commandBuffers(vk_swapchainImages.size());
	{
		VkCommandBufferAllocateInfo vk_CommandBufferAllocateInfo;
		{
			vk_CommandBufferAllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			vk_CommandBufferAllocateInfo.pNext = nullptr;
			vk_CommandBufferAllocateInfo.commandPool = vk_commandPool;
			vk_CommandBufferAllocateInfo.level = VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			vk_CommandBufferAllocateInfo.commandBufferCount = vk_swapchainImages.size();
		}

		if (vkAllocateCommandBuffers(vk_device, &vk_CommandBufferAllocateInfo, vk_commandBuffers.data()) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to allocate command buffers");
		}

		for (uint32_t i = 0; i < vk_swapchainImages.size(); ++i)
		{
			auto &vk_commandBuffer = vk_commandBuffers[i];
			auto &vk_image = vk_swapchainImages[i];
			auto &vk_framebuffer = vk_framebuffers[i];

			if (vkResetCommandBuffer(vk_commandBuffer, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT) != VkResult::VK_SUCCESS)
			{
				throw Exception("failed to reset command buffer");
			}

			VkCommandBufferInheritanceInfo vk_commandBufferInheritanceInfo;
			{
				vk_commandBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
				vk_commandBufferInheritanceInfo.pNext = nullptr;
				vk_commandBufferInheritanceInfo.renderPass = vk_renderPass;
				vk_commandBufferInheritanceInfo.subpass = 0;
				vk_commandBufferInheritanceInfo.framebuffer = vk_framebuffer;
				vk_commandBufferInheritanceInfo.occlusionQueryEnable = VK_FALSE;
				vk_commandBufferInheritanceInfo.queryFlags = 0;
				vk_commandBufferInheritanceInfo.pipelineStatistics = 0;
			}
			VkCommandBufferBeginInfo vk_commandBufferBeginInfo;
			{
				vk_commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				vk_commandBufferBeginInfo.pNext = nullptr;
				vk_commandBufferBeginInfo.flags = 0;
				vk_commandBufferBeginInfo.pInheritanceInfo = &vk_commandBufferInheritanceInfo;
			}
			vkBeginCommandBuffer(vk_commandBuffer, &vk_commandBufferBeginInfo);
			{
				VkClearValue vk_clearValue;
				{
					vk_clearValue.color.float32[0] = 1.0f;
					vk_clearValue.color.float32[1] = 0.0f;
					vk_clearValue.color.float32[2] = 0.0f;
					vk_clearValue.color.float32[3] = 1.0f;
				}
				VkRenderPassBeginInfo vk_renderPassBeginInfo;
				{
					vk_renderPassBeginInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
					vk_renderPassBeginInfo.pNext = nullptr;
					vk_renderPassBeginInfo.renderPass = vk_renderPass;
					vk_renderPassBeginInfo.framebuffer = vk_framebuffers[i];
					vk_renderPassBeginInfo.renderArea = VkRect2D{
						VkOffset2D{0, 0},
						VkExtent2D{
							vk_surfaceCapabilitiesKHR.currentExtent.width,
							vk_surfaceCapabilitiesKHR.currentExtent.height
						}
					};
					vk_renderPassBeginInfo.clearValueCount = 1;
					vk_renderPassBeginInfo.pClearValues = &vk_clearValue;
				};

				vkCmdBeginRenderPass(
					vk_commandBuffer,
					&vk_renderPassBeginInfo,
					VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
					);
				{
					vkCmdBindPipeline(
						vk_commandBuffer,
						VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS,
						vk_pipeline
						);

					vkCmdSetViewport(
						vk_commandBuffer,
						0,
						1,
						&vk_viewport
						);

					vkCmdSetScissor(
						vk_commandBuffer,
						0,
						1,
						&vk_scissor
						);

					Vector<VkBuffer> vk_vertexBuffers = {vk_buffer};
					Vector<VkDeviceSize> vk_vertexOffsets = {0};
					vkCmdBindVertexBuffers(
						vk_commandBuffer,
						0,
						1,
						vk_vertexBuffers.data(),
						vk_vertexOffsets.data()
						);

					vkCmdDraw(
						vk_commandBuffer,
						3,
						1,
						0,
						0
						);
				}
				vkCmdEndRenderPass(vk_commandBuffer);

				VkImageMemoryBarrier vk_imageMemoryBarrier;
				{
					vk_imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					vk_imageMemoryBarrier.pNext = nullptr;
					vk_imageMemoryBarrier.srcAccessMask = 0;
					vk_imageMemoryBarrier.dstAccessMask =
						VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
						VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT;
					vk_imageMemoryBarrier.oldLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
					vk_imageMemoryBarrier.newLayout = VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					vk_imageMemoryBarrier.srcQueueFamilyIndex = 0;
					vk_imageMemoryBarrier.dstQueueFamilyIndex = 0;
					vk_imageMemoryBarrier.image = vk_image;
					vk_imageMemoryBarrier.subresourceRange = {VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
				}
				vkCmdPipelineBarrier(
					vk_commandBuffer,
					VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
					VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
					0,
					0, nullptr,
					0, nullptr,
					1, &vk_imageMemoryBarrier
					);
			}
			vkEndCommandBuffer(vk_commandBuffer);
		}
	}

	VkFence vk_fence;
	{
		VkFenceCreateInfo vk_fenceCreateInfo;
		{
			vk_fenceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			vk_fenceCreateInfo.pNext = nullptr;
			vk_fenceCreateInfo.flags = 0;
		}

		if (vkCreateFence(vk_device, &vk_fenceCreateInfo, nullptr, &vk_fence) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to create fence");
		}
	}

	// main loop
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while (PeekMessageA(&msg, windowHandle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		uint32_t vk_swapchainImage;
		{
			if (vkAcquireNextImageKHR(vk_device, vk_swapchainKHR, UINT64_MAX, VK_NULL_HANDLE, vk_fence, &vk_swapchainImage) != VkResult::VK_SUCCESS)
			{
				throw Exception("failed to get next swapchain image");
			}
		}

		if (vkWaitForFences(vk_device, 1, &vk_fence, VK_TRUE, UINT64_MAX) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to wait for fence");
		}
		if (vkResetFences(vk_device, 1, &vk_fence) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to reset fence");
		}

		auto &vk_commandBuffer = vk_commandBuffers[vk_swapchainImage];

		VkPipelineStageFlags vk_waitMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		VkSubmitInfo vk_submitInfo;
		{
			vk_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			vk_submitInfo.pNext = nullptr;
			vk_submitInfo.waitSemaphoreCount = 0;
			vk_submitInfo.pWaitSemaphores = nullptr;
			vk_submitInfo.pWaitDstStageMask = &vk_waitMask;
			vk_submitInfo.commandBufferCount = 1;
			vk_submitInfo.pCommandBuffers = &vk_commandBuffer;
			vk_submitInfo.signalSemaphoreCount = 0;
			vk_submitInfo.pSignalSemaphores = nullptr;
		}
		if (vkQueueSubmit(vk_queue, 1, &vk_submitInfo, VK_NULL_HANDLE) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to submit command buffer");
		}

		if (vkQueueWaitIdle(vk_queue) != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to wait for queue");
		}

		VkResult vk_result;
		VkPresentInfoKHR vk_presentInfoKHR;
		{
			vk_presentInfoKHR.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			vk_presentInfoKHR.pNext = nullptr;
			vk_presentInfoKHR.waitSemaphoreCount = 0;
			vk_presentInfoKHR.pWaitSemaphores = nullptr;
			vk_presentInfoKHR.swapchainCount = 1;
			vk_presentInfoKHR.pSwapchains = &vk_swapchainKHR;
			vk_presentInfoKHR.pImageIndices = &vk_swapchainImage;
			vk_presentInfoKHR.pResults = &vk_result;
		}
		if (vkQueuePresentKHR(vk_queue, &vk_presentInfoKHR) != VkResult::VK_SUCCESS || vk_result != VkResult::VK_SUCCESS)
		{
			throw Exception("failed to present swapchain");
		}
	}

	// std::system("pause");
}