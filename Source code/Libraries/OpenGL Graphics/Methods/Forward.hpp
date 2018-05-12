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
					class Forward:
						public Method
					{
					protected:
						class Output; friend Output;
					protected:
						class ContextHolder;
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
						inline ContextHolder():
							win_windowClassName(ObtainWindowClassName()),
							win_windowHandle(ObtainWindowHandle(win_windowClassName)),
							win_deviceContextHandle(ObtainDeviceContextHandle(win_windowHandle)),
							gl_context(MakeStrong<GLContext>(win_deviceContextHandle))
						{
						}
					};
#pragma endregion
#pragma region Forward::SceneCache
					class Forward::SceneCache:
						public This<SceneCache>
					{
						friend Output;
					public:
						using ObjectsTable = Vector<Memory<Object>>;
						using ModelsTable = Map<Memory<ModelCache>, ObjectsTable>;
						using MaterialsTable = Map<Memory<MaterialCache>, ModelsTable>;
					protected:
						const Memory<Forward> methodMemory;
						const Memory<Scene> sceneMemory;
						Scene::Version sceneVersion;
						MaterialsTable materialsTable;
					public:
						inline SceneCache(const StrongPointer<SceneCache>& this_, const Memory<Forward>& methodMemory_, const Memory<Scene>& sceneMemory_);
					protected:
						inline ModelsTable& FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_);
						inline ObjectsTable& FindOrCreate(ModelsTable& modelsTable_, const Memory<ModelCache>& modelCacheMemory_);
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
						inline GL::Program::Handle ObtainProgramHandle()
						{
							const auto &context			= methodMemory->contextHolder->gl_context;
							const auto &programHandle	= context->CreateProgram();

							return programHandle;
						}
					protected:
						const Memory<Forward>							methodMemory;
						const Memory<Material>							materialMemory;
						const Material::EventDestruction::Unsubscriber	unsubscriber;
						const GL::Program::Handle						gl_programHandle;
					public:
						inline MaterialCache(const Memory<Forward>& methodMemory_, const Memory<Material>& materialMemory_):
							methodMemory(methodMemory_),
							materialMemory(materialMemory_),
							unsubscriber(materialMemory->OnDestruction(std::bind(static_cast<void(Forward::*)(const Memory<Material>&)>(&Forward::Remove), methodMemory, materialMemory))),
							gl_programHandle(ObtainProgramHandle())
						{
						}
						inline ~MaterialCache()
						{
							const auto &context = methodMemory->contextHolder->gl_context;

							// TODO: unuse program

							context->DeleteProgram(gl_programHandle);
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
					protected:
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

					Forward::SceneCache::ModelsTable& Forward::SceneCache::FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_)
					{
						const auto it		= materialsTable.find(materialCacheMemory_);

						if (it != materialsTable.end())
						{
							auto &modelsTable = (*it).second;

							return modelsTable;
						}

						const auto &nIt		= materialsTable.insert({ materialCacheMemory_, ModelsTable() }); // TODO: add check?
						auto &modelsTable	= (*nIt.first).second;

						return modelsTable;
					}
					Forward::SceneCache::ObjectsTable& Forward::SceneCache::FindOrCreate(ModelsTable& modelsTable_, const Memory<ModelCache>& modelCacheMemory_)
					{
						const auto it		= modelsTable_.find(modelCacheMemory_);

						if (it != modelsTable_.end())
						{
							auto &objectsTable = (*it).second;

							return objectsTable;
						}

						const auto &nIt		= modelsTable_.insert({ modelCacheMemory_, ObjectsTable() }); // TODO: add check?
						auto &modelsTable	= (*nIt.first).second;

						return modelsTable;
					}

					void Forward::SceneCache::ForceUpdateCaches()
					{
						const auto &contextHolder	= methodMemory->contextHolder;
						const auto &deviceContext	= contextHolder->win_deviceContextHandle;
						const auto &renderContext	= contextHolder->gl_context;

						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

						GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

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
							auto &modelsTable					= FindOrCreate(materialCacheMemory);
							auto &objectsTable					= FindOrCreate(modelsTable, modelCacheMemory);

							objectsTable.push_back(objectMemory);
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

						// TODO
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


