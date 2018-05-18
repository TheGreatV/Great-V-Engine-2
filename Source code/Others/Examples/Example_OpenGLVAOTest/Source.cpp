#include <iostream>

#include <../Common/Common.hpp>
#include <../OpenGL/OpenGL.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;
namespace GL = OpenGL;
namespace WGL = OpenGL::OSs::Windows;


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

	auto windowHandle = [&](String t, int x, int y, int w, int h)
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
	}("window", 50, 50, 800, 600);
	auto deviceContextHandle = GetDC(windowHandle);
	{
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
	};
	auto context = MakeStrong<WGL::Context_3_1>(deviceContextHandle);

	WGL::MakeCurrent(deviceContextHandle, context->GetHandle());

	auto program = context->CreateProgram();
	{
		const auto &vertexShaderHandle = context->CreateShader(GL::Shader::Type::Vertex);
		{
			context->ShaderSource(vertexShaderHandle, "#version 330\nin vec2 vPos; void main() { gl_Position = vec4(vPos,0,1); }");
			context->CompileShader(vertexShaderHandle);

			const auto &compileStatus = context->GetShaderCompileStatus(vertexShaderHandle);

			if (!compileStatus)
			{
				const auto &log = context->GetShaderInfoLog(vertexShaderHandle);

				throw Exception("Error while compiling shader: " + log);
			}
		}
		const auto &fragmentShaderHandle	= context->CreateShader(GL::Shader::Type::Fragment);
		{
			context->ShaderSource(fragmentShaderHandle, "#version 330\nuniform Global { float x; }; out vec4 oColor; void main() { oColor = vec4(x, 0, 1 - x, 1); }");
			context->CompileShader(fragmentShaderHandle);

			const auto &compileStatus = context->GetShaderCompileStatus(fragmentShaderHandle);

			if (!compileStatus)
			{
				const auto &log = context->GetShaderInfoLog(fragmentShaderHandle);

				throw Exception("Error while compiling shader: " + log);
			}
		}

		context->AttachShader(program, vertexShaderHandle);
		context->AttachShader(program, fragmentShaderHandle);

		context->LinkProgram(program);

		const auto &linkStatus = context->GetProgramLinkStatus(program);

		if (!linkStatus)
		{
			const auto &log = context->GetProgramInfoLog(program);

			throw Exception("Error while linking program: " + log);
		}

		context->DeleteShader(vertexShaderHandle);
		context->DeleteShader(fragmentShaderHandle);
	}

	auto attributeLocation = context->GetAttributeLocation(program, "vPos");
	auto blockIndex = context->GetUniformBlockIndex(program, "Global");
	{
		context->UniformBlockBinding(program, blockIndex, GL::UniformBlock::Binding(0));
	}

	auto vbo1 = context->GenBuffer();
	{
		context->BindBuffer(OpenGL::Buffer::Type::Array, vbo1);
		
		context->BufferData<Vec2>(OpenGL::Buffer::Type::Array, {
			Vec2(-0.5f, -0.5f) * Vec2(0.5f) - Vec2(0.5f, 0.0f),
			Vec2(+0.5f, -0.5f) * Vec2(0.5f) - Vec2(0.5f, 0.0f),
			Vec2(-0.5f, +0.5f) * Vec2(0.5f) - Vec2(0.5f, 0.0f),
			Vec2(+0.5f, +0.5f) * Vec2(0.5f) - Vec2(0.5f, 0.0f),
		}, GL::Buffer::Usage::Static);
		
		context->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
	}
	auto ibo1 = context->GenBuffer();
	{
		context->BindBuffer(OpenGL::Buffer::Type::Array, ibo1);

		context->BufferData<UInt32>(OpenGL::Buffer::Type::Array, { 0,1,2, 1,3,2 }, GL::Buffer::Usage::Static);

		context->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
	}
	auto ubo1 = context->GenBuffer();
	{
		context->BindBuffer(OpenGL::Buffer::Type::Array, ubo1);

		context->BufferData<Float32>(OpenGL::Buffer::Type::Array, { 1.0f }, GL::Buffer::Usage::Static);

		context->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
	}
	auto vao1 = context->GenVertexArray();
	{
		context->BindVertexArray(vao1);

		context->BindBuffer(GL::Buffer::Type::Array, vbo1);
		context->VertexAttributePointer(attributeLocation, 2, GL::Program::Attribute::Type::Float, false, sizeof(Vec2), 0);
		context->EnableVertexAttributeArray(attributeLocation);

		context->BindBuffer(GL::Buffer::Type::ElementArray, ibo1);

		context->BindVertexArray(nullptr);
		context->BindBuffer(GL::Buffer::Type::Array, nullptr);
	}

	auto vbo2 = context->GenBuffer();
	{
		context->BindBuffer(OpenGL::Buffer::Type::Array, vbo2);
		
		context->BufferData<Vec2>(OpenGL::Buffer::Type::Array, {
			Vec2(-0.5f, -0.5f) * Vec2(0.5f) + Vec2(0.5f, 0.0f), Vec2(0.0f),
			Vec2(+0.5f, -0.5f) * Vec2(0.5f) + Vec2(0.5f, 0.0f), Vec2(0.0f),
			Vec2(+0.0f, +0.5f) * Vec2(0.5f) + Vec2(0.5f, 0.0f), Vec2(0.0f),
		}, GL::Buffer::Usage::Static);
		
		context->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
	}
	auto ibo2 = context->GenBuffer();
	{
		context->BindBuffer(OpenGL::Buffer::Type::Array, ibo2);

		context->BufferData<UInt32>(OpenGL::Buffer::Type::Array, { 0,1,2 }, GL::Buffer::Usage::Static);

		context->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
	}
	auto ubo2 = context->GenBuffer();
	{
		context->BindBuffer(OpenGL::Buffer::Type::Array, ubo2);

		context->BufferData<Float32>(OpenGL::Buffer::Type::Array, { 0.0f }, GL::Buffer::Usage::Static);

		context->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
	}
	auto vao2 = context->GenVertexArray();
	{
		context->BindVertexArray(vao2);

		context->BindBuffer(GL::Buffer::Type::Array, vbo2);
		context->VertexAttributePointer(attributeLocation, 2, GL::Program::Attribute::Type::Float, false, sizeof(Vec2) * 2, 0);
		context->EnableVertexAttributeArray(attributeLocation);

		context->BindBuffer(GL::Buffer::Type::ElementArray, ibo2);

		context->BindVertexArray(nullptr);
		context->BindBuffer(GL::Buffer::Type::Array, nullptr);
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

			performWindow(windowHandle);
		}

		context->ConfigureViewport(0, 0, 800, 600);
		context->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		context->Clear(GL_COLOR_BUFFER_BIT);

		context->UseProgram(program);

		context->BindVertexArray(vao1);
		context->BindBufferBase(GL::Buffer::Type::Uniform, GL::UniformBlock::Binding(0), ubo1);
		context->DrawElements(GL::PrimitiveType::Triangles, 6, GL::IndexType::UInt32, 0);
		context->BindVertexArray(nullptr);

		context->BindVertexArray(vao2);
		context->BindBufferBase(GL::Buffer::Type::Uniform, GL::UniformBlock::Binding(0), ubo2);
		context->DrawElements(GL::PrimitiveType::Triangles, 3, GL::IndexType::UInt32, 0);
		context->BindVertexArray(nullptr);

		context->Flush();

		SwapBuffers(deviceContextHandle);

		std::this_thread::sleep_for(std::chrono::microseconds(1000 / 60));
	}
	
	WGL::MakeCurrent(nullptr, nullptr);
}