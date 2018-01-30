#pragma region Include

#pragma once

#include "Header.hpp"
#include "Exception.hpp"

#pragma endregion


namespace GreatVEngine2
{
	namespace Vulkan // functions wrappers
	{
		// handles wrappers
		class InstanceHandle
		{
		public:
			using Value = VkInstance;
		protected:
			Value value;
		public:
			inline InstanceHandle() = default;
			inline explicit InstanceHandle(const Value& value_):
				value(value_)
			{
			}
			inline InstanceHandle(const InstanceHandle&) = default;
			inline ~InstanceHandle() = default;
		public:
			inline InstanceHandle& operator = (const InstanceHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class PhysicalDeviceHandle
		{
		public:
			using Value = VkPhysicalDevice;
		protected:
			Value value;
		public:
			inline PhysicalDeviceHandle() = default;
			inline explicit PhysicalDeviceHandle(const Value& value_):
				value(value_)
			{
			}
			inline PhysicalDeviceHandle(const PhysicalDeviceHandle&) = default;
			inline ~PhysicalDeviceHandle() = default;
		public:
			inline PhysicalDeviceHandle& operator = (const PhysicalDeviceHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class DeviceHandle
		{
		public:
			using Value = VkDevice;
		protected:
			Value value;
		public:
			inline DeviceHandle() = default;
			inline explicit DeviceHandle(const Value& value_):
				value(value_)
			{
			}
			inline DeviceHandle(const DeviceHandle&) = default;
			inline ~DeviceHandle() = default;
		public:
			inline DeviceHandle& operator = (const DeviceHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class QueueHandle
		{
		public:
			using Value = VkQueue;
		protected:
			Value value;
		public:
			inline QueueHandle() = default;
			inline explicit QueueHandle(const Value& value_):
				value(value_)
			{
			}
			inline QueueHandle(const QueueHandle&) = default;
			inline ~QueueHandle() = default;
		public:
			inline QueueHandle& operator = (const QueueHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class CommandPoolHandle
		{
		public:
			using Value = VkCommandPool;
		protected:
			Value value;
		public:
			inline CommandPoolHandle() = default;
			inline explicit CommandPoolHandle(const Value& value_):
				value(value_)
			{
			}
			inline CommandPoolHandle(const CommandPoolHandle&) = default;
			inline ~CommandPoolHandle() = default;
		public:
			inline CommandPoolHandle& operator = (const CommandPoolHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class CommandBufferHandle
		{
		public:
			using Value = VkCommandBuffer;
		protected:
			Value value;
		public:
			inline CommandBufferHandle() = default;
			inline explicit CommandBufferHandle(const Value& value_):
				value(value_)
			{
			}
			inline CommandBufferHandle(const CommandBufferHandle&) = default;
			inline ~CommandBufferHandle() = default;
		public:
			inline CommandBufferHandle& operator = (const CommandBufferHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class RenderPassHandle
		{
		public:
			using Value = VkRenderPass;
		protected:
			Value value;
		public:
			inline RenderPassHandle() = default;
			inline explicit RenderPassHandle(const Value& value_):
				value(value_)
			{
			}
			inline RenderPassHandle(const RenderPassHandle&) = default;
			inline ~RenderPassHandle() = default;
		public:
			inline RenderPassHandle& operator = (const RenderPassHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class ImageHandle
		{
		public:
			using Value = VkImage;
		protected:
			Value value;
		public:
			inline ImageHandle() = default;
			inline explicit ImageHandle(const Value& value_):
				value(value_)
			{
			}
			inline ImageHandle(const ImageHandle&) = default;
			inline ~ImageHandle() = default;
		public:
			inline ImageHandle& operator = (const ImageHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class ImageViewHandle
		{
		public:
			using Value = VkImageView;
		protected:
			Value value;
		public:
			inline ImageViewHandle() = default;
			inline explicit ImageViewHandle(const Value& value_):
				value(value_)
			{
			}
			inline ImageViewHandle(const ImageViewHandle&) = default;
			inline ~ImageViewHandle() = default;
		public:
			inline ImageViewHandle& operator = (const ImageViewHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class FramebufferHandle
		{
		public:
			using Value = VkFramebuffer;
		protected:
			Value value;
		public:
			inline FramebufferHandle() = default;
			inline explicit FramebufferHandle(const Value& value_):
				value(value_)
			{
			}
			inline FramebufferHandle(const FramebufferHandle&) = default;
			inline ~FramebufferHandle() = default;
		public:
			inline FramebufferHandle& operator = (const FramebufferHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
		class FenceHandle
		{
		public:
			using Value = VkFence;
		protected:
			Value value;
		public:
			inline FenceHandle() = default;
			inline explicit FenceHandle(const Value& value_):
				value(value_)
			{
			}
			inline FenceHandle(const FenceHandle&) = default;
			inline ~FenceHandle() = default;
		public:
			inline FenceHandle& operator = (const FenceHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};


#if VK_USE_PLATFORM_WIN32_KHR
		class SurfaceKHRHandle
		{
		public:
			using Value = VkSurfaceKHR;
		protected:
			Value value;
		public:
			inline SurfaceKHRHandle() = default;
			inline explicit SurfaceKHRHandle(const Value& value_):
				value(value_)
			{
			}
			inline SurfaceKHRHandle(const SurfaceKHRHandle&) = default;
			inline ~SurfaceKHRHandle() = default;
		public:
			inline SurfaceKHRHandle& operator = (const SurfaceKHRHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
#endif
#if VK_USE_PLATFORM_WIN32_KHR
		class SwapchainKHRHandle
		{
		public:
			using Value = VkSwapchainKHR;
		protected:
			Value value;
		public:
			inline SwapchainKHRHandle() = default;
			inline explicit SwapchainKHRHandle(const Value& value_):
				value(value_)
			{
			}
			inline explicit SwapchainKHRHandle(const Null&):
				SwapchainKHRHandle(static_cast<Value>(VK_NULL_HANDLE))
			{
			}
			inline SwapchainKHRHandle(const SwapchainKHRHandle&) = default;
			inline ~SwapchainKHRHandle() = default;
		public:
			inline SwapchainKHRHandle& operator = (const SwapchainKHRHandle&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
			inline operator Value*()
			{
				return &value;
			}
			inline operator const Value*() const
			{
				return &value;
			}
		};
#endif


		// structures wrappers
		class ApplicationInfo:
			public VkApplicationInfo
		{
		public:
			using APIVersion = decltype(VkApplicationInfo::apiVersion);
		protected:
			const String applicationNameContainer;
			const String engineNameContainer;
		public:
			inline ApplicationInfo() = delete;
			inline ApplicationInfo(const String& applicationName_, const Size& applicationVersion_, const String& engineName_, const Size& engineVersion_, const APIVersion& apiVersion_);
			inline ApplicationInfo(const ApplicationInfo&) = delete;
			inline ~ApplicationInfo() = default;
		public:
			inline ApplicationInfo& operator = (const ApplicationInfo&) = delete;
		};
		class PhysicalDeviceFeatures:
			public VkPhysicalDeviceFeatures
		{
		public:
			enum class Feature
			{
				RobustBufferAccess,
				FullDrawIndexUint32,
				ImageCubeArray,
				IndependentBlend,
				GeometryShader,
				TessellationShader,
				SampleRateShading,
				DualSrcBlend,
				LogicOp,
				MultiDrawIndirect,
				DrawIndirectFirstInstance,
				DepthClamp,
				DepthBiasClamp,
				FillModeNonSolid,
				DepthBounds,
				WideLines,
				LargePoints,
				AlphaToOne,
				MultiViewport,
				SamplerAnisotropy,
				TextureCompressionETC2,
				TextureCompressionASTC_LDR,
				TextureCompressionBC,
				OcclusionQueryPrecise,
				PipelineStatisticsQuery,
				VertexPipelineStoresAndAtomics,
				FragmentStoresAndAtomics,
				ShaderTessellationAndGeometryPointSize,
				ShaderImageGatherExtended,
				ShaderStorageImageExtendedFormats,
				ShaderStorageImageMultisample,
				ShaderStorageImageReadWithoutFormat,
				ShaderStorageImageWriteWithoutFormat,
				ShaderUniformBufferArrayDynamicIndexing,
				ShaderSampledImageArrayDynamicIndexing,
				ShaderStorageBufferArrayDynamicIndexing,
				ShaderStorageImageArrayDynamicIndexing,
				ShaderClipDistance,
				ShaderCullDistance,
				ShaderFloat64,
				ShaderInt64,
				ShaderInt16,
				ShaderResourceResidency,
				ShaderResourceMinLod,
				SparseBinding,
				SparseResidencyBuffer,
				SparseResidencyImage2D,
				SparseResidencyImage3D,
				SparseResidency2Samples,
				SparseResidency4Samples,
				SparseResidency8Samples,
				SparseResidency16Samples,
				SparseResidencyAliased,
				VariableMultisampleRate,
				InheritedQueries,
			};
		protected:
			inline static VkBool32 Has(const Initializer<Feature>& features_, const Feature& feature_);
		public:
			inline PhysicalDeviceFeatures() = delete;
			inline PhysicalDeviceFeatures(const Initializer<Feature>& features_);
			inline PhysicalDeviceFeatures(const PhysicalDeviceFeatures&) = delete;
			inline ~PhysicalDeviceFeatures() = default;
		public:
			inline PhysicalDeviceFeatures& operator = (const PhysicalDeviceFeatures&) = delete;
		};
		class AttachmentDescription:
			public VkAttachmentDescription
		{
		public:
			inline AttachmentDescription() = delete;
			inline AttachmentDescription( // TODO: add flags
				const VkFormat& format_,
				const VkSampleCountFlagBits& samples_,
				const VkAttachmentLoadOp& loadOp_,
				const VkAttachmentStoreOp& storeOp_,
				const VkAttachmentLoadOp& stencilLoadOp_,
				const VkAttachmentStoreOp& stencilStoreOp_,
				const VkImageLayout& initialLayout_,
				const VkImageLayout& finalLayout_
				);
			inline AttachmentDescription(const AttachmentDescription&) = delete;
			inline ~AttachmentDescription() = default;
		public:
			inline AttachmentDescription& operator = (const AttachmentDescription&) = delete;
		};
		class AttachmentReference:
			public VkAttachmentReference
		{
		public:
			inline AttachmentReference() = delete;
			inline AttachmentReference(const decltype(attachment)& attachment_, const VkImageLayout& layout_);
			inline AttachmentReference(const AttachmentReference&) = delete;
			inline ~AttachmentReference() = default;
		public:
			inline AttachmentReference& operator = (const AttachmentReference&) = delete;
		};
		class SubpassDescription:
			public VkSubpassDescription
		{
		public:
			inline SubpassDescription() = delete;
			inline SubpassDescription(const VkPipelineBindPoint& pipelineBindPoint_, const Vector<VkAttachmentReference>& colorAttachments_);
			inline SubpassDescription(const VkPipelineBindPoint& pipelineBindPoint_, const Vector<VkAttachmentReference>& colorAttachments_, const VkAttachmentReference& depthStencilAttachment_);
			inline SubpassDescription(
				const VkPipelineBindPoint& pipelineBindPoint_,
				const Vector<VkAttachmentReference>& inputAttachments_,
				const Vector<VkAttachmentReference>& colorAttachments_,
				const Vector<VkAttachmentReference>& resolveAttachments_,
				const VkAttachmentReference* depthStencilAttachment_,
				const Vector<uint32_t>& preserveAttachments_
				);
			inline SubpassDescription(const SubpassDescription&) = delete;
			inline ~SubpassDescription() = default;
		public:
			inline SubpassDescription& operator = (const SubpassDescription&) = delete;
		};
		class CommandBufferBeginInfo:
			public VkCommandBufferBeginInfo
		{
		public:
			inline CommandBufferBeginInfo() = delete;
			inline CommandBufferBeginInfo(const VkCommandBufferUsageFlags& flags_, const VkCommandBufferInheritanceInfo& inheritanceInfo_);
			inline CommandBufferBeginInfo(const VkCommandBufferUsageFlags& flags_, const VkCommandBufferInheritanceInfo* inheritanceInfo_ = nullptr);
			inline CommandBufferBeginInfo(const CommandBufferBeginInfo&) = delete;
			inline ~CommandBufferBeginInfo() = default;
		public:
			inline CommandBufferBeginInfo& operator = (const CommandBufferBeginInfo&) = delete;
		};
		class RenderPassBeginInfo:
			public VkRenderPassBeginInfo
		{
		public:
			inline RenderPassBeginInfo() = delete;
			inline RenderPassBeginInfo(const RenderPassHandle& renderPassHandle_, const FramebufferHandle& framebufferHandle_, const VkRect2D& vk_renderArea_, const Vector<VkClearValue>& vk_clearValues_);
			inline RenderPassBeginInfo(const RenderPassBeginInfo&) = delete;
			inline ~RenderPassBeginInfo() = default;
		public:
			inline RenderPassBeginInfo& operator = (const RenderPassBeginInfo&) = delete;
		};
		class SubmitInfo:
			public VkSubmitInfo
		{
		protected:
			const Vector<VkCommandBuffer> vk_commandBuffers;
		public:
			inline SubmitInfo() = delete;
			inline SubmitInfo(
				const Vector<CommandBufferHandle>& commandBuffersHandles_,
				// const Vector<VkSemaphore>& vk_waitSemaphores_ = Vector<VkSemaphore>(),
				const Vector<VkPipelineStageFlags>& vk_waitMasks_ = Vector<VkPipelineStageFlags>()
				// const Vector<VkSemaphore>& vk_signalSemaphores_ = Vector<VkSemaphore>()
			);
			inline SubmitInfo(const SubmitInfo&) = delete;
			inline ~SubmitInfo() = default;
		public:
			inline SubmitInfo& operator = (const SubmitInfo&) = delete;
		};

		class Offset2D:
			public VkOffset2D
		{
		public:
			using X = decltype(x);
			using Y = decltype(y);
		public:
			inline Offset2D() = delete;
			inline Offset2D(const X& x_, const Y& y_);
			inline Offset2D(const Offset2D&) = delete;
			inline ~Offset2D() = default;
		public:
			inline Offset2D& operator = (const Offset2D&) = delete;
		};
		class Offset3D:
			public VkOffset3D
		{
		public:
			using X = decltype(x);
			using Y = decltype(y);
			using Z = decltype(z);
		public:
			inline Offset3D() = delete;
			inline Offset3D(const X& x_, const Y& y_, const Z& z_);
			inline Offset3D(const Offset3D&) = delete;
			inline ~Offset3D() = default;
		public:
			inline Offset3D& operator = (const Offset3D&) = delete;
		};
		class Extent2D:
			public VkExtent2D
		{
		public:
			using Width = decltype(width);
			using Height = decltype(height);
		public:
			inline Extent2D() = delete;
			inline Extent2D(const Width& width_, const Height& height_);
			inline Extent2D(const Extent2D&) = delete;
			inline ~Extent2D() = default;
		public:
			inline Extent2D& operator = (const Extent2D&) = delete;
		};
		class Extent3D:
			public VkExtent3D
		{
		public:
			using Width = decltype(width);
			using Height = decltype(height);
			using Depth = decltype(depth);
		public:
			inline Extent3D() = delete;
			inline Extent3D(const Width& width_, const Height& height_, const Depth& depth_);
			inline Extent3D(const VkExtent2D& extent_, const Depth& depth_);
			inline Extent3D(const Extent3D&) = delete;
			inline ~Extent3D() = default;
		public:
			inline Extent3D& operator = (const Extent3D&) = delete;
		};
		class Rect2D:
			public VkRect2D
		{
		public:
			using Offset = decltype(offset);
			using Extent = decltype(extent);
		public:
			inline Rect2D() = delete;
			inline Rect2D(const Offset& offset_, const Extent& extent_);
			inline Rect2D(const Rect2D&) = delete;
			inline ~Rect2D() = default;
		public:
			inline Rect2D& operator = (const Rect2D&) = delete;
		};
		class ComponentMapping:
			public VkComponentMapping
		{
		public:
			inline ComponentMapping() = delete;
			inline ComponentMapping(const VkComponentSwizzle& r_, const VkComponentSwizzle& g_, const VkComponentSwizzle& b_, const VkComponentSwizzle& a_);
			inline ComponentMapping(const ComponentMapping&) = delete;
			inline ~ComponentMapping() = default;
		public:
			inline ComponentMapping& operator = (const ComponentMapping&) = delete;
		};
		class ImageSubresourceRange:
			public VkImageSubresourceRange
		{
		public:
			inline ImageSubresourceRange() = delete;
			inline ImageSubresourceRange(
				VkImageAspectFlags aspectMask_,
				uint32_t baseMipLevel_,
				uint32_t levelCount_,
				uint32_t baseArrayLayer_,
				uint32_t layerCount_
			);
			inline ImageSubresourceRange(const ImageSubresourceRange&) = delete;
			inline ~ImageSubresourceRange() = default;
		public:
			inline ImageSubresourceRange& operator = (const ImageSubresourceRange&) = delete;
		};
		class ClearValue
		{
		public:
			inline static VkClearValue Color(const float& r_, const float& g_, const float& b_, const float& a_);
			inline static VkClearValue DepthStencil(const float& depth_, const uint32_t& stencil_);
		public:
			inline ClearValue() = delete;
			inline ClearValue(const ClearValue&) = delete;
			inline ~ClearValue() = default;
		public:
			inline ClearValue& operator = (const ClearValue&) = delete;
		};

		class InstanceCreateInfo:
			public VkInstanceCreateInfo
		{
		public:
			using LayerName = const char*;
			using ExtensionName = const char*;
			using LayersNames = Vector<LayerName>;
			using ExtensionsNames = Vector<ExtensionName>;
		public:
			inline InstanceCreateInfo() = delete;
			inline InstanceCreateInfo(const LayersNames& enabledLayersNames_, const ExtensionsNames& enabledExtensionsNames_);
			inline InstanceCreateInfo(const VkApplicationInfo& vk_applicationInfo_, const LayersNames& enabledLayersNames_, const ExtensionsNames& enabledExtensionsNames_);
			inline InstanceCreateInfo(const VkApplicationInfo* vk_applicationInfo_, const LayersNames& enabledLayersNames_, const ExtensionsNames& enabledExtensionsNames_);
			inline InstanceCreateInfo(const InstanceCreateInfo&) = delete;
			inline ~InstanceCreateInfo() = default;
		public:
			inline InstanceCreateInfo& operator = (const InstanceCreateInfo&) = delete;
		};
		class DeviceCreateInfo:
			public VkDeviceCreateInfo
		{
		public:
			inline DeviceCreateInfo() = delete;
			inline DeviceCreateInfo(const Vector<VkDeviceQueueCreateInfo>& vk_deviceQueueCreateInfos_, const Vector<const char*>& vk_enabledPhysicalDeviceLayersNames_, const Vector<const char*>& vk_enabledPhysicalDeviceExtensionsNames_, const VkPhysicalDeviceFeatures& vk_physicalDeviceFeatures_);
			inline DeviceCreateInfo(const Vector<VkDeviceQueueCreateInfo>& vk_deviceQueueCreateInfos_, const Vector<const char*>& vk_enabledPhysicalDeviceLayersNames_, const Vector<const char*>& vk_enabledPhysicalDeviceExtensionsNames_, const VkPhysicalDeviceFeatures* vk_physicalDeviceFeatures_);
			inline DeviceCreateInfo(const DeviceCreateInfo&) = delete;
			inline ~DeviceCreateInfo() = default;
		public:
			inline DeviceCreateInfo& operator = (const DeviceCreateInfo&) = delete;
		};
		class DeviceQueueCreateInfo:
			public VkDeviceQueueCreateInfo
		{
		public:
			inline DeviceQueueCreateInfo() = delete;
			inline DeviceQueueCreateInfo(const decltype(VkDeviceQueueCreateInfo::queueFamilyIndex)& queueFamilyIndex_, const Vector<float>& queuePriorities_);
			inline DeviceQueueCreateInfo(const DeviceQueueCreateInfo&) = delete;
			inline ~DeviceQueueCreateInfo() = default;
		public:
			inline DeviceQueueCreateInfo& operator = (const DeviceQueueCreateInfo&) = delete;
		};
		class CommandPoolCreateInfo:
			public VkCommandPoolCreateInfo
		{
		public:
			inline CommandPoolCreateInfo() = delete;
			inline CommandPoolCreateInfo(const VkCommandPoolCreateFlags& flags_, const decltype(queueFamilyIndex)& queueFamilyIndex_);
			inline CommandPoolCreateInfo(const CommandPoolCreateInfo&) = delete;
			inline ~CommandPoolCreateInfo() = default;
		public:
			inline CommandPoolCreateInfo& operator = (const CommandPoolCreateInfo&) = delete;
		};
		class RenderPassCreateInfo:
			public VkRenderPassCreateInfo
		{
		public:
			inline RenderPassCreateInfo() = delete;
			inline RenderPassCreateInfo(const Vector<VkAttachmentDescription>& vk_attachmentDescriptions_, const Vector<VkSubpassDescription>& vk_subpassDescriptions_, const Vector<VkSubpassDependency>& vk_subpassDependencies_ = Vector<VkSubpassDependency>());
			inline RenderPassCreateInfo(const RenderPassCreateInfo&) = delete;
			inline ~RenderPassCreateInfo() = default;
		public:
			inline RenderPassCreateInfo& operator = (const RenderPassCreateInfo&) = delete;
		};
		class ImageViewCreateInfo:
			public VkImageViewCreateInfo
		{
		public:
			inline ImageViewCreateInfo() = delete;
			inline ImageViewCreateInfo(
				const VkImageViewCreateFlags& flags_,
				const ImageHandle& imageHandle_,
				const VkImageViewType& vk_imageViewType_,
				const VkFormat& format_,
				const VkComponentMapping& vk_componentMapping_,
				const VkImageSubresourceRange& vk_imageSubresourceRange_
				);
			inline ImageViewCreateInfo(const ImageViewCreateInfo&) = delete;
			inline ~ImageViewCreateInfo() = default;
		public:
			inline ImageViewCreateInfo& operator = (const ImageViewCreateInfo&) = delete;
		};
		class FramebufferCreateInfo:
			public VkFramebufferCreateInfo
		{
		protected:
			const Vector<VkImageView> attachments;
		public:
			inline FramebufferCreateInfo() = delete;
			inline FramebufferCreateInfo(
				const RenderPassHandle& renderPassHandle_,
				const Vector<ImageViewHandle>& attachments_,
				const decltype(width)& width_,
				const decltype(height)& height_,
				const decltype(layers)& layers_
				);
			inline FramebufferCreateInfo(const FramebufferCreateInfo&) = delete;
			inline ~FramebufferCreateInfo() = default;
		public:
			inline FramebufferCreateInfo& operator = (const FramebufferCreateInfo&) = delete;
		};
		class FenceCreateInfo:
			public VkFenceCreateInfo
		{
		public:
			inline FenceCreateInfo() = delete;
			inline FenceCreateInfo(const VkFenceCreateFlags& flags_);
			inline FenceCreateInfo(const FenceCreateInfo&) = delete;
			inline ~FenceCreateInfo() = default;
		public:
			inline FenceCreateInfo& operator = (const FenceCreateInfo&) = delete;
		};

#if VK_USE_PLATFORM_WIN32_KHR
		class Win32SurfaceCreateInfoKHR:
			public VkWin32SurfaceCreateInfoKHR
		{
		public:
			inline Win32SurfaceCreateInfoKHR() = delete;
			inline Win32SurfaceCreateInfoKHR(const decltype(VkWin32SurfaceCreateInfoKHR::hinstance)& handleInstance_, const decltype(VkWin32SurfaceCreateInfoKHR::hwnd)& handleWindow_);
			inline Win32SurfaceCreateInfoKHR(const Win32SurfaceCreateInfoKHR&) = delete;
			inline ~Win32SurfaceCreateInfoKHR() = default;
		public:
			inline Win32SurfaceCreateInfoKHR& operator = (const Win32SurfaceCreateInfoKHR&) = delete;
		};
#endif
#if VK_USE_PLATFORM_WIN32_KHR
		class SwapchainCreateInfoKHR:
			public VkSwapchainCreateInfoKHR
		{
		public:
			inline SwapchainCreateInfoKHR() = delete;
			inline SwapchainCreateInfoKHR(
				VkSwapchainCreateFlagsKHR		flags_,
				SurfaceKHRHandle				surfaceHandle_,
				uint32_t						minImageCount_,
				VkFormat						imageFormat_,
				VkColorSpaceKHR					imageColorSpace_,
				VkExtent2D						imageExtent_,
				uint32_t						imageArrayLayers_,
				VkImageUsageFlags				imageUsage_,
				VkSharingMode					imageSharingMode_,
				const Vector<uint32_t>&			queueFamilyIndices_,
				VkSurfaceTransformFlagBitsKHR	preTransform_,
				VkCompositeAlphaFlagBitsKHR		compositeAlpha_,
				VkPresentModeKHR				presentMode_,
				VkBool32						clipped_,
				SwapchainKHRHandle				oldSwapchainHandle_
			);
			inline SwapchainCreateInfoKHR(const SwapchainCreateInfoKHR&) = delete;
			inline ~SwapchainCreateInfoKHR() = default;
		public:
			inline SwapchainCreateInfoKHR& operator = (const SwapchainCreateInfoKHR&) = delete;
		};
#endif

		class CommandBufferAllocateInfo:
			public VkCommandBufferAllocateInfo
		{
		public:
			inline CommandBufferAllocateInfo() = delete;
			inline CommandBufferAllocateInfo(const CommandPoolHandle& commandPoolHandle_, const VkCommandBufferLevel& level_, const decltype(commandBufferCount)& commandBufferCount_);
			inline CommandBufferAllocateInfo(const CommandBufferAllocateInfo&) = delete;
			inline ~CommandBufferAllocateInfo() = default;
		public:
			inline CommandBufferAllocateInfo& operator = (const CommandBufferAllocateInfo&) = delete;
		};
		class PresentInfoKHR:
			public VkPresentInfoKHR
		{
		public:
			inline PresentInfoKHR() = delete;
			inline PresentInfoKHR(const Vector<VkSemaphore>& vk_waitSemaphores_, const Vector<VkSwapchainKHR>& vk_swapchains_, const Vector<uint32_t>& vk_nextImageIndices_); // TODO: vk_swapchains_ and vk_nextImageIndices_ should have the same size!
			inline PresentInfoKHR(const PresentInfoKHR&) = delete;
			inline ~PresentInfoKHR() = default;
		public:
			inline PresentInfoKHR& operator = (const PresentInfoKHR&) = delete;
		};



		// enums


		// functions
		// // Instance
		inline Vector<VkLayerProperties> EnumerateInstanceLayerProperties()
		{
			uint32_t vk_instanceLayersPropertiesCount;

			if (auto result = Result(vkEnumerateInstanceLayerProperties(&vk_instanceLayersPropertiesCount, nullptr)))
			{
				Vector<VkLayerProperties> vk_instanceLayersProperties(vk_instanceLayersPropertiesCount);

				if (auto result = Result(vkEnumerateInstanceLayerProperties(&vk_instanceLayersPropertiesCount, vk_instanceLayersProperties.data())))
				{
					return Move(vk_instanceLayersProperties);
				}
				else
				{
					throw Exception(); // TODO
				}
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline InstanceHandle CreateInstance(const InstanceCreateInfo& instanceCreateInfo_)
		{
			InstanceHandle instanceHandle;

			if (auto result = Result(vkCreateInstance(&instanceCreateInfo_, nullptr, instanceHandle)))
			{
				return instanceHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void DestroyInstance(const InstanceHandle& instanceHandle_)
		{
			vkDestroyInstance(instanceHandle_, nullptr);
		}

		// // PhysicalDevices
		inline Vector<PhysicalDeviceHandle> EnumeratePhysicalDevices(const InstanceHandle& instanceHandle_)
		{
			uint32_t vk_physicalDevicesCount;

			if (auto result = Result(vkEnumeratePhysicalDevices(instanceHandle_, &vk_physicalDevicesCount, nullptr)))
			{
				Vector<PhysicalDeviceHandle::Value> vk_physicalDevices(vk_physicalDevicesCount);
				{
					if (auto result = Result(vkEnumeratePhysicalDevices(instanceHandle_, &vk_physicalDevicesCount, vk_physicalDevices.data())))
					{
						auto physicalDevicesHandles = Vector<PhysicalDeviceHandle>(vk_physicalDevicesCount);

						for (Size i = 0; i < vk_physicalDevicesCount; ++i)
						{
							physicalDevicesHandles[i] = PhysicalDeviceHandle(vk_physicalDevices[i]);
						}

						return Move(physicalDevicesHandles);
					}
					else
					{
						throw Exception(); // TODO
					}
				}
			}	
			else
			{
				throw Exception(); // TODO
			}
		}
		inline VkPhysicalDeviceProperties GetPhysicalDeviceProperties(const PhysicalDeviceHandle& physicalDeviceHandle_)
		{
			VkPhysicalDeviceProperties vk_physicalDeviceProperties;

			vkGetPhysicalDeviceProperties(physicalDeviceHandle_, &vk_physicalDeviceProperties);

			return vk_physicalDeviceProperties;
		}
		inline Vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(const PhysicalDeviceHandle& physicalDeviceHandle_)
		{
			uint32_t vk_physicalDeviceQueueFamilyPropertiesCount = 0;

			vkGetPhysicalDeviceQueueFamilyProperties(physicalDeviceHandle_, &vk_physicalDeviceQueueFamilyPropertiesCount, nullptr);

			Vector<VkQueueFamilyProperties> vk_physicalDeviceQueueFamilyProperties(vk_physicalDeviceQueueFamilyPropertiesCount);

			vkGetPhysicalDeviceQueueFamilyProperties(physicalDeviceHandle_, &vk_physicalDeviceQueueFamilyPropertiesCount, vk_physicalDeviceQueueFamilyProperties.data());

			return Move(vk_physicalDeviceQueueFamilyProperties);
		}
		inline VkPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(const PhysicalDeviceHandle& physicalDeviceHandle_)
		{
			VkPhysicalDeviceMemoryProperties vk_physicalDeviceMemoryProperties;

			vkGetPhysicalDeviceMemoryProperties(physicalDeviceHandle_, &vk_physicalDeviceMemoryProperties);

			return Move(vk_physicalDeviceMemoryProperties);
		}
		inline VkFormatProperties GetPhysicalDeviceFormatProperties(const PhysicalDeviceHandle& physicalDeviceHandle_, const VkFormat& vk_format_)
		{
			VkFormatProperties vk_formatProperties;

			vkGetPhysicalDeviceFormatProperties(physicalDeviceHandle_, vk_format_, &vk_formatProperties);

			return vk_formatProperties;
		}

		// // Device
		inline DeviceHandle CreateDevice(const PhysicalDeviceHandle& physicalDeviceHandle_, const DeviceCreateInfo& deviceCreateInfo_)
		{
			DeviceHandle deviceHandle;

			if (auto result = Result(vkCreateDevice(physicalDeviceHandle_, &deviceCreateInfo_, nullptr, deviceHandle)))
			{
				return deviceHandle;
			}
			else
			{
				throw Exception();
			}
		}
		inline void DestroyDevice(const DeviceHandle& deviceHandle_)
		{
			vkDestroyDevice(deviceHandle_, nullptr);
		}

		// Queue
		inline QueueHandle GetDeviceQueue(const DeviceHandle& deviceHandle_, const uint32_t& vk_queueFamilyIndex_, const uint32_t& vk_queueIndex_)
		{
			QueueHandle queueHandle;

			vkGetDeviceQueue(deviceHandle_, vk_queueFamilyIndex_, vk_queueIndex_, queueHandle);

			return queueHandle;
		}
		inline void QueueSubmit(const QueueHandle& queueHandle_, const Vector<VkSubmitInfo>& vk_submitInfos_) // , const VkFence& vk_fence_
		{
			if (auto result = Result(vkQueueSubmit(queueHandle_, vk_submitInfos_.size(), vk_submitInfos_.data(), VK_NULL_HANDLE))); else
			{
				throw Exception(); // TODO
			}
		}
		inline void QueueWaitIdle(const QueueHandle& queueHandle_)
		{
			if (auto result = Result(vkQueueWaitIdle(queueHandle_))); else
			{
				throw Exception(); // TODO
			}
		}
		inline void QueuePresentKHR(const QueueHandle& queueHandle_, const VkPresentInfoKHR& vk_presentInfoKHR_)
		{
			if (auto result = Result(vkQueuePresentKHR(queueHandle_, &vk_presentInfoKHR_))); else
			{
				throw Exception(); // TODO
			}
		}


		// Command Pool
		inline CommandPoolHandle CreateCommandPool(const DeviceHandle& deviceHandle_, const CommandPoolCreateInfo &commandPoolCreateInfo_)
		{
			CommandPoolHandle commandPoolHandle;

			if (auto result = Result(vkCreateCommandPool(deviceHandle_, &commandPoolCreateInfo_, nullptr, commandPoolHandle)))
			{
				return commandPoolHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void ResetCommandPool(const DeviceHandle& deviceHandle_, const CommandPoolHandle& commandPoolHandle_, const VkCommandPoolResetFlags& flags_)
		{
			if (auto result = Result(vkResetCommandPool(deviceHandle_, commandPoolHandle_, flags_))); else
			{
				throw Exception();
			}
		}
		inline void DestroyCommandPool(const DeviceHandle& deviceHandle_, const CommandPoolHandle& commandPoolHandle_)
		{
			vkDestroyCommandPool(deviceHandle_, commandPoolHandle_, nullptr);
		}

		// Command Buffer
		inline Vector<CommandBufferHandle> AllocateCommandBuffers(const DeviceHandle& deviceHandle_, const CommandBufferAllocateInfo& commandBufferAllocateInfo_)
		{
			Vector<VkCommandBuffer> vk_commandBuffers(commandBufferAllocateInfo_.commandBufferCount);

			if (auto result = Result(vkAllocateCommandBuffers(deviceHandle_, &commandBufferAllocateInfo_, vk_commandBuffers.data())))
			{
				Vector<CommandBufferHandle> commandBuffersHandles(commandBufferAllocateInfo_.commandBufferCount);

				for (Size i = 0; i < commandBufferAllocateInfo_.commandBufferCount; ++i)
				{
					commandBuffersHandles[i] = CommandBufferHandle(vk_commandBuffers[i]);
				}

				return Move(commandBuffersHandles);
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void ResetCommandBuffer(const CommandBufferHandle& commandBufferHandle_, const VkCommandBufferResetFlags& flags_)
		{
			if (auto result = Result(vkResetCommandBuffer(commandBufferHandle_, flags_))); else
			{
				throw Exception(); // TODO
			}
		}
		inline void BeginCommandBuffer(const CommandBufferHandle& commandBufferHandle_, const CommandBufferBeginInfo& commandBufferBeginInfo_)
		{
			if (auto result = Result(vkBeginCommandBuffer(commandBufferHandle_, &commandBufferBeginInfo_)));  else
			{
				throw Exception(); // TODO
			}
		}
		inline void EndCommandBuffer(const CommandBufferHandle& commandBufferHandle_)
		{
			if (auto result = Result(vkEndCommandBuffer(commandBufferHandle_))); else
			{
				throw Exception(); // TODO
			}
		}
		inline void FreeCommandBuffers(const DeviceHandle& deviceHandle_, const CommandPoolHandle& commandPoolHandle_, const Vector<CommandBufferHandle>& commandBuffersHandles_)
		{
			Vector<VkCommandBuffer> vk_commandBuffers(commandBuffersHandles_.size());

			for (Size i = 0; i < commandBuffersHandles_.size(); ++i)
			{
				vk_commandBuffers[i] = commandBuffersHandles_[i];
			}

			vkFreeCommandBuffers(deviceHandle_, commandPoolHandle_, vk_commandBuffers.size(), vk_commandBuffers.data());
		}

		// Commands
		inline void CmdBeginRenderPass(const CommandBufferHandle& commandBufferHandle_, const RenderPassBeginInfo& renderPassBeginInfo_, const VkSubpassContents& vk_subpassContents_)
		{
			vkCmdBeginRenderPass(commandBufferHandle_, &renderPassBeginInfo_, vk_subpassContents_);
		}
		inline void CmdEndRenderPass(const CommandBufferHandle& commandBufferHandle_)
		{
			vkCmdEndRenderPass(commandBufferHandle_);
		}

		// Win32SurfaceKHR
#if VK_USE_PLATFORM_WIN32_KHR

		inline Boolean GetPhysicalDeviceWin32PresentationSupportKHR(const PhysicalDeviceHandle& physicalDeviceHandle_, const Size& queueFamilyIndex_)
		{
			auto vk_isPresentationSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDeviceHandle_, queueFamilyIndex_);

			return Boolean(vk_isPresentationSupport);
		}
		inline SurfaceKHRHandle CreateWin32SurfaceKHR(const InstanceHandle& instanceHandle_, const Win32SurfaceCreateInfoKHR& win32SurfaceCreateInfo_)
		{
			SurfaceKHRHandle surfaceHandle;

			if (auto result = Result(vkCreateWin32SurfaceKHR(instanceHandle_, &win32SurfaceCreateInfo_, nullptr, surfaceHandle)))
			{
				return surfaceHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline Boolean GetPhysicalDeviceSurfaceSupportKHR(const PhysicalDeviceHandle& physicalDeviceHandle_, const decltype(VkDeviceQueueCreateInfo::queueFamilyIndex)& vk_queueFamilyIndex_, const SurfaceKHRHandle& surfaceHandle_)
		{
			VkBool32 vk_isSufraceSupported;

			if (auto result = Result(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDeviceHandle_, vk_queueFamilyIndex_, surfaceHandle_, &vk_isSufraceSupported)))
			{
				return Boolean(vk_isSufraceSupported);
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline VkSurfaceCapabilitiesKHR GetPhysicalDeviceSurfaceCapabilitiesKHR(const PhysicalDeviceHandle& physicalDeviceHandle_, const SurfaceKHRHandle& surfaceHandle_)
		{
			VkSurfaceCapabilitiesKHR vk_surfaceCapabilities;

			if (auto result = Result(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDeviceHandle_, surfaceHandle_, &vk_surfaceCapabilities)))
			{
				return vk_surfaceCapabilities;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline Vector<VkSurfaceFormatKHR> GetPhysicalDeviceSurfaceFormatsKHR(const PhysicalDeviceHandle& physicalDeviceHandle_, const SurfaceKHRHandle& surfaceHandle_)
		{
			uint32_t vk_surfaceFormatsCount;

			if (auto result = Result(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDeviceHandle_, surfaceHandle_, &vk_surfaceFormatsCount, nullptr)))
			{
				Vector<VkSurfaceFormatKHR> vk_surfaceFormats(vk_surfaceFormatsCount);

				if (auto result = Result(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDeviceHandle_, surfaceHandle_, &vk_surfaceFormatsCount, vk_surfaceFormats.data())))
				{
					return Move(vk_surfaceFormats);
				}
				else
				{
					throw Exception(); // TODO
				}
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void DestroySurfaceKHR(const InstanceHandle& instanceHandle_, const SurfaceKHRHandle& surfaceHandle_)
		{
			vkDestroySurfaceKHR(instanceHandle_, surfaceHandle_, nullptr);
		}

#endif

		// VK_KHR_swapchain
#if VK_USE_PLATFORM_WIN32_KHR

		inline SwapchainKHRHandle CreateSwapchainKHR(const DeviceHandle& deviceHandle_, const SwapchainCreateInfoKHR& swapchainCreateInfo_)
		{
			SwapchainKHRHandle swapchainHandle;

			if (auto result = Result(vkCreateSwapchainKHR(deviceHandle_, &swapchainCreateInfo_, nullptr, swapchainHandle)))
			{
				return swapchainHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline Vector<ImageHandle> GetSwapchainImagesKHR(const DeviceHandle& deviceHandle_, const SwapchainKHRHandle& swapchainHandle_)
		{
			uint32_t vk_swapchainImagesCount;

			if (auto result = Result(vkGetSwapchainImagesKHR(deviceHandle_, swapchainHandle_, &vk_swapchainImagesCount, nullptr)))
			{
				Vector<VkImage> vk_swapchainImages(vk_swapchainImagesCount);

				if (auto result = Result(vkGetSwapchainImagesKHR(deviceHandle_, swapchainHandle_, &vk_swapchainImagesCount, vk_swapchainImages.data())))
				{
					Vector<ImageHandle> imagesHandles(vk_swapchainImagesCount);

					for (Size i = 0; i < vk_swapchainImagesCount; ++i)
					{
						imagesHandles[i] = ImageHandle(vk_swapchainImages[i]);
					}

					return Move(imagesHandles);
				}
				else
				{
					throw Exception();
				}
			}
			else
			{
				throw Exception();
			}
		}
		inline uint32_t AcquireNextImageKHR(const DeviceHandle& deviceHandle_, const SwapchainKHRHandle& swapchainHandle_, const FenceHandle& fenceHandle_, const uint64_t& timeout_ = UINT64_MAX)
		{
			uint32_t vk_nextImageIndex;

			if (auto result = Result(vkAcquireNextImageKHR(deviceHandle_, swapchainHandle_, timeout_, VK_NULL_HANDLE, fenceHandle_, &vk_nextImageIndex)))
			{
				return vk_nextImageIndex;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void DestroySwapchainKHR(const DeviceHandle& deviceHandle_, const SwapchainKHRHandle& swapchainHandle_)
		{
			vkDestroySwapchainKHR(deviceHandle_, swapchainHandle_, nullptr);
		}

#endif

		// RenderPass
		inline RenderPassHandle CreateRenderPass(const DeviceHandle& deviceHandle_, const RenderPassCreateInfo& renderPassCreateInfo_)
		{
			RenderPassHandle renderPassHandle;

			if (auto result = Result(vkCreateRenderPass(deviceHandle_, &renderPassCreateInfo_, nullptr, renderPassHandle)))
			{
				return renderPassHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void DestroyRenderPass(const DeviceHandle& deviceHandle_, const RenderPassHandle& renderPassHandle_)
		{
			vkDestroyRenderPass(deviceHandle_, renderPassHandle_, nullptr);
		}

		// Image View
		inline ImageViewHandle CreateImageView(const DeviceHandle& deviceHandle_, const ImageViewCreateInfo& imageViewCreateInfo_)
		{
			ImageViewHandle imageViewHandle;

			if (auto result = Result(vkCreateImageView(deviceHandle_, &imageViewCreateInfo_, nullptr, imageViewHandle)))
			{
				return imageViewHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void DestroyImageView(const DeviceHandle& deviceHandle_, const ImageViewHandle& imageViewHandle_)
		{
			vkDestroyImageView(deviceHandle_, imageViewHandle_, nullptr);
		}

		// Framebuffer
		inline FramebufferHandle CreateFramebuffer(const DeviceHandle& deviceHandle_, const FramebufferCreateInfo& framebufferCreateInfo_)
		{
			FramebufferHandle framebufferHandle;

			if (auto result = Result(vkCreateFramebuffer(deviceHandle_, &framebufferCreateInfo_, nullptr, framebufferHandle)))
			{
				return framebufferHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void DestroyFramebuffer(const DeviceHandle& deviceHandle_, const FramebufferHandle& framebufferHandle_)
		{
			vkDestroyFramebuffer(deviceHandle_, framebufferHandle_, nullptr);
		}

		// Fence
		inline FenceHandle CreateFence(const DeviceHandle& deviceHandle_, const FenceCreateInfo& fenceCreateInfo_)
		{
			FenceHandle fenceHandle;

			if (auto result = Result(vkCreateFence(deviceHandle_, &fenceCreateInfo_, nullptr, fenceHandle)))
			{
				return fenceHandle;
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		inline void ResetFences(const DeviceHandle& deviceHandle_, const Vector<FenceHandle>& fencesHandles_)
		{
			Vector<VkFence> vk_fences(fencesHandles_.size());

			for (Size i = 0; i < fencesHandles_.size(); ++i)
			{
				vk_fences[i] = fencesHandles_[i];
			}

			if (auto result = Result(vkResetFences(deviceHandle_, vk_fences.size(), vk_fences.data()))); else
			{
				throw Exception(); // TODO
			}
		}
		inline bool WaitForFences(const DeviceHandle& deviceHandle_, const Vector<FenceHandle>& fencesHandles_, const Boolean& waitAll_, const uint64_t timeout_ = UINT64_MAX)
		{
			Vector<VkFence> vk_fences(fencesHandles_.size());

			for (Size i = 0; i < fencesHandles_.size(); ++i)
			{
				vk_fences[i] = fencesHandles_[i];
			}

			if (auto result = Result(vkWaitForFences(deviceHandle_, vk_fences.size(), vk_fences.data(), static_cast<VkBool32>(waitAll_), timeout_)))
			{
				return true;
			}
			else
			{
				if (static_cast<const Result::Value>(result) == Result::Value::Timeout)
				{
					return false;
				}
				else
				{
					throw Exception(); // TODO
				}
			}
		}
		inline void DestroyFence(const DeviceHandle& deviceHandle_, const FenceHandle& fenceHandle_)
		{
			vkDestroyFence(deviceHandle_, fenceHandle_, nullptr);
		}
	}
}


#pragma region GreatVEngine2

#pragma region Vulkan

#pragma region ApplicationInfo

GreatVEngine2::Vulkan::ApplicationInfo::ApplicationInfo(const String& applicationName_, const Size& applicationVersion_, const String& engineName_, const Size& engineVersion_, const APIVersion& apiVersion_):
	applicationNameContainer(applicationName_),
	engineNameContainer(engineName_)
{
	// TODO: move to initialization
	sType				= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
	pNext				= nullptr;
	pApplicationName	= applicationNameContainer.c_str();
	applicationVersion	= applicationVersion_;
	pEngineName			= engineNameContainer.c_str();
	engineVersion		= engineVersion_;
	apiVersion			= apiVersion_;
}

#pragma endregion

#pragma region PhysicalDeviceFeatures

inline VkBool32 GreatVEngine2::Vulkan::PhysicalDeviceFeatures::Has(const Initializer<Feature>& features_, const Feature& feature_)
{
	auto it = std::find(features_.begin(), features_.end(), feature_);

	return it != features_.end();
}

inline GreatVEngine2::Vulkan::PhysicalDeviceFeatures::PhysicalDeviceFeatures(const Initializer<Feature>& features_)
{
	robustBufferAccess						= Has(features_, Feature::RobustBufferAccess);
    fullDrawIndexUint32						= Has(features_, Feature::FullDrawIndexUint32);
    imageCubeArray							= Has(features_, Feature::ImageCubeArray);
    independentBlend						= Has(features_, Feature::IndependentBlend);
    geometryShader							= Has(features_, Feature::GeometryShader);
    tessellationShader						= Has(features_, Feature::TessellationShader);
    sampleRateShading						= Has(features_, Feature::SampleRateShading);
    dualSrcBlend							= Has(features_, Feature::DualSrcBlend);
    logicOp									= Has(features_, Feature::LogicOp);
    multiDrawIndirect						= Has(features_, Feature::MultiDrawIndirect);
    drawIndirectFirstInstance				= Has(features_, Feature::DrawIndirectFirstInstance);
    depthClamp								= Has(features_, Feature::DepthClamp);
    depthBiasClamp							= Has(features_, Feature::DepthBiasClamp);
    fillModeNonSolid						= Has(features_, Feature::FillModeNonSolid);
    depthBounds								= Has(features_, Feature::DepthBounds);
    wideLines								= Has(features_, Feature::WideLines);
    largePoints								= Has(features_, Feature::LargePoints);
    alphaToOne								= Has(features_, Feature::AlphaToOne);
    multiViewport							= Has(features_, Feature::MultiViewport);
    samplerAnisotropy						= Has(features_, Feature::SamplerAnisotropy);
    textureCompressionETC2					= Has(features_, Feature::TextureCompressionETC2);
    textureCompressionASTC_LDR				= Has(features_, Feature::TextureCompressionASTC_LDR);
    textureCompressionBC					= Has(features_, Feature::TextureCompressionBC);
    occlusionQueryPrecise					= Has(features_, Feature::OcclusionQueryPrecise);
    pipelineStatisticsQuery					= Has(features_, Feature::PipelineStatisticsQuery);
    vertexPipelineStoresAndAtomics			= Has(features_, Feature::VertexPipelineStoresAndAtomics);
    fragmentStoresAndAtomics				= Has(features_, Feature::FragmentStoresAndAtomics);
    shaderTessellationAndGeometryPointSize	= Has(features_, Feature::ShaderTessellationAndGeometryPointSize);
    shaderImageGatherExtended				= Has(features_, Feature::ShaderImageGatherExtended);
    shaderStorageImageExtendedFormats		= Has(features_, Feature::ShaderStorageImageExtendedFormats);
    shaderStorageImageMultisample			= Has(features_, Feature::ShaderStorageImageMultisample);
    shaderStorageImageReadWithoutFormat		= Has(features_, Feature::ShaderStorageImageReadWithoutFormat);
    shaderStorageImageWriteWithoutFormat	= Has(features_, Feature::ShaderStorageImageWriteWithoutFormat);
    shaderUniformBufferArrayDynamicIndexing	= Has(features_, Feature::ShaderUniformBufferArrayDynamicIndexing);
    shaderSampledImageArrayDynamicIndexing	= Has(features_, Feature::ShaderSampledImageArrayDynamicIndexing);
    shaderStorageBufferArrayDynamicIndexing	= Has(features_, Feature::ShaderStorageBufferArrayDynamicIndexing);
    shaderStorageImageArrayDynamicIndexing	= Has(features_, Feature::ShaderStorageImageArrayDynamicIndexing);
    shaderClipDistance						= Has(features_, Feature::ShaderClipDistance);
    shaderCullDistance						= Has(features_, Feature::ShaderCullDistance);
    shaderFloat64							= Has(features_, Feature::ShaderFloat64);
    shaderInt64								= Has(features_, Feature::ShaderInt64);
    shaderInt16								= Has(features_, Feature::ShaderInt16);
    shaderResourceResidency					= Has(features_, Feature::ShaderResourceResidency);
    shaderResourceMinLod					= Has(features_, Feature::ShaderResourceMinLod);
    sparseBinding							= Has(features_, Feature::SparseBinding);
    sparseResidencyBuffer					= Has(features_, Feature::SparseResidencyBuffer);
    sparseResidencyImage2D					= Has(features_, Feature::SparseResidencyImage2D);
    sparseResidencyImage3D					= Has(features_, Feature::SparseResidencyImage3D);
    sparseResidency2Samples					= Has(features_, Feature::SparseResidency2Samples);
    sparseResidency4Samples					= Has(features_, Feature::SparseResidency4Samples);
    sparseResidency8Samples					= Has(features_, Feature::SparseResidency8Samples);
    sparseResidency16Samples				= Has(features_, Feature::SparseResidency16Samples);
    sparseResidencyAliased					= Has(features_, Feature::SparseResidencyAliased);
    variableMultisampleRate					= Has(features_, Feature::VariableMultisampleRate);
    inheritedQueries						= Has(features_, Feature::InheritedQueries);
}

#pragma endregion

#pragma region AttachmentDescription

inline GreatVEngine2::Vulkan::AttachmentDescription::AttachmentDescription(
	const VkFormat& format_,
	const VkSampleCountFlagBits& samples_,
	const VkAttachmentLoadOp& loadOp_,
	const VkAttachmentStoreOp& storeOp_,
	const VkAttachmentLoadOp& stencilLoadOp_,
	const VkAttachmentStoreOp& stencilStoreOp_,
	const VkImageLayout& initialLayout_,
	const VkImageLayout& finalLayout_
) {
	flags			= 0; // VkAttachmentDescriptionFlagBits::VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;
	format			= format_;
	samples			= samples_;
	loadOp			= loadOp_;
	storeOp			= storeOp_;
	stencilLoadOp	= stencilLoadOp_;
	stencilStoreOp	= stencilStoreOp_;
	initialLayout	= initialLayout_;
	finalLayout		= finalLayout_;
}

#pragma endregion

#pragma region AttachmentReference

inline GreatVEngine2::Vulkan::AttachmentReference::AttachmentReference(const decltype(attachment)& attachment_, const VkImageLayout& layout_)
{
	attachment	= attachment_;
	layout		= layout_;
}

#pragma endregion

#pragma region SubpassDescription

inline GreatVEngine2::Vulkan::SubpassDescription::SubpassDescription(const VkPipelineBindPoint& pipelineBindPoint_, const Vector<VkAttachmentReference>& colorAttachments_):
	SubpassDescription(pipelineBindPoint_, {}, colorAttachments_, {}, nullptr, {})
{
}
inline GreatVEngine2::Vulkan::SubpassDescription::SubpassDescription(const VkPipelineBindPoint& pipelineBindPoint_, const Vector<VkAttachmentReference>& colorAttachments_, const VkAttachmentReference& depthStencilAttachment_):
	SubpassDescription(pipelineBindPoint_, {}, colorAttachments_, {}, &depthStencilAttachment_, {})
{
}
inline GreatVEngine2::Vulkan::SubpassDescription::SubpassDescription(
	const VkPipelineBindPoint& pipelineBindPoint_,
	const Vector<VkAttachmentReference>& inputAttachments_,
	const Vector<VkAttachmentReference>& colorAttachments_,
	const Vector<VkAttachmentReference>& resolveAttachments_,
	const VkAttachmentReference* depthStencilAttachment_,
	const Vector<uint32_t>& preserveAttachments_
) {
	// TODO: check resolveAttachments_.size()
	flags						= 0;
	pipelineBindPoint			= pipelineBindPoint_;
	inputAttachmentCount		= inputAttachments_.size();
	pInputAttachments			= inputAttachments_.data();
	colorAttachmentCount		= colorAttachments_.size();
	pColorAttachments			= colorAttachments_.data();
	pResolveAttachments			= resolveAttachments_.data();
	pDepthStencilAttachment		= depthStencilAttachment_;
	preserveAttachmentCount		= preserveAttachments_.size();
	pPreserveAttachments		= preserveAttachments_.data();
}

#pragma endregion

#pragma region CommandBufferBeginInfo

inline GreatVEngine2::Vulkan::CommandBufferBeginInfo::CommandBufferBeginInfo(const VkCommandBufferUsageFlags& flags_, const VkCommandBufferInheritanceInfo& inheritanceInfo_):
	CommandBufferBeginInfo(flags_, &inheritanceInfo_)
{
}
inline GreatVEngine2::Vulkan::CommandBufferBeginInfo::CommandBufferBeginInfo(const VkCommandBufferUsageFlags& flags_, const VkCommandBufferInheritanceInfo* inheritanceInfo_)
{
	sType				= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	pNext				= nullptr;
	flags				= flags_;
	pInheritanceInfo	= inheritanceInfo_;
}

#pragma endregion

#pragma region RenderPassBeginInfo

inline GreatVEngine2::Vulkan::RenderPassBeginInfo::RenderPassBeginInfo(const RenderPassHandle& renderPassHandle_, const FramebufferHandle& framebufferHandle_, const VkRect2D& vk_renderArea_, const Vector<VkClearValue>& vk_clearValues_)
{
	sType			= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	pNext			= nullptr;
	renderPass		= renderPassHandle_;
	framebuffer		= framebufferHandle_;
	renderArea		= vk_renderArea_;
	clearValueCount	= vk_clearValues_.size();
	pClearValues	= vk_clearValues_.data();
}

#pragma endregion

#pragma region SubmitInfo

inline GreatVEngine2::Vulkan::SubmitInfo::SubmitInfo(
	const Vector<CommandBufferHandle>& commandBuffersHandles_,
	// const Vector<VkSemaphore>& vk_waitSemaphores_,
	const Vector<VkPipelineStageFlags>& vk_waitMasks_
	// const Vector<VkSemaphore>& vk_signalSemaphores_
):
	vk_commandBuffers([&](){
		Vector<VkCommandBuffer> commandBuffers(commandBuffersHandles_.size());

		for (Size i = 0; i < commandBuffersHandles_.size(); ++i)
		{
			commandBuffers[i] = commandBuffersHandles_[i];
		}

		return Move(commandBuffers);
	}())
{
	sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	pNext					= nullptr;
	waitSemaphoreCount		= 0; // vk_waitSemaphores_.size();
	pWaitSemaphores			= nullptr; // vk_waitSemaphores_.data();
	pWaitDstStageMask		= vk_waitMasks_.data();
	commandBufferCount		= vk_commandBuffers.size();
	pCommandBuffers			= vk_commandBuffers.data();
	signalSemaphoreCount	= 0; // vk_signalSemaphores_.size();
	pSignalSemaphores		= nullptr; // vk_signalSemaphores_.data();
}

#pragma endregion


#pragma region Offset2D

inline GreatVEngine2::Vulkan::Offset2D::Offset2D(const X& x_, const Y& y_)
{
	x = x_;
	y = y_;
}

#pragma endregion

#pragma region Offset3D

inline GreatVEngine2::Vulkan::Offset3D::Offset3D(const X& x_, const Y& y_, const Z& z_)
{
	x = x_;
	y = y_;
	z = z_;
}

#pragma endregion

#pragma region Extent2D

inline GreatVEngine2::Vulkan::Extent2D::Extent2D(const Width& width_, const Height& height_)
{
	width = width_;
	height = height_;
}

#pragma endregion

#pragma region Extent3D

inline GreatVEngine2::Vulkan::Extent3D::Extent3D(const Width& width_, const Height& height_, const Depth& depth_)
{
	width = width_;
	height = height_;
	depth = depth_;
}
inline GreatVEngine2::Vulkan::Extent3D::Extent3D(const VkExtent2D& extent_, const Depth& depth_):
	Extent3D(extent_.width, extent_.height, depth_)
{
}

#pragma endregion

#pragma region Rect2D

inline GreatVEngine2::Vulkan::Rect2D::Rect2D(const Offset& offset_, const Extent& extent_)
{
	offset = offset_;
	extent = extent_;
}

#pragma endregion

#pragma region ComponentMapping

inline GreatVEngine2::Vulkan::ComponentMapping::ComponentMapping(const VkComponentSwizzle& r_, const VkComponentSwizzle& g_, const VkComponentSwizzle& b_, const VkComponentSwizzle& a_)
{
	r	= r_;
	g	= g_;
	b	= b_;
	a	= a_;
}

#pragma endregion

#pragma region ImageSubresourceRange

inline GreatVEngine2::Vulkan::ImageSubresourceRange::ImageSubresourceRange(
	VkImageAspectFlags aspectMask_,
	uint32_t baseMipLevel_,
	uint32_t levelCount_,
	uint32_t baseArrayLayer_,
	uint32_t layerCount_
) {
	aspectMask = aspectMask_;
	baseMipLevel = baseMipLevel_;
	levelCount = levelCount_;
	baseArrayLayer = baseArrayLayer_;
	layerCount = layerCount_;
}

#pragma endregion

#pragma region ClearValue

inline VkClearValue GreatVEngine2::Vulkan::ClearValue::Color(const float& r_, const float& g_, const float& b_, const float& a_)
{
	VkClearValue vk_clearValue;

	vk_clearValue.color.float32[0] = r_;
	vk_clearValue.color.float32[1] = g_;
	vk_clearValue.color.float32[2] = b_;
	vk_clearValue.color.float32[3] = a_;

	return vk_clearValue;
}
inline VkClearValue GreatVEngine2::Vulkan::ClearValue::DepthStencil(const float& depth_, const uint32_t& stencil_)
{
	VkClearValue vk_clearValue;

	vk_clearValue.depthStencil.depth = depth_;
	vk_clearValue.depthStencil.stencil = stencil_;

	return vk_clearValue;
}

#pragma endregion


#pragma region InstanceCreateInfo

GreatVEngine2::Vulkan::InstanceCreateInfo::InstanceCreateInfo(const LayersNames& enabledLayersNames_, const ExtensionsNames& enabledExtensionsNames_):
	InstanceCreateInfo(nullptr, enabledLayersNames_, enabledExtensionsNames_)
{
}
GreatVEngine2::Vulkan::InstanceCreateInfo::InstanceCreateInfo(const VkApplicationInfo& vk_applicationInfo_, const LayersNames& enabledLayersNames_, const ExtensionsNames& enabledExtensionsNames_) :
InstanceCreateInfo(&vk_applicationInfo_, enabledLayersNames_, enabledExtensionsNames_)
{
}
GreatVEngine2::Vulkan::InstanceCreateInfo::InstanceCreateInfo(const VkApplicationInfo* vk_applicationInfo_, const LayersNames& enabledLayersNames_, const ExtensionsNames& enabledExtensionsNames_)
{
	// TODO: move to initialization
	sType						= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	pNext						= nullptr;
	flags						= 0;
	pApplicationInfo			= vk_applicationInfo_;
	enabledLayerCount			= enabledLayersNames_.size();
	ppEnabledLayerNames			= enabledLayersNames_.data();
	enabledExtensionCount		= enabledExtensionsNames_.size();
	ppEnabledExtensionNames		= enabledExtensionsNames_.data();
}

#pragma endregion

#pragma region DeviceCreateInfo

inline GreatVEngine2::Vulkan::DeviceCreateInfo::DeviceCreateInfo(const Vector<VkDeviceQueueCreateInfo>& vk_deviceQueueCreateInfos_, const Vector<const char*>& vk_enabledPhysicalDeviceLayersNames_, const Vector<const char*>& vk_enabledPhysicalDeviceExtensionsNames_, const VkPhysicalDeviceFeatures& vk_physicalDeviceFeatures_):
	DeviceCreateInfo(vk_deviceQueueCreateInfos_, vk_enabledPhysicalDeviceLayersNames_, vk_enabledPhysicalDeviceExtensionsNames_, &vk_physicalDeviceFeatures_)
{
}
inline GreatVEngine2::Vulkan::DeviceCreateInfo::DeviceCreateInfo(const Vector<VkDeviceQueueCreateInfo>& vk_deviceQueueCreateInfos_, const Vector<const char*>& vk_enabledPhysicalDeviceLayersNames_, const Vector<const char*>& vk_enabledPhysicalDeviceExtensionsNames_, const VkPhysicalDeviceFeatures* vk_physicalDeviceFeatures_)
{
	sType					= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	pNext					= nullptr;
	flags					= 0;
	queueCreateInfoCount	= vk_deviceQueueCreateInfos_.size();
	pQueueCreateInfos		= vk_deviceQueueCreateInfos_.data();
	enabledLayerCount		= vk_enabledPhysicalDeviceLayersNames_.size();
	ppEnabledLayerNames		= vk_enabledPhysicalDeviceLayersNames_.data();
	enabledExtensionCount	= vk_enabledPhysicalDeviceExtensionsNames_.size();
	ppEnabledExtensionNames	= vk_enabledPhysicalDeviceExtensionsNames_.data();
	pEnabledFeatures		= vk_physicalDeviceFeatures_;
}

#pragma endregion

#pragma region DeviceQueueCreateInfo

inline GreatVEngine2::Vulkan::DeviceQueueCreateInfo::DeviceQueueCreateInfo(const decltype(VkDeviceQueueCreateInfo::queueFamilyIndex)& queueFamilyIndex_, const Vector<float>& queuePriorities_)
{
	sType				= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	pNext				= nullptr;
	flags				= 0;
	queueFamilyIndex	= queueFamilyIndex_;
	queueCount			= queuePriorities_.size();
	pQueuePriorities	= queuePriorities_.data();
}

#pragma endregion

#pragma region CommandPoolCreateInfo

inline GreatVEngine2::Vulkan::CommandPoolCreateInfo::CommandPoolCreateInfo(const VkCommandPoolCreateFlags& flags_, const decltype(queueFamilyIndex)& queueFamilyIndex_)
{
	sType				= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pNext				= nullptr;
	flags				= flags_;
	queueFamilyIndex	= queueFamilyIndex_;
}

#pragma endregion

#pragma region RenderPassCreateInfo

inline GreatVEngine2::Vulkan::RenderPassCreateInfo::RenderPassCreateInfo(const Vector<VkAttachmentDescription>& vk_attachmentDescriptions_, const Vector<VkSubpassDescription>& vk_subpassDescriptions_, const Vector<VkSubpassDependency>& vk_subpassDependencies_)
{
	sType			= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	pNext			= nullptr;
	flags			= 0;
	attachmentCount	= vk_attachmentDescriptions_.size();
	pAttachments	= vk_attachmentDescriptions_.data();
	subpassCount	= vk_subpassDescriptions_.size();
	pSubpasses		= vk_subpassDescriptions_.data();
	dependencyCount	= vk_subpassDependencies_.size();
	pDependencies	= vk_subpassDependencies_.data();
}

#pragma endregion

#pragma region ImageViewCreateInfo

inline GreatVEngine2::Vulkan::ImageViewCreateInfo::ImageViewCreateInfo(
	const VkImageViewCreateFlags& flags_,
	const ImageHandle& imageHandle_,
	const VkImageViewType& vk_imageViewType_,
	const VkFormat& format_,
	const VkComponentMapping& vk_componentMapping_,
	const VkImageSubresourceRange& vk_imageSubresourceRange_
) {
	sType				= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	pNext				= nullptr;
	flags				= flags_;
	image				= imageHandle_;
	viewType			= vk_imageViewType_;
	format				= format_;
	components			= vk_componentMapping_;
	subresourceRange	= vk_imageSubresourceRange_;
}

#pragma endregion

#pragma region FramebufferCreateInfo

GreatVEngine2::Vulkan::FramebufferCreateInfo::FramebufferCreateInfo(
	const RenderPassHandle& renderPassHandle_,
	const Vector<ImageViewHandle>& attachments_,
	const decltype(width)& width_,
	const decltype(height)& height_,
	const decltype(layers)& layers_
):
	attachments([&](){
		Vector<VkImageView> values;

		values.reserve(attachments_.size());

		for (auto &value : attachments_)
		{
			values.push_back(value);
		}

		return Move(values);
	}())
{
	sType				= VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	pNext				= nullptr;
	flags				= 0;
	renderPass			= renderPassHandle_;
	attachmentCount		= attachments.size();
	pAttachments		= attachments.data();
	width				= width_;
	height				= height_;
	layers				= layers_;
}

#pragma endregion

#pragma region FenceCreateInfo

inline GreatVEngine2::Vulkan::FenceCreateInfo::FenceCreateInfo(const VkFenceCreateFlags& flags_)
{
	sType	= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	pNext	= nullptr;
	flags	= flags_;
}

#pragma endregion

#pragma region Win32SurfaceCreateInfoKHR

#if VK_USE_PLATFORM_WIN32_KHR

inline GreatVEngine2::Vulkan::Win32SurfaceCreateInfoKHR::Win32SurfaceCreateInfoKHR(const decltype(VkWin32SurfaceCreateInfoKHR::hinstance)& handleInstance_, const decltype(VkWin32SurfaceCreateInfoKHR::hwnd)& handleWindow_)
{
	sType		= VkStructureType::VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	pNext		= nullptr;
	flags		= 0;
	hinstance	= handleInstance_;
	hwnd		= handleWindow_;
}

#endif

#pragma endregion

#pragma region SwapchainCreateInfoKHR

#if VK_USE_PLATFORM_WIN32_KHR

inline GreatVEngine2::Vulkan::SwapchainCreateInfoKHR::SwapchainCreateInfoKHR(
	VkSwapchainCreateFlagsKHR		flags_,
	SurfaceKHRHandle				surfaceHandle_,
	uint32_t						minImageCount_,
	VkFormat						imageFormat_,
	VkColorSpaceKHR					imageColorSpace_,
	VkExtent2D						imageExtent_,
	uint32_t						imageArrayLayers_,
	VkImageUsageFlags				imageUsage_,
	VkSharingMode					imageSharingMode_,
	const Vector<uint32_t>&			queueFamilyIndices_,
	VkSurfaceTransformFlagBitsKHR	preTransform_,
	VkCompositeAlphaFlagBitsKHR		compositeAlpha_,
	VkPresentModeKHR				presentMode_,
	VkBool32						clipped_,
	SwapchainKHRHandle				oldSwapchainHandle_
)
{
	sType					= VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	pNext					= nullptr;
	flags					= flags_;
	surface					= surfaceHandle_;
	minImageCount			= minImageCount_;
	imageFormat				= imageFormat_;
	imageColorSpace			= imageColorSpace_;
	imageExtent				= imageExtent_;
	imageArrayLayers		= imageArrayLayers_;
	imageUsage				= imageUsage_;
	imageSharingMode		= imageSharingMode_;
	queueFamilyIndexCount	= queueFamilyIndices_.size();
	pQueueFamilyIndices		= queueFamilyIndices_.data();
	preTransform			= preTransform_;
	compositeAlpha			= compositeAlpha_;
	presentMode				= presentMode_;
	clipped					= clipped_;
	oldSwapchain			= oldSwapchainHandle_;
}

#endif

#pragma endregion

#pragma region CommandBufferAllocateInfo

inline GreatVEngine2::Vulkan::CommandBufferAllocateInfo::CommandBufferAllocateInfo(const CommandPoolHandle& commandPoolHandle_, const VkCommandBufferLevel& level_, const decltype(commandBufferCount)& commandBufferCount_)
{
	sType				= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	pNext				= nullptr;
	commandPool			= commandPoolHandle_;
	level				= level_;
	commandBufferCount	= commandBufferCount_;
}

#pragma endregion

#pragma region PresentInfoKHR

inline GreatVEngine2::Vulkan::PresentInfoKHR::PresentInfoKHR(const Vector<VkSemaphore>& vk_waitSemaphores_, const Vector<VkSwapchainKHR>& vk_swapchains_, const Vector<uint32_t>& vk_nextImageIndices_)
{
	sType				= VkStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	pNext				= nullptr;
	waitSemaphoreCount	= vk_waitSemaphores_.size();
	pWaitSemaphores		= vk_waitSemaphores_.data();
	swapchainCount		= vk_swapchains_.size();
	pSwapchains			= vk_swapchains_.data();
	pImageIndices		= vk_nextImageIndices_.data();
	pResults			= nullptr; // may be NULL, TODO: implement
}

#pragma endregion


#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


