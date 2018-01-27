#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace Vulkan
	{
		class Exception:
			public GreatVEngine2::Exception
		{
		public:
			inline Exception();
			inline Exception(const Text& text_);
		};
	}
}


#pragma region GreatVEngine2

#pragma region Vulkan

#pragma region Exception

GreatVEngine2::Vulkan::Exception::Exception():
	Exception("Unknown Vulkan exception.")
{
}
GreatVEngine2::Vulkan::Exception::Exception(const Text& text_) :
	GreatVEngine2::Exception(text_)
{
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


