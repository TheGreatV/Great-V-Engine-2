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
						inline void Submit(Threading::Event onComplete_, const Task& task_)
						{
							Lock lock(mutex);

							onComplete_.Reset();

							tasks.push({ task_, onComplete_ });

							wakeUp.Set();
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
						class TextureCache;
						using TextureCaches = Map<Memory<Image>, StrongPointer<TextureCache>>;
					protected:
						const StrongPointer<ContextHolder> contextHolder = MakeStrong<ContextHolder>();
						const StrongPointer<GeometryBufferHolder> geometryBufferHolder = MakeStrong<GeometryBufferHolder>(contextHolder);
						SceneCaches sceneCaches;
						TextureCaches textureCaches;
						MaterialCaches materialCaches;
						ModelCaches modelCaches;
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
						inline Memory<TextureCache> FindOrAdd(const Memory<Image>& imageMemory_);
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
							const Memory<Geometry2::Indexed> geometryMemory;
							const Geometry2::EventDestruction::Unsubscriber unsubscriber;
							Size firstVertex;
						public:
							inline VerticesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry2::Indexed>& geometryMemory_, const Size& firstVertex_);
						};
						class VerticesRange
						{
						protected:
							inline static Size GetVertexSize(const StrongPointer<Geometry2::Vertices::Attributes>& attributes_)
							{
								if (const auto attributes = DynamicCast<Geometry2::Vertices::Attributes::Listed>(attributes_))
								{
									const auto attributesValues = attributes->GetValues();
									const auto firstAttribute = attributesValues[0];

									if (const auto attribute = DynamicCast<Geometry2::Vertices::Attribute::Regular>(firstAttribute))
									{
										const auto stride = attribute->GetStride();

										// TODO: check that all stdires is the same

										return stride;
									}
								}

								throw Exception();
							}
						public:
							const StrongPointer<Geometry2::Vertices::Attributes> attributes;
							const Size vertexSize;
							Buffer gl_verticesBuffer;
							Vector<StrongPointer<VerticesHolder>> verticesHolders;
						public:
							inline VerticesRange(const Memory<ContextHolder>& contextHolder_, const StrongPointer<Geometry2::Vertices::Attributes>& attributes_):
								attributes(attributes_),
								gl_verticesBuffer(contextHolder_, GL::Buffer::Type::Array, 128 * 1024),
								vertexSize(GetVertexSize(attributes_))
							{
							}
						public:
							inline Size GetTotalVerticesCount() const
							{
								Size count = 0;

								for (auto &verticesHolder : verticesHolders)
								{
									count += verticesHolder->geometryMemory->GetVertices()->GetCount();
								}

								return count;
							}
						};
						class IndicesRange;
						class IndicesHolder
						{
						public:
							const Memory<IndicesRange> indicesRangeMemory;
							const Memory<Geometry2::Indexed> geometryMemory;
							const Geometry2::EventDestruction::Unsubscriber unsubscriber;
							Size firstIndex;
						public:
							inline IndicesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry2::Indexed>& geometryMemory_, const Size& firstIndex_);
						};
						class IndicesRange
						{
						protected:
							inline static Size GetIndexSize(const StrongPointer<Geometry2::Indices::Attributes>& attributes_)
							{
								const auto component = attributes_->GetComponent();

								if (const auto regular = DynamicCast<Geometry2::Component::Regular>(component))
								{
									return regular->GetSize();
								}

								throw Exception();
							}
						public:
							const StrongPointer<Geometry2::Indices::Attributes> attributes;
							const Size indexSize;
							Size offset = 0; // in bytes
							Size size = 0;
							Vector<StrongPointer<IndicesHolder>> indicesHolders;
							StrongPointer<IndicesRange> next = StrongPointer<IndicesRange>(nullptr);
						public:
							inline IndicesRange(const StrongPointer<Geometry2::Indices::Attributes>& attributes_, const StrongPointer<IndicesRange>& next_):
								attributes(attributes_),
								indexSize(GetIndexSize(attributes_)),
								next(next_)
							{
							}
						public:
							inline Size GetTotalIndicesCount() const
							{
								Size count = 0;

								for (auto &indicesHolder : indicesHolders)
								{
									count += indicesHolder->geometryMemory->GetIndices()->GetCount();
								}

								return count;
							}
						};
					public:
						class VerticesAttributesComparator
						{
						public:
							inline bool operator () (const StrongPointer<Geometry2::Vertices::Attributes>& a_, const StrongPointer<Geometry2::Vertices::Attributes>& b_)const
							{
								return a_->operator==(b_);
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
						const Size						instancesCount = 64 * 1024;
						const GL::Buffer::Handle		gl_objectsDataBufferHandle;
					public:
						StrongPointer<IndicesRange> indicesRange = StrongPointer<IndicesRange>(nullptr);
						Buffer gl_indicesBuffer;
						std::map<StrongPointer<Geometry2::Vertices::Attributes>, StrongPointer<VerticesRange>, VerticesAttributesComparator> verticesRanges;
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
						/*inline Memory<IndicesRange> FindOrCreate(const Geometry::IndexPackMode& indicesPackMode_)
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
						}*/
						inline Memory<IndicesRange> FindOrCreate(const StrongPointer<Geometry2::Indices::Attributes>& indicesAttributes_)
						{
							auto currentIndicesRangeMemory = indicesRange.GetValue();

							while (currentIndicesRangeMemory && currentIndicesRangeMemory->attributes->operator==(indicesAttributes_))
							{
								currentIndicesRangeMemory = currentIndicesRangeMemory->next.GetValue();
							}

							if (currentIndicesRangeMemory)
							{
								return currentIndicesRangeMemory;
							}

							indicesRange = MakeStrong<IndicesRange>(indicesAttributes_, indicesRange);

							const auto &indicesRangeMemory	= indicesRange.GetValue();

							return indicesRangeMemory;
						}
						inline Memory<IndicesHolder> FindOrCreate(const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry2::Indexed>& geometryMemory_)
						{
							const auto indices			= geometryMemory_->GetIndices();
							const auto indicesMemory	= indices.GetValue();

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
							const auto &indicesData		= indicesMemory->GetData();
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
						inline Memory<IndicesHolder> FindOrCreateIndices(const Memory<Model>& modelMemory_)
						{
							const auto geometry				= modelMemory_->GetGeometry2();
							const auto geometryMemory		= geometry.GetValue();

							const auto indices				= geometryMemory->GetIndices();
							const auto indicesAttributes	= indices->GetAttributes();

							const auto indicesRangeMemory	= FindOrCreate(indicesAttributes);
							const auto indicesHolderMemory	= FindOrCreate(indicesRangeMemory, geometryMemory);

							return indicesHolderMemory;
						}
						inline void Delete(const Memory<IndicesHolder>& indicesHolderMemory_)
						{
							const auto &indicesRangeMemory	= indicesHolderMemory_->indicesRangeMemory;
							const auto &indexSize			= indicesRangeMemory->indexSize;
							const auto &indicesCount		= indicesHolderMemory_->geometryMemory->GetIndices()->GetCount();
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
						inline Memory<VerticesRange> FindOrCreate(const StrongPointer<Geometry2::Vertices::Attributes>& verticesAttributes_)
						{
							const auto &it = verticesRanges.find(verticesAttributes_);

							if (it != verticesRanges.end())
							{
								const auto &verticesRange		= (*it).second;
								const auto &verticesRangeMemory	= verticesRange.GetValue();

								return verticesRangeMemory;
							}

							const auto &context			= contextHolder->gl_context;
							const auto &contextLock		= WGL::Lock(context, contextHolder->win_deviceContextHandle);
							const auto &verticesRange	= MakeStrong<VerticesRange>(contextHolder, verticesAttributes_);

							verticesRanges.insert({ verticesAttributes_, verticesRange });

							const auto &verticesRangeMemory	= verticesRange.GetValue();

							return verticesRangeMemory;
						}
						inline Memory<VerticesHolder> FindOrCreate(const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry2::Indexed>& geometryMemory_)
						{
							const auto vertices			= geometryMemory_->GetVertices();
							const auto verticesMemory	= vertices.GetValue();
							
							auto &verticesHolders		= verticesRangeMemory_->verticesHolders;

							for (const auto &verticesHolder : verticesHolders)
							{
								const auto &verticesHolderMemory = verticesHolder.GetValue();

								if (verticesHolderMemory->geometryMemory->GetVertices().GetValue() == verticesMemory)
								{
									return verticesHolderMemory;
								}
							}

							// prepare data
							const auto &verticesData		= verticesMemory->GetData();
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
						inline Memory<VerticesHolder> FindOrCreateVertices(const Memory<Model>& modelMemory_)
						{
							const auto geometry				= modelMemory_->GetGeometry2();
							const auto geometryMemory		= geometry.GetValue();

							const auto vertices				= geometryMemory->GetVertices();
							const auto verticesAttributes	= vertices->GetAttributes();

							const auto verticesRangeMemory	= FindOrCreate(verticesAttributes);
							const auto verticesHolderMemory	= FindOrCreate(verticesRangeMemory, geometryMemory);

							return verticesHolderMemory;
						}
						inline void Delete(const Memory<VerticesHolder>& verticesHolderMemory_)
						{
							const auto &verticesRangeMemory	= verticesHolderMemory_->verticesRangeMemory;
							const auto &vertexSize			= verticesRangeMemory->vertexSize;
							const auto &verticesCount		= verticesHolderMemory_->geometryMemory->GetVertices()->GetCount();
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
					Forward::GeometryBufferHolder::VerticesHolder::VerticesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<VerticesRange>& verticesRangeMemory_, const Memory<Geometry2::Indexed>& geometryMemory_, const Size& firstVertex_):
						verticesRangeMemory(verticesRangeMemory_),
						geometryMemory(geometryMemory_),
						unsubscriber(geometryMemory_->OnDestruction(std::bind(static_cast<void(GeometryBufferHolder::*)(const Memory<GeometryBufferHolder::VerticesHolder>&)>(&Forward::GeometryBufferHolder::Delete), geometryBufferHolderMemory_, this))),
						firstVertex(firstVertex_)
					{
					}
					Forward::GeometryBufferHolder::IndicesHolder::IndicesHolder(const Memory<GeometryBufferHolder>& geometryBufferHolderMemory_, const Memory<IndicesRange>& indicesRangeMemory_, const Memory<Geometry2::Indexed>& geometryMemory_, const Size& firstIndex_):
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
						class AttributesNode;
						class DrawCallNode;
						class TaskNode
						{
						public:
							const Size firstObjectIndex;
							const Size lastObjectIndex;
							mutable Threading::Event onComputationCompleted;
						public:
							inline TaskNode(const Size& firstObjectIndex_, const Size& lastObjectIndex_):
								firstObjectIndex(firstObjectIndex_),
								lastObjectIndex(lastObjectIndex_)
							{
							}
						};
						class DrawCallNode
						{
						public:
							const Size firstObjectIndex;
							const Size lastObjectIndex;
							mutable Size numberOfVisibleObjects = 0;
							mutable StrongPointer<std::mutex> visibleObjectsCounterMutex = MakeStrong<std::mutex>();
							Vector<TaskNode> taskNodes;
						public:
							inline DrawCallNode(const Size& firstObjectIndex_, const Size& lastObjectIndex_):
								firstObjectIndex(firstObjectIndex_),
								lastObjectIndex(lastObjectIndex_)
							{
							}
						};
						class AttributesNode
						{
						public:
							const Memory<AttributesCache> attributesCacheMemory;
							Vector<Memory<Object>> objectsMemories;
							mutable Vector<ObjectUniformBuffer> objectsData;
							// mutable Vector<Vector<Threading::Event>> events; // [draw call id, task id]
							mutable Vector<DrawCallNode> drawCallNodes;
						public:
							inline AttributesNode(const Memory<AttributesCache>& attributesCacheMemory_):
								attributesCacheMemory(attributesCacheMemory_)
							{
							}
							inline AttributesNode(AttributesNode&& source_):
								attributesCacheMemory(source_.attributesCacheMemory),
								objectsMemories(Move(source_.objectsMemories)),
								objectsData(Move(objectsData))
							{
							}
						public:
							inline void Add(const Memory<Object>& objectMemory_)
							{
								objectsMemories.push_back(objectMemory_);
								// objectsData.resize(objectsMemories.size());
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

							if (const auto &uniformLocation = context->GetUniformLocation(programHandle, "textureAlbedo"))
							{
								context->SetUniform(uniformLocation, 0);
							}
							if (const auto &uniformLocation = context->GetUniformLocation(programHandle, "textureNormals"))
							{
								context->SetUniform(uniformLocation, 1);
							}
							if (const auto &uniformLocation = context->GetUniformLocation(programHandle, "textureRoughness"))
							{
								context->SetUniform(uniformLocation, 2);
							}
							if (const auto &uniformLocation = context->GetUniformLocation(programHandle, "textureMetalness"))
							{
								context->SetUniform(uniformLocation, 3);
							}
							if (const auto &uniformLocation = context->GetUniformLocation(programHandle, "textureOcclusion"))
							{
								context->SetUniform(uniformLocation, 4);
							}

							if (const auto &uniformBlockIndex = context->GetUniformBlockIndex(programHandle, "CameraBuffer"))
							{
								context->UniformBlockBinding(programHandle, uniformBlockIndex, GL::UniformBlock::Binding(0));
							}

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
						const Memory<TextureCache>						textureAlbedoCacheMemory;
						const Memory<TextureCache>						textureNormalsCacheMemory;
						const Memory<TextureCache>						textureRoughnessCacheMemory;
						const Memory<TextureCache>						textureMetalnessCacheMemory;
						const Memory<TextureCache>						textureOcclusionCacheMemory;
					public:
						inline MaterialCache(const Memory<Forward>& methodMemory_, const Memory<Material>& materialMemory_):
							methodMemory(methodMemory_),
							materialMemory(materialMemory_),
							unsubscriber(materialMemory->OnDestruction(std::bind(static_cast<void(Forward::*)(const Memory<Material>&)>(&Forward::Remove), methodMemory, materialMemory))),
							gl_programHandle(ObtainProgramHandle()),
							textureAlbedoCacheMemory(methodMemory->FindOrAdd(ObtainModule()->albedoImage.GetValue())),
							textureNormalsCacheMemory(methodMemory->FindOrAdd(ObtainModule()->normalsImage.GetValue())),
							textureRoughnessCacheMemory(methodMemory->FindOrAdd(ObtainModule()->roughnessImage.GetValue())),
							textureMetalnessCacheMemory(methodMemory->FindOrAdd(ObtainModule()->metalnessImage.GetValue())),
							textureOcclusionCacheMemory(methodMemory->FindOrAdd(ObtainModule()->occlusionImage.GetValue()))
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
							verticesHolderMemory(methodMemory->geometryBufferHolder->FindOrCreateVertices(modelMemory)),
							indicesHolderMemory(methodMemory->geometryBufferHolder->FindOrCreateIndices(modelMemory))
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
							// const auto &verticesPackMode	= modelCacheMemory->modelMemory->GetVerticesPackMode();
							// const auto vertexSize			= modelCacheMemory->verticesHolderMemory->verticesRangeMemory->vertexSize;
							// const auto verticesCount		= modelCacheMemory->modelMemory->GetGeometry2()->GetVerticesCount();
							// const auto &vertexSize			= Geometry::GetVertexSize(verticesPackMode);
							// const auto &verticesCount		= modelCacheMemory->modelMemory->GetGeometry()->GetVerticesCount();

							context->BindBuffer(GL::Buffer::Type::ElementArray, materialCacheMemory->methodMemory->geometryBufferHolder->gl_indicesBuffer.gl_bufferHandle);

							const auto geometry				= modelCacheMemory->modelMemory->GetGeometry2();
							const auto geometryMemory		= geometry.GetValue();

							const auto vertices				= geometryMemory->GetVertices();
							const auto verticesAttributes	= vertices->GetAttributes();

							if (const auto attributes = DynamicCast<Geometry2::Vertices::Attributes::Listed>(verticesAttributes))
							{
								for (const auto &attribute : attributes->GetValues())
								{
									if (const auto regular = DynamicCast<Geometry2::Vertices::Attribute::Regular>(attribute))
									{
										const auto offset	= regular->GetOffset();
										const auto stride	= regular->GetStride();
										const auto type		= regular->GetType();

										if (const auto vector = DynamicCast<Geometry2::Vertices::Attribute::Type::Vector>(type))
										{
											const auto component		= vector->GetComponent();
											const auto componentsCount	= vector->GetComponentsCount();

											if (const auto regularComponent = DynamicCast<Geometry2::Component::Regular>(component))
											{
												using Component = Geometry2::Component::Regular;

												const auto size				= regularComponent->GetSize();
												const auto sign				= regularComponent->GetSign();
												const auto normalization	= regularComponent->GetNormalization();
												const auto conversion		= regularComponent->GetConversion();

												const auto isNormalized		= normalization == Component::Normalization::Normalized;

												if (size == 32 && sign == Component::Sign::Signed && conversion == Component::Conversion::Floating) // SFloat32
												{
													const auto type = GL::Program::Attribute::Type::Float;
													const auto name = String(
														regular->GetName() == "Position"			? "vPos" :
														regular->GetName() == "Tangent"				? "vTan" :
														regular->GetName() == "Bitangent"			? "vBin" :
														regular->GetName() == "Normal"				? "vNor" :
														regular->GetName() == "Texture Coordinates"	? "vTex" :
														// regular->GetName() == "Tangent Space"	? "vTBN" :
														""
													);

													if (name != "")
													{
														context->BindBuffer(GL::Buffer::Type::Array, modelCacheMemory->verticesHolderMemory->verticesRangeMemory->gl_verticesBuffer.gl_bufferHandle);

														if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, name))
														{
															context->VertexAttributePointer(attributeLocation, componentsCount, type, isNormalized, stride, offset);
															context->EnableVertexAttributeArray(attributeLocation);
														}
													}
												}
											}
										}
										else if (const auto matrix = DynamicCast<Geometry2::Vertices::Attribute::Type::Matrix>(type))
										{
											const auto component		= matrix->GetComponent();
											const auto rowsCount		= matrix->GetRowsCount();
											const auto columnsCount		= matrix->GetColumnsCount();
											const auto order			= matrix->GetOrder();

											if (const auto regularComponent = DynamicCast<Geometry2::Component::Regular>(component))
											{
												using Component = Geometry2::Component::Regular;

												const auto size				= regularComponent->GetSize();
												const auto sign				= regularComponent->GetSign();
												const auto normalization	= regularComponent->GetNormalization();
												const auto conversion		= regularComponent->GetConversion();

												const auto isNormalized		= normalization == Component::Normalization::Normalized;

												if (size == 32 && sign == Component::Sign::Signed && conversion == Component::Conversion::Floating) // SFloat32
												{
													const auto type = GL::Program::Attribute::Type::Float;

													if (regular->GetName() == "Tangent Space")
													{
														const auto offset1	= offset + sizeof(float) * 3 * 0;
														const auto offset2	= offset + sizeof(float) * 3 * 1;
														const auto offset3	= offset + sizeof(float) * 3 * 2;

														context->BindBuffer(GL::Buffer::Type::Array, modelCacheMemory->verticesHolderMemory->verticesRangeMemory->gl_verticesBuffer.gl_bufferHandle);

														if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vTBN"))
														{
															const auto column1	= GL::Program::Attribute::Location(static_cast<GL::Program::Attribute::Location::Value>(attributeLocation) + 0);
															const auto column2	= GL::Program::Attribute::Location(static_cast<GL::Program::Attribute::Location::Value>(attributeLocation) + 1);
															const auto column3	= GL::Program::Attribute::Location(static_cast<GL::Program::Attribute::Location::Value>(attributeLocation) + 2);

															context->VertexAttributePointer(column1, 3, type, isNormalized, stride, offset1);
															context->EnableVertexAttributeArray(column1);
															context->VertexAttributePointer(column2, 3, type, isNormalized, stride, offset2);
															context->EnableVertexAttributeArray(column2);
															context->VertexAttributePointer(column3, 3, type, isNormalized, stride, offset3);
															context->EnableVertexAttributeArray(column3);
														}
														else
														{
															if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vTan"))
															{
																context->VertexAttributePointer(attributeLocation, 3, type, isNormalized, stride, offset1);
																context->EnableVertexAttributeArray(attributeLocation);
															}
															if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vBin"))
															{
																context->VertexAttributePointer(attributeLocation, 3, type, isNormalized, stride, offset2);
																context->EnableVertexAttributeArray(attributeLocation);
															}
															if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vNor"))
															{
																context->VertexAttributePointer(attributeLocation, 3, type, isNormalized, stride, offset3);
																context->EnableVertexAttributeArray(attributeLocation);
															}
														}
													}
												}
											}
										}
									}
								}
							}

							/*
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
								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vTan"))
								{
									context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Vec3));
									context->EnableVertexAttributeArray(attributeLocation);
								}
								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vBin"))
								{
									context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Vec3) * 2);
									context->EnableVertexAttributeArray(attributeLocation);
								}
								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vNor"))
								{
									context->VertexAttributePointer(attributeLocation, 3, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Vec3) * 3);
									context->EnableVertexAttributeArray(attributeLocation);
								}
								if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vTex"))
								{
									context->VertexAttributePointer(attributeLocation, 2, GL::Program::Attribute::Type::Float, false, vertexSize, sizeof(Vec3) * 4);
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
							*/

							context->BindBuffer(GL::Buffer::Type::Array, materialCacheMemory->methodMemory->geometryBufferHolder->gl_objectsDataBufferHandle);

							if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vModelMatrix1"))
							{
								context->VertexAttributePointer(attributeLocation, 4, GL::Program::Attribute::Type::Float, false, sizeof(ObjectUniformBuffer), 0);
								context->VertexAttribDivisor(attributeLocation, 1);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vModelMatrix2"))
							{
								context->VertexAttributePointer(attributeLocation, 4, GL::Program::Attribute::Type::Float, false, sizeof(ObjectUniformBuffer), sizeof(Vec4));
								context->VertexAttribDivisor(attributeLocation, 1);
								context->EnableVertexAttributeArray(attributeLocation);
							}
							if (const auto &attributeLocation = context->GetAttributeLocation(materialCacheMemory->gl_programHandle, "vModelMatrix3"))
							{
								context->VertexAttributePointer(attributeLocation, 4, GL::Program::Attribute::Type::Float, false, sizeof(ObjectUniformBuffer), sizeof(Vec4) * 2);
								context->VertexAttribDivisor(attributeLocation, 1);
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
#pragma region Forward::TextureCache
					class Forward::TextureCache
					{
					public:
						inline GL::Texture::Handle ObtainTextureHandle() const
						{
							const auto &context		= methodMemory->contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, methodMemory->contextHolder->win_deviceContextHandle);
							const auto &textureHandle = context->GenTexture();

							return textureHandle;
						}
						inline GL::Texture::Type ObtainTextureType() const
						{
							const auto &context		= methodMemory->contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, methodMemory->contextHolder->win_deviceContextHandle);

							if (auto image2D = dynamic_cast<Memory<Image2D>>(imageMemory))
							{
								const auto &textureType = GL::Texture::Type::D2;

								context->BindTexture(textureType, gl_textureHandle);

								context->TextureParameter(textureType, GL::Texture::Wrap::Direction::S, GL::Texture::Wrap::Mode::Repeat);
								context->TextureParameter(textureType, GL::Texture::Wrap::Direction::T, GL::Texture::Wrap::Mode::Repeat);

								context->TextureParameter(textureType, GL::Texture::Filter::Magnification::Mode::Linear);
								context->TextureParameter(textureType, GL::Texture::Filter::Minification::Mode::Linear);

								// TODO: texture parameters

								const auto &internalTextureFormat	= GL::Texture::Format::GetInternal(image2D);
								const auto &externalTextureFormat	= GL::Texture::Format::GetExternal(image2D);
								const auto &textureDataType			= GL::Texture::Data::GetType(image2D);

								for (auto mipmapIndex : Range(image2D->GetMipmapsCount()))
								{
									const auto &mipmap	= (*image2D)[mipmapIndex];
									const auto &data	= mipmap.GetData();

									context->TextureImage(textureType, mipmapIndex, internalTextureFormat, mipmap.GetSize(), externalTextureFormat, textureDataType, data);
								}

								context->BindTexture(textureType, nullptr);

								return textureType;
							}

							throw NotImplementedException();
						}
					public:
						const Memory<Methods::Forward> methodMemory;
						const Memory<Image> imageMemory;
						const GL::Texture::Handle gl_textureHandle;
						const GL::Texture::Type gl_textureType;
					public:
						inline TextureCache(const Memory<Methods::Forward> methodMemory_, const Memory<Image>& imageMemory_):
							methodMemory(methodMemory_),
							imageMemory(imageMemory_),
							gl_textureHandle(ObtainTextureHandle()),
							gl_textureType(ObtainTextureType())
						{
						}
						inline ~TextureCache()
						{
							const auto &context		= methodMemory->contextHolder->gl_context;
							const auto &contextLock	= WGL::Lock(context, methodMemory->contextHolder->win_deviceContextHandle);

							context->DeleteTexture(gl_textureHandle);
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
					Memory<Forward::TextureCache> Forward::FindOrAdd(const Memory<Image>& imageMemory_)
					{
						const auto it					= textureCaches.find(imageMemory_);

						if (it != textureCaches.end())
						{
							const auto textureCache			= (*it).second;
							const auto textureCacheMemory	= textureCache.GetValue();

							return textureCacheMemory;
						}

						const auto textureCache			= MakeStrong<TextureCache>(this, imageMemory_);

						textureCaches.insert({ imageMemory_, textureCache }); // TODO: add check?
						
						const auto textureCacheMemory	= textureCache.GetValue();

						return textureCacheMemory;
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

						// task manager 
						auto &taskManagers = methodMemory->taskManagers;

						// prepare data
						for (auto &materialNode : materialsNodes.materialsNodes)
						{
							for (auto &attributesNode : materialNode.attributesNodes)
							{
								const auto &objectsMemories	= attributesNode.objectsMemories;
								auto &objectsData			= attributesNode.objectsData;
								auto &drawCallNodes			= attributesNode.drawCallNodes;

								objectsData.resize(objectsMemories.size());

								// prepare draw calls
								const Size maxObjectsCountPerDrawCall	= methodMemory->geometryBufferHolder->instancesCount;
								const Size drawCallsCount				= (objectsMemories.size() + maxObjectsCountPerDrawCall - 1) / maxObjectsCountPerDrawCall;
								const Size objectsCountPerDrawCall		= maxObjectsCountPerDrawCall;

								for (const auto &drawCallIndex : Range(drawCallsCount))
								{
									const Size firstObjectIndexInDrawCall	= drawCallIndex * objectsCountPerDrawCall;
									const Size lastObjectIndexInDrawCall	= static_cast<Size>(drawCallIndex) < (drawCallsCount - 1)
										? firstObjectIndexInDrawCall + objectsCountPerDrawCall
										: objectsMemories.size();
									const Size countOfObjectsInDrawCall		= lastObjectIndexInDrawCall - firstObjectIndexInDrawCall;

									// create draw call node
									drawCallNodes.push_back(DrawCallNode(firstObjectIndexInDrawCall, lastObjectIndexInDrawCall));
									
									auto &drawCallNode = drawCallNodes.back();

									// prepare tasks
									const Size minimalCountOfObjectsPerTask	= 256;
									const Size tasksCount					= glm::min(taskManagers.size(), (countOfObjectsInDrawCall + minimalCountOfObjectsPerTask - 1) / minimalCountOfObjectsPerTask);
									const Size averageCountOfObjectsPerTask	= countOfObjectsInDrawCall / tasksCount;

									for (auto &taskIndex : Range(tasksCount))
									{
										const Size	firstObjectIndexInTask	= firstObjectIndexInDrawCall + taskIndex * averageCountOfObjectsPerTask;
										const Size	lastObjectIndexInTask	= static_cast<Size>(taskIndex) < (tasksCount - 1)
											? firstObjectIndexInTask + averageCountOfObjectsPerTask
											: lastObjectIndexInDrawCall;

										auto &taskNode = TaskNode(firstObjectIndexInTask, lastObjectIndexInTask);

										drawCallNode.taskNodes.push_back(taskNode);
									}
								}
							}
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

						glDisable(GL_CULL_FACE);
						// glEnable(GL_CULL_FACE);
						// glCullFace(GL_BACK);
						// glFrontFace(GL_CCW);

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

							renderContext->BindBufferBase(GL::Buffer::Type::Uniform, GL::UniformBlock::Binding(0), contextHolder->gl_cameraUniformsBuffer);
						}

						// task manager 
						auto &taskManagers = methodMemory->taskManagers;

						Size lastUsedTaskManagerIndex = 0;

						auto getTaskManagerIndex = [&]()
						{
							auto i = lastUsedTaskManagerIndex;

							++lastUsedTaskManagerIndex;
							
							lastUsedTaskManagerIndex = lastUsedTaskManagerIndex % taskManagers.size();
							
							return i;
						};


						// prepare data
						for (const auto &materialNode : materialsNodes.materialsNodes)
						{
							for (const auto &attributesNode : materialNode.attributesNodes)
							{
								const auto &objectsMemories			= attributesNode.objectsMemories;
								auto &objectsData					= attributesNode.objectsData;
								const auto &drawCallNodes			= attributesNode.drawCallNodes;
								
								for (const auto &drawCallNode : drawCallNodes)
								{
									auto &counter	= drawCallNode.numberOfVisibleObjects;
									auto mutex		= drawCallNode.visibleObjectsCounterMutex.GetValue();		
									
									counter = 0;

									for (const auto &taskNode : drawCallNode.taskNodes)
									{
										auto taskManagerIndex	= getTaskManagerIndex();
										auto &taskManager		= taskManagers[taskManagerIndex];
										
										taskManager.Submit(taskNode.onComputationCompleted, std::bind([](Object*const* objectsMemories_, ObjectUniformBuffer* objectsData_, const Size firtsIndex_, const Size lastIndex_, std::mutex* mutex_, Size* counter_)
										{
											for (Size objectIndex = firtsIndex_; objectIndex < lastIndex_; ++objectIndex)
											{
												const auto &objectMemory	= objectsMemories_[objectIndex];
												auto &objectData			= objectsData_[objectIndex];
												auto &modelMatrix			= objectData.modelMatrix;

												// objectData.modelMatrix = Transpose(glm::mat4x3(objectMemory->GetMMat()));
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

												const auto &say_saz		= say * saz;
												const auto &say_caz		= say * caz;
												const auto &cay_caz		= cay * caz;
												const auto &cay_saz		= cay * saz;
												const auto &sax_sx		= sax * sx;
												const auto &sax_sy		= sax * sy;
												const auto &cax_sz		= cax * sz;

												modelMatrix[0][0]		= + (cay_caz) - (say_saz * sax_sx);
												modelMatrix[0][1]		= + (cay_saz) + (say_caz * sax_sy);
												modelMatrix[0][2]		= + (say * cax_sz);
												modelMatrix[0][3]		= + (px);

												modelMatrix[1][0]		= - (cax * saz * sx);
												modelMatrix[1][1]		= + (cax * caz * sy);
												modelMatrix[1][2]		= - (sax * sz);
												modelMatrix[1][3]		= + (py);

												modelMatrix[2][0]		= - (say_caz) - (cay_saz * sax_sx);
												modelMatrix[2][1]		= - (say_saz) + (cay_caz * sax_sy);
												modelMatrix[2][2]		= + (cay * cax_sz);
												modelMatrix[2][3]		= + (pz);
											}
										}, objectsMemories.data(), objectsData.data(), taskNode.firstObjectIndex, taskNode.lastObjectIndex, mutex, &counter));
									}
								}
							}
						}

						renderContext->BindBuffer(GL::Buffer::Type::Array, methodMemory->geometryBufferHolder->gl_objectsDataBufferHandle);

						for (const auto &materialNode : materialsNodes.materialsNodes)
						{
							const auto &materialCacheMemory = materialNode.materialCacheMemory;

							renderContext->UseProgram(materialCacheMemory->gl_programHandle);

							renderContext->ActiveTexture(0);
							renderContext->BindTexture(materialCacheMemory->textureAlbedoCacheMemory->gl_textureType, materialCacheMemory->textureAlbedoCacheMemory->gl_textureHandle);
							renderContext->ActiveTexture(1);
							renderContext->BindTexture(materialCacheMemory->textureNormalsCacheMemory->gl_textureType, materialCacheMemory->textureNormalsCacheMemory->gl_textureHandle);
							renderContext->ActiveTexture(2);
							renderContext->BindTexture(materialCacheMemory->textureRoughnessCacheMemory->gl_textureType, materialCacheMemory->textureRoughnessCacheMemory->gl_textureHandle);
							renderContext->ActiveTexture(3);
							renderContext->BindTexture(materialCacheMemory->textureMetalnessCacheMemory->gl_textureType, materialCacheMemory->textureMetalnessCacheMemory->gl_textureHandle);
							renderContext->ActiveTexture(4);
							renderContext->BindTexture(materialCacheMemory->textureOcclusionCacheMemory->gl_textureType, materialCacheMemory->textureOcclusionCacheMemory->gl_textureHandle);

							if (auto location = renderContext->GetUniformLocation(materialCacheMemory->gl_programHandle, "viewProjectionMatrix"))
							{
								renderContext->SetUniform(location, Perspective(60.0f, aspect, 0.1f, 10000.0f) * camera_->GetVMat());
							}

							for (const auto &attributesNode : materialNode.attributesNodes)
							{
								using Component = Geometry2::Component::Regular;

								const auto &attributesCacheMemory	= attributesNode.attributesCacheMemory;

								renderContext->BindVertexArray(attributesCacheMemory->gl_verticesArrayHandle);
								
								const auto &modelCacheMemory		= attributesCacheMemory->modelCacheMemory;
								const auto &modelMemory				= modelCacheMemory->modelMemory;
								
								// const auto &geometryMemory			= modelMemory->GetGeometry().GetValue();
								const auto geometry					= modelMemory->GetGeometry2();
								const auto indices					= geometry->GetIndices();
								const auto indicesComponent			= DynamicCast<Geometry2::Component::Regular>(indices->GetAttributes()->GetComponent());

								if (!indicesComponent)
								{
									throw Exception(); // TODO
								}

								const auto indexType				= (
									(indicesComponent->GetSign() == Component::Sign::Unsigned) &&
									(indicesComponent->GetNormalization() == Component::Normalization::Unnormalized) &&
									(indicesComponent->GetConversion() == Component::Conversion::Integer)
								)
									? (
										indicesComponent->GetSize() == 32 ? GL::IndexType::UInt32 :
										indicesComponent->GetSize() == 16 ? GL::IndexType::UInt16 :
										indicesComponent->GetSize() == 8 ? GL::IndexType::UInt8 :
										throw Exception()
									)
									: throw Exception();

								auto &objectsData					= attributesNode.objectsData;
								const auto &drawCallNodes			= attributesNode.drawCallNodes;
								
								for (const auto &drawCallNode : drawCallNodes)
								{
									for (const auto &taskNode : drawCallNode.taskNodes)
									{
										taskNode.onComputationCompleted.Wait();
									}

									const Size firstObjectIndex	= drawCallNode.firstObjectIndex;
									const Size objectsCount		= drawCallNode.lastObjectIndex - drawCallNode.firstObjectIndex;

									renderContext->BufferSubData(GL::Buffer::Type::Array, 0, sizeof(ObjectUniformBuffer) * objectsCount, objectsData.data() + firstObjectIndex);

									renderContext->DrawElementsInstancedBaseVertex(
										GL::PrimitiveType::Triangles,
										indices->GetCount(),
										indexType,
										// geometryMemory->GetIndicesCount(),																// TODO: move to cache
										// modelMemory->GetIndicesPackMode() == Geometry::IndexPackMode::UInt32 ? GL::IndexType::UInt32 :	// TODO: move to cache
										// modelMemory->GetIndicesPackMode() == Geometry::IndexPackMode::UInt16 ? GL::IndexType::UInt16 :	// TODO: move to cache
										// GL::IndexType::UInt8,																			// TODO: move to cache
										modelCacheMemory->indicesHolderMemory->indicesRangeMemory->offset + modelCacheMemory->indicesHolderMemory->indicesRangeMemory->indexSize * modelCacheMemory->indicesHolderMemory->firstIndex, // TODO: move to cache
										objectsCount,
										modelCacheMemory->verticesHolderMemory->firstVertex												// TODO: move to cache
									);
								}
							}
							
							renderContext->ActiveTexture(0);
							renderContext->BindTexture(materialCacheMemory->textureAlbedoCacheMemory->gl_textureType, nullptr);
							renderContext->ActiveTexture(1);
							renderContext->BindTexture(materialCacheMemory->textureNormalsCacheMemory->gl_textureType, nullptr);
							renderContext->ActiveTexture(2);
							renderContext->BindTexture(materialCacheMemory->textureRoughnessCacheMemory->gl_textureType, nullptr);
							renderContext->ActiveTexture(3);
							renderContext->BindTexture(materialCacheMemory->textureMetalnessCacheMemory->gl_textureType, nullptr);
							renderContext->ActiveTexture(4);
							renderContext->BindTexture(materialCacheMemory->textureOcclusionCacheMemory->gl_textureType, nullptr);
						}
						
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


