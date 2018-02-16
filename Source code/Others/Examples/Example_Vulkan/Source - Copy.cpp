#include <../Common/Common.hpp>
#include <../Vulkan/Vulkan.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#include <iostream>


void main()
{
	auto processInstanceHandle = GetModuleHandleA(NULL);

	std::string windowClassName = "window";
	WNDCLASSA windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = windowClassName.c_str();
		windowClass.hInstance = processInstanceHandle;
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
			processInstanceHandle,
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

	auto &windowSize = Vulkan::Extent2D(400, 300);

	auto windowHandle = createWindow("Vulkan", 50, 50, windowSize.width, windowSize.height);
	auto windowDeviceContextHandle = getDeviceContext(windowHandle);



	// Instance
	Vulkan::InstanceCreateInfo::LayersNames instancelayersNames = {
		"VK_LAYER_LUNARG_api_dump",
		"VK_LAYER_LUNARG_core_validation",
		// "VK_LAYER_LUNARG_device_simulation",
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
	Vulkan::InstanceCreateInfo::ExtensionsNames instanceExtensionsNames = {
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
	};

	auto vulkanInstanceHandle = Vulkan::CreateInstance(Vulkan::InstanceCreateInfo(
		Vulkan::ApplicationInfo("Application name", 0, "Engine name", 0, VK_MAKE_VERSION(1, 0, 65)),
		instancelayersNames,
		instanceExtensionsNames
	));

	// Physical Device
	auto physicalDevicesHandles = Move(Vulkan::EnumeratePhysicalDevices(vulkanInstanceHandle));
	auto physicalDeviceHandle = physicalDevicesHandles[0];
	auto vk_physicalDeviceProperties = Vulkan::GetPhysicalDeviceProperties(physicalDeviceHandle);
	auto vk_physicalDeviceQueueFamilyProperties = Vulkan::GetPhysicalDeviceQueueFamilyProperties(physicalDeviceHandle);
	auto vk_physicalDeviceMemoryProperties = Vulkan::GetPhysicalDeviceMemoryProperties(physicalDeviceHandle);

	// Device
	Vector<const char*> deviceLayersNames = {
		"VK_LAYER_LUNARG_api_dump",
		"VK_LAYER_LUNARG_screenshot",
		"VK_LAYER_RENDERDOC_Capture",
		"VK_LAYER_LUNARG_standard_validation",
	};
	Vector<const char*> deviceExtensionsNames = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	auto deviceHandle = Vulkan::CreateDevice(physicalDeviceHandle, Vulkan::DeviceCreateInfo(
		{Vulkan::DeviceQueueCreateInfo(0, {1.0f})},
		deviceLayersNames,
		deviceExtensionsNames,
		Vulkan::PhysicalDeviceFeatures(Initializer<Vulkan::PhysicalDeviceFeatures::Feature>({}))
	));

	auto getDeviceMemoryIndex = [&](const VkMemoryPropertyFlags& properties) -> uint32_t
	{
		for (uint32_t i = 0; i < vk_physicalDeviceMemoryProperties.memoryTypeCount; ++i)
		{
			auto &memoryType = vk_physicalDeviceMemoryProperties.memoryTypes[i];

			if ((memoryType.propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		throw Exception(); // TODO
	};


	// Surface
	if (auto isPresentationSupported = Vulkan::GetPhysicalDeviceWin32PresentationSupportKHR(physicalDeviceHandle, 0)); else
	{
		throw Exception(); // TODO
	}
	auto surfaceHandle = Vulkan::CreateWin32SurfaceKHR(vulkanInstanceHandle, Vulkan::Win32SurfaceCreateInfoKHR(processInstanceHandle, windowHandle));
	{
		if (auto isSufraceSupported = Vulkan::GetPhysicalDeviceSurfaceSupportKHR(physicalDeviceHandle, 0, surfaceHandle)); else
		{
			throw Exception(); // TODO
		}
	}
	auto vk_surfaceCapabilities = Vulkan::GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDeviceHandle, surfaceHandle);
	auto vk_surfaceFormats = Move(Vulkan::GetPhysicalDeviceSurfaceFormatsKHR(physicalDeviceHandle, surfaceHandle));
	auto vk_surfaceFormat = vk_surfaceFormats[0];

	// Swapchain
	auto swapchainHandle = Vulkan::CreateSwapchainKHR(deviceHandle, Vulkan::SwapchainCreateInfoKHR(
		0,
		surfaceHandle,
		std::max<uint32_t>(vk_surfaceCapabilities.minImageCount, 2),
		vk_surfaceFormat.format,
		vk_surfaceFormat.colorSpace,
		windowSize,
		1,
		VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		VkSharingMode::VK_SHARING_MODE_EXCLUSIVE,
		{},
		VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR,
		VK_FALSE,
		Vulkan::SwapchainKHRHandle(nullptr)
	));
	auto swapchainImagesHandles = Move(Vulkan::GetSwapchainImagesKHR(deviceHandle, swapchainHandle));
	auto swapchainImageViewsHandles = Vector<Vulkan::ImageViewHandle>(swapchainImagesHandles.size());
	{
		for (Size i = 0; i < swapchainImagesHandles.size(); ++i)
		{
			auto &swapchainImageHandle = swapchainImagesHandles[i];
			auto &swapchainImageViewHandle = swapchainImageViewsHandles[i];

			// vk_swapchainImageView = CreateImageView(vk_device, )
			swapchainImageViewHandle = Vulkan::CreateImageView(deviceHandle, Vulkan::ImageViewCreateInfo(
				0, swapchainImageHandle, VkImageViewType::VK_IMAGE_VIEW_TYPE_2D, vk_surfaceFormat.format,
				Vulkan::ComponentMapping(
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B,
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A
				),
				Vulkan::ImageSubresourceRange(VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1)
			));
		}
	}

	auto renderPassHandle = Vulkan::CreateRenderPass(deviceHandle, Vulkan::RenderPassCreateInfo(
		{
			Vulkan::AttachmentDescription(
				vk_surfaceFormat.format,
				VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
				VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR,
				VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
				VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
				VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
				VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			),
		},
		{
			Vulkan::SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, {
				Vulkan::AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL),
			})
		}
	));

	// Framebuffers
	Vector<Vulkan::FramebufferHandle> framebuffersHandles(swapchainImageViewsHandles.size());
	{
		for (Size i = 0; i < framebuffersHandles.size(); ++i)
		{
			auto &framebufferHandle = framebuffersHandles[i];
			auto &swapchainImageViewHandle = swapchainImageViewsHandles[i];

			framebufferHandle = Vulkan::CreateFramebuffer(deviceHandle, Vulkan::FramebufferCreateInfo(
				renderPassHandle,
				{swapchainImageViewHandle},
				windowSize.width,
				windowSize.height,
				1
			));
		}
	}

	// Queue
	auto vk_queue = Vulkan::GetDeviceQueue(deviceHandle, 0, 0);

	// Command Pool
	auto commandPoolHandle = Vulkan::CreateCommandPool(deviceHandle, Vulkan::CommandPoolCreateInfo(VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, 0));
	{
		Vulkan::ResetCommandPool(deviceHandle, commandPoolHandle, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	}

	// Command Buffers
	auto commandBuffersHandles = Move(Vulkan::AllocateCommandBuffers(deviceHandle, Vulkan::CommandBufferAllocateInfo(commandPoolHandle, VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY, framebuffersHandles.size())));
	{
		for (Size i = 0; i < commandBuffersHandles.size(); ++i)
		{
			auto &commandBufferHandle = commandBuffersHandles[i];
			auto &framebufferHandle = framebuffersHandles[i];

			Vulkan::ResetCommandBuffer(commandBufferHandle, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

			Vulkan::BeginCommandBuffer(commandBufferHandle, Vulkan::CommandBufferBeginInfo(0));
			
			Vulkan::CmdBeginRenderPass(commandBufferHandle, Vulkan::RenderPassBeginInfo(
				renderPassHandle,
				framebufferHandle,
				Vulkan::Rect2D(Vulkan::Offset2D(0, 0), vk_surfaceCapabilities.currentExtent), {
					Vulkan::ClearValue::Color(1.0f, 0.0f, 0.0f, 1.0f),
				}),
				VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
			);

			Vulkan::CmdEndRenderPass(commandBufferHandle);

			Vulkan::EndCommandBuffer(commandBufferHandle);
		}
	}

	// Fence
	auto fenceHandle = Vulkan::CreateFence(deviceHandle, Vulkan::FenceCreateInfo(0));

	// Loop
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

		auto nextImageIndex = Vulkan::AcquireNextImageKHR(deviceHandle, swapchainHandle, fenceHandle);
		
		Vulkan::WaitForFences(deviceHandle, {fenceHandle}, false);
		Vulkan::ResetFences(deviceHandle, {fenceHandle});

		auto &vk_commandBuffer = commandBuffersHandles[nextImageIndex];

		Vulkan::QueueSubmit(vk_queue, {Vulkan::SubmitInfo({vk_commandBuffer})});
		Vulkan::QueueWaitIdle(vk_queue);

		Vulkan::QueuePresentKHR(vk_queue, Vulkan::PresentInfoKHR({}, {static_cast<VkSwapchainKHR>(swapchainHandle)}, {nextImageIndex}));
	}

	Vulkan::DestroyFence(deviceHandle, fenceHandle);
	Vulkan::FreeCommandBuffers(deviceHandle, commandPoolHandle, commandBuffersHandles);
	Vulkan::DestroyCommandPool(deviceHandle, commandPoolHandle);
	for (auto &framebufferHandle : framebuffersHandles)
	{
		Vulkan::DestroyFramebuffer(deviceHandle, framebufferHandle);
	}
	Vulkan::DestroyRenderPass(deviceHandle, renderPassHandle);
	for (auto &swapchainImageViewHandle : swapchainImageViewsHandles)
	{
		Vulkan::DestroyImageView(deviceHandle, swapchainImageViewHandle);
	}
	Vulkan::DestroySwapchainKHR(deviceHandle, swapchainHandle);
	Vulkan::DestroySurfaceKHR(vulkanInstanceHandle, surfaceHandle);
	Vulkan::DestroyDevice(deviceHandle);
	Vulkan::DestroyInstance(vulkanInstanceHandle);

	std::system("pause");
}