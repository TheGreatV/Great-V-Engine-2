#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Texture
		{
		public:
			enum class Type
			{
				D1					= GL_TEXTURE_1D,
				D2					= GL_TEXTURE_2D,
				D3					= GL_TEXTURE_3D,
				D1Array				= GL_TEXTURE_1D_ARRAY,
				D2Array				= GL_TEXTURE_2D_ARRAY,
				Rectangle			= GL_TEXTURE_RECTANGLE,
				CubeMap				= GL_TEXTURE_CUBE_MAP,
				CubeMapArray		= GL_TEXTURE_CUBE_MAP_ARRAY,
				Buffer				= GL_TEXTURE_BUFFER,
				D2Multisample		= GL_TEXTURE_2D_MULTISAMPLE,
				D2MultisampleArray	= GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
			};
		public:
			class Format
			{
			public:
				enum class Internal: GLint
				{
					// Base internal formats
					DepthComponent		= GL_DEPTH_COMPONENT,
					Stencil				= GL_DEPTH_STENCIL,
					R					= GL_RED,
					RG					= GL_RG,
					RGB					= GL_RGB,
					RGBA				= GL_RGBA,
					// Sized internal formats
					R8					= GL_R8,
					R8SNorm				= GL_R8_SNORM,
					R16					= GL_R16,
					R16SNorm			= GL_R16_SNORM,
					RG8					= GL_RG8,
					RG8SNorm			= GL_RG8_SNORM,
					RG16				= GL_RG16,
					RG16SNorm			= GL_RG16_SNORM,
					R3G3B2				= GL_R3_G3_B2,
					RGB4				= GL_RGB4,
					RGB5				= GL_RGB5,
					RGB8				= GL_RGB8,
					RGB8SNorm			= GL_RGB8_SNORM,
					RGB10				= GL_RGB10,
					RGB12				= GL_RGB12,
					RGB16				= GL_RGB16, // Added manually
					RGB16SNorm			= GL_RGB16_SNORM,
					RGBA2				= GL_RGBA2,
					RGBA4				= GL_RGBA4,
					RGB5A1				= GL_RGB5_A1,
					RGBA8				= GL_RGBA8,
					RGBA8SNorm			= GL_RGBA8_SNORM,
					RGB10A2				= GL_RGB10_A2,
					RGB10A2UI			= GL_RGB10_A2UI,
					RGBA12				= GL_RGBA12,
					RGBA16				= GL_RGBA16,
					SRGB8				= GL_SRGB8,
					SRGB8A8				= GL_SRGB8_ALPHA8,
					R16F				= GL_R16F,
					RG16F				= GL_RG16F,
					RGB16F				= GL_RGB16F,
					RGBA16F				= GL_RGBA16F,
					R32F				= GL_R32F,
					RG32F				= GL_RG32F,
					RGB32F				= GL_RGB32F,
					RGBA32F				= GL_RGBA32F,
					R11FG11FB10F		= GL_R11F_G11F_B10F,
					RGB9E5				= GL_RGB9_E5,
					R8I					= GL_R8I,
					R8UI				= GL_R8UI,
					R16I				= GL_R16I,
					R16UI				= GL_R16UI,
					R32I				= GL_R32I,
					R32UI				= GL_R32UI,
					RG8I				= GL_RG8I,
					RG8UI				= GL_RG8UI,
					RG16I				= GL_RG16I,
					RG16UI				= GL_RG16UI,
					RG32I				= GL_RG32I,
					RG32UI				= GL_RG32UI,
					RGB8I				= GL_RGB8I,
					RGB8UI				= GL_RGB8UI,
					RGB16I				= GL_RGB16I,
					RGB16UI				= GL_RGB16UI,
					RGB32I				= GL_RGB32I,
					RGB32UI				= GL_RGB32UI,
					RGBA8I				= GL_RGBA8I,
					RGBA8UI				= GL_RGBA8UI,
					RGBA16I				= GL_RGBA16I,
					RGBA16UI			= GL_RGBA16UI,
					RGBA32I				= GL_RGBA32I,
					RGBA32UI			= GL_RGBA32UI,
				};
				enum class External: GLenum
				{
					R					= GL_RED,
					RG					= GL_RG,
					RGB					= GL_RGB,
					BGR					= GL_BGR,
					RGBA				= GL_RGBA,
					BGRA				= GL_BGRA,
					RI					= GL_RED_INTEGER,
					RGI					= GL_RG_INTEGER,
					RGBI				= GL_RGB_INTEGER,
					BGRI				= GL_BGR_INTEGER,
					RGBAI				= GL_RGBA_INTEGER,
					BGRAI				= GL_BGRA_INTEGER,
					StencilIndex		= GL_STENCIL_INDEX,
					DepthComponent		= GL_DEPTH_COMPONENT,
					DepthStencil		= GL_DEPTH_STENCIL,
				};
			public:
				inline static Internal GetInternal(const Memory<const Image>& image_)
				{
					if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt8>>>>(image_))
					{
						return Internal::R8;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt8, UInt8, UInt8>>>>(image_))
					{
						return Internal::RGB8;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt8, UInt8, UInt8, UInt8>>>>(image_))
					{
						return Internal::RGBA8;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt16>>>>(image_))
					{
						return Internal::R16;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16, UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt16, UInt16, UInt16>>>>(image_))
					{
						return Internal::RGB16;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16, UInt16, UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt16, UInt16, UInt16, UInt16>>>>(image_))
					{
						return Internal::RGBA16;
					}

					throw NotImplementedException();
				}
				inline static External GetExternal(const Memory<const Image>& image_)
				{
					if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16>>>>(image_)
					) {
						return External::R;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16, UInt16>>>>(image_)
					) {
						return External::RGB;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16, UInt16, UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt8, UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt16, UInt16, UInt16, UInt16>>>>(image_)
					) {
						return External::RGBA;
					}

					throw NotImplementedException();
				};
			};
			class Data
			{
			public:
				enum class Type: GLenum
				{
					UInt8				= GL_UNSIGNED_BYTE,
					SInt8				= GL_BYTE,
					UInt16				= GL_UNSIGNED_SHORT,
					SInt16				= GL_SHORT,
					UInt32				= GL_UNSIGNED_INT,
					SInt32				= GL_INT,
					SFloat32			= GL_FLOAT,
					// TODO:			= GL_UNSIGNED_BYTE_3_3_2,
					// TODO:			= GL_UNSIGNED_BYTE_2_3_3_REV,
					// TODO:			= GL_UNSIGNED_SHORT_5_6_5,
					// TODO:			= GL_UNSIGNED_SHORT_5_6_5_REV,
					// TODO:			= GL_UNSIGNED_SHORT_4_4_4_4,
					// TODO:			= GL_UNSIGNED_SHORT_4_4_4_4_REV,
					// TODO:			= GL_UNSIGNED_SHORT_5_5_5_1,
					// TODO:			= GL_UNSIGNED_SHORT_1_5_5_5_REV,
					// TODO:			= GL_UNSIGNED_INT_8_8_8_8,
					// TODO:			= GL_UNSIGNED_INT_8_8_8_8_REV,
					// TODO:			= GL_UNSIGNED_INT_10_10_10_2,
					// TODO:			= GL_UNSIGNED_INT_2_10_10_10_REV,
				};
			public:
				inline static Type GetType(const Memory<const Image>& image_)
				{
					if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt8, UInt8, UInt8, UInt8>>>>(image_) ||
						dynamic_cast<const Memory<const ImageCubeX<Pixel<UInt8, UInt8, UInt8, UInt8>>>>(image_)
					) {
						return Type::UInt8;
					}
					else if (
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16, UInt16>>>>(image_) ||
						dynamic_cast<const Memory<const Image2DX<Pixel<UInt16, UInt16, UInt16, UInt16>>>>(image_)
					) {
						return Type::UInt16;
					}

					throw Exception();
				};
			};
			class Wrap
			{
			public:
				enum class Direction: GLenum
				{
					S = GL_TEXTURE_WRAP_S,
					T = GL_TEXTURE_WRAP_T,
					R = GL_TEXTURE_WRAP_R,
				};
				enum class Mode: GLint
				{
					ClampToEdge			= GL_CLAMP_TO_EDGE,
					Repeat				= GL_REPEAT,
					MirroredRepeat		= GL_MIRRORED_REPEAT,
					MirrorClampToEdge	= GL_MIRROR_CLAMP_TO_EDGE,
					ClampToBorder		= GL_CLAMP_TO_BORDER,
				};
			};
			class Filter
			{
			public:
				class Magnification
				{
				public:
					enum class Mode
					{
						Nearest = GL_NEAREST,
						Linear	= GL_LINEAR,
					};
				};
				class Minification
				{
				public:
					enum class Mode
					{
						Nearest					= GL_NEAREST,
						Linear					= GL_LINEAR,
						NearestMipmapNearest	= GL_NEAREST_MIPMAP_NEAREST,
						LinearMipmapNearest		= GL_LINEAR_MIPMAP_NEAREST,
						NearestMipmapLinear		= GL_NEAREST_MIPMAP_LINEAR,
						LinearMipmapLinear		= GL_LINEAR_MIPMAP_LINEAR,
					};
				};
			};
		public:
			class Handle
			{
			public:
				using Value = GLuint;
			protected:
				Value value;
			public:
				inline Handle() = default;
				inline explicit Handle(const Value& value_):
					value(value_)
				{}
				inline Handle(const Handle&) = default;
				inline ~Handle() = default;
			public:
				inline Handle& operator = (const Handle&) = default;
			public:
				inline bool operator == (const Handle& source_) const
				{
					return value == source_.value;
				}
				inline bool operator != (const Handle& source_) const
				{
					return value != source_.value;
				}
			public:
				inline explicit operator Value() const
				{
					return value;
				}
				inline explicit operator Memory<Value>()
				{
					return &value;
				}
				inline explicit operator Memory<const Value>() const
				{
					return &value;
				}
			};
		};


		class Core_1_0:
			public virtual Core
		{
		public:
			inline void				ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const;
			inline void				ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const;
			inline void				Clear(const GLbitfield& mask_) const;
			inline void				DrawArrays(const PrimitiveType& primitiveType_, const Size& first_, const Size& count_);
			inline void				DrawElements(const PrimitiveType& primitiveType_, const Size& indicesCount_, const IndexType& indexType_, const Size& offset_) const
			{
				glDrawElements(static_cast<GLenum>(primitiveType_), indicesCount_, static_cast<GLenum>(indexType_), reinterpret_cast<const GLvoid*>(offset_));
				
				CheckForErrors();
			}
			inline void				BindTexture(const Texture::Type& type_, const Null&) const
			{
				glBindTexture(static_cast<GLenum>(type_), 0);

				CheckForErrors();
			}
			inline void				BindTexture(const Texture::Type& type_, const Texture::Handle& handle_) const
			{
				glBindTexture(static_cast<GLenum>(type_), static_cast<Texture::Handle::Value>(handle_));

				CheckForErrors();
			}
			inline Texture::Handle	GenTexture() const
			{
				Texture::Handle handle;

				glGenTextures(1, static_cast<Memory<Texture::Handle::Value>>(handle));

				CheckForErrors();

				return handle;
			}
			inline void				DeleteTexture(const Texture::Handle& handle_) const
			{
				glDeleteTextures(1, static_cast<Memory<const Texture::Handle::Value>>(handle_));

				CheckForErrors();
			}
			inline void				TextureParameter(const Texture::Type& type_, const Texture::Wrap::Direction& wrapDirection_, const Texture::Wrap::Mode& wrapMode_) const
			{
				glTexParameteri(static_cast<GLenum>(type_), static_cast<GLenum>(wrapDirection_), static_cast<GLint>(wrapMode_));

				CheckForErrors();
			}
			inline void				TextureParameter(const Texture::Type& type_, const Texture::Filter::Magnification::Mode& magnificationMode_) const
			{
				glTexParameteri(static_cast<GLenum>(type_), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magnificationMode_));

				CheckForErrors();
			}
			inline void				TextureParameter(const Texture::Type& type_, const Texture::Filter::Minification::Mode& minificationMode_) const
			{
				glTexParameteri(static_cast<GLenum>(type_), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minificationMode_));

				CheckForErrors();
			}
			inline void				TextureImage(const Texture::Type& type_, const Size& level_, const Texture::Format::Internal& internalTextureFormat_, const Size2& size_, const Texture::Format::External& externalTextureFormat_, const Texture::Data::Type& textureDataType_, const Memory<const void>& data_ = nullptr) // TexImage2D
			{
				glTexImage2D(static_cast<GLenum>(type_), level_, static_cast<GLint>(internalTextureFormat_), size_.x, size_.y, 0, static_cast<GLenum>(externalTextureFormat_), static_cast<GLenum>(textureDataType_), data_);

				CheckForErrors();
			}
			inline void				Flush() const;
			inline void				Finish() const;
		};
#pragma region Core_1_0
		void Core_1_0::ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const
		{
			glViewport(x_, y_, width_, height_);

			CheckForErrors();
		}
		void Core_1_0::ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const
		{
			glClearColor(red_, green_, blue_, alpha_);

			CheckForErrors();
		}
		void Core_1_0::Clear(const GLbitfield& mask_) const
		{
			glClear(mask_);

			CheckForErrors();
		}
		void Core_1_0::DrawArrays(const PrimitiveType& primitiveType_, const Size& first_, const Size& count_)
		{
			glDrawArrays(static_cast<GLenum>(primitiveType_), first_, count_);

			CheckForErrors();
		}
		void Core_1_0::Flush() const
		{
			glFlush();

			CheckForErrors();
		}
		void Core_1_0::Finish() const
		{
			glFinish();

			CheckForErrors();
		}
#pragma endregion

		class Context_1_0:
			public virtual Core_1_0
		{
		};
#pragma region Context_1_0
#pragma endregion

	namespace OSs
	{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
		namespace Windows
		{
			class Context_1_0:
				public Context,
				protected OpenGL::Context_1_0
			{
			private:
				inline static Attributes	GetAttributes();
			protected:
				inline static Handle		ObtainHandle(const DeviceContextHandle& deviceContextHandle_, const Handle& parent_, const Attributes& attributes_); // TODO: move to context?
				inline static Handle		MakeCurrentAndReturn(const DeviceContextHandle& deviceContextHandle_, const Handle& handle_);
			protected:
				inline						Context_1_0(const Handle& handle_);
			public:
				inline						Context_1_0(const DeviceContextHandle& deviceContextHandle_);
				inline						~Context_1_0();
			protected:
				inline void					CheckForCurrentContext() const;
				inline void					CheckForCurrentContext(const Handle& handle_) const; // TODO: remove this workaround
			public:
				inline Procedure			GetProcedureAddress(const String& name_) const; // TODO: move to OpenGL::Context?
				inline Procedure			GetProcedureAddress(const String& name_, const Handle& handle_) const; // TODO: remove this workaround
			public: // overridden
				inline void					ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const;
				inline void					ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const;
				inline void					Clear(const GLbitfield& mask_) const;
				inline void					Flush() const;
				inline void					Finish() const;
			};
#pragma region Context_1_0
			Context_1_0::Attributes Context_1_0::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	1,
					WGL_CONTEXT_MINOR_VERSION_ARB,	0,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_1_0::Handle Context_1_0::ObtainHandle(const DeviceContextHandle& deviceContextHandle_, const Handle& parent_, const Attributes& attributes_)
			{
				// obtain process handle
				auto instanceHandle = GetModuleHandleA(NULL);

				// create window class
				const auto temporaryWindowClassName = String("microsoft sucks cocks class");
				{
					WNDCLASSA windowClass;
					{
						memset(&windowClass, 0, sizeof(windowClass));

						windowClass.lpszClassName	= temporaryWindowClassName.c_str();
						windowClass.hInstance		= instanceHandle;
						windowClass.lpfnWndProc		= DefWindowProcA;
						windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

						if (!RegisterClassA(&windowClass))
						{
							throw Exception();
						}
					}
				}

				// create window
				auto windowHandle = CreateWindowA(temporaryWindowClassName.c_str(), "microsoft sucks cocks", NULL, 0, 0, 0, 0, NULL, NULL, instanceHandle, NULL);
				{
					if (!windowHandle)
					{
						throw Exception();
					}
				}

				// obtain device context and set pixel format for it
				auto temporaryDeviceContextHandle = GetDC(windowHandle);
				{
					if (!temporaryDeviceContextHandle)
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

						auto pixelFormat = ChoosePixelFormat(temporaryDeviceContextHandle, &pixelFormatDescriptorInfo);

						if (!pixelFormat)
						{
							throw Exception();
						}

						if (!SetPixelFormat(temporaryDeviceContextHandle, pixelFormat, &pixelFormatDescriptorInfo))
						{
							throw Exception();
						}
					}
				}

				// create temporary OpenGL context to obtain wglCreateContextAttribsARB
				auto temporaryRenderContextHandle = CreateContext(temporaryDeviceContextHandle);
				{
					if (!temporaryRenderContextHandle)
					{
						throw Exception();
					}
				}

				// make temporary OpenGL context current to obtain important shit
				if (!wglMakeCurrent(temporaryDeviceContextHandle, temporaryRenderContextHandle))
				{
					throw Exception();
				}
		
				// obtain wglCreateContextAttribsARB
				auto wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
				{
					if (!wglCreateContextAttribsARB)
					{
						throw Exception();
					}
				}

				// release temporary OpenGL context
				if (!wglMakeCurrent(nullptr, nullptr))
				{
					throw Exception();
				}

				// destroy temporary OpenGL context
				if (!wglDeleteContext(temporaryRenderContextHandle))
				{
					throw Exception();
				}

				// destroy window
				if (!DestroyWindow(windowHandle))
				{
					throw Exception();
				}

				// destroy window class
				if (!UnregisterClassA(temporaryWindowClassName.c_str(), instanceHandle))
				{
					throw Exception();
				}

				// obtain "permanent" OpenGL context
				auto renderContextHandle = wglCreateContextAttribsARB(deviceContextHandle_, nullptr, attributes_.data());

				if (!renderContextHandle)
				{
					throw Exception();
				}

				return renderContextHandle;
			}
			Context_1_0::Handle Context_1_0::MakeCurrentAndReturn(const DeviceContextHandle& deviceContextHandle_, const Handle& handle_)
			{
				// TODO: save last current RC & DC to restore them later

				MakeCurrent(deviceContextHandle_, handle_);

				return handle_;
			}

			Context_1_0::Context_1_0(const Handle& handle_):
				Context(handle_)
			{
			}
			Context_1_0::Context_1_0(const DeviceContextHandle& deviceContextHandle_):
				Context_1_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_1_0::~Context_1_0()
			{
				auto currentHandle = GetCurrentContextHandle();

				if (currentHandle == handle)
				{
					throw Exception();
				}
			}

			void Context_1_0::CheckForCurrentContext() const
			{
#if __GREAT_V_ENGINE_2__DEBUG__
				auto currentHandle = GetCurrentContextHandle();

				if (currentHandle != handle)
				{
					throw Exception();
				}
#endif
			}
			void Context_1_0::CheckForCurrentContext(const Handle& handle_) const
			{
#if __GREAT_V_ENGINE_2__DEBUG__
				auto currentHandle = GetCurrentContextHandle();

				if (currentHandle != handle_)
				{
					throw Exception();
				}
#endif
			}

			Context_1_0::Procedure Context_1_0::GetProcedureAddress(const String& name_) const
			{
				CheckForCurrentContext();

				auto procedure = wglGetProcAddress(name_.c_str());

				if (!procedure)
				{
					throw Exception();
				}

				return procedure;
			}
			Context_1_0::Procedure Context_1_0::GetProcedureAddress(const String& name_, const Handle& handle_) const
			{
				CheckForCurrentContext(handle_);

				auto procedure = wglGetProcAddress(name_.c_str());

				if (!procedure)
				{
					throw Exception();
				}

				return procedure;
			}

			void Context_1_0::ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const
			{
				CheckForCurrentContext();

				OpenGL::Context_1_0::ConfigureViewport(x_, y_, width_, height_);
			}
			void Context_1_0::ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const
			{
				CheckForCurrentContext();

				OpenGL::Context_1_0::ClearColor(red_, green_, blue_, alpha_);
			}
			void Context_1_0::Flush() const
			{
				CheckForCurrentContext();

				OpenGL::Context_1_0::Flush();
			}
			void Context_1_0::Finish() const
			{
				CheckForCurrentContext();

				OpenGL::Context_1_0::Flush();
			}
			void Context_1_0::Clear(const GLbitfield& mask_) const
			{
				CheckForCurrentContext();

				OpenGL::Context_1_0::Clear(mask_);
			}
#pragma endregion
		}
#endif
	}
	}
}


#pragma region
#pragma endregion


