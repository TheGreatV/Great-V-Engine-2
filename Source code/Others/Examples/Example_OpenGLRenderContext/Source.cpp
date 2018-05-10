#include <iostream>
#include <thread>
#include <../Common/Common.hpp>
#include <../OpenGL/OpenGL.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__

#include <Windows.h>

#endif

const Size2 windowSize = Size2(200, 120);
const Size2 windowOffset = Size2(30, 50);

HWND GetWindow(HINSTANCE instanceHandle, const std::string& windowClassName, String title, int x, int y)
{
	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	RECT rect;
	{
		rect.left = x;
		rect.right = x + windowSize.x;
		rect.top = y;
		rect.bottom = y + windowSize.y;
	}

	if (!AdjustWindowRect(&rect, style, NULL))
	{
		throw Exception();
	}

	HWND windowHandle = CreateWindowA(
		windowClassName.c_str(),
		title.c_str(),
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
}
HDC GetDeviceContext(HWND windowHandle)
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
}


void main1()
{
	namespace GL = OpenGL::OSs::Windows;

	auto instanceHandle = GetModuleHandleA(NULL);

	std::string windowClassName = "window class";
	{
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
	}

	auto window_1_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_0_Handle		= GetDeviceContext(window_1_0_Handle);
	auto renderContext_1_0_Handle		= MakeStrong<GL::Context_1_0>(deviceContext_1_0_Handle);

	auto window_1_2_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.2", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_2_Handle		= GetDeviceContext(window_1_2_Handle);
	auto renderContext_1_2_Handle		= MakeStrong<GL::Context_1_2>(deviceContext_1_2_Handle);

	auto window_1_3_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.3", windowOffset.x + (windowSize.x + windowOffset.x) * 2, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_3_Handle		= GetDeviceContext(window_1_3_Handle);
	auto renderContext_1_3_Handle		= MakeStrong<GL::Context_1_3>(deviceContext_1_3_Handle);

	auto window_1_4_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.4", windowOffset.x + (windowSize.x + windowOffset.x) * 3, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_4_Handle		= GetDeviceContext(window_1_4_Handle);
	auto renderContext_1_4_Handle		= MakeStrong<GL::Context_1_4>(deviceContext_1_4_Handle);

	auto window_1_5_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.5", windowOffset.x + (windowSize.x + windowOffset.x) * 4, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_5_Handle		= GetDeviceContext(window_1_5_Handle);
	auto renderContext_1_5_Handle		= MakeStrong<GL::Context_1_5>(deviceContext_1_5_Handle);

	auto window_2_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 2.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 1);
	auto deviceContext_2_0_Handle		= GetDeviceContext(window_2_0_Handle);
	auto renderContext_2_0_Handle		= MakeStrong<GL::Context_2_0>(deviceContext_2_0_Handle);

	auto window_2_1_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 2.1", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 1);
	auto deviceContext_2_1_Handle		= GetDeviceContext(window_2_1_Handle);
	auto renderContext_2_1_Handle		= MakeStrong<GL::Context_2_1>(deviceContext_2_1_Handle);

	auto window_3_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_0_Handle		= GetDeviceContext(window_3_0_Handle);
	auto renderContext_3_0_Handle		= MakeStrong<GL::Context_3_0>(deviceContext_3_0_Handle);

	auto window_3_1_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.1", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_1_Handle		= GetDeviceContext(window_3_1_Handle);
	auto renderContext_3_1_Handle		= MakeStrong<GL::Context_3_1>(deviceContext_3_1_Handle);

	auto window_3_2_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.2", windowOffset.x + (windowSize.x + windowOffset.x) * 2, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_2_Handle		= GetDeviceContext(window_3_2_Handle);
	auto renderContext_3_2_Handle		= MakeStrong<GL::Context_3_2>(deviceContext_3_2_Handle);

	auto window_3_3_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.3", windowOffset.x + (windowSize.x + windowOffset.x) * 3, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_3_Handle		= GetDeviceContext(window_3_3_Handle);
	auto renderContext_3_3_Handle		= MakeStrong<GL::Context_3_3>(deviceContext_3_3_Handle);

	auto window_4_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_0_Handle		= GetDeviceContext(window_4_0_Handle);
	auto renderContext_4_0_Handle		= MakeStrong<GL::Context_4_0>(deviceContext_4_0_Handle);

	auto window_4_1_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.1", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_1_Handle		= GetDeviceContext(window_4_1_Handle);
	auto renderContext_4_1_Handle		= MakeStrong<GL::Context_4_1>(deviceContext_4_1_Handle);

	auto window_4_2_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.2", windowOffset.x + (windowSize.x + windowOffset.x) * 2, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_2_Handle		= GetDeviceContext(window_4_2_Handle);
	auto renderContext_4_2_Handle		= MakeStrong<GL::Context_4_2>(deviceContext_4_2_Handle);

	auto window_4_3_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.3", windowOffset.x + (windowSize.x + windowOffset.x) * 3, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_3_Handle		= GetDeviceContext(window_4_3_Handle);
	auto renderContext_4_3_Handle		= MakeStrong<GL::Context_4_3>(deviceContext_4_3_Handle);

	auto window_4_4_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.4", windowOffset.x + (windowSize.x + windowOffset.x) * 4, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_4_Handle		= GetDeviceContext(window_4_4_Handle);
	auto renderContext_4_4_Handle		= MakeStrong<GL::Context_4_4>(deviceContext_4_4_Handle);

	auto window_4_5_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.5", windowOffset.x + (windowSize.x + windowOffset.x) * 5, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_5_Handle		= GetDeviceContext(window_4_5_Handle);
	auto renderContext_4_5_Handle		= MakeStrong<GL::Context_4_5>(deviceContext_4_5_Handle);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while (PeekMessageA(&msg, window_1_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_2_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_3_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_4_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_5_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			
			while (PeekMessageA(&msg, window_2_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_2_1_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}

			while (PeekMessageA(&msg, window_3_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_3_1_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_3_2_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_3_3_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}

			while (PeekMessageA(&msg, window_4_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_1_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_2_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_3_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_4_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_5_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		// OpenGL 1.*
		GL::MakeCurrent(deviceContext_1_0_Handle, renderContext_1_0_Handle->GetHandle());
		{
			renderContext_1_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_0_Handle->ClearColor(1, 0, 0, 0);
			renderContext_1_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_0_Handle->Flush();
			
			SwapBuffers(deviceContext_1_0_Handle);
		}
		GL::MakeCurrent(deviceContext_1_2_Handle, renderContext_1_2_Handle->GetHandle());
		{
			renderContext_1_2_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_2_Handle->ClearColor(1, 0.15f, 0, 0);
			renderContext_1_2_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_2_Handle->Flush();

			SwapBuffers(deviceContext_1_2_Handle);
		}
		GL::MakeCurrent(deviceContext_1_3_Handle, renderContext_1_3_Handle->GetHandle());
		{
			renderContext_1_3_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_3_Handle->ClearColor(1, 0.3f, 0, 0);
			renderContext_1_3_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_3_Handle->Flush();

			SwapBuffers(deviceContext_1_3_Handle);
		}
		GL::MakeCurrent(deviceContext_1_4_Handle, renderContext_1_4_Handle->GetHandle());
		{
			renderContext_1_4_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_4_Handle->ClearColor(1, 0.45f, 0, 0);
			renderContext_1_4_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_4_Handle->Flush();

			SwapBuffers(deviceContext_1_4_Handle);
		}
		GL::MakeCurrent(deviceContext_1_5_Handle, renderContext_1_5_Handle->GetHandle());
		{
			renderContext_1_5_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_5_Handle->ClearColor(1, 0.6f, 0, 0);
			renderContext_1_5_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				auto bufferHandle = renderContext_1_5_Handle->GenBuffer();

				renderContext_1_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
				renderContext_1_5_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({}), OpenGL::Buffer::Usage::Static);

				// TODO

				renderContext_1_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_1_5_Handle->DeleteBuffer(bufferHandle);
			}
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_5_Handle->Flush();

			SwapBuffers(deviceContext_1_5_Handle);
		}

		// OpenGL 2.*
		GL::MakeCurrent(deviceContext_2_0_Handle, renderContext_2_0_Handle->GetHandle());
		{
			renderContext_2_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_2_0_Handle->ClearColor(0, 1, 0, 0);
			renderContext_2_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				auto bufferHandle = renderContext_2_0_Handle->GenBuffer();
				{
					renderContext_2_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_2_0_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_2_0_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_2_0_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_2_0_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_2_0_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_0_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_2_0_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_2_0_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_2_0_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_2_0_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_0_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_2_0_Handle->CreateProgram();
				{
					renderContext_2_0_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_2_0_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_2_0_Handle->LinkProgram(programHandle);

					if (auto linkStatus = renderContext_2_0_Handle->GetProgramLinkStatus(programHandle)); else
					{
						auto programInfoLog = renderContext_2_0_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_2_0_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_2_0_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_2_0_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_2_0_Handle->DeleteShader(vertexShaderHandle);
				renderContext_2_0_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_2_0_Handle->UseProgram(programHandle);
				
				renderContext_2_0_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_2_0_Handle->UseProgram(nullptr);
				renderContext_2_0_Handle->DeleteProgram(programHandle);

				renderContext_2_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_2_0_Handle->DeleteBuffer(bufferHandle);
			}
			renderContext_2_0_Handle->Flush();

			SwapBuffers(deviceContext_2_0_Handle);
		}
		GL::MakeCurrent(deviceContext_2_1_Handle, renderContext_2_1_Handle->GetHandle());
		{
			renderContext_2_1_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_2_1_Handle->ClearColor(0, 1, 0.5f, 0);
			renderContext_2_1_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				auto bufferHandle = renderContext_2_1_Handle->GenBuffer();
				{
					renderContext_2_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_2_1_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_2_1_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_2_1_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_2_1_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_2_1_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_1_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_2_1_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_2_1_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_2_1_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_2_1_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_1_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_2_1_Handle->CreateProgram();
				{
					renderContext_2_1_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_2_1_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_2_1_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_2_1_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_2_1_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_2_1_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_2_1_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_2_1_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_2_1_Handle->DeleteShader(vertexShaderHandle);
				renderContext_2_1_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_2_1_Handle->UseProgram(programHandle);
				
				renderContext_2_1_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_2_1_Handle->UseProgram(nullptr);
				renderContext_2_1_Handle->DeleteProgram(programHandle);

				renderContext_2_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_2_1_Handle->DeleteBuffer(bufferHandle);
			}
			renderContext_2_1_Handle->Flush();

			SwapBuffers(deviceContext_2_1_Handle);
		}

		// OpenGL 3.*
		GL::MakeCurrent(deviceContext_3_0_Handle, renderContext_3_0_Handle->GetHandle());
		{
			renderContext_3_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_0_Handle->ClearColor(0, 0, 1, 0);
			renderContext_3_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_0_Handle->GenVertexArray();
				{
					renderContext_3_0_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_0_Handle->GenBuffer();
				{
					renderContext_3_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_0_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_0_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_0_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_0_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_0_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_0_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_0_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_0_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_0_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_0_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_0_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_0_Handle->CreateProgram();
				{
					renderContext_3_0_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_0_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_0_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_0_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_0_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_0_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_0_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_0_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_0_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_0_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_0_Handle->UseProgram(programHandle);
				
				renderContext_3_0_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_0_Handle->UseProgram(nullptr);
				renderContext_3_0_Handle->DeleteProgram(programHandle);

				renderContext_3_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_0_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_0_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_0_Handle->Flush();

			SwapBuffers(deviceContext_3_0_Handle);
		}
		GL::MakeCurrent(deviceContext_3_1_Handle, renderContext_3_1_Handle->GetHandle());
		{
			renderContext_3_1_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_1_Handle->ClearColor(0, 0.2f, 1, 0);
			renderContext_3_1_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_1_Handle->GenVertexArray();
				{
					renderContext_3_1_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_1_Handle->GenBuffer();
				{
					renderContext_3_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_1_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_1_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_1_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_1_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_1_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_1_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_1_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_1_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_1_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_1_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_1_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_1_Handle->CreateProgram();
				{
					renderContext_3_1_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_1_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_1_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_1_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_1_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_1_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_1_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_1_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_1_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_1_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_1_Handle->UseProgram(programHandle);
				
				renderContext_3_1_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_1_Handle->UseProgram(nullptr);
				renderContext_3_1_Handle->DeleteProgram(programHandle);

				renderContext_3_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_1_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_1_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_1_Handle->Flush();

			SwapBuffers(deviceContext_3_1_Handle);
		}
		GL::MakeCurrent(deviceContext_3_2_Handle, renderContext_3_2_Handle->GetHandle());
		{
			renderContext_3_2_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_2_Handle->ClearColor(0, 0.4f, 1, 0);
			renderContext_3_2_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_2_Handle->GenVertexArray();
				{
					renderContext_3_2_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_2_Handle->GenBuffer();
				{
					renderContext_3_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_2_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_2_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_2_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_2_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_2_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_2_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_2_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_2_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_2_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_2_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_2_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_2_Handle->CreateProgram();
				{
					renderContext_3_2_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_2_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_2_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_2_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_2_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_2_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_2_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_2_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_2_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_2_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_2_Handle->UseProgram(programHandle);
				
				renderContext_3_2_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_2_Handle->UseProgram(nullptr);
				renderContext_3_2_Handle->DeleteProgram(programHandle);

				renderContext_3_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_2_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_2_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_2_Handle->Flush();

			SwapBuffers(deviceContext_3_2_Handle);
		}
		GL::MakeCurrent(deviceContext_3_3_Handle, renderContext_3_3_Handle->GetHandle());
		{
			renderContext_3_3_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_3_Handle->ClearColor(0, 0.6f, 1, 0);
			renderContext_3_3_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_3_Handle->GenVertexArray();
				{
					renderContext_3_3_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_3_Handle->GenBuffer();
				{
					renderContext_3_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_3_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_3_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_3_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_3_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_3_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_3_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_3_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_3_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_3_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_3_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_3_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_3_Handle->CreateProgram();
				{
					renderContext_3_3_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_3_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_3_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_3_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_3_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_3_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_3_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_3_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_3_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_3_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_3_Handle->UseProgram(programHandle);
				
				renderContext_3_3_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_3_Handle->UseProgram(nullptr);
				renderContext_3_3_Handle->DeleteProgram(programHandle);

				renderContext_3_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_3_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_3_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_3_Handle->Flush();

			SwapBuffers(deviceContext_3_3_Handle);
		}

		// OpenGL 4.*
		GL::MakeCurrent(deviceContext_4_0_Handle, renderContext_4_0_Handle->GetHandle());
		{
			renderContext_4_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_0_Handle->ClearColor(0.5f, 0, 1, 0);
			renderContext_4_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_0_Handle->GenVertexArray();
				{
					renderContext_4_0_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_0_Handle->GenBuffer();
				{
					renderContext_4_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_0_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_0_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_0_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_0_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_0_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_0_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_0_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_0_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_0_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_0_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_0_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_0_Handle->CreateProgram();
				{
					renderContext_4_0_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_0_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_0_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_0_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_0_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_0_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_0_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_0_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_0_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_0_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_0_Handle->UseProgram(programHandle);
				
				renderContext_4_0_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_0_Handle->UseProgram(nullptr);
				renderContext_4_0_Handle->DeleteProgram(programHandle);

				renderContext_4_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_0_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_0_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_0_Handle->Flush();

			SwapBuffers(deviceContext_4_0_Handle);
		}
		GL::MakeCurrent(deviceContext_4_1_Handle, renderContext_4_1_Handle->GetHandle());
		{
			renderContext_4_1_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_1_Handle->ClearColor(0.6f, 0, 0.9f, 0);
			renderContext_4_1_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_1_Handle->GenVertexArray();
				{
					renderContext_4_1_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_1_Handle->GenBuffer();
				{
					renderContext_4_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_1_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_1_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_1_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_1_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_1_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_1_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_1_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_1_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_1_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_1_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_1_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_1_Handle->CreateProgram();
				{
					renderContext_4_1_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_1_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_1_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_1_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_1_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_1_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_1_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_1_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_1_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_1_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_1_Handle->UseProgram(programHandle);
				
				renderContext_4_1_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_1_Handle->UseProgram(nullptr);
				renderContext_4_1_Handle->DeleteProgram(programHandle);

				renderContext_4_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_1_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_1_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_1_Handle->Flush();

			SwapBuffers(deviceContext_4_1_Handle);
		}
		GL::MakeCurrent(deviceContext_4_2_Handle, renderContext_4_2_Handle->GetHandle());
		{
			renderContext_4_2_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_2_Handle->ClearColor(0.7f, 0, 0.8f, 0);
			renderContext_4_2_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_2_Handle->GenVertexArray();
				{
					renderContext_4_2_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_2_Handle->GenBuffer();
				{
					renderContext_4_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_2_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_2_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_2_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_2_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_2_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_2_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_2_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_2_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_2_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_2_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_2_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_2_Handle->CreateProgram();
				{
					renderContext_4_2_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_2_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_2_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_2_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_2_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_2_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_2_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_2_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_2_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_2_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_2_Handle->UseProgram(programHandle);
				
				renderContext_4_2_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_2_Handle->UseProgram(nullptr);
				renderContext_4_2_Handle->DeleteProgram(programHandle);

				renderContext_4_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_2_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_2_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_2_Handle->Flush();

			SwapBuffers(deviceContext_4_2_Handle);
		}
		GL::MakeCurrent(deviceContext_4_3_Handle, renderContext_4_3_Handle->GetHandle());
		{
			renderContext_4_3_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_3_Handle->ClearColor(0.8f, 0, 0.7f, 0);
			renderContext_4_3_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_3_Handle->GenVertexArray();
				{
					renderContext_4_3_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_3_Handle->GenBuffer();
				{
					renderContext_4_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_3_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_3_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_3_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_3_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_3_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_3_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_3_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_3_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_3_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_3_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_3_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_3_Handle->CreateProgram();
				{
					renderContext_4_3_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_3_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_3_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_3_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_3_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_3_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_3_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_3_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_3_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_3_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_3_Handle->UseProgram(programHandle);
				
				renderContext_4_3_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_3_Handle->UseProgram(nullptr);
				renderContext_4_3_Handle->DeleteProgram(programHandle);

				renderContext_4_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_3_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_3_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_3_Handle->Flush();

			SwapBuffers(deviceContext_4_3_Handle);
		}
		GL::MakeCurrent(deviceContext_4_4_Handle, renderContext_4_4_Handle->GetHandle());
		{
			renderContext_4_4_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_4_Handle->ClearColor(0.9f, 0, 0.6f, 0);
			renderContext_4_4_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_4_Handle->GenVertexArray();
				{
					renderContext_4_4_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_4_Handle->GenBuffer();
				{
					renderContext_4_4_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_4_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_4_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_4_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_4_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_4_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_4_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_4_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_4_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_4_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_4_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_4_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_4_Handle->CreateProgram();
				{
					renderContext_4_4_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_4_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_4_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_4_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_4_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_4_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_4_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_4_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_4_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_4_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_4_Handle->UseProgram(programHandle);
				
				renderContext_4_4_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_4_Handle->UseProgram(nullptr);
				renderContext_4_4_Handle->DeleteProgram(programHandle);

				renderContext_4_4_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_4_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_4_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_4_Handle->Flush();

			SwapBuffers(deviceContext_4_4_Handle);
		}
		GL::MakeCurrent(deviceContext_4_5_Handle, renderContext_4_5_Handle->GetHandle());
		{
			renderContext_4_5_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_5_Handle->ClearColor(1, 0, 0.5f, 0);
			renderContext_4_5_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_5_Handle->GenVertexArray();
				{
					renderContext_4_5_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_5_Handle->GenBuffer();
				{
					renderContext_4_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_5_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_5_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_5_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_5_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_5_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_5_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_5_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_5_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_5_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_5_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_5_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_5_Handle->CreateProgram();
				{
					renderContext_4_5_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_5_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_5_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_5_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_5_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_5_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_5_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_5_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_5_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_5_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_5_Handle->UseProgram(programHandle);
				
				renderContext_4_5_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_5_Handle->UseProgram(nullptr);
				renderContext_4_5_Handle->DeleteProgram(programHandle);

				renderContext_4_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_5_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_5_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_5_Handle->Flush();

			SwapBuffers(deviceContext_4_5_Handle);
		}

		Sleep(1000 / 60);
	}

	GL::MakeCurrent(nullptr, nullptr);
}
void main()
{
	namespace GL = OpenGL::OSs::Windows;

	auto instanceHandle = GetModuleHandleA(NULL);

	std::string windowClassName = "window class";
	{
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
	}

	auto window1Handle				= GetWindow(instanceHandle, windowClassName, "window 1", 50, 50);
	auto deviceContext1Handle		= GetDeviceContext(window1Handle);
	auto renderContext1Handle		= MakeStrong<GL::Context_2_0>(deviceContext1Handle);

	auto window2Handle				= GetWindow(instanceHandle, windowClassName, "window 2", 500, 50);
	auto deviceContext2Handle		= GetDeviceContext(window2Handle);
	// auto renderContext2Handle		= MakeStrong<GL::Context_2_0>(deviceContext2Handle);

	GL::MakeCurrent(deviceContext1Handle, renderContext1Handle->GetHandle());
	
	auto bufferHandle = renderContext1Handle->GenBuffer();
	{
		renderContext1Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
		renderContext1Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
	}

	auto vertexShaderHandle = renderContext1Handle->CreateShader(OpenGL::Shader::Type::Vertex);
	{
		renderContext1Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
		renderContext1Handle->CompileShader(vertexShaderHandle);

		if (auto compileStatus = renderContext1Handle->GetShaderCompileStatus(vertexShaderHandle)); else
		{
			auto shaderInfoLog = renderContext1Handle->GetShaderInfoLog(vertexShaderHandle);

			throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
		}
	}
	auto fragmentShaderHandle = renderContext1Handle->CreateShader(OpenGL::Shader::Type::Fragment);
	{
		renderContext1Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
		renderContext1Handle->CompileShader(fragmentShaderHandle);

		if (auto compileStatus = renderContext1Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
		{
			auto shaderInfoLog = renderContext1Handle->GetShaderInfoLog(fragmentShaderHandle);

			throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
		}
	}
	auto programHandle = renderContext1Handle->CreateProgram();
	{
		renderContext1Handle->AttachShader(programHandle, vertexShaderHandle);
		renderContext1Handle->AttachShader(programHandle, fragmentShaderHandle);
		renderContext1Handle->LinkProgram(programHandle);

		if (auto linkStatus = renderContext1Handle->GetProgramLinkStatus(programHandle)); else
		{
			auto programInfoLog = renderContext1Handle->GetProgramInfoLog(programHandle);

			throw Exception("Exception during program linking" + programInfoLog);
		}
	}

	const auto attributeLocation = renderContext1Handle->GetAttributeLocation(programHandle, "vPos");

	renderContext1Handle->DeleteShader(vertexShaderHandle);
	renderContext1Handle->DeleteShader(fragmentShaderHandle);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while (PeekMessageA(&msg, window1Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window2Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		GL::MakeCurrent(deviceContext1Handle, renderContext1Handle->GetHandle());
		{
			renderContext1Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext1Handle->ClearColor(1, 0, 0, 0);
			renderContext1Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				renderContext1Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
				renderContext1Handle->UseProgram(programHandle);
				
				if (attributeLocation)
				{
					renderContext1Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
					renderContext1Handle->EnableVertexAttributeArray(attributeLocation);
				}

				renderContext1Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
			}
			renderContext1Handle->Flush();

			SwapBuffers(deviceContext1Handle);
		}
		GL::MakeCurrent(deviceContext2Handle, renderContext1Handle->GetHandle());
		{
			renderContext1Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext1Handle->ClearColor(0, 1, 0, 0);
			renderContext1Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				renderContext1Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
				renderContext1Handle->UseProgram(programHandle);

				if (attributeLocation)
				{
					renderContext1Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
					renderContext1Handle->EnableVertexAttributeArray(attributeLocation);
				}

				renderContext1Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);
			}
			renderContext1Handle->Flush();

			SwapBuffers(deviceContext2Handle);
		}

		Sleep(1000 / 60);
	}

	GL::MakeCurrent(nullptr, nullptr);
}


#pragma region
#pragma endregion



