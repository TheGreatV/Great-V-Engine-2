#pragma region Include

#pragma once

#include "Core_1_4.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Buffer
		{
		public:
			enum class Type: GLenum
			{
				Array = GL_ARRAY_BUFFER,
				ElementArray = GL_ELEMENT_ARRAY_BUFFER,
				Uniform = GL_UNIFORM_BUFFER,
			};
			enum class Binding
			{
				Array = GL_ARRAY_BUFFER_BINDING,
				ElementArray = GL_ELEMENT_ARRAY_BUFFER_BINDING,
				Uniform = GL_UNIFORM_BUFFER_BINDING,
			};
			enum class Usage: GLenum
			{
				Static = GL_STATIC_DRAW,
				Dynamic = GL_DYNAMIC_DRAW,
				Stream = GL_STREAM_DRAW,
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
				{
				}
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

		class Core_1_5:
			public virtual Core
		{
		protected:
			const PFNGLGENQUERIESPROC				glGenQueries = nullptr;
			const PFNGLDELETEQUERIESPROC			glDeleteQueries = nullptr;
			const PFNGLISQUERYPROC					glIsQuery = nullptr;
			const PFNGLBEGINQUERYPROC				glBeginQuery = nullptr;
			const PFNGLENDQUERYPROC					glEndQuery = nullptr;
			const PFNGLGETQUERYIVPROC				glGetQueryiv = nullptr;
			const PFNGLGETQUERYOBJECTIVPROC			glGetQueryObjectiv = nullptr;
			const PFNGLGETQUERYOBJECTUIVPROC		glGetQueryObjectuiv = nullptr;
			const PFNGLBINDBUFFERPROC				glBindBuffer = nullptr;
			const PFNGLDELETEBUFFERSPROC			glDeleteBuffers = nullptr;
			const PFNGLGENBUFFERSPROC				glGenBuffers = nullptr;
			const PFNGLISBUFFERPROC					glIsBuffer = nullptr;
			const PFNGLBUFFERDATAPROC				glBufferData = nullptr;
			const PFNGLBUFFERSUBDATAPROC			glBufferSubData = nullptr;
			const PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData = nullptr;
			const PFNGLMAPBUFFERPROC				glMapBuffer = nullptr;
			const PFNGLUNMAPBUFFERPROC				glUnmapBuffer = nullptr;
			const PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParameteriv = nullptr;
			const PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv = nullptr;
		protected:
			inline Core_1_5() = default;
			inline Core_1_5(
				const PFNGLGENQUERIESPROC				glGenQueries_,
				const PFNGLDELETEQUERIESPROC			glDeleteQueries_,
				const PFNGLISQUERYPROC					glIsQuery_,
				const PFNGLBEGINQUERYPROC				glBeginQuery_,
				const PFNGLENDQUERYPROC					glEndQuery_,
				const PFNGLGETQUERYIVPROC				glGetQueryiv_,
				const PFNGLGETQUERYOBJECTIVPROC			glGetQueryObjectiv_,
				const PFNGLGETQUERYOBJECTUIVPROC		glGetQueryObjectuiv_,
				const PFNGLBINDBUFFERPROC				glBindBuffer_,
				const PFNGLDELETEBUFFERSPROC			glDeleteBuffers_,
				const PFNGLGENBUFFERSPROC				glGenBuffers_,
				const PFNGLISBUFFERPROC					glIsBuffer_,
				const PFNGLBUFFERDATAPROC				glBufferData_,
				const PFNGLBUFFERSUBDATAPROC			glBufferSubData_,
				const PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData_,
				const PFNGLMAPBUFFERPROC				glMapBuffer_,
				const PFNGLUNMAPBUFFERPROC				glUnmapBuffer_,
				const PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParameteriv_,
				const PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv_
				);
		public:
			inline Buffer::Handle								GetBufferBinding(const Buffer::Binding& type_) const;
			inline void											BindBuffer(const Buffer::Type& type_, const Null&) const;
			inline void											BindBuffer(const Buffer::Type& type_, const Buffer::Handle& handle_) const;
			inline Buffer::Handle								GenBuffer() const;
			inline void											DeleteBuffer(const Buffer::Handle& handle_) const;
			inline void											BufferData(const Buffer::Type& type_, const GLsizeiptr& size_, const Memory<const void>& data_, const Buffer::Usage& usage_) const;
			template<class Type_> inline void					BufferData(const Buffer::Type& type_, const Vector<Type_>& data_, const Buffer::Usage& usage_) const;
		};
#pragma region Core_1_5
		Core_1_5::Core_1_5(
			const PFNGLGENQUERIESPROC				glGenQueries_,
			const PFNGLDELETEQUERIESPROC			glDeleteQueries_,
			const PFNGLISQUERYPROC					glIsQuery_,
			const PFNGLBEGINQUERYPROC				glBeginQuery_,
			const PFNGLENDQUERYPROC					glEndQuery_,
			const PFNGLGETQUERYIVPROC				glGetQueryiv_,
			const PFNGLGETQUERYOBJECTIVPROC			glGetQueryObjectiv_,
			const PFNGLGETQUERYOBJECTUIVPROC		glGetQueryObjectuiv_,
			const PFNGLBINDBUFFERPROC				glBindBuffer_,
			const PFNGLDELETEBUFFERSPROC			glDeleteBuffers_,
			const PFNGLGENBUFFERSPROC				glGenBuffers_,
			const PFNGLISBUFFERPROC					glIsBuffer_,
			const PFNGLBUFFERDATAPROC				glBufferData_,
			const PFNGLBUFFERSUBDATAPROC			glBufferSubData_,
			const PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData_,
			const PFNGLMAPBUFFERPROC				glMapBuffer_,
			const PFNGLUNMAPBUFFERPROC				glUnmapBuffer_,
			const PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParameteriv_,
			const PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv_
			):
			glGenQueries(glGenQueries_),
			glDeleteQueries(glDeleteQueries_),
			glIsQuery(glIsQuery_),
			glBeginQuery(glBeginQuery_),
			glEndQuery(glEndQuery_),
			glGetQueryiv(glGetQueryiv_),
			glGetQueryObjectiv(glGetQueryObjectiv_),
			glGetQueryObjectuiv(glGetQueryObjectuiv_),
			glBindBuffer(glBindBuffer_),
			glDeleteBuffers(glDeleteBuffers_),
			glGenBuffers(glGenBuffers_),
			glIsBuffer(glIsBuffer_),
			glBufferData(glBufferData_),
			glBufferSubData(glBufferSubData_),
			glGetBufferSubData(glGetBufferSubData_),
			glMapBuffer(glMapBuffer_),
			glUnmapBuffer(glUnmapBuffer_),
			glGetBufferParameteriv(glGetBufferParameteriv_),
			glGetBufferPointerv(glGetBufferPointerv_)
		{
		}

		Buffer::Handle Core_1_5::GetBufferBinding(const Buffer::Binding& binding_) const
		{
			GLint value;

			glGetIntegerv(static_cast<GLenum>(binding_), &value);

			CheckForErrors();

			return Buffer::Handle(value);

		}
		void Core_1_5::BindBuffer(const Buffer::Type& type_, const Null&) const
		{
			glBindBuffer(static_cast<GLenum>(type_), 0);

			CheckForErrors();
		}
		void Core_1_5::BindBuffer(const Buffer::Type& type_, const Buffer::Handle& handle_) const
		{
			glBindBuffer(static_cast<GLenum>(type_), static_cast<Buffer::Handle::Value>(handle_));

			CheckForErrors();
		}
		Buffer::Handle Core_1_5::GenBuffer() const
		{
			Buffer::Handle handle;

			glGenBuffers(1, static_cast<Memory<Buffer::Handle::Value>>(handle));

			CheckForErrors();

			return handle;
		}
		void Core_1_5::DeleteBuffer(const Buffer::Handle& handle_) const
		{
			glDeleteBuffers(1, static_cast<Memory<const Buffer::Handle::Value>>(handle_));

			CheckForErrors();
		}
		void Core_1_5::BufferData(const Buffer::Type& type_, const GLsizeiptr& size_, const Memory<const void>& data_, const Buffer::Usage& usage_) const
		{
			glBufferData(static_cast<GLenum>(type_), size_, data_, static_cast<GLenum>(usage_));

			CheckForErrors();
		}
		template<class Type_> void Core_1_5::BufferData(const Buffer::Type& type_, const Vector<Type_>& data_, const Buffer::Usage& usage_) const
		{
			glBufferData(static_cast<GLenum>(type_), sizeof(Type_)* data_.size(), data_.data(), static_cast<GLenum>(usage_));

			CheckForErrors();
		}
#pragma endregion

		class Context_1_5:
			public Context_1_4,
			public virtual Core_1_5
		{
		};
#pragma region Context_1_5
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
				class Context_1_5:
					public Context_1_4,
					public OpenGL::Context_1_5
				{
				protected:
					inline static Attributes GetAttributes();
				private:
					inline Context_1_5(const Handle& handle_);
				protected:
					inline Context_1_5(const Handle& handle_, const EmptyTag&);
				public:
					inline Context_1_5(const DeviceContextHandle& deviceContextHandle_);
				public:
					inline void									BindBuffer(const Buffer::Type& type_, const Null&) const;
					inline void									BindBuffer(const Buffer::Type& type_, const Buffer::Handle& handle_) const;
					inline Buffer::Handle						GenBuffer() const;
					inline void									DeleteBuffer(const Buffer::Handle& handle_) const;
					inline void									BufferData(const Buffer::Type& type_, const GLsizeiptr& size_, const Memory<const void>& data_, const Buffer::Usage& usage_) const;
					template<class Type_> inline void			BufferData(const Buffer::Type& type_, const Vector<Type_>& data_, const Buffer::Usage& usage_) const;
				};
#pragma region Context_1_5
				Context_1_5::Attributes Context_1_5::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
						WGL_CONTEXT_MINOR_VERSION_ARB, 5,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_1_5::Context_1_5(const Handle& handle_, const EmptyTag&):
					Windows::Context_1_4(handle_, EmptyTag()),
					OpenGL::Context_1_5(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4(),
					Core_1_5()
				{
					}
				Context_1_5::Context_1_5(const Handle& handle_):
					Windows::Context_1_4(handle_, EmptyTag()),
					OpenGL::Context_1_5(),
					Core_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D, handle_)
					),
					Core_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd, handle_)
					),
					Core_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation, handle_)
					),
					Core_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv, handle_)
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_1_5::Context_1_5(const DeviceContextHandle& deviceContextHandle_):
					Context_1_5(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
				{
				}

				void Context_1_5::BindBuffer(const Buffer::Type& type_, const Null&) const
				{
					CheckForCurrentContext();

					OpenGL::Context_1_5::BindBuffer(type_, nullptr);
				}
				void Context_1_5::BindBuffer(const Buffer::Type& type_, const Buffer::Handle& handle_) const
				{
					CheckForCurrentContext();

					OpenGL::Context_1_5::BindBuffer(type_, handle_);
				}
				Buffer::Handle Context_1_5::GenBuffer() const
				{
					CheckForCurrentContext();

					return OpenGL::Context_1_5::GenBuffer();
				}
				void Context_1_5::DeleteBuffer(const Buffer::Handle& handle_) const
				{
					CheckForCurrentContext();

					OpenGL::Context_1_5::DeleteBuffer(handle_);
				}
				void Context_1_5::BufferData(const Buffer::Type& type_, const GLsizeiptr& size_, const Memory<const void>& data_, const Buffer::Usage& usage_) const
				{
					CheckForCurrentContext();

					OpenGL::Context_1_5::BufferData(type_, size_, data_, usage_);
				}
				template<class Type_> void Context_1_5::BufferData(const Buffer::Type& type_, const Vector<Type_>& data_, const Buffer::Usage& usage_) const
				{
					CheckForCurrentContext();

					OpenGL::Context_1_5::BufferData(type_, data_, usage_);
				}
#pragma endregion
			}
#endif
		}
	}
}


#pragma region
#pragma endregion


