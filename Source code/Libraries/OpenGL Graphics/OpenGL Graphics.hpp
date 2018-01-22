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
						class Context;
					protected:
						using RenderersLookup = Map<Memory<Scene>, StrongPointer<Renderer>>;
						using RendererIt = RenderersLookup::iterator;
					protected:
						static StrongPointer<Context> context;
					protected:
						static inline StrongPointer<Context> GetContext();
					protected:
						RenderersLookup renderersLookup;
					protected:
						using RenderContextsLookup = Map<Memory<APIs::Windows::View>, HGLRC>;
					protected:
						RenderContextsLookup renderContextsLookup;
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
					};
#pragma region Forward::Output
					class Forward::Output:
						public OpenGL::Output
					{
					protected:
						const StrongPointer<Camera> camera;
						const Memory<Renderer> renderer;
					public:
						inline Output() = delete;
						inline Output(const StrongPointer<Output>& this_, const StrongPointer<Camera>& camera_, const Memory<Renderer>& renderer_);
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
					public:
						class ProgramHolder;
						class BuffersHolder;
					protected:
						using ProgramsLookup = Map<Memory<Material>, StrongPointer<ProgramHolder>>;
						using BuffersLookup = Map<Memory<Model>, StrongPointer<BuffersHolder>>;
						using ObjectsTable = Vector<Memory<Object>>;
						using BuffersTable = Map<Memory<BuffersHolder>, ObjectsTable>;
						using ProgramsTable = Map<Memory<ProgramHolder>, BuffersTable>;
						using SceneGraph = Vector<Memory<Object>>; // TODO: optimize
					protected:
						const Memory<Forward> method;
						const Memory<Scene> scene;
					protected:
						ProgramsLookup programsLookup;
						BuffersLookup buffersLookup;
						ProgramsTable programsTable;
						Scene::Version sceneVersion;
						SceneGraph sceneGraph;
					public:
						inline Renderer() = delete;
						inline Renderer(const StrongPointer<Renderer>& this_, const Memory<Scene>& scene_, const Memory<Forward>& method_);
						inline Renderer(const Renderer&) = delete;
						inline virtual ~Renderer() = default;
					public:
						inline Renderer& operator = (const Renderer&) = delete;
					protected:
						inline void UpdateSceneGraph();
						inline void ForceUpdateSceneGraph();
					protected:
						inline void PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_);
					public:
						inline StrongPointer<Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_);
					};
					class Forward::Renderer::ProgramHolder
					{
					public:
						GreatVEngine2::OpenGL::ProgramHandle programHandle;
					};
					class Forward::Renderer::BuffersHolder
					{
					public:
						GreatVEngine2::OpenGL::VertexArrayHandle vertexArrayHandle;
						GreatVEngine2::OpenGL::BufferHandle verticesBufferHandle;
						GreatVEngine2::OpenGL::BufferHandle indicesBufferHandle;
					};
#pragma endregion
#pragma region Forward::Context
					class Forward::Context
					{
					public:
						String windowClassName = "OpenGL render context window class";
						HINSTANCE instanceHandle;
						HWND windowHandle;
						HDC deviceContextHandle;
						HGLRC renderContext;
					public:
						inline Context();
						inline Context(const Context&) = delete;
						inline ~Context();
					public:
						inline Context& operator = (const Context&) = delete;
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

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Output::Output(const StrongPointer<Output>& this_, const StrongPointer<Camera>& camera_, const Memory<Renderer>& renderer_):
	OpenGL::Output(this_),
	camera(camera_),
	renderer(renderer_)
{
}

void GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Output::Present(const Memory<APIs::Windows::View>& view_)
{
	renderer->PresentOn(view_, camera);
}

#pragma endregion

#pragma region Renderer

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::Renderer(const StrongPointer<Renderer>& this_, const Memory<Scene>& scene_, const Memory<Forward>& method_):
	This(this_),
	method(method_),
	scene(scene_),
	sceneVersion(scene_->GetVersion())
{
	ForceUpdateSceneGraph();
}

void GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::ForceUpdateSceneGraph()
{
	auto renderContext = method->GetContext()->renderContext;
	auto deviceContextHandle = method->GetContext()->deviceContextHandle;

	if (!wglMakeCurrent(deviceContextHandle, renderContext))
	{
		throw Exception();
	}

	auto &objects = scene->objects;

	sceneGraph.clear();
	programsTable.clear();

	for (auto &objectMemory : objects)
	{
		auto material = objectMemory->GetMaterial();
		auto materialMemory = material.GetValue();

		auto programHolderMemory = [&]
		{
			auto it = programsLookup.find(materialMemory);

			if (it == programsLookup.end())
			{
				auto programHolder = MakeStrong<ProgramHolder>();

				programsLookup.insert({materialMemory, programHolder});

				auto programHolderMemory = programHolder.GetValue();

				auto program = GreatVEngine2::OpenGL::CreateProgram();
				{
					auto vs = GreatVEngine2::OpenGL::CreateShader(GreatVEngine2::OpenGL::ShaderType::Vertex);
					{
						String source = "#version 330\n uniform mat4 modelViewProjectionMatrix; in vec3 vPos; void main() { gl_Position = modelViewProjectionMatrix * vec4(vPos,1.0f); }";

						GreatVEngine2::OpenGL::ShaderSource(vs, {source});
						GreatVEngine2::OpenGL::CompileShader(vs);

						if (!GreatVEngine2::OpenGL::GetShaderCompileStatus(vs))
						{
							auto log = GreatVEngine2::OpenGL::GetShaderInfoLog(vs);

							throw Exception("Error while compiling shader: " + log);
						}
					}
					auto fs = GreatVEngine2::OpenGL::CreateShader(GreatVEngine2::OpenGL::ShaderType::Fragment);
					{
						String source = "#version 330\nout vec4 oColor; void main() { oColor = vec4(1.0f); }";

						GreatVEngine2::OpenGL::ShaderSource(fs, {source});
						GreatVEngine2::OpenGL::CompileShader(fs);

						if (!GreatVEngine2::OpenGL::GetShaderCompileStatus(fs))
						{
							auto log = GreatVEngine2::OpenGL::GetShaderInfoLog(fs);

							throw Exception("Error while compiling shader: " + log);
						}
					}

					GreatVEngine2::OpenGL::AttachShader(program, vs);
					GreatVEngine2::OpenGL::AttachShader(program, fs);

					GreatVEngine2::OpenGL::LinkProgram(program);

					if (!GreatVEngine2::OpenGL::GetProgramLinkStatus(program))
					{
						auto log = GreatVEngine2::OpenGL::GetProgramInfoLog(program);

						throw Exception("Error while linking program: " + log);
					}

					GreatVEngine2::OpenGL::DetachShader(program, vs);
					GreatVEngine2::OpenGL::DetachShader(program, fs);

					GreatVEngine2::OpenGL::DeleteShader(vs);
					GreatVEngine2::OpenGL::DeleteShader(fs);
				}

				programHolderMemory->programHandle = program;

				return programHolderMemory;
			}
			else
			{
				auto programHolder = (*it).second;
				auto programHolderMemory = programHolder.GetValue();

				return programHolderMemory;
			}
		}();
		auto programIt = [&]
		{
			auto it = programsTable.find(programHolderMemory);

			if (it == programsTable.end())
			{
				auto t = programsTable.insert({programHolderMemory, BuffersTable()});
				auto nIt = t.first;

				return nIt;
			}
			else
			{
				return it;
			}
		}();
		auto &buffersTable = (*programIt).second;

		auto model = objectMemory->GetModel();
		auto modelMemory = model.GetValue();

		auto buffersHolderMemory = [&]
		{
			auto it = buffersLookup.find(modelMemory);

			if (it == buffersLookup.end())
			{
				auto buffersHolder = MakeStrong<BuffersHolder>();

				buffersLookup.insert({modelMemory, buffersHolder});

				auto buffersHolderMemory = buffersHolder.GetValue();

				auto geometry = modelMemory->GetGeometry();

				auto vbo = GreatVEngine2::OpenGL::GenBuffer();
				{
					auto data = Move(geometry->GetVertices(Geometry::VertexPackMode::Pos32F));

					GreatVEngine2::OpenGL::BindBuffer(GreatVEngine2::OpenGL::BufferType::Array, vbo);
					GreatVEngine2::OpenGL::BufferData(GreatVEngine2::OpenGL::BufferType::Array, data.size(), data.data(), GreatVEngine2::OpenGL::BufferUsage::Static);
				}
				auto ibo = GreatVEngine2::OpenGL::GenBuffer();
				{
					auto data = Move(geometry->GetIndices());

					GreatVEngine2::OpenGL::BindBuffer(GreatVEngine2::OpenGL::BufferType::ElementArray, ibo);
					GreatVEngine2::OpenGL::BufferData(GreatVEngine2::OpenGL::BufferType::ElementArray, data.size(), data.data(), GreatVEngine2::OpenGL::BufferUsage::Static);
				}
				auto vao = GreatVEngine2::OpenGL::GenVertexArray();
				{
					GreatVEngine2::OpenGL::BindVertexArray(vao);

					auto programHandle = (*programIt).first->programHandle;

					GreatVEngine2::OpenGL::UseProgram(programHandle);
					GreatVEngine2::OpenGL::BindBuffer(GreatVEngine2::OpenGL::BufferType::Array, vbo);

					auto l1 = GreatVEngine2::OpenGL::GetAttributeLocation(programHandle, "vPos");

					GreatVEngine2::OpenGL::VertexAttribPointer(l1, 3, GreatVEngine2::OpenGL::ComponentType::Float, false, geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F), 0);
					GreatVEngine2::OpenGL::EnableVertexAttribArray(l1);

					/*auto modelMatrix = objectMemory->GetMMat();
					auto viewMatrix = camera_->GetVMat();
					auto viewProjectionMatrix = Perspective(60.0f, aspect, 0.1f, 1000.0f) * Scale4(Vec3(1.0f, 1.0f, 1.0f)) * viewMatrix;
					auto mat = viewProjectionMatrix * modelMatrix;

					auto u1 = GetUniformLocation(programHandle, "modelViewProjectionMatrix");
					UniformMatrix(u1, mat);*/
				}

				buffersHolderMemory->vertexArrayHandle = vao;
				buffersHolderMemory->verticesBufferHandle = vbo;
				buffersHolderMemory->indicesBufferHandle = ibo;

				return buffersHolderMemory;
			}
			else
			{
				auto buffersHolder = (*it).second;
				auto buffersHolderMemory = buffersHolder.GetValue();

				return buffersHolderMemory;
			}
		}();
		auto buffersIt = [&]
		{
			auto it = buffersTable.find(buffersHolderMemory);

			if (it == buffersTable.end())
			{
				auto t = buffersTable.insert({buffersHolderMemory, ObjectsTable()});
				auto nIt = t.first;

				return nIt;
			}
			else
			{
				return it;
			}
		}();
		auto &objectsTable = (*buffersIt).second;

		objectsTable.push_back(objectMemory);

		sceneGraph.push_back(objectMemory);
	}

	if (!wglMakeCurrent(nullptr, nullptr))
	{
		throw Exception();
	}
}
void GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::UpdateSceneGraph()
{
	auto currentSceneVersion = scene->GetVersion();

	if (currentSceneVersion != sceneVersion)
	{
		ForceUpdateSceneGraph();

		sceneVersion = currentSceneVersion;
	}
}

void GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_)
{
	UpdateSceneGraph();

	auto deviceContextHandle = view_->GetDeviceContextHandle();
	auto renderContext = method->GetContext()->renderContext;

	using namespace GreatVEngine2::OpenGL;

	if (!wglMakeCurrent(deviceContextHandle, renderContext))
	{
		throw Exception();
	}

	auto viewport = view_->GetViewportRange();
	auto aspect = viewport.GetAspect();

	glViewport(viewport.GetPosition().x, viewport.GetPosition().y, viewport.GetSize().x, viewport.GetSize().y);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDisable(GL_BLEND);


	// draw objects
	for (auto &programIt : programsTable)
	{
		auto &programHolder = programIt.first;
		auto programHandle = programHolder->programHandle;
		auto &buffersTable = programIt.second;

		for (auto &buffersIt : buffersTable)
		{
			auto &buffersHolder = buffersIt.first;
			auto vertexArrayHandle = buffersHolder->vertexArrayHandle;
			auto verticesBufferHandle = buffersHolder->verticesBufferHandle;
			auto indicesBufferHandle = buffersHolder->indicesBufferHandle;
			auto &objectsTable = buffersIt.second;

			UseProgram(programHandle);
			BindVertexArray(vertexArrayHandle);
			BindBuffer(BufferType::ElementArray, indicesBufferHandle);

			ValidateProgram(programHandle);
			{
				if (!GetProgramValidateStatus(programHandle))
				{
					auto log = GetProgramInfoLog(programHandle);

					throw Exception("Error while validating program: " + log);
				}
			}
			
			for (auto &objectMemory : objectsTable)
			{
				auto modelMatrix = objectMemory->GetMMat();
				auto viewMatrix = camera_->GetVMat();
				auto viewProjectionMatrix = Perspective(60.0f, aspect, 0.1f, 1000.0f) * Scale4(Vec3(1.0f, 1.0f, 1.0f)) * viewMatrix;
				auto mat = viewProjectionMatrix * modelMatrix;

				auto u1 = GetUniformLocation(programHandle, "modelViewProjectionMatrix");
				UniformMatrix(u1, mat);

				auto geometry = objectMemory->GetModel()->GetGeometry();
				
				if (geometry->GetTopology() == Geometry::Topology::Triangles)
				{
					glDrawElements(GL_TRIANGLES, geometry->GetIndicesCount(), GL_UNSIGNED_INT, 0);
				}
				else
				{
					throw Exception();
				}
			}
		}
	}


	glFlush();

	SwapBuffers(deviceContextHandle);

	wglMakeCurrent(nullptr, nullptr);
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Output> GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Renderer::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	auto output = Make<Output>(camera_, this);

	return Move(output);
}

#pragma endregion

#pragma region Context

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Context::Context()
{
	instanceHandle = GetModuleHandleA(NULL);

	WNDCLASSA windowClass;
	{
		memset(&windowClass, 0, sizeof(windowClass));

		windowClass.lpszClassName = windowClassName.c_str();
		windowClass.hInstance = instanceHandle;
		windowClass.lpfnWndProc = DefWindowProcA;
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if (!RegisterClassA(&windowClass))
		{
			throw Exception(); // TODO
		}
	}

	windowHandle = CreateWindowA(
		windowClassName.c_str(),
		"window",
		NULL,
		0, 0, 0, 0,
		NULL,
		NULL,
		instanceHandle,
		NULL
	);

	if (!windowHandle)
	{
		throw Exception(); // TODO
	}

	deviceContextHandle = GetDC(windowHandle);

	if (!deviceContextHandle)
	{
		throw Exception(); // TODO
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
			throw Exception(); // TODO
		}

		if (!SetPixelFormat(deviceContextHandle, pixelFormat, &pixelFormatDescriptorInfo))
		{
			throw Exception(); // TODO
		}
	}

	const GLint attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0, 0
	};

	renderContext = GreatVEngine2::OpenGL::wglCreateContextAttribsARB(deviceContextHandle, nullptr, attribs);
}
GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Context::~Context()
{
	auto currentRenderContext = wglGetCurrentContext();

	if (currentRenderContext == renderContext)
	{
		wglMakeCurrent(nullptr, nullptr);
	}

	if (!wglDeleteContext(renderContext))
	{
		throw Exception(); // TODO
	}

	DestroyWindow(windowHandle); // TODO: check for errors

	UnregisterClassA(windowClassName.c_str(), instanceHandle); // TODO: check for errors
}

#pragma endregion


GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Context> GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::GetContext()
{
	if (!context)
	{
		context = MakeStrong<Context>();
	}

	return context;
}


GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Forward(const StrongPointer<Forward>& this_):
	Method(this_)
{
}

GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::RendererIt GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::FindOrCreate(const Memory<Scene>& sceneMemory_)
{
	auto it = renderersLookup.find(sceneMemory_);

	if (it == renderersLookup.end())
	{
		auto nIt = renderersLookup.insert({sceneMemory_, Make<Renderer>(sceneMemory_, this)});

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

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


