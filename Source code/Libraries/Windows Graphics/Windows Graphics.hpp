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
			namespace Windows
			{
				class View:
					public Graphics::View
				{
				public:
					using InstanceHandle = HINSTANCE;
					using WindowHandle = HWND;
					using DeviceContextHandle = HDC;
				public:
					inline View() = delete;
					inline View(const StrongPointer<View>& this_);
					inline View(const View&) = delete;
					inline ~View() = default;
				public:
					inline View& operator = (const View&) = delete;
				public:
					inline virtual void Present(const StrongPointer<Output>& renderResult_) override;
				public:
					inline virtual InstanceHandle GetInstanceHandle() const;
					inline virtual WindowHandle GetWindowHandle() const;
					inline virtual DeviceContextHandle GetDeviceContextHandle() const;
				};
			}
		}
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region APIs

#pragma region Windows

#pragma region View

GreatVEngine2::Graphics::APIs::Windows::View::View(const StrongPointer<View>& this_):
	Graphics::View(this_)
{
}

void GreatVEngine2::Graphics::APIs::Windows::View::Present(const StrongPointer<Output>& renderResult_)
{
	renderResult_->SignalPresented(GetThis<View>());
}

GreatVEngine2::Graphics::APIs::Windows::View::InstanceHandle GreatVEngine2::Graphics::APIs::Windows::View::GetInstanceHandle() const
{
	return 0;
}
GreatVEngine2::Graphics::APIs::Windows::View::WindowHandle GreatVEngine2::Graphics::APIs::Windows::View::GetWindowHandle() const
{
	return 0;
}
GreatVEngine2::Graphics::APIs::Windows::View::DeviceContextHandle GreatVEngine2::Graphics::APIs::Windows::View::GetDeviceContextHandle() const
{
	return 0;
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


