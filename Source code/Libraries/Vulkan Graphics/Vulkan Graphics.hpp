#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace Graphics
	{
		namespace APIs
		{
			namespace Vulkan
			{
				namespace Vk = GreatVEngine2::Vulkan;

				class SurfaceHolder
				{
				public:
					const WeakPointer<Driver> driver;
					const VkSurfaceKHR vk_surface;
				public:
					inline SurfaceHolder(const HINSTANCE& instanceHandle_, const HWND& windowHandle_, const StrongPointer<Driver>& driver_);
					inline ~SurfaceHolder();
				};
				class SurfaceInfo
				{
				public:
					const VkSurfaceCapabilitiesKHR vk_surfaceCapabilities;
					const Vector<VkSurfaceFormatKHR> vk_surfaceFormats;
				public:
					inline SurfaceInfo(const VkPhysicalDevice& vk_physicalDevice_, const VkSurfaceKHR& vk_surface_);
				};
				class SwapchainHolder
				{
				protected:
					static inline Vector<VkImageView> ObtainSwapchainImageViews(const VkDevice& vk_device_, const VkSurfaceFormatKHR& vk_surfaceFormat_, const Vector<VkImage>& vk_swapchainImages_);
				public:
					const VkDevice vk_device;
					const VkSwapchainKHR vk_swapchain;
					const Vector<VkImage> vk_swapchainImages;
					const Vector<VkImageView> vk_swapchainImageViews;
				public:
					inline SwapchainHolder(const VkDevice& vk_device_, const VkSurfaceKHR& vk_surface_, const VkSurfaceFormatKHR& vk_surfaceFormat_, const uint32_t& imagesCount_, const VkExtent2D& size_);
					inline ~SwapchainHolder();
				};

				class Driver:
					public This<Driver>
				{
				public:
					using Devices = Vector<StrongPointer<Device>>;
				protected:
					using SurfaceLookup = Map<Memory<View>, StrongPointer<SurfaceHolder>>;
				protected:
					static inline VkInstance ObtainInstance();
					static inline Devices ObtainDevices(const StrongPointer<Driver>& driver_);
				public: // protected:
					const VkInstance vk_instance;
					const Devices devices;
					SurfaceLookup surfaceLookup;
				public:
					inline Driver() = delete;
					inline Driver(const StrongPointer<Driver>& this_);
					inline Driver(const Driver&) = delete;
					inline virtual ~Driver() = default;
				public:
					inline Driver& operator = (const Driver&) = delete;
				public:
					inline Devices GetDevices() const;
					inline StrongPointer<SurfaceHolder> GetSurface(const StrongPointer<View>& view_);
				};
				class Device:
					public This<Device>
				{
				public:
					class SurfaceFormatComparator
					{
					public:
						inline bool operator()(const VkSurfaceFormatKHR& a_, const VkSurfaceFormatKHR& b_)
						{
							return a_.colorSpace < b_.colorSpace || a_.format < b_.format;
						}
					};
				protected:
					using SurfaceInfoLookup = Map<Memory<SurfaceHolder>, StrongPointer<SurfaceInfo>>;
					using SwapchainFormatLookup = std::map<VkSurfaceFormatKHR, StrongPointer<SwapchainHolder>, SurfaceFormatComparator>;//  Map<VkSurfaceFormatKHR, StrongPointer<SwapchainHolder>>;
					using SwapchainsLookup = Map<Memory<SurfaceInfo>, SwapchainFormatLookup>;
				protected:
					static inline VkDevice ObtainDevice(const VkPhysicalDevice& vk_physicalDevice_);
				public: // protected:
					const WeakPointer<Driver> driver;
				public: // protected:
					const VkPhysicalDevice vk_physicalDevice;
					const VkPhysicalDeviceProperties vk_physicalDeviceProperties;
					const Vector<VkQueueFamilyProperties> vk_physicalDeviceQueueFamilyProperties;
					const VkPhysicalDeviceMemoryProperties vk_physicalDeviceMemoryProperties;
					const VkDevice vk_device;
				public: // protected:
					const bool isPresentationSupported;
					SurfaceInfoLookup surfaceInfoLookup;
					SwapchainsLookup swapchainsLookup;
				public:
					inline Device() = delete;
					inline Device(const StrongPointer<Device>& this_, const VkPhysicalDevice& vk_physicalDevice_, const StrongPointer<Driver>& driver_);
					inline Device(const Device&) = delete;
					inline virtual ~Device() = default;
				public:
					inline Device& operator = (const Device&) = delete;
				public:
					inline StrongPointer<SurfaceInfo> GetSurfaceInfo(const Memory<SurfaceHolder>& surfaceHolderMemory_);
					inline StrongPointer<SwapchainHolder> GetSwapchain(const Memory<SurfaceHolder>& surfaceHolderMemory_, const StrongPointer<SurfaceInfo>& surfaceInfo_, const VkSurfaceFormatKHR& format_);
				};

				class Output:
					public Graphics::Output
				{
				protected:
					const StrongPointer<Scene> scene;
					const StrongPointer<Camera> camera;
					const Memory<Engine> engine;
				public:
					inline Output() = delete;
					inline Output(const StrongPointer<Output>& this_, const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_, const Memory<Engine>& engine_);
					inline Output(const Output&) = delete;
					inline virtual ~Output() = default;
				public:
					inline Output& operator = (const Output&) = delete;
				public:
					inline virtual void SignalPresented(const StrongPointer<View>& view_) override;
				};
				class Engine:
					public Graphics::Engine
				{
					friend Output;
				protected:
					class Context;
				protected:
					const ConstantPointer<Context> context;
				public: // protected: // can't use friend due to firward declaration
					const WeakPointer<Device> device;
					const StrongPointer<Method> method;
				public:
					inline Engine() = delete;
					inline Engine(const StrongPointer<Engine>& this_, const StrongPointer<Device>& device_);
					inline Engine(const Engine&) = delete;
					inline virtual ~Engine() = default;
				public:
					inline Engine& operator = (const Engine&) = delete;
				protected:
					Memory<Context> GetContext() const;
				public:
					inline virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
				};
#pragma region Engine::Context
				class Engine::Context
				{
				public:
					struct DeviceInfo
					{
						VkPhysicalDevice vk_physicalDevice;
						VkPhysicalDeviceProperties vk_physicalDeviceProperties;
						Vector<VkQueueFamilyProperties> vk_physicalDeviceQueueFamilyProperties;
						VkPhysicalDeviceMemoryProperties vk_physicalDeviceMemoryProperties;
						VkDevice vk_device;

						DeviceInfo(
							const VkPhysicalDevice& vk_physicalDevice_,
							const VkPhysicalDeviceProperties& vk_physicalDeviceProperties_,
							const Vector<VkQueueFamilyProperties>& vk_physicalDeviceQueueFamilyProperties_,
							const VkPhysicalDeviceMemoryProperties& vk_physicalDeviceMemoryProperties_,
							const VkDevice& vk_device_
						):
							vk_physicalDevice(vk_physicalDevice_),
							vk_physicalDeviceProperties(vk_physicalDeviceProperties_),
							vk_physicalDeviceQueueFamilyProperties(vk_physicalDeviceQueueFamilyProperties_),
							vk_physicalDeviceMemoryProperties(vk_physicalDeviceMemoryProperties_),
							vk_device(vk_device_)
						{
						}
					};
					struct SurfaceHolder
					{
						VkSurfaceKHR vk_surface;
						VkSurfaceCapabilitiesKHR vk_surfaceCapabilities;
						Vector<VkSurfaceFormatKHR> vk_surfaceFormats;

						// SurfaceHolder(const StrongPointer<APIs::Windows::View>& view_, const VkPhysicalDevice& vk_physicalDevice_)
						// {
						// 	if (auto isPresentationSupported = Vk::Boolean(Vk::GetPhysicalDeviceWin32PresentationSupportKHR(vk_physicalDevice_, 0))); else
						// 	{
						// 		throw Exception(); // TODO
						// 	}
						// 	auto vk_surface = Vk::CreateWin32SurfaceKHR(vk_instance, Vk::Win32SurfaceCreateInfoKHR(win_instanceHandle, win_windowHandle));
						// 	{
						// 		if (auto isSufraceSupported = Vk::Boolean(Vk::GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, vk_surface))); else
						// 		{
						// 			throw Exception(); // TODO
						// 		}
						// 	}
						// 
						// }
						SurfaceHolder(const VkSurfaceKHR& vk_surface_, const VkPhysicalDevice& vk_physicalDevice_)
						{
							if (auto isSufraceSupported = Vk::Boolean(Vk::GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice_, 0, vk_surface))); else
							{
								throw Exception(); // TODO
							}

							vk_surface = vk_surface_;
							
							vk_surfaceCapabilities = Vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physicalDevice_, vk_surface);
							vk_surfaceFormats = Move(Vk::GetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice_, vk_surface));
						}
					};
				public:
					VkInstance vk_instance;
					Vector<DeviceInfo> devicesInfos;
				public:
					inline Context();
					inline ~Context();
				};
#pragma endregion

				class Method:
					public This<Method>
				{
				protected:
					const WeakPointer<Engine> engine;
				public:
					inline Method() = delete;
					inline Method(const StrongPointer<Method>& this_, const StrongPointer<Engine>& engine_);
					inline Method(const Method&) = delete;
					inline virtual ~Method() = default;
				public:
					inline Method& operator = (const Method&) = delete;
				public:
					inline virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) = 0;
				};
				class ForwardMethod:
					public Method
				{
				protected:
					class Output;
					class Renderer;
				protected:
					using RenderersLookup = Map<Memory<Scene>, StrongPointer<Renderer>>;
					using RendererIt = RenderersLookup::iterator;
				protected:
					RenderersLookup renderersLookup;
				public:
					inline ForwardMethod() = delete;
					inline ForwardMethod(const StrongPointer<ForwardMethod>& this_, const StrongPointer<Engine>& engine_);
					inline ForwardMethod(const ForwardMethod&) = delete;
					inline virtual ~ForwardMethod() override = default;
				public:
					inline ForwardMethod& operator = (const ForwardMethod&) = delete;
				protected:
					inline RendererIt FindOrCreate(const Memory<Scene>& sceneMemory_);
				public:
					inline virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
				};
#pragma region ForwardMethod::Output
				class ForwardMethod::Output:
					public Graphics::Output
				{
				protected:
					const StrongPointer<Renderer> renderer;
					const StrongPointer<Camera> camera;
				public:
					inline Output() = delete;
					inline Output(const StrongPointer<Output>& this_, const StrongPointer<Renderer>& renderer_, const StrongPointer<Camera>& camera_);
					inline Output(const Output&) = delete;
					inline virtual ~Output() = default;
				public:
					inline Output& operator = (const Output&) = delete;
				public:
					inline virtual void SignalPresented(const StrongPointer<View>& view_) override;
				};
#pragma endregion
#pragma region ForwardMethod::Renderer
				class ForwardMethod::Renderer:
					public This<Renderer>
				{
					friend Output;
				protected:
					const Memory<ForwardMethod> method;
					const Memory<Scene> scene;
				protected:
					Scene::Version sceneVersion;
				public:
					inline Renderer() = delete;
					inline Renderer(const StrongPointer<Renderer>& this_, const Memory<Scene>& scene_, const Memory<ForwardMethod>& method_);
					inline Renderer(const Renderer&) = delete;
					inline virtual ~Renderer() = default;
				public:
					inline Renderer& operator = (const Renderer&) = delete;
				protected:
					inline void UpdateSceneGraph();
					inline void ForceUpdateSceneGraph();
				protected:
					inline void PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_);
				public:
					inline StrongPointer<Output> Render(const StrongPointer<Camera>& camera_);
				};
#pragma endregion
			}
		}
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region APIs

#pragma region Vulkan

#pragma region SurfaceHolder

GreatVEngine2::Graphics::APIs::Vulkan::SurfaceHolder::SurfaceHolder(const HINSTANCE& instanceHandle_, const HWND& windowHandle_, const StrongPointer<Driver>& driver_):
	driver(driver_),
	vk_surface(Vk::CreateWin32SurfaceKHR(driver_->vk_instance, Vk::Win32SurfaceCreateInfoKHR(instanceHandle_, windowHandle_)))
{
	// if (auto isSufraceSupported = Vk::Boolean(Vk::GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, vk_surface))); else
	// {
	// 	throw Exception(); // TODO
	// }
}
GreatVEngine2::Graphics::APIs::Vulkan::SurfaceHolder::~SurfaceHolder()
{
	Vk::DestroySurfaceKHR(driver->vk_instance, vk_surface);
}

#pragma endregion

#pragma region SurfaceInfo

GreatVEngine2::Graphics::APIs::Vulkan::SurfaceInfo::SurfaceInfo(const VkPhysicalDevice& vk_physicalDevice_, const VkSurfaceKHR& vk_surface_):
	vk_surfaceCapabilities(Vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physicalDevice_, vk_surface_)),
	vk_surfaceFormats(Move(Vk::GetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice_, vk_surface_)))
{
}

#pragma endregion

#pragma region SwapchainHolder

GreatVEngine2::Vector<VkImageView> GreatVEngine2::Graphics::APIs::Vulkan::SwapchainHolder::ObtainSwapchainImageViews(const VkDevice& vk_device_, const VkSurfaceFormatKHR& vk_surfaceFormat_, const Vector<VkImage>& vk_swapchainImages_)
{
	auto vk_swapchainImageViews = Vector<VkImageView>(vk_swapchainImages_.size());

	for (auto &i : Range(vk_swapchainImages_.size()))
	{
		auto &vk_swapchainImage = vk_swapchainImages_[i];
		auto &vk_swapchainImageView = vk_swapchainImageViews[i];

		// vk_swapchainImageView = CreateImageView(vk_device, )
		vk_swapchainImageView = Vk::CreateImageView(vk_device_, Vk::ImageViewCreateInfo(
			0, vk_swapchainImage, VkImageViewType::VK_IMAGE_VIEW_TYPE_2D, vk_surfaceFormat_.format,
			Vk::ComponentMapping(
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A
			),
			Vk::ImageSubresourceRange(VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1)
		));
	}
	return Move(vk_swapchainImageViews);
}

GreatVEngine2::Graphics::APIs::Vulkan::SwapchainHolder::SwapchainHolder(const VkDevice& vk_device_, const VkSurfaceKHR& vk_surface_, const VkSurfaceFormatKHR& vk_surfaceFormat_, const uint32_t& imagesCount_, const VkExtent2D& size_):
	vk_device(vk_device_),
	vk_swapchain(Vk::CreateSwapchainKHR(vk_device, Vk::SwapchainCreateInfoKHR(
		0,
		vk_surface_,
		imagesCount_, // std::max<uint32_t>(vk_surfaceCapabilities.minImageCount, 2),
		vk_surfaceFormat_.format,
		vk_surfaceFormat_.colorSpace,
		size_, // windowSize,
		1,
		VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		VkSharingMode::VK_SHARING_MODE_EXCLUSIVE,
		{},
		VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR,
		VK_FALSE,
		VK_NULL_HANDLE
	))),
	vk_swapchainImages(Move(Vk::GetSwapchainImagesKHR(vk_device, vk_swapchain))),
	vk_swapchainImageViews(Move(ObtainSwapchainImageViews(vk_device, vk_surfaceFormat_, vk_swapchainImages)))
{
}
GreatVEngine2::Graphics::APIs::Vulkan::SwapchainHolder::~SwapchainHolder()
{
	Vk::DestroySwapchainKHR(vk_device, vk_swapchain);
}

#pragma endregion

#pragma region Driver

VkInstance GreatVEngine2::Graphics::APIs::Vulkan::Driver::ObtainInstance()
{
	auto vk_instanceLayersProperties = Vk::EnumerateInstanceLayerProperties(); // TODO
	
	Vector<const char*> vk_instanceLayersNames =
#if __GREAT_V_ENGINE_2__DEBUG__
	{
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
#else
	{};
#endif

	auto vk_instanceLayersExtensionsProperties = Vk::EnumerateInstanceExtensionsProperties(vk_instanceLayersNames + static_cast<const char*>("")); // TODO
	
	Vector<const char*> vk_instanceLayersExtensionsNames = {
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
	};
	
	auto vk_instance = Vk::CreateInstance(Vk::InstanceCreateInfo(
		Vk::ApplicationInfo("Application Name", 0, "Engine Name", 0, VK_MAKE_VERSION(1, 0, 65)),
		vk_instanceLayersNames,
		vk_instanceLayersExtensionsNames
	));

	return vk_instance;
}
GreatVEngine2::Graphics::APIs::Vulkan::Driver::Devices GreatVEngine2::Graphics::APIs::Vulkan::Driver::ObtainDevices(const StrongPointer<Driver>& driver_)
{
	auto vk_instance = driver_->vk_instance;
	auto vk_physicalDevices = Move(Vk::EnumeratePhysicalDevices(vk_instance));

	Devices devices(vk_physicalDevices.size());

	for (auto i : Range(devices.size()))
	{
		auto &vk_physicalDevice = vk_physicalDevices[i];

		devices[i] = Make<Device>(vk_physicalDevice, driver_);
	}

	return Move(devices);
}

GreatVEngine2::Graphics::APIs::Vulkan::Driver::Driver(const StrongPointer<Driver>& this_):
	This(this_),
	vk_instance(ObtainInstance()),
	devices(ObtainDevices(this_))
{
}

GreatVEngine2::Graphics::APIs::Vulkan::Driver::Devices GreatVEngine2::Graphics::APIs::Vulkan::Driver::GetDevices() const
{
	return devices;
}
GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::Vulkan::SurfaceHolder> GreatVEngine2::Graphics::APIs::Vulkan::Driver::GetSurface(const StrongPointer<View>& view_)
{
	auto viewMemory = view_.GetValue();
	auto it = surfaceLookup.find(viewMemory);

	if (it == surfaceLookup.end())
	{
		auto surfaceHolder = [&]()
		{
			if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
			{
				auto holder = MakeStrong<SurfaceHolder>(windowsView->GetInstanceHandle(), windowsView->GetWindowHandle(), GetThis<Driver>());

				return holder;
			}

			throw NotImplementedException();
		}();

		surfaceLookup.insert({viewMemory, surfaceHolder});

		return surfaceHolder;
	}
	else
	{
		auto surfaceHolder = (*it).second;

		return surfaceHolder;
	}
}

#pragma endregion

#pragma region Device

VkDevice GreatVEngine2::Graphics::APIs::Vulkan::Device::ObtainDevice(const VkPhysicalDevice& vk_physicalDevice_)
{
	// Device
	auto vk_deviceLayersProperties = Vk::EnumerateDeviceLayerProperties(vk_physicalDevice_); // TODO

	Vector<const char*> vk_deviceLayersNames = {
	};
	
	auto vk_deviceLayersExtensionsProperties = Vk::EnumerateDeviceExtensionsProperties(vk_physicalDevice_, vk_deviceLayersNames + static_cast<const char*>("")); // TODO

	Vector<const char*> vk_deviceLayersExtensionsNames = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	auto vk_device = Vk::CreateDevice(vk_physicalDevice_, Vk::DeviceCreateInfo(
		{ Vk::DeviceQueueCreateInfo(0, {1.0f}), },
		vk_deviceLayersNames,
		vk_deviceLayersExtensionsNames,
		Vk::PhysicalDeviceFeatures(Initializer<Vk::PhysicalDeviceFeatures::Feature>({
		}))
	));

	return vk_device;
}

GreatVEngine2::Graphics::APIs::Vulkan::Device::Device(const StrongPointer<Device>& this_, const VkPhysicalDevice& vk_physicalDevice_, const StrongPointer<Driver>& driver_):
	This(this_),
	driver(driver_),
	vk_physicalDevice(vk_physicalDevice_),
	vk_physicalDeviceProperties(Vk::GetPhysicalDeviceProperties(vk_physicalDevice)),
	vk_physicalDeviceQueueFamilyProperties(Move(Vk::GetPhysicalDeviceQueueFamilyProperties(vk_physicalDevice))),
	vk_physicalDeviceMemoryProperties(Vk::GetPhysicalDeviceMemoryProperties(vk_physicalDevice)),
	vk_device(ObtainDevice(vk_physicalDevice)),
	isPresentationSupported(Vk::Boolean(Vk::GetPhysicalDeviceWin32PresentationSupportKHR(vk_physicalDevice, 0)))
{
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::Vulkan::SurfaceInfo> GreatVEngine2::Graphics::APIs::Vulkan::Device::GetSurfaceInfo(const Memory<SurfaceHolder>& surfaceHolderMemory_)
{
	auto it = surfaceInfoLookup.find(surfaceHolderMemory_);

	if (it == surfaceInfoLookup.end())
	{
		if (auto isSufraceSupported = Vk::Boolean(Vk::GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, surfaceHolderMemory_->vk_surface))); else // TODO: replace 0 with queue index
		{
			throw Exception(); // TODO
		}

		auto surfaceInfo = MakeStrong<SurfaceInfo>(vk_physicalDevice, surfaceHolderMemory_->vk_surface);

		surfaceInfoLookup.insert({surfaceHolderMemory_, surfaceInfo});

		return surfaceInfo;
	}
	else
	{
		auto surfaceInfo = (*it).second;

		return surfaceInfo;
	}
}
GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::Vulkan::SwapchainHolder> GreatVEngine2::Graphics::APIs::Vulkan::Device::GetSwapchain(const Memory<SurfaceHolder>& surfaceHolderMemory_, const StrongPointer<SurfaceInfo>& surfaceInfo_, const VkSurfaceFormatKHR& format_)
{
	auto surfaceInfoMemory = surfaceInfo_.GetValue();
	auto swapchainFormatsIt = [&]()
	{
		auto it = swapchainsLookup.find(surfaceInfoMemory);

		if (it == swapchainsLookup.end())
		{
			auto nIt = swapchainsLookup.insert({surfaceInfoMemory, SwapchainFormatLookup()});

			return nIt.first;
		}
		else
		{
			return it;
		}
	}();
	auto &swapchainFormats = (*swapchainFormatsIt).second;
	auto swapchainIt = [&]
	{
		auto it = swapchainFormats.find(format_);

		if (it == swapchainFormats.end())
		{
			auto holder = MakeStrong<SwapchainHolder>(
				vk_device,
				surfaceHolderMemory_->vk_surface,
				format_, 
				std::max<uint32_t>(surfaceInfo_->vk_surfaceCapabilities.minImageCount, 2),
				surfaceInfo_->vk_surfaceCapabilities.currentExtent
			);
			auto nIt = swapchainFormats.insert({format_, holder});

			return nIt.first;
		}
		else
		{
			return it;
		}
	}();
	auto &swapchainHolder = (*swapchainIt).second;

	return swapchainHolder;
}

#pragma endregion

#pragma region Output

GreatVEngine2::Graphics::APIs::Vulkan::Output::Output(const StrongPointer<Output>& this_, const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_, const Memory<Engine>& engine_):
	Graphics::Output(this_),
	scene(scene_),
	camera(camera_),
	engine(engine_)
{
}

void GreatVEngine2::Graphics::APIs::Vulkan::Output::SignalPresented(const StrongPointer<View>& view_)
{
	if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
	{
		namespace Vk = GreatVEngine2::Vulkan;

		auto context = engine->GetContext();
		auto &deviceInfo = context->devicesInfos[0];

		auto vk_instance = context->vk_instance;
		auto vk_physicalDevice = deviceInfo.vk_physicalDevice;
		auto vk_device = deviceInfo.vk_device;

		auto &vk_physicalDeviceMemoryProperties = deviceInfo.vk_physicalDeviceMemoryProperties;

		auto win_instanceHandle = windowsView->GetInstanceHandle();
		auto win_windowHandle = windowsView->GetWindowHandle();

		auto windowSize = [&]
		{
			RECT rect;
			
			if (GetClientRect(win_windowHandle, &rect) == 0)
			{
				throw Exception();
			}

			return Vk::Extent2D(rect.right, rect.bottom);
		}();
		
		auto viewport = view_->GetViewportRange();
		auto aspect = viewport.GetAspect();

		// functions
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
		auto getDeviceMemoryIndex2 = [&](const VkMemoryPropertyFlags& properties, const uint32_t& memoryTypeBits) -> uint32_t
		{
			for (uint32_t i = 0; i < vk_physicalDeviceMemoryProperties.memoryTypeCount; ++i)
			{
				if (((1 << i) & memoryTypeBits) != 0)
				{
					auto &memoryType = vk_physicalDeviceMemoryProperties.memoryTypes[i];

					if ((memoryType.propertyFlags & properties) == properties)
					{
						return i;
					}
				}
			}

			throw Exception(); // TODO
		};
		auto loadShader = [](const String& filename)
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

		// Surface
		if (auto isPresentationSupported = Vk::Boolean(Vk::GetPhysicalDeviceWin32PresentationSupportKHR(vk_physicalDevice, 0))); else
		{
			throw Exception(); // TODO
		}
		auto vk_surface = Vk::CreateWin32SurfaceKHR(vk_instance, Vk::Win32SurfaceCreateInfoKHR(win_instanceHandle, win_windowHandle));
		{
			if (auto isSufraceSupported = Vk::Boolean(Vk::GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, vk_surface))); else
			{
				throw Exception(); // TODO
			}
		}
		auto vk_surfaceCapabilities = Vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physicalDevice, vk_surface);
		auto vk_surfaceFormats = Move(Vk::GetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice, vk_surface));
		auto vk_surfaceFormat = vk_surfaceFormats[0];

		// Swapchain
		auto vk_swapchain = Vk::CreateSwapchainKHR(vk_device, Vk::SwapchainCreateInfoKHR(
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

		auto vk_swapchainImages = Move(Vk::GetSwapchainImagesKHR(vk_device, vk_swapchain));
		auto vk_nextImageIndex = [&]()
		{
			// Fence
			auto vk_fence = Vk::CreateFence(vk_device, Vk::FenceCreateInfo(0));

			auto vk_nextImageIndex = Vk::AcquireNextImageKHR(vk_device, vk_swapchain, UINT64_MAX, VK_NULL_HANDLE, vk_fence);

			Vk::WaitForFences(vk_device, {vk_fence}, VK_FALSE, UINT64_MAX);
			Vk::ResetFences(vk_device, {vk_fence});

			Vk::DestroyFence(vk_device, vk_fence);
			
			return vk_nextImageIndex;
		}();
		auto vk_swapchainImage = vk_swapchainImages[vk_nextImageIndex];
		auto vk_swapchainImageView = Vk::CreateImageView(vk_device, Vk::ImageViewCreateInfo(
			0, vk_swapchainImage, VkImageViewType::VK_IMAGE_VIEW_TYPE_2D, vk_surfaceFormat.format,
			Vk::ComponentMapping(
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A
			),
			Vk::ImageSubresourceRange(VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1)
		));
		auto vk_depthFormat = VkFormat::VK_FORMAT_D32_SFLOAT;
		auto vk_swapchainDepthImage = Vk::CreateImage(vk_device, Vk::ImageCreateInfo(0,
			VkImageType::VK_IMAGE_TYPE_2D, vk_depthFormat, Vk::Extent3D(vk_surfaceCapabilities.currentExtent, 1), 1, 1, VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
			VkImageTiling::VK_IMAGE_TILING_OPTIMAL, VkImageUsageFlagBits::VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED
		));
		auto vk_swapchainDepthImageDeviceMemory = [&]()
		{
			auto vk_memoryRequirements = Vk::GetImageMemoryRequirements(vk_device, vk_swapchainDepthImage);
			auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
				vk_memoryRequirements.size,
				getDeviceMemoryIndex2(0, vk_memoryRequirements.memoryTypeBits)
			));

			Vk::BindImageMemory(vk_device, vk_swapchainDepthImage, vk_deviceMemory);

			return vk_deviceMemory;
		}();
		auto vk_swapchainDepthImageView = Vk::CreateImageView(vk_device, Vk::ImageViewCreateInfo(
			0, vk_swapchainDepthImage, VkImageViewType::VK_IMAGE_VIEW_TYPE_2D, vk_depthFormat,
			Vk::ComponentMapping(
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY,
				VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY
			),
			Vk::ImageSubresourceRange(VkImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1)
		));

		// RenderPass
		auto vk_renderPass = Vk::CreateRenderPass(vk_device, Vk::RenderPassCreateInfo(
			{
				Vk::AttachmentDescription(
					vk_surfaceFormat.format,
					VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
				),
				Vk::AttachmentDescription(
					vk_depthFormat,
					VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				),
			},
			{
				Vk::SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS,
					{ Vk::AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) },
					Vk::AttachmentReference(1, VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
				)
			}
		));

		// Framebuffers
		auto vk_framebuffer = Vk::CreateFramebuffer(vk_device, Vk::FramebufferCreateInfo(vk_renderPass, {vk_swapchainImageView, vk_swapchainDepthImageView}, windowSize.width, windowSize.height, 1));

		// Command Pool
		auto vk_commandPool = Vk::CreateCommandPool(vk_device, Vk::CommandPoolCreateInfo(VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, 0));
		{
			Vk::ResetCommandPool(vk_device, vk_commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
		}

		// Command Buffers
		auto vk_commandBuffer = Vk::AllocateCommandBuffer(vk_device, vk_commandPool, VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		{
			Vk::ResetCommandBuffer(vk_commandBuffer, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

			Vk::BeginCommandBuffer(vk_commandBuffer, Vk::CommandBufferBeginInfo(0));
			
			Vk::CmdBeginRenderPass(vk_commandBuffer, Vk::RenderPassBeginInfo(
				vk_renderPass,
				vk_framebuffer,
				Vk::Rect2D(Vk::Offset2D(0, 0), vk_surfaceCapabilities.currentExtent), {
					Vk::ClearValue::Color(1.0f, 0.0f, 0.0f, 1.0f),
					Vk::ClearValue::DepthStencil(1.0f, 0),
				}),
				VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
			);

			Vk::CmdEndRenderPass(vk_commandBuffer);

			Vk::EndCommandBuffer(vk_commandBuffer);
		}

		// Queue
		auto vk_queue = Vk::GetDeviceQueue(vk_device, 0, 0);

		Vk::QueueSubmit(vk_queue, {Vk::SubmitInfo({vk_commandBuffer})});
		Vk::QueueWaitIdle(vk_queue);

		// Cleanup
		Vk::FreeCommandBuffer(vk_device, vk_commandPool, vk_commandBuffer);
		Vk::DestroyRenderPass(vk_device, vk_renderPass);
		Vk::DestroyFramebuffer(vk_device, vk_framebuffer);

		// Descriptors Pool
		auto vk_descriptorPool = Vk::CreateDescriptorPool(vk_device, Vk::DescriptorPoolCreateInfo(
			VkDescriptorPoolCreateFlagBits::VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
			1,
			{Vk::DescriptorPoolSize(VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1)}
		));

		// Descriptor Set Layout
		auto vk_descriptorSetLayout = Vk::CreateDescriptorSetLayout(vk_device, Vk::DescriptorSetLayoutCreateInfo(0, {
			Vk::DescriptorSetLayoutBinding(0, VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT),
		}));

		// Pipeline
		auto vk_pipelineLayout = Vk::CreatePipelineLayout(vk_device, Vk::PipelineLayoutCreateInfo({vk_descriptorSetLayout}, {}));


		for (auto &objectMemory : scene->objects)
		{
			auto model = objectMemory->GetModel();
			auto geometry = model->GetGeometry();

			// Data
			auto verticesCount = geometry->GetVerticesCount();
			auto vertexSize = geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F);
			auto totalVerticesSize = verticesCount * vertexSize;
			auto vertices = Move(geometry->GetVertices(Geometry::VertexPackMode::Pos32F));

			auto indicesCount = geometry->GetIndicesCount();
			auto indexSize = geometry->GetIndexSize(Geometry::IndexPackMode::UInt32);
			auto totalIndicesSize = indicesCount * indexSize;
			auto indices = Move(geometry->GetIndices(Geometry::IndexPackMode::UInt32));

			Size uniformsTotalSize = sizeof(Float32)* 16;

			// Buffers
			auto vk_vertexBuffer = Vk::CreateBuffer(vk_device, Vk::BufferCreateInfo(0, totalVerticesSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
			auto vk_vertexBufferDeviceMemory = [&](){
				auto vk_memoryRequirements = Vk::GetBufferMemoryRequirements(vk_device, vk_vertexBuffer);
				auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
					vk_memoryRequirements.size,
					getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
				));

				auto data = reinterpret_cast<Memory<UInt8>>(Vk::MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0));

				CopyMemory(data, vertices.data(), totalVerticesSize);

				Vk::UnmapMemory(vk_device, vk_deviceMemory);

				Vk::BindBufferMemory(vk_device, vk_vertexBuffer, vk_deviceMemory);

				return vk_deviceMemory;
			}();
			auto vk_indexBuffer = Vk::CreateBuffer(vk_device, Vk::BufferCreateInfo(0, totalIndicesSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
			auto vk_indexBufferDeviceMemory = [&]()
			{
				auto vk_memoryRequirements = Vk::GetBufferMemoryRequirements(vk_device, vk_indexBuffer);
				auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
					vk_memoryRequirements.size,
					getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
				));

				auto data = reinterpret_cast<Memory<UInt8>>(Vk::MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0));

				CopyMemory(data, indices.data(), totalIndicesSize);

				Vk::UnmapMemory(vk_device, vk_deviceMemory);

				Vk::BindBufferMemory(vk_device, vk_indexBuffer, vk_deviceMemory);

				return vk_deviceMemory;
			}();
			auto vk_uniformBuffer = Vk::CreateBuffer(vk_device, Vk::BufferCreateInfo(0, uniformsTotalSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
			auto vk_uniformBufferDeviceMemory = [&]()
			{
				auto vk_memoryRequirements = Vk::GetBufferMemoryRequirements(vk_device, vk_uniformBuffer);
				auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
					vk_memoryRequirements.size,
					getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
				));

				auto data = reinterpret_cast<Memory<Float32>>(Vk::MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0));

				auto modelMatrix = objectMemory->GetMMat();
				auto viewMatrix = camera->GetVMat();
				auto viewProjectionMatrix = Perspective(60.0f, aspect, 0.1f, 10.0f) * viewMatrix;
				auto mat = viewProjectionMatrix * modelMatrix;

				CopyMemory(data, reinterpret_cast<Memory<Float32>>(&mat), 16);

				Vk::UnmapMemory(vk_device, vk_deviceMemory);

				Vk::BindBufferMemory(vk_device, vk_uniformBuffer, vk_deviceMemory);

				return vk_deviceMemory;
			}();

			// Shaders
			auto vk_vertexShaderModule = Vk::CreateShaderModule(vk_device, Vk::ShaderModuleCreateInfo(Move(loadShader("Media/Shaders/Vulkan/Example_Graphics/triangle.spir-v.vertex-shader"))));
			auto vk_fragmentShaderModule = Vk::CreateShaderModule(vk_device, Vk::ShaderModuleCreateInfo(Move(loadShader("Media/Shaders/Vulkan/Example_Graphics/triangle.spir-v.fragment-shader"))));

			// Descriptor Set
			auto vk_descriptorSets = Move(Vk::AllocateDescriptorSets(vk_device, Vk::DescriptorSetAllocateInfo(vk_descriptorPool, {vk_descriptorSetLayout})));
			auto &vk_descriptorSet = vk_descriptorSets[0];
			{
				Vk::UpdateDescriptorSets(vk_device, {
					Vk::WriteDescriptorSet(vk_descriptorSet, 0, 0, VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, {Vk::DescriptorBufferInfo(vk_uniformBuffer)}),
				}, {});
			}

			// RenderPass
			auto vk_renderPass = Vk::CreateRenderPass(vk_device, Vk::RenderPassCreateInfo(
				{
					Vk::AttachmentDescription(
						vk_surfaceFormat.format,
						VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
						VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_LOAD,
						VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
						VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
						VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
						VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
						VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
					),
					Vk::AttachmentDescription(
						vk_depthFormat,
						VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
						VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_LOAD,
						VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
						VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
						VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
						VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
						VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
					),
				},
				{
					Vk::SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS,
						{Vk::AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)},
						Vk::AttachmentReference(1, VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
					)
				}
			));

			// Framebuffers
			auto vk_framebuffer = Vk::CreateFramebuffer(vk_device, Vk::FramebufferCreateInfo(vk_renderPass, {vk_swapchainImageView, vk_swapchainDepthImageView}, windowSize.width, windowSize.height, 1));

			// Pipeline
			auto vk_pipelines = Move(Vk::CreateGraphicsPipelines(vk_device, VK_NULL_HANDLE,
				{
					Vk::GraphicsPipelineCreateInfo(
						0,
						{
							Vk::PipelineShaderStageCreateInfo(VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT, vk_vertexShaderModule, "main"),
							Vk::PipelineShaderStageCreateInfo(VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT, vk_fragmentShaderModule, "main"),
						},
						Vk::PipelineVertexInputStateCreateInfo(
							{ Vk::VertexInputBindingDescription(0, vertexSize, VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX) },
							{ Vk::VertexInputAttributeDescription(0, 0, VkFormat::VK_FORMAT_R32G32B32_SFLOAT, 0) }
						),
						Vk::PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE),
						Vk::PipelineViewportStateCreateInfo(
							{ Vk::Viewport(
								0,
								static_cast<Float32>(vk_surfaceCapabilities.currentExtent.height),
								static_cast<Float32>(vk_surfaceCapabilities.currentExtent.width),
								-static_cast<Float32>(vk_surfaceCapabilities.currentExtent.height),
								0.0f,
								1.0f
							) },
							{ Vk::Rect2D(Vk::Offset2D(0, 0), Vk::Extent2D(vk_surfaceCapabilities.currentExtent.width, vk_surfaceCapabilities.currentExtent.height)) }
						),
						Vk::PipelineRasterizationStateCreateInfo(
							VK_FALSE, VK_FALSE,
							VkPolygonMode::VK_POLYGON_MODE_FILL, VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT, VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE,
							VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f
						),
						Vk::PipelineMultisampleStateCreateInfo(
							VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
							VK_FALSE, 0.0f, nullptr, VK_FALSE, VK_FALSE
						),
						Vk::PipelineDepthStencilStateCreateInfo(
							VK_TRUE, VK_TRUE, VkCompareOp::VK_COMPARE_OP_LESS, VK_FALSE,
							VK_FALSE,
							Vk::StencilOpState(VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkCompareOp::VK_COMPARE_OP_ALWAYS, 0, 0, 0),
							Vk::StencilOpState(VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkCompareOp::VK_COMPARE_OP_ALWAYS, 0, 0, 0),
							0.0f,
							0.0f
						),
						Vk::PipelineColorBlendStateCreateInfo(
							VK_FALSE, VkLogicOp::VK_LOGIC_OP_CLEAR,
							{
								Vk::PipelineColorBlendAttachmentState(
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

			Vk::DestroyShaderModule(vk_device, vk_vertexShaderModule);
			Vk::DestroyShaderModule(vk_device, vk_fragmentShaderModule);

			// Command Buffers
			auto vk_commandBuffer = Vk::AllocateCommandBuffer(vk_device, vk_commandPool, VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY);
			{
				Vk::ResetCommandBuffer(vk_commandBuffer, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

				Vk::BeginCommandBuffer(vk_commandBuffer, Vk::CommandBufferBeginInfo(0));
			
				Vk::CmdBeginRenderPass(vk_commandBuffer, Vk::RenderPassBeginInfo(
					vk_renderPass,
					vk_framebuffer,
					Vk::Rect2D(Vk::Offset2D(0, 0), vk_surfaceCapabilities.currentExtent), {
						// Vk::ClearValue::Color(1.0f, 0.0f, 0.0f, 1.0f),
						// Vk::ClearValue::DepthStencil(1.0f, 0),
					}),
					VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
				);

				Vk::CmdBindPipeline(vk_commandBuffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline);
				
				Vk::CmdBindVertexBuffers(vk_commandBuffer, 0, 1, {vk_vertexBuffer}, {0});
				Vk::CmdBindIndexBuffer(vk_commandBuffer, vk_indexBuffer, 0, VkIndexType::VK_INDEX_TYPE_UINT32);
				
				Vk::CmdBindDescriptorSets(vk_commandBuffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipelineLayout, 0, {vk_descriptorSet}, {});
				
				Vk::CmdDrawIndexed(vk_commandBuffer, indicesCount, 1, 0, 0, 0);

				Vk::CmdEndRenderPass(vk_commandBuffer);

				Vk::EndCommandBuffer(vk_commandBuffer);
			}

			Vk::QueueSubmit(vk_queue, {Vk::SubmitInfo({vk_commandBuffer})});
			Vk::QueueWaitIdle(vk_queue);

			// Cleanup
			Vk::FreeCommandBuffer(vk_device, vk_commandPool, vk_commandBuffer);
			Vk::DestroyPipeline(vk_device, vk_pipeline);
			Vk::DestroyRenderPass(vk_device, vk_renderPass);
			Vk::DestroyFramebuffer(vk_device, vk_framebuffer);
			Vk::FreeDescriptorSets(vk_device, vk_descriptorPool, vk_descriptorSets);
			Vk::FreeMemory(vk_device, vk_vertexBufferDeviceMemory); Vk::DestroyBuffer(vk_device, vk_vertexBuffer);
			Vk::FreeMemory(vk_device, vk_indexBufferDeviceMemory); Vk::DestroyBuffer(vk_device, vk_indexBuffer);
			Vk::FreeMemory(vk_device, vk_uniformBufferDeviceMemory); Vk::DestroyBuffer(vk_device, vk_uniformBuffer);
		}
		
		Vk::QueuePresentKHR(vk_queue, Vk::PresentInfoKHR({}, {vk_swapchain}, {vk_nextImageIndex}));

		// Cleanup
		Vk::DestroyCommandPool(vk_device, vk_commandPool); // TODO: crash when attempting to destroy pool without any buffers allocated
		Vk::DestroyPipelineLayout(vk_device, vk_pipelineLayout);
		Vk::DestroyDescriptorSetLayout(vk_device, vk_descriptorSetLayout);
		Vk::DestroyDescriptorPool(vk_device, vk_descriptorPool);
		Vk::DestroyImageView(vk_device, vk_swapchainImageView);
		Vk::DestroyImageView(vk_device, vk_swapchainDepthImageView); Vk::FreeMemory(vk_device, vk_swapchainDepthImageDeviceMemory); Vk::DestroyImage(vk_device, vk_swapchainDepthImage);
		Vk::DestroySwapchainKHR(vk_device, vk_swapchain);
		Vk::DestroySurfaceKHR(vk_instance, vk_surface);
	}
}

/*
void GreatVEngine2::Graphics::APIs::Vulkan::Output::SignalPresented(const StrongPointer<View>& view_)
{
	if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
	{
		namespace Vk = GreatVEngine2::Vulkan;

		auto context = engine->GetContext();
		auto &deviceInfo = context->devicesInfos[0];

		auto vk_instance = context->vk_instance;
		auto vk_physicalDevice = deviceInfo.vk_physicalDevice;
		auto vk_device = deviceInfo.vk_device;

		auto &vk_physicalDeviceMemoryProperties = deviceInfo.vk_physicalDeviceMemoryProperties;

		auto win_instanceHandle = windowsView->GetInstanceHandle();
		auto win_windowHandle = windowsView->GetWindowHandle();

		auto windowSize = [&]
		{
			RECT rect;
			
			if (GetClientRect(win_windowHandle, &rect) == 0)
			{
				throw Exception();
			}

			return Vk::Extent2D(rect.right, rect.bottom);
		}();
		
		auto viewport = view_->GetViewportRange();
		auto aspect = viewport.GetAspect();

		// functions
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
		auto loadShader = [](const String& filename)
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

		// Surface
		if (auto isPresentationSupported = Vk::Boolean(Vk::GetPhysicalDeviceWin32PresentationSupportKHR(vk_physicalDevice, 0))); else
		{
			throw Exception(); // TODO
		}
		auto vk_surface = Vk::CreateWin32SurfaceKHR(vk_instance, Vk::Win32SurfaceCreateInfoKHR(win_instanceHandle, win_windowHandle));
		{
			if (auto isSufraceSupported = Vk::Boolean(Vk::GetPhysicalDeviceSurfaceSupportKHR(vk_physicalDevice, 0, vk_surface))); else
			{
				throw Exception(); // TODO
			}
		}
		auto vk_surfaceCapabilities = Vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(vk_physicalDevice, vk_surface);
		auto vk_surfaceFormats = Move(Vk::GetPhysicalDeviceSurfaceFormatsKHR(vk_physicalDevice, vk_surface));
		auto vk_surfaceFormat = vk_surfaceFormats[0];

		// Swapchain
		auto vk_swapchain = Vk::CreateSwapchainKHR(vk_device, Vk::SwapchainCreateInfoKHR(
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

		auto vk_swapchainImages = Move(Vk::GetSwapchainImagesKHR(vk_device, vk_swapchain));
		auto vk_swapchainImageViews = Vector<VkImageView>(vk_swapchainImages.size());
		{
			for (Size i = 0; i < vk_swapchainImages.size(); ++i)
			{
				auto &vk_swapchainImage = vk_swapchainImages[i];
				auto &vk_swapchainImageView = vk_swapchainImageViews[i];

				// vk_swapchainImageView = CreateImageView(vk_device, )
				vk_swapchainImageView = Vk::CreateImageView(vk_device, Vk::ImageViewCreateInfo(
					0, vk_swapchainImage, VkImageViewType::VK_IMAGE_VIEW_TYPE_2D, vk_surfaceFormat.format,
					Vk::ComponentMapping(
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B,
						VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A
					),
					Vk::ImageSubresourceRange(VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1)
				));
			}
		}

		// RenderPass
		auto vk_renderPass = Vk::CreateRenderPass(vk_device, Vk::RenderPassCreateInfo(
			{
				Vk::AttachmentDescription(
					vk_surfaceFormat.format,
					VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageLayout::VK_IMAGE_LAYOUT_PREINITIALIZED
				),
			},
			{
				Vk::SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, {
					Vk::AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL),
				})
			}
		));
		auto vk_renderPass2 = Vk::CreateRenderPass(vk_device, Vk::RenderPassCreateInfo(
			{
				Vk::AttachmentDescription(
					vk_surfaceFormat.format,
					VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_LOAD,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
					VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				),
			},
			{
				Vk::SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, {
					Vk::AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL),
				})
			}
		));

		// Framebuffers
		Vector<VkFramebuffer> vk_framebuffers(vk_swapchainImageViews.size());
		{
			for (Size i = 0; i < vk_framebuffers.size(); ++i)
			{
				auto &vk_framebuffer = vk_framebuffers[i];
				auto &vk_swapchainImageView = vk_swapchainImageViews[i];

				vk_framebuffer = Vk::CreateFramebuffer(vk_device, Vk::FramebufferCreateInfo(vk_renderPass, {vk_swapchainImageView}, windowSize.width, windowSize.height, 1));
			}
		}

		// Descriptors Pool
		auto vk_descriptorPool = Vk::CreateDescriptorPool(vk_device, Vk::DescriptorPoolCreateInfo(
			VkDescriptorPoolCreateFlagBits::VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
			1,
			{Vk::DescriptorPoolSize(VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1)}
		));

		// Descriptor Set Layout
		auto vk_descriptorSetLayout = Vk::CreateDescriptorSetLayout(vk_device, Vk::DescriptorSetLayoutCreateInfo(0, {
			Vk::DescriptorSetLayoutBinding(0, VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT),
		}));

		// Pipeline
		auto vk_pipelineLayout = Vk::CreatePipelineLayout(vk_device, Vk::PipelineLayoutCreateInfo({vk_descriptorSetLayout}, {}));

		// Queue
		auto vk_queue = Vk::GetDeviceQueue(vk_device, 0, 0);

		// Command Pool
		auto vk_commandPool = Vk::CreateCommandPool(vk_device, Vk::CommandPoolCreateInfo(VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, 0));
		{
			Vk::ResetCommandPool(vk_device, vk_commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
		}

		// Fence
		auto vk_fence = Vk::CreateFence(vk_device, Vk::FenceCreateInfo(0));

		auto vk_nextImageIndex = Vk::AcquireNextImageKHR(vk_device, vk_swapchain, UINT64_MAX, VK_NULL_HANDLE, vk_fence);
		
		Vk::WaitForFences(vk_device, {vk_fence}, VK_FALSE, UINT64_MAX);
		Vk::ResetFences(vk_device, {vk_fence});

		Size i = 0;
		for (auto &objectMemory : scene->objects)
		{
			auto model = objectMemory->GetModel();
			auto geometry = model->GetGeometry();

			// Data
			Size vertexStride = sizeof(float)* 2;
			Vector<UInt8> vertices(vertexStride * 3);
			{
				*reinterpret_cast<float*>(vertices.data() + vertexStride * 0 + 0)		= -0.5f;
				*reinterpret_cast<float*>(vertices.data() + vertexStride * 0 + 4)		= +0.5f;

				*reinterpret_cast<float*>(vertices.data() + vertexStride * 1 + 0)		= +0.5f;
				*reinterpret_cast<float*>(vertices.data() + vertexStride * 1 + 4)		= +0.5f;
		
				*reinterpret_cast<float*>(vertices.data() + vertexStride * 2 + 0)		= +0.0f;
				*reinterpret_cast<float*>(vertices.data() + vertexStride * 2 + 4)		= -0.5f;
			}
			Size verticesMemoryTotalSize = sizeof(UInt8) * vertices.size();
			Vector<UInt32> indices(3);
			{
				indices[0] = 0;
				indices[1] = 1;
				indices[2] = 2;
			}
			Size indicesTotalSize = sizeof(UInt32)* indices.size();
			Size uniformsTotalSize = sizeof(Float32)* 16;

			// Buffers
			auto vk_vertexBuffer = Vk::CreateBuffer(vk_device, Vk::BufferCreateInfo(0, verticesMemoryTotalSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
			auto vk_vertexBufferDeviceMemory = [&](){
				auto vk_memoryRequirements = Vk::GetBufferMemoryRequirements(vk_device, vk_vertexBuffer);
				auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
					vk_memoryRequirements.size,
					getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
				));

				auto data = reinterpret_cast<Memory<UInt8>>(Vk::MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0));

				CopyMemory(data, vertices.data(), verticesMemoryTotalSize);

				Vk::UnmapMemory(vk_device, vk_deviceMemory);

				Vk::BindBufferMemory(vk_device, vk_vertexBuffer, vk_deviceMemory);

				return vk_deviceMemory;
			}();
			auto vk_indexBuffer = Vk::CreateBuffer(vk_device, Vk::BufferCreateInfo(0, indicesTotalSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
			auto vk_indexBufferDeviceMemory = [&]()
			{
				auto vk_memoryRequirements = Vk::GetBufferMemoryRequirements(vk_device, vk_indexBuffer);
				auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
					vk_memoryRequirements.size,
					getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
				));

				auto data = reinterpret_cast<Memory<UInt32>>(Vk::MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0));

				CopyMemory(data, indices.data(), indicesTotalSize);

				Vk::UnmapMemory(vk_device, vk_deviceMemory);

				Vk::BindBufferMemory(vk_device, vk_indexBuffer, vk_deviceMemory);

				return vk_deviceMemory;
			}();
			auto vk_uniformBuffer = Vk::CreateBuffer(vk_device, Vk::BufferCreateInfo(0, uniformsTotalSize, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE));
			auto vk_uniformBufferDeviceMemory = [&]()
			{
				auto vk_memoryRequirements = Vk::GetBufferMemoryRequirements(vk_device, vk_uniformBuffer);
				auto vk_deviceMemory = Vk::AllocateMemory(vk_device, Vk::MemoryAllocateInfo(
					vk_memoryRequirements.size,
					getDeviceMemoryIndex(VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
				));

				auto data = reinterpret_cast<Memory<Float32>>(Vk::MapMemory(vk_device, vk_deviceMemory, 0, VK_WHOLE_SIZE, 0));

				auto modelMatrix = objectMemory->GetMMat();
				auto viewMatrix = camera->GetVMat();
				auto viewProjectionMatrix = Perspective(60.0f, aspect, 0.1f, 1000.0f) * Scale4(Vec3(1.0f, 1.0f, 1.0f)) * viewMatrix;
				auto mat = viewProjectionMatrix * modelMatrix;

				CopyMemory(data, reinterpret_cast<Memory<Float32>>(&mat), 16);

				Vk::UnmapMemory(vk_device, vk_deviceMemory);

				Vk::BindBufferMemory(vk_device, vk_uniformBuffer, vk_deviceMemory);

				return vk_deviceMemory;
			}();

			// Shaders
			auto vk_vertexShaderModule = Vk::CreateShaderModule(vk_device, Vk::ShaderModuleCreateInfo(Move(loadShader("Media/Shaders/Vulkan/Example_Graphics/triangle.spir-v.vertex-shader"))));
			auto vk_fragmentShaderModule = Vk::CreateShaderModule(vk_device, Vk::ShaderModuleCreateInfo(Move(loadShader("Media/Shaders/Vulkan/Example_Graphics/triangle.spir-v.fragment-shader"))));

			// Descriptor Set
			auto vk_descriptorSets = Move(Vk::AllocateDescriptorSets(vk_device, Vk::DescriptorSetAllocateInfo(vk_descriptorPool, {vk_descriptorSetLayout})));
			auto &vk_descriptorSet = vk_descriptorSets[0];
			{
				Vk::UpdateDescriptorSets(vk_device, {
					Vk::WriteDescriptorSet(vk_descriptorSet, 0, 0, VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, {Vk::DescriptorBufferInfo(vk_uniformBuffer)}),
				}, {});
			}

			// Pipeline
			auto vk_pipelines = Move(Vk::CreateGraphicsPipelines(vk_device, VK_NULL_HANDLE,
				{
					Vk::GraphicsPipelineCreateInfo(
						0,
						{
							Vk::PipelineShaderStageCreateInfo(VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT, vk_vertexShaderModule, "main"),
							Vk::PipelineShaderStageCreateInfo(VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT, vk_fragmentShaderModule, "main"),
						},
						Vk::PipelineVertexInputStateCreateInfo(
							{ Vk::VertexInputBindingDescription(0, vertexStride, VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX) },
							{ Vk::VertexInputAttributeDescription(0, 0, VkFormat::VK_FORMAT_R32G32_SFLOAT, 0) }
						),
						Vk::PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE),
						Vk::PipelineViewportStateCreateInfo(
							{ Vk::Viewport(0, 0, static_cast<float>(vk_surfaceCapabilities.currentExtent.width), static_cast<float>(vk_surfaceCapabilities.currentExtent.height), 0.0f, 1.0f) },
							{ Vk::Rect2D(Vk::Offset2D(0, 0), Vk::Extent2D(vk_surfaceCapabilities.currentExtent.width, vk_surfaceCapabilities.currentExtent.height)) }
						),
						Vk::PipelineRasterizationStateCreateInfo(
							VK_FALSE, VK_FALSE,
							VkPolygonMode::VK_POLYGON_MODE_FILL, VkCullModeFlagBits::VK_CULL_MODE_NONE, VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE,
							VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f
						),
						Vk::PipelineMultisampleStateCreateInfo(
							VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
							VK_FALSE, 0.0f, nullptr, VK_FALSE, VK_FALSE
						),
						Vk::PipelineDepthStencilStateCreateInfo(
							VK_FALSE, VK_FALSE, VkCompareOp::VK_COMPARE_OP_ALWAYS, VK_FALSE,
							VK_FALSE,
							Vk::StencilOpState(VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkCompareOp::VK_COMPARE_OP_ALWAYS, 0, 0, 0),
							Vk::StencilOpState(VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkStencilOp::VK_STENCIL_OP_KEEP, VkCompareOp::VK_COMPARE_OP_ALWAYS, 0, 0, 0),
							0.0f,
							0.0f
						),
						Vk::PipelineColorBlendStateCreateInfo(
							VK_FALSE, VkLogicOp::VK_LOGIC_OP_CLEAR,
							{
								Vk::PipelineColorBlendAttachmentState(
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

			Vk::DestroyShaderModule(vk_device, vk_vertexShaderModule);
			Vk::DestroyShaderModule(vk_device, vk_fragmentShaderModule);

			// Command Buffers
			auto vk_commandBuffers = Move(Vk::AllocateCommandBuffers(vk_device, Vk::CommandBufferAllocateInfo(vk_commandPool, VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY, vk_framebuffers.size())));
			{
				for (Size i = 0; i < vk_commandBuffers.size(); ++i)
				{
					auto &vk_commandBuffer = vk_commandBuffers[i];
					auto &vk_framebuffer = vk_framebuffers[i];

					Vk::ResetCommandBuffer(vk_commandBuffer, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

					Vk::BeginCommandBuffer(vk_commandBuffer, Vk::CommandBufferBeginInfo(0));
			
					Vk::CmdBeginRenderPass(vk_commandBuffer, Vk::RenderPassBeginInfo(
						vk_renderPass,
						vk_framebuffer,
						Vk::Rect2D(Vk::Offset2D(0, 0), vk_surfaceCapabilities.currentExtent), {
							Vk::ClearValue::Color(1.0f, 0.0f, 0.0f, 1.0f),
						}),
						VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
					);

					Vk::CmdBindPipeline(vk_commandBuffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipeline);
				
					Vk::CmdBindVertexBuffers(vk_commandBuffer, 0, 1, {vk_vertexBuffer}, {0});
					Vk::CmdBindIndexBuffer(vk_commandBuffer, vk_indexBuffer, 0, VkIndexType::VK_INDEX_TYPE_UINT32);
				
					Vk::CmdBindDescriptorSets(vk_commandBuffer, VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, vk_pipelineLayout, 0, {vk_descriptorSet}, {});
				
					Vk::CmdDrawIndexed(vk_commandBuffer, indices.size(), 1, 0, 0, 0);

					Vk::CmdEndRenderPass(vk_commandBuffer);

					Vk::EndCommandBuffer(vk_commandBuffer);
				}
			}

			auto &vk_commandBuffer = vk_commandBuffers[vk_nextImageIndex];

			Vk::QueueSubmit(vk_queue, {Vk::SubmitInfo({vk_commandBuffer})});
			Vk::QueueWaitIdle(vk_queue);

			// Cleanup
			Vk::FreeCommandBuffers(vk_device, vk_commandPool, vk_commandBuffers);
			Vk::DestroyPipeline(vk_device, vk_pipeline);
			Vk::FreeDescriptorSets(vk_device, vk_descriptorPool, vk_descriptorSets);
			Vk::FreeMemory(vk_device, vk_vertexBufferDeviceMemory); Vk::DestroyBuffer(vk_device, vk_vertexBuffer);
			Vk::FreeMemory(vk_device, vk_indexBufferDeviceMemory); Vk::DestroyBuffer(vk_device, vk_indexBuffer);
			Vk::FreeMemory(vk_device, vk_uniformBufferDeviceMemory); Vk::DestroyBuffer(vk_device, vk_uniformBuffer);

			++i;
		}
		
		Vk::QueuePresentKHR(vk_queue, Vk::PresentInfoKHR({}, {vk_swapchain}, {vk_nextImageIndex}));

		// Cleanup
		Vk::DestroyFence(vk_device, vk_fence);
		Vk::DestroyCommandPool(vk_device, vk_commandPool); // TODO: crash when attempting to destroy pool without any buffers allocated
		Vk::DestroyPipelineLayout(vk_device, vk_pipelineLayout);
		Vk::DestroyDescriptorSetLayout(vk_device, vk_descriptorSetLayout);
		Vk::DestroyDescriptorPool(vk_device, vk_descriptorPool);
		Vk::DestroyRenderPass(vk_device, vk_renderPass);
		Vk::DestroyRenderPass(vk_device, vk_renderPass2);
		for (auto &vk_framebuffer : vk_framebuffers)
		{
			Vk::DestroyFramebuffer(vk_device, vk_framebuffer);
		}
		for (auto &vk_swapchainImageView : vk_swapchainImageViews)
		{
			Vk::DestroyImageView(vk_device, vk_swapchainImageView);
		}
		Vk::DestroySwapchainKHR(vk_device, vk_swapchain);
		Vk::DestroySurfaceKHR(vk_instance, vk_surface);
	}
}
*/

#pragma endregion

#pragma region Engine

#pragma region Context

GreatVEngine2::Graphics::APIs::Vulkan::Engine::Context::Context()
{
	namespace Vk = GreatVEngine2::Vulkan;

	// Instance
	Vector<Memory<const char>> instanceLayers = {
		// "VK_LAYER_LUNARG_api_dump",
		// "VK_LAYER_LUNARG_core_validation",
		// // "VK_LAYER_LUNARG_device_simulation",
		// "VK_LAYER_LUNARG_monitor",
		// "VK_LAYER_LUNARG_object_tracker",
		// "VK_LAYER_LUNARG_parameter_validation",
		// "VK_LAYER_LUNARG_screenshot",
		// // "VK_LAYER_LUNARG_standard_validation",
		// "VK_LAYER_GOOGLE_threading",
		// "VK_LAYER_GOOGLE_unique_objects",
		// // "VK_LAYER_LUNARG_vktrace",
		// "VK_LAYER_RENDERDOC_Capture",
	};
	Vector<Memory<const char>> instanceExtensions = {
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
	};

	vk_instance = Vk::CreateInstance(Vk::InstanceCreateInfo(
		Vk::ApplicationInfo("Application name", 0, "Great V Engine 2", 0, VK_MAKE_VERSION(1, 0, 65)),
		instanceLayers,
		instanceExtensions
	));

	// Physical Device
	auto vk_physicalDevices = Move(Vk::EnumeratePhysicalDevices(vk_instance));
		
	// Devices
	devicesInfos;
	{
		for (Size i = 0; i < vk_physicalDevices.size(); ++i)
		{
			// Physical device
			auto vk_physicalDevice = vk_physicalDevices[i];
			auto vk_physicalDeviceProperties = Vk::GetPhysicalDeviceProperties(vk_physicalDevice);
			auto vk_physicalDeviceQueueFamilyProperties = Vk::GetPhysicalDeviceQueueFamilyProperties(vk_physicalDevice);
			auto vk_physicalDeviceMemoryProperties = Vk::GetPhysicalDeviceMemoryProperties(vk_physicalDevice);
			
			// Device
			Vector<const char*> deviceLayers = {
			};
			Vector<const char*> deviceExtensions = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME,
			};
	
			auto vk_device = Vk::CreateDevice(vk_physicalDevice, Vk::DeviceCreateInfo(
				{ Vk::DeviceQueueCreateInfo(0, {1.0f}), },
				deviceLayers,
				deviceExtensions,
				Vk::PhysicalDeviceFeatures(Initializer<Vk::PhysicalDeviceFeatures::Feature>({
				}))
			));

			devicesInfos.emplace_back(
				vk_physicalDevice,
				vk_physicalDeviceProperties,
				vk_physicalDeviceQueueFamilyProperties,
				vk_physicalDeviceMemoryProperties,
				vk_device
			);
		}
	}
}
GreatVEngine2::Graphics::APIs::Vulkan::Engine::Context::~Context()
{
	namespace Vk = GreatVEngine2::Vulkan;

	for (auto &deviceInfo : devicesInfos)
	{
		auto vk_device = deviceInfo.vk_device;
		
		Vk::DestroyDevice(vk_device);
	}

	Vk::DestroyInstance(vk_instance);
}

#pragma endregion


GreatVEngine2::Graphics::APIs::Vulkan::Engine::Engine(const StrongPointer<Engine>& this_, const StrongPointer<Device>& device_):
	Graphics::Engine(this_),
	device(device_),
	method(Make<ForwardMethod>(this_)),
	context(MakeConstant<Context>())
{
}

GreatVEngine2::Memory<GreatVEngine2::Graphics::APIs::Vulkan::Engine::Context> GreatVEngine2::Graphics::APIs::Vulkan::Engine::GetContext() const
{
	return context.GetValue();
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::Output> GreatVEngine2::Graphics::APIs::Vulkan::Engine::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	auto output = method->Render(scene_, camera_);
	
	return Move(output);
}

#pragma endregion

#pragma region Method

GreatVEngine2::Graphics::APIs::Vulkan::Method::Method(const StrongPointer<Method>& this_, const StrongPointer<Engine>& engine_):
	This(this_),
	engine(engine_)
{
}

#pragma endregion

#pragma region Methods

#pragma region Forward

#pragma region Output

GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Output::Output(const StrongPointer<Output>& this_, const StrongPointer<Renderer>& renderer_, const StrongPointer<Camera>& camera_):
	Graphics::Output(this_),
	renderer(renderer_),
	camera(camera_)
{
}

void GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Output::SignalPresented(const StrongPointer<View>& view_)
{
	if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
	{
		auto viewMemory = windowsView.GetValue();

		renderer->PresentOn(viewMemory, camera);
	}
	else
	{
		throw NotImplementedException();
	}
}

#pragma endregion

#pragma region Renderer

GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Renderer::Renderer(const StrongPointer<Renderer>& this_, const Memory<Scene>& scene_, const Memory<ForwardMethod>& method_):
	This(this_),
	method(method_),
	scene(scene_),
	sceneVersion(scene_->GetVersion())
{
	ForceUpdateSceneGraph();
}

void GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Renderer::ForceUpdateSceneGraph()
{
	// TODO
}
void GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Renderer::UpdateSceneGraph()
{
	auto currentSceneVersion = scene->GetVersion();

	if (currentSceneVersion != sceneVersion)
	{
		ForceUpdateSceneGraph();

		sceneVersion = currentSceneVersion;
	}
}

void GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Renderer::PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_)
{
	if (!method->engine->device->isPresentationSupported)
	{
		throw Exception();
	}

	UpdateSceneGraph();

	auto surfaceHoder = method->engine->device->driver->GetSurface(view_->GetThis<View>());
	auto surfaceHolderMemory = surfaceHoder.GetValue();
	auto surfaceInfo = method->engine->device->GetSurfaceInfo(surfaceHolderMemory);
	auto &vk_surfaceCapabilities = surfaceInfo->vk_surfaceCapabilities;
	auto &vk_surfaceFormats = surfaceInfo->vk_surfaceFormats;
	auto vk_surfaceFormat = vk_surfaceFormats[0]; // TODO: do something with thit
	auto swapchainHolder = method->engine->device->GetSwapchain(surfaceHolderMemory, surfaceInfo, vk_surfaceFormat);
	
	// Global objects
	auto vk_device = method->engine->device->vk_device;
	auto vk_surface = surfaceHoder->vk_surface;
	auto vk_swapchain = swapchainHolder->vk_swapchain;
	auto &vk_swapchainImageViews = swapchainHolder->vk_swapchainImageViews;


	// RenderPass
	auto vk_renderPass = Vk::CreateRenderPass(vk_device, Vk::RenderPassCreateInfo(
		{
			Vk::AttachmentDescription(
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
			Vk::SubpassDescription(VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, {
				Vk::AttachmentReference(0, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL),
			})
		}
	));

	// Fence
	auto vk_fence = Vk::CreateFence(vk_device, Vk::FenceCreateInfo(0));

	// Current image
	auto vk_nextImageIndex = Vk::AcquireNextImageKHR(vk_device, vk_swapchain, UINT64_MAX, VK_NULL_HANDLE, vk_fence);

	Vk::WaitForFences(vk_device, {vk_fence}, VK_FALSE, UINT64_MAX);
	Vk::ResetFences(vk_device, {vk_fence});

	Vk::DestroyFence(vk_device, vk_fence);

	// Image View
	auto vk_swapchainImageView = vk_swapchainImageViews[vk_nextImageIndex];

	// Framebuffer
	auto vk_framebuffer = Vk::CreateFramebuffer(vk_device, Vk::FramebufferCreateInfo(vk_renderPass, {vk_swapchainImageView}, vk_surfaceCapabilities.currentExtent.width, vk_surfaceCapabilities.currentExtent.height, 1));

	// Queue
	auto vk_queue = Vk::GetDeviceQueue(vk_device, 0, 0);

	// Command Pool
	auto vk_commandPool = Vk::CreateCommandPool(vk_device, Vk::CommandPoolCreateInfo(VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, 0));
	{
		Vk::ResetCommandPool(vk_device, vk_commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	}

	// Command Buffer
	auto vk_commandBuffer = Vk::AllocateCommandBuffer(vk_device, vk_commandPool, VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	{
		Vk::ResetCommandBuffer(vk_commandBuffer, VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
		Vk::BeginCommandBuffer(vk_commandBuffer, Vk::CommandBufferBeginInfo(0));
		Vk::CmdBeginRenderPass(vk_commandBuffer, Vk::RenderPassBeginInfo(
			vk_renderPass,
			vk_framebuffer,
			Vk::Rect2D(Vk::Offset2D(0, 0), vk_surfaceCapabilities.currentExtent), {
				Vk::ClearValue::Color(1.0f, 0.0f, 0.0f, 1.0f),
			}),
			VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE
		);
		Vk::CmdEndRenderPass(vk_commandBuffer);
		Vk::EndCommandBuffer(vk_commandBuffer);
	}

	Vk::QueueSubmit(vk_queue, {Vk::SubmitInfo({vk_commandBuffer})});
	Vk::QueueWaitIdle(vk_queue);
	Vk::QueuePresentKHR(vk_queue, Vk::PresentInfoKHR({}, {vk_swapchain}, {vk_nextImageIndex}));

	Vk::FreeCommandBuffer(vk_device, vk_commandPool, vk_commandBuffer);
	Vk::DestroyCommandPool(vk_device, vk_commandPool);
	Vk::DestroyFramebuffer(vk_device, vk_framebuffer);
	Vk::DestroyRenderPass(vk_device, vk_renderPass);
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Output> GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Renderer::Render(const StrongPointer<Camera>& camera_)
{
	auto output = Make<Output>(GetThis<Renderer>(), camera_);
	
	return Move(output);
}

#pragma endregion


GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::ForwardMethod(const StrongPointer<ForwardMethod>& this_, const StrongPointer<Engine>& engine_):
	Method(this_, engine_)
{
}

GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::RendererIt GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::FindOrCreate(const Memory<Scene>& sceneMemory_)
{
	auto it = renderersLookup.find(sceneMemory_);
	
	if (it == renderersLookup.end())
	{
		auto nIt = renderersLookup.insert({sceneMemory_, Make<Renderer>(sceneMemory_, this)});
	
		return nIt.first;
	}
	else
	{
		return it;
	}
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::Output> GreatVEngine2::Graphics::APIs::Vulkan::ForwardMethod::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	auto sceneMemory = scene_.GetValue();
	auto rendererIt = FindOrCreate(sceneMemory);
	auto renderer = (*rendererIt).second;
	
	auto output = renderer->Render(camera_);
	
	return Move(output);
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


