#include <iostream>
#include <../Common/Common.hpp>
#include <../OpenGL/OpenGL.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#include <Windows.h>
#include <gl/gl.h>


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
			throw GVE::Exception();
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
		throw GVE::Exception();
	}

	auto deviceContextHandle = GetDC(windowHandle);

	if (!deviceContextHandle)
	{
		throw GVE::Exception();
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
			throw GVE::Exception();
		}

		if (!SetPixelFormat(deviceContextHandle, pixelFormat, &pixelFormatDescriptorInfo))
		{
			throw GVE::Exception();
		}
	}


	const GLint attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0, 0
	};

	auto openGLRenderContextHandle = OpenGL::wglCreateContextAttribsARB(deviceContextHandle, nullptr, attribs);

	wglMakeCurrent(deviceContextHandle, openGLRenderContextHandle);

	if (glGetError() != GL_NO_ERROR) throw GVE::Exception();

	using namespace OpenGL;

	GLuint vbo;
	{
		Vector<float> data = { -0.5f, -0.5f, +0.5f, -0.5f, +0.0f, +0.5f };

		glGenBuffers(1, &vbo); if (glGetError() != GL_NO_ERROR) throw GVE::Exception();
		glBindBuffer(GL_ARRAY_BUFFER, vbo); if (glGetError() != GL_NO_ERROR) throw GVE::Exception();
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* data.size(), data.data(), GL_STATIC_DRAW); if (glGetError() != GL_NO_ERROR) throw GVE::Exception();
	}
	GLuint program = glCreateProgram();
	{
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		{
			std::string source = "#version 330\nin vec2 vPos; void main() { gl_Position = vec4(vPos,0.0f,1.0f); }";
			const char* d = source.c_str();
			GLint s = source.length();
			glShaderSource(vs, 1, &d, &s);
			glCompileShader(vs);
			GLint compileResult;
			glGetShaderiv(vs, GL_COMPILE_STATUS, &compileResult);
			if (compileResult != GL_TRUE)
			{
				throw GVE::Exception();
			}
		}
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		{
			std::string source = "#version 330\nout vec4 oColor; void main() { oColor = vec4(1.0f); }";
			const char* d = source.c_str();
			GLint s = source.length();
			glShaderSource(fs, 1, &d, &s);
			glCompileShader(fs);
			GLint compileResult;
			glGetShaderiv(fs, GL_COMPILE_STATUS, &compileResult);
			if (compileResult != GL_TRUE)
			{
				throw GVE::Exception();
			}
		}

		glAttachShader(program, vs);
		glAttachShader(program, fs);

		glLinkProgram(program);
		
		GLint result;
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result != GL_TRUE)
		{
			throw GVE::Exception();
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	GLuint vao;
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		auto l1 = glGetAttribLocation(program, "vPos");
		glVertexAttribPointer(l1, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 2, 0);
		glEnableVertexAttribArray(l1);
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

		glViewport(0, 0, 800, 600);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glFlush();

		SwapBuffers(deviceContextHandle);
	}

	if (!wglDeleteContext(openGLRenderContextHandle))
	{
		throw GVE::Exception();
	}


	// std::system("pause");
}