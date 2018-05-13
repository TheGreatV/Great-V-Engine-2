#pragma region Include

#pragma once
#pragma warning (disable : 4503) // names is too long

#include "../Header.hpp"

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
				namespace Methods
				{
					class TaskManager
					{
					public:
						using Task = std::function<void()>;
						using Tasks = Queue<Pair<Task, Threading::Event>>;
					protected:
						using Lock = std::lock_guard<std::mutex>;
					private:
						inline Tasks ObtainTasks()
						{
							Lock lock(mutex);

							return Move(tasks);
						}
						inline void Dispatcher()
						{
							while (!isDone)
							{
								wakeUp.Wait([&](){
									wakeUp.Reset();
								});

								auto tasksToProcess = ObtainTasks();

								while (!tasksToProcess.empty())
								{
									auto taskPair = tasksToProcess.front();
									auto task = taskPair.first;
									auto event = taskPair.second;

									tasksToProcess.pop();

									task();

									event.Set();
								}
							}
						}
					protected:
						bool isDone;
						Threading::Event wakeUp;
						std::thread thread;
						std::mutex mutex;
						Tasks tasks;
					public:
						inline TaskManager():
							isDone(false),
							wakeUp(false),
							thread(std::thread(std::bind(&TaskManager::Dispatcher, this)))
						{
						}
						inline TaskManager(const TaskManager&) = delete;
						inline ~TaskManager()
						{
							isDone = true;

							wakeUp.Set();

							thread.join();
						}
					public:
						inline TaskManager& operator = (const TaskManager&) = delete;
					public:
						inline Threading::Event Submit(const Task& task_)
						{
							Lock lock(mutex);

							Threading::Event doneEvent;

							tasks.push({ task_, doneEvent });

							wakeUp.Set();

							return doneEvent;
						}
					};
					class Forward:
						public Method
					{
					protected:
						class Output; friend Output;
					protected:
						class ContextHolder;
					public:
						struct CameraUniformBuffer
						{
							Vec4 position;
							Mat4 viewProjectionMatrix;
						};
						struct ObjectUniformBuffer
						{
							glm::mat3x4 modelMatrix;
						};
					protected:
						class SceneCache;
						using SceneCaches = Map<Memory<Scene>, StrongPointer<SceneCache>>;
						class MaterialCache;
						using MaterialCaches = Map<Memory<Material>, StrongPointer<MaterialCache>>;
						class ModelCache;
						using ModelCaches = Map<Memory<Model>, StrongPointer<ModelCache>>;
					protected:
						const StrongPointer<ContextHolder> contextHolder = MakeStrong<ContextHolder>();
						MaterialCaches materialCaches;
						ModelCaches modelCaches;
						SceneCaches sceneCaches;
					public:
						Vector<TaskManager> taskManagers = Vector<TaskManager>(std::thread::hardware_concurrency());
					public:
						inline Forward() = delete;
						inline Forward(const StrongPointer<Forward>& this_);
						inline Forward(const Forward&) = delete;
						inline virtual ~Forward();
					public:
						inline Forward& operator = (const Forward&) = delete;
					protected:
						inline Memory<SceneCache> FindOrAdd(const Memory<Scene>& sceneMemory_);
						inline Memory<MaterialCache> FindOrAdd(const Memory<Material>& materialMemory_);
						inline Memory<ModelCache> FindOrAdd(const Memory<Model>& modelMemory_);
						inline void Remove(const Memory<Material>& materialMemory_);
						inline void Remove(const Memory<Model>& modelMemory_);
					public:
						inline virtual StrongPointer<OpenGL::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
					};
#pragma region Forward::Output
					class Forward::Output:
						public OpenGL::Output
					{
					protected:
						const StrongPointer<SceneCache> sceneCache;
						const StrongPointer<Camera> camera;
					public:
						inline Output() = delete;
						inline Output(const StrongPointer<Output>& this_, const StrongPointer<SceneCache>& sceneCache_, const StrongPointer<Camera>& camera_);
						inline Output(const Output&) = delete;
						inline virtual ~Output() = default;
					public:
						inline Output& operator = (const Output&) = delete;
					protected:
						inline virtual void Present(const Memory<APIs::Windows::View>& view_) override;
					};
#pragma endregion
#pragma region Forward::ContextHolder
					class Forward::ContextHolder
					{
					public:
						using GLContext = GL::OSs::Windows::Context_3_3;
					protected:
						inline static String ObtainWindowClassName()
						{
							auto instanceHandle = GetModuleHandleA(NULL);
							
							std::string windowClassName = "window class";
							
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

							return windowClassName;
						}
						inline static HWND ObtainWindowHandle(const String& windowClassName_)
						{
							auto instanceHandle = GetModuleHandleA(NULL);

							HWND windowHandle = CreateWindowA(
								windowClassName_.c_str(),
								"OpenGL 3.3 background window",
								0 & ~WS_VISIBLE,
								0, 0, 0, 0,
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
						inline static HDC ObtainDeviceContextHandle(const HWND& windowHandle_)
						{
							auto deviceContextHandle = GetDC(windowHandle_);

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
					public:
						const String					win_windowClassName;
						const HWND						win_windowHandle;
						const HDC						win_deviceContextHandle;
						const StrongPointer<GLContext>	gl_context;
					public:
						inline GL::Buffer::Handle		ObtainCameraUniformsBuffer() const
						{
							const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
							const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

							GL::OSs::Windows::MakeCurrent(win_deviceContextHandle, gl_context->GetHandle());

							const auto &bufferHandle = gl_context->GenBuffer();

							gl_context->BindBuffer(GL::Buffer::Type::Uniform, bufferHandle);
							gl_context->BufferData(GL::Buffer::Type::Uniform, sizeof(CameraUniformBuffer), nullptr, GL::Buffer::Usage::Dynamic);

							GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);

							return bufferHandle;
						}
					public:
						CameraUniformBuffer				cameraUniformsBufferData;
						const GL::Buffer::Handle		gl_cameraUniformsBuffer;
					public:
						inline ContextHolder():
							win_windowClassName(ObtainWindowClassName()),
							win_windowHandle(ObtainWindowHandle(win_windowClassName)),
							win_deviceContextHandle(ObtainDeviceContextHandle(win_windowHandle)),
							gl_context(MakeStrong<GLContext>(win_deviceContextHandle)),
							gl_cameraUniformsBuffer(ObtainCameraUniformsBuffer())
						{
						}
						inline ~ContextHolder()
						{
							const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
							const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

							GL::OSs::Windows::MakeCurrent(win_deviceContextHandle, gl_context->GetHandle());

							const auto &currentUniformBufferHandle = gl_context->GetBufferBinding(GL::Buffer::Binding::Uniform);
							{
								if (gl_cameraUniformsBuffer == currentUniformBufferHandle)
								{
									gl_context->BindBuffer(GL::Buffer::Type::Uniform, nullptr);
								}
							}

							gl_context->DeleteBuffer(gl_cameraUniformsBuffer);

							GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
						}
					};
#pragma endregion
#pragma region Forward::SceneCache
					class Forward::SceneCache:
						public This<SceneCache>
					{
						friend Output;
					protected:
						class MaterialNode;
						class ModelNode;
					public:
						using ObjectsTable = Vector<Memory<Object>>;
						using ModelsTable = Map<Memory<ModelCache>, ModelNode>;
						using MaterialsTable = Map<Memory<MaterialCache>, MaterialNode>;
					protected:
						const Memory<Forward> methodMemory;
						const Memory<Scene> sceneMemory;
						Scene::Version sceneVersion;
						MaterialsTable materialsTable;
					public:
						inline SceneCache(const StrongPointer<SceneCache>& this_, const Memory<Forward>& methodMemory_, const Memory<Scene>& sceneMemory_);
					protected:
						inline MaterialNode& FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_);
						inline ModelNode& FindOrCreate(MaterialNode& materialNode_, const Memory<ModelCache>& modelCacheMemory_);
					protected:
						inline void ForceUpdateCaches();
						inline void UpdateCaches();
					protected:
						inline void PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_);
					public:
						inline StrongPointer<Output> Render(const StrongPointer<Camera>& camera_);
					};
#pragma endregion
#pragma region Forward::MaterialCache
					class Forward::MaterialCache
					{
					protected:
						inline Size ObtainMaxObjectsCount() const
						{
							const auto &context				= methodMemory->contextHolder->gl_context;
							const auto &bufferHandle		= context->GenBuffer();
							const Size maxUniformBlockSize	= context->GetMaxUniformBlockSize();
							const Size maxObjectsCount		= maxUniformBlockSize / sizeof(ObjectUniformBuffer);

							return glm::min<Size>(1024, maxObjectsCount);
						}
						inline GL::Buffer::Handle ObtainObjectsUniformBuffer() const
						{
							const auto &context			= methodMemory->contextHolder->gl_context;
							const auto &bufferHandle	= context->GenBuffer();

							context->BindBuffer(GL::Buffer::Type::Uniform, bufferHandle);
							context->BufferData(GL::Buffer::Type::Uniform, maxObjectsCount * sizeof(ObjectUniformBuffer), nullptr, GL::Buffer::Usage::Dynamic);

							return bufferHandle;
						}
					protected:
						inline StrongPointer<Module> ObtainModule()
						{
							for (auto &module : materialMemory->modules)
							{
								if (const auto &casted = DynamicCast<Module>(module))
								{
									return casted;
								}
							}

							throw Exception();
						}
						inline GL::Program::Handle ObtainProgramHandle()
						{
							const auto loadShader = [](const String& filename) // TODO: replace with something
							{
								std::ifstream file(filename);
								std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

								return Move(code);
							};

							const auto &context			= methodMemory->contextHolder->gl_context;
							const auto &programHandle	= context->CreateProgram();
							const auto &module			= ObtainModule();

							const auto &vertexShaderHandle		= context->CreateShader(GL::Shader::Type::Vertex);
							{
								const auto &source = loadShader(module->vertexShaderFilename);

								context->ShaderSource(vertexShaderHandle, source);
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
								const auto &source = loadShader(module->fragmentShaderFilename);

								context->ShaderSource(fragmentShaderHandle, { source });
								context->CompileShader(fragmentShaderHandle);

								const auto &compileStatus = context->GetShaderCompileStatus(fragmentShaderHandle);

								if (!compileStatus)
								{
									const auto &log = context->GetShaderInfoLog(fragmentShaderHandle);

									throw Exception("Error while compiling shader: " + log);
								}
							}

							context->AttachShader(programHandle, vertexShaderHandle);
							context->AttachShader(programHandle, fragmentShaderHandle);

							context->LinkProgram(programHandle);

							const auto &linkStatus = context->GetProgramLinkStatus(programHandle);

							if (!linkStatus)
							{
								const auto &log = context->GetProgramInfoLog(programHandle);

								throw Exception("Error while linking program: " + log);
							}

							context->DeleteShader(vertexShaderHandle);
							context->DeleteShader(fragmentShaderHandle);

							context->UseProgram(programHandle);

							/*if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureAlbedo"))
							{
								GL::SetUniform(uniformLocation, 0);
							}
							if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureNormals"))
							{
								GL::SetUniform(uniformLocation, 1);
							}
							if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureRoughness"))
							{
								GL::SetUniform(uniformLocation, 2);
							}
							if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureMetalness"))
							{
								GL::SetUniform(uniformLocation, 3);
							}
							if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureOcclusion"))
							{
								GL::SetUniform(uniformLocation, 4);
							}
							if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureEnvironment"))
							{
								GL::SetUniform(uniformLocation, 8);
							}*/

							return programHandle;
						}
					protected:
						const Memory<Forward>							methodMemory;
						const Memory<Material>							materialMemory;
						const Material::EventDestruction::Unsubscriber	unsubscriber;
					public:
						const GL::Program::Handle						gl_programHandle;
						const Size										maxObjectsCount;
						const GL::Buffer::Handle						gl_objectsUniformBufferHandle;
					public:
						inline MaterialCache(const Memory<Forward>& methodMemory_, const Memory<Material>& materialMemory_):
							methodMemory(methodMemory_),
							materialMemory(materialMemory_),
							unsubscriber(materialMemory->OnDestruction(std::bind(static_cast<void(Forward::*)(const Memory<Material>&)>(&Forward::Remove), methodMemory, materialMemory))),
							gl_programHandle(ObtainProgramHandle()),
							maxObjectsCount(ObtainMaxObjectsCount()),
							gl_objectsUniformBufferHandle(ObtainObjectsUniformBuffer())
						{
						}
						inline ~MaterialCache()
						{
							const auto &context = methodMemory->contextHolder->gl_context;
							const auto &currentProgramHandle = context->GetCurrentProgram();

							if (currentProgramHandle == gl_programHandle)
							{
								context->UseProgram(0);
							}

							context->DeleteProgram(gl_programHandle);

							const auto &currentUniformBufferHandle = context->GetBufferBinding(GL::Buffer::Binding::Uniform);
							{
								if (gl_objectsUniformBufferHandle == currentUniformBufferHandle)
								{
									context->BindBuffer(GL::Buffer::Type::Uniform, nullptr);
								}
							}

							context->DeleteBuffer(gl_objectsUniformBufferHandle);
						}
					};
#pragma endregion
#pragma region Forward::ModelCache
					class Forward::ModelCache
					{
					protected:
						inline GL::Buffer::Handle ObtainVerticesBufferHandle()
						{
							const auto &context			= methodMemory->contextHolder->gl_context;
							const auto &bufferHandle	= context->GenBuffer();

							context->BindBuffer(GL::Buffer::Type::Array, bufferHandle);
							
							const auto &geometry	= modelMemory->GetGeometry();
							const auto &data		= geometry->GetVertices(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F);
							
							context->BufferData(GL::Buffer::Type::Array, data, GL::Buffer::Usage::Static);

							return bufferHandle;
						}
						inline GL::Buffer::Handle ObtainIndicesBufferHandle()
						{
							const auto &context			= methodMemory->contextHolder->gl_context;
							const auto &bufferHandle	= context->GenBuffer();

							context->BindBuffer(GL::Buffer::Type::ElementArray, bufferHandle);
							
							const auto &geometry	= modelMemory->GetGeometry();
							const auto &data		= geometry->GetIndices(Geometry::IndexPackMode::UInt32);
							
							context->BufferData(GL::Buffer::Type::ElementArray, data, GL::Buffer::Usage::Static);

							return bufferHandle;
						}
					public:
						const Memory<Forward>						methodMemory;
						const Memory<Model>							modelMemory;
						const Model::EventDestruction::Unsubscriber	unsubscriber;
						const GL::Buffer::Handle					gl_verticesBufferHandle;
						const GL::Buffer::Handle					gl_indicesBufferHandle;
					public:
						inline ModelCache(const Memory<Forward>& methodMemory_, const Memory<Model> modelMemory_):
							methodMemory(methodMemory_),
							modelMemory(modelMemory_),
							unsubscriber(modelMemory->OnDestruction(std::bind(static_cast<void(Forward::*)(const Memory<Model>&)>(&Forward::Remove), methodMemory, modelMemory))),
							gl_verticesBufferHandle(ObtainVerticesBufferHandle()),
							gl_indicesBufferHandle(ObtainIndicesBufferHandle())
						{
						}
						inline ~ModelCache()
						{
							const auto &context = methodMemory->contextHolder->gl_context;

							const auto &currentArrayBufferHandle = context->GetBufferBinding(GL::Buffer::Binding::Array);
							{
								if (gl_verticesBufferHandle == currentArrayBufferHandle)
								{
									context->BindBuffer(GL::Buffer::Type::Array, nullptr);
								}
							}

							context->DeleteBuffer(gl_verticesBufferHandle);

							const auto &currentElementArrayBufferHandle = context->GetBufferBinding(GL::Buffer::Binding::ElementArray);
							{
								if (gl_indicesBufferHandle == currentElementArrayBufferHandle)
								{
									context->BindBuffer(GL::Buffer::Type::ElementArray, nullptr);
								}
							}

							context->DeleteBuffer(gl_indicesBufferHandle);
						}
					};
#pragma endregion
#pragma region Forward::SceneCache::MaterialNode
					class Forward::SceneCache::MaterialNode
					{
					public:
						const Memory<SceneCache> sceneCacheMemory;
						const Memory<MaterialCache> materialCacheMemory;
						ModelsTable modelsTable;
					public:
						inline MaterialNode(const Memory<SceneCache>& sceneCacheMemory_, const Memory<MaterialCache>& materialCacheMemory_):
							sceneCacheMemory(sceneCacheMemory_),
							materialCacheMemory(materialCacheMemory_)
						{
						}
						inline MaterialNode(const MaterialNode&) = delete;
						inline ~MaterialNode()
						{
						}
					};
#pragma endregion
#pragma region Forward::SceneCache::ModelNode
					class Forward::SceneCache::ModelNode
					{
					public:
						inline GL::VertexArray::Handle ObtainVertexArraysHandle() const
						{
							const auto &context = materialNodeMemory->sceneCacheMemory->methodMemory->contextHolder->gl_context;
							const auto &vertexArrayHandle = context->GenVertexArray();
							const auto vertexSize = modelCacheMemory->modelMemory->GetGeometry()->GetVertexSize(Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F);

							context->BindVertexArray(vertexArrayHandle);

							context->BindBuffer(GL::Buffer::Type::Array, modelCacheMemory->gl_verticesBufferHandle);
							
							if (const auto attributeLocation = context->GetAttributeLocation(materialNodeMemory->materialCacheMemory->gl_programHandle, "vPos"))
							{
								context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Float32)* 0);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto attributeLocation = context->GetAttributeLocation(materialNodeMemory->materialCacheMemory->gl_programHandle, "vTan"))
							{
								context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Float32)* 3);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto attributeLocation = context->GetAttributeLocation(materialNodeMemory->materialCacheMemory->gl_programHandle, "vBin"))
							{
								context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Float32)* 6);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto attributeLocation = context->GetAttributeLocation(materialNodeMemory->materialCacheMemory->gl_programHandle, "vNor"))
							{
								context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Float32)* 9);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto attributeLocation = context->GetAttributeLocation(materialNodeMemory->materialCacheMemory->gl_programHandle, "vTex"))
							{
								context->VertexAttributePointer(attributeLocation, 2, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Float32)* 12);
								context->EnableVertexAttributeArray(attributeLocation);
							}

							context->BindVertexArray(nullptr);

							return vertexArrayHandle;
						}
					public:
						const Memory<MaterialNode> materialNodeMemory;
						const Memory<ModelCache> modelCacheMemory;
						ObjectsTable objectsTable;
						Vector<ObjectUniformBuffer> objectsUniformBufferData;
						const GL::VertexArray::Handle gl_vertexArrayHandle;
						Vector<Threading::Event> events;
					public:
						inline ModelNode(const Memory<MaterialNode>& materialNodeMemory_, const Memory<ModelCache>& modelCacheMemory_):
							materialNodeMemory(materialNodeMemory_),
							modelCacheMemory(modelCacheMemory_),
							gl_vertexArrayHandle(ObtainVertexArraysHandle())
						{
						}
						inline ModelNode(const ModelNode&) = delete;
						inline ~ModelNode()
						{
							const auto &context = materialNodeMemory->sceneCacheMemory->methodMemory->contextHolder->gl_context;

							// TODO: check

							context->BindVertexArray(nullptr);
							context->DeleteVertexArray(gl_vertexArrayHandle);
						}
					};
#pragma endregion

#pragma region Forward
					Forward::Forward(const StrongPointer<Forward>& this_):
						Method(this_)
					{
					}
					Forward::~Forward()
					{
						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

						GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

						sceneCaches.clear();
						modelCaches.clear();
						materialCaches.clear();

						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
					}

					Memory<Forward::SceneCache> Forward::FindOrAdd(const Memory<Scene>& sceneMemory_)
					{
						const auto it				= sceneCaches.find(sceneMemory_);

						if (it != sceneCaches.end())
						{
							const auto sceneCache		= (*it).second;
							const auto sceneCacheMemory	= sceneCache.GetValue();

							return sceneCacheMemory;
						}

						const auto sceneCache		= Make<SceneCache>(this, sceneMemory_);

						sceneCaches.insert({ sceneMemory_, sceneCache }); // TODO: add check?
						
						const auto sceneCacheMemory	= sceneCache.GetValue();

						return sceneCacheMemory;
					}
					Memory<Forward::MaterialCache> Forward::FindOrAdd(const Memory<Material>& materialMemory_)
					{
						const auto it					= materialCaches.find(materialMemory_);

						if (it != materialCaches.end())
						{
							const auto materialCache		= (*it).second;
							const auto materialCacheMemory	= materialCache.GetValue();

							return materialCacheMemory;
						}

						const auto materialCache		= MakeStrong<MaterialCache>(this, materialMemory_);

						materialCaches.insert({ materialMemory_, materialCache }); // TODO: add check?
						
						const auto materialCacheMemory	= materialCache.GetValue();

						return materialCacheMemory;
					}
					Memory<Forward::ModelCache> Forward::FindOrAdd(const Memory<Model>& modelMemory_)
					{
						const auto it				= modelCaches.find(modelMemory_);

						if (it != modelCaches.end())
						{
							const auto modelCache		= (*it).second;
							const auto modelCacheMemory	= modelCache.GetValue();

							return modelCacheMemory;
						}

						const auto modelCache		= MakeStrong<ModelCache>(this, modelMemory_);

						modelCaches.insert({ modelMemory_, modelCache }); // TODO: add check?
						
						const auto modelCacheMemory	= modelCache.GetValue();

						return modelCacheMemory;
					}
					void Forward::Remove(const Memory<Material>& materialMemory_)
					{
						const auto &it = materialCaches.find(materialMemory_);

						if (it == materialCaches.end())
						{
							throw Exception();
						}

						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();
						
						GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

						materialCaches.erase(it);

						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
					}
					void Forward::Remove(const Memory<Model>& modelMemory_)
					{
						const auto &it = modelCaches.find(modelMemory_);

						if (it == modelCaches.end())
						{
							throw Exception();
						}

						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

						GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

						modelCaches.erase(it);

						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
					}

					StrongPointer<OpenGL::Output> Forward::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
					{
						const auto &sceneMemory	= scene_.GetValue();
						const auto &sceneCache	= FindOrAdd(sceneMemory);

						return sceneCache->Render(camera_);
					}
#pragma endregion
#pragma region Forward::Output
					Forward::Output::Output(const StrongPointer<Output>& this_, const StrongPointer<SceneCache>& sceneCache_, const StrongPointer<Camera>& camera_):
						OpenGL::Output(this_),
						sceneCache(sceneCache_),
						camera(camera_)
					{
					}

					void Forward::Output::Present(const Memory<APIs::Windows::View>& view_)
					{
						sceneCache->PresentOn(view_, camera);
					}
#pragma endregion
#pragma region Forward::SceneCache
					Forward::SceneCache::SceneCache(const StrongPointer<SceneCache>& this_, const Memory<Forward>& methodMemory_, const Memory<Scene>& sceneMemory_):
						This(this_),
						methodMemory(methodMemory_),
						sceneMemory(sceneMemory_),
						sceneVersion(sceneMemory->GetVersion())
					{
						ForceUpdateCaches();
					}

					Forward::SceneCache::MaterialNode& Forward::SceneCache::FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_)
					{
						const auto it		= materialsTable.find(materialCacheMemory_);

						if (it != materialsTable.end())
						{
							auto &materialNode = (*it).second;

							return materialNode;
						}

						const auto &nIt		= materialsTable.emplace(
							std::piecewise_construct,
							std::forward_as_tuple(materialCacheMemory_),
							std::forward_as_tuple(this, materialCacheMemory_)
						); // TODO: add check?
						auto &materialNode	= (*nIt.first).second;

						return materialNode;
					}
					Forward::SceneCache::ModelNode& Forward::SceneCache::FindOrCreate(MaterialNode& materialNode_, const Memory<ModelCache>& modelCacheMemory_)
					{
						auto		&modelsTable	= materialNode_.modelsTable;
						const auto	&it				= modelsTable.find(modelCacheMemory_);

						if (it != modelsTable.end())
						{
							auto &modelNode = (*it).second;

							return modelNode;
						}

						const auto &nIt		= modelsTable.emplace(
							std::piecewise_construct,
							std::forward_as_tuple(modelCacheMemory_),
							std::forward_as_tuple(&materialNode_, modelCacheMemory_)
						); // TODO: add check?
						auto &modelNode		= (*nIt.first).second;

						return modelNode;
					}

					void Forward::SceneCache::ForceUpdateCaches()
					{
						const auto &contextHolder	= methodMemory->contextHolder;
						const auto &deviceContext	= contextHolder->win_deviceContextHandle;
						const auto &renderContext	= contextHolder->gl_context->GetHandle();
						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

						GL::OSs::Windows::MakeCurrent(deviceContext, renderContext);

						auto &objects = sceneMemory->objects;

						materialsTable.clear();

						for (auto &objectMemory : objects)
						{
							// obtain material cache
							const auto &material				= objectMemory->GetMaterial();
							const auto &materialMemory			= material.GetValue();
							const auto &materialCacheMemory		= methodMemory->FindOrAdd(materialMemory);

							// obtain model cache
							const auto &model					= objectMemory->GetModel();
							const auto &modelMemory				= model.GetValue();
							const auto &modelCacheMemory		= methodMemory->FindOrAdd(modelMemory);

							// obtain tables
							auto &materialNode					= FindOrCreate(materialCacheMemory);
							auto &modelsTable					= materialNode.modelsTable;
							auto &modelNode						= FindOrCreate(materialNode, modelCacheMemory);
							auto &objectsTable					= modelNode.objectsTable;

							objectsTable.push_back(objectMemory);
						}

						for (auto &materialIt : materialsTable)
						{
							auto &materialNode	= materialIt.second;
							auto &modelsTable	= materialNode.modelsTable;

							for (auto &modelIt : modelsTable)
							{
								auto &modelNode		= modelIt.second;
								auto objectsTable	= modelNode.objectsTable;

								modelNode.objectsUniformBufferData.resize(objectsTable.size());
							}
						}

						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
					}
					void Forward::SceneCache::UpdateCaches()
					{
						auto currentSceneVersion = sceneMemory->GetVersion();

						if (sceneVersion != currentSceneVersion)
						{
							ForceUpdateCaches();

							sceneVersion = currentSceneVersion;
						}
					}

					void Forward::SceneCache::PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_)
					{
						UpdateCaches();

						const auto &contextHolder	= methodMemory->contextHolder;
						const auto &deviceContext	= view_->GetDeviceContextHandle();
						const auto &renderContext	= contextHolder->gl_context;
						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

						GL::OSs::Windows::MakeCurrent(deviceContext, renderContext->GetHandle());
						
						auto viewport = view_->GetViewportRange();
						auto aspect = viewport.GetAspect();

						glViewport(viewport.GetPosition().x, viewport.GetPosition().y, viewport.GetSize().x, viewport.GetSize().y);
						glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
						glClearDepth(1.0f);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

						glEnable(GL_CULL_FACE);
						glCullFace(GL_BACK);
						glFrontFace(GL_CCW);

						glEnable(GL_DEPTH_TEST);
						glDepthFunc(GL_LESS);

						glDisable(GL_BLEND);

						// TODO: camera buffer
						contextHolder->cameraUniformsBufferData;
						{
							auto viewProjectionMatrix =
								Perspective(60.0f, aspect, 0.1f, 10000.0f) *
								camera_->GetVMat();

							contextHolder->cameraUniformsBufferData.position				= Vec4(camera_->GetPosition(), 0.0f);
							contextHolder->cameraUniformsBufferData.viewProjectionMatrix	= viewProjectionMatrix;

							renderContext->BindBuffer(GL::Buffer::Type::Uniform, contextHolder->gl_cameraUniformsBuffer);
							renderContext->BufferSubData(GL::Buffer::Type::Uniform, 0, sizeof(CameraUniformBuffer), &contextHolder->cameraUniformsBufferData);
						}

						auto &taskManagers = methodMemory->taskManagers;

						for (auto &materialIt : materialsTable)
						{
							auto		&materialNode			= materialIt.second;
							auto		&modelsTable			= materialNode.modelsTable;

							for (auto &modelIt : modelsTable)
							{
								auto		&modelNode				= modelIt.second;
								auto		&objectsTable			= modelNode.objectsTable;
								auto		&objectsData			= modelNode.objectsUniformBufferData;
								auto		&events					= modelNode.events;

								events.resize(taskManagers.size());

								const Size	objectsPerTask			= objectsTable.size() / taskManagers.size();

								for (auto &taskIndex : Range(taskManagers.size()))
								{
									auto		&taskManager	= taskManagers[taskIndex];
									const Size	firstIndex		= taskIndex * objectsPerTask;
									const Size	lastIndex		= taskIndex < static_cast<int>(taskManagers.size() - 1)
										? (taskIndex + 1) * objectsPerTask
										: objectsTable.size();

									events[taskIndex] = taskManager.Submit(std::bind([](Object** objectsTable_, ObjectUniformBuffer* objectsData_, const Size firtsIndex_, const Size lastIndex_){
										for (Size objectIndex = firtsIndex_; objectIndex < lastIndex_; ++objectIndex)
										{
											const auto &objectMemory	= objectsTable_[objectIndex];
											const auto &modelMatrix		= objectMemory->GetMMat();
											auto &objectData			= objectsData_[objectIndex];

											objectData.modelMatrix = Transpose(glm::mat4x3(modelMatrix));
										}
									}, objectsTable.data(), objectsData.data(), firstIndex, lastIndex));
								}
							}
						}

						for (auto &materialIt : materialsTable)
						{
							const auto	&materialCacheMemory	= materialIt.first;
							auto		&materialNode			= materialIt.second;
							auto		&modelsTable			= materialNode.modelsTable;
							const auto	&programHandle			= materialCacheMemory->gl_programHandle;

							renderContext->UseProgram(programHandle);

							if (auto index = renderContext->GetUniformBlockIndex(programHandle, "CameraBuffer"))
							{
								renderContext->UniformBlockBinding(programHandle, index, GL::UniformBlock::Binding(0));
								renderContext->BindBufferBase(GL::Buffer::Type::Uniform, GL::UniformBlock::Binding(0), contextHolder->gl_cameraUniformsBuffer);
							}
							if (auto index = renderContext->GetUniformBlockIndex(programHandle, "ObjectsBuffer"))
							{
								renderContext->UniformBlockBinding(programHandle, index, GL::UniformBlock::Binding(1));
								renderContext->BindBufferBase(GL::Buffer::Type::Uniform, GL::UniformBlock::Binding(1), materialCacheMemory->gl_objectsUniformBufferHandle);
							}

							renderContext->BindBuffer(GL::Buffer::Type::Uniform, materialCacheMemory->gl_objectsUniformBufferHandle);

							for (auto &modelIt : modelsTable)
							{
								const auto	&modelCache				= modelIt.first;
								const auto	&geometryMemory			= modelCache->modelMemory->GetGeometry().GetValue();
								const auto	&verticesBufferHandle	= modelCache->gl_verticesBufferHandle;
								const auto	&indicesBufferHandle	= modelCache->gl_indicesBufferHandle;

								auto		&modelNode				= modelIt.second;
								const auto	&vertexArrayHandle		= modelNode.gl_vertexArrayHandle;

								auto		&objectsTable			= modelNode.objectsTable;
								auto		&objectsData			= modelNode.objectsUniformBufferData;
								auto		&events					= modelNode.events;

								renderContext->BindVertexArray(vertexArrayHandle);
								renderContext->BindBuffer(GL::Buffer::Type::Array, verticesBufferHandle);
								renderContext->BindBuffer(GL::Buffer::Type::ElementArray, indicesBufferHandle);

								/*for (auto &objectIndex : Range(objectsTable.size()))
								{
									const auto &objectMemory	= objectsTable[objectIndex];
									const auto &modelMatrix		= objectMemory->GetMMat();
									auto &objectData			= objectsData[objectIndex];

									objectData.modelMatrix = Transpose(glm::mat4x3(modelMatrix));
								}*/

								for (auto &event : events)
								{
									event.Wait();
								}

								const Size maxObjectsCountPerDrawCall	= materialCacheMemory->maxObjectsCount;
								const Size drawCallsCount				= (objectsTable.size() + maxObjectsCountPerDrawCall - 1) / maxObjectsCountPerDrawCall;

								for (const auto &drawCallIndex : Range(drawCallsCount))
								{
									const Size firstIndex		= drawCallIndex * maxObjectsCountPerDrawCall;
									const Size lastIndex		= glm::min((drawCallIndex + 1) * maxObjectsCountPerDrawCall, objectsData.size());
									const Size instancesCount	= lastIndex - firstIndex;

									renderContext->BufferSubData(GL::Buffer::Type::Uniform, 0, sizeof(ObjectUniformBuffer) * instancesCount, objectsData.data() + firstIndex);

									if (geometryMemory->GetTopology() == Geometry::Topology::Triangles)
									{
										renderContext->DrawElementsInstanced(GL::PrimitiveType::Triangles, geometryMemory->GetIndicesCount(), instancesCount);
									}
									else
									{
										throw Exception();
									}
								}
							}
						}

						SwapBuffers(deviceContext);
						
						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
					}

					StrongPointer<Forward::Output> Forward::SceneCache::Render(const StrongPointer<Camera>& camera_)
					{
						return Make<Output>(GetThis<SceneCache>(), camera_);
					}
#pragma endregion
				}
			}
		}
	}
}


#pragma region
#pragma endregion


