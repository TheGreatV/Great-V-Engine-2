#pragma region Include

#pragma once
#pragma warning (disable : 4503) // names is too long

#include "Header.hpp"

#include <string>
#include <fstream>
#include <streambuf>

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
				namespace GL = GreatVEngine2::OpenGL;

				class Module:
					public Material::Module
				{
				public:
					const String albedoFilename;
					const String normalsFilename;
					const String roughnessFilename;
					const String metalnessFilename;
					const String occlusionFilename;
				public:
					inline Module(const StrongPointer<Module>& this_,
						const String& albedoFilename_,
						const String& normalsFilename_,
						const String& roughnessFilename_,
						const String& metalnessFilename_,
						const String& occlusionFilename_
					): Material::Module(this_),
						albedoFilename(albedoFilename_),
						normalsFilename(normalsFilename_),
						roughnessFilename(roughnessFilename_),
						metalnessFilename(metalnessFilename_),
						occlusionFilename(occlusionFilename_)
					{
					}
					virtual ~Module() override = default;
				};

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
						class SkyboxHolder;
					protected:
						using ProgramsLookup = Map<Memory<Material>, StrongPointer<ProgramHolder>>;
						using BuffersLookup = Map<Memory<Model>, StrongPointer<BuffersHolder>>;
						using SkyboxesLookup = Map<Memory<Environments::Skybox>, StrongPointer<SkyboxHolder>>;
						using ObjectsTable = Vector<Memory<Object>>;
						using BuffersTable = Map<Memory<BuffersHolder>, ObjectsTable>;
						using ProgramsTable = Map<Memory<ProgramHolder>, BuffersTable>;
						using SkyboxesTable = Vector<Memory<SkyboxHolder>>;
					protected:
						struct SceneGraph
						{
							ProgramsTable programsTable;
							SkyboxesTable skyboxesTable;
						};
					protected:
						const Memory<Forward> method;
						const Memory<Scene> scene;
					protected:
						ProgramsLookup programsLookup;
						BuffersLookup buffersLookup;
						SkyboxesLookup skyboxesLookup;
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
						Map<Size, GL::TextureHandle> textures;
					};
					class Forward::Renderer::BuffersHolder
					{
					public:
						GreatVEngine2::OpenGL::VertexArrayHandle vertexArrayHandle;
						GreatVEngine2::OpenGL::BufferHandle verticesBufferHandle;
						GreatVEngine2::OpenGL::BufferHandle indicesBufferHandle;
					};
					class Forward::Renderer::SkyboxHolder
					{
					public:
						GreatVEngine2::OpenGL::TextureHandle textureHandle;
						GreatVEngine2::OpenGL::VertexArrayHandle vertexArrayHandle;
						GreatVEngine2::OpenGL::BufferHandle verticesBufferHandle;
						GreatVEngine2::OpenGL::ProgramHandle programHandle;
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
	auto &programsTable = sceneGraph.programsTable;
	
	programsTable.clear();

	for (auto &objectMemory : objects)
	{
		auto material = objectMemory->GetMaterial();
		auto materialMemory = material.GetValue();
		auto moduleIt = std::find_if(materialMemory->modules.begin(), materialMemory->modules.end(), [](const StrongPointer<Graphics::Material::Module>& module) {
			return DynamicCast<Graphics::APIs::OpenGL::Module>(module) != nullptr;
		});

		if (moduleIt == materialMemory->modules.end())
		{
			throw Exception();
		}

		auto module = DynamicCast<Graphics::APIs::OpenGL::Module>(*moduleIt);

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
					auto loadShader = [](const String& filename)
					{
						std::ifstream t(filename);
						std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

						return Move(str);
					};

					auto vs = GreatVEngine2::OpenGL::CreateShader(GreatVEngine2::OpenGL::ShaderType::Vertex);
					{
						// String source = "#version 330\n uniform mat4 modelViewProjectionMatrix; in vec3 vPos; void main() { gl_Position = modelViewProjectionMatrix * vec4(vPos,1.0f); }";
						auto source = loadShader("Media/Shaders/GLSL/Example_OpenGLGraphics/triangle.glsl.vertex-shader");

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
						// String source = "#version 330\nout vec4 oColor; void main() { oColor = vec4(vec3(gl_FragCoord.z), 1.0f); }";
						auto source = loadShader("Media/Shaders/GLSL/Example_OpenGLGraphics/triangle.glsl.fragment-shader");

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

					GL::UseProgram(program);

					if (auto uniformLocation = GL::GetUniformLocation(program, "textureAlbedo"))
					{
						GL::SetUniform(uniformLocation, 0);
					}
					if (auto uniformLocation = GL::GetUniformLocation(program, "textureNormals"))
					{
						GL::SetUniform(uniformLocation, 1);
					}
					if (auto uniformLocation = GL::GetUniformLocation(program, "textureRoughness"))
					{
						GL::SetUniform(uniformLocation, 2);
					}
					if (auto uniformLocation = GL::GetUniformLocation(program, "textureMetalness"))
					{
						GL::SetUniform(uniformLocation, 3);
					}
					if (auto uniformLocation = GL::GetUniformLocation(program, "textureOcclusion"))
					{
						GL::SetUniform(uniformLocation, 4);
					}
					if (auto uniformLocation = GL::GetUniformLocation(program, "textureEnvironment"))
					{
						GL::SetUniform(uniformLocation, 8);
					}
				}

				auto loadTexture = [](const String& filename_)
				{
					auto texture = GL::GenTexture();
					{
						auto image = OpenIL::Load(filename_);

						if (auto image2D = DynamicCast<Image2D>(image))
						{
							GL::ActiveTexture(0); GL::BindTexture(GL::TextureType::D2, texture);

							GL::TextureParameterWrap(GL::TextureType::D2, GL::TextureWrap::Repeat, GL::TextureWrap::Repeat, GL::TextureWrap::Repeat);
							GL::TextureParameterFilter(GL::TextureType::D2, GL::TextureMinificationFilter::LinearMipmapLinear, GL::TextureMagnificationFilter::Linear);

							for (auto &mipmapIndex : Range(image2D->GetMipmapsCount()))
							{
								auto &mipmap = (*image2D)[mipmapIndex];

								GL::TextureImage(mipmapIndex, GL::GetInternalFormat(image), mipmap.GetSize(), GL::GetFormat(image), GL::GetDataType(image), mipmap.GetData());
							}
						}
						else
						{
							throw Exception();
						}

						GL::glGenerateMipmap(static_cast<GLenum>(GL::TextureType::D2));
					}

					return texture;
				};

				auto textureAlbedo = loadTexture(module->albedoFilename);
				auto textureNormals = loadTexture(module->normalsFilename);
				auto textureRoughness = loadTexture(module->roughnessFilename);
				auto textureMetalness = loadTexture(module->metalnessFilename);
				auto textureOcclusion = loadTexture(module->occlusionFilename);

				programHolderMemory->programHandle = program;
				programHolderMemory->textures[0] = textureAlbedo;
				programHolderMemory->textures[1] = textureNormals;
				programHolderMemory->textures[2] = textureRoughness;
				programHolderMemory->textures[3] = textureMetalness;
				programHolderMemory->textures[4] = textureOcclusion;

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
					auto data = Move(geometry->GetVertices(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F));

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

					const Size positionAttributeOffset				= 0;
					const Size tangentAttributeOffset				= sizeof(Float32) * 3;
					const Size binormalAttributeOffset				= sizeof(Float32) * 3 + (sizeof(Float32) * 3) * 1;
					const Size normalAttributeOffset				= sizeof(Float32) * 3 + (sizeof(Float32) * 3) * 2;
					const Size textureCoordinatesAttributeOffset	= sizeof(Float32) * 3 + (sizeof(Float32) * 3) * 3;

					if (auto attributeLocation = GreatVEngine2::OpenGL::GetAttributeLocation(programHandle, "vPos"))
					{
						GreatVEngine2::OpenGL::VertexAttribPointer(attributeLocation, 3, GreatVEngine2::OpenGL::ComponentType::Float, false, geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F), positionAttributeOffset);
						GreatVEngine2::OpenGL::EnableVertexAttribArray(attributeLocation);
					}
					if (auto attributeLocation = GreatVEngine2::OpenGL::GetAttributeLocation(programHandle, "vTan"))
					{
						GreatVEngine2::OpenGL::VertexAttribPointer(attributeLocation, 3, GreatVEngine2::OpenGL::ComponentType::Float, false, geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F), tangentAttributeOffset);
						GreatVEngine2::OpenGL::EnableVertexAttribArray(attributeLocation);
					}
					if (auto attributeLocation = GreatVEngine2::OpenGL::GetAttributeLocation(programHandle, "vBin"))
					{
						GreatVEngine2::OpenGL::VertexAttribPointer(attributeLocation, 3, GreatVEngine2::OpenGL::ComponentType::Float, false, geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F), binormalAttributeOffset);
						GreatVEngine2::OpenGL::EnableVertexAttribArray(attributeLocation);
					}
					if (auto attributeLocation = GreatVEngine2::OpenGL::GetAttributeLocation(programHandle, "vNor"))
					{
						GreatVEngine2::OpenGL::VertexAttribPointer(attributeLocation, 3, GreatVEngine2::OpenGL::ComponentType::Float, false, geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F), normalAttributeOffset);
						GreatVEngine2::OpenGL::EnableVertexAttribArray(attributeLocation);
					}
					if (auto attributeLocation = GreatVEngine2::OpenGL::GetAttributeLocation(programHandle, "vTex"))
					{
						GreatVEngine2::OpenGL::VertexAttribPointer(attributeLocation, 2, GreatVEngine2::OpenGL::ComponentType::Float, false, geometry->GetVertexSize(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F), textureCoordinatesAttributeOffset);
						GreatVEngine2::OpenGL::EnableVertexAttribArray(attributeLocation);
					}
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

		// sceneGraph.push_back(objectMemory);
	}

	auto &skyboxes = scene->skyboxes;
	auto &skyboxesTable = sceneGraph.skyboxesTable;

	for (auto &skyboxMemory : skyboxes)
	{
		auto skyboxHolderMemory = [&]() -> Memory<SkyboxHolder>
		{
			auto it = skyboxesLookup.find(skyboxMemory);

			if (it == skyboxesLookup.end())
			{
				auto skyboxHolder = MakeStrong<SkyboxHolder>();

				skyboxesLookup.insert({skyboxMemory, skyboxHolder});

				auto skyboxHolderMemory = skyboxHolder.GetValue();
				
				auto programHandle = GreatVEngine2::OpenGL::CreateProgram();
				{
					auto loadShader = [](const String& filename)
					{
						std::ifstream t(filename);
						std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

						return Move(str);
					};

					auto vs = GreatVEngine2::OpenGL::CreateShader(GreatVEngine2::OpenGL::ShaderType::Vertex);
					{
						auto source = loadShader("Media/Shaders/GLSL/Example_OpenGLGraphics/skybox.glsl.vertex-shader");

						GreatVEngine2::OpenGL::ShaderSource(vs, {source});
						GreatVEngine2::OpenGL::CompileShader(vs);

						if (!GreatVEngine2::OpenGL::GetShaderCompileStatus(vs))
						{
							auto log = GreatVEngine2::OpenGL::GetShaderInfoLog(vs);

							throw Exception("Error while compiling shader: " + log);
						}
					}
					auto gs = GreatVEngine2::OpenGL::CreateShader(GreatVEngine2::OpenGL::ShaderType::Geometry);
					{
						auto source = loadShader("Media/Shaders/GLSL/Example_OpenGLGraphics/skybox.glsl.geometry-shader");

						GreatVEngine2::OpenGL::ShaderSource(gs, {source});
						GreatVEngine2::OpenGL::CompileShader(gs);

						if (!GreatVEngine2::OpenGL::GetShaderCompileStatus(gs))
						{
							auto log = GreatVEngine2::OpenGL::GetShaderInfoLog(gs);

							throw Exception("Error while compiling shader: " + log);
						}
					}
					auto fs = GreatVEngine2::OpenGL::CreateShader(GreatVEngine2::OpenGL::ShaderType::Fragment);
					{
						auto source = loadShader("Media/Shaders/GLSL/Example_OpenGLGraphics/skybox.glsl.fragment-shader");

						GreatVEngine2::OpenGL::ShaderSource(fs, {source});
						GreatVEngine2::OpenGL::CompileShader(fs);

						if (!GreatVEngine2::OpenGL::GetShaderCompileStatus(fs))
						{
							auto log = GreatVEngine2::OpenGL::GetShaderInfoLog(fs);

							throw Exception("Error while compiling shader: " + log);
						}
					}

					GreatVEngine2::OpenGL::AttachShader(programHandle, vs);
					GreatVEngine2::OpenGL::AttachShader(programHandle, gs);
					GreatVEngine2::OpenGL::AttachShader(programHandle, fs);

					GreatVEngine2::OpenGL::LinkProgram(programHandle);

					if (!GreatVEngine2::OpenGL::GetProgramLinkStatus(programHandle))
					{
						auto log = GreatVEngine2::OpenGL::GetProgramInfoLog(programHandle);

						throw Exception("Error while linking programHandle: " + log);
					}

					GreatVEngine2::OpenGL::DetachShader(programHandle, vs);
					GreatVEngine2::OpenGL::DetachShader(programHandle, gs);
					GreatVEngine2::OpenGL::DetachShader(programHandle, fs);

					GreatVEngine2::OpenGL::DeleteShader(vs);
					GreatVEngine2::OpenGL::DeleteShader(gs);
					GreatVEngine2::OpenGL::DeleteShader(fs);

					GL::UseProgram(programHandle);

					if (auto uniformLocation = GL::GetUniformLocation(programHandle, "textureEnvironment"))
					{
						GL::SetUniform(uniformLocation, 0);
					}
				}

				skyboxHolderMemory->programHandle = programHandle;

				auto vbo = GreatVEngine2::OpenGL::GenBuffer();
				{
					GreatVEngine2::OpenGL::BindBuffer(GreatVEngine2::OpenGL::BufferType::Array, vbo);
					GreatVEngine2::OpenGL::BufferData(GreatVEngine2::OpenGL::BufferType::Array, 0, nullptr, GreatVEngine2::OpenGL::BufferUsage::Static);
				}
				auto vao = GreatVEngine2::OpenGL::GenVertexArray();
				{
					GreatVEngine2::OpenGL::BindVertexArray(vao);

					GreatVEngine2::OpenGL::UseProgram(programHandle);
					GreatVEngine2::OpenGL::BindBuffer(GreatVEngine2::OpenGL::BufferType::Array, vbo);
				}

				skyboxHolderMemory->vertexArrayHandle = vao;
				skyboxHolderMemory->verticesBufferHandle = vbo;

				auto loadTexture = [](const String& filename_)
				{
					auto texture = GL::GenTexture();
					{
						auto image = OpenIL::Load(filename_);

						if (auto imageCube = DynamicCast<ImageCube>(image))
						{
							GL::ActiveTexture(0); GL::BindTexture(GL::TextureType::Cubemap, texture);
							
							GL::TextureParameterWrap(GL::TextureType::Cubemap, GL::TextureWrap::ClampToEdge, GL::TextureWrap::ClampToEdge, GL::TextureWrap::ClampToEdge);
							GL::TextureParameterFilter(GL::TextureType::Cubemap, GL::TextureMinificationFilter::LinearMipmapLinear, GL::TextureMagnificationFilter::Linear);
							
							for (auto &mipmapIndex : Range(imageCube->GetMipmapsCount()))
							{
								auto &mipmap = (*imageCube)[mipmapIndex];
								auto &data = mipmap.GetData();

								for (auto &faceIndex : Range(mipmap.GetFacesCount()))
								{
									auto faceData = data[faceIndex];
									auto face =
										faceIndex == static_cast<Size>(MipmapCube::Face::NegativeX) ? GL::CubemapFace::NegativeX :
										faceIndex == static_cast<Size>(MipmapCube::Face::PositiveX) ? GL::CubemapFace::PositiveX :
										faceIndex == static_cast<Size>(MipmapCube::Face::NegativeY) ? GL::CubemapFace::NegativeY :
										faceIndex == static_cast<Size>(MipmapCube::Face::PositiveY) ? GL::CubemapFace::PositiveY :
										faceIndex == static_cast<Size>(MipmapCube::Face::NegativeZ) ? GL::CubemapFace::NegativeZ :
										faceIndex == static_cast<Size>(MipmapCube::Face::PositiveZ) ? GL::CubemapFace::PositiveZ :
										throw Exception();

									GL::TextureImage(face, mipmapIndex, GL::GetInternalFormat(image), mipmap.GetSize(), GL::GetFormat(image), GL::GetDataType(image), faceData);
								}
							}
						}
						else
						{
							throw Exception();
						}

						// GL::glGenerateMipmap(static_cast<GLenum>(GL::TextureType::D2));
					}

					return texture;
				};

				auto textureEnvironment = loadTexture("Media/Images/Environment.dds");

				skyboxHolderMemory->textureHandle = textureEnvironment;

				return skyboxHolderMemory;
			}
			else
			{
				auto skyboxHolder = (*it).second;
				auto skyboxHolderMemory = skyboxHolder.GetValue();

				return skyboxHolderMemory;
			}
		}();
		
		skyboxesTable.push_back(skyboxHolderMemory);
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
	
	auto &programsTable = sceneGraph.programsTable;
	auto &skyboxesTable = sceneGraph.skyboxesTable;

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
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// draw skybox
	if (!skyboxesTable.empty())
	{
		auto &skybox = skyboxesTable.front();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		UseProgram(skybox->programHandle);
		BindVertexArray(skybox->vertexArrayHandle);

		auto projectionInverseMatrix = PerspectiveInverse(60.0f, aspect, 0.02f, 10000.0f);

		if (auto uniformLocation = GetUniformLocation(skybox->programHandle, "viewProjectionInverseMatrix"))
		{
			SetUniform(uniformLocation, Mat4(camera_->GetRMat()) * projectionInverseMatrix);
		}

		GL::ActiveTexture(0);
		GL::BindTexture(GL::TextureType::Cubemap, skybox->textureHandle);

		glDrawArrays(GL_POINTS, 0, 1);
	}


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDisable(GL_BLEND);


	float roughness = 0.1f;
	float metalness = 0.0f;

	// draw objects
	for (auto &programIt : programsTable)
	{
		auto &programHolder = programIt.first;
		auto programHandle = programHolder->programHandle;
		auto &buffersTable = programIt.second;

		UseProgram(programHandle);

		for (auto &it : programHolder->textures)
		{
			auto &index = it.first;
			auto &texture = it.second;

			GL::ActiveTexture(index);
			GL::BindTexture(GL::TextureType::D2, texture);
		}

		if (!skyboxesTable.empty())
		{
			auto &skybox = skyboxesTable.front();

			GL::ActiveTexture(8);
			GL::BindTexture(GL::TextureType::Cubemap, skybox->textureHandle);
		}

		for (auto &buffersIt : buffersTable)
		{
			auto &buffersHolder = buffersIt.first;
			auto vertexArrayHandle = buffersHolder->vertexArrayHandle;
			auto verticesBufferHandle = buffersHolder->verticesBufferHandle;
			auto indicesBufferHandle = buffersHolder->indicesBufferHandle;
			auto &objectsTable = buffersIt.second;

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
				auto rotateMatrix = objectMemory->GetRMat();
				auto modelMatrix = objectMemory->GetMMat();
				auto viewMatrix = camera_->GetVMat();
				auto viewProjectionMatrix = Perspective(60.0f, aspect, 0.02f, 10000.0f) * viewMatrix;
				auto mat = viewProjectionMatrix * modelMatrix;

				if (auto uniformLocation = GetUniformLocation(programHandle, "modelViewProjectionMatrix"))
				{
					SetUniform(uniformLocation, mat);
				}
				if (auto uniformLocation = GetUniformLocation(programHandle, "modelMatrix"))
				{
					SetUniform(uniformLocation, Move4(-camera_->GetPosition()) * modelMatrix);
				}
				if (auto uniformLocation = GetUniformLocation(programHandle, "rotateMatrix"))
				{
					SetUniform(uniformLocation, rotateMatrix);
				}
				if (auto uniformLocation = GetUniformLocation(programHandle, "mode"))
				{
					if (GetAsyncKeyState(VK_NUMPAD1)) SetUniform(uniformLocation, 1);
					if (GetAsyncKeyState(VK_NUMPAD2)) SetUniform(uniformLocation, 2);
					if (GetAsyncKeyState(VK_NUMPAD3)) SetUniform(uniformLocation, 3);
					if (GetAsyncKeyState(VK_NUMPAD4)) SetUniform(uniformLocation, 4);
					if (GetAsyncKeyState(VK_NUMPAD5)) SetUniform(uniformLocation, 5);
					if (GetAsyncKeyState(VK_NUMPAD6)) SetUniform(uniformLocation, 6);
					if (GetAsyncKeyState(VK_NUMPAD7)) SetUniform(uniformLocation, 7);
					if (GetAsyncKeyState(VK_NUMPAD8)) SetUniform(uniformLocation, 8);
					if (GetAsyncKeyState(VK_NUMPAD9)) SetUniform(uniformLocation, 9);
					if (GetAsyncKeyState(VK_NUMPAD0)) SetUniform(uniformLocation, 10);
					if (GetAsyncKeyState('T')) SetUniform(uniformLocation, 11);
					if (GetAsyncKeyState('Y')) SetUniform(uniformLocation, 12);
					if (GetAsyncKeyState('U')) SetUniform(uniformLocation, 13);
					if (GetAsyncKeyState('G')) SetUniform(uniformLocation, 14);
					if (GetAsyncKeyState('H')) SetUniform(uniformLocation, 15);
					if (GetAsyncKeyState('J')) SetUniform(uniformLocation, 16);
					if (GetAsyncKeyState('B')) SetUniform(uniformLocation, 17);
					if (GetAsyncKeyState('N')) SetUniform(uniformLocation, 18);
					if (GetAsyncKeyState('M')) SetUniform(uniformLocation, 19);
				}

				if (auto uniformLocation = GetUniformLocation(programHandle, "roughness"))
				{
					SetUniform(uniformLocation, roughness);
				}
				if (auto uniformLocation = GetUniformLocation(programHandle, "metalness"))
				{
					SetUniform(uniformLocation, metalness);
				}

				roughness += 0.1f;

				if (roughness > 1.05f)
				{
					roughness = 0.1f;
					metalness += 0.1f;
				}

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


