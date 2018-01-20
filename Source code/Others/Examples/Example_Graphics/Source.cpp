#include <iostream>
#include <chrono>

#include <../OpenGL/OpenGL.hpp>
#include <../Graphics/Graphics.hpp>
#include <../OpenGL Graphics/OpenGL Graphics.hpp>
#include <../Windows Graphics/Windows Graphics.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;


void render_windows_opengl()
{
	while (true) // main loop
	{
		// wglMakeCurrent(window device context handle, opengl device context handle);
		// render stuff
		// SwapBuffers(window device context handle);
	}
}
void render_windows_vulkan()
{
	while (true) // main loop
	{
		// vkAcquireNextImageKHR
		// render stuff
		// vkQueuePresentKHR
	}
}


namespace GreatVEngine2
{
	namespace Graphics
	{
		namespace Windows
		{
			class View:
				public Graphics::View
			{
			public:
				inline View(const StrongPointer<View>& this_): Graphics::View(this_)
				{
				}
			public:
				inline virtual void Present(const StrongPointer<Output>& renderResult_) override
				{
					renderResult_->SignalPresented(GetThis<View>());
				}
			};
		}
		
		namespace OpenGL
		{
			class Output:
				public Graphics::Output
			{
			public:
				Output(const StrongPointer<Output>& this_): Graphics::Output(this_)
				{
				}
			protected:
				inline void PresendOn(const Memory<Windows::View>& view_)
				{
				}
			public:
				inline virtual void SignalPresented(const StrongPointer<View>& view_) override
				{
					if (auto windowsView = DynamicCast<Windows::View>(view_))
					{
						PresendOn(windowsView.GetValue());
					}
				}
			};
			class Engine:
				public Graphics::Engine
			{
			public:
				inline Engine(const StrongPointer<Engine>& this_): Graphics::Engine(this_)
				{
				}
			public:
				virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Graphics::Scene>& scene_, const StrongPointer<Graphics::Camera>& camera_) override
				{
					auto renderResult = Make<Output>();

					// TODO

					return renderResult;
				}
			};
		}
	}
}


void stressTest_objectsAddingAndRemoving()
{
	auto engine = Make<Graphics::OpenGL::Engine>();

	auto material = Make<Graphics::Material>();
	auto model = Make<Graphics::Model>();

	auto scene = Make<Graphics::Scene>();

	std::chrono::microseconds average = std::chrono::microseconds::zero();
	Size m = 10;

	for (Size i = 0; i < m; ++i)
	{
		Vector<StrongPointer<Graphics::Object>> objects(1000000);

		auto timeBegin = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());

		for (auto &object : objects)
		{
			object = Make<Graphics::Object>(material, model, scene);
		}

		objects.clear();

		auto timeEnd = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
		auto timeDifference = timeEnd - timeBegin;

		std::cout << "time: " << timeDifference.count() << " microseconds" << std::endl;

		average += timeDifference;
	}

	average /= m;

	std::cout << "average: " << average.count() << " microseconds" << std::endl;
}


/*void main()
{
	auto engine = Make<Graphics::APIs::OpenGL::Engine>(); // Make<Graphics::Engine>();

	auto material = Make<Graphics::Material>();
	auto model = Make<Graphics::Model>();

	auto scene = Make<Graphics::Scene>();

	auto object = Make<Graphics::Object>(material, model, scene);

	auto camera = Make<Graphics::Camera>();

	auto result = engine->Render(scene, camera);

	auto view = Make<Graphics::APIs::Windows::View>();

	view->Present(result);

	std::system("pause");
}*/


class TView:
	public Graphics::APIs::Windows::View
{
protected:
	const DeviceContextHandle deviceContextHandle;
public:
	inline TView(const StrongPointer<TView>& this_, const DeviceContextHandle& deviceContextHandle_):
		View(this_),
		deviceContextHandle(deviceContextHandle_)
	{
	}
public:
	inline virtual DeviceContextHandle GetDeviceContextHandle() const override
	{
		return deviceContextHandle;
	}
};

void main()
{
	OpenGL::Init();


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

	HWND windowHandle = CreateWindowA(
		windowClassName.c_str(),
		"window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600,
		NULL,
		NULL,
		instanceHandle,
		NULL
	);

	if (!windowHandle)
	{
		throw Exception();
	}

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


	HWND windowHandle2 = CreateWindowA(
		windowClassName.c_str(),
		"window2",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600,
		NULL,
		NULL,
		instanceHandle,
		NULL
		);

	if (!windowHandle2)
	{
		throw Exception();
	}

	auto deviceContextHandle2 = GetDC(windowHandle2);

	if (!deviceContextHandle2)
	{
		throw Exception();
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptorInfo2;
	{
		memset(&pixelFormatDescriptorInfo2, 0, sizeof(pixelFormatDescriptorInfo2));

		pixelFormatDescriptorInfo2.nSize = sizeof(pixelFormatDescriptorInfo2);
		pixelFormatDescriptorInfo2.nVersion = 1;
		pixelFormatDescriptorInfo2.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatDescriptorInfo2.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDescriptorInfo2.cColorBits = 32;
		pixelFormatDescriptorInfo2.cDepthBits = 32;
		pixelFormatDescriptorInfo2.cStencilBits = 0;

		auto pixelFormat = ChoosePixelFormat(deviceContextHandle2, &pixelFormatDescriptorInfo2);
		if (!pixelFormat)
		{
			throw Exception();
		}

		if (!SetPixelFormat(deviceContextHandle2, pixelFormat, &pixelFormatDescriptorInfo2))
		{
			throw Exception();
		}
	}


	auto engine = Make<Graphics::APIs::OpenGL::Engine>();

	auto material = Make<Graphics::Material>();
	auto model = Make<Graphics::Model>();

	auto scene = Make<Graphics::Scene>();

	auto object = Make<Graphics::Object>(material, model, scene);

	auto camera = Make<Graphics::Camera>();

	auto view = Make<TView>(deviceContextHandle);
	auto view2 = Make<TView>(deviceContextHandle2);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while (PeekMessageA(&msg, windowHandle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, windowHandle2, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		auto result = engine->Render(scene, camera);

		view->Present(result);
		view2->Present(result);
	}
}