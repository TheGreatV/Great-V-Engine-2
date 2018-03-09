#include <iostream>

#include <../Graphics/Graphics.hpp>
#include <../OpenGL Graphics/OpenGL Graphics.hpp>
#include <../Windows Graphics/Windows Graphics.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;


class TView:
	public Graphics::APIs::Windows::View
{
protected:
	const ViewportRange viewportRange;
	const InstanceHandle instanceHandle;
	const WindowHandle windowHandle;
	const DeviceContextHandle deviceContextHandle;
public:
	inline TView(const StrongPointer<TView>& this_, const ViewportRange& viewportRange_, const InstanceHandle instanceHandle_, const WindowHandle& windowHandle_, const DeviceContextHandle& deviceContextHandle_):
		View(this_),
		viewportRange(viewportRange_),
		instanceHandle(instanceHandle_),
		windowHandle(windowHandle_),
		deviceContextHandle(deviceContextHandle_)
	{
	}
public:
	inline virtual ViewportRange GetViewportRange() const override
	{
		return viewportRange;
	}
public:
	inline virtual InstanceHandle GetInstanceHandle() const override
	{
		return instanceHandle;
	}
	inline virtual WindowHandle GetWindowHandle() const override
	{
		return windowHandle;
	}
	inline virtual DeviceContextHandle GetDeviceContextHandle() const override
	{
		return deviceContextHandle;
	}
};


void main()
{
	OpenGL::Init();
	OpenIL::Init();
	OpenIL::Enable(OpenIL::State::OriginSet);
	OpenIL::OriginFunc(OpenIL::Origin::UpperLeft);


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
	auto createView = [&](HWND windowHandle)
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

		auto view = Make<TView>(Graphics::View::ViewportRange(IVec2(0), Size2(800, 600)), instanceHandle, windowHandle, deviceContextHandle);

		return Move(view);
	};

	auto openGLWindow1Handle = createWindow("OpenGL #1", 50, 50, 800, 600);
	auto openGLWindow1View = createView(openGLWindow1Handle);


	auto openGLEngine = Make<Graphics::APIs::OpenGL::Engine>();

	auto geometry = Geometry::CreateBox(Vec3(1.0f), Vec3(1.0f), UVec3(1));
	auto geometry2 = Geometry::CreateSphere(0.5f, Vec2(3.0f, 2.0f), UVec2(128, 64));
	auto geometry3 = Geometry::CreateTorus(0.35f, 0.15f, Vec2(6.0f, 2.0f), UVec2(256, 64));
	auto geometry4 = Geometry::CreateCapsule(0.3f, 0.4f, Vec2(3.0f, 2.0f), UVec2(128, 64));

	auto model = Make<Graphics::Model>(geometry);
	auto model2 = Make<Graphics::Model>(geometry2);
	auto model3 = Make<Graphics::Model>(geometry3);
	auto model4 = Make<Graphics::Model>(geometry4);

	auto material = Make<Graphics::Material>();

	auto scene = Make<Graphics::Scene>();

	auto object = Make<Graphics::Object>(material, model, scene);
	auto object2 = Make<Graphics::Object>(material, model, scene);
	{
		object2->SetLocalPosition(Vec3(2.0f, 0.0f, 0.0f));
	}
	auto object3 = Make<Graphics::Object>(material, model2, scene);
	{
		object3->SetLocalPosition(Vec3(-2.0f, 0.0f, 0.0f));
	}
	auto object4 = Make<Graphics::Object>(material, model3, scene);
	{
		object4->SetLocalPosition(Vec3(-4.0f, 0.0f, 0.0f));
	}
	auto object5 = Make<Graphics::Object>(material, model4, scene);
	{
		object5->SetLocalPosition(Vec3(+4.0f, 0.0f, 0.0f));
	}

	auto skybox = Make<Graphics::Environments::Skybox>(scene);

	auto camera = Make<Graphics::Camera>();
	{
		camera->SetPosition(Vec3(0.0f, 0.0f, -5.0f));
	}

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			auto performWindow = [&](HWND windowHandle)
			{
				while (PeekMessageA(&msg, windowHandle, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
				}
			};

			performWindow(openGLWindow1Handle);
		}

		object->LocalRotate(Vec3(0.7f, 1.0f, 0.3f) * 0.5f);
		// object2->LocalRotate(Vec3(0.7f, 1.0f, 0.3f) * 0.5f);
		// object3->LocalRotate(Vec3(0.7f, 1.0f, 0.3f) * 0.5f);
		// object4->LocalRotate(Vec3(0.7f, 1.0f, 0.3f) * 0.5f);
		// object5->LocalRotate(Vec3(0.7f, 1.0f, 0.3f) * 0.5f);

		Float32 movingSpeed = 0.1f;
		if (GetAsyncKeyState(VK_SHIFT))
		{
			movingSpeed *= 5.0f;
		}
		if (GetAsyncKeyState(VK_MENU))
		{
			movingSpeed /= 5.0f;
		}
		if (GetAsyncKeyState('D'))
		{
			camera->Move(Vec3(+movingSpeed, 0.0f, 0.0f));
		}
		if (GetAsyncKeyState('A'))
		{
			camera->Move(Vec3(-movingSpeed, 0.0f, 0.0f));
		}
		if (GetAsyncKeyState('W'))
		{
			camera->Move(Vec3(0.0f, 0.0f, +movingSpeed));
		}
		if (GetAsyncKeyState('S'))
		{
			camera->Move(Vec3(0.0f, 0.0f, -movingSpeed));
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			camera->Move(Vec3(0.0f, +movingSpeed, 0.0f));
		}
		if (GetAsyncKeyState(VK_CONTROL))
		{
			camera->Move(Vec3(0.0f, -movingSpeed, 0.0f));
		}

		Float32 rotatingSpeed = 2.5f;
		if (GetAsyncKeyState(VK_RIGHT))
		{
			camera->Rotate(Vec3(0.0, +rotatingSpeed, 0.0f));
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			camera->Rotate(Vec3(0.0f, -rotatingSpeed, 0.0f));
		}
		if (GetAsyncKeyState(VK_UP))
		{
			camera->Rotate(Vec3(+rotatingSpeed, 0.0, 0.0f));
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			camera->Rotate(Vec3(-rotatingSpeed, 0.0f, 0.0f));
		}
		if (GetAsyncKeyState('E'))
		{
			camera->Rotate(Vec3(0.0, 0.0f, +rotatingSpeed));
		}
		if (GetAsyncKeyState('Q'))
		{
			camera->Rotate(Vec3(0.0f, 0.0f, -rotatingSpeed));
		}

		auto openGLRenderResult = openGLEngine->Render(scene, camera);

		openGLWindow1View->Present(openGLRenderResult);

		Sleep(1000 / 60);
	}
}