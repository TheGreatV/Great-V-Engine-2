#include <iostream>

#include <../Graphics/Graphics.hpp>
#include <../OpenGL Graphics/OpenGL Graphics.hpp>
#include <../Windows Graphics/Windows Graphics.hpp>
#include <../OpenIL/OpenIL.hpp>
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


	auto openGLEngine = Make<Graphics::APIs::OpenGL::Engine>(Make<Graphics::APIs::OpenGL::Methods::Forward>());

	auto models = Vector<StrongPointer<Graphics::Model>>();
	{
		for (auto &i : Range(10))
		{
			models.push_back(Make<Graphics::Model>(Geometry::CreateBox(Vec3(1.0f), Vec3(1.0f), UVec3(1))));
			// models.push_back(Make<Graphics::Model>(Geometry::CreateSphere(0.5f, Vec2(3.14f, 3.14f / 2), UVec2(64, 32))));
			// models.push_back(Make<Graphics::Model>(Geometry::CreateCapsule(0.4f, 0.5f, Vec2(3.14f, 3.14f / 2 + 0.5f), UVec2(64, 32))));
			// models.push_back(Make<Graphics::Model>(Geometry::CreateTorus(0.6f, 0.2f, Vec2(8.0f, 2.0f), UVec2(128, 32))));
		}
	}

	auto materials = Vector<StrongPointer<Graphics::Material>>();
	{
		for (auto &i : Range(10))
		{
			auto material1 = Make<Graphics::Material>();
			{
				material1->modules.push_back(Make<Graphics::APIs::OpenGL::Module>(
					"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle.glsl.vertex-shader",
					"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle1.glsl.fragment-shader"
				));

				materials.push_back(material1);
			}
			/*auto material2 = Make<Graphics::Material>();
			{
				material2->modules.push_back(Make<Graphics::APIs::OpenGL::Module>(
					"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle.glsl.vertex-shader",
					"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle2.glsl.fragment-shader"
				));

				materials.push_back(material2);
			}
			auto material3 = Make<Graphics::Material>();
			{
				material3->modules.push_back(Make<Graphics::APIs::OpenGL::Module>(
					"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle.glsl.vertex-shader",
					"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle3.glsl.fragment-shader"
				));

				materials.push_back(material3);
			}*/
		}
	};

	auto scene = Make<Graphics::Scene>();

	auto object = Make<Graphics::Object>(materials[0], models[0], scene);
	auto objects = Vector<StrongPointer<Graphics::Object>>();

	auto directionalLight = Make<Graphics::Lights::Directional>(scene);

	auto skybox = Make<Graphics::Environments::Skybox>(scene);

	auto camera = Make<Graphics::Camera>();
	{
		camera->SetPosition(Vec3(0.0f, 0.0f, -5.0f));
	}

	bool rotate = false;
	bool rotateLock = false;

	double averageFrameTime = 0.0;
	Vector<double> averageFrameTimeBuffer;

	bool changeMaterialsCountLock = false;
	bool changeModelsCountLock = false;
	bool rebuildSceneLock = false;

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

		if (GetAsyncKeyState('R'))
		{
			if (rotateLock == false)
			{
				rotate = !rotate;
				rotateLock = true;
			}
		}
		else
		{
			rotateLock = false;
		}

		const Size count =
			objects.size() < 100 ? 1:
			objects.size() < 1000 ? 10:
			objects.size() < 2000 ? 50:
			objects.size() < 5000 ? 100:
			1000;
		const Float32 minimalDistance = 10.0f;
		const Float32 maximalDistance = 30.0f;
		
		if (GetAsyncKeyState(VK_PRIOR))
		{
			for (auto &i : Range(count))
			{
				auto object = Make<Graphics::Object>(materials[rand() % materials.size()], models[rand() % models.size()], scene);
				
				object->SetLocalPosition(RotateY3(Rnd(360.0)) * Vec3(0.0f, 0.0f, Rnd(minimalDistance, maximalDistance)));
				object->SetLocalAngle(Rnd3(360.0f));

				objects.push_back(object);
			}
		}
		if (GetAsyncKeyState(VK_NEXT))
		{
			for (auto &i : Range(count))
			{
				if (!objects.empty())
				{
					objects.pop_back();
				}
			}
		}

		// std::cout << "objects count: " << objects.size() << std::endl;

		if (rotate)
		{
			object->LocalRotate(Vec3(0.7f, 1.0f, 0.3f));

			for (auto &object : objects)
			{
				object->LocalRotate(Vec3(0.7f, 1.0f, 0.3f));

				auto distance = Length(object->GetPosition());
				auto power = Mix(0.2f, 0.04f, Clamp((distance - minimalDistance) / (maximalDistance - minimalDistance), 0.0f, 1.0f));

				object->SetLocalPosition(RotateY3(power) * object->GetPosition());
			}
		}

		Float32 movingSpeed = 0.1f;
		if (GetAsyncKeyState(VK_SHIFT))
		{
			movingSpeed *= 5.0f;
		}
		if (GetAsyncKeyState('C'))
		{
			movingSpeed /= 10.0f;
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

		if (GetAsyncKeyState(VK_OEM_PLUS))
		{
			if (!changeMaterialsCountLock)
			{
				auto material = Make<Graphics::Material>();
				{
					material->modules.push_back(Make<Graphics::APIs::OpenGL::Module>(
						"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle.glsl.vertex-shader",
						"Media/Shaders/GLSL/Example_OpenGLGraphics/triangle1.glsl.fragment-shader"
					));
				}

				materials.push_back(material);

				changeMaterialsCountLock = true;
			}
		}
		else if (GetAsyncKeyState(VK_OEM_MINUS))
		{
			if (!changeMaterialsCountLock)
			{
				if (materials.size() > 1)
				{
					materials.pop_back();
				}

				changeMaterialsCountLock = true;
			}
		}
		else
		{
			changeMaterialsCountLock = false;
		}

		if (GetAsyncKeyState('0'))
		{
			if (!changeModelsCountLock)
			{
				models.push_back(Make<Graphics::Model>(Geometry::CreateBox(Vec3(1.0f), Vec3(1.0f), UVec3(1))));

				changeModelsCountLock = true;
			}
		}
		else if (GetAsyncKeyState('9'))
		{
			if (!changeModelsCountLock)
			{
				if (models.size() > 1)
				{
					models.pop_back();
				}

				changeModelsCountLock = true;
			}
		}
		else
		{
			changeModelsCountLock = false;
		}

		if (GetAsyncKeyState('T'))
		{
			if (!rebuildSceneLock)
			{
				auto objectsCount = objects.size();

				objects.clear();

				objects.resize(objectsCount);
				
				for (auto &object : objects)
				{
					object = Make<Graphics::Object>(materials[rand() % materials.size()], models[rand() % models.size()], scene);
				
					object->SetLocalPosition(RotateY3(Rnd(360.0)) * Vec3(0.0f, 0.0f, Rnd(minimalDistance, maximalDistance)));
					object->SetLocalAngle(Rnd3(360.0f));
				}

				rebuildSceneLock = true;
			}
		}
		else
		{
			rebuildSceneLock = false;
		}

		// bool changeMaterialsCountLock = false;
		// bool changeModelsCountLock = false;

		auto beginTime = std::chrono::high_resolution_clock::now();

		auto openGLRenderResult = openGLEngine->Render(scene, camera);
		
		openGLWindow1View->Present(openGLRenderResult);

		auto endTime = std::chrono::high_resolution_clock::now();

		auto frameTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count());
		auto frameTimeMs = frameTime / 1000.0;

		averageFrameTimeBuffer.push_back(frameTimeMs);

		if (averageFrameTimeBuffer.size() > 10)
		{
			averageFrameTime = 0.0;

			for (auto t : averageFrameTimeBuffer)
			{
				averageFrameTime += t;
			}

			averageFrameTime /= static_cast<double>(averageFrameTimeBuffer.size());

			averageFrameTimeBuffer.clear();
		}

		std::cout <<
			"materials: " << materials.size() << ", " <<
			"models: " << models.size() << ", " <<
			"frame time: " << averageFrameTime << "ms, " <<
			"objects: " << objects.size() + 1 <<
			std::endl;
		// std::cout << "frame time: " << frameTimeMs << "ms" << std::endl;

		auto timePerFrameMs = 1000.0 / 60.0;

		if (frameTimeMs < timePerFrameMs)
		{
			auto timeToWaitMs = timePerFrameMs - frameTimeMs;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<Size>(timeToWaitMs)));
			
			//auto discreteTimeToWaitMs = glm::floor(timeToWaitMs / 10.0) * 10.0;

			// Sleep(static_cast<DWORD>(timeToWaitMs)); // 1000 / 60);
		}
	}
}