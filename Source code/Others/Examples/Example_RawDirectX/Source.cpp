#include <iostream>

#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#include <../../Direct3D/include/d3d9.h>
#include <../../Direct3D/include/d3dx9.h>


void main()
{
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

	auto windowHandle = createWindow("DirectX", 50, 50, 300, 200);
	auto deviceContextHandle = getDeviceContext(windowHandle);

	// DirectX
	auto renderContext = Direct3DCreate9(D3D_SDK_VERSION);
	{
		if (!renderContext)
		{
			throw Exception("Cant create DirectX render context.");
		}
	}

	LPDIRECT3DDEVICE9 device;
	{
		D3DPRESENT_PARAMETERS presentParameters;
		{
			ZeroMemory(&presentParameters, sizeof(presentParameters));
			presentParameters.Windowed						= TRUE;
			presentParameters.BackBufferWidth				= 300;
			presentParameters.BackBufferHeight				= 200;
			presentParameters.BackBufferCount				= 1;
			presentParameters.MultiSampleType				= _D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;
			presentParameters.MultiSampleQuality			= 0;
			presentParameters.SwapEffect					= _D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;
			presentParameters.Flags							= 0;
			presentParameters.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
			presentParameters.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;
			presentParameters.BackBufferFormat				= D3DFMT_UNKNOWN;	//D3DFMT_R8G8B8;	//D3DFMT_UNKNOWN
			presentParameters.EnableAutoDepthStencil		= FALSE;
			presentParameters.hDeviceWindow					= windowHandle;
		}

		auto result = renderContext->CreateDevice
			(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			NULL,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// D3DCREATE_HARDWARE_VERTEXPROCESSING
			&presentParameters,
			&device
		);

		if (result != D3D_OK)
		{
			throw Exception();
		}
	}



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

		device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0);
		device->BeginScene();
		
		// TODO

		device->EndScene();
		device->Present(NULL, NULL, NULL, NULL);

		SwapBuffers(deviceContextHandle);
	}

	// std::system("pause");
}