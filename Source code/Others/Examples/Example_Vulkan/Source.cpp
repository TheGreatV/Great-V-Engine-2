#include <iostream>
#include <fstream>

#include <../Common/Common.hpp>
#include <../Vulkan/Vulkan.hpp>

#include <Windows.h>
namespace GVE = GreatVEngine2;
using namespace GVE;
using namespace Vulkan;


void func()
{
	// shaders loader
	auto loadShader = [](const String& filename)
	{
		FILE* file = nullptr;

		auto loadResult = fopen_s(&file, filename.c_str(), "rb");

		if (loadResult != 0)
		{
			throw GVE::Exception("failed to load file");
		}

		fseek(file, 0, FILE_END);
		
		auto size = ftell(file);
		
		if (size % 4 != 0)
		{
			throw GVE::Exception(); // TODO
		}

		rewind(file);

		std::vector<uint32_t> result(size);
		fread((void*)result.data(), 1, size, file);

		fclose(file);

		return Move(result);
	};

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
			throw GVE::Exception();
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
			throw GVE::Exception();
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
			throw GVE::Exception();
		}

		return windowHandle;
	};
	auto getDeviceContext = [&](HWND windowHandle)
	{
		auto deviceContextHandle = GetDC(windowHandle);

		if (!deviceContextHandle)
		{
			throw GVE::Exception();
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
				throw GVE::Exception();
			}

			if (!SetPixelFormat(deviceContextHandle, pixelFormat, &pixelFormatDescriptorInfo))
			{
				throw GVE::Exception();
			}
		}
		
		return deviceContextHandle;
	};

	auto &windowSize = Vulkan::Extent2D(400, 300);

	auto windowHandle = createWindow("Vulkan", 50, 50, windowSize.width, windowSize.height);
	auto windowDeviceContextHandle = getDeviceContext(windowHandle);


	// Hack for VS shit
	Vector<const char*> empty;

	// Instance
	auto vk_instanceLayersProperties = EnumerateInstanceLayerProperties();
	/*auto vk_instanceLayersNames = ExtractInstanceLayersNames(vk_instanceLayersProperties);
	{
		while (true)
		{
			auto i = std::find_if(vk_instanceLayersNames.begin(), vk_instanceLayersNames.end(), [](const String& a)
			{
				auto r =
					a == "VK_LAYER_LUNARG_device_simulation" ||
					a == "VK_LAYER_LUNARG_standard_validation" ||
					a == "VK_LAYER_LUNARG_vktrace";

				return r;
			});

			if (i == vk_instanceLayersNames.end())
			{
				break;
			}

			vk_instanceLayersNames.erase(i);
		}
	}*/
	Vector<const char*> vk_instanceLayersNames = {
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
	auto vk_instanceLayersExtensionsProperties = EnumerateInstanceExtensionsProperties(vk_instanceLayersNames + static_cast<const char*>(""));
	// auto vk_instanceLayersExtensionsNames = ExtractInstanceExtensionsNames(vk_instanceLayersExtensionsProperties);
	Vector<const char*> vk_instanceLayersExtensionsNames = {
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
	};
	
	auto vk_instance = CreateInstance(InstanceCreateInfo(
		ApplicationInfo("Application Name", 0, "Engine Name", 0, VK_MAKE_VERSION(1, 0, 65)),
#if _DEBUG
		vk_instanceLayersNames,
#else
		empty,
#endif
		vk_instanceLayersExtensionsNames
	));
	
	// Physical Device
	auto vk_physicalDevices = Move(EnumeratePhysicalDevices(vk_instance));
	auto vk_physicalDevice = vk_physicalDevices[0];
	auto vk_physicalDeviceProperties = GetPhysicalDeviceProperties(vk_physicalDevice);
	auto vk_physicalDeviceQueueFamilyProperties = GetPhysicalDeviceQueueFamilyProperties(vk_physicalDevice);
	auto vk_physicalDeviceMemoryProperties = GetPhysicalDeviceMemoryProperties(vk_physicalDevice);

	// Device
	auto vk_deviceLayersProperties = EnumerateDeviceLayerProperties(vk_physicalDevice);
	// auto vk_deviceLayersNames = ExtractDeviceLayersNames(vk_deviceLayersProperties);
	Vector<const char*> vk_deviceLayersNames = {
	};
	auto vk_deviceLayersExtensionsProperties = EnumerateDeviceExtensionsProperties(vk_physicalDevice, vk_deviceLayersNames + static_cast<const char*>(""));
	// auto vk_deviceLayersExtensionsNames = ExtractDeviceExtensionsNames(vk_deviceLayersExtensionsProperties);
	Vector<const char*> vk_deviceLayersExtensionsNames = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	auto vk_device = CreateDevice(vk_physicalDevice, DeviceCreateInfo(
		{
			DeviceQueueCreateInfo(0, {1.0f}),
		},
#if _DEBUG
		vk_deviceLayersNames,
#else
		empty,
#endif
		vk_deviceLayersExtensionsNames,
		PhysicalDeviceFeatures(Initializer<PhysicalDeviceFeatures::Feature>({
		}))
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

		throw GVE::Exception(); // TODO
	};
	
	// Surface
	if (auto isPresentationSupported = Boolean(GetPhysicalDeviceWin32PresentationSupportKHR(vk_physicalDevice, 0))); else
	{
		throw GVE::Exception(); // TODO
	}
	auto vk_surface = CreateWin32SurfaceKHR(vk_instance, Win32SurfaceCreateInfoKHR(processInstanceHandle, windowHandle));
	{
		if (auto isSufraceSupported = Boolean(GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, vk_surface))); else
		{
			throw GVE::Exception(); // TODO
		}
	}
	auto vk_surfaceCapabilities = GetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physicalDevice, vk_surface);
	auto vk_surfaceFormats = Move(GetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice, vk_surface));
	auto vk_surfaceFormat = vk_surfaceFormats[0];

	// Swapchain
	auto vk_swapchain = CreateSwapchainKHR(vk_device, SwapchainCreateInfoKHR(
		0,
		vk_surface,
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
		VK_NULL_HANDLE
	));
	auto vk_swapchainImages = Move(GetSwapchainImagesKHR(vk_device, vk_swapchain));
	auto vk_swapchainImageViews = Vector<VkImageView>(vk_swapchainImages.size());
	{
		for (Size i = 0; i < vk_swapchainImages.size(); ++i)
		{
			auto &vk_swapchainImage = vk_swapchainImages[i];
			auto &vk_swapchainImageView = vk_swapchainImageViews[i];

			// vk_swapchainImageView = CreateImageView(vk_device, )
			vk_swapchainImageView = CreateImageView(vk_device, ImageViewCreateInfo(
				0, vk_swapchainImage, VkImageViewType::VK_IMAGE_VIEW_TYPE_2D, vk_surfaceFormat.format,
				ComponentMapping(
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B,
					VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A
				),
				ImageSubresourceRange(VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1)
			));
		}
	}

	// Data
	Size vertexStride = sizeof(float)* 2;
	Vector<uint8_t> vertices(vertexStride * 3);
	{
		*reinterpret_cast<float*>(vertices.data() + vertexStride * 0 + 0)		= -0.5f;
		*reinterpret_cast<float*>(vertices.data() + vertexStride * 0 + 4)		= +0.5f;

		*reinterpret_cast<float*>(vertices.data() + vertexStride * 1 + 0)		= +0.5f;
		*reinterpret_cast<float*>(vertices.data() + vertexStride * 1 + 4)		= +0.5f;
		
		*reinterpret_cast<float*>(vertices.data() + vertexStride * 2 + 0)		= +0.0f;
		*reinterpret_cast<float*>(vertices.data() + vertexStride * 2 + 4)		= -0.5f;
	}
	Size verticesMemoryTotalSize = sizeof(uint8_t) * vertices.size();

	// Buffers
	auto vk_vertexBuffer = CreateBuffer(vk_device, BufferCreateInfo(0, verticesMemoryTotalSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
	auto vk_vertexBufferDeviceMemory = [&](){
		auto vk_memoryRequirements = GetBufferMemoryRequirements(vk_device, vk_vertexBuffer);
		auto vk_deviceMemory = AllocateMemory(vk_device, MemoryAllocateInfo(
			vk_memoryRequirements.size,
			getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		));

		auto data = MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0);

		std::memcpy(data, vertices.data(), verticesMemoryTotalSize);

		UnmapMemory(vk_device, vk_deviceMemory);

		BindBufferMemory(vk_device, vk_vertexBuffer, vk_deviceMemory);

		return vk_deviceMemory;
	}();

	// Shaders
	auto vk_vertexShaderModule = CreateShaderModule(vk_device, ShaderModuleCreateInfo(Move(loadShader("Media/Shaders/Vulkan/Example_RawVulkan/triangle.spir-v.vertex-shader"))));
	auto vk_fragmentShaderModule = CreateShaderModule(vk_device, ShaderModuleCreateInfo(Move(loadShader("Media/Shaders/Vulkan/Example_RawVulkan/triangle.spir-v.fragment-shader"))));

	// RenderPass
	auto vk_renderPass = CreateRenderPass(vk_device, RenderPassCreateInfo(
		{
			AttachmentDescription(
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
			SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, {
				AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL),
			})
		}
	));

	// Pipeline
	auto vk_pipelineLayout = CreatePipelineLayout(vk_device, PipelineLayoutCreateInfo({}, {}));
	auto vk_pipelines = Move(CreateGraphicsPipelines(vk_device, VK_NULL_HANDLE, 
		{
			GraphicsPipelineCreateInfo(
				0,
				{
					PipelineShaderStageCreateInfo(VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT, vk_vertexShaderModule, "main"),
					PipelineShaderStageCreateInfo(VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT, vk_fragmentShaderModule, "main"),
				},
				PipelineVertexInputStateCreateInfo(
					{
						VertexInputBindingDescription(0, vertexStride, VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX),
					},
					{
						VertexInputAttributeDescription(0, 0, VkFormat::VK_FORMAT_R32G32_SFLOAT, 0),
					}
				),
				PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE),
				PipelineViewportStateCreateInfo(
					{
						Viewport(0, 0, static_cast<float>(vk_surfaceCapabilities.currentExtent.width), static_cast<float>(vk_surfaceCapabilities.currentExtent.height), 0.0f, 1.0f),
					},
					{
						Rect2D(Offset2D(0, 0), Extent2D(vk_surfaceCapabilities.currentExtent.width, vk_surfaceCapabilities.currentExtent.height)),
					}
				),
				PipelineRasterizationStateCreateInfo(
					VK_FALSE, VK_FALSE,
					VkPolygonMode::VK_POLYGON_MODE_FILL, VkCullModeFlagBits::VK_CULL_MODE_NONE, VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE,
					VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f
				),
				PipelineMultisampleStateCreateInfo(
					VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VK_FALSE, 0.0f, nullptr, VK_FALSE, VK_FALSE
				),
				PipelineDepthStencilStateCreateInfo(
					VK_FALSE, VK_FALSE, VkCompareOp::VK_COMPARE_OP_ALWAYS, VK_FALSE,
					VK_FALSE,
					StencilOpState(VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkCompareOp::VK_COMPARE_OP_ALWAYS, 0, 0, 0),
					StencilOpState(VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkCompareOp::VK_COMPARE_OP_ALWAYS, 0, 0, 0),
					0.0f,
					0.0f
				),
				PipelineColorBlendStateCreateInfo(
					VK_FALSE, VkLogicOp::VK_LOGIC_OP_CLEAR,
					{
						PipelineColorBlendAttachmentState(
							VK_FALSE,
							VkBlendFactor::VK_BLEND_FACTOR_ONE,
							VkBlendFactor::VK_BLEND_FACTOR_ONE,
							VkBlendOp::VK_BLEND_OP_ADD,
							VkBlendFactor::VK_BLEND_FACTOR_ONE,
							VkBlendFactor::VK_BLEND_FACTOR_ONE,
							VkBlendOp::VK_BLEND_OP_ADD,
							VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT
						),
					},
					{0.0f, 0.0f, 0.0f, 0.0f}
				),
				vk_pipelineLayout,
				vk_renderPass,
				0
			),
		}
	));
	auto &vk_pipeline = vk_pipelines[0];

	DestroyShaderModule(vk_device, vk_vertexShaderModule);
	DestroyShaderModule(vk_device, vk_fragmentShaderModule);

	// Framebuffers
	Vector<VkFramebuffer> vk_framebuffers(vk_swapchainImageViews.size());
	{
		for (Size i = 0; i < vk_framebuffers.size(); ++i)
		{
			auto &vk_framebuffer = vk_framebuffers[i];
			auto &vk_swapchainImageView = vk_swapchainImageViews[i];

			vk_framebuffer = CreateFramebuffer(vk_device, FramebufferCreateInfo(vk_renderPass, { vk_swapchainImageView }, windowSize.width, windowSize.height, 1));
		}
	}

	// Queue
	auto vk_queue = GetDeviceQueue(vk_device, 0, 0);

	// Command Pool
	auto vk_commandPool = CreateCommandPool(vk_device, CommandPoolCreateInfo(VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, 0));
	{
		ResetCommandPool(vk_device, vk_commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	}

	// Command Buffers
	auto vk_commandBuffers = Move(AllocateCommandBuffers(vk_device, CommandBufferAllocateInfo(vk_commandPool, VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY, vk_framebuffers.size())));
	{
		for (Size i = 0; i < vk_commandBuffers.size(); ++i)
		{
			auto &vk_commandBuffer = vk_commandBuffers[i];
			auto &vk_framebuffer = vk_framebuffers[i];

			ResetCommandBuffer(vk_commandBuffer, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

			BeginCommandBuffer(vk_commandBuffer, CommandBufferBeginInfo(0));
			
			CmdBeginRenderPass(vk_commandBuffer, RenderPassBeginInfo(
				vk_renderPass,
				vk_framebuffer,
				Rect2D(Offset2D(0, 0), vk_surfaceCapabilities.currentExtent), {
					ClearValue::Color(1.0f, 0.5f, 0.0f, 1.0f),
				}),
				VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
			);

			CmdBindPipeline(vk_commandBuffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline);

			CmdBindVertexBuffers(vk_commandBuffer, 0, 1, {vk_vertexBuffer}, {0});

			CmdDraw(vk_commandBuffer, 3, 1, 0, 0);

			CmdEndRenderPass(vk_commandBuffer);

			EndCommandBuffer(vk_commandBuffer);
		}
	}

	// Fence
	auto vk_fence = CreateFence(vk_device, FenceCreateInfo(0));

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

		//
		auto vk_nextImageIndex = AcquireNextImageKHR(vk_device, vk_swapchain, UINT64_MAX, VK_NULL_HANDLE, vk_fence);
		
		WaitForFences(vk_device, {vk_fence}, VK_FALSE, UINT64_MAX);
		ResetFences(vk_device, {vk_fence});

		auto &vk_commandBuffer = vk_commandBuffers[vk_nextImageIndex];

		QueueSubmit(vk_queue, {SubmitInfo({vk_commandBuffer})});
		QueueWaitIdle(vk_queue);

		QueuePresentKHR(vk_queue, PresentInfoKHR({}, {vk_swapchain}, {vk_nextImageIndex}));
	}

	DestroyFence(vk_device, vk_fence);
	FreeCommandBuffers(vk_device, vk_commandPool, vk_commandBuffers);
	DestroyCommandPool(vk_device, vk_commandPool); // TODO: crash when attempting to destroy pool without any buffers allocated
	DestroyPipeline(vk_device, vk_pipeline);
	DestroyPipelineLayout(vk_device, vk_pipelineLayout);
	DestroyRenderPass(vk_device, vk_renderPass);
	FreeMemory(vk_device, vk_vertexBufferDeviceMemory);
	DestroyBuffer(vk_device, vk_vertexBuffer);
	for (auto &vk_framebuffer : vk_framebuffers)
	{
		DestroyFramebuffer(vk_device, vk_framebuffer);
	}
	for (auto &vk_swapchainImageView : vk_swapchainImageViews)
	{
		DestroyImageView(vk_device, vk_swapchainImageView);
	}
	DestroySwapchainKHR(vk_device, vk_swapchain);
	DestroySurfaceKHR(vk_instance, vk_surface);
	DestroyDevice(vk_device);
	DestroyInstance(vk_instance);

	DestroyWindow(windowHandle);
}

void main()
{
	func();

	std::system("pause");
}