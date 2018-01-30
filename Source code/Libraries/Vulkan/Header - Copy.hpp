#pragma region Include

#pragma once

#include <../Common/Common.hpp>

#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__

#define VK_USE_PLATFORM_WIN32_KHR 1

#endif

#include <../../Vulkan/Include/vulkan/vulkan.h>

#pragma endregion


#pragma region Macro

#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

#if _DEBUG
#define __GREAT_V_ENGINE_2__VULKAN__DEBUG__ 1
#else
#define __GREAT_V_ENGINE_2__VULKAN__DEBUG__ 0
#endif

#if __GREAT_V_ENGINE_2__VULKAN__DEBUG__
#define __GREAT_V_ENGINE_2__VULKAN__VALIDATE_ADMISSIBLE_VALUES__ 1
#else
#define __GREAT_V_ENGINE_2__VULKAN__VALIDATE_ADMISSIBLE_VALUES__ 0
#endif

#define __GREAT_V_ENGINE_2__VULKAN__IMPLICIT_VALUE_OPERATIONS__ 0

#pragma endregion


namespace GreatVEngine2
{
	namespace Vulkan
	{
		class Boolean
		{
		public:
			using Value = VkBool32;
		public:
			static const Value TRUE = VK_TRUE;
			static const Value FALSE = VK_FALSE;
		public:
			inline static Value ToValue(const bool& value_);
		protected:
			inline static void ValidateOnAdmissibility(const Value& value_);
			inline static Value ValidateOnAdmissibilityAndReturn(const Value& value_);
		protected:
			Value value;
		public:
			inline Boolean() = delete; // undefined initial state is not allowed
			inline Boolean(const Boolean&) = default;
			inline explicit Boolean(const Value& value_);
			inline Boolean(const bool& value_);
			inline ~Boolean() = default;
		public:
			inline Boolean& operator = (const Boolean&) = default;
		public:
			inline Boolean operator ! () const;
		public:
			inline bool operator == (const Boolean& source_);
			inline bool operator != (const Boolean& source_);
		public:
			inline explicit operator Value() const;
			inline operator bool() const;
			// TODO: operator String()
#if __GREAT_VULKAN__IMPLICIT_VALUE_OPERATIONS__
		public:
			inline Boolean& operator = (const Value& value_);
			inline Boolean& operator = (const bool& value_);
		public:
			inline bool operator == (const Value& source_);
			inline bool operator != (const Value& source_);
			inline bool operator == (const bool& source_);
			inline bool operator != (const bool& source_);
#endif
		};
		class Result
		{
		public:
			using RawValue = VkResult;
			enum class Value // : VkResult
			{
				Success							= VkResult::VK_SUCCESS,
				NotReady						= VkResult::VK_NOT_READY,
				Timeout							= VkResult::VK_TIMEOUT,
				EventSet						= VkResult::VK_EVENT_SET,
				EventReset						= VkResult::VK_EVENT_RESET,
				Incomplete						= VkResult::VK_INCOMPLETE,
			
				Error_OutOfHostMemory			= VkResult::VK_ERROR_OUT_OF_HOST_MEMORY,
				Error_OutOfDeviceMemory			= VkResult::VK_ERROR_OUT_OF_DEVICE_MEMORY,
				Error_InitializationFailed		= VkResult::VK_ERROR_INITIALIZATION_FAILED,
				Error_DeviceLost				= VkResult::VK_ERROR_DEVICE_LOST,
				Error_MemoryMapFailed			= VkResult::VK_ERROR_MEMORY_MAP_FAILED,
				Error_LayerNotPresent			= VkResult::VK_ERROR_LAYER_NOT_PRESENT,
				Error_ExtensionNotPresent		= VkResult::VK_ERROR_EXTENSION_NOT_PRESENT,
				Error_FeatureNotPresent			= VkResult::VK_ERROR_FEATURE_NOT_PRESENT,
				Error_IncompatibleDriver		= VkResult::VK_ERROR_INCOMPATIBLE_DRIVER,
				Error_TooManyObjects			= VkResult::VK_ERROR_TOO_MANY_OBJECTS,
				Error_FormatNotSupported		= VkResult::VK_ERROR_FORMAT_NOT_SUPPORTED,
				Error_FragmentedPool			= VkResult::VK_ERROR_FRAGMENTED_POOL,
			
				Error_KHR_SufraceLost			= VkResult::VK_ERROR_SURFACE_LOST_KHR,
				Error_KHR_NativeWindowInUse		= VkResult::VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,
				Error_KHR_Suboptimal			= VkResult::VK_SUBOPTIMAL_KHR,
				Error_KHR_OutOfDate				= VkResult::VK_ERROR_OUT_OF_DATE_KHR,
				Error_KHR_IncompatibleDisplay	= VkResult::VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,
				Error_KHR_OutOfPoolMemory		= VkResult::VK_ERROR_OUT_OF_POOL_MEMORY_KHR,
				Error_KHR_InvalidExternalHandle = VkResult::VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR,
			
				Error_EXT_ValidationFailed		= VkResult::VK_ERROR_VALIDATION_FAILED_EXT,
			
				Error_NV_InvalidShader			= VkResult::VK_ERROR_INVALID_SHADER_NV,
			};
		protected:
			inline static void ValidateOnAdmissibility(const Value& value_);
			inline static Value ValidateOnAdmissibilityAndReturn(const Value& value_);
			inline static Value ToValue(const RawValue& source_);
		protected:
			Value value;
		public:
			inline Result() = delete; // undefined initial state is not allowed
			inline Result(const Result&) = default;
			inline explicit Result(const Value& value_);
			inline explicit Result(const RawValue& value_);
			inline ~Result() = default;
		public:
			inline Result& operator = (const Result&) = default;
		public:
			inline bool operator == (const Result& source_) const;
			inline bool operator != (const Result& source_) const;
		public:
			inline operator bool() const;
			inline explicit operator Value() const;
		public:
			inline bool IsError() const;
		};

#if VK_USE_PLATFORM_WIN32_KHR
		class SurfaceKHRHandle;
		class SwapchainKHRHandle;
#endif
	}
}


#pragma region GreatVEngine2

#pragma region Vulkan

#pragma region Boolean

inline GreatVEngine2::Vulkan::Boolean::Value GreatVEngine2::Vulkan::Boolean::ToValue(const bool& value_)
{
	return value_
		? TRUE
		: FALSE;
}

inline void GreatVEngine2::Vulkan::Boolean::ValidateOnAdmissibility(const Value& value_)
{
#if	__GREAT_VULKAN__VALIDATE_ADMISSIBLE_VALUES__
	
	switch(value_)
	{
		case TRUE:	break;
		case FALSE:	break;
		default:	throw Exception(); // TODO
	}

#endif
}
inline GreatVEngine2::Vulkan::Boolean::Value GreatVEngine2::Vulkan::Boolean::ValidateOnAdmissibilityAndReturn(const Value& value_)
{
	ValidateOnAdmissibility(value_);

	return value_;
}


inline GreatVEngine2::Vulkan::Boolean::Boolean(const Value& value_):
	value(ValidateOnAdmissibilityAndReturn(value_))
{
}
inline GreatVEngine2::Vulkan::Boolean::Boolean(const bool& value_):
	value(ToValue(value_))
{
}

inline GreatVEngine2::Vulkan::Boolean GreatVEngine2::Vulkan::Boolean::operator ! () const
{
	return Boolean(ValidateOnAdmissibilityAndReturn(value) == FALSE);
}

inline bool GreatVEngine2::Vulkan::Boolean::operator == (const Boolean& source_)
{
	return value == source_.value; // ValidateOnAdmissibilityAndReturn not needed
}
inline bool GreatVEngine2::Vulkan::Boolean::operator != (const Boolean& source_)
{
	return value != source_.value; // ValidateOnAdmissibilityAndReturn not needed
}

inline GreatVEngine2::Vulkan::Boolean::operator Value() const
{
	return value;
}
inline GreatVEngine2::Vulkan::Boolean::operator bool() const
{
	return ValidateOnAdmissibilityAndReturn(value) == TRUE;
}

#if __GREAT_VULKAN__IMPLICIT_VALUE_OPERATIONS__

inline GreatVEngine2::Vulkan::Boolean& GreatVEngine2::Vulkan::Boolean::operator = (const Value& value_)
{
	value = ValidateOnAdmissibilityAndReturn(value_);

	return *this;
}
inline GreatVEngine2::Vulkan::Boolean& GreatVEngine2::Vulkan::Boolean::operator = (const bool& value_)
{
	value = ToValue(value_);

	return *this;
}

inline bool GreatVEngine2::Vulkan::Boolean::operator == (const Value& source_)
{
	return value == source_; // ValidateOnAdmissibilityAndReturn not needed
}
inline bool GreatVEngine2::Vulkan::Boolean::operator != (const Value& source_)
{
	return value != source_; // ValidateOnAdmissibilityAndReturn not needed
}
inline bool GreatVEngine2::Vulkan::Boolean::operator == (const bool& source_)
{
	return ValidateOnAdmissibilityAndReturn(value) == (source_
		? TRUE
		: FALSE);
}
inline bool GreatVEngine2::Vulkan::Boolean::operator != (const bool& source_)
{
	return ValidateOnAdmissibilityAndReturn(value) != (source_
		? TRUE
		: FALSE);
}

#endif

#pragma endregion

#pragma region Result

inline void GreatVEngine2::Vulkan::Result::ValidateOnAdmissibility(const Value& value_)
{
#if __GREAT_V_ENGINE_2__VULKAN__VALIDATE_ADMISSIBLE_VALUES__

	switch(value_)
	{
		case GreatVEngine2::Vulkan::Result::Value::Success: break;
		case GreatVEngine2::Vulkan::Result::Value::NotReady: break;
		case GreatVEngine2::Vulkan::Result::Value::Timeout: break;
		case GreatVEngine2::Vulkan::Result::Value::EventSet: break;
		case GreatVEngine2::Vulkan::Result::Value::EventReset: break;
		case GreatVEngine2::Vulkan::Result::Value::Incomplete: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_OutOfHostMemory: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_OutOfDeviceMemory: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_InitializationFailed: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_DeviceLost: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_MemoryMapFailed: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_LayerNotPresent: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_ExtensionNotPresent: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_FeatureNotPresent: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_IncompatibleDriver: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_TooManyObjects: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_FormatNotSupported: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_FragmentedPool: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_SufraceLost: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_NativeWindowInUse: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_Suboptimal: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_OutOfDate: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_IncompatibleDisplay: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_OutOfPoolMemory: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_KHR_InvalidExternalHandle: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_EXT_ValidationFailed: break;
		case GreatVEngine2::Vulkan::Result::Value::Error_NV_InvalidShader: break;
		default: throw Exception(); // TODO
	}
#endif
}
inline GreatVEngine2::Vulkan::Result::Value GreatVEngine2::Vulkan::Result::ValidateOnAdmissibilityAndReturn(const Value& value_)
{
	ValidateOnAdmissibility(value_);

	return value_;
}
inline GreatVEngine2::Vulkan::Result::Value GreatVEngine2::Vulkan::Result::ToValue(const RawValue& source_)
{
	return ValidateOnAdmissibilityAndReturn(static_cast<Value>(source_));
}

inline GreatVEngine2::Vulkan::Result::Result(const Value& value_):
	value(ValidateOnAdmissibilityAndReturn(value_))
{
}
inline GreatVEngine2::Vulkan::Result::Result(const RawValue& value_):
	value(ToValue(value_))
{
}

inline bool GreatVEngine2::Vulkan::Result::operator == (const Result& source_) const
{
	return value == source_.value; // ValidateOnAdmissibilityAndReturn not needed
}
inline bool GreatVEngine2::Vulkan::Result::operator != (const Result& source_) const
{
	return value != source_.value; // ValidateOnAdmissibilityAndReturn not needed
}

inline GreatVEngine2::Vulkan::Result::operator bool() const
{
	return value == Value::Success;
}
inline GreatVEngine2::Vulkan::Result::operator Value() const
{
	return value;
}

inline bool GreatVEngine2::Vulkan::Result::IsError() const
{
	return static_cast<Size>(ValidateOnAdmissibilityAndReturn(value)) < 0;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


