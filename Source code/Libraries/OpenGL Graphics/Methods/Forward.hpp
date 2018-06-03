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
						class GeometryBufferHolder;
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
						class AttributesCache;
						using AttributesCaches = Map<Memory<ModelCache>, StrongPointer<AttributesCache>>;
					protected:
						const StrongPointer<ContextHolder> contextHolder = MakeStrong<ContextHolder>();
						const StrongPointer<GeometryBufferHolder> geometryBufferHolder = MakeStrong<GeometryBufferHolder>(contextHolder);
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
						// inline void Remove(const Memory<Model>& modelMemory_);
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
						using GLContext = WGL::Context_3_3;
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
							WGL::Lock contextLock(gl_context, win_deviceContextHandle);

							const auto &bufferHandle = gl_context->GenBuffer();

							gl_context->BindBuffer(GL::Buffer::Type::Uniform, bufferHandle);
							gl_context->BufferData(GL::Buffer::Type::Uniform, sizeof(CameraUniformBuffer), nullptr, GL::Buffer::Usage::Dynamic);

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
							WGL::Lock contextLock(gl_context, win_deviceContextHandle);

							const auto &currentUniformBufferHandle = gl_context->GetBufferBinding(GL::Buffer::Binding::Uniform);
							{
								if (gl_cameraUniformsBuffer == currentUniformBufferHandle)
								{
									gl_context->BindBuffer(GL::Buffer::Type::Uniform, nullptr);
								}
							}

							gl_context->DeleteBuffer(gl_cameraUniformsBuffer);
						}
					};
#pragma endregion
#pragma region Forward::GeometryBufferHolder
					class Forward::GeometryBufferHolder
					{
					public:
						class Buffer
						{
						public:
							inline GL::Buffer::Handle ObtainBufferHandle() const
							{
								const auto &context		= contextHolder->gl_context;
								const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

								auto buffer = context->GenBuffer();
						
								context->BindBuffer(gl_bufferType, buffer);
								context->BufferData(gl_bufferType, capacity, nullptr, GL::Buffer::Usage::Static);
								context->BindBuffer(gl_bufferType, nullptr);

								return buffer;
							}
						public:
							const Memory<ContextHolder>		contextHolder;
							const GL::Buffer::Type			gl_bufferType;
							Size							size = 0;
							Size							capacity;
							const GL::Buffer::Handle		gl_bufferHandle;
						public:
							inline Buffer(const Memory<ContextHolder>& contextHolder_, const GL::Buffer::Type& bufferType_, const Size& capacity_):
								contextHolder(contextHolder_),
								capacity(capacity_),
								gl_bufferType(bufferType_),
								gl_bufferHandle(ObtainBufferHandle())
							{
							}
							inline ~Buffer()
							{
								const auto &context		= contextHolder->gl_context;
								const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

								context->UnbindBuffer(gl_bufferType, gl_bufferHandle);
								context->DeleteBuffer(gl_bufferHandle);
							}
						public:
							inline void Insert(const Size& offset_, const Vector<UInt8>& data_)
							{
								const auto &sizeAfterInsertion	= size + data_.size();

								// lock render context
								const auto &context		= contextHolder->gl_context;
								const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

								// copy currently allocated data to temporal buffer, resize buffer, copy data back
								if (sizeAfterInsertion > capacity)
								{
									// prepare temporal buffer
									auto temporalBufferHandle = context->GenBuffer();
									{
										context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
										context->BufferData(GL::Buffer::Type::CopyWrite, size, nullptr, GL::Buffer::Usage::Stream);
									}

									// store backup in temporal buffer
									context->BindBuffer(GL::Buffer::Type::CopyRead, gl_bufferHandle);
									context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, size);

									// resize buffer
									auto powerOfTwoSize = static_cast<Size>(glm::pow(2, glm::ceil(glm::log(static_cast<Float64>(sizeAfterInsertion)) / glm::log(2.0))));
									auto newBufferSize = glm::max<Size>(powerOfTwoSize * 2, 128 * 1024);

									context->BufferData(GL::Buffer::Type::CopyRead, newBufferSize, nullptr, GL::Buffer::Usage::Static);
									
									// restore data from backup in temporal buffer
									context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, size);

									capacity = newBufferSize;

									context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
									context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

									context->DeleteBuffer(temporalBufferHandle);
								}

								const auto &tailSize	= size - offset_; // number of bytes to move right
							
								if (tailSize > 0)
								{
									// prepare temporal buffer
									auto temporalBufferHandle = context->GenBuffer();
									{
										context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
										context->BufferData(GL::Buffer::Type::CopyWrite, tailSize, nullptr, GL::Buffer::Usage::Stream);
									}

									// store backup in temporal buffer
									context->BindBuffer(GL::Buffer::Type::CopyRead, gl_bufferHandle);
									context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, offset_, 0, tailSize);

									// restore data from backup in temporal buffer
									context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, offset_ + data_.size(), tailSize);

									context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
									context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

									context->DeleteBuffer(temporalBufferHandle);
								}

								// insert data
								context->BindBuffer(GL::Buffer::Type::Array, gl_bufferHandle);
								context->BufferSubData(GL::Buffer::Type::Array, offset_, data_.size(), data_.data());
								context->BindBuffer(GL::Buffer::Type::Array, nullptr);

								size += data_.size();
							}
							inline void Remove(const Size& offset_, const Size& size_)
							{
								// lock render context
								const auto &context		= contextHolder->gl_context;
								const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

								const auto &tailOffset				= offset_ + size_;
								const auto &tailSize				= size - tailOffset;

								if (tailSize > 0)
								{
									// prepare temporal buffer
									auto temporalBufferHandle = context->GenBuffer();
									{
										context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
										context->BufferData(GL::Buffer::Type::CopyWrite, tailSize, nullptr, GL::Buffer::Usage::Stream);
									}

									// store backup in temporal buffer
									context->BindBuffer(GL::Buffer::Type::CopyRead, gl_bufferHandle);
									context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, tailOffset, 0, tailSize);

									// restore data from backup in temporal buffer
									context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, offset_, tailSize);

									context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
									context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

									context->DeleteBuffer(temporalBufferHandle);
								}

								/*const auto &totalBufferSizeAfterRemoving	= size - size_;
								const auto &sizeLimit						= glm::max<Size>(verticesBufferCapacity / 8, 128 * 1024);

								// resize buffer if needed
								if (totalBufferSizeAfterRemoving < sizeLimit)
								{
									// prepare temporal buffer
									auto temporalBufferHandle = context->GenBuffer();
									{
										context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
										context->BufferData(GL::Buffer::Type::CopyWrite, totalBufferSizeAfterRemoving, nullptr, GL::Buffer::Usage::Stream);
									}

									// store backup in temporal buffer
									context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
									context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, totalBufferSizeAfterRemoving);

									// resize buffer
									context->BufferData(GL::Buffer::Type::CopyRead, sizeLimit, nullptr, GL::Buffer::Usage::Static);
									
									// restore data from backup in temporal buffer
									context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, totalBufferSizeAfterRemoving);

									verticesBufferCapacity = sizeLimit;

									context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
									context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

									context->DeleteBuffer(temporalBufferHandle);
								}*/
							}
						};
					public:
						class VerticesRange;
						class VerticesHolder
						{
						public:
							const Memory<VerticesRange> verticesRangeMemory;
							const Memory<Geometry> geometryMemory;
							const Geometry::EventDestruction::Unsubscriber unsubscriber;
							Size firstVertex;
						public:
							inline VerticesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry>& geometryMemory_, const Size& firstVertex_);
						};
						class VerticesRange
						{
						public:
							const Geometry::VertexPackMode packMode;
							const Size vertexSize;
							Buffer gl_verticesBuffer;
							Vector<StrongPointer<VerticesHolder>> verticesHolders;
						public:
							inline VerticesRange(const Memory<ContextHolder>& contextHolder_, const Geometry::VertexPackMode& packMode_):
								packMode(packMode_),
								gl_verticesBuffer(contextHolder_, GL::Buffer::Type::Array, 128 * 1024),
								vertexSize(Geometry::GetVertexSize(packMode))
							{
							}
						public:
							inline Size GetTotalVerticesCount() const
							{
								Size count = 0;

								for (auto &verticesHolder : verticesHolders)
								{
									count += verticesHolder->geometryMemory->GetVerticesCount();
								}

								return count;
							}
						};
						class IndicesRange;
						class IndicesHolder
						{
						public:
							const Memory<IndicesRange> indicesRangeMemory;
							const Memory<Geometry> geometryMemory;
							const Geometry::EventDestruction::Unsubscriber unsubscriber;
							Size firstIndex;
						public:
							inline IndicesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry>& geometryMemory_, const Size& firstIndex_);
						};
						class IndicesRange
						{
						public:
							const Geometry::IndexPackMode packMode;
							const Size indexSize;
							Size offset = 0; // in bytes
							Size size = 0;
							Vector<StrongPointer<IndicesHolder>> indicesHolders;
							StrongPointer<IndicesRange> next = StrongPointer<IndicesRange>(nullptr);
						public:
							inline IndicesRange(const Geometry::IndexPackMode& packMode_, const StrongPointer<IndicesRange>& next_):
								packMode(packMode_),
								indexSize(Geometry::GetIndexSize(packMode)),
								next(next_)
							{
							}
						public:
							inline Size GetTotalIndicesCount() const
							{
								Size count = 0;

								for (auto &indicesHolder : indicesHolders)
								{
									count += indicesHolder->geometryMemory->GetIndicesCount();
								}

								return count;
							}
						};
					protected:
						inline GL::VertexArray::Handle ObtainVerticesArrayHandle() const
						{
							const auto &context				= contextHolder->gl_context;
							const auto &contextLock			= WGL::Lock(context, contextHolder->win_deviceContextHandle);
							const auto &verticesArrayHandle	= context->GenVertexArray();

							context->BindVertexArray(verticesArrayHandle);

							return verticesArrayHandle;
						}
						inline GL::Buffer::Handle ObtainObjectsDataBuffer() const
						{
							const auto &context			= contextHolder->gl_context;
							const auto &contextLock		= WGL::Lock(context, contextHolder->win_deviceContextHandle);
							const auto &bufferHandle	= context->GenBuffer();

							context->BindBuffer(GL::Buffer::Type::Array, bufferHandle);
							context->BufferData(GL::Buffer::Type::Array, sizeof(ObjectUniformBuffer) * instancesCount, nullptr, GL::Buffer::Usage::Dynamic);

							return bufferHandle;
						}
					public:
						const Memory<ContextHolder>		contextHolder;
						const GL::VertexArray::Handle	gl_verticesArrayHandle; // Indices buffer binding cannot be performed without VAO
					public:
						const Size						instancesCount = 32 * 1024;
						const GL::Buffer::Handle		gl_objectsDataBufferHandle;
					public:
						StrongPointer<IndicesRange> indicesRange = StrongPointer<IndicesRange>(nullptr);
						Buffer gl_indicesBuffer;
						Map<Geometry::VertexPackMode, StrongPointer<VerticesRange>> verticesRanges;
					public:
						inline GeometryBufferHolder(const Memory<ContextHolder>& contextHolder_):
							contextHolder(contextHolder_),
							gl_verticesArrayHandle(ObtainVerticesArrayHandle()),
							gl_objectsDataBufferHandle(ObtainObjectsDataBuffer()),
							gl_indicesBuffer(contextHolder, GL::Buffer::Type::ElementArray, 16 * 1024)
						{
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);
							
							context->BindVertexArray(nullptr);
						}
						inline ~GeometryBufferHolder()
						{
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

							context->UnbindVertexArray(gl_verticesArrayHandle);
							context->DeleteVertexArray(gl_verticesArrayHandle);

							context->UnbindBuffer(GL::Buffer::Type::Array, gl_objectsDataBufferHandle);
							context->DeleteBuffer(gl_objectsDataBufferHandle);

							verticesRanges.clear();
						}
					public:
						inline Memory<IndicesRange> FindOrCreate(const Geometry::IndexPackMode& indicesPackMode_)
						{
							auto currentIndicesRangeMemory = indicesRange.GetValue();

							while (currentIndicesRangeMemory && currentIndicesRangeMemory->packMode != indicesPackMode_)
							{
								currentIndicesRangeMemory = currentIndicesRangeMemory->next.GetValue();
							}

							if (currentIndicesRangeMemory)
							{
								return currentIndicesRangeMemory;
							}

							indicesRange = MakeStrong<IndicesRange>(indicesPackMode_, indicesRange);

							const auto &indicesRangeMemory	= indicesRange.GetValue();

							return indicesRangeMemory;
						}
						inline Memory<IndicesHolder> FindOrCreate(const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry>& geometryMemory_)
						{
							auto &indicesHolders = indicesRangeMemory_->indicesHolders;

							for (const auto &indicesHolder : indicesHolders)
							{
								const auto &indicesHolderMemory = indicesHolder.GetValue();

								if (indicesHolderMemory->geometryMemory == geometryMemory_)
								{
									return indicesHolderMemory;
								}
							}

							// prepare data
							const auto &indicesData		= geometryMemory_->GetIndices(indicesRangeMemory_->packMode);
							const auto &indicesDataSize	= indicesData.size();

							// add new holder
							const auto &indicesHolder		= MakeStrong<IndicesHolder>(this, indicesRangeMemory_, geometryMemory_, indicesRangeMemory_->GetTotalIndicesCount());
							const auto &indicesHolderMemory	= indicesHolder.GetValue();

							indicesHolders.push_back(indicesHolder);

							indicesRangeMemory_->size += indicesDataSize;

							// insert data to buffer
							gl_indicesBuffer.Insert(indicesRangeMemory_->offset + indicesHolderMemory->firstIndex * indicesRangeMemory_->indexSize, indicesData);

							// update offsets
							auto currentIndicesRangeMemory = indicesRangeMemory_->next.GetValue();

							while (currentIndicesRangeMemory)
							{
								currentIndicesRangeMemory->offset += indicesDataSize;
								currentIndicesRangeMemory = currentIndicesRangeMemory->next.GetValue();
							}

							// return result
							return indicesHolderMemory;
						}
						inline Memory<IndicesHolder> FindOrCreate(const Memory<Geometry>& geometryMemory_, const Geometry::IndexPackMode& indicesPackMode_)
						{
							const auto &indicesRangeMemory	= FindOrCreate(indicesPackMode_);
							const auto &indicesHolderMemory = FindOrCreate(indicesRangeMemory, geometryMemory_);

							return indicesHolderMemory;
						}
						inline void Delete(const Memory<IndicesHolder>& indicesHolderMemory_)
						{
							const auto &indicesRangeMemory	= indicesHolderMemory_->indicesRangeMemory;
							const auto &indexSize			= indicesRangeMemory->indexSize;
							const auto &indicesCount		= indicesHolderMemory_->geometryMemory->GetIndicesCount();
							const auto &totalIndicesSize	= indicesRangeMemory->indexSize * indicesCount;
							const auto &totalIndicesOffset	= indicesRangeMemory->offset + indicesHolderMemory_->firstIndex * indexSize;

							gl_indicesBuffer.Remove(totalIndicesOffset, totalIndicesSize);

							// find position inside IndicesRange
							auto &indicesHolders	= indicesRangeMemory->indicesHolders;
							const auto &it			= std::find_if(indicesHolders.begin(), indicesHolders.end(), [&](const StrongPointer<IndicesHolder>& indicesHolder_){
								return indicesHolder_.GetValue() == indicesHolderMemory_;
							});

							if (it == indicesHolders.end())
							{
								throw Exception();
							}

							// update following holders
							auto nit = it; ++nit;

							while (nit != indicesHolders.end())
							{
								(*nit)->firstIndex -= indicesCount;

								++nit;
							}

							// update followint ranges
							auto currentIndicesRangeMemory = indicesRangeMemory->next.GetValue();

							while (currentIndicesRangeMemory)
							{
								currentIndicesRangeMemory->offset -= totalIndicesSize;

								currentIndicesRangeMemory = currentIndicesRangeMemory->next.GetValue();
							}

							// remove
							indicesHolders.erase(it);
						}
						inline Memory<VerticesRange> FindOrCreate(const Geometry::VertexPackMode& verticesPackMode_)
						{
							const auto &it = verticesRanges.find(verticesPackMode_);

							if (it != verticesRanges.end())
							{
								const auto &verticesRange		= (*it).second;
								const auto &verticesRangeMemory	= verticesRange.GetValue();

								return verticesRangeMemory;
							}

							const auto &context			= contextHolder->gl_context;
							const auto &contextLock		= WGL::Lock(context, contextHolder->win_deviceContextHandle);
							const auto &verticesRange	= MakeStrong<VerticesRange>(contextHolder, verticesPackMode_);

							verticesRanges.insert({ verticesPackMode_, verticesRange });

							const auto &verticesRangeMemory	= verticesRange.GetValue();

							return verticesRangeMemory;
						}
						inline Memory<VerticesHolder> FindOrCreate(const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry>& geometryMemory_)
						{
							auto &verticesHolders = verticesRangeMemory_->verticesHolders;

							for (const auto &verticesHolder : verticesHolders)
							{
								const auto &verticesHolderMemory = verticesHolder.GetValue();

								if (verticesHolderMemory->geometryMemory == geometryMemory_)
								{
									return verticesHolderMemory;
								}
							}

							// prepare data
							const auto &verticesData		= geometryMemory_->GetVertices(verticesRangeMemory_->packMode);
							const auto &verticesDataSize	= verticesData.size();

							// add new holder
							const auto &verticesHolder			= MakeStrong<VerticesHolder>(this, verticesRangeMemory_, geometryMemory_, verticesRangeMemory_->GetTotalVerticesCount());
							const auto &verticesHolderMemory	= verticesHolder.GetValue();

							verticesHolders.push_back(verticesHolder);

							// insert data to buffer
							auto &gl_verticesBuffer = verticesRangeMemory_->gl_verticesBuffer;
							
							gl_verticesBuffer.Insert(verticesHolderMemory->firstVertex * verticesRangeMemory_->vertexSize, verticesData);

							// return result
							return verticesHolderMemory;
						}
						inline Memory<VerticesHolder> FindOrCreate(const Memory<Geometry>& geometryMemory_, const Geometry::VertexPackMode& verticesPackMode_)
						{
							const auto &verticesRangeMemory		= FindOrCreate(verticesPackMode_);
							const auto &verticesHolderMemory	= FindOrCreate(verticesRangeMemory, geometryMemory_);

							return verticesHolderMemory;
						}
						inline void Delete(const Memory<VerticesHolder>& verticesHolderMemory_)
						{
							const auto &verticesRangeMemory	= verticesHolderMemory_->verticesRangeMemory;
							const auto &vertexSize			= verticesRangeMemory->vertexSize;
							const auto &verticesCount		= verticesHolderMemory_->geometryMemory->GetVerticesCount();
							const auto &totalVerticesSize	= verticesRangeMemory->vertexSize * verticesCount;
							const auto &totalVerticesOffset	= verticesHolderMemory_->firstVertex * vertexSize;

							// remove from buffer
							auto &gl_verticesBuffer = verticesRangeMemory->gl_verticesBuffer;
							
							gl_verticesBuffer.Remove(totalVerticesOffset, totalVerticesSize);

							// fvert position inside VerticesRange
							auto &verticesHolders	= verticesRangeMemory->verticesHolders;
							const auto &it			= std::find_if(verticesHolders.begin(), verticesHolders.end(), [&](const StrongPointer<VerticesHolder>& verticesHolder_){
								return verticesHolder_.GetValue() == verticesHolderMemory_;
							});

							if (it == verticesHolders.end())
							{
								throw Exception();
							}

							// update following holders
							auto nit = it; ++nit;

							while (nit != verticesHolders.end())
							{
								(*nit)->firstVertex -= verticesCount;

								++nit;
							}

							// remove
							verticesHolders.erase(it);
						}
					};
					Forward::GeometryBufferHolder::VerticesHolder::VerticesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry>& geometryMemory_, const Size& firstVertex_):
						verticesRangeMemory(verticesRangeMemory_),
						geometryMemory(geometryMemory_),
						unsubscriber(geometryMemory->OnDestruction(std::bind(static_cast<void(GeometryBufferHolder::*)(const Memory<GeometryBufferHolder::VerticesHolder>&)>(&Forward::GeometryBufferHolder::Delete), geometryBufferHolderMemory_, this))),
						firstVertex(firstVertex_)
					{
					}
					Forward::GeometryBufferHolder::IndicesHolder::IndicesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry>& geometryMemory_, const Size& firstIndex_):
						indicesRangeMemory(indicesRangeMemory_),
						geometryMemory(geometryMemory_),
						unsubscriber(geometryMemory->OnDestruction(std::bind(static_cast<void(GeometryBufferHolder::*)(const Memory<GeometryBufferHolder::IndicesHolder>&)>(&Forward::GeometryBufferHolder::Delete), geometryBufferHolderMemory_, this))),
						firstIndex(firstIndex_)
					{
					}
#pragma endregion
#pragma region Forward::SceneCache
					class Forward::SceneCache:
						public This<SceneCache>
					{
						friend Output;
					public:
						class AttributesNode
						{
						public:
							const Memory<AttributesCache> attributesCacheMemory;
							Vector<Memory<Object>> objectsMemories;
						public:
							inline AttributesNode(const Memory<AttributesCache>& attributesCacheMemory_):
								attributesCacheMemory(attributesCacheMemory_)
							{
							}
							inline AttributesNode(AttributesNode&& source_):
								attributesCacheMemory(source_.attributesCacheMemory),
								objectsMemories(Move(source_.objectsMemories))
							{
							}
						public:
							inline void Add(const Memory<Object>& objectMemory_)
							{
								objectsMemories.push_back(objectMemory_);
							}
						};
						class MaterialNode
						{
						public:
							const Memory<MaterialCache> materialCacheMemory;
							Vector<AttributesNode> attributesNodes;
							Map<Memory<AttributesCache>, Size> attributesCachesIndices;
						public:
							inline MaterialNode(const Memory<MaterialCache>& materialCacheMemory_):
								materialCacheMemory(materialCacheMemory_)
							{
							}
							inline MaterialNode(MaterialNode&& source_):
								materialCacheMemory(source_.materialCacheMemory),
								attributesNodes(Move(source_.attributesNodes)),
								attributesCachesIndices(Move(source_.attributesCachesIndices))
							{
							}
						public:
							inline AttributesNode& FindOrCreate(const Memory<AttributesCache>& attributesCacheMemory_)
							{
								const auto &it = attributesCachesIndices.find(attributesCacheMemory_);

								if (it != attributesCachesIndices.end())
								{
									const auto &attributesCacheIndex	= (*it).second;
									auto &attributesCache				= attributesNodes[attributesCacheIndex];

									return attributesCache;
								}

								const auto &index = attributesNodes.size();

								attributesCachesIndices.insert({ attributesCacheMemory_, index });
								attributesNodes.emplace_back(attributesCacheMemory_);

								auto &attributesNode = attributesNodes[index];

								return attributesNode;
							}
						};
						class MaterialsNodes
						{
						public:
							Vector<MaterialNode> materialsNodes;
							Map<Memory<MaterialCache>, Size> materialsCachesIndices;
						public:
							inline void Clear()
							{
								materialsNodes.clear();
								materialsCachesIndices.clear();
							}
							inline MaterialNode& FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_)
							{
								const auto &it = materialsCachesIndices.find(materialCacheMemory_);

								if (it != materialsCachesIndices.end())
								{
									const auto &materialNodeIndex	= (*it).second;
									auto &materialNode				= materialsNodes[materialNodeIndex];

									return materialNode;
								}

								const auto &index = materialsNodes.size();

								materialsCachesIndices.insert({ materialCacheMemory_, index });
								materialsNodes.emplace_back(materialCacheMemory_);

								auto &materialNode = materialsNodes[index];

								return materialNode;
							}
						};
					protected:
						const Memory<Forward> methodMemory;
						const Memory<Scene> sceneMemory;
						Scene::Version sceneVersion;
						MaterialsNodes materialsNodes;
					public:
						inline SceneCache(const StrongPointer<SceneCache>& this_, const Memory<Forward>& methodMemory_, const Memory<Scene>& sceneMemory_);
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

							// if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureAlbedo"))
							// {
							// 	GL::SetUniform(uniformLocation, 0);
							// }
							// if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureNormals"))
							// {
							// 	GL::SetUniform(uniformLocation, 1);
							// }
							// if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureRoughness"))
							// {
							// 	GL::SetUniform(uniformLocation, 2);
							// }
							// if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureMetalness"))
							// {
							// 	GL::SetUniform(uniformLocation, 3);
							// }
							// if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureOcclusion"))
							// {
							// 	GL::SetUniform(uniformLocation, 4);
							// }
							// if (const auto &uniformLocation = GL::GetUniformLocation(program, "textureEnvironment"))
							// {
							// 	GL::SetUniform(uniformLocation, 8);
							// }

							return programHandle;
						}
					public:
						const Memory<Forward>							methodMemory;
						const Memory<Material>							materialMemory;
						const Material::EventDestruction::Unsubscriber	unsubscriber;
					public:
						const GL::Program::Handle						gl_programHandle;
						AttributesCaches								attributesCaches;
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
							const auto &context					= methodMemory->contextHolder->gl_context;
							const auto &currentProgramHandle	= context->GetCurrentProgram();

							if (currentProgramHandle == gl_programHandle)
							{
								context->UseProgram(0);
							}

							context->DeleteProgram(gl_programHandle);
						}
					public:
						inline Memory<AttributesCache> FindOrCreate(const Memory<ModelCache>& modelCacheMemory_);
						inline void Delete(const Memory<AttributesCache>& attributesCacheMemory_);
					};
#pragma endregion
#pragma region Forward::ModelCache
					class Forward::ModelCache
					{
					public:
						const Memory<Forward>								methodMemory;
						const Memory<Model>									modelMemory;
						const Memory<GeometryBufferHolder::VerticesHolder>	verticesHolderMemory;
						const Memory<GeometryBufferHolder::IndicesHolder>	indicesHolderMemory;
					public:
						inline ModelCache(const Memory<Forward>& methodMemory_, const Memory<Model>& modelMemory_):
							methodMemory(methodMemory_),
							modelMemory(modelMemory_),
							verticesHolderMemory(methodMemory->geometryBufferHolder->FindOrCreate(modelMemory->GetGeometry().GetValue(), modelMemory->GetVerticesPackMode())),
							indicesHolderMemory(methodMemory->geometryBufferHolder->FindOrCreate(modelMemory->GetGeometry().GetValue(), modelMemory->GetIndicesPackMode()))
						{
						}
						inline ~ModelCache()
						{
							// TODO
						}
					};
#pragma endregion
#pragma region Forward::AttributesCache
					class Forward::AttributesCache
					{
					public:
						inline GL::VertexArray::Handle ObtainVerticesArrayHandle() const
						{
							const auto &context		= materialCacheMemory->methodMemory->contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, materialCacheMemory->methodMemory->contextHolder->win_deviceContextHandle);
							const auto &verticesArrayHandle = context->GenVertexArray();

							context->BindVertexArray(verticesArrayHandle);

							return verticesArrayHandle;
						}
					public:
						const Memory<MaterialCache> materialCacheMemory;
						const Memory<ModelCache> modelCacheMemory;
						const Model::EventDestruction::Unsubscriber unsubscriber;
						const GL::VertexArray::Handle gl_verticesArrayHandle;
					public:
						inline AttributesCache(const Memory<MaterialCache>& materialCacheMemory_, const Memory<ModelCache>& modelCacheMemory_):
							materialCacheMemory(materialCacheMemory_),
							modelCacheMemory(modelCacheMemory_),
							unsubscriber(modelCacheMemory_->modelMemory->OnDestruction(std::bind(&MaterialCache::Delete, materialCacheMemory, this))),
							gl_verticesArrayHandle(ObtainVerticesArrayHandle())
						{
							const auto &context				= materialCacheMemory->methodMemory->contextHolder->gl_context;
							const auto &contextLock			= WGL::Lock(context, materialCacheMemory->methodMemory->contextHolder->win_deviceContextHandle);
							const auto &verticesPackMode	= modelCacheMemory->modelMemory->GetVerticesPackMode();
							const auto &vertexSize			= Geometry::GetVertexSize(verticesPackMode);
							const auto &verticesCount		= modelCacheMemory->modelMemory->GetGeometry()->GetVerticesCount();

							context->BindBuffer(GL::Buffer::Type::ElementArray, materialCacheMemory->methodMemory->geometryBufferHolder->gl_indicesBuffer.gl_bufferHandle);

							if (verticesPackMode == Geometry::VertexPackMode::Pos32F)
							{
								context->BindBuffer(GL::Buffer::Type::Array, modelCacheMemory->verticesHolderMemory->verticesRangeMemory->gl_verticesBuffer.gl_bufferHandle);
								
								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vPos"))
								{
									context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, 0);
									context->EnableVertexAttributeArray(attributeLocation);
								}
							}
							else if (verticesPackMode == Geometry::VertexPackMode::Pos32F_TBN32F_Tex32F)
							{
								context->BindBuffer(GL::Buffer::Type::Array, modelCacheMemory->verticesHolderMemory->verticesRangeMemory->gl_verticesBuffer.gl_bufferHandle);

								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vPos"))
								{
									context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, 0);
									context->EnableVertexAttributeArray(attributeLocation);
								}
							}
							else if (verticesPackMode == Geometry::VertexPackMode::Pos32F_TN16F_Tex32F)
							{
								context->BindBuffer(GL::Buffer::Type::Array, modelCacheMemory->verticesHolderMemory->verticesRangeMemory->gl_verticesBuffer.gl_bufferHandle);

								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vPos"))
								{
									context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, 0);
									context->EnableVertexAttributeArray(attributeLocation);
								}
							}

							context->BindBuffer(GL::Buffer::Type::Array, materialCacheMemory->methodMemory->geometryBufferHolder->gl_objectsDataBufferHandle);

							if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vModelMatrix1"))
							{
								context->VertexAttributePointer(attributeLocation, 4, GL::Program::Attribute::Type::Float, false, sizeof(ObjectUniformBuffer), 0);
								context->VertexAttribDivisor(attributeLocation, verticesCount);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vModelMatrix2"))
							{
								context->VertexAttributePointer(attributeLocation, 4, GL::Program::Attribute::Type::Float, false, sizeof(ObjectUniformBuffer), sizeof(Vec4));
								context->VertexAttribDivisor(attributeLocation, verticesCount);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vModelMatrix3"))
							{
								context->VertexAttributePointer(attributeLocation, 4, GL::Program::Attribute::Type::Float, false, sizeof(ObjectUniformBuffer), sizeof(Vec4) * 2);
								context->VertexAttribDivisor(attributeLocation, verticesCount);
								context->EnableVertexAttributeArray(attributeLocation);
							}

							context->BindVertexArray(nullptr);
						}
						inline ~AttributesCache()
						{
							const auto &context		= materialCacheMemory->methodMemory->contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, materialCacheMemory->methodMemory->contextHolder->win_deviceContextHandle);

							context->UnbindVertexArray(gl_verticesArrayHandle);
							context->DeleteVertexArray(gl_verticesArrayHandle);
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
						const auto &context		= contextHolder->gl_context;
						const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

						sceneCaches.clear();
						// modelCaches.clear();
						materialCaches.clear();
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

						const auto &context		= contextHolder->gl_context;
						const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

						materialCaches.erase(it);
					}
					// void Forward::Remove(const Memory<Model>& modelMemory_)
					// {
					// 	/*const auto &it = modelCaches.find(modelMemory_);
					// 
					// 	if (it == modelCaches.end())
					// 	{
					// 		throw Exception();
					// 	}
					// 
					// 	const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
					// 	const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();
					// 
					// 	GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());
					// 
					// 	modelCaches.erase(it);
					// 
					// 	GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);*/
					// }

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

					/*Forward::SceneCache::MaterialNode& Forward::SceneCache::FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_)
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
					Forward::SceneCache::ModelNode& Forward::SceneCache::FindOrCreate(MaterialNode& materialNode_, const Memory<Model>& modelMemory_)
					{
						auto		&modelsTable	= materialNode_.modelsTable;
						const auto	&it				= modelsTable.find(modelMemory_);

						if (it != modelsTable.end())
						{
							auto &modelNode = (*it).second;

							return modelNode;
						}

						const auto &geometryHolder			= methodMemory->geometryBufferHolder->Allocate(modelMemory_->GetGeometry().GetValue(), modelMemory_->GetVerticesPackMode(), modelMemory_->GetIndicesPackMode());
						const auto &attributesCacheMemory	= materialNode_.materialCacheMemory->FindOrCreate(geometryHolder.GetValue());
						const auto &nIt						= modelsTable.emplace(
							std::piecewise_construct,
							std::forward_as_tuple(modelMemory_),
							std::forward_as_tuple(&materialNode_, modelMemory_, geometryHolder, attributesCacheMemory)
						); // TODO: add check?
						auto &modelNode		= (*nIt.first).second;

						return modelNode;
					}*/

					void Forward::SceneCache::ForceUpdateCaches()
					{
						const auto &contextHolder		= methodMemory->contextHolder;
						const auto &deviceContextHandle	= contextHolder->win_deviceContextHandle;
						const auto &renderContext		= contextHolder->gl_context;

						WGL::Lock contextLock(renderContext, deviceContextHandle);

						auto &objects = sceneMemory->objects;

						// materialsTable.clear();
						materialsNodes.Clear();
						
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

							// obtain attributes cache
							const auto &attributesCacheMemory	= materialCacheMemory->FindOrCreate(modelCacheMemory);

							// obtain tables
							auto &materialNode					= materialsNodes.FindOrCreate(materialCacheMemory);
							auto &attributesNode				= materialNode.FindOrCreate(attributesCacheMemory);
						
							attributesNode.Add(objectMemory);
						}
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

						const auto &contextHolder		= methodMemory->contextHolder;
						const auto &deviceContextHandle	= view_->GetDeviceContextHandle();
						const auto &renderContext		= contextHolder->gl_context;
						const auto &contextLock			= WGL::Lock(renderContext, deviceContextHandle);
						
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

						const bool useMultithreading = GetAsyncKeyState('H') == 0;

						for (const auto &materialNode : materialsNodes.materialsNodes)
						{
							const auto &materialCacheMemory = materialNode.materialCacheMemory;

							renderContext->UseProgram(materialCacheMemory->gl_programHandle);

							if (auto location = renderContext->GetUniformLocation(materialCacheMemory->gl_programHandle, "viewProjectionMatrix"))
							{
								renderContext->SetUniform(location, Perspective(60.0f, aspect, 0.1f, 10000.0f) * camera_->GetVMat());
							}

							for (auto &attributesNode : materialNode.attributesNodes)
							{
								const auto &attributesCacheMemory	= attributesNode.attributesCacheMemory;

								renderContext->BindVertexArray(attributesCacheMemory->gl_verticesArrayHandle);
								
								const auto &modelCacheMemory		= attributesCacheMemory->modelCacheMemory;
								const auto &modelMemory				= modelCacheMemory->modelMemory;
								const auto &geometryMemory			= modelMemory->GetGeometry().GetValue();

								for (auto &objectMemory : attributesNode.objectsMemories)
								{
									renderContext->BindBuffer(GL::Buffer::Type::Array, methodMemory->geometryBufferHolder->gl_objectsDataBufferHandle);

									ObjectUniformBuffer t;

									t.modelMatrix = Transpose(glm::mat4x3(objectMemory->GetMMat()));

									renderContext->BufferSubData(GL::Buffer::Type::Array, 0, sizeof(t), &t);

									renderContext->DrawElementsBaseVertex(
										GL::PrimitiveType::Triangles,
										geometryMemory->GetIndicesCount(), // TODO: move to cache
										modelMemory->GetIndicesPackMode() == Geometry::IndexPackMode::UInt32 ? GL::IndexType::UInt32 : // TODO: move to cache
										modelMemory->GetIndicesPackMode() == Geometry::IndexPackMode::UInt16 ? GL::IndexType::UInt16 : // TODO: move to cache
										GL::IndexType::UInt8,																		   // TODO: move to cache
										modelCacheMemory->indicesHolderMemory->indicesRangeMemory->offset + modelCacheMemory->indicesHolderMemory->indicesRangeMemory->indexSize * modelCacheMemory->indicesHolderMemory->firstIndex, // TODO: move to cache
										modelCacheMemory->verticesHolderMemory->firstVertex // TODO: move to cache
									);
								}
							}
						}

						/*for (auto &objectMemory : sceneMemory->objects)
						{
							// obtain material cache
							const auto &material				= objectMemory->GetMaterial();
							const auto &materialMemory			= material.GetValue();
							const auto &materialCacheMemory		= methodMemory->FindOrAdd(materialMemory);
						
							// obtain model cache
							const auto &model					= objectMemory->GetModel();
							const auto &modelMemory				= model.GetValue();
							const auto &modelCacheMemory		= methodMemory->FindOrAdd(modelMemory);

							// obtain attributes cache
							const auto &attributesCacheMemory	= materialCacheMemory->FindOrCreate(modelCacheMemory);

							// if (auto location = renderContext->GetUniformLocation(materialCacheMemory->gl_programHandle, "modelViewProjectionMatrix"))
							// {
							// 	renderContext->SetUniform(location, Perspective(60.0f, aspect, 0.1f, 10000.0f) * camera_->GetVMat() * objectMemory->GetMMat());
							// }
							if (auto location = renderContext->GetUniformLocation(materialCacheMemory->gl_programHandle, "viewProjectionMatrix"))
							{
								renderContext->SetUniform(location, Perspective(60.0f, aspect, 0.1f, 10000.0f) * camera_->GetVMat());
							}

							renderContext->BindBuffer(GL::Buffer::Type::Array, methodMemory->geometryBufferHolder->gl_objectsDataBufferHandle);

							ObjectUniformBuffer t;

							t.modelMatrix = Transpose(glm::mat4x3(objectMemory->GetMMat()));

							renderContext->BufferSubData(GL::Buffer::Type::Array, 0, sizeof(t), &t);

							const auto &geometryMemory = modelMemory->GetGeometry().GetValue();

							renderContext->BindVertexArray(attributesCacheMemory->gl_verticesArrayHandle);

							renderContext->DrawElementsBaseVertex(
								GL::PrimitiveType::Triangles,
								geometryMemory->GetIndicesCount(),
								modelMemory->GetIndicesPackMode() == Geometry::IndexPackMode::UInt32 ? GL::IndexType::UInt32 :
								modelMemory->GetIndicesPackMode() == Geometry::IndexPackMode::UInt16 ? GL::IndexType::UInt16 :
								GL::IndexType::UInt8,
								modelCacheMemory->indicesHolderMemory->indicesRangeMemory->offset + modelCacheMemory->indicesHolderMemory->indicesRangeMemory->indexSize * modelCacheMemory->indicesHolderMemory->firstIndex,
								modelCacheMemory->verticesHolderMemory->firstVertex
							);
						}*/

						/*for (auto &materialIt : materialsTable)
						{
							const auto	&materialCacheMemory	= materialIt.first;
							const auto	&materialNode			= materialIt.second;
							const auto	&modelsTable			= materialNode.modelsTable;

							renderContext->UseProgram(materialCacheMemory->gl_programHandle);

							for (auto &modelIt : modelsTable)
							{
								const auto &modelNode				= modelIt.second;
								const auto &geometryMemory			= modelNode.modelMemory->GetGeometry().GetValue();
								const auto &attributesCacheMemory	= modelNode.attributesCacheMemory;
								const auto &objectsTable			= modelNode.objectsTable;

								renderContext->BindVertexArray(attributesCacheMemory->gl_verticesArrayHandle);

								for (auto &objectMemory : objectsTable)
								{
									if (auto location = renderContext->GetUniformLocation(materialCacheMemory->gl_programHandle, "modelViewProjectionMatrix"))
									{
										renderContext->SetUniform(location, Perspective(60.0f, aspect, 0.1f, 10000.0f) * camera_->GetVMat() * objectMemory->GetMMat());
									}

									renderContext->DrawElementsBaseVertex(
										GL::PrimitiveType::Triangles,
										geometryMemory->GetIndicesCount(),
										attributesCacheMemory->indicesRangeMemory->packMode == Geometry::IndexPackMode::UInt32 ? GL::IndexType::UInt32 :
										attributesCacheMemory->indicesRangeMemory->packMode == Geometry::IndexPackMode::UInt16 ? GL::IndexType::UInt16 :
										GL::IndexType::UInt8,
										attributesCacheMemory->indicesRangeMemory->offset + attributesCacheMemory->indicesRangeMemory->indexSize * modelNode.geometryHolder->geometryIndicesHolderMemory->firstIndex,
										modelNode.geometryHolder->geometryVerticesHolderMemory->firstVertex
									);
								}
							}
						}*/
						
						renderContext->BindVertexArray(nullptr);

						SwapBuffers(deviceContextHandle);
					}

					StrongPointer<Forward::Output> Forward::SceneCache::Render(const StrongPointer<Camera>& camera_)
					{
						return Make<Output>(GetThis<SceneCache>(), camera_);
					}
#pragma endregion
#pragma region Forward::MaterialCache
					Memory<Forward::AttributesCache> Forward::MaterialCache::FindOrCreate(const Memory<ModelCache>& modelCacheMemory_)
					{
						const auto &it = attributesCaches.find(modelCacheMemory_);

						if (it != attributesCaches.end())
						{
							const auto &attributesCache			= (*it).second;
							const auto &attributesCacheMemory	= attributesCache.GetValue();

							return attributesCacheMemory;
						}

						const auto &attributesCache = MakeStrong<AttributesCache>(this, modelCacheMemory_);

						attributesCaches.insert({ modelCacheMemory_, attributesCache });

						const auto &attributesCacheMemory = attributesCache.GetValue();

						return attributesCacheMemory;
					}
					void Forward::MaterialCache::Delete(const Memory<AttributesCache>& attributesCacheMemory_)
					{

					}
#pragma endregion
				}
			}
		}
	}
}


#pragma region
#pragma endregion


