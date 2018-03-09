#include <iostream>
#include <../Common/Common.hpp>
#include <../OpenGL/OpenGL.hpp>
#include <../OpenIL/OpenIL.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#include <Windows.h>
#include <gl/gl.h>


void main()
{
	OpenGL::Init();
	OpenIL::Init();

	auto createTexture = [](const StrongPointer<Image2D>& image_)
	{
		using namespace OpenGL;

		auto texture = GenTexture();
		{
			ActiveTexture(0); BindTexture(TextureType::D2, texture);

			TextureParameterWrap(TextureType::D2, TextureWrap::Repeat, TextureWrap::Repeat, TextureWrap::Repeat);
			TextureParameterFilter(TextureType::D2, TextureMinificationFilter::Nearest, TextureMagnificationFilter::Nearest);

			for (auto &mipmapIndex : Range(image_->GetMipmapsCount()))
			{
				auto &mipmap = (*image_)[mipmapIndex];
				
				TextureImage(mipmapIndex, GetInternalFormat(image_), mipmap.GetSize(), GetFormat(image_), GetDataType(image_), mipmap.GetData());
			}
		}

		return texture;
	};

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

	auto texture = createTexture(OpenIL::Load("Media/Images/Test.png"));

	auto vbo = GenBuffer();
	{
		Vector<float> data = {
			-0.5f, -0.5f,	0.0f, 0.0f,
			+0.5f, -0.5f,	1.0f, 0.0f,
			+0.0f, +0.5f,	0.5f, 1.0f,
		};

		BindBuffer(BufferType::Array, vbo);
		BufferData(BufferType::Array, sizeof(Float32)* data.size(), data.data(), BufferUsage::Static);
	}
	auto program = CreateProgram();
	{
		auto vs = CreateShader(ShaderType::Vertex);
		{
			String source = "#version 330\nin vec2 vPos; in vec2 vTex; out vec2 fTex; void main() { gl_Position = vec4(vPos,0.0f,1.0f); fTex = vTex; }";
			
			ShaderSource(vs, {source});
			CompileShader(vs);
		}
		auto fs = CreateShader(ShaderType::Fragment);
		{
			String source = "#version 330\nuniform sampler2D color; in vec2 fTex; out vec4 oColor; void main() { oColor = texture(color, fTex); }";

			ShaderSource(fs, {source});
			CompileShader(fs);
		}

		AttachShader(program, vs);
		AttachShader(program, fs);

		LinkProgram(program);
		
		UseProgram(program);

		if (auto uniformLocation = GetUniformLocation(program, "color"))
		{
			SetUniform(uniformLocation, 0);
		}

		DeleteShader(vs);
		DeleteShader(fs);
	}
	auto vao = GenVertexArray();
	{
		BindVertexArray(vao);

		UseProgram(program);
		BindBuffer(BufferType::Array, vbo);

		if (auto attributeLocation = GetAttributeLocation(program, "vPos"))
		{
			VertexAttribPointer(attributeLocation, 2, ComponentType::Float, false, sizeof(Float32)* 4, 0);
			EnableVertexAttribArray(attributeLocation);
		}
		if (auto attributeLocation = GetAttributeLocation(program, "vTex"))
		{
			VertexAttribPointer(attributeLocation, 2, ComponentType::Float, false, sizeof(Float32)* 4, sizeof(Float32)* 2);
			EnableVertexAttribArray(attributeLocation);
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

		glViewport(0, 0, 800, 600);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glFlush();

		SwapBuffers(deviceContextHandle);
	}

	BindVertexArray(nullptr); DeleteVertexArray(vao);
	UseProgram(nullptr); DeleteProgram(program);
	BindBuffer(BufferType::Array, nullptr); DeleteBuffer(vbo);
	BindTexture(TextureType::D2, nullptr); DeleteTexture(texture);

	if (!wglDeleteContext(openGLRenderContextHandle))
	{
		throw GVE::Exception();
	}


	// std::system("pause");
}