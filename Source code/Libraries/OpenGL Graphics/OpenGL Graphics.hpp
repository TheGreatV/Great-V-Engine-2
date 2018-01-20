#pragma region Include

#pragma once
#pragma warning (disable : 4503) // names is too long

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
			namespace OpenGL
			{
				class Output:
					public Graphics::Output
				{
				public:
					inline Output() = delete;
					inline Output(const StrongPointer<Output>& this_);
					inline Output(const Output&) = delete;
					inline virtual ~Output() = default;
				public:
					inline Output& operator = (const Output&) = delete;
				protected:
					inline virtual void Present(const Memory<APIs::Windows::View>& view_) = 0;
				public:
					inline virtual void SignalPresented(const StrongPointer<View>& view_) override;
				};
				class Engine:
					public Graphics::Engine
				{
				protected:
					StrongPointer<Method> method = Make<Methods::Forward>();
				public:
					inline Engine() = delete;
					inline Engine(const StrongPointer<Engine>& this_);
					inline Engine(const Engine&) = delete;
					inline virtual ~Engine() = default;
				public:
					inline Engine& operator = (const Engine&) = delete;
				public:
					inline virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
				};

				class Method:
					public This<Method>
				{
				public:
					inline Method() = delete;
					inline Method(const StrongPointer<Method>& this_);
					inline Method(const Method&) = delete;
					inline virtual ~Method() = default;
				public:
					inline Method& operator = (const Method&) = delete;
				public:
					inline virtual StrongPointer<OpenGL::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) = 0;
				};
				namespace Methods
				{
					class Forward:
						public Method
					{
					protected:
						class Output; friend Output;
						class Renderer; friend Renderer;
					protected:
						using RenderersLookup = Map<Memory<Scene>, StrongPointer<Renderer>>;
						using RendererIt = RenderersLookup::iterator;
					protected:
						RenderersLookup renderersLookup;
					protected:
						using RenderContextsLookup = Map<Memory<APIs::Windows::View>, HGLRC>;
					protected:
						RenderContextsLookup renderContextsLookup;
						HGLRC renderContext = 0;
					public:
						inline Forward() = delete;
						inline Forward(const StrongPointer<Forward>& this_);
						inline Forward(const Forward&) = delete;
						inline virtual ~Forward() = default;
					public:
						inline Forward& operator = (const Forward&) = delete;
					protected:
						inline RendererIt FindOrCreate(const Memory<Scene>& sceneMemory_);
					public:
						inline virtual StrongPointer<OpenGL::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
					protected:
						HGLRC FindOrCreate(const Memory<APIs::Windows::View>& view_);
					protected:
						inline void PresentOn(const Memory<APIs::Windows::View>& view_);
					};
#pragma region Forward::Output
					class Forward::Output:
						public OpenGL::Output
					{
					protected:
						const Memory<Renderer> renderer;
					public:
						inline Output() = delete;
						inline Output(const StrongPointer<Output>& this_, const Memory<Renderer>& renderer_);
						inline Output(const Output&) = delete;
						inline virtual ~Output() = default;
					public:
						inline Output& operator = (const Output&) = delete;
					protected:
						inline virtual void Present(const Memory<APIs::Windows::View>& view_) override;
					};
#pragma endregion
#pragma region Forward::Renderer
					class Forward::Renderer:
						public This<Renderer>
					{
						friend Output;
					protected:
						const Memory<Forward> method;
					public:
						inline Renderer() = delete;
						inline Renderer(const StrongPointer<Renderer>& this_, const Memory<Forward>& method_);
						inline Renderer(const Renderer&) = delete;
						inline virtual ~Renderer() = default;
					public:
						inline Renderer& operator = (const Renderer&) = delete;
					public:
						inline StrongPointer<Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_);
					};
#pragma endregion
				}
			}
		}
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region APIs

#pragma region OpenGL

#pragma region Output

GreatVEngine2::Graphics::APIs::OpenGL::Output::Output(const StrongPointer<Output>& this_):
	Graphics::Output(this_)
{
}

void GreatVEngine2::Graphics::APIs::OpenGL::Output::SignalPresented(const StrongPointer<View>& view_)
{
	if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
	{
		Present(windowsView.GetValue());
	}
}

#pragma endregion

#pragma region Engine

GreatVEngine2::Graphics::APIs::OpenGL::Engine::Engine(const StrongPointer<Engine>& this_):
	Graphics::Engine(this_)
{
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::Output> GreatVEngine2::Graphics::APIs::OpenGL::Engine::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	return method->Render(scene_, camera_);
}

#pragma endregion

#pragma region Method

GreatVEngine2::Graphics::APIs::OpenGL::Method::Method(const StrongPointer<Method>& this_):
	This(this_)
{
}

#pragma endregion

#pragma region Methods

#pragma region Forward

#pragma region Output

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Output::Output(const StrongPointer<Output>& this_, const Memory<Renderer>& renderer_):
	OpenGL::Output(this_),
	renderer(renderer_)
{
}

void GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Output::Present(const Memory<APIs::Windows::View>& view_)
{
	renderer->method->PresentOn(view_);
}

#pragma endregion

#pragma region Renderer

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::Renderer(const StrongPointer<Renderer>& this_, const Memory<Forward>& method_):
	This(this_),
	method(method_)
{
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Output> GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	auto output = Make<Output>(this);

	return Move(output);
}

#pragma endregion


GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Forward(const StrongPointer<Forward>& this_):
	Method(this_)
{
}

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::RendererIt GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::FindOrCreate(const Memory<Scene>& sceneMemory_)
{
	auto it = renderersLookup.find(sceneMemory_);

	if (it == renderersLookup.end())
	{
		auto nIt = renderersLookup.insert({sceneMemory_, Make<Renderer>(this)});

		return nIt.first;
	}
	else
	{
		return it;
	}
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::OpenGL::Output> GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	auto sceneMemory = scene_.GetValue();
	auto rendererIt = FindOrCreate(sceneMemory);
	auto renderer = (*rendererIt).second;

	return renderer->Render(scene_, camera_);
}

HGLRC GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::FindOrCreate(const Memory<APIs::Windows::View>& view_)
{
	/*auto it = renderContextsLookup.find(view_);

	if (it == renderContextsLookup.end())
	{
		const GLint attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0, 0
		};

		auto deviceContextHandle = view_->GetDeviceContextHandle();
		auto renderContext = GreatVEngine2::OpenGL::wglCreateContextAttribsARB(deviceContextHandle, nullptr, attribs);

		renderContextsLookup.insert({view_, renderContext});

		return renderContext;
	}
	else
	{
		auto renderContext = (*it).second;

		return renderContext;
	}*/

	if (renderContext == 0)
	{
		const GLint attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0, 0
		};

		auto deviceContextHandle = view_->GetDeviceContextHandle();
		
		renderContext = GreatVEngine2::OpenGL::wglCreateContextAttribsARB(deviceContextHandle, nullptr, attribs);
	}

	return renderContext;
}

void GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::PresentOn(const Memory<APIs::Windows::View>& view_)
{
	auto deviceContextHandle = view_->GetDeviceContextHandle();
	auto renderContext = FindOrCreate(view_);

	using namespace GreatVEngine2::OpenGL;

	if (!wglMakeCurrent(deviceContextHandle, renderContext))
	{
		throw Exception();
	}


	auto vbo = GenBuffer();
	{
		Vector<float> data = {-0.5f, -0.5f, +0.5f, -0.5f, +0.0f, +0.5f};

		BindBuffer(BufferType::Array, vbo);
		BufferData(BufferType::Array, sizeof(float)* data.size(), data.data(), BufferUsage::Static);
	}
	auto program = CreateProgram();
	{
		auto vs = CreateShader(ShaderType::Vertex);
		{
			String source = "#version 330\nin vec2 vPos; void main() { gl_Position = vec4(vPos,0.0f,1.0f); }";

			ShaderSource(vs, {source});
			CompileShader(vs);

			if (!GetShaderCompileStatus(vs))
			{
				auto log = GetShaderInfoLog(vs);

				throw Exception("Error while compiling shader: " + log);
			}
		}
		auto fs = CreateShader(ShaderType::Fragment);
		{
			std::string source = "#version 330\nout vec4 oColor; void main() { oColor = vec4(1.0f); }";

			ShaderSource(fs, {source});
			CompileShader(fs);

			if (!GetShaderCompileStatus(fs))
			{
				auto log = GetShaderInfoLog(fs);

				throw Exception("Error while compiling shader: " + log);
			}
		}

		AttachShader(program, vs);
		AttachShader(program, fs);

		LinkProgram(program);

		if (!GetProgramLinkStatus(program))
		{
			auto log = GetProgramInfoLog(program);

			throw Exception("Error while linking program: " + log);
		}

		DeleteShader(vs);
		DeleteShader(fs);
	}
	auto vao = GenVertexArray();
	{
		BindVertexArray(vao);

		UseProgram(program);
		BindBuffer(BufferType::Array, vbo);

		auto l1 = GetAttribLocation(program, "vPos");

		VertexAttribPointer(l1, 2, ComponentType::Float, false, sizeof(float)* 2, 0);
		EnableVertexAttribArray(l1);
	}

	glViewport(0, 0, 800, 600);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ValidateProgram(program);
	{
		if (!GetProgramValidateStatus(program))
		{
			auto log = GetProgramInfoLog(program);

			throw Exception("Error while validating program: " + log);
		}
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();

	SwapBuffers(deviceContextHandle);

	UnbindVertexArray(); DeleteVertexArray(vao);
	UnuseProgram(); DeleteProgram(program);
	UnbindBuffer(BufferType::Array); DeleteBuffer(vbo);

	wglMakeCurrent(nullptr, nullptr);
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


