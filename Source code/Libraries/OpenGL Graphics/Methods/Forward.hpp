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
						/*class MaterialCache;
						using MaterialCaches = Map<Memory<Material>, StrongPointer<MaterialCache>>;
						class AttributesCache;
						class ModelCache;
						using ModelCaches = Map<Memory<Model>, StrongPointer<ModelCache>>;*/
					protected:
						const StrongPointer<ContextHolder> contextHolder = MakeStrong<ContextHolder>();
						const StrongPointer<GeometryBufferHolder> geometryBufferHolder = MakeStrong<GeometryBufferHolder>(contextHolder);
						// MaterialCaches materialCaches;
						// ModelCaches modelCaches;
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
						// inline Memory<MaterialCache> FindOrAdd(const Memory<Material>& materialMemory_);
						// inline Memory<ModelCache> FindOrAdd(const Memory<Model>& modelMemory_);
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
#pragma region GeometryBufferHolder
					class Forward::GeometryBufferHolder
					{
					protected:
						class VerticesRange;
						class IndicesRange;
						class GeometryVerticesHolder
						{
						public:
							const Memory<VerticesRange>					verticesRangeMemory;
							const Memory<Geometry>						geometryMemory;
							const Size									verticesCount;
							Size										firstVertex;
							Geometry::EventDestruction::Unsubscriber	unsubscriber;
						public:
							inline GeometryVerticesHolder(const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry>& geometryMemory_, const Size& verticesCount_, const Size& firstVertex_):
								verticesRangeMemory(verticesRangeMemory_),
								geometryMemory(geometryMemory_),
								verticesCount(verticesCount_),
								firstVertex(firstVertex_)
							{
							}
						};
						class GeometryIndicesHolder
						{
						public:
							const Memory<IndicesRange>					indicesRangeMemory;
							const Memory<Geometry>						geometryMemory;
							const Size									indicesCount;
							Size										firstIndex;
							Geometry::EventDestruction::Unsubscriber	unsubscriber;
						public:
							inline GeometryIndicesHolder(const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry>& geometryMemory_, const Size& indicesCount_, const Size& firstIndex_):
								indicesRangeMemory(indicesRangeMemory_),
								geometryMemory(geometryMemory_),
								indicesCount(indicesCount_),
								firstIndex(firstIndex_)
							{
							}
						};
						class VerticesRange
						{
						public:
							const Geometry::VertexPackMode packMode;
							const Size vertexSize = Geometry::GetVertexSize(packMode);
							StrongPointer<VerticesRange> next = StrongPointer<VerticesRange>(nullptr);
							Vector<StrongPointer<GeometryVerticesHolder>> geometryVerticesHolders;
						public:
							inline VerticesRange(const Geometry::VertexPackMode& packMode_, const StrongPointer<VerticesRange>& next_ = StrongPointer<VerticesRange>(nullptr)):
								packMode(packMode_),
								next(next_)
							{
							}
						};
						class IndicesRange
						{
						public:
							const Geometry::IndexPackMode packMode;
							const Size indexSize = Geometry::GetIndexSize(packMode);
							StrongPointer<IndicesRange> next = StrongPointer<IndicesRange>(nullptr);
							Vector<StrongPointer<GeometryIndicesHolder>> geometryIndicesHolders;
						public:
							inline IndicesRange(const Geometry::IndexPackMode& packMode_, const StrongPointer<IndicesRange>& next_ = StrongPointer<IndicesRange>(nullptr)):
								packMode(packMode_),
								next(next_)
							{
							}
						};
						class GeometryHolder
						{
						public:
							const Memory<GeometryVerticesHolder> geometryVerticesHolderMemory;
							const Memory<GeometryIndicesHolder> geometryIndicesHolderMemory;
						public:
							inline GeometryHolder(const Memory<GeometryVerticesHolder>& geometryVerticesHolderMemory_, const Memory<GeometryIndicesHolder>& geometryIndicesHolderMemory_):
								geometryVerticesHolderMemory(geometryVerticesHolderMemory_),
								geometryIndicesHolderMemory(geometryIndicesHolderMemory_)
							{
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
						inline GL::Buffer::Handle ObtainVerticesBuffer()
						{
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

							auto buffer = context->GenBuffer();
						
							context->BindBuffer(GL::Buffer::Type::Array, buffer);
							context->BufferData(GL::Buffer::Type::Array, verticesBufferCapacity, nullptr, GL::Buffer::Usage::Static);
						
							return buffer;
						}
						inline GL::Buffer::Handle ObtainIndicesBuffer()
						{
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

							auto buffer = context->GenBuffer();
						
							context->BindBuffer(GL::Buffer::Type::ElementArray, buffer);
							context->BufferData(GL::Buffer::Type::ElementArray, indicesBufferCapacity, nullptr, GL::Buffer::Usage::Static);
						
							return buffer;
						}
					public:
						const Memory<ContextHolder>		contextHolder;
						const GL::VertexArray::Handle	gl_verticesArrayHandle; // Indices buffer binding cannot be performed without VAO
					public:
						Size							verticesBufferCapacity = 128 * 1024; // in bytes
						const GL::Buffer::Handle		gl_verticesBuffer;
						StrongPointer<VerticesRange>	verticesRange = StrongPointer<VerticesRange>(nullptr);
						Size							indicesBufferCapacity = 16 * 1024; // in bytes
						const GL::Buffer::Handle		gl_indicesBuffer;
						StrongPointer<IndicesRange>		indicesRange = StrongPointer<IndicesRange>(nullptr);
					public:
						inline GeometryBufferHolder(const Memory<ContextHolder>& contextHolder_):
							contextHolder(contextHolder_),
							gl_verticesArrayHandle(ObtainVerticesArrayHandle()),
							gl_verticesBuffer(ObtainVerticesBuffer()),
							gl_indicesBuffer(ObtainIndicesBuffer())
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

							context->UnbindBuffer(GL::Buffer::Type::Array, gl_verticesBuffer);
							context->DeleteBuffer(gl_verticesBuffer);

							context->UnbindBuffer(GL::Buffer::Type::ElementArray, gl_indicesBuffer);
							context->DeleteBuffer(gl_indicesBuffer);
						}
					protected:
						inline Size GetTotalVerticesCount(const Memory<VerticesRange>& verticesRangeMemory_) const
						{
							auto size = Size(0);

							if (verticesRangeMemory_)
							{
								for (auto &geometryVerticesHolder : verticesRangeMemory_->geometryVerticesHolders)
								{
									size += geometryVerticesHolder->verticesCount;
								}
							}

							return size;
						}
						inline Size GetTotalVerticesSize(const Memory<VerticesRange>& verticesRangeMemory_) const
						{
							if (verticesRangeMemory_)
							{
								return GetTotalVerticesCount(verticesRangeMemory_) * verticesRangeMemory_->vertexSize;
							}

							return 0;
						}
						inline Size GetTotalVerticesSizeUntil(const Memory<VerticesRange>& verticesRangeMemory_) const
						{
							auto currentVerticesRange		= verticesRange;
							auto currentVerticesRangeMemory	= currentVerticesRange.GetValue();

							if (currentVerticesRangeMemory)
							{
								auto size = GetTotalVerticesSize(currentVerticesRangeMemory);

								while (currentVerticesRangeMemory != verticesRangeMemory_)
								{
									currentVerticesRangeMemory = currentVerticesRangeMemory->next.GetValue();

									size += GetTotalVerticesSize(currentVerticesRangeMemory);
								}

								return size;
							}

							return 0;
						}
						inline Size GetTotalIndicesCount(const Memory<IndicesRange>& indicesRangeMemory_) const
						{
							auto size = Size(0);

							if (indicesRangeMemory_)
							{
								for (auto &geometryIndicesHolder : indicesRangeMemory_->geometryIndicesHolders)
								{
									size += geometryIndicesHolder->indicesCount;
								}
							}

							return size;
						}
						inline Size GetTotalIndicesSize(const Memory<IndicesRange>& indicesRangeMemory_) const
						{
							if (indicesRangeMemory_)
							{
								return GetTotalIndicesCount(indicesRangeMemory_) * indicesRangeMemory_->indexSize;
							}

							return 0;
						}
						inline Size GetTotalIndicesSizeUntil(const Memory<IndicesRange>& indicesRangeMemory_) const
						{
							auto currentIndicesRange		= indicesRange;
							auto currentIndicesRangeMemory	= currentIndicesRange.GetValue();

							if (currentIndicesRangeMemory)
							{
								auto size = GetTotalIndicesSize(currentIndicesRangeMemory);

								while (currentIndicesRangeMemory != indicesRangeMemory_)
								{
									currentIndicesRangeMemory = currentIndicesRangeMemory->next.GetValue();

									size += GetTotalIndicesSize(currentIndicesRangeMemory);
								}

								return size;
							}

							return 0;
						}
					protected:
						inline void InsertToVerticesBuffer(const Size& offset_, const Vector<UInt8>& data_)
						{
							const auto &totalCurrentBufferSize			= GetTotalVerticesSizeUntil(nullptr); // memory currently allocated
							const auto &totalBufferSizeAfterInsertion	= totalCurrentBufferSize + data_.size();

							// lock render context
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

							// copy currently allocated data to temporal buffer, resize vertices buffer, copy data back
							if (totalBufferSizeAfterInsertion > verticesBufferCapacity)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, totalCurrentBufferSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, totalCurrentBufferSize);

								// resize buffer
								auto powerOfTwoSize = static_cast<Size>(glm::pow(2, glm::ceil(glm::log(static_cast<Float64>(totalBufferSizeAfterInsertion)) / glm::log(2.0))));
								auto newBufferSize = glm::max<Size>(powerOfTwoSize * 2, 128 * 1024);

								context->BufferData(GL::Buffer::Type::CopyRead, newBufferSize, nullptr, GL::Buffer::Usage::Static);
									
								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, totalCurrentBufferSize);

								verticesBufferCapacity = newBufferSize;

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							const auto &tailSize		= totalCurrentBufferSize - offset_; // number of bytes to move right
							
							if (tailSize > 0)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, tailSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, offset_, 0, tailSize);

								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, offset_ + data_.size(), tailSize);

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							// insert data
							context->BindBuffer(GL::Buffer::Type::Array, gl_verticesBuffer);
							context->BufferSubData(GL::Buffer::Type::Array, offset_, data_.size(), data_.data());
							context->BindBuffer(GL::Buffer::Type::Array, nullptr);
						}
						inline void RemoveFromVerticesBuffer(const Size& offset_, const Size& size_)
						{
							// lock render context
							const auto &context = contextHolder->gl_context;
							const auto &contextLock = WGL::Lock(context, contextHolder->win_deviceContextHandle);

							const auto &totalCurrentBufferSize	= GetTotalVerticesSizeUntil(nullptr); // memory currently allocated
							const auto &tailOffset				= offset_ + size_;
							const auto &tailSize				= totalCurrentBufferSize - tailOffset;

							if (tailSize > 0)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, tailSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, tailOffset, 0, tailSize);

								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, offset_, tailSize);

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							const auto &totalBufferSizeAfterRemoving	= totalCurrentBufferSize - size_;
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
							}
						}
						inline void InsertToIndicesBuffer(const Size& offset_, const Vector<UInt8>& data_)
						{
							const auto &totalCurrentBufferSize			= GetTotalIndicesSizeUntil(nullptr); // memory currently allocated
							const auto &totalBufferSizeAfterInsertion	= totalCurrentBufferSize + data_.size();

							// lock render context
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

							// copy currently allocated data to temporal buffer, resize indices buffer, copy data back
							if (totalBufferSizeAfterInsertion > indicesBufferCapacity)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, totalCurrentBufferSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_indicesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, totalCurrentBufferSize);

								// resize buffer
								auto powerOfTwoSize = static_cast<Size>(glm::pow(2, glm::ceil(glm::log(static_cast<Float64>(totalBufferSizeAfterInsertion)) / glm::log(2.0))));
								auto newBufferSize = glm::max<Size>(powerOfTwoSize * 2, 16 * 1024);

								context->BufferData(GL::Buffer::Type::CopyRead, newBufferSize, nullptr, GL::Buffer::Usage::Static);
									
								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, totalCurrentBufferSize);

								indicesBufferCapacity = newBufferSize;

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							const auto &tailSize		= totalCurrentBufferSize - offset_; // number of bytes to move right
							
							if (tailSize > 0)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, tailSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_indicesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, offset_, 0, tailSize);

								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, offset_ + data_.size(), tailSize);

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							// insert data
							context->BindBuffer(GL::Buffer::Type::Array, gl_indicesBuffer);
							context->BufferSubData(GL::Buffer::Type::Array, offset_, data_.size(), data_.data());
							context->BindBuffer(GL::Buffer::Type::Array, nullptr);
						}
						inline void RemoveFromIndicesBuffer(const Size& offset_, const Size& size_)
						{
							// lock render context
							const auto &context = contextHolder->gl_context;
							const auto &contextLock = WGL::Lock(context, contextHolder->win_deviceContextHandle);

							const auto &totalCurrentBufferSize	= GetTotalIndicesSizeUntil(nullptr); // memory currently allocated
							const auto &tailOffset				= offset_ + size_;
							const auto &tailSize				= totalCurrentBufferSize - tailOffset;

							if (tailSize > 0)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, tailSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_indicesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, tailOffset, 0, tailSize);

								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, offset_, tailSize);

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							const auto &totalBufferSizeAfterRemoving	= totalCurrentBufferSize - size_;
							const auto &sizeLimit						= glm::max<Size>(indicesBufferCapacity / 8, 128 * 1024);

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
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_indicesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, totalBufferSizeAfterRemoving);

								// resize buffer
								context->BufferData(GL::Buffer::Type::CopyRead, sizeLimit, nullptr, GL::Buffer::Usage::Static);
									
								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, totalBufferSizeAfterRemoving);

								indicesBufferCapacity = sizeLimit;

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}
						}
					protected:
						inline Memory<VerticesRange> FindOrCreate(const Geometry::VertexPackMode& packMode_)
						{
							auto currentVerticesRange = verticesRange;

							while (currentVerticesRange && currentVerticesRange->packMode != packMode_)
							{
								currentVerticesRange = currentVerticesRange->next;
							}

							if (!currentVerticesRange)
							{
								currentVerticesRange = verticesRange = MakeStrong<VerticesRange>(packMode_, verticesRange);
							}

							return currentVerticesRange.GetValue();
						}
						inline void Delete(const Memory<GeometryVerticesHolder>& geometryVerticesHolderMemory_)
						{
							const auto &verticesRangeMemory = geometryVerticesHolderMemory_->verticesRangeMemory;

							// calculate offset
							const auto &verticesRangeTotalDataAmount	= GetTotalVerticesSize(verticesRangeMemory);
							const auto &verticesRangeDataOffset			= GetTotalVerticesSizeUntil(verticesRangeMemory) - verticesRangeTotalDataAmount;
							const auto &geometryVerticesDataOffset		= verticesRangeDataOffset + geometryVerticesHolderMemory_->firstVertex * verticesRangeMemory->vertexSize;
							const auto &geometryVerticesDataSize		= geometryVerticesHolderMemory_->verticesCount * verticesRangeMemory->vertexSize;
							
							// remove from buffer
							RemoveFromVerticesBuffer(geometryVerticesDataOffset, geometryVerticesDataSize);
						}
						inline Memory<GeometryVerticesHolder> FindOrCreate(const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry>& geometryMemory_)
						{
							auto &geometryVerticesHolders = verticesRangeMemory_->geometryVerticesHolders;

							// check if holder already exist
							for (auto &geometryVerticesHolder : geometryVerticesHolders)
							{
								if (geometryVerticesHolder->geometryMemory == geometryMemory_)
								{
									return geometryVerticesHolder.GetValue();
								}
							}

							// create new holder
							// obtain vertices data
							const auto &verticesCount	= geometryMemory_->GetVerticesCount();
							const auto &verticesData	= geometryMemory_->GetVertices(verticesRangeMemory_->packMode);

							// calculate offset within VerticesRange
							const auto &verticesRangeTotalVerticesCount	= GetTotalVerticesCount(verticesRangeMemory_);
							const auto &verticesRangeTotalDataAmount	= verticesRangeTotalVerticesCount * verticesRangeMemory_->vertexSize;

							// create holder
							const auto &geometryVerticesHolder = MakeStrong<GeometryVerticesHolder>(verticesRangeMemory_, geometryMemory_, verticesCount, verticesRangeTotalVerticesCount);

							geometryVerticesHolder->unsubscriber = geometryMemory_->OnDestruction(std::bind(static_cast<void(GeometryBufferHolder::*)(const Memory<GeometryVerticesHolder>& geometryVerticesHolderMemory_)>(&GeometryBufferHolder::Delete), this, geometryVerticesHolder.GetValue()));

							// insert data to buffer
							InsertToVerticesBuffer(verticesRangeTotalDataAmount, verticesData);

							geometryVerticesHolders.push_back(geometryVerticesHolder);
							
							return geometryVerticesHolder.GetValue();
						}
						inline Memory<IndicesRange> FindOrCreate(const Geometry::IndexPackMode& packMode_)
						{
							auto currentIndicesRange = indicesRange;

							while (currentIndicesRange && currentIndicesRange->packMode != packMode_)
							{
								currentIndicesRange = currentIndicesRange->next;
							}

							if (!currentIndicesRange)
							{
								currentIndicesRange = indicesRange = MakeStrong<IndicesRange>(packMode_, indicesRange);
							}

							return currentIndicesRange.GetValue();
						}
						inline void Delete(const Memory<GeometryIndicesHolder>& geometryIndicesHolderMemory_)
						{
							const auto &indicesRangeMemory = geometryIndicesHolderMemory_->indicesRangeMemory;

							// calculate offset
							const auto &indicesRangeTotalDataAmount	= GetTotalIndicesSize(indicesRangeMemory);
							const auto &indicesRangeDataOffset		= GetTotalIndicesSizeUntil(indicesRangeMemory) - indicesRangeTotalDataAmount;
							const auto &geometryIndicesDataOffset	= indicesRangeDataOffset + geometryIndicesHolderMemory_->firstIndex * indicesRangeMemory->indexSize;
							const auto &geometryIndicesDataSize		= geometryIndicesHolderMemory_->indicesCount * indicesRangeMemory->indexSize;
							
							// remove from buffer
							RemoveFromIndicesBuffer(geometryIndicesDataOffset, geometryIndicesDataSize);
						}
						inline Memory<GeometryIndicesHolder> FindOrCreate(const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry>& geometryMemory_)
						{
							auto &geometryIndicesHolders = indicesRangeMemory_->geometryIndicesHolders;

							// check if holder already exist
							for (auto &geometryIndicesHolder : geometryIndicesHolders)
							{
								if (geometryIndicesHolder->geometryMemory == geometryMemory_)
								{
									return geometryIndicesHolder.GetValue();
								}
							}

							// create new holder
							// obtain indices data
							const auto &indicesCount	= geometryMemory_->GetIndicesCount();
							const auto &indicesData		= geometryMemory_->GetIndices(indicesRangeMemory_->packMode);

							// calculate offset within IndicesRange
							const auto &indicesRangeTotalIndicesCount	= GetTotalIndicesCount(indicesRangeMemory_);
							const auto &indicesRangeTotalDataAmount		= indicesRangeTotalIndicesCount * indicesRangeMemory_->indexSize;

							// create holder
							const auto &geometryIndicesHolder = MakeStrong<GeometryIndicesHolder>(indicesRangeMemory_, geometryMemory_, indicesCount, indicesRangeTotalIndicesCount);

							geometryIndicesHolder->unsubscriber = geometryMemory_->OnDestruction(std::bind(static_cast<void(GeometryBufferHolder::*)(const Memory<GeometryIndicesHolder>& geometryIndicesHolderMemory_)>(&GeometryBufferHolder::Delete), this, geometryIndicesHolder.GetValue()));

							// insert data to buffer
							InsertToIndicesBuffer(indicesRangeTotalDataAmount, indicesData);

							geometryIndicesHolders.push_back(geometryIndicesHolder);
							
							return geometryIndicesHolder.GetValue();
						}
					public:
						inline void Free(const Memory<GeometryHolder>& geometryHolderMemory_)
						{
							/*auto currentVerticesRange = verticesRange;
							auto currentVerticesRangeMemory = currentVerticesRange.GetValue();

							while (currentVerticesRangeMemory && currentVerticesRangeMemory != geometryHolderMemory_->verticesRangeMemory)
							{
								currentVerticesRangeMemory = currentVerticesRangeMemory->next.GetValue();
							}

							if (!currentVerticesRangeMemory)
							{
								throw Exception();
							}

							auto &geometryHolders = currentVerticesRangeMemory->geometryHolders;

							auto it = std::find_if(geometryHolders.begin(), geometryHolders.end(), [&](const StrongPointer<GeometryHolder>& geometryHolder){
								return geometryHolder.GetValue() == geometryHolderMemory_;
							});

							if (it == geometryHolders.end())
							{
								throw Exception();
							}

							auto &geometryHolder = (*it);

							const auto &geometryHolderVerticesCount			= geometryHolder->verticesCount;
							const auto &geometryHolderVerticesTotalSize		= geometryHolderVerticesCount * currentVerticesRangeMemory->vertexSize;

							// calculate amount of memory within the range and after the subRange
							const auto rangeEndSize = [&]()
							{
								Size s = 0;
								auto nit = std::next(it);

								while (nit != geometryHolders.end())
								{
									s += (*nit)->verticesCount * currentVerticesRangeMemory->vertexSize;

									++nit;
								}

								return s;
							}();
							// calculate amount of memory after range
							const auto &geometryHolderVerticesTotalSize	= GetTotalSize(currentVerticesRangeMemory);
							const auto &totalVerticesSizeUntilRange		= GetTotalSizeUntil(currentVerticesRangeMemory);
							const auto &totalVerticesEndSize			= GetTotalSizeUntil(nullptr) - totalVerticesSizeUntilRange + rangeEndSize;
							const auto geometryHolderVerticesOffset		= totalVerticesSizeUntilRange - totalVerticesEndSize - geometryHolderVerticesTotalSize;

							// context
							const auto &context		= contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

							if (totalVerticesEndSize > 0)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, totalVerticesEndSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, geometryHolderVerticesOffset + geometryHolderVerticesTotalSize, 0, totalVerticesEndSize);

								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, geometryHolderVerticesOffset, totalVerticesEndSize);

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}

							it = geometryHolders.erase(it);

							while (it != geometryHolders.end())
							{
								(*it)->firstVertex -= geometryHolderVerticesCount;

								++it;
							}

							const auto &currentTotalDataSize = GetTotalSizeUntil(nullptr);
							const auto &sizeLimit = glm::max<Size>(verticesBufferCapacity / 8, 128 * 1024);

							// resize buffer if needed
							if (currentTotalDataSize < sizeLimit)
							{
								// prepare temporal buffer
								auto temporalBufferHandle = context->GenBuffer();
								{
									context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
									context->BufferData(GL::Buffer::Type::CopyWrite, currentTotalDataSize, nullptr, GL::Buffer::Usage::Stream);
								}

								// store backup in temporal buffer
								context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
								context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, currentTotalDataSize);

								// resize buffer
								context->BufferData(GL::Buffer::Type::CopyRead, sizeLimit, nullptr, GL::Buffer::Usage::Static);
									
								// restore data from backup in temporal buffer
								context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, currentTotalDataSize);

								verticesBufferCapacity = sizeLimit;

								context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
								context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

								context->DeleteBuffer(temporalBufferHandle);
							}*/
						}
						inline StrongPointer<GeometryHolder> Allocate(const Memory<Geometry>& geometryMemory_, const Geometry::VertexPackMode& verticesPackMode_, const Geometry::IndexPackMode& indicesPackMode_)
						{
							const auto &verticesRangeMemory				= FindOrCreate(verticesPackMode_);
							const auto &geometryVerticesHolderMemory	= FindOrCreate(verticesRangeMemory, geometryMemory_);
							const auto &indicesRangeMemory				= FindOrCreate(indicesPackMode_);
							const auto &geometryIndicesHolderMemory		= FindOrCreate(indicesRangeMemory, geometryMemory_);

							/*auto verticesRange = FindOrCreate(packMode_);
							auto verticesRangeMemory = verticesRange.GetValue();
							auto &geometryHolders = verticesRange->geometryHolders;
							auto it = std::find_if(geometryHolders.begin(), geometryHolders.end(), [&](const StrongPointer<GeometryHolder>& geometryHolders){
								return geometryHolders->geometryMemory == geometryMemory_;
							});

							if (it == geometryHolders.end())
							{
								// obtain buffer size [[begin][end][empty]]
								const auto &previousTotalDataSize	= GetTotalSizeUntil(nullptr);
								const auto &previousBeginDataSize	= GetTotalSizeUntil(verticesRangeMemory);
								const auto &previousEndDataSize		= previousTotalDataSize - previousBeginDataSize;

								// obtain vertices
								const auto &firstVertex		= GetTotalVerticesCount(verticesRangeMemory);
								const auto &verticesCount	= geometryMemory_->GetVerticesCount();
								const auto &verticesData	= geometryMemory_->GetVertices(packMode_);
								const auto &indicesCount	= geometryMemory_->GetIndicesCount();
								const auto &indicesData		= geometryMemory_->GetIndices();

								auto geometryHolder = MakeStrong<GeometryHolder>(verticesRangeMemory, geometryMemory_, verticesCount, firstVertex, 0, 0);

								geometryHolder->unsubscriber = geometryMemory_->OnDestruction(std::bind(&GeometryBufferHolder::Free, this, geometryHolder.GetValue()));

								geometryHolders.push_back(geometryHolder);

								it = std::prev(geometryHolders.end());

								const auto &currentTotalDataSize	= GetTotalSizeUntil(nullptr);

								// context
								const auto &context		= contextHolder->gl_context;
								const auto &contextLock	= WGL::Lock(context, contextHolder->win_deviceContextHandle);

								// resize buffer if needed
								if (currentTotalDataSize > verticesBufferCapacity)
								{
									// prepare temporal buffer
									auto temporalBufferHandle = context->GenBuffer();
									{
										context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
										context->BufferData(GL::Buffer::Type::CopyWrite, verticesBufferCapacity, nullptr, GL::Buffer::Usage::Stream);
									}

									// store backup in temporal buffer
									context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
									context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, 0, 0, verticesBufferCapacity);

									// resize buffer
									auto powerOfTwoSize = static_cast<Size>(glm::pow(2, glm::ceil(glm::log(static_cast<Float64>(currentTotalDataSize)) / glm::log(2.0))));
									auto newBufferSize = glm::max<Size>(powerOfTwoSize * 2, 128 * 1024);

									context->BufferData(GL::Buffer::Type::CopyRead, newBufferSize, nullptr, GL::Buffer::Usage::Static);
									
									// restore data from backup in temporal buffer
									context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, 0, verticesBufferCapacity);

									verticesBufferCapacity = newBufferSize;

									context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
									context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

									context->DeleteBuffer(temporalBufferHandle);
								}
								
								// move data at the end if needed
								if (previousEndDataSize > 0)
								{
									// prepare temporal buffer
									auto temporalBufferHandle = context->GenBuffer();
									{
										context->BindBuffer(GL::Buffer::Type::CopyWrite, temporalBufferHandle);
										context->BufferData(GL::Buffer::Type::CopyWrite, previousEndDataSize, nullptr, GL::Buffer::Usage::Stream);
									}

									// store backup in temporal buffer
									context->BindBuffer(GL::Buffer::Type::CopyRead, gl_verticesBuffer);
									context->CopyBufferSubData(GL::Buffer::Type::CopyRead, GL::Buffer::Type::CopyWrite, previousBeginDataSize, 0, previousEndDataSize);

									// restore data from backup in temporal buffer
									context->CopyBufferSubData(GL::Buffer::Type::CopyWrite, GL::Buffer::Type::CopyRead, 0, previousBeginDataSize + verticesData.size(), previousEndDataSize);

									context->BindBuffer(GL::Buffer::Type::CopyRead, nullptr);
									context->BindBuffer(GL::Buffer::Type::CopyWrite, nullptr);

									context->DeleteBuffer(temporalBufferHandle);
								}

								// insert data
								context->BindBuffer(GL::Buffer::Type::Array, gl_verticesBuffer);
								context->BufferSubData(GL::Buffer::Type::Array, previousBeginDataSize, verticesData.size(), verticesData.data());
							}

							auto geometryHolder = *it;

							return geometryHolder.GetValue();*/

							return MakeStrong<GeometryHolder>(geometryVerticesHolderMemory, geometryIndicesHolderMemory);
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
						// using ModelsTable = Map<Memory<ModelCache>, ModelNode>;
						// using MaterialsTable = Map<Memory<MaterialCache>, MaterialNode>;
					protected:
						const Memory<Forward> methodMemory;
						const Memory<Scene> sceneMemory;
						Scene::Version sceneVersion;
						// MaterialsTable materialsTable;
					public:
						inline SceneCache(const StrongPointer<SceneCache>& this_, const Memory<Forward>& methodMemory_, const Memory<Scene>& sceneMemory_);
					protected:
						// inline MaterialNode& FindOrCreate(const Memory<MaterialCache>& materialCacheMemory_);
						// inline ModelNode& FindOrCreate(MaterialNode& materialNode_, const Memory<ModelCache>& modelCacheMemory_);
					protected:
						inline void ForceUpdateCaches();
						inline void UpdateCaches();
					protected:
						inline void PresentOn(const Memory<APIs::Windows::View>& view_, const StrongPointer<Camera>& camera_);
					public:
						inline StrongPointer<Output> Render(const StrongPointer<Camera>& camera_);
					};
#pragma endregion
/*#pragma region Forward::MaterialCache
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
#pragma endregion*/
/*#pragma region Forward::AttributesCache
					class Forward::AttributesCache
					{
					protected:
						inline GL::VertexArray::Handle ObtainVerticesArrayHandle() const
						{
							const auto &methodMemory	= materialCacheMemory->methodMemory;
							const auto &context			= methodMemory->contextHolder->gl_context;
							const auto &bufferHandle	= context->GenVertexArray();

							return bufferHandle;
						}
					protected:
						const Memory<MaterialCache>			materialCacheMemory;
						const GL::VertexArray::Handle		gl_verticesArrayHandle;
					public:
						inline AttributesCache(const Memory<MaterialCache>& materialCacheMemory_, const Vector<GL::Program::Attribute>& attributes_):
							materialCacheMemory(materialCacheMemory_),
							gl_verticesArrayHandle(ObtainVerticesArrayHandle())
						{
							const auto &methodMemory	= materialCacheMemory->methodMemory;
							const auto &context			= methodMemory->contextHolder->gl_context;

							context->BindBuffer(GL::Buffer::Type::Array, methodMemory->contextHolder->gl_verticesBuffer);

							for (auto &attribute : attributes_)
							{
								if (auto &location = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, attribute.GetName()))
								{
									context->VertexAttributePointer(location, attribute.GetSize(), attribute.GetType(), false, attribute.GetStride(), attribute.GetOffset());
									context->EnableVertexAttributeArray(location);
								}
							}
						}
						inline ~AttributesCache()
						{
							const auto &methodMemory	= materialCacheMemory->methodMemory;
							const auto &context			= methodMemory->contextHolder->gl_context;

							context->BindVertexArray(nullptr);
							context->DeleteVertexArray(gl_verticesArrayHandle);
						}
					};
#pragma endregion*/

/*#pragma region Forward::ModelCache
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
#pragma endregion*/
/*#pragma region Forward::SceneCache::MaterialNode
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
#pragma endregion*/
/*#pragma region Forward::SceneCache::ModelNode
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
						Vector<Vector<Threading::Event>> events;
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
#pragma endregion*/

#pragma region Forward
					Forward::Forward(const StrongPointer<Forward>& this_):
						Method(this_)
					{
					}
					Forward::~Forward()
					{
						// const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						// const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();
						// 
						// GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

						/*sceneCaches.clear();
						modelCaches.clear();
						materialCaches.clear();*/

						// GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);
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
					/*Memory<Forward::MaterialCache> Forward::FindOrAdd(const Memory<Material>& materialMemory_)
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
					}*/
					void Forward::Remove(const Memory<Material>& materialMemory_)
					{
						/*const auto &it = materialCaches.find(materialMemory_);

						if (it == materialCaches.end())
						{
							throw Exception();
						}

						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();
						
						GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

						materialCaches.erase(it);

						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);*/
					}
					void Forward::Remove(const Memory<Model>& modelMemory_)
					{
						/*const auto &it = modelCaches.find(modelMemory_);

						if (it == modelCaches.end())
						{
							throw Exception();
						}

						const auto &previousDeviceContextHandle = GL::OSs::Windows::GetCurrentDeviceContextHandle();
						const auto &previousRenderContextHandle = GL::OSs::Windows::GetCurrentHandle();

						GL::OSs::Windows::MakeCurrent(contextHolder->win_deviceContextHandle, contextHolder->gl_context->GetHandle());

						modelCaches.erase(it);

						GL::OSs::Windows::MakeCurrent(previousDeviceContextHandle, previousRenderContextHandle);*/
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
					}*/

					void Forward::SceneCache::ForceUpdateCaches()
					{
						const auto &contextHolder		= methodMemory->contextHolder;
						const auto &deviceContextHandle	= contextHolder->win_deviceContextHandle;
						const auto &renderContext		= contextHolder->gl_context;

						WGL::Lock contextLock(renderContext, deviceContextHandle);

						auto &objects = sceneMemory->objects;

						for (auto &object : objects)
						{
							auto model = object->GetModel();
							auto geometry = model->GetGeometry();

							methodMemory->geometryBufferHolder->Allocate(geometry.GetValue(), model->GetVerticesPackMode(), model->GetIndicesPackMode());
						}

						/*materialsTable.clear();

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
						}*/
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

						WGL::Lock contextLock(renderContext, deviceContextHandle);
						
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

						/*if (useMultithreading)
						{
							auto &taskManagers = methodMemory->taskManagers;

							Size lastUsedTaskManagerIndex = 0;

							auto getTaskManagerIndex = [&]()
							{
								auto i = lastUsedTaskManagerIndex;

								++lastUsedTaskManagerIndex;

								lastUsedTaskManagerIndex = lastUsedTaskManagerIndex % taskManagers.size();

								return i;
							};

							for (auto &materialIt : materialsTable)
							{
								const auto	&materialCacheMemory	= materialIt.first;
								auto		&materialNode			= materialIt.second;
								auto		&modelsTable			= materialNode.modelsTable;

								for (auto &modelIt : modelsTable)
								{
									auto		&modelNode				= modelIt.second;
									auto		&objectsTable			= modelNode.objectsTable;
									auto		&objectsData			= modelNode.objectsUniformBufferData;
									auto		&events					= modelNode.events;

									const Size	maxObjectsCountPerDrawCall	= materialCacheMemory->maxObjectsCount;
									const Size	drawCallsCount				= (objectsTable.size() + maxObjectsCountPerDrawCall - 1) / maxObjectsCountPerDrawCall;

									events.resize(drawCallsCount);

									for (const auto &drawCallIndex : Range(drawCallsCount))
									{
										const Size firstDrawCallIndex		= drawCallIndex * maxObjectsCountPerDrawCall;
										const Size lastDrawCallIndex		= glm::min((drawCallIndex + 1) * maxObjectsCountPerDrawCall, objectsData.size());
										const Size drawCallInstancesCount	= lastDrawCallIndex - firstDrawCallIndex;

										auto &drawCallEvents						= events[drawCallIndex];
										const Size minAverageObjectsCountPerTask	= 128;
										const Size tasksCount						= glm::min(taskManagers.size(), (drawCallInstancesCount + minAverageObjectsCountPerTask - 1) / minAverageObjectsCountPerTask);

										// std::cout << "tasksCount: " << tasksCount << std::endl;

										drawCallEvents.resize(tasksCount);

										const Size objectsPerTask			= drawCallInstancesCount / tasksCount;

										for (auto &taskIndex : Range(tasksCount))
										{
											auto taskManagerIndex			= getTaskManagerIndex();
											auto		&taskManager		= taskManagers[taskManagerIndex];
											const Size	firstIndex			= firstDrawCallIndex + taskIndex * objectsPerTask;
											const Size	lastIndex			= taskIndex < static_cast<int>(tasksCount - 1)
												? firstIndex + objectsPerTask
												: lastDrawCallIndex;

											drawCallEvents[taskIndex] = taskManager.Submit(std::bind([](Object** objectsTable_, ObjectUniformBuffer* objectsData_, const Size firtsIndex_, const Size lastIndex_){
												for (Size objectIndex = firtsIndex_; objectIndex < lastIndex_; ++objectIndex)
												{
													const auto &objectMemory	= objectsTable_[objectIndex];
													// const auto &modelMatrix		= objectMemory->GetMMat();
													auto &objectData			= objectsData_[objectIndex];

													// objectData.modelMatrix = Transpose(glm::mat4x3(modelMatrix));
													const auto &position	= objectMemory->GetPosition();
													const auto &angle		= objectMemory->GetAngle();
													const auto &scale		= objectMemory->GetScale();

													const auto &px			= position.x;
													const auto &py			= position.y;
													const auto &pz			= position.z;

													const auto &sx			= scale.x;
													const auto &sy			= scale.y;
													const auto &sz			= scale.z;

													const auto &ax			= Radians(angle.x);
													const auto &ay			= Radians(angle.y);
													const auto &az			= Radians(angle.z);
													const auto &sax			= Sin(ax);
													const auto &cax			= Cos(ax);
													const auto &say			= Sin(ay);
													const auto &cay			= Cos(ay);
													const auto &saz			= Sin(az);
													const auto &caz			= Cos(az);

													objectData.modelMatrix[0][0] = cay * caz + say * sax * -saz * sx;
													objectData.modelMatrix[0][1] = cay * saz + say * sax * caz * sy;
													objectData.modelMatrix[0][2] = say * cax * sz;
													objectData.modelMatrix[0][3] = px;

													objectData.modelMatrix[1][0] = cax * -saz * sx;
													objectData.modelMatrix[1][1] = cax * caz * sy;
													objectData.modelMatrix[1][2] = -sax * sz;
													objectData.modelMatrix[1][3] = py;

													objectData.modelMatrix[2][0] = -say * caz + cay * sax * -saz * sx;
													objectData.modelMatrix[2][1] = -say * saz + cay * sax * caz * sy;
													objectData.modelMatrix[2][2] = cay * cax * sz;
													objectData.modelMatrix[2][3] = pz;


													// objectData.modelMatrix[0][0] = 1.0f;
													// objectData.modelMatrix[0][1] = 0.0f;
													// objectData.modelMatrix[0][2] = 0.0f;
													// objectData.modelMatrix[0][3] = 0.0f;
													// 
													// objectData.modelMatrix[1][0] = 0.0f;
													// objectData.modelMatrix[1][1] = 1.0f;
													// objectData.modelMatrix[1][2] = 0.0f;
													// objectData.modelMatrix[1][3] = 0.0f;
													// 
													// objectData.modelMatrix[2][0] = 0.0f;
													// objectData.modelMatrix[2][1] = 0.0f;
													// objectData.modelMatrix[2][2] = 1.0f;
													// objectData.modelMatrix[2][3] = 0.0f;
												}
											}, objectsTable.data(), objectsData.data(), firstIndex, lastIndex));
										}
									}
								}
							}
						}
						else
						{
							for (auto &materialIt : materialsTable)
							{
								auto		&materialNode			= materialIt.second;
								auto		&modelsTable			= materialNode.modelsTable;

								for (auto &modelIt : modelsTable)
								{
									auto		&modelNode				= modelIt.second;
									auto		&objectsTable			= modelNode.objectsTable;
									auto		&objectsData			= modelNode.objectsUniformBufferData;

									for (Size objectIndex = 0; objectIndex < objectsTable.size(); ++objectIndex)
									{
										const auto &objectMemory	= objectsTable[objectIndex];
										const auto &modelMatrix		= objectMemory->GetMMat();
										auto &objectData			= objectsData[objectIndex];

										objectData.modelMatrix = Transpose(glm::mat4x3(modelMatrix));
									}
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

								// for (auto &objectIndex : Range(objectsTable.size()))
								// {
								// 	const auto &objectMemory	= objectsTable[objectIndex];
								// 	const auto &modelMatrix		= objectMemory->GetMMat();
								// 	auto &objectData			= objectsData[objectIndex];
								// 
								// 	objectData.modelMatrix = Transpose(glm::mat4x3(modelMatrix));
								// }

								const Size maxObjectsCountPerDrawCall	= materialCacheMemory->maxObjectsCount;
								const Size drawCallsCount				= (objectsTable.size() + maxObjectsCountPerDrawCall - 1) / maxObjectsCountPerDrawCall;

								for (const auto &drawCallIndex : Range(drawCallsCount))
								{
									if (useMultithreading)
									{
										auto &drawCallEvents = events[drawCallIndex];

										for (auto &event : drawCallEvents)
										{
											event.Wait();
										}
									}

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
						}*/

						SwapBuffers(deviceContextHandle);
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


