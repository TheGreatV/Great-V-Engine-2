#include <iostream>
#include <thread>
#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__

#include <Windows.h>

#endif

#define __GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS__(x) reinterpret_cast<decltype(x)>(GetProcedureAddress(#x))
#define __GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(x, h) reinterpret_cast<decltype(x)>(GetProcedureAddress(#x, h))

#include <gl/gl.h>
#include <gl/glext.h>
#include <gl/wglext.h>


namespace OpenGL
{
	class Error
	{
	public:
		enum class Code: GLenum
		{
			NoError							= GL_NO_ERROR,
				
			InvalidOperation				= GL_INVALID_OPERATION,
			InvalidEnum						= GL_INVALID_ENUM,
			InvalidValue					= GL_INVALID_VALUE,
			StackOverflow					= GL_STACK_OVERFLOW,
			StackUnderflow					= GL_STACK_UNDERFLOW,
			OutOfMemory						= GL_OUT_OF_MEMORY,
			InvalidFramebufferOperation		= GL_INVALID_FRAMEBUFFER_OPERATION,
		};
	public:
		static inline String GetText(const Code& code_);
	protected:
		const Code code;
	public:
		inline Error(const Code& code_);
	public:
		inline Code GetCode() const;
	public:
		inline operator bool() const;
	};
#pragma region Error
	String Error::GetText(const Code& code_)
	{
		switch (code_)
		{
		case Code::NoError:						return "No error.";
		case Code::InvalidOperation:			return "Invalid operation.";
		case Code::InvalidEnum:					return "Invalid enum.";
		case Code::InvalidValue:				return "Invalid value.";
		case Code::StackOverflow:				return "Stack overflow.";
		case Code::StackUnderflow:				return "Stack underflow.";
		case Code::OutOfMemory:					return "Out of memory.";
		case Code::InvalidFramebufferOperation:	return "Invalid framebuffer operation.";
		default: throw Exception("Invalid OpenGL error code: " + ToString(static_cast<Size>(code_)));
		}
	}

	Error::Error(const Code& code_):
		code(code_)
	{
	}

	Error::Code Error::GetCode() const
	{
		return code;
	}

	Error::operator bool() const
	{
		return code == Code::NoError;
	}
#pragma endregion

	enum class PrimitiveType: GLenum
	{
		Triangles = GL_TRIANGLES,
	};

	class Buffer
	{
	public:
		enum class Type: GLenum
		{
			Array				= GL_ARRAY_BUFFER,
			ElementArray		= GL_ELEMENT_ARRAY_BUFFER,
			Uniform				= GL_UNIFORM_BUFFER,
		};
		enum class Usage: GLenum
		{
			Static				= GL_STATIC_DRAW,
			Dynamic				= GL_DYNAMIC_DRAW,
			Stream				= GL_STREAM_DRAW,
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
	class Shader
	{
	public:
		enum class Type: GLenum
		{
			Vertex				= GL_VERTEX_SHADER,
			Geometry			= GL_GEOMETRY_SHADER,
			Fragment			= GL_FRAGMENT_SHADER,
		};
		enum class Parameter: GLenum
		{
			CompilseStatus		= GL_COMPILE_STATUS,
			InfoLogLength		= GL_INFO_LOG_LENGTH,
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
			inline explicit operator Value() const
			{
				return value;
			}
			inline explicit operator Value*()
			{
				return &value;
			}
			inline explicit operator const Value*() const
			{
				return &value;
			}
		};
	};
	class VertexArray
	{
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
			inline explicit operator Value() const
			{
				return value;
			}
			inline explicit operator Value*()
			{
				return &value;
			}
			inline explicit operator const Value*() const
			{
				return &value;
			}
		};
	};
	class Program
	{
	public:
		enum class Parameter: GLenum
		{
			LinkStatus			= GL_LINK_STATUS,
			ValidateStatus		= GL_VALIDATE_STATUS,
			InfoLogLength		= GL_INFO_LOG_LENGTH,
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
			inline explicit operator Value() const
			{
				return value;
			}
			inline explicit operator Value*()
			{
				return &value;
			}
			inline explicit operator const Value*() const
			{
				return &value;
			}
		};
		class Attribute
		{
		public:
			enum class Type: GLenum
			{
				Float	= GL_FLOAT,
			};
		public:
			class Location
			{
			public:
				using Value = GLint;
			protected:
				Value value;
			public:
				inline Location() = default;
				inline explicit Location(const Value& value_):
					value(value_)
				{
				}
				inline Location(const Location&) = default;
				inline ~Location() = default;
			public:
				inline Location& operator = (const Location&) = default;
			public:
				inline operator Value() const
				{
					return value;
				}
				inline operator bool() const
				{
					return value != -1;
				}
			};
		};
	};

	class Interface
	{
	protected:
		inline void				CheckForErrors() const;
	public:
		inline Error::Code		GetErrorCode() const;
	};
	class Interface_1_0:
		public virtual Interface
	{
	public:
		inline void				ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const;
		inline void				ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const;
		inline void				Clear(const GLbitfield& mask_) const;
		inline void				DrawArrays(const PrimitiveType& primitiveType_, const Size& first_, const Size& count_);
		inline void				Flush() const;
		inline void				Finish() const;
	};
	class Interface_1_2:
		public virtual Interface
	{
	protected:
		const PFNGLDRAWRANGEELEMENTSPROC	glDrawRangeElements	 = nullptr;
		const PFNGLTEXIMAGE3DPROC			glTexImage3D		 = nullptr;
		const PFNGLTEXSUBIMAGE3DPROC		glTexSubImage3D		 = nullptr;
		const PFNGLCOPYTEXSUBIMAGE3DPROC	glCopyTexSubImage3D	 = nullptr;
	protected:
		inline Interface_1_2() = default;
		inline Interface_1_2(
			const PFNGLDRAWRANGEELEMENTSPROC&	glDrawRangeElements_,
			const PFNGLTEXIMAGE3DPROC&			glTexImage3D_,
			const PFNGLTEXSUBIMAGE3DPROC&		glTexSubImage3D_,
			const PFNGLCOPYTEXSUBIMAGE3DPROC&	glCopyTexSubImage3D_
		);
	};
	class Interface_1_3:
		public virtual Interface
	{
	protected:
		const PFNGLACTIVETEXTUREPROC			glActiveTexture				= nullptr;
		const PFNGLSAMPLECOVERAGEPROC			glSampleCoverage			= nullptr;
		const PFNGLCOMPRESSEDTEXIMAGE3DPROC		glCompressedTexImage3D		= nullptr;
		const PFNGLCOMPRESSEDTEXIMAGE2DPROC		glCompressedTexImage2D		= nullptr;
		const PFNGLCOMPRESSEDTEXIMAGE1DPROC		glCompressedTexImage1D		= nullptr;
		const PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC	glCompressedTexSubImage3D	= nullptr;
		const PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC	glCompressedTexSubImage2D	= nullptr;
		const PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC	glCompressedTexSubImage1D	= nullptr;
		const PFNGLGETCOMPRESSEDTEXIMAGEPROC	glGetCompressedTexImage		= nullptr;
		const PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture		= nullptr;
		const PFNGLMULTITEXCOORD1DPROC			glMultiTexCoord1d			= nullptr;
		const PFNGLMULTITEXCOORD1DVPROC			glMultiTexCoord1dv			= nullptr;
		const PFNGLMULTITEXCOORD1FPROC			glMultiTexCoord1f			= nullptr;
		const PFNGLMULTITEXCOORD1FVPROC			glMultiTexCoord1fv			= nullptr;
		const PFNGLMULTITEXCOORD1IPROC			glMultiTexCoord1i			= nullptr;
		const PFNGLMULTITEXCOORD1IVPROC			glMultiTexCoord1iv			= nullptr;
		const PFNGLMULTITEXCOORD1SPROC			glMultiTexCoord1s			= nullptr;
		const PFNGLMULTITEXCOORD1SVPROC			glMultiTexCoord1sv			= nullptr;
		const PFNGLMULTITEXCOORD2DPROC			glMultiTexCoord2d			= nullptr;
		const PFNGLMULTITEXCOORD2DVPROC			glMultiTexCoord2dv			= nullptr;
		const PFNGLMULTITEXCOORD2FPROC			glMultiTexCoord2f			= nullptr;
		const PFNGLMULTITEXCOORD2FVPROC			glMultiTexCoord2fv			= nullptr;
		const PFNGLMULTITEXCOORD2IPROC			glMultiTexCoord2i			= nullptr;
		const PFNGLMULTITEXCOORD2IVPROC			glMultiTexCoord2iv			= nullptr;
		const PFNGLMULTITEXCOORD2SPROC			glMultiTexCoord2s			= nullptr;
		const PFNGLMULTITEXCOORD2SVPROC			glMultiTexCoord2sv			= nullptr;
		const PFNGLMULTITEXCOORD3DPROC			glMultiTexCoord3d			= nullptr;
		const PFNGLMULTITEXCOORD3DVPROC			glMultiTexCoord3dv			= nullptr;
		const PFNGLMULTITEXCOORD3FPROC			glMultiTexCoord3f			= nullptr;
		const PFNGLMULTITEXCOORD3FVPROC			glMultiTexCoord3fv			= nullptr;
		const PFNGLMULTITEXCOORD3IPROC			glMultiTexCoord3i			= nullptr;
		const PFNGLMULTITEXCOORD3IVPROC			glMultiTexCoord3iv			= nullptr;
		const PFNGLMULTITEXCOORD3SPROC			glMultiTexCoord3s			= nullptr;
		const PFNGLMULTITEXCOORD3SVPROC			glMultiTexCoord3sv			= nullptr;
		const PFNGLMULTITEXCOORD4DPROC			glMultiTexCoord4d			= nullptr;
		const PFNGLMULTITEXCOORD4DVPROC			glMultiTexCoord4dv			= nullptr;
		const PFNGLMULTITEXCOORD4FPROC			glMultiTexCoord4f			= nullptr;
		const PFNGLMULTITEXCOORD4FVPROC			glMultiTexCoord4fv			= nullptr;
		const PFNGLMULTITEXCOORD4IPROC			glMultiTexCoord4i			= nullptr;
		const PFNGLMULTITEXCOORD4IVPROC			glMultiTexCoord4iv			= nullptr;
		const PFNGLMULTITEXCOORD4SPROC			glMultiTexCoord4s			= nullptr;
		const PFNGLMULTITEXCOORD4SVPROC			glMultiTexCoord4sv			= nullptr;
		const PFNGLLOADTRANSPOSEMATRIXFPROC		glLoadTransposeMatrixf		= nullptr;
		const PFNGLLOADTRANSPOSEMATRIXDPROC		glLoadTransposeMatrixd		= nullptr;
		const PFNGLMULTTRANSPOSEMATRIXFPROC		glMultTransposeMatrixf		= nullptr;
		const PFNGLMULTTRANSPOSEMATRIXDPROC		glMultTransposeMatrixd		= nullptr;
	protected:
		inline Interface_1_3() = default;
		inline Interface_1_3(
			const PFNGLACTIVETEXTUREPROC&			glActiveTexture_,
			const PFNGLSAMPLECOVERAGEPROC&			glSampleCoverage_,
			const PFNGLCOMPRESSEDTEXIMAGE3DPROC&	glCompressedTexImage3D_,
			const PFNGLCOMPRESSEDTEXIMAGE2DPROC&	glCompressedTexImage2D_,
			const PFNGLCOMPRESSEDTEXIMAGE1DPROC&	glCompressedTexImage1D_,
			const PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC&	glCompressedTexSubImage3D_,
			const PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC&	glCompressedTexSubImage2D_,
			const PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC&	glCompressedTexSubImage1D_,
			const PFNGLGETCOMPRESSEDTEXIMAGEPROC&	glGetCompressedTexImage_,
			const PFNGLCLIENTACTIVETEXTUREPROC&		glClientActiveTexture_,
			const PFNGLMULTITEXCOORD1DPROC&			glMultiTexCoord1d_,
			const PFNGLMULTITEXCOORD1DVPROC&		glMultiTexCoord1dv_,
			const PFNGLMULTITEXCOORD1FPROC&			glMultiTexCoord1f_,
			const PFNGLMULTITEXCOORD1FVPROC&		glMultiTexCoord1fv_,
			const PFNGLMULTITEXCOORD1IPROC&			glMultiTexCoord1i_,
			const PFNGLMULTITEXCOORD1IVPROC&		glMultiTexCoord1iv_,
			const PFNGLMULTITEXCOORD1SPROC&			glMultiTexCoord1s_,
			const PFNGLMULTITEXCOORD1SVPROC&		glMultiTexCoord1sv_,
			const PFNGLMULTITEXCOORD2DPROC&			glMultiTexCoord2d_,
			const PFNGLMULTITEXCOORD2DVPROC&		glMultiTexCoord2dv_,
			const PFNGLMULTITEXCOORD2FPROC&			glMultiTexCoord2f_,
			const PFNGLMULTITEXCOORD2FVPROC&		glMultiTexCoord2fv_,
			const PFNGLMULTITEXCOORD2IPROC&			glMultiTexCoord2i_,
			const PFNGLMULTITEXCOORD2IVPROC&		glMultiTexCoord2iv_,
			const PFNGLMULTITEXCOORD2SPROC&			glMultiTexCoord2s_,
			const PFNGLMULTITEXCOORD2SVPROC&		glMultiTexCoord2sv_,
			const PFNGLMULTITEXCOORD3DPROC&			glMultiTexCoord3d_,
			const PFNGLMULTITEXCOORD3DVPROC&		glMultiTexCoord3dv_,
			const PFNGLMULTITEXCOORD3FPROC&			glMultiTexCoord3f_,
			const PFNGLMULTITEXCOORD3FVPROC&		glMultiTexCoord3fv_,
			const PFNGLMULTITEXCOORD3IPROC&			glMultiTexCoord3i_,
			const PFNGLMULTITEXCOORD3IVPROC&		glMultiTexCoord3iv_,
			const PFNGLMULTITEXCOORD3SPROC&			glMultiTexCoord3s_,
			const PFNGLMULTITEXCOORD3SVPROC&		glMultiTexCoord3sv_,
			const PFNGLMULTITEXCOORD4DPROC&			glMultiTexCoord4d_,
			const PFNGLMULTITEXCOORD4DVPROC&		glMultiTexCoord4dv_,
			const PFNGLMULTITEXCOORD4FPROC&			glMultiTexCoord4f_,
			const PFNGLMULTITEXCOORD4FVPROC&		glMultiTexCoord4fv_,
			const PFNGLMULTITEXCOORD4IPROC&			glMultiTexCoord4i_,
			const PFNGLMULTITEXCOORD4IVPROC&		glMultiTexCoord4iv_,
			const PFNGLMULTITEXCOORD4SPROC&			glMultiTexCoord4s_,
			const PFNGLMULTITEXCOORD4SVPROC&		glMultiTexCoord4sv_,
			const PFNGLLOADTRANSPOSEMATRIXFPROC&	glLoadTransposeMatrixf_,
			const PFNGLLOADTRANSPOSEMATRIXDPROC&	glLoadTransposeMatrixd_,
			const PFNGLMULTTRANSPOSEMATRIXFPROC&	glMultTransposeMatrixf_,
			const PFNGLMULTTRANSPOSEMATRIXDPROC&	glMultTransposeMatrixd_
		);
	};
	class Interface_1_4:
		public virtual Interface
	{
	protected:
		const PFNGLBLENDFUNCSEPARATEPROC		glBlendFuncSeparate			= nullptr;
		const PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays			= nullptr;
		const PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements			= nullptr;
		const PFNGLPOINTPARAMETERFPROC			glPointParameterf			= nullptr;
		const PFNGLPOINTPARAMETERFVPROC			glPointParameterfv			= nullptr;
		const PFNGLPOINTPARAMETERIPROC			glPointParameteri			= nullptr;
		const PFNGLPOINTPARAMETERIVPROC			glPointParameteriv			= nullptr;
		const PFNGLFOGCOORDFPROC				glFogCoordf					= nullptr;
		const PFNGLFOGCOORDFVPROC				glFogCoordfv				= nullptr;
		const PFNGLFOGCOORDDPROC				glFogCoordd					= nullptr;
		const PFNGLFOGCOORDDVPROC				glFogCoorddv				= nullptr;
		const PFNGLFOGCOORDPOINTERPROC			glFogCoordPointer			= nullptr;
		const PFNGLSECONDARYCOLOR3BPROC			glSecondaryColor3b			= nullptr;
		const PFNGLSECONDARYCOLOR3BVPROC		glSecondaryColor3bv			= nullptr;
		const PFNGLSECONDARYCOLOR3DPROC			glSecondaryColor3d			= nullptr;
		const PFNGLSECONDARYCOLOR3DVPROC		glSecondaryColor3dv			= nullptr;
		const PFNGLSECONDARYCOLOR3FPROC			glSecondaryColor3f			= nullptr;
		const PFNGLSECONDARYCOLOR3FVPROC		glSecondaryColor3fv			= nullptr;
		const PFNGLSECONDARYCOLOR3IPROC			glSecondaryColor3i			= nullptr;
		const PFNGLSECONDARYCOLOR3IVPROC		glSecondaryColor3iv			= nullptr;
		const PFNGLSECONDARYCOLOR3SPROC			glSecondaryColor3s			= nullptr;
		const PFNGLSECONDARYCOLOR3SVPROC		glSecondaryColor3sv			= nullptr;
		const PFNGLSECONDARYCOLOR3UBPROC		glSecondaryColor3ub			= nullptr;
		const PFNGLSECONDARYCOLOR3UBVPROC		glSecondaryColor3ubv		= nullptr;
		const PFNGLSECONDARYCOLOR3UIPROC		glSecondaryColor3ui			= nullptr;
		const PFNGLSECONDARYCOLOR3UIVPROC		glSecondaryColor3uiv		= nullptr;
		const PFNGLSECONDARYCOLOR3USPROC		glSecondaryColor3us			= nullptr;
		const PFNGLSECONDARYCOLOR3USVPROC		glSecondaryColor3usv		= nullptr;
		const PFNGLSECONDARYCOLORPOINTERPROC	glSecondaryColorPointer		= nullptr;
		const PFNGLWINDOWPOS2DPROC				glWindowPos2d				= nullptr;
		const PFNGLWINDOWPOS2DVPROC				glWindowPos2dv				= nullptr;
		const PFNGLWINDOWPOS2FPROC				glWindowPos2f				= nullptr;
		const PFNGLWINDOWPOS2FVPROC				glWindowPos2fv				= nullptr;
		const PFNGLWINDOWPOS2IPROC				glWindowPos2i				= nullptr;
		const PFNGLWINDOWPOS2IVPROC				glWindowPos2iv				= nullptr;
		const PFNGLWINDOWPOS2SPROC				glWindowPos2s				= nullptr;
		const PFNGLWINDOWPOS2SVPROC				glWindowPos2sv				= nullptr;
		const PFNGLWINDOWPOS3DPROC				glWindowPos3d				= nullptr;
		const PFNGLWINDOWPOS3DVPROC				glWindowPos3dv				= nullptr;
		const PFNGLWINDOWPOS3FPROC				glWindowPos3f				= nullptr;
		const PFNGLWINDOWPOS3FVPROC				glWindowPos3fv				= nullptr;
		const PFNGLWINDOWPOS3IPROC				glWindowPos3i				= nullptr;
		const PFNGLWINDOWPOS3IVPROC				glWindowPos3iv				= nullptr;
		const PFNGLWINDOWPOS3SPROC				glWindowPos3s				= nullptr;
		const PFNGLWINDOWPOS3SVPROC				glWindowPos3sv				= nullptr;
		const PFNGLBLENDCOLORPROC				glBlendColor				= nullptr;
		const PFNGLBLENDEQUATIONPROC			glBlendEquation				= nullptr;
	protected:
		inline Interface_1_4() = default;
		inline Interface_1_4(
			const PFNGLBLENDFUNCSEPARATEPROC		glBlendFuncSeparate_,
			const PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays_,
			const PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements_,
			const PFNGLPOINTPARAMETERFPROC			glPointParameterf_,
			const PFNGLPOINTPARAMETERFVPROC			glPointParameterfv_,
			const PFNGLPOINTPARAMETERIPROC			glPointParameteri_,
			const PFNGLPOINTPARAMETERIVPROC			glPointParameteriv_,
			const PFNGLFOGCOORDFPROC				glFogCoordf_,
			const PFNGLFOGCOORDFVPROC				glFogCoordfv_,
			const PFNGLFOGCOORDDPROC				glFogCoordd_,
			const PFNGLFOGCOORDDVPROC				glFogCoorddv_,
			const PFNGLFOGCOORDPOINTERPROC			glFogCoordPointer_,
			const PFNGLSECONDARYCOLOR3BPROC			glSecondaryColor3b_,
			const PFNGLSECONDARYCOLOR3BVPROC		glSecondaryColor3bv_,
			const PFNGLSECONDARYCOLOR3DPROC			glSecondaryColor3d_,
			const PFNGLSECONDARYCOLOR3DVPROC		glSecondaryColor3dv_,
			const PFNGLSECONDARYCOLOR3FPROC			glSecondaryColor3f_,
			const PFNGLSECONDARYCOLOR3FVPROC		glSecondaryColor3fv_,
			const PFNGLSECONDARYCOLOR3IPROC			glSecondaryColor3i_,
			const PFNGLSECONDARYCOLOR3IVPROC		glSecondaryColor3iv_,
			const PFNGLSECONDARYCOLOR3SPROC			glSecondaryColor3s_,
			const PFNGLSECONDARYCOLOR3SVPROC		glSecondaryColor3sv_,
			const PFNGLSECONDARYCOLOR3UBPROC		glSecondaryColor3ub_,
			const PFNGLSECONDARYCOLOR3UBVPROC		glSecondaryColor3ubv_,
			const PFNGLSECONDARYCOLOR3UIPROC		glSecondaryColor3ui_,
			const PFNGLSECONDARYCOLOR3UIVPROC		glSecondaryColor3uiv_,
			const PFNGLSECONDARYCOLOR3USPROC		glSecondaryColor3us_,
			const PFNGLSECONDARYCOLOR3USVPROC		glSecondaryColor3usv_,
			const PFNGLSECONDARYCOLORPOINTERPROC	glSecondaryColorPointer_,
			const PFNGLWINDOWPOS2DPROC				glWindowPos2d_,
			const PFNGLWINDOWPOS2DVPROC				glWindowPos2dv_,
			const PFNGLWINDOWPOS2FPROC				glWindowPos2f_,
			const PFNGLWINDOWPOS2FVPROC				glWindowPos2fv_,
			const PFNGLWINDOWPOS2IPROC				glWindowPos2i_,
			const PFNGLWINDOWPOS2IVPROC				glWindowPos2iv_,
			const PFNGLWINDOWPOS2SPROC				glWindowPos2s_,
			const PFNGLWINDOWPOS2SVPROC				glWindowPos2sv_,
			const PFNGLWINDOWPOS3DPROC				glWindowPos3d_,
			const PFNGLWINDOWPOS3DVPROC				glWindowPos3dv_,
			const PFNGLWINDOWPOS3FPROC				glWindowPos3f_,
			const PFNGLWINDOWPOS3FVPROC				glWindowPos3fv_,
			const PFNGLWINDOWPOS3IPROC				glWindowPos3i_,
			const PFNGLWINDOWPOS3IVPROC				glWindowPos3iv_,
			const PFNGLWINDOWPOS3SPROC				glWindowPos3s_,
			const PFNGLWINDOWPOS3SVPROC				glWindowPos3sv_,
			const PFNGLBLENDCOLORPROC				glBlendColor_,
			const PFNGLBLENDEQUATIONPROC			glBlendEquation_
		);
	};
	class Interface_1_5:
		public virtual Interface
	{
	protected:
		const PFNGLGENQUERIESPROC				glGenQueries			= nullptr;
		const PFNGLDELETEQUERIESPROC			glDeleteQueries			= nullptr;
		const PFNGLISQUERYPROC					glIsQuery				= nullptr;
		const PFNGLBEGINQUERYPROC				glBeginQuery			= nullptr;
		const PFNGLENDQUERYPROC					glEndQuery				= nullptr;
		const PFNGLGETQUERYIVPROC				glGetQueryiv			= nullptr;
		const PFNGLGETQUERYOBJECTIVPROC			glGetQueryObjectiv		= nullptr;
		const PFNGLGETQUERYOBJECTUIVPROC		glGetQueryObjectuiv		= nullptr;
		const PFNGLBINDBUFFERPROC				glBindBuffer			= nullptr;
		const PFNGLDELETEBUFFERSPROC			glDeleteBuffers			= nullptr;
		const PFNGLGENBUFFERSPROC				glGenBuffers			= nullptr;
		const PFNGLISBUFFERPROC					glIsBuffer				= nullptr;
		const PFNGLBUFFERDATAPROC				glBufferData			= nullptr;
		const PFNGLBUFFERSUBDATAPROC			glBufferSubData			= nullptr;
		const PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData		= nullptr;
		const PFNGLMAPBUFFERPROC				glMapBuffer				= nullptr;
		const PFNGLUNMAPBUFFERPROC				glUnmapBuffer			= nullptr;
		const PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParameteriv	= nullptr;
		const PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv		= nullptr;
	protected:
		inline Interface_1_5() = default;
		inline Interface_1_5(
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
		inline void									BindBuffer(const Buffer::Type& type_, const Null&) const;
		inline void									BindBuffer(const Buffer::Type& type_, const Buffer::Handle& handle_) const;
		inline Buffer::Handle						GenBuffer() const;
		inline void									DeleteBuffer(const Buffer::Handle& handle_) const;
		inline void									BufferData(const Buffer::Type& type_, const GLsizeiptr& size_, const Memory<const void>& data_, const Buffer::Usage& usage_) const;
		template<class Type_> inline void			BufferData(const Buffer::Type& type_, const Vector<Type_>& data_, const Buffer::Usage& usage_) const;
	};
	class Interface_2_0:
		public virtual Interface
	{
	protected:
		const PFNGLBLENDEQUATIONSEPARATEPROC			glBlendEquationSeparate				= nullptr;
		const PFNGLDRAWBUFFERSPROC						glDrawBuffers						= nullptr;
		const PFNGLSTENCILOPSEPARATEPROC				glStencilOpSeparate					= nullptr;
		const PFNGLSTENCILFUNCSEPARATEPROC				glStencilFuncSeparate				= nullptr;
		const PFNGLSTENCILMASKSEPARATEPROC				glStencilMaskSeparate				= nullptr;
		const PFNGLATTACHSHADERPROC						glAttachShader						= nullptr;
		const PFNGLBINDATTRIBLOCATIONPROC				glBindAttribLocation				= nullptr;
		const PFNGLCOMPILESHADERPROC					glCompileShader						= nullptr;
		const PFNGLCREATEPROGRAMPROC					glCreateProgram						= nullptr;
		const PFNGLCREATESHADERPROC						glCreateShader						= nullptr;
		const PFNGLDELETEPROGRAMPROC					glDeleteProgram						= nullptr;
		const PFNGLDELETESHADERPROC						glDeleteShader						= nullptr;
		const PFNGLDETACHSHADERPROC						glDetachShader						= nullptr;
		const PFNGLDISABLEVERTEXATTRIBARRAYPROC			glDisableVertexAttribArray			= nullptr;
		const PFNGLENABLEVERTEXATTRIBARRAYPROC			glEnableVertexAttribArray			= nullptr;
		const PFNGLGETACTIVEATTRIBPROC					glGetActiveAttrib					= nullptr;
		const PFNGLGETACTIVEUNIFORMPROC					glGetActiveUniform					= nullptr;
		const PFNGLGETATTACHEDSHADERSPROC				glGetAttachedShaders				= nullptr;
		const PFNGLGETATTRIBLOCATIONPROC				glGetAttribLocation					= nullptr;
		const PFNGLGETPROGRAMIVPROC						glGetProgramiv						= nullptr;
		const PFNGLGETPROGRAMINFOLOGPROC				glGetProgramInfoLog					= nullptr;
		const PFNGLGETSHADERIVPROC						glGetShaderiv						= nullptr;
		const PFNGLGETSHADERINFOLOGPROC					glGetShaderInfoLog					= nullptr;
		const PFNGLGETSHADERSOURCEPROC					glGetShaderSource					= nullptr;
		const PFNGLGETUNIFORMLOCATIONPROC				glGetUniformLocation				= nullptr;
		const PFNGLGETUNIFORMFVPROC						glGetUniformfv						= nullptr;
		const PFNGLGETUNIFORMIVPROC						glGetUniformiv						= nullptr;
		const PFNGLGETVERTEXATTRIBDVPROC				glGetVertexAttribdv					= nullptr;
		const PFNGLGETVERTEXATTRIBFVPROC				glGetVertexAttribfv					= nullptr;
		const PFNGLGETVERTEXATTRIBIVPROC				glGetVertexAttribiv					= nullptr;
		const PFNGLGETVERTEXATTRIBPOINTERVPROC			glGetVertexAttribPointerv			= nullptr;
		const PFNGLISPROGRAMPROC						glIsProgram							= nullptr;
		const PFNGLISSHADERPROC							glIsShader							= nullptr;
		const PFNGLLINKPROGRAMPROC						glLinkProgram						= nullptr;
		const PFNGLSHADERSOURCEPROC						glShaderSource						= nullptr;
		const PFNGLUSEPROGRAMPROC						glUseProgram						= nullptr;
		const PFNGLUNIFORM1FPROC						glUniform1f							= nullptr;
		const PFNGLUNIFORM2FPROC						glUniform2f							= nullptr;
		const PFNGLUNIFORM3FPROC						glUniform3f							= nullptr;
		const PFNGLUNIFORM4FPROC						glUniform4f							= nullptr;
		const PFNGLUNIFORM1IPROC						glUniform1i							= nullptr;
		const PFNGLUNIFORM2IPROC						glUniform2i							= nullptr;
		const PFNGLUNIFORM3IPROC						glUniform3i							= nullptr;
		const PFNGLUNIFORM4IPROC						glUniform4i							= nullptr;
		const PFNGLUNIFORM1FVPROC						glUniform1fv						= nullptr;
		const PFNGLUNIFORM2FVPROC						glUniform2fv						= nullptr;
		const PFNGLUNIFORM3FVPROC						glUniform3fv						= nullptr;
		const PFNGLUNIFORM4FVPROC						glUniform4fv						= nullptr;
		const PFNGLUNIFORM1IVPROC						glUniform1iv						= nullptr;
		const PFNGLUNIFORM2IVPROC						glUniform2iv						= nullptr;
		const PFNGLUNIFORM3IVPROC						glUniform3iv						= nullptr;
		const PFNGLUNIFORM4IVPROC						glUniform4iv						= nullptr;
		const PFNGLUNIFORMMATRIX2FVPROC					glUniformMatrix2fv					= nullptr;
		const PFNGLUNIFORMMATRIX3FVPROC					glUniformMatrix3fv					= nullptr;
		const PFNGLUNIFORMMATRIX4FVPROC					glUniformMatrix4fv					= nullptr;
		const PFNGLVALIDATEPROGRAMPROC					glValidateProgram					= nullptr;
		const PFNGLVERTEXATTRIB1DPROC					glVertexAttrib1d					= nullptr;
		const PFNGLVERTEXATTRIB1DVPROC					glVertexAttrib1dv					= nullptr;
		const PFNGLVERTEXATTRIB1FPROC					glVertexAttrib1f					= nullptr;
		const PFNGLVERTEXATTRIB1FVPROC					glVertexAttrib1fv					= nullptr;
		const PFNGLVERTEXATTRIB1SPROC					glVertexAttrib1s					= nullptr;
		const PFNGLVERTEXATTRIB1SVPROC					glVertexAttrib1sv					= nullptr;
		const PFNGLVERTEXATTRIB2DPROC					glVertexAttrib2d					= nullptr;
		const PFNGLVERTEXATTRIB2DVPROC					glVertexAttrib2dv					= nullptr;
		const PFNGLVERTEXATTRIB2FPROC					glVertexAttrib2f					= nullptr;
		const PFNGLVERTEXATTRIB2FVPROC					glVertexAttrib2fv					= nullptr;
		const PFNGLVERTEXATTRIB2SPROC					glVertexAttrib2s					= nullptr;
		const PFNGLVERTEXATTRIB2SVPROC					glVertexAttrib2sv					= nullptr;
		const PFNGLVERTEXATTRIB3DPROC					glVertexAttrib3d					= nullptr;
		const PFNGLVERTEXATTRIB3DVPROC					glVertexAttrib3dv					= nullptr;
		const PFNGLVERTEXATTRIB3FPROC					glVertexAttrib3f					= nullptr;
		const PFNGLVERTEXATTRIB3FVPROC					glVertexAttrib3fv					= nullptr;
		const PFNGLVERTEXATTRIB3SPROC					glVertexAttrib3s					= nullptr;
		const PFNGLVERTEXATTRIB3SVPROC					glVertexAttrib3sv					= nullptr;
		const PFNGLVERTEXATTRIB4NBVPROC					glVertexAttrib4Nbv					= nullptr;
		const PFNGLVERTEXATTRIB4NIVPROC					glVertexAttrib4Niv					= nullptr;
		const PFNGLVERTEXATTRIB4NSVPROC					glVertexAttrib4Nsv					= nullptr;
		const PFNGLVERTEXATTRIB4NUBPROC					glVertexAttrib4Nub					= nullptr;
		const PFNGLVERTEXATTRIB4NUBVPROC				glVertexAttrib4Nubv					= nullptr;
		const PFNGLVERTEXATTRIB4NUIVPROC				glVertexAttrib4Nuiv					= nullptr;
		const PFNGLVERTEXATTRIB4NUSVPROC				glVertexAttrib4Nusv					= nullptr;
		const PFNGLVERTEXATTRIB4BVPROC					glVertexAttrib4bv					= nullptr;
		const PFNGLVERTEXATTRIB4DPROC					glVertexAttrib4d					= nullptr;
		const PFNGLVERTEXATTRIB4DVPROC					glVertexAttrib4dv					= nullptr;
		const PFNGLVERTEXATTRIB4FPROC					glVertexAttrib4f					= nullptr;
		const PFNGLVERTEXATTRIB4FVPROC					glVertexAttrib4fv					= nullptr;
		const PFNGLVERTEXATTRIB4IVPROC					glVertexAttrib4iv					= nullptr;
		const PFNGLVERTEXATTRIB4SPROC					glVertexAttrib4s					= nullptr;
		const PFNGLVERTEXATTRIB4SVPROC					glVertexAttrib4sv					= nullptr;
		const PFNGLVERTEXATTRIB4UBVPROC					glVertexAttrib4ubv					= nullptr;
		const PFNGLVERTEXATTRIB4UIVPROC					glVertexAttrib4uiv					= nullptr;
		const PFNGLVERTEXATTRIB4USVPROC					glVertexAttrib4usv					= nullptr;
		const PFNGLVERTEXATTRIBPOINTERPROC				glVertexAttribPointer				= nullptr;
	protected:
		inline Interface_2_0() = default;
		inline Interface_2_0(
			const PFNGLBLENDEQUATIONSEPARATEPROC&			glBlendEquationSeparate_,
			const PFNGLDRAWBUFFERSPROC&						glDrawBuffers_,
			const PFNGLSTENCILOPSEPARATEPROC&				glStencilOpSeparate_,
			const PFNGLSTENCILFUNCSEPARATEPROC&				glStencilFuncSeparate_,
			const PFNGLSTENCILMASKSEPARATEPROC&				glStencilMaskSeparate_,
			const PFNGLATTACHSHADERPROC&					glAttachShader_,
			const PFNGLBINDATTRIBLOCATIONPROC&				glBindAttribLocation_,
			const PFNGLCOMPILESHADERPROC&					glCompileShader_,
			const PFNGLCREATEPROGRAMPROC&					glCreateProgram_,
			const PFNGLCREATESHADERPROC&					glCreateShader_,
			const PFNGLDELETEPROGRAMPROC&					glDeleteProgram_,
			const PFNGLDELETESHADERPROC&					glDeleteShader_,
			const PFNGLDETACHSHADERPROC&					glDetachShader_,
			const PFNGLDISABLEVERTEXATTRIBARRAYPROC&		glDisableVertexAttribArray_,
			const PFNGLENABLEVERTEXATTRIBARRAYPROC&			glEnableVertexAttribArray_,
			const PFNGLGETACTIVEATTRIBPROC&					glGetActiveAttrib_,
			const PFNGLGETACTIVEUNIFORMPROC&				glGetActiveUniform_,
			const PFNGLGETATTACHEDSHADERSPROC&				glGetAttachedShaders_,
			const PFNGLGETATTRIBLOCATIONPROC&				glGetAttribLocation_,
			const PFNGLGETPROGRAMIVPROC&					glGetProgramiv_,
			const PFNGLGETPROGRAMINFOLOGPROC&				glGetProgramInfoLog_,
			const PFNGLGETSHADERIVPROC&						glGetShaderiv_,
			const PFNGLGETSHADERINFOLOGPROC&				glGetShaderInfoLog_,
			const PFNGLGETSHADERSOURCEPROC&					glGetShaderSource_,
			const PFNGLGETUNIFORMLOCATIONPROC&				glGetUniformLocation_,
			const PFNGLGETUNIFORMFVPROC&					glGetUniformfv_,
			const PFNGLGETUNIFORMIVPROC&					glGetUniformiv_,
			const PFNGLGETVERTEXATTRIBDVPROC&				glGetVertexAttribdv_,
			const PFNGLGETVERTEXATTRIBFVPROC&				glGetVertexAttribfv_,
			const PFNGLGETVERTEXATTRIBIVPROC&				glGetVertexAttribiv_,
			const PFNGLGETVERTEXATTRIBPOINTERVPROC&			glGetVertexAttribPointerv_,
			const PFNGLISPROGRAMPROC&						glIsProgram_,
			const PFNGLISSHADERPROC&						glIsShader_,
			const PFNGLLINKPROGRAMPROC&						glLinkProgram_,
			const PFNGLSHADERSOURCEPROC&					glShaderSource_,
			const PFNGLUSEPROGRAMPROC&						glUseProgram_,
			const PFNGLUNIFORM1FPROC&						glUniform1f_,
			const PFNGLUNIFORM2FPROC&						glUniform2f_,
			const PFNGLUNIFORM3FPROC&						glUniform3f_,
			const PFNGLUNIFORM4FPROC&						glUniform4f_,
			const PFNGLUNIFORM1IPROC&						glUniform1i_,
			const PFNGLUNIFORM2IPROC&						glUniform2i_,
			const PFNGLUNIFORM3IPROC&						glUniform3i_,
			const PFNGLUNIFORM4IPROC&						glUniform4i_,
			const PFNGLUNIFORM1FVPROC&						glUniform1fv_,
			const PFNGLUNIFORM2FVPROC&						glUniform2fv_,
			const PFNGLUNIFORM3FVPROC&						glUniform3fv_,
			const PFNGLUNIFORM4FVPROC&						glUniform4fv_,
			const PFNGLUNIFORM1IVPROC&						glUniform1iv_,
			const PFNGLUNIFORM2IVPROC&						glUniform2iv_,
			const PFNGLUNIFORM3IVPROC&						glUniform3iv_,
			const PFNGLUNIFORM4IVPROC&						glUniform4iv_,
			const PFNGLUNIFORMMATRIX2FVPROC&				glUniformMatrix2fv_,
			const PFNGLUNIFORMMATRIX3FVPROC&				glUniformMatrix3fv_,
			const PFNGLUNIFORMMATRIX4FVPROC&				glUniformMatrix4fv_,
			const PFNGLVALIDATEPROGRAMPROC&					glValidateProgram_,
			const PFNGLVERTEXATTRIB1DPROC&					glVertexAttrib1d_,
			const PFNGLVERTEXATTRIB1DVPROC&					glVertexAttrib1dv_,
			const PFNGLVERTEXATTRIB1FPROC&					glVertexAttrib1f_,
			const PFNGLVERTEXATTRIB1FVPROC&					glVertexAttrib1fv_,
			const PFNGLVERTEXATTRIB1SPROC&					glVertexAttrib1s_,
			const PFNGLVERTEXATTRIB1SVPROC&					glVertexAttrib1sv_,
			const PFNGLVERTEXATTRIB2DPROC&					glVertexAttrib2d_,
			const PFNGLVERTEXATTRIB2DVPROC&					glVertexAttrib2dv_,
			const PFNGLVERTEXATTRIB2FPROC&					glVertexAttrib2f_,
			const PFNGLVERTEXATTRIB2FVPROC&					glVertexAttrib2fv_,
			const PFNGLVERTEXATTRIB2SPROC&					glVertexAttrib2s_,
			const PFNGLVERTEXATTRIB2SVPROC&					glVertexAttrib2sv_,
			const PFNGLVERTEXATTRIB3DPROC&					glVertexAttrib3d_,
			const PFNGLVERTEXATTRIB3DVPROC&					glVertexAttrib3dv_,
			const PFNGLVERTEXATTRIB3FPROC&					glVertexAttrib3f_,
			const PFNGLVERTEXATTRIB3FVPROC&					glVertexAttrib3fv_,
			const PFNGLVERTEXATTRIB3SPROC&					glVertexAttrib3s_,
			const PFNGLVERTEXATTRIB3SVPROC&					glVertexAttrib3sv_,
			const PFNGLVERTEXATTRIB4NBVPROC&				glVertexAttrib4Nbv_,
			const PFNGLVERTEXATTRIB4NIVPROC&				glVertexAttrib4Niv_,
			const PFNGLVERTEXATTRIB4NSVPROC&				glVertexAttrib4Nsv_,
			const PFNGLVERTEXATTRIB4NUBPROC&				glVertexAttrib4Nub_,
			const PFNGLVERTEXATTRIB4NUBVPROC&				glVertexAttrib4Nubv_,
			const PFNGLVERTEXATTRIB4NUIVPROC&				glVertexAttrib4Nuiv_,
			const PFNGLVERTEXATTRIB4NUSVPROC&				glVertexAttrib4Nusv_,
			const PFNGLVERTEXATTRIB4BVPROC&					glVertexAttrib4bv_,
			const PFNGLVERTEXATTRIB4DPROC&					glVertexAttrib4d_,
			const PFNGLVERTEXATTRIB4DVPROC&					glVertexAttrib4dv_,
			const PFNGLVERTEXATTRIB4FPROC&					glVertexAttrib4f_,
			const PFNGLVERTEXATTRIB4FVPROC&					glVertexAttrib4fv_,
			const PFNGLVERTEXATTRIB4IVPROC&					glVertexAttrib4iv_,
			const PFNGLVERTEXATTRIB4SPROC&					glVertexAttrib4s_,
			const PFNGLVERTEXATTRIB4SVPROC&					glVertexAttrib4sv_,
			const PFNGLVERTEXATTRIB4UBVPROC&				glVertexAttrib4ubv_,
			const PFNGLVERTEXATTRIB4UIVPROC&				glVertexAttrib4uiv_,
			const PFNGLVERTEXATTRIB4USVPROC&				glVertexAttrib4usv_,
			const PFNGLVERTEXATTRIBPOINTERPROC&				glVertexAttribPointer_
		);
	public:
		inline bool								GetShaderCompileStatus(const Shader::Handle& shaderHandle_)
		{
			GLint result;

			glGetShaderiv(static_cast<GLuint>(shaderHandle_), static_cast<GLenum>(Shader::Parameter::CompilseStatus), &result);

			CheckForErrors();

#if __GREAT_V_ENGINE_2__DEBUG__
			return
				result == GL_TRUE ? true :
				result == GL_FALSE ? false :
				throw Exception("Unexpected \"glGetShaderiv\" + \"GL_COMPILE_STATUS\" result: " + ToString(static_cast<Size>(result)));
#else
			return result == GL_TRUE
				? true
				: false;
#endif
		}
		inline Size								GetShaderInfoLogLength(const Shader::Handle& shaderHandle_)
		{
			GLint result;

			glGetShaderiv(static_cast<GLuint>(shaderHandle_), static_cast<GLenum>(Shader::Parameter::InfoLogLength), &result);

			CheckForErrors();

#if __GREAT_V_ENGINE_2__DEBUG__
			return result >= 0
				? static_cast<Size>(result)
				: throw Exception("Unexpected \"glGetShaderiv\" + \"GL_INFO_LOG_LENGTH\" result: " + ToString(static_cast<Size>(result)));
#else
			return static_cast<Size>(result);
#endif
		}
		inline String							GetShaderInfoLog(const Shader::Handle& shaderHandle_)
		{
			auto length = GetShaderInfoLogLength(shaderHandle_);

			Vector<char> buffer(length);

			glGetShaderInfoLog(static_cast<GLuint>(shaderHandle_), buffer.size(), nullptr, buffer.data());

			CheckForErrors();

			auto text = String(buffer.begin(), buffer.end());

			return Move(text);
		}
		inline bool								GetProgramLinkStatus(const Program::Handle& programHandle_)
		{
			GLint result;

			glGetProgramiv(static_cast<GLuint>(programHandle_), static_cast<GLenum>(Program::Parameter::LinkStatus), &result);

			CheckForErrors();

#if __GREAT_V_ENGINE_2__DEBUG__
			return
				result == GL_TRUE ? true :
				result == GL_FALSE ? false :
				throw Exception("Unexpected \"glGetProgramiv\" + \"GL_LINK_STATUS\" result: " + ToString(static_cast<Size>(result)));
#else
			return result == GL_TRUE
				? true
				: false;
#endif
		}
		inline Size								GetProgramInfoLogLength(const Program::Handle& programHandle_)
		{
			GLint result;

			glGetProgramiv(static_cast<GLuint>(programHandle_), static_cast<GLenum>(Program::Parameter::InfoLogLength), &result);

			CheckForErrors();

#if __GREAT_V_ENGINE_2__DEBUG__
			return result >= 0
				? static_cast<Size>(result)
				: throw Exception("Unexpected \"glGetProgramiv\" + \"GL_INFO_LOG_LENGTH\" result: " + ToString(static_cast<Size>(result)));
#else
			return static_cast<Size>(result);
#endif
		}
		inline String							GetProgramInfoLog(const Program::Handle& programHandle_)
		{
			auto length = GetProgramInfoLogLength(programHandle_);

			Vector<char> buffer(length);

			glGetProgramInfoLog(static_cast<GLuint>(programHandle_), buffer.size(), nullptr, buffer.data());

			CheckForErrors();

			auto text = String(buffer.begin(), buffer.end());

			return Move(text);
		}
		inline void								AttachShader(const Program::Handle& programHandle_, const Shader::Handle& shaderHandle_) const
		{
			glAttachShader(static_cast<Program::Handle::Value>(programHandle_), static_cast<Shader::Handle::Value>(shaderHandle_));

			CheckForErrors();
		}
		inline void								CompileShader(const Shader::Handle& handle_) const
		{
			glCompileShader(static_cast<Shader::Handle::Value>(handle_));

			CheckForErrors();
		}
		inline Program::Handle					CreateProgram() const
		{
			const auto value	= glCreateProgram();

			CheckForErrors();

			const auto handle	= Program::Handle(value);

			return handle;
		}
		inline Shader::Handle					CreateShader(const Shader::Type& type_) const
		{
			const auto value	= glCreateShader(static_cast<GLenum>(type_));

			CheckForErrors();

			const auto handle = Shader::Handle(value);

			return handle;
		}
		inline void								DeleteProgram(const Program::Handle& handle_) const
		{
			glDeleteProgram(static_cast<Program::Handle::Value>(handle_));

			CheckForErrors();
		}
		inline void								DeleteShader(const Shader::Handle& handle_) const
		{
			glDeleteShader(static_cast<Shader::Handle::Value>(handle_));

			CheckForErrors();
		}
		inline void								LinkProgram(const Program::Handle& handle_) const
		{
			glLinkProgram(static_cast<Program::Handle::Value>(handle_));

			CheckForErrors();
		}
		inline void								ShaderSource(const Shader::Handle& handle_, const String& source_) const
		{
			const GLchar*const	data	= source_.c_str();
			const GLint			length	= source_.length();

			glShaderSource(static_cast<Shader::Handle::Value>(handle_), 1, &data, &length);

			CheckForErrors();
		}
		inline void								UseProgram(const Null&) const
		{
			glUseProgram(0);
		}
		inline void								UseProgram(const Program::Handle& handle_) const
		{
			glUseProgram(static_cast<Program::Handle::Value>(handle_));
		}
		inline Program::Attribute::Location		GetAttributeLocation(const Program::Handle& handle_, const String& name_) const
		{
			const auto value = glGetAttribLocation(static_cast<Program::Handle::Value>(handle_), name_.c_str());

			CheckForErrors();

			const auto location = Program::Attribute::Location(value);

			return location;
		}
		inline void								VertexAttributePointer(const Program::Attribute::Location& location_, const Size& componentsCount_, const Program::Attribute::Type& type_, const bool& isNormalized_, const Size& stride_, const Size& offset_) const
		{
			if (!location_)
			{
				throw Exception();
			}

			glVertexAttribPointer(static_cast<GLuint>(static_cast<Program::Attribute::Location::Value>(location_)), componentsCount_, static_cast<GLenum>(type_), isNormalized_ ? GL_TRUE : GL_FALSE, stride_, reinterpret_cast<const void*>(offset_));

			CheckForErrors();
		}
		inline void								EnableVertexAttributeArray(const Program::Attribute::Location& location_) const
		{
			if (!location_)
			{
				throw Exception();
			}

			glEnableVertexAttribArray(static_cast<GLuint>(static_cast<Program::Attribute::Location::Value>(location_)));

			CheckForErrors();
		}
	};
	class Interface_2_1:
		public virtual Interface
	{
	protected:
		const PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv	= nullptr;
		const PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv	= nullptr;
		const PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv	= nullptr;
		const PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv	= nullptr;
		const PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv	= nullptr;
		const PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv	= nullptr;
	protected:
		inline Interface_2_1() = default;
		inline Interface_2_1(
			const PFNGLUNIFORMMATRIX2X3FVPROC& glUniformMatrix2x3fv_,
			const PFNGLUNIFORMMATRIX3X2FVPROC& glUniformMatrix3x2fv_,
			const PFNGLUNIFORMMATRIX2X4FVPROC& glUniformMatrix2x4fv_,
			const PFNGLUNIFORMMATRIX4X2FVPROC& glUniformMatrix4x2fv_,
			const PFNGLUNIFORMMATRIX3X4FVPROC& glUniformMatrix3x4fv_,
			const PFNGLUNIFORMMATRIX4X3FVPROC& glUniformMatrix4x3fv_
		);
	};
	class Interface_3_0:
		public virtual Interface
	{
	protected:
		const PFNGLCOLORMASKIPROC										glColorMaski							= nullptr;
		const PFNGLGETBOOLEANI_VPROC									glGetBooleani_v							= nullptr;
		const PFNGLGETINTEGERI_VPROC									glGetIntegeri_v							= nullptr;
		const PFNGLENABLEIPROC											glEnablei								= nullptr;
		const PFNGLDISABLEIPROC											glDisablei								= nullptr;
		const PFNGLISENABLEDIPROC										glIsEnabledi							= nullptr;
		const PFNGLBEGINTRANSFORMFEEDBACKPROC							glBeginTransformFeedback				= nullptr;
		const PFNGLENDTRANSFORMFEEDBACKPROC								glEndTransformFeedback					= nullptr;
		const PFNGLBINDBUFFERRANGEPROC									glBindBufferRange						= nullptr;
		const PFNGLBINDBUFFERBASEPROC									glBindBufferBase						= nullptr;
		const PFNGLTRANSFORMFEEDBACKVARYINGSPROC						glTransformFeedbackVaryings				= nullptr;
		const PFNGLGETTRANSFORMFEEDBACKVARYINGPROC						glGetTransformFeedbackVarying			= nullptr;
		const PFNGLCLAMPCOLORPROC										glClampColor							= nullptr;
		const PFNGLBEGINCONDITIONALRENDERPROC							glBeginConditionalRender				= nullptr;
		const PFNGLENDCONDITIONALRENDERPROC								glEndConditionalRender					= nullptr;
		const PFNGLVERTEXATTRIBIPOINTERPROC								glVertexAttribIPointer					= nullptr;
		const PFNGLGETVERTEXATTRIBIIVPROC								glGetVertexAttribIiv					= nullptr;
		const PFNGLGETVERTEXATTRIBIUIVPROC								glGetVertexAttribIuiv					= nullptr;
		const PFNGLVERTEXATTRIBI1IPROC									glVertexAttribI1i						= nullptr;
		const PFNGLVERTEXATTRIBI2IPROC									glVertexAttribI2i						= nullptr;
		const PFNGLVERTEXATTRIBI3IPROC									glVertexAttribI3i						= nullptr;
		const PFNGLVERTEXATTRIBI4IPROC									glVertexAttribI4i						= nullptr;
		const PFNGLVERTEXATTRIBI1UIPROC									glVertexAttribI1ui						= nullptr;
		const PFNGLVERTEXATTRIBI2UIPROC									glVertexAttribI2ui						= nullptr;
		const PFNGLVERTEXATTRIBI3UIPROC									glVertexAttribI3ui						= nullptr;
		const PFNGLVERTEXATTRIBI4UIPROC									glVertexAttribI4ui						= nullptr;
		const PFNGLVERTEXATTRIBI1IVPROC									glVertexAttribI1iv						= nullptr;
		const PFNGLVERTEXATTRIBI2IVPROC									glVertexAttribI2iv						= nullptr;
		const PFNGLVERTEXATTRIBI3IVPROC									glVertexAttribI3iv						= nullptr;
		const PFNGLVERTEXATTRIBI4IVPROC									glVertexAttribI4iv						= nullptr;
		const PFNGLVERTEXATTRIBI1UIVPROC								glVertexAttribI1uiv						= nullptr;
		const PFNGLVERTEXATTRIBI2UIVPROC								glVertexAttribI2uiv						= nullptr;
		const PFNGLVERTEXATTRIBI3UIVPROC								glVertexAttribI3uiv						= nullptr;
		const PFNGLVERTEXATTRIBI4UIVPROC								glVertexAttribI4uiv						= nullptr;
		const PFNGLVERTEXATTRIBI4BVPROC									glVertexAttribI4bv						= nullptr;
		const PFNGLVERTEXATTRIBI4SVPROC									glVertexAttribI4sv						= nullptr;
		const PFNGLVERTEXATTRIBI4UBVPROC								glVertexAttribI4ubv						= nullptr;
		const PFNGLVERTEXATTRIBI4USVPROC								glVertexAttribI4usv						= nullptr;
		const PFNGLGETUNIFORMUIVPROC									glGetUniformuiv							= nullptr;
		const PFNGLBINDFRAGDATALOCATIONPROC								glBindFragDataLocation					= nullptr;
		const PFNGLGETFRAGDATALOCATIONPROC								glGetFragDataLocation					= nullptr;
		const PFNGLUNIFORM1UIPROC										glUniform1ui							= nullptr;
		const PFNGLUNIFORM2UIPROC										glUniform2ui							= nullptr;
		const PFNGLUNIFORM3UIPROC										glUniform3ui							= nullptr;
		const PFNGLUNIFORM4UIPROC										glUniform4ui							= nullptr;
		const PFNGLUNIFORM1UIVPROC										glUniform1uiv							= nullptr;
		const PFNGLUNIFORM2UIVPROC										glUniform2uiv							= nullptr;
		const PFNGLUNIFORM3UIVPROC										glUniform3uiv							= nullptr;
		const PFNGLUNIFORM4UIVPROC										glUniform4uiv							= nullptr;
		const PFNGLTEXPARAMETERIIVPROC									glTexParameterIiv						= nullptr;
		const PFNGLTEXPARAMETERIUIVPROC									glTexParameterIuiv						= nullptr;
		const PFNGLGETTEXPARAMETERIIVPROC								glGetTexParameterIiv					= nullptr;
		const PFNGLGETTEXPARAMETERIUIVPROC								glGetTexParameterIuiv					= nullptr;
		const PFNGLCLEARBUFFERIVPROC									glClearBufferiv							= nullptr;
		const PFNGLCLEARBUFFERUIVPROC									glClearBufferuiv						= nullptr;
		const PFNGLCLEARBUFFERFVPROC									glClearBufferfv							= nullptr;
		const PFNGLCLEARBUFFERFIPROC									glClearBufferfi							= nullptr;
		const PFNGLGETSTRINGIPROC										glGetStringi							= nullptr;
		const PFNGLISRENDERBUFFERPROC									glIsRenderbuffer						= nullptr;
		const PFNGLBINDRENDERBUFFERPROC									glBindRenderbuffer						= nullptr;
		const PFNGLDELETERENDERBUFFERSPROC								glDeleteRenderbuffers					= nullptr;
		const PFNGLGENRENDERBUFFERSPROC									glGenRenderbuffers						= nullptr;
		const PFNGLRENDERBUFFERSTORAGEPROC								glRenderbufferStorage					= nullptr;
		const PFNGLGETRENDERBUFFERPARAMETERIVPROC						glGetRenderbufferParameteriv			= nullptr;
		const PFNGLISFRAMEBUFFERPROC									glIsFramebuffer							= nullptr;
		const PFNGLBINDFRAMEBUFFERPROC									glBindFramebuffer						= nullptr;
		const PFNGLDELETEFRAMEBUFFERSPROC								glDeleteFramebuffers					= nullptr;
		const PFNGLGENFRAMEBUFFERSPROC									glGenFramebuffers						= nullptr;
		const PFNGLCHECKFRAMEBUFFERSTATUSPROC							glCheckFramebufferStatus				= nullptr;
		const PFNGLFRAMEBUFFERTEXTURE1DPROC								glFramebufferTexture1D					= nullptr;
		const PFNGLFRAMEBUFFERTEXTURE2DPROC								glFramebufferTexture2D					= nullptr;
		const PFNGLFRAMEBUFFERTEXTURE3DPROC								glFramebufferTexture3D					= nullptr;
		const PFNGLFRAMEBUFFERRENDERBUFFERPROC							glFramebufferRenderbuffer				= nullptr;
		const PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC				glGetFramebufferAttachmentParameteriv	= nullptr;
		const PFNGLGENERATEMIPMAPPROC									glGenerateMipmap						= nullptr;
		const PFNGLBLITFRAMEBUFFERPROC									glBlitFramebuffer						= nullptr;
		const PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC					glRenderbufferStorageMultisample		= nullptr;
		const PFNGLFRAMEBUFFERTEXTURELAYERPROC							glFramebufferTextureLayer				= nullptr;
		const PFNGLMAPBUFFERRANGEPROC									glMapBufferRange						= nullptr;
		const PFNGLFLUSHMAPPEDBUFFERRANGEPROC							glFlushMappedBufferRange				= nullptr;
		const PFNGLBINDVERTEXARRAYPROC									glBindVertexArray						= nullptr;
		const PFNGLDELETEVERTEXARRAYSPROC								glDeleteVertexArrays					= nullptr;
		const PFNGLGENVERTEXARRAYSPROC									glGenVertexArrays						= nullptr;
		const PFNGLISVERTEXARRAYPROC									glIsVertexArray							= nullptr;
	protected:
		inline Interface_3_0() = default;
		inline Interface_3_0(
			const PFNGLCOLORMASKIPROC&										glColorMaski_,
			const PFNGLGETBOOLEANI_VPROC&									glGetBooleani_v_,
			const PFNGLGETINTEGERI_VPROC&									glGetIntegeri_v_,
			const PFNGLENABLEIPROC&											glEnablei_,
			const PFNGLDISABLEIPROC&										glDisablei_,
			const PFNGLISENABLEDIPROC&										glIsEnabledi_,
			const PFNGLBEGINTRANSFORMFEEDBACKPROC&							glBeginTransformFeedback_,
			const PFNGLENDTRANSFORMFEEDBACKPROC&							glEndTransformFeedback_,
			const PFNGLBINDBUFFERRANGEPROC&									glBindBufferRange_,
			const PFNGLBINDBUFFERBASEPROC&									glBindBufferBase_,
			const PFNGLTRANSFORMFEEDBACKVARYINGSPROC&						glTransformFeedbackVaryings_,
			const PFNGLGETTRANSFORMFEEDBACKVARYINGPROC&						glGetTransformFeedbackVarying_,
			const PFNGLCLAMPCOLORPROC&										glClampColor_,
			const PFNGLBEGINCONDITIONALRENDERPROC&							glBeginConditionalRender_,
			const PFNGLENDCONDITIONALRENDERPROC&							glEndConditionalRender_,
			const PFNGLVERTEXATTRIBIPOINTERPROC&							glVertexAttribIPointer_,
			const PFNGLGETVERTEXATTRIBIIVPROC&								glGetVertexAttribIiv_,
			const PFNGLGETVERTEXATTRIBIUIVPROC&								glGetVertexAttribIuiv_,
			const PFNGLVERTEXATTRIBI1IPROC&									glVertexAttribI1i_,
			const PFNGLVERTEXATTRIBI2IPROC&									glVertexAttribI2i_,
			const PFNGLVERTEXATTRIBI3IPROC&									glVertexAttribI3i_,
			const PFNGLVERTEXATTRIBI4IPROC&									glVertexAttribI4i_,
			const PFNGLVERTEXATTRIBI1UIPROC&								glVertexAttribI1ui_,
			const PFNGLVERTEXATTRIBI2UIPROC&								glVertexAttribI2ui_,
			const PFNGLVERTEXATTRIBI3UIPROC&								glVertexAttribI3ui_,
			const PFNGLVERTEXATTRIBI4UIPROC&								glVertexAttribI4ui_,
			const PFNGLVERTEXATTRIBI1IVPROC&								glVertexAttribI1iv_,
			const PFNGLVERTEXATTRIBI2IVPROC&								glVertexAttribI2iv_,
			const PFNGLVERTEXATTRIBI3IVPROC&								glVertexAttribI3iv_,
			const PFNGLVERTEXATTRIBI4IVPROC&								glVertexAttribI4iv_,
			const PFNGLVERTEXATTRIBI1UIVPROC&								glVertexAttribI1uiv_,
			const PFNGLVERTEXATTRIBI2UIVPROC&								glVertexAttribI2uiv_,
			const PFNGLVERTEXATTRIBI3UIVPROC&								glVertexAttribI3uiv_,
			const PFNGLVERTEXATTRIBI4UIVPROC&								glVertexAttribI4uiv_,
			const PFNGLVERTEXATTRIBI4BVPROC&								glVertexAttribI4bv_,
			const PFNGLVERTEXATTRIBI4SVPROC&								glVertexAttribI4sv_,
			const PFNGLVERTEXATTRIBI4UBVPROC&								glVertexAttribI4ubv_,
			const PFNGLVERTEXATTRIBI4USVPROC&								glVertexAttribI4usv_,
			const PFNGLGETUNIFORMUIVPROC&									glGetUniformuiv_,
			const PFNGLBINDFRAGDATALOCATIONPROC&							glBindFragDataLocation_,
			const PFNGLGETFRAGDATALOCATIONPROC&								glGetFragDataLocation_,
			const PFNGLUNIFORM1UIPROC&										glUniform1ui_,
			const PFNGLUNIFORM2UIPROC&										glUniform2ui_,
			const PFNGLUNIFORM3UIPROC&										glUniform3ui_,
			const PFNGLUNIFORM4UIPROC&										glUniform4ui_,
			const PFNGLUNIFORM1UIVPROC&										glUniform1uiv_,
			const PFNGLUNIFORM2UIVPROC&										glUniform2uiv_,
			const PFNGLUNIFORM3UIVPROC&										glUniform3uiv_,
			const PFNGLUNIFORM4UIVPROC&										glUniform4uiv_,
			const PFNGLTEXPARAMETERIIVPROC&									glTexParameterIiv_,
			const PFNGLTEXPARAMETERIUIVPROC&								glTexParameterIuiv_,
			const PFNGLGETTEXPARAMETERIIVPROC&								glGetTexParameterIiv_,
			const PFNGLGETTEXPARAMETERIUIVPROC&								glGetTexParameterIuiv_,
			const PFNGLCLEARBUFFERIVPROC&									glClearBufferiv_,
			const PFNGLCLEARBUFFERUIVPROC&									glClearBufferuiv_,
			const PFNGLCLEARBUFFERFVPROC&									glClearBufferfv_,
			const PFNGLCLEARBUFFERFIPROC&									glClearBufferfi_,
			const PFNGLGETSTRINGIPROC&										glGetStringi_,
			const PFNGLISRENDERBUFFERPROC&									glIsRenderbuffer_,
			const PFNGLBINDRENDERBUFFERPROC&								glBindRenderbuffer_,
			const PFNGLDELETERENDERBUFFERSPROC&								glDeleteRenderbuffers_,
			const PFNGLGENRENDERBUFFERSPROC&								glGenRenderbuffers_,
			const PFNGLRENDERBUFFERSTORAGEPROC&								glRenderbufferStorage_,
			const PFNGLGETRENDERBUFFERPARAMETERIVPROC&						glGetRenderbufferParameteriv_,
			const PFNGLISFRAMEBUFFERPROC&									glIsFramebuffer_,
			const PFNGLBINDFRAMEBUFFERPROC&									glBindFramebuffer_,
			const PFNGLDELETEFRAMEBUFFERSPROC&								glDeleteFramebuffers_,
			const PFNGLGENFRAMEBUFFERSPROC&									glGenFramebuffers_,
			const PFNGLCHECKFRAMEBUFFERSTATUSPROC&							glCheckFramebufferStatus_,
			const PFNGLFRAMEBUFFERTEXTURE1DPROC&							glFramebufferTexture1D_,
			const PFNGLFRAMEBUFFERTEXTURE2DPROC&							glFramebufferTexture2D_,
			const PFNGLFRAMEBUFFERTEXTURE3DPROC&							glFramebufferTexture3D_,
			const PFNGLFRAMEBUFFERRENDERBUFFERPROC&							glFramebufferRenderbuffer_,
			const PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC&				glGetFramebufferAttachmentParameteriv_,
			const PFNGLGENERATEMIPMAPPROC&									glGenerateMipmap_,
			const PFNGLBLITFRAMEBUFFERPROC&									glBlitFramebuffer_,
			const PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC&					glRenderbufferStorageMultisample_,
			const PFNGLFRAMEBUFFERTEXTURELAYERPROC&							glFramebufferTextureLayer_,
			const PFNGLMAPBUFFERRANGEPROC&									glMapBufferRange_,
			const PFNGLFLUSHMAPPEDBUFFERRANGEPROC&							glFlushMappedBufferRange_,
			const PFNGLBINDVERTEXARRAYPROC&									glBindVertexArray_,
			const PFNGLDELETEVERTEXARRAYSPROC&								glDeleteVertexArrays_,
			const PFNGLGENVERTEXARRAYSPROC&									glGenVertexArrays_,
			const PFNGLISVERTEXARRAYPROC&									glIsVertexArray_
		);
	public:
		inline void														BindVertexArray(const Null&) const
		{
			glBindVertexArray(0);

			CheckForErrors();
		}
		inline void														BindVertexArray(const VertexArray::Handle& handle_) const
		{
			glBindVertexArray(static_cast<VertexArray::Handle::Value>(handle_));

			CheckForErrors();
		}
		inline void														DeleteVertexArray(const VertexArray::Handle& handle_) const
		{
			glDeleteVertexArrays(1, static_cast<const VertexArray::Handle::Value*>(handle_));

			CheckForErrors();
		}
		inline VertexArray::Handle										GenVertexArray() const
		{
			VertexArray::Handle handle;

			glGenVertexArrays(1, static_cast<VertexArray::Handle::Value*>(handle));

			CheckForErrors();

			return handle;
		}
	};
	class Interface_3_1:
		public virtual Interface
	{
	protected:
		const PFNGLDRAWARRAYSINSTANCEDPROC			glDrawArraysInstanced			= nullptr;
		const PFNGLDRAWELEMENTSINSTANCEDPROC		glDrawElementsInstanced			= nullptr;
		const PFNGLTEXBUFFERPROC					glTexBuffer						= nullptr;
		const PFNGLPRIMITIVERESTARTINDEXPROC		glPrimitiveRestartIndex			= nullptr;
		const PFNGLCOPYBUFFERSUBDATAPROC			glCopyBufferSubData				= nullptr;
		const PFNGLGETUNIFORMINDICESPROC			glGetUniformIndices				= nullptr;
		const PFNGLGETACTIVEUNIFORMSIVPROC			glGetActiveUniformsiv			= nullptr;
		const PFNGLGETACTIVEUNIFORMNAMEPROC			glGetActiveUniformName			= nullptr;
		const PFNGLGETUNIFORMBLOCKINDEXPROC			glGetUniformBlockIndex			= nullptr;
		const PFNGLGETACTIVEUNIFORMBLOCKIVPROC		glGetActiveUniformBlockiv		= nullptr;
		const PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC	glGetActiveUniformBlockName		= nullptr;
		const PFNGLUNIFORMBLOCKBINDINGPROC			glUniformBlockBinding			= nullptr;
	protected:
		inline Interface_3_1() = default;
		inline Interface_3_1(
			const PFNGLDRAWARRAYSINSTANCEDPROC&			glDrawArraysInstanced_,
			const PFNGLDRAWELEMENTSINSTANCEDPROC&		glDrawElementsInstanced_,
			const PFNGLTEXBUFFERPROC&					glTexBuffer_,
			const PFNGLPRIMITIVERESTARTINDEXPROC&		glPrimitiveRestartIndex_,
			const PFNGLCOPYBUFFERSUBDATAPROC&			glCopyBufferSubData_,
			const PFNGLGETUNIFORMINDICESPROC&			glGetUniformIndices_,
			const PFNGLGETACTIVEUNIFORMSIVPROC&			glGetActiveUniformsiv_,
			const PFNGLGETACTIVEUNIFORMNAMEPROC&		glGetActiveUniformName_,
			const PFNGLGETUNIFORMBLOCKINDEXPROC&		glGetUniformBlockIndex_,
			const PFNGLGETACTIVEUNIFORMBLOCKIVPROC&		glGetActiveUniformBlockiv_,
			const PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC&	glGetActiveUniformBlockName_,
			const PFNGLUNIFORMBLOCKBINDINGPROC&			glUniformBlockBinding_
		);
	};
	class Interface_3_2:
		public virtual Interface
	{
	protected:
		const PFNGLDRAWELEMENTSBASEVERTEXPROC			glDrawElementsBaseVertex			= nullptr;
		const PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC		glDrawRangeElementsBaseVertex		= nullptr;
		const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC	glDrawElementsInstancedBaseVertex	= nullptr;
		const PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC		glMultiDrawElementsBaseVertex		= nullptr;
		const PFNGLPROVOKINGVERTEXPROC					glProvokingVertex					= nullptr;
		const PFNGLFENCESYNCPROC						glFenceSync							= nullptr;
		const PFNGLISSYNCPROC							glIsSync							= nullptr;
		const PFNGLDELETESYNCPROC						glDeleteSync						= nullptr;
		const PFNGLCLIENTWAITSYNCPROC					glClientWaitSync					= nullptr;
		const PFNGLWAITSYNCPROC							glWaitSync							= nullptr;
		const PFNGLGETINTEGER64VPROC					glGetInteger64v						= nullptr;
		const PFNGLGETSYNCIVPROC						glGetSynciv							= nullptr;
		const PFNGLGETINTEGER64I_VPROC					glGetInteger64i_v					= nullptr;
		const PFNGLGETBUFFERPARAMETERI64VPROC			glGetBufferParameteri64v			= nullptr;
		const PFNGLFRAMEBUFFERTEXTUREPROC				glFramebufferTexture				= nullptr;
		const PFNGLTEXIMAGE2DMULTISAMPLEPROC			glTexImage2DMultisample				= nullptr;
		const PFNGLTEXIMAGE3DMULTISAMPLEPROC			glTexImage3DMultisample				= nullptr;
		const PFNGLGETMULTISAMPLEFVPROC					glGetMultisamplefv					= nullptr;
		const PFNGLSAMPLEMASKIPROC						glSampleMaski						= nullptr;
	protected:
		inline Interface_3_2() = default;
		inline Interface_3_2(
			const PFNGLDRAWELEMENTSBASEVERTEXPROC&			glDrawElementsBaseVertex_,
			const PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC&		glDrawRangeElementsBaseVertex_,
			const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC&	glDrawElementsInstancedBaseVertex_,
			const PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC&		glMultiDrawElementsBaseVertex_,
			const PFNGLPROVOKINGVERTEXPROC&					glProvokingVertex_,
			const PFNGLFENCESYNCPROC&						glFenceSync_,
			const PFNGLISSYNCPROC&							glIsSync_,
			const PFNGLDELETESYNCPROC&						glDeleteSync_,
			const PFNGLCLIENTWAITSYNCPROC&					glClientWaitSync_,
			const PFNGLWAITSYNCPROC&						glWaitSync_,	
			const PFNGLGETINTEGER64VPROC&					glGetInteger64v_,
			const PFNGLGETSYNCIVPROC&						glGetSynciv_,
			const PFNGLGETINTEGER64I_VPROC&					glGetInteger64i_v_,
			const PFNGLGETBUFFERPARAMETERI64VPROC&			glGetBufferParameteri64v_,
			const PFNGLFRAMEBUFFERTEXTUREPROC&				glFramebufferTexture_,
			const PFNGLTEXIMAGE2DMULTISAMPLEPROC&			glTexImage2DMultisample_,
			const PFNGLTEXIMAGE3DMULTISAMPLEPROC&			glTexImage3DMultisample_,
			const PFNGLGETMULTISAMPLEFVPROC&				glGetMultisamplefv_,	
			const PFNGLSAMPLEMASKIPROC&						glSampleMaski_
		);
	};
	class Interface_3_3:
		public virtual Interface
	{
	protected:
		const PFNGLBINDFRAGDATALOCATIONINDEXEDPROC		glBindFragDataLocationIndexed	= nullptr;
		const PFNGLGETFRAGDATAINDEXPROC					glGetFragDataIndex				= nullptr;
		const PFNGLGENSAMPLERSPROC						glGenSamplers					= nullptr;
		const PFNGLDELETESAMPLERSPROC					glDeleteSamplers				= nullptr;
		const PFNGLISSAMPLERPROC						glIsSampler						= nullptr;
		const PFNGLBINDSAMPLERPROC						glBindSampler					= nullptr;
		const PFNGLSAMPLERPARAMETERIPROC				glSamplerParameteri				= nullptr;
		const PFNGLSAMPLERPARAMETERIVPROC				glSamplerParameteriv			= nullptr;
		const PFNGLSAMPLERPARAMETERFPROC				glSamplerParameterf				= nullptr;
		const PFNGLSAMPLERPARAMETERFVPROC				glSamplerParameterfv			= nullptr;
		const PFNGLSAMPLERPARAMETERIIVPROC				glSamplerParameterIiv			= nullptr;
		const PFNGLSAMPLERPARAMETERIUIVPROC				glSamplerParameterIuiv			= nullptr;
		const PFNGLGETSAMPLERPARAMETERIVPROC			glGetSamplerParameteriv			= nullptr;
		const PFNGLGETSAMPLERPARAMETERIIVPROC			glGetSamplerParameterIiv		= nullptr;
		const PFNGLGETSAMPLERPARAMETERFVPROC			glGetSamplerParameterfv			= nullptr;
		const PFNGLGETSAMPLERPARAMETERIUIVPROC			glGetSamplerParameterIuiv		= nullptr;
		const PFNGLQUERYCOUNTERPROC						glQueryCounter					= nullptr;
		const PFNGLGETQUERYOBJECTI64VPROC				glGetQueryObjecti64v			= nullptr;
		const PFNGLGETQUERYOBJECTUI64VPROC				glGetQueryObjectui64v			= nullptr;
		const PFNGLVERTEXATTRIBDIVISORPROC				glVertexAttribDivisor			= nullptr;
		const PFNGLVERTEXATTRIBP1UIPROC					glVertexAttribP1ui				= nullptr;
		const PFNGLVERTEXATTRIBP1UIVPROC				glVertexAttribP1uiv				= nullptr;
		const PFNGLVERTEXATTRIBP2UIPROC					glVertexAttribP2ui				= nullptr;
		const PFNGLVERTEXATTRIBP2UIVPROC				glVertexAttribP2uiv				= nullptr;
		const PFNGLVERTEXATTRIBP3UIPROC					glVertexAttribP3ui				= nullptr;
		const PFNGLVERTEXATTRIBP3UIVPROC				glVertexAttribP3uiv				= nullptr;
		const PFNGLVERTEXATTRIBP4UIPROC					glVertexAttribP4ui				= nullptr;
		const PFNGLVERTEXATTRIBP4UIVPROC				glVertexAttribP4uiv				= nullptr;
		const PFNGLVERTEXP2UIPROC						glVertexP2ui					= nullptr;
		const PFNGLVERTEXP2UIVPROC						glVertexP2uiv					= nullptr;
		const PFNGLVERTEXP3UIPROC						glVertexP3ui					= nullptr;
		const PFNGLVERTEXP3UIVPROC						glVertexP3uiv					= nullptr;
		const PFNGLVERTEXP4UIPROC						glVertexP4ui					= nullptr;
		const PFNGLVERTEXP4UIVPROC						glVertexP4uiv					= nullptr;
		const PFNGLTEXCOORDP1UIPROC						glTexCoordP1ui					= nullptr;
		const PFNGLTEXCOORDP1UIVPROC					glTexCoordP1uiv					= nullptr;
		const PFNGLTEXCOORDP2UIPROC						glTexCoordP2ui					= nullptr;
		const PFNGLTEXCOORDP2UIVPROC					glTexCoordP2uiv					= nullptr;
		const PFNGLTEXCOORDP3UIPROC						glTexCoordP3ui					= nullptr;
		const PFNGLTEXCOORDP3UIVPROC					glTexCoordP3uiv					= nullptr;
		const PFNGLTEXCOORDP4UIPROC						glTexCoordP4ui					= nullptr;
		const PFNGLTEXCOORDP4UIVPROC					glTexCoordP4uiv					= nullptr;
		const PFNGLMULTITEXCOORDP1UIPROC				glMultiTexCoordP1ui				= nullptr;
		const PFNGLMULTITEXCOORDP1UIVPROC				glMultiTexCoordP1uiv			= nullptr;
		const PFNGLMULTITEXCOORDP2UIPROC				glMultiTexCoordP2ui				= nullptr;
		const PFNGLMULTITEXCOORDP2UIVPROC				glMultiTexCoordP2uiv			= nullptr;
		const PFNGLMULTITEXCOORDP3UIPROC				glMultiTexCoordP3ui				= nullptr;
		const PFNGLMULTITEXCOORDP3UIVPROC				glMultiTexCoordP3uiv			= nullptr;
		const PFNGLMULTITEXCOORDP4UIPROC				glMultiTexCoordP4ui				= nullptr;
		const PFNGLMULTITEXCOORDP4UIVPROC				glMultiTexCoordP4uiv			= nullptr;
		const PFNGLNORMALP3UIPROC						glNormalP3ui					= nullptr;
		const PFNGLNORMALP3UIVPROC						glNormalP3uiv					= nullptr;
		const PFNGLCOLORP3UIPROC						glColorP3ui						= nullptr;
		const PFNGLCOLORP3UIVPROC						glColorP3uiv					= nullptr;
		const PFNGLCOLORP4UIPROC						glColorP4ui						= nullptr;
		const PFNGLCOLORP4UIVPROC						glColorP4uiv					= nullptr;
		const PFNGLSECONDARYCOLORP3UIPROC				glSecondaryColorP3ui			= nullptr;
		const PFNGLSECONDARYCOLORP3UIVPROC				glSecondaryColorP3uiv			= nullptr;
	protected:
		inline Interface_3_3() = default;
		inline Interface_3_3(
			const PFNGLBINDFRAGDATALOCATIONINDEXEDPROC&		glBindFragDataLocationIndexed_,
			const PFNGLGETFRAGDATAINDEXPROC&				glGetFragDataIndex_,	
			const PFNGLGENSAMPLERSPROC&						glGenSamplers_,
			const PFNGLDELETESAMPLERSPROC&					glDeleteSamplers_,
			const PFNGLISSAMPLERPROC&						glIsSampler_,
			const PFNGLBINDSAMPLERPROC&						glBindSampler_,
			const PFNGLSAMPLERPARAMETERIPROC&				glSamplerParameteri_,
			const PFNGLSAMPLERPARAMETERIVPROC&				glSamplerParameteriv_,
			const PFNGLSAMPLERPARAMETERFPROC&				glSamplerParameterf_,
			const PFNGLSAMPLERPARAMETERFVPROC&				glSamplerParameterfv_,
			const PFNGLSAMPLERPARAMETERIIVPROC&				glSamplerParameterIiv_,
			const PFNGLSAMPLERPARAMETERIUIVPROC&			glSamplerParameterIuiv_,	
			const PFNGLGETSAMPLERPARAMETERIVPROC&			glGetSamplerParameteriv_,
			const PFNGLGETSAMPLERPARAMETERIIVPROC&			glGetSamplerParameterIiv_,
			const PFNGLGETSAMPLERPARAMETERFVPROC&			glGetSamplerParameterfv_,
			const PFNGLGETSAMPLERPARAMETERIUIVPROC&			glGetSamplerParameterIuiv_,
			const PFNGLQUERYCOUNTERPROC&					glQueryCounter_,	
			const PFNGLGETQUERYOBJECTI64VPROC&				glGetQueryObjecti64v_,
			const PFNGLGETQUERYOBJECTUI64VPROC&				glGetQueryObjectui64v_,
			const PFNGLVERTEXATTRIBDIVISORPROC&				glVertexAttribDivisor_,
			const PFNGLVERTEXATTRIBP1UIPROC&				glVertexAttribP1ui_,	
			const PFNGLVERTEXATTRIBP1UIVPROC&				glVertexAttribP1uiv_,
			const PFNGLVERTEXATTRIBP2UIPROC&				glVertexAttribP2ui_,	
			const PFNGLVERTEXATTRIBP2UIVPROC&				glVertexAttribP2uiv_,
			const PFNGLVERTEXATTRIBP3UIPROC&				glVertexAttribP3ui_,	
			const PFNGLVERTEXATTRIBP3UIVPROC&				glVertexAttribP3uiv_,
			const PFNGLVERTEXATTRIBP4UIPROC&				glVertexAttribP4ui_,	
			const PFNGLVERTEXATTRIBP4UIVPROC&				glVertexAttribP4uiv_,
			const PFNGLVERTEXP2UIPROC&						glVertexP2ui_,
			const PFNGLVERTEXP2UIVPROC&						glVertexP2uiv_,
			const PFNGLVERTEXP3UIPROC&						glVertexP3ui_,
			const PFNGLVERTEXP3UIVPROC&						glVertexP3uiv_,
			const PFNGLVERTEXP4UIPROC&						glVertexP4ui_,
			const PFNGLVERTEXP4UIVPROC&						glVertexP4uiv_,
			const PFNGLTEXCOORDP1UIPROC&					glTexCoordP1ui_,	
			const PFNGLTEXCOORDP1UIVPROC&					glTexCoordP1uiv_,
			const PFNGLTEXCOORDP2UIPROC&					glTexCoordP2ui_,	
			const PFNGLTEXCOORDP2UIVPROC&					glTexCoordP2uiv_,
			const PFNGLTEXCOORDP3UIPROC&					glTexCoordP3ui_,	
			const PFNGLTEXCOORDP3UIVPROC&					glTexCoordP3uiv_,
			const PFNGLTEXCOORDP4UIPROC&					glTexCoordP4ui_,	
			const PFNGLTEXCOORDP4UIVPROC&					glTexCoordP4uiv_,
			const PFNGLMULTITEXCOORDP1UIPROC&				glMultiTexCoordP1ui_,
			const PFNGLMULTITEXCOORDP1UIVPROC&				glMultiTexCoordP1uiv_,
			const PFNGLMULTITEXCOORDP2UIPROC&				glMultiTexCoordP2ui_,
			const PFNGLMULTITEXCOORDP2UIVPROC&				glMultiTexCoordP2uiv_,
			const PFNGLMULTITEXCOORDP3UIPROC&				glMultiTexCoordP3ui_,
			const PFNGLMULTITEXCOORDP3UIVPROC&				glMultiTexCoordP3uiv_,
			const PFNGLMULTITEXCOORDP4UIPROC&				glMultiTexCoordP4ui_,
			const PFNGLMULTITEXCOORDP4UIVPROC&				glMultiTexCoordP4uiv_,
			const PFNGLNORMALP3UIPROC&						glNormalP3ui_,
			const PFNGLNORMALP3UIVPROC&						glNormalP3uiv_,
			const PFNGLCOLORP3UIPROC&						glColorP3ui_,
			const PFNGLCOLORP3UIVPROC&						glColorP3uiv_,
			const PFNGLCOLORP4UIPROC&						glColorP4ui_,
			const PFNGLCOLORP4UIVPROC&						glColorP4uiv_,
			const PFNGLSECONDARYCOLORP3UIPROC&				glSecondaryColorP3ui_,
			const PFNGLSECONDARYCOLORP3UIVPROC&				glSecondaryColorP3uiv_
		);
	};
	class Interface_4_0:
		public virtual Interface
	{
	protected:
		const PFNGLMINSAMPLESHADINGPROC					glMinSampleShading					= nullptr;
		const PFNGLBLENDEQUATIONIPROC					glBlendEquationi					= nullptr;
		const PFNGLBLENDEQUATIONSEPARATEIPROC			glBlendEquationSeparatei			= nullptr;
		const PFNGLBLENDFUNCIPROC						glBlendFunci						= nullptr;
		const PFNGLBLENDFUNCSEPARATEIPROC				glBlendFuncSeparatei				= nullptr;
		const PFNGLDRAWARRAYSINDIRECTPROC				glDrawArraysIndirect				= nullptr;
		const PFNGLDRAWELEMENTSINDIRECTPROC				glDrawElementsIndirect				= nullptr;
		const PFNGLUNIFORM1DPROC						glUniform1d							= nullptr;
		const PFNGLUNIFORM2DPROC						glUniform2d							= nullptr;
		const PFNGLUNIFORM3DPROC						glUniform3d							= nullptr;
		const PFNGLUNIFORM4DPROC						glUniform4d							= nullptr;
		const PFNGLUNIFORM1DVPROC						glUniform1dv						= nullptr;
		const PFNGLUNIFORM2DVPROC						glUniform2dv						= nullptr;
		const PFNGLUNIFORM3DVPROC						glUniform3dv						= nullptr;
		const PFNGLUNIFORM4DVPROC						glUniform4dv						= nullptr;
		const PFNGLUNIFORMMATRIX2DVPROC					glUniformMatrix2dv					= nullptr;
		const PFNGLUNIFORMMATRIX3DVPROC					glUniformMatrix3dv					= nullptr;
		const PFNGLUNIFORMMATRIX4DVPROC					glUniformMatrix4dv					= nullptr;
		const PFNGLUNIFORMMATRIX2X3DVPROC				glUniformMatrix2x3dv				= nullptr;
		const PFNGLUNIFORMMATRIX2X4DVPROC				glUniformMatrix2x4dv				= nullptr;
		const PFNGLUNIFORMMATRIX3X2DVPROC				glUniformMatrix3x2dv				= nullptr;
		const PFNGLUNIFORMMATRIX3X4DVPROC				glUniformMatrix3x4dv				= nullptr;
		const PFNGLUNIFORMMATRIX4X2DVPROC				glUniformMatrix4x2dv				= nullptr;
		const PFNGLUNIFORMMATRIX4X3DVPROC				glUniformMatrix4x3dv				= nullptr;
		const PFNGLGETUNIFORMDVPROC						glGetUniformdv						= nullptr;
		const PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC		glGetSubroutineUniformLocation		= nullptr;
		const PFNGLGETSUBROUTINEINDEXPROC				glGetSubroutineIndex				= nullptr;
		const PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC		glGetActiveSubroutineUniformiv		= nullptr;
		const PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC	glGetActiveSubroutineUniformName	= nullptr;
		const PFNGLGETACTIVESUBROUTINENAMEPROC			glGetActiveSubroutineName			= nullptr;
		const PFNGLUNIFORMSUBROUTINESUIVPROC			glUniformSubroutinesuiv				= nullptr;
		const PFNGLGETUNIFORMSUBROUTINEUIVPROC			glGetUniformSubroutineuiv			= nullptr;
		const PFNGLGETPROGRAMSTAGEIVPROC				glGetProgramStageiv					= nullptr;
		const PFNGLPATCHPARAMETERIPROC					glPatchParameteri					= nullptr;
		const PFNGLPATCHPARAMETERFVPROC					glPatchParameterfv					= nullptr;
		const PFNGLBINDTRANSFORMFEEDBACKPROC			glBindTransformFeedback				= nullptr;
		const PFNGLDELETETRANSFORMFEEDBACKSPROC			glDeleteTransformFeedbacks			= nullptr;
		const PFNGLGENTRANSFORMFEEDBACKSPROC			glGenTransformFeedbacks				= nullptr;
		const PFNGLISTRANSFORMFEEDBACKPROC				glIsTransformFeedback				= nullptr;
		const PFNGLPAUSETRANSFORMFEEDBACKPROC			glPauseTransformFeedback			= nullptr;
		const PFNGLRESUMETRANSFORMFEEDBACKPROC			glResumeTransformFeedback			= nullptr;
		const PFNGLDRAWTRANSFORMFEEDBACKPROC			glDrawTransformFeedback				= nullptr;
		const PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC		glDrawTransformFeedbackStream		= nullptr;
		const PFNGLBEGINQUERYINDEXEDPROC				glBeginQueryIndexed					= nullptr;
		const PFNGLENDQUERYINDEXEDPROC					glEndQueryIndexed					= nullptr;
		const PFNGLGETQUERYINDEXEDIVPROC				glGetQueryIndexediv					= nullptr;
	protected:
		inline Interface_4_0() = default;
		inline Interface_4_0(
			const PFNGLMINSAMPLESHADINGPROC&					glMinSampleShading_,
			const PFNGLBLENDEQUATIONIPROC&						glBlendEquationi_,
			const PFNGLBLENDEQUATIONSEPARATEIPROC&				glBlendEquationSeparatei_,
			const PFNGLBLENDFUNCIPROC&							glBlendFunci_,
			const PFNGLBLENDFUNCSEPARATEIPROC&					glBlendFuncSeparatei_,
			const PFNGLDRAWARRAYSINDIRECTPROC&					glDrawArraysIndirect_,
			const PFNGLDRAWELEMENTSINDIRECTPROC&				glDrawElementsIndirect_,
			const PFNGLUNIFORM1DPROC&							glUniform1d_,
			const PFNGLUNIFORM2DPROC&							glUniform2d_,
			const PFNGLUNIFORM3DPROC&							glUniform3d_,
			const PFNGLUNIFORM4DPROC&							glUniform4d_,
			const PFNGLUNIFORM1DVPROC&							glUniform1dv_,
			const PFNGLUNIFORM2DVPROC&							glUniform2dv_,
			const PFNGLUNIFORM3DVPROC&							glUniform3dv_,
			const PFNGLUNIFORM4DVPROC&							glUniform4dv_,
			const PFNGLUNIFORMMATRIX2DVPROC&					glUniformMatrix2dv_,
			const PFNGLUNIFORMMATRIX3DVPROC&					glUniformMatrix3dv_,
			const PFNGLUNIFORMMATRIX4DVPROC&					glUniformMatrix4dv_,
			const PFNGLUNIFORMMATRIX2X3DVPROC&					glUniformMatrix2x3dv_,
			const PFNGLUNIFORMMATRIX2X4DVPROC&					glUniformMatrix2x4dv_,
			const PFNGLUNIFORMMATRIX3X2DVPROC&					glUniformMatrix3x2dv_,
			const PFNGLUNIFORMMATRIX3X4DVPROC&					glUniformMatrix3x4dv_,
			const PFNGLUNIFORMMATRIX4X2DVPROC&					glUniformMatrix4x2dv_,
			const PFNGLUNIFORMMATRIX4X3DVPROC&					glUniformMatrix4x3dv_,
			const PFNGLGETUNIFORMDVPROC&						glGetUniformdv_,
			const PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC&		glGetSubroutineUniformLocation_,
			const PFNGLGETSUBROUTINEINDEXPROC&					glGetSubroutineIndex_,
			const PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC&		glGetActiveSubroutineUniformiv_,
			const PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC&		glGetActiveSubroutineUniformName_,
			const PFNGLGETACTIVESUBROUTINENAMEPROC&				glGetActiveSubroutineName_,
			const PFNGLUNIFORMSUBROUTINESUIVPROC&				glUniformSubroutinesuiv_,
			const PFNGLGETUNIFORMSUBROUTINEUIVPROC&				glGetUniformSubroutineuiv_,
			const PFNGLGETPROGRAMSTAGEIVPROC&					glGetProgramStageiv_,
			const PFNGLPATCHPARAMETERIPROC&						glPatchParameteri_,
			const PFNGLPATCHPARAMETERFVPROC&					glPatchParameterfv_,
			const PFNGLBINDTRANSFORMFEEDBACKPROC&				glBindTransformFeedback_,
			const PFNGLDELETETRANSFORMFEEDBACKSPROC&			glDeleteTransformFeedbacks_,
			const PFNGLGENTRANSFORMFEEDBACKSPROC&				glGenTransformFeedbacks_,
			const PFNGLISTRANSFORMFEEDBACKPROC&					glIsTransformFeedback_,
			const PFNGLPAUSETRANSFORMFEEDBACKPROC&				glPauseTransformFeedback_,
			const PFNGLRESUMETRANSFORMFEEDBACKPROC&				glResumeTransformFeedback_,
			const PFNGLDRAWTRANSFORMFEEDBACKPROC&				glDrawTransformFeedback_,
			const PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC&			glDrawTransformFeedbackStream_,
			const PFNGLBEGINQUERYINDEXEDPROC&					glBeginQueryIndexed_,
			const PFNGLENDQUERYINDEXEDPROC&						glEndQueryIndexed_,
			const PFNGLGETQUERYINDEXEDIVPROC&					glGetQueryIndexediv_
		);
	};
	class Interface_4_1:
		public virtual Interface
	{
	protected:
		const PFNGLRELEASESHADERCOMPILERPROC			glReleaseShaderCompiler				= nullptr;
		const PFNGLSHADERBINARYPROC						glShaderBinary						= nullptr;
		const PFNGLGETSHADERPRECISIONFORMATPROC			glGetShaderPrecisionFormat			= nullptr;
		const PFNGLDEPTHRANGEFPROC						glDepthRangef						= nullptr;
		const PFNGLCLEARDEPTHFPROC						glClearDepthf						= nullptr;
		const PFNGLGETPROGRAMBINARYPROC					glGetProgramBinary					= nullptr;
		const PFNGLPROGRAMBINARYPROC					glProgramBinary						= nullptr;
		const PFNGLPROGRAMPARAMETERIPROC				glProgramParameteri					= nullptr;
		const PFNGLUSEPROGRAMSTAGESPROC					glUseProgramStages					= nullptr;
		const PFNGLACTIVESHADERPROGRAMPROC				glActiveShaderProgram				= nullptr;
		const PFNGLCREATESHADERPROGRAMVPROC				glCreateShaderProgramv				= nullptr;
		const PFNGLBINDPROGRAMPIPELINEPROC				glBindProgramPipeline				= nullptr;
		const PFNGLDELETEPROGRAMPIPELINESPROC			glDeleteProgramPipelines			= nullptr;
		const PFNGLGENPROGRAMPIPELINESPROC				glGenProgramPipelines				= nullptr;
		const PFNGLISPROGRAMPIPELINEPROC				glIsProgramPipeline					= nullptr;
		const PFNGLGETPROGRAMPIPELINEIVPROC				glGetProgramPipelineiv				= nullptr;
		const PFNGLPROGRAMUNIFORM1IPROC					glProgramUniform1i					= nullptr;
		const PFNGLPROGRAMUNIFORM1IVPROC				glProgramUniform1iv					= nullptr;
		const PFNGLPROGRAMUNIFORM1FPROC					glProgramUniform1f					= nullptr;
		const PFNGLPROGRAMUNIFORM1FVPROC				glProgramUniform1fv					= nullptr;
		const PFNGLPROGRAMUNIFORM1DPROC					glProgramUniform1d					= nullptr;
		const PFNGLPROGRAMUNIFORM1DVPROC				glProgramUniform1dv					= nullptr;
		const PFNGLPROGRAMUNIFORM1UIPROC				glProgramUniform1ui					= nullptr;
		const PFNGLPROGRAMUNIFORM1UIVPROC				glProgramUniform1uiv				= nullptr;
		const PFNGLPROGRAMUNIFORM2IPROC					glProgramUniform2i					= nullptr;
		const PFNGLPROGRAMUNIFORM2IVPROC				glProgramUniform2iv					= nullptr;
		const PFNGLPROGRAMUNIFORM2FPROC					glProgramUniform2f					= nullptr;
		const PFNGLPROGRAMUNIFORM2FVPROC				glProgramUniform2fv					= nullptr;
		const PFNGLPROGRAMUNIFORM2DPROC					glProgramUniform2d					= nullptr;
		const PFNGLPROGRAMUNIFORM2DVPROC				glProgramUniform2dv					= nullptr;
		const PFNGLPROGRAMUNIFORM2UIPROC				glProgramUniform2ui					= nullptr;
		const PFNGLPROGRAMUNIFORM2UIVPROC				glProgramUniform2uiv				= nullptr;
		const PFNGLPROGRAMUNIFORM3IPROC					glProgramUniform3i					= nullptr;
		const PFNGLPROGRAMUNIFORM3IVPROC				glProgramUniform3iv					= nullptr;
		const PFNGLPROGRAMUNIFORM3FPROC					glProgramUniform3f					= nullptr;
		const PFNGLPROGRAMUNIFORM3FVPROC				glProgramUniform3fv					= nullptr;
		const PFNGLPROGRAMUNIFORM3DPROC					glProgramUniform3d					= nullptr;
		const PFNGLPROGRAMUNIFORM3DVPROC				glProgramUniform3dv					= nullptr;
		const PFNGLPROGRAMUNIFORM3UIPROC				glProgramUniform3ui					= nullptr;
		const PFNGLPROGRAMUNIFORM3UIVPROC				glProgramUniform3uiv				= nullptr;
		const PFNGLPROGRAMUNIFORM4IPROC					glProgramUniform4i					= nullptr;
		const PFNGLPROGRAMUNIFORM4IVPROC				glProgramUniform4iv					= nullptr;
		const PFNGLPROGRAMUNIFORM4FPROC					glProgramUniform4f					= nullptr;
		const PFNGLPROGRAMUNIFORM4FVPROC				glProgramUniform4fv					= nullptr;
		const PFNGLPROGRAMUNIFORM4DPROC					glProgramUniform4d					= nullptr;
		const PFNGLPROGRAMUNIFORM4DVPROC				glProgramUniform4dv					= nullptr;
		const PFNGLPROGRAMUNIFORM4UIPROC				glProgramUniform4ui					= nullptr;
		const PFNGLPROGRAMUNIFORM4UIVPROC				glProgramUniform4uiv				= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX2FVPROC			glProgramUniformMatrix2fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX3FVPROC			glProgramUniformMatrix3fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX4FVPROC			glProgramUniformMatrix4fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX2DVPROC			glProgramUniformMatrix2dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX3DVPROC			glProgramUniformMatrix3dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX4DVPROC			glProgramUniformMatrix4dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC		glProgramUniformMatrix2x3fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC		glProgramUniformMatrix3x2fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC		glProgramUniformMatrix2x4fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC		glProgramUniformMatrix4x2fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC		glProgramUniformMatrix3x4fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC		glProgramUniformMatrix4x3fv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC		glProgramUniformMatrix2x3dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC		glProgramUniformMatrix3x2dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC		glProgramUniformMatrix2x4dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC		glProgramUniformMatrix4x2dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC		glProgramUniformMatrix3x4dv			= nullptr;
		const PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC		glProgramUniformMatrix4x3dv			= nullptr;
		const PFNGLVALIDATEPROGRAMPIPELINEPROC			glValidateProgramPipeline			= nullptr;
		const PFNGLGETPROGRAMPIPELINEINFOLOGPROC		glGetProgramPipelineInfoLog			= nullptr;
		const PFNGLVERTEXATTRIBL1DPROC					glVertexAttribL1d					= nullptr;
		const PFNGLVERTEXATTRIBL2DPROC					glVertexAttribL2d					= nullptr;
		const PFNGLVERTEXATTRIBL3DPROC					glVertexAttribL3d					= nullptr;
		const PFNGLVERTEXATTRIBL4DPROC					glVertexAttribL4d					= nullptr;
		const PFNGLVERTEXATTRIBL1DVPROC					glVertexAttribL1dv					= nullptr;
		const PFNGLVERTEXATTRIBL2DVPROC					glVertexAttribL2dv					= nullptr;
		const PFNGLVERTEXATTRIBL3DVPROC					glVertexAttribL3dv					= nullptr;
		const PFNGLVERTEXATTRIBL4DVPROC					glVertexAttribL4dv					= nullptr;
		const PFNGLVERTEXATTRIBLPOINTERPROC				glVertexAttribLPointer				= nullptr;
		const PFNGLGETVERTEXATTRIBLDVPROC				glGetVertexAttribLdv				= nullptr;
		const PFNGLVIEWPORTARRAYVPROC					glViewportArrayv					= nullptr;
		const PFNGLVIEWPORTINDEXEDFPROC					glViewportIndexedf					= nullptr;
		const PFNGLVIEWPORTINDEXEDFVPROC				glViewportIndexedfv					= nullptr;
		const PFNGLSCISSORARRAYVPROC					glScissorArrayv						= nullptr;
		const PFNGLSCISSORINDEXEDPROC					glScissorIndexed					= nullptr;
		const PFNGLSCISSORINDEXEDVPROC					glScissorIndexedv					= nullptr;
		const PFNGLDEPTHRANGEARRAYVPROC					glDepthRangeArrayv					= nullptr;
		const PFNGLDEPTHRANGEINDEXEDPROC				glDepthRangeIndexed					= nullptr;
		const PFNGLGETFLOATI_VPROC						glGetFloati_v						= nullptr;
		const PFNGLGETDOUBLEI_VPROC						glGetDoublei_v						= nullptr;
	protected:
		inline Interface_4_1() = default;
		inline Interface_4_1(
			const PFNGLRELEASESHADERCOMPILERPROC&			glReleaseShaderCompiler_,
			const PFNGLSHADERBINARYPROC&					glShaderBinary_,	
			const PFNGLGETSHADERPRECISIONFORMATPROC&		glGetShaderPrecisionFormat_,	
			const PFNGLDEPTHRANGEFPROC&						glDepthRangef_,
			const PFNGLCLEARDEPTHFPROC&						glClearDepthf_,
			const PFNGLGETPROGRAMBINARYPROC&				glGetProgramBinary_,	
			const PFNGLPROGRAMBINARYPROC&					glProgramBinary_,
			const PFNGLPROGRAMPARAMETERIPROC&				glProgramParameteri_,
			const PFNGLUSEPROGRAMSTAGESPROC&				glUseProgramStages_,	
			const PFNGLACTIVESHADERPROGRAMPROC&				glActiveShaderProgram_,
			const PFNGLCREATESHADERPROGRAMVPROC&			glCreateShaderProgramv_,	
			const PFNGLBINDPROGRAMPIPELINEPROC&				glBindProgramPipeline_,
			const PFNGLDELETEPROGRAMPIPELINESPROC&			glDeleteProgramPipelines_,
			const PFNGLGENPROGRAMPIPELINESPROC&				glGenProgramPipelines_,
			const PFNGLISPROGRAMPIPELINEPROC&				glIsProgramPipeline_,
			const PFNGLGETPROGRAMPIPELINEIVPROC&			glGetProgramPipelineiv_,	
			const PFNGLPROGRAMUNIFORM1IPROC&				glProgramUniform1i_,	
			const PFNGLPROGRAMUNIFORM1IVPROC&				glProgramUniform1iv_,
			const PFNGLPROGRAMUNIFORM1FPROC&				glProgramUniform1f_,	
			const PFNGLPROGRAMUNIFORM1FVPROC&				glProgramUniform1fv_,
			const PFNGLPROGRAMUNIFORM1DPROC&				glProgramUniform1d_,	
			const PFNGLPROGRAMUNIFORM1DVPROC&				glProgramUniform1dv_,
			const PFNGLPROGRAMUNIFORM1UIPROC&				glProgramUniform1ui_,
			const PFNGLPROGRAMUNIFORM1UIVPROC&				glProgramUniform1uiv_,
			const PFNGLPROGRAMUNIFORM2IPROC&				glProgramUniform2i_,	
			const PFNGLPROGRAMUNIFORM2IVPROC&				glProgramUniform2iv_,
			const PFNGLPROGRAMUNIFORM2FPROC&				glProgramUniform2f_,	
			const PFNGLPROGRAMUNIFORM2FVPROC&				glProgramUniform2fv_,
			const PFNGLPROGRAMUNIFORM2DPROC&				glProgramUniform2d_,	
			const PFNGLPROGRAMUNIFORM2DVPROC&				glProgramUniform2dv_,
			const PFNGLPROGRAMUNIFORM2UIPROC&				glProgramUniform2ui_,
			const PFNGLPROGRAMUNIFORM2UIVPROC&				glProgramUniform2uiv_,
			const PFNGLPROGRAMUNIFORM3IPROC&				glProgramUniform3i_,	
			const PFNGLPROGRAMUNIFORM3IVPROC&				glProgramUniform3iv_,
			const PFNGLPROGRAMUNIFORM3FPROC&				glProgramUniform3f_,	
			const PFNGLPROGRAMUNIFORM3FVPROC&				glProgramUniform3fv_,
			const PFNGLPROGRAMUNIFORM3DPROC&				glProgramUniform3d_,	
			const PFNGLPROGRAMUNIFORM3DVPROC&				glProgramUniform3dv_,
			const PFNGLPROGRAMUNIFORM3UIPROC&				glProgramUniform3ui_,
			const PFNGLPROGRAMUNIFORM3UIVPROC&				glProgramUniform3uiv_,
			const PFNGLPROGRAMUNIFORM4IPROC&				glProgramUniform4i_,	
			const PFNGLPROGRAMUNIFORM4IVPROC&				glProgramUniform4iv_,
			const PFNGLPROGRAMUNIFORM4FPROC&				glProgramUniform4f_,	
			const PFNGLPROGRAMUNIFORM4FVPROC&				glProgramUniform4fv_,
			const PFNGLPROGRAMUNIFORM4DPROC&				glProgramUniform4d_,	
			const PFNGLPROGRAMUNIFORM4DVPROC&				glProgramUniform4dv_,
			const PFNGLPROGRAMUNIFORM4UIPROC&				glProgramUniform4ui_,
			const PFNGLPROGRAMUNIFORM4UIVPROC&				glProgramUniform4uiv_,
			const PFNGLPROGRAMUNIFORMMATRIX2FVPROC&			glProgramUniformMatrix2fv_,
			const PFNGLPROGRAMUNIFORMMATRIX3FVPROC&			glProgramUniformMatrix3fv_,
			const PFNGLPROGRAMUNIFORMMATRIX4FVPROC&			glProgramUniformMatrix4fv_,
			const PFNGLPROGRAMUNIFORMMATRIX2DVPROC&			glProgramUniformMatrix2dv_,
			const PFNGLPROGRAMUNIFORMMATRIX3DVPROC&			glProgramUniformMatrix3dv_,
			const PFNGLPROGRAMUNIFORMMATRIX4DVPROC&			glProgramUniformMatrix4dv_,
			const PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC&		glProgramUniformMatrix2x3fv_,
			const PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC&		glProgramUniformMatrix3x2fv_,
			const PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC&		glProgramUniformMatrix2x4fv_,
			const PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC&		glProgramUniformMatrix4x2fv_,
			const PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC&		glProgramUniformMatrix3x4fv_,
			const PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC&		glProgramUniformMatrix4x3fv_,
			const PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC&		glProgramUniformMatrix2x3dv_,
			const PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC&		glProgramUniformMatrix3x2dv_,
			const PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC&		glProgramUniformMatrix2x4dv_,
			const PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC&		glProgramUniformMatrix4x2dv_,
			const PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC&		glProgramUniformMatrix3x4dv_,
			const PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC&		glProgramUniformMatrix4x3dv_,
			const PFNGLVALIDATEPROGRAMPIPELINEPROC&			glValidateProgramPipeline_,
			const PFNGLGETPROGRAMPIPELINEINFOLOGPROC&		glGetProgramPipelineInfoLog_,
			const PFNGLVERTEXATTRIBL1DPROC&					glVertexAttribL1d_,
			const PFNGLVERTEXATTRIBL2DPROC&					glVertexAttribL2d_,
			const PFNGLVERTEXATTRIBL3DPROC&					glVertexAttribL3d_,
			const PFNGLVERTEXATTRIBL4DPROC&					glVertexAttribL4d_,
			const PFNGLVERTEXATTRIBL1DVPROC&				glVertexAttribL1dv_,	
			const PFNGLVERTEXATTRIBL2DVPROC&				glVertexAttribL2dv_,	
			const PFNGLVERTEXATTRIBL3DVPROC&				glVertexAttribL3dv_,	
			const PFNGLVERTEXATTRIBL4DVPROC&				glVertexAttribL4dv_,	
			const PFNGLVERTEXATTRIBLPOINTERPROC&			glVertexAttribLPointer_,	
			const PFNGLGETVERTEXATTRIBLDVPROC&				glGetVertexAttribLdv_,
			const PFNGLVIEWPORTARRAYVPROC&					glViewportArrayv_,
			const PFNGLVIEWPORTINDEXEDFPROC&				glViewportIndexedf_,	
			const PFNGLVIEWPORTINDEXEDFVPROC&				glViewportIndexedfv_,
			const PFNGLSCISSORARRAYVPROC&					glScissorArrayv_,
			const PFNGLSCISSORINDEXEDPROC&					glScissorIndexed_,
			const PFNGLSCISSORINDEXEDVPROC&					glScissorIndexedv_,
			const PFNGLDEPTHRANGEARRAYVPROC&				glDepthRangeArrayv_,
			const PFNGLDEPTHRANGEINDEXEDPROC&				glDepthRangeIndexed_,
			const PFNGLGETFLOATI_VPROC&						glGetFloati_v_,
			const PFNGLGETDOUBLEI_VPROC&					glGetDoublei_v_
		);
	};
	class Interface_4_2:
		public virtual Interface
	{
	protected:
		const PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC				glDrawArraysInstancedBaseInstance				= nullptr;
		const PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC			glDrawElementsInstancedBaseInstance				= nullptr;
		const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC	glDrawElementsInstancedBaseVertexBaseInstance	= nullptr;
		const PFNGLGETINTERNALFORMATIVPROC							glGetInternalformativ							= nullptr;
		const PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC				glGetActiveAtomicCounterBufferiv				= nullptr;
		const PFNGLBINDIMAGETEXTUREPROC								glBindImageTexture								= nullptr;
		const PFNGLMEMORYBARRIERPROC								glMemoryBarrier									= nullptr;
		const PFNGLTEXSTORAGE1DPROC									glTexStorage1D									= nullptr;
		const PFNGLTEXSTORAGE2DPROC									glTexStorage2D									= nullptr;
		const PFNGLTEXSTORAGE3DPROC									glTexStorage3D									= nullptr;
		const PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC				glDrawTransformFeedbackInstanced				= nullptr;
		const PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC			glDrawTransformFeedbackStreamInstanced			= nullptr;
	protected:
		inline Interface_4_2() = default;
		inline Interface_4_2(
			const PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC&				glDrawArraysInstancedBaseInstance_,
			const PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC&			glDrawElementsInstancedBaseInstance_,
			const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC&	glDrawElementsInstancedBaseVertexBaseInstance_,
			const PFNGLGETINTERNALFORMATIVPROC&							glGetInternalformativ_,
			const PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC&				glGetActiveAtomicCounterBufferiv_,
			const PFNGLBINDIMAGETEXTUREPROC&							glBindImageTexture_,
			const PFNGLMEMORYBARRIERPROC&								glMemoryBarrier_,
			const PFNGLTEXSTORAGE1DPROC&								glTexStorage1D_,
			const PFNGLTEXSTORAGE2DPROC&								glTexStorage2D_,
			const PFNGLTEXSTORAGE3DPROC&								glTexStorage3D_,
			const PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC&				glDrawTransformFeedbackInstanced_,
			const PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC&		glDrawTransformFeedbackStreamInstanced_
		);
	};
	class Interface_4_3:
		public virtual Interface
	{
	protected:
		const PFNGLCLEARBUFFERDATAPROC						glClearBufferData					= nullptr;
		const PFNGLCLEARBUFFERSUBDATAPROC					glClearBufferSubData				= nullptr;
		const PFNGLDISPATCHCOMPUTEPROC						glDispatchCompute					= nullptr;
		const PFNGLDISPATCHCOMPUTEINDIRECTPROC				glDispatchComputeIndirect			= nullptr;
		const PFNGLCOPYIMAGESUBDATAPROC						glCopyImageSubData					= nullptr;
		const PFNGLFRAMEBUFFERPARAMETERIPROC				glFramebufferParameteri				= nullptr;
		const PFNGLGETFRAMEBUFFERPARAMETERIVPROC			glGetFramebufferParameteriv			= nullptr;
		const PFNGLGETINTERNALFORMATI64VPROC				glGetInternalformati64v				= nullptr;
		const PFNGLINVALIDATETEXSUBIMAGEPROC				glInvalidateTexSubImage				= nullptr;
		const PFNGLINVALIDATETEXIMAGEPROC					glInvalidateTexImage				= nullptr;
		const PFNGLINVALIDATEBUFFERSUBDATAPROC				glInvalidateBufferSubData			= nullptr;
		const PFNGLINVALIDATEBUFFERDATAPROC					glInvalidateBufferData				= nullptr;
		const PFNGLINVALIDATEFRAMEBUFFERPROC				glInvalidateFramebuffer				= nullptr;
		const PFNGLINVALIDATESUBFRAMEBUFFERPROC				glInvalidateSubFramebuffer			= nullptr;
		const PFNGLMULTIDRAWARRAYSINDIRECTPROC				glMultiDrawArraysIndirect			= nullptr;
		const PFNGLMULTIDRAWELEMENTSINDIRECTPROC			glMultiDrawElementsIndirect			= nullptr;
		const PFNGLGETPROGRAMINTERFACEIVPROC				glGetProgramInterfaceiv				= nullptr;
		const PFNGLGETPROGRAMRESOURCEINDEXPROC				glGetProgramResourceIndex			= nullptr;
		const PFNGLGETPROGRAMRESOURCENAMEPROC				glGetProgramResourceName			= nullptr;
		const PFNGLGETPROGRAMRESOURCEIVPROC					glGetProgramResourceiv				= nullptr;
		const PFNGLGETPROGRAMRESOURCELOCATIONPROC			glGetProgramResourceLocation		= nullptr;
		const PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC		glGetProgramResourceLocationIndex	= nullptr;
		const PFNGLSHADERSTORAGEBLOCKBINDINGPROC			glShaderStorageBlockBinding			= nullptr;
		const PFNGLTEXBUFFERRANGEPROC						glTexBufferRange					= nullptr;
		const PFNGLTEXSTORAGE2DMULTISAMPLEPROC				glTexStorage2DMultisample			= nullptr;
		const PFNGLTEXSTORAGE3DMULTISAMPLEPROC				glTexStorage3DMultisample			= nullptr;
		const PFNGLTEXTUREVIEWPROC							glTextureView						= nullptr;
		const PFNGLBINDVERTEXBUFFERPROC						glBindVertexBuffer					= nullptr;
		const PFNGLVERTEXATTRIBFORMATPROC					glVertexAttribFormat				= nullptr;
		const PFNGLVERTEXATTRIBIFORMATPROC					glVertexAttribIFormat				= nullptr;
		const PFNGLVERTEXATTRIBLFORMATPROC					glVertexAttribLFormat				= nullptr;
		const PFNGLVERTEXATTRIBBINDINGPROC					glVertexAttribBinding				= nullptr;
		const PFNGLVERTEXBINDINGDIVISORPROC					glVertexBindingDivisor				= nullptr;
		const PFNGLDEBUGMESSAGECONTROLPROC					glDebugMessageControl				= nullptr;
		const PFNGLDEBUGMESSAGEINSERTPROC					glDebugMessageInsert				= nullptr;
		const PFNGLDEBUGMESSAGECALLBACKPROC					glDebugMessageCallback				= nullptr;
		const PFNGLGETDEBUGMESSAGELOGPROC					glGetDebugMessageLog				= nullptr;
		const PFNGLPUSHDEBUGGROUPPROC						glPushDebugGroup					= nullptr;
		const PFNGLPOPDEBUGGROUPPROC						glPopDebugGroup						= nullptr;
		const PFNGLOBJECTLABELPROC							glObjectLabel						= nullptr;
		const PFNGLGETOBJECTLABELPROC						glGetObjectLabel					= nullptr;
		const PFNGLOBJECTPTRLABELPROC						glObjectPtrLabel					= nullptr;
		const PFNGLGETOBJECTPTRLABELPROC					glGetObjectPtrLabel					= nullptr;
	protected:
		inline Interface_4_3() = default;
		inline Interface_4_3(
			const PFNGLCLEARBUFFERDATAPROC&						glClearBufferData_,
			const PFNGLCLEARBUFFERSUBDATAPROC&					glClearBufferSubData_,
			const PFNGLDISPATCHCOMPUTEPROC&						glDispatchCompute_,
			const PFNGLDISPATCHCOMPUTEINDIRECTPROC&				glDispatchComputeIndirect_,
			const PFNGLCOPYIMAGESUBDATAPROC&					glCopyImageSubData_,
			const PFNGLFRAMEBUFFERPARAMETERIPROC&				glFramebufferParameteri_,
			const PFNGLGETFRAMEBUFFERPARAMETERIVPROC&			glGetFramebufferParameteriv_,
			const PFNGLGETINTERNALFORMATI64VPROC&				glGetInternalformati64v_,
			const PFNGLINVALIDATETEXSUBIMAGEPROC&				glInvalidateTexSubImage_,
			const PFNGLINVALIDATETEXIMAGEPROC&					glInvalidateTexImage_,
			const PFNGLINVALIDATEBUFFERSUBDATAPROC&				glInvalidateBufferSubData_,
			const PFNGLINVALIDATEBUFFERDATAPROC&				glInvalidateBufferData_,
			const PFNGLINVALIDATEFRAMEBUFFERPROC&				glInvalidateFramebuffer_,
			const PFNGLINVALIDATESUBFRAMEBUFFERPROC&			glInvalidateSubFramebuffer_,
			const PFNGLMULTIDRAWARRAYSINDIRECTPROC&				glMultiDrawArraysIndirect_,
			const PFNGLMULTIDRAWELEMENTSINDIRECTPROC&			glMultiDrawElementsIndirect_,
			const PFNGLGETPROGRAMINTERFACEIVPROC&				glGetProgramInterfaceiv_,
			const PFNGLGETPROGRAMRESOURCEINDEXPROC&				glGetProgramResourceIndex_,
			const PFNGLGETPROGRAMRESOURCENAMEPROC&				glGetProgramResourceName_,
			const PFNGLGETPROGRAMRESOURCEIVPROC&				glGetProgramResourceiv_,
			const PFNGLGETPROGRAMRESOURCELOCATIONPROC&			glGetProgramResourceLocation_,
			const PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC&		glGetProgramResourceLocationIndex_,
			const PFNGLSHADERSTORAGEBLOCKBINDINGPROC&			glShaderStorageBlockBinding_,
			const PFNGLTEXBUFFERRANGEPROC&						glTexBufferRange_,
			const PFNGLTEXSTORAGE2DMULTISAMPLEPROC&				glTexStorage2DMultisample_,
			const PFNGLTEXSTORAGE3DMULTISAMPLEPROC&				glTexStorage3DMultisample_,
			const PFNGLTEXTUREVIEWPROC&							glTextureView_,
			const PFNGLBINDVERTEXBUFFERPROC&					glBindVertexBuffer_,
			const PFNGLVERTEXATTRIBFORMATPROC&					glVertexAttribFormat_,
			const PFNGLVERTEXATTRIBIFORMATPROC&					glVertexAttribIFormat_,
			const PFNGLVERTEXATTRIBLFORMATPROC&					glVertexAttribLFormat_,
			const PFNGLVERTEXATTRIBBINDINGPROC&					glVertexAttribBinding_,
			const PFNGLVERTEXBINDINGDIVISORPROC&				glVertexBindingDivisor_,
			const PFNGLDEBUGMESSAGECONTROLPROC&					glDebugMessageControl_,
			const PFNGLDEBUGMESSAGEINSERTPROC&					glDebugMessageInsert_,
			const PFNGLDEBUGMESSAGECALLBACKPROC&				glDebugMessageCallback_,
			const PFNGLGETDEBUGMESSAGELOGPROC&					glGetDebugMessageLog_,
			const PFNGLPUSHDEBUGGROUPPROC&						glPushDebugGroup_,
			const PFNGLPOPDEBUGGROUPPROC&						glPopDebugGroup_,
			const PFNGLOBJECTLABELPROC&							glObjectLabel_,
			const PFNGLGETOBJECTLABELPROC&						glGetObjectLabel_,
			const PFNGLOBJECTPTRLABELPROC&						glObjectPtrLabel_,
			const PFNGLGETOBJECTPTRLABELPROC&					glGetObjectPtrLabel_
		);
	};
	class Interface_4_4:
		public virtual Interface
	{
	protected:
		const PFNGLBUFFERSTORAGEPROC		glBufferStorage		= nullptr;
		const PFNGLCLEARTEXIMAGEPROC		glClearTexImage		= nullptr;
		const PFNGLCLEARTEXSUBIMAGEPROC		glClearTexSubImage	= nullptr;
		const PFNGLBINDBUFFERSBASEPROC		glBindBuffersBase	= nullptr;
		const PFNGLBINDBUFFERSRANGEPROC		glBindBuffersRange	= nullptr;
		const PFNGLBINDTEXTURESPROC			glBindTextures		= nullptr;
		const PFNGLBINDSAMPLERSPROC			glBindSamplers		= nullptr;
		const PFNGLBINDIMAGETEXTURESPROC	glBindImageTextures	= nullptr;
		const PFNGLBINDVERTEXBUFFERSPROC	glBindVertexBuffers	= nullptr;
	protected:
		inline Interface_4_4() = default;
		inline Interface_4_4(
			const PFNGLBUFFERSTORAGEPROC&		glBufferStorage_,
			const PFNGLCLEARTEXIMAGEPROC&		glClearTexImage_,
			const PFNGLCLEARTEXSUBIMAGEPROC&	glClearTexSubImage_,
			const PFNGLBINDBUFFERSBASEPROC&		glBindBuffersBase_,
			const PFNGLBINDBUFFERSRANGEPROC&	glBindBuffersRange_,
			const PFNGLBINDTEXTURESPROC&		glBindTextures_,
			const PFNGLBINDSAMPLERSPROC&		glBindSamplers_,
			const PFNGLBINDIMAGETEXTURESPROC&	glBindImageTextures_,
			const PFNGLBINDVERTEXBUFFERSPROC&	glBindVertexBuffers_
		);
	};
	class Interface_4_5:
		public virtual Interface
	{
	protected:
		const PFNGLCLIPCONTROLPROC									glClipControl									= nullptr;
		const PFNGLCREATETRANSFORMFEEDBACKSPROC						glCreateTransformFeedbacks						= nullptr;
		const PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC					glTransformFeedbackBufferBase					= nullptr;
		const PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC					glTransformFeedbackBufferRange					= nullptr;
		const PFNGLGETTRANSFORMFEEDBACKIVPROC						glGetTransformFeedbackiv						= nullptr;
		const PFNGLGETTRANSFORMFEEDBACKI_VPROC						glGetTransformFeedbacki_v						= nullptr;
		const PFNGLGETTRANSFORMFEEDBACKI64_VPROC					glGetTransformFeedbacki64_v						= nullptr;
		const PFNGLCREATEBUFFERSPROC								glCreateBuffers									= nullptr;
		const PFNGLNAMEDBUFFERSTORAGEPROC							glNamedBufferStorage							= nullptr;
		const PFNGLNAMEDBUFFERDATAPROC								glNamedBufferData								= nullptr;
		const PFNGLNAMEDBUFFERSUBDATAPROC							glNamedBufferSubData							= nullptr;
		const PFNGLCOPYNAMEDBUFFERSUBDATAPROC						glCopyNamedBufferSubData						= nullptr;
		const PFNGLCLEARNAMEDBUFFERDATAPROC							glClearNamedBufferData							= nullptr;
		const PFNGLCLEARNAMEDBUFFERSUBDATAPROC						glClearNamedBufferSubData						= nullptr;
		const PFNGLMAPNAMEDBUFFERPROC								glMapNamedBuffer								= nullptr;
		const PFNGLMAPNAMEDBUFFERRANGEPROC							glMapNamedBufferRange							= nullptr;
		const PFNGLUNMAPNAMEDBUFFERPROC								glUnmapNamedBuffer								= nullptr;
		const PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC					glFlushMappedNamedBufferRange					= nullptr;
		const PFNGLGETNAMEDBUFFERPARAMETERIVPROC					glGetNamedBufferParameteriv						= nullptr;
		const PFNGLGETNAMEDBUFFERPARAMETERI64VPROC					glGetNamedBufferParameteri64v					= nullptr;
		const PFNGLGETNAMEDBUFFERPOINTERVPROC						glGetNamedBufferPointerv						= nullptr;
		const PFNGLGETNAMEDBUFFERSUBDATAPROC						glGetNamedBufferSubData							= nullptr;
		const PFNGLCREATEFRAMEBUFFERSPROC							glCreateFramebuffers							= nullptr;
		const PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC					glNamedFramebufferRenderbuffer					= nullptr;
		const PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC					glNamedFramebufferParameteri					= nullptr;
		const PFNGLNAMEDFRAMEBUFFERTEXTUREPROC						glNamedFramebufferTexture						= nullptr;
		const PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC					glNamedFramebufferTextureLayer					= nullptr;
		const PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC					glNamedFramebufferDrawBuffer					= nullptr;
		const PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC					glNamedFramebufferDrawBuffers					= nullptr;
		const PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC					glNamedFramebufferReadBuffer					= nullptr;
		const PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC				glInvalidateNamedFramebufferData				= nullptr;
		const PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC			glInvalidateNamedFramebufferSubData				= nullptr;
		const PFNGLCLEARNAMEDFRAMEBUFFERIVPROC						glClearNamedFramebufferiv						= nullptr;
		const PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC						glClearNamedFramebufferuiv						= nullptr;
		const PFNGLCLEARNAMEDFRAMEBUFFERFVPROC						glClearNamedFramebufferfv						= nullptr;
		const PFNGLCLEARNAMEDFRAMEBUFFERFIPROC						glClearNamedFramebufferfi						= nullptr;
		const PFNGLBLITNAMEDFRAMEBUFFERPROC							glBlitNamedFramebuffer							= nullptr;
		const PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC					glCheckNamedFramebufferStatus					= nullptr;
		const PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC				glGetNamedFramebufferParameteriv				= nullptr;
		const PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC		glGetNamedFramebufferAttachmentParameteriv		= nullptr;
		const PFNGLCREATERENDERBUFFERSPROC							glCreateRenderbuffers							= nullptr;
		const PFNGLNAMEDRENDERBUFFERSTORAGEPROC						glNamedRenderbufferStorage						= nullptr;
		const PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC			glNamedRenderbufferStorageMultisample			= nullptr;
		const PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC				glGetNamedRenderbufferParameteriv				= nullptr;
		const PFNGLCREATETEXTURESPROC								glCreateTextures								= nullptr;
		const PFNGLTEXTUREBUFFERPROC								glTextureBuffer									= nullptr;
		const PFNGLTEXTUREBUFFERRANGEPROC							glTextureBufferRange							= nullptr;
		const PFNGLTEXTURESTORAGE1DPROC								glTextureStorage1D								= nullptr;
		const PFNGLTEXTURESTORAGE2DPROC								glTextureStorage2D								= nullptr;
		const PFNGLTEXTURESTORAGE3DPROC								glTextureStorage3D								= nullptr;
		const PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC					glTextureStorage2DMultisample					= nullptr;
		const PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC					glTextureStorage3DMultisample					= nullptr;
		const PFNGLTEXTURESUBIMAGE1DPROC							glTextureSubImage1D								= nullptr;
		const PFNGLTEXTURESUBIMAGE2DPROC							glTextureSubImage2D								= nullptr;
		const PFNGLTEXTURESUBIMAGE3DPROC							glTextureSubImage3D								= nullptr;
		const PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC					glCompressedTextureSubImage1D					= nullptr;
		const PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC					glCompressedTextureSubImage2D					= nullptr;
		const PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC					glCompressedTextureSubImage3D					= nullptr;
		const PFNGLCOPYTEXTURESUBIMAGE1DPROC						glCopyTextureSubImage1D							= nullptr;
		const PFNGLCOPYTEXTURESUBIMAGE2DPROC						glCopyTextureSubImage2D							= nullptr;
		const PFNGLCOPYTEXTURESUBIMAGE3DPROC						glCopyTextureSubImage3D							= nullptr;
		const PFNGLTEXTUREPARAMETERFPROC							glTextureParameterf								= nullptr;
		const PFNGLTEXTUREPARAMETERFVPROC							glTextureParameterfv							= nullptr;
		const PFNGLTEXTUREPARAMETERIPROC							glTextureParameteri								= nullptr;
		const PFNGLTEXTUREPARAMETERIIVPROC							glTextureParameterIiv							= nullptr;
		const PFNGLTEXTUREPARAMETERIUIVPROC							glTextureParameterIuiv							= nullptr;
		const PFNGLTEXTUREPARAMETERIVPROC							glTextureParameteriv							= nullptr;
		const PFNGLGENERATETEXTUREMIPMAPPROC						glGenerateTextureMipmap							= nullptr;
		const PFNGLBINDTEXTUREUNITPROC								glBindTextureUnit								= nullptr;
		const PFNGLGETTEXTUREIMAGEPROC								glGetTextureImage								= nullptr;
		const PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC					glGetCompressedTextureImage						= nullptr;
		const PFNGLGETTEXTURELEVELPARAMETERFVPROC					glGetTextureLevelParameterfv					= nullptr;
		const PFNGLGETTEXTURELEVELPARAMETERIVPROC					glGetTextureLevelParameteriv					= nullptr;
		const PFNGLGETTEXTUREPARAMETERFVPROC						glGetTextureParameterfv							= nullptr;
		const PFNGLGETTEXTUREPARAMETERIIVPROC						glGetTextureParameterIiv						= nullptr;
		const PFNGLGETTEXTUREPARAMETERIUIVPROC						glGetTextureParameterIuiv						= nullptr;
		const PFNGLGETTEXTUREPARAMETERIVPROC						glGetTextureParameteriv							= nullptr;
		const PFNGLCREATEVERTEXARRAYSPROC							glCreateVertexArrays							= nullptr;
		const PFNGLDISABLEVERTEXARRAYATTRIBPROC						glDisableVertexArrayAttrib						= nullptr;
		const PFNGLENABLEVERTEXARRAYATTRIBPROC						glEnableVertexArrayAttrib						= nullptr;
		const PFNGLVERTEXARRAYELEMENTBUFFERPROC						glVertexArrayElementBuffer						= nullptr;
		const PFNGLVERTEXARRAYVERTEXBUFFERPROC						glVertexArrayVertexBuffer						= nullptr;
		const PFNGLVERTEXARRAYVERTEXBUFFERSPROC						glVertexArrayVertexBuffers						= nullptr;
		const PFNGLVERTEXARRAYATTRIBBINDINGPROC						glVertexArrayAttribBinding						= nullptr;
		const PFNGLVERTEXARRAYATTRIBFORMATPROC						glVertexArrayAttribFormat						= nullptr;
		const PFNGLVERTEXARRAYATTRIBIFORMATPROC						glVertexArrayAttribIFormat						= nullptr;
		const PFNGLVERTEXARRAYATTRIBLFORMATPROC						glVertexArrayAttribLFormat						= nullptr;
		const PFNGLVERTEXARRAYBINDINGDIVISORPROC					glVertexArrayBindingDivisor						= nullptr;
		const PFNGLGETVERTEXARRAYIVPROC								glGetVertexArrayiv								= nullptr;
		const PFNGLGETVERTEXARRAYINDEXEDIVPROC						glGetVertexArrayIndexediv						= nullptr;
		const PFNGLGETVERTEXARRAYINDEXED64IVPROC					glGetVertexArrayIndexed64iv						= nullptr;
		const PFNGLCREATESAMPLERSPROC								glCreateSamplers								= nullptr;
		const PFNGLCREATEPROGRAMPIPELINESPROC						glCreateProgramPipelines						= nullptr;
		const PFNGLCREATEQUERIESPROC								glCreateQueries									= nullptr;
		const PFNGLGETQUERYBUFFEROBJECTI64VPROC						glGetQueryBufferObjecti64v						= nullptr;
		const PFNGLGETQUERYBUFFEROBJECTIVPROC						glGetQueryBufferObjectiv						= nullptr;
		const PFNGLGETQUERYBUFFEROBJECTUI64VPROC					glGetQueryBufferObjectui64v						= nullptr;
		const PFNGLGETQUERYBUFFEROBJECTUIVPROC						glGetQueryBufferObjectuiv						= nullptr;
		const PFNGLMEMORYBARRIERBYREGIONPROC						glMemoryBarrierByRegion							= nullptr;
		const PFNGLGETTEXTURESUBIMAGEPROC							glGetTextureSubImage							= nullptr;
		const PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC					glGetCompressedTextureSubImage					= nullptr;
		const PFNGLGETGRAPHICSRESETSTATUSPROC						glGetGraphicsResetStatus						= nullptr;
		const PFNGLGETNCOMPRESSEDTEXIMAGEPROC						glGetnCompressedTexImage						= nullptr;
		const PFNGLGETNTEXIMAGEPROC									glGetnTexImage									= nullptr;
		const PFNGLGETNUNIFORMDVPROC								glGetnUniformdv									= nullptr;
		const PFNGLGETNUNIFORMFVPROC								glGetnUniformfv									= nullptr;
		const PFNGLGETNUNIFORMIVPROC								glGetnUniformiv									= nullptr;
		const PFNGLGETNUNIFORMUIVPROC								glGetnUniformuiv								= nullptr;
		const PFNGLREADNPIXELSPROC									glReadnPixels									= nullptr;
		const PFNGLGETNMAPDVPROC									glGetnMapdv										= nullptr;
		const PFNGLGETNMAPFVPROC									glGetnMapfv										= nullptr;
		const PFNGLGETNMAPIVPROC									glGetnMapiv										= nullptr;
		const PFNGLGETNPIXELMAPFVPROC								glGetnPixelMapfv								= nullptr;
		const PFNGLGETNPIXELMAPUIVPROC								glGetnPixelMapuiv								= nullptr;
		const PFNGLGETNPIXELMAPUSVPROC								glGetnPixelMapusv								= nullptr;
		const PFNGLGETNPOLYGONSTIPPLEPROC							glGetnPolygonStipple							= nullptr;
		const PFNGLGETNCOLORTABLEPROC								glGetnColorTable								= nullptr;
		const PFNGLGETNCONVOLUTIONFILTERPROC						glGetnConvolutionFilter							= nullptr;
		const PFNGLGETNSEPARABLEFILTERPROC							glGetnSeparableFilter							= nullptr;
		const PFNGLGETNHISTOGRAMPROC								glGetnHistogram									= nullptr;
		const PFNGLGETNMINMAXPROC									glGetnMinmax									= nullptr;
		const PFNGLTEXTUREBARRIERPROC								glTextureBarrier								= nullptr;
	protected:
		inline Interface_4_5() = default;
		inline Interface_4_5(
			const PFNGLCLIPCONTROLPROC&									glClipControl_,
			const PFNGLCREATETRANSFORMFEEDBACKSPROC&					glCreateTransformFeedbacks_,
			const PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC&					glTransformFeedbackBufferBase_,
			const PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC&				glTransformFeedbackBufferRange_,
			const PFNGLGETTRANSFORMFEEDBACKIVPROC&						glGetTransformFeedbackiv_,
			const PFNGLGETTRANSFORMFEEDBACKI_VPROC&						glGetTransformFeedbacki_v_,
			const PFNGLGETTRANSFORMFEEDBACKI64_VPROC&					glGetTransformFeedbacki64_v_,
			const PFNGLCREATEBUFFERSPROC&								glCreateBuffers_,
			const PFNGLNAMEDBUFFERSTORAGEPROC&							glNamedBufferStorage_,
			const PFNGLNAMEDBUFFERDATAPROC&								glNamedBufferData_,
			const PFNGLNAMEDBUFFERSUBDATAPROC&							glNamedBufferSubData_,
			const PFNGLCOPYNAMEDBUFFERSUBDATAPROC&						glCopyNamedBufferSubData_,
			const PFNGLCLEARNAMEDBUFFERDATAPROC&						glClearNamedBufferData_,
			const PFNGLCLEARNAMEDBUFFERSUBDATAPROC&						glClearNamedBufferSubData_,
			const PFNGLMAPNAMEDBUFFERPROC&								glMapNamedBuffer_,
			const PFNGLMAPNAMEDBUFFERRANGEPROC&							glMapNamedBufferRange_,
			const PFNGLUNMAPNAMEDBUFFERPROC&							glUnmapNamedBuffer_,
			const PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC&					glFlushMappedNamedBufferRange_,
			const PFNGLGETNAMEDBUFFERPARAMETERIVPROC&					glGetNamedBufferParameteriv_,
			const PFNGLGETNAMEDBUFFERPARAMETERI64VPROC&					glGetNamedBufferParameteri64v_,
			const PFNGLGETNAMEDBUFFERPOINTERVPROC&						glGetNamedBufferPointerv_,
			const PFNGLGETNAMEDBUFFERSUBDATAPROC&						glGetNamedBufferSubData_,
			const PFNGLCREATEFRAMEBUFFERSPROC&							glCreateFramebuffers_,
			const PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC&				glNamedFramebufferRenderbuffer_,
			const PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC&					glNamedFramebufferParameteri_,
			const PFNGLNAMEDFRAMEBUFFERTEXTUREPROC&						glNamedFramebufferTexture_,
			const PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC&				glNamedFramebufferTextureLayer_,
			const PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC&					glNamedFramebufferDrawBuffer_,
			const PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC&					glNamedFramebufferDrawBuffers_,
			const PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC&					glNamedFramebufferReadBuffer_,
			const PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC&				glInvalidateNamedFramebufferData_,
			const PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC&			glInvalidateNamedFramebufferSubData_,
			const PFNGLCLEARNAMEDFRAMEBUFFERIVPROC&						glClearNamedFramebufferiv_,
			const PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC&					glClearNamedFramebufferuiv_,
			const PFNGLCLEARNAMEDFRAMEBUFFERFVPROC&						glClearNamedFramebufferfv_,
			const PFNGLCLEARNAMEDFRAMEBUFFERFIPROC&						glClearNamedFramebufferfi_,
			const PFNGLBLITNAMEDFRAMEBUFFERPROC&						glBlitNamedFramebuffer_,
			const PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC&					glCheckNamedFramebufferStatus_,
			const PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC&				glGetNamedFramebufferParameteriv_,
			const PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC&	glGetNamedFramebufferAttachmentParameteriv_,
			const PFNGLCREATERENDERBUFFERSPROC&							glCreateRenderbuffers_,
			const PFNGLNAMEDRENDERBUFFERSTORAGEPROC&					glNamedRenderbufferStorage_,
			const PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC&			glNamedRenderbufferStorageMultisample_,
			const PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC&				glGetNamedRenderbufferParameteriv_,
			const PFNGLCREATETEXTURESPROC&								glCreateTextures_,
			const PFNGLTEXTUREBUFFERPROC&								glTextureBuffer_,
			const PFNGLTEXTUREBUFFERRANGEPROC&							glTextureBufferRange_,
			const PFNGLTEXTURESTORAGE1DPROC&							glTextureStorage1D_,
			const PFNGLTEXTURESTORAGE2DPROC&							glTextureStorage2D_,
			const PFNGLTEXTURESTORAGE3DPROC&							glTextureStorage3D_,
			const PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC&					glTextureStorage2DMultisample_,
			const PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC&					glTextureStorage3DMultisample_,
			const PFNGLTEXTURESUBIMAGE1DPROC&							glTextureSubImage1D_,
			const PFNGLTEXTURESUBIMAGE2DPROC&							glTextureSubImage2D_,
			const PFNGLTEXTURESUBIMAGE3DPROC&							glTextureSubImage3D_,
			const PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC&					glCompressedTextureSubImage1D_,
			const PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC&					glCompressedTextureSubImage2D_,
			const PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC&					glCompressedTextureSubImage3D_,
			const PFNGLCOPYTEXTURESUBIMAGE1DPROC&						glCopyTextureSubImage1D_,
			const PFNGLCOPYTEXTURESUBIMAGE2DPROC&						glCopyTextureSubImage2D_,
			const PFNGLCOPYTEXTURESUBIMAGE3DPROC&						glCopyTextureSubImage3D_,
			const PFNGLTEXTUREPARAMETERFPROC&							glTextureParameterf_,
			const PFNGLTEXTUREPARAMETERFVPROC&							glTextureParameterfv_,
			const PFNGLTEXTUREPARAMETERIPROC&							glTextureParameteri_,
			const PFNGLTEXTUREPARAMETERIIVPROC&							glTextureParameterIiv_,
			const PFNGLTEXTUREPARAMETERIUIVPROC&						glTextureParameterIuiv_,
			const PFNGLTEXTUREPARAMETERIVPROC&							glTextureParameteriv_,
			const PFNGLGENERATETEXTUREMIPMAPPROC&						glGenerateTextureMipmap_,
			const PFNGLBINDTEXTUREUNITPROC&								glBindTextureUnit_,
			const PFNGLGETTEXTUREIMAGEPROC&								glGetTextureImage_,
			const PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC&					glGetCompressedTextureImage_,
			const PFNGLGETTEXTURELEVELPARAMETERFVPROC&					glGetTextureLevelParameterfv_,
			const PFNGLGETTEXTURELEVELPARAMETERIVPROC&					glGetTextureLevelParameteriv_,
			const PFNGLGETTEXTUREPARAMETERFVPROC&						glGetTextureParameterfv_,
			const PFNGLGETTEXTUREPARAMETERIIVPROC&						glGetTextureParameterIiv_,
			const PFNGLGETTEXTUREPARAMETERIUIVPROC&						glGetTextureParameterIuiv_,
			const PFNGLGETTEXTUREPARAMETERIVPROC&						glGetTextureParameteriv_,
			const PFNGLCREATEVERTEXARRAYSPROC&							glCreateVertexArrays_,
			const PFNGLDISABLEVERTEXARRAYATTRIBPROC&					glDisableVertexArrayAttrib_,
			const PFNGLENABLEVERTEXARRAYATTRIBPROC&						glEnableVertexArrayAttrib_,
			const PFNGLVERTEXARRAYELEMENTBUFFERPROC&					glVertexArrayElementBuffer_,
			const PFNGLVERTEXARRAYVERTEXBUFFERPROC&						glVertexArrayVertexBuffer_,
			const PFNGLVERTEXARRAYVERTEXBUFFERSPROC&					glVertexArrayVertexBuffers_,
			const PFNGLVERTEXARRAYATTRIBBINDINGPROC&					glVertexArrayAttribBinding_,
			const PFNGLVERTEXARRAYATTRIBFORMATPROC&						glVertexArrayAttribFormat_,
			const PFNGLVERTEXARRAYATTRIBIFORMATPROC&					glVertexArrayAttribIFormat_,
			const PFNGLVERTEXARRAYATTRIBLFORMATPROC&					glVertexArrayAttribLFormat_,
			const PFNGLVERTEXARRAYBINDINGDIVISORPROC&					glVertexArrayBindingDivisor_,
			const PFNGLGETVERTEXARRAYIVPROC&							glGetVertexArrayiv_,
			const PFNGLGETVERTEXARRAYINDEXEDIVPROC&						glGetVertexArrayIndexediv_,
			const PFNGLGETVERTEXARRAYINDEXED64IVPROC&					glGetVertexArrayIndexed64iv_,
			const PFNGLCREATESAMPLERSPROC&								glCreateSamplers_,
			const PFNGLCREATEPROGRAMPIPELINESPROC&						glCreateProgramPipelines_,
			const PFNGLCREATEQUERIESPROC&								glCreateQueries_,
			const PFNGLGETQUERYBUFFEROBJECTI64VPROC&					glGetQueryBufferObjecti64v_,
			const PFNGLGETQUERYBUFFEROBJECTIVPROC&						glGetQueryBufferObjectiv_,
			const PFNGLGETQUERYBUFFEROBJECTUI64VPROC&					glGetQueryBufferObjectui64v_,
			const PFNGLGETQUERYBUFFEROBJECTUIVPROC&						glGetQueryBufferObjectuiv_,
			const PFNGLMEMORYBARRIERBYREGIONPROC&						glMemoryBarrierByRegion_,
			const PFNGLGETTEXTURESUBIMAGEPROC&							glGetTextureSubImage_,
			const PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC&				glGetCompressedTextureSubImage_,
			const PFNGLGETGRAPHICSRESETSTATUSPROC&						glGetGraphicsResetStatus_,
			const PFNGLGETNCOMPRESSEDTEXIMAGEPROC&						glGetnCompressedTexImage_,
			const PFNGLGETNTEXIMAGEPROC&								glGetnTexImage_,
			const PFNGLGETNUNIFORMDVPROC&								glGetnUniformdv_,
			const PFNGLGETNUNIFORMFVPROC&								glGetnUniformfv_,
			const PFNGLGETNUNIFORMIVPROC&								glGetnUniformiv_,
			const PFNGLGETNUNIFORMUIVPROC&								glGetnUniformuiv_,
			const PFNGLREADNPIXELSPROC&									glReadnPixels_,
			const PFNGLGETNMAPDVPROC&									glGetnMapdv_,
			const PFNGLGETNMAPFVPROC&									glGetnMapfv_,
			const PFNGLGETNMAPIVPROC&									glGetnMapiv_,
			const PFNGLGETNPIXELMAPFVPROC&								glGetnPixelMapfv_,
			const PFNGLGETNPIXELMAPUIVPROC&								glGetnPixelMapuiv_,
			const PFNGLGETNPIXELMAPUSVPROC&								glGetnPixelMapusv_,
			const PFNGLGETNPOLYGONSTIPPLEPROC&							glGetnPolygonStipple_,
			const PFNGLGETNCOLORTABLEPROC&								glGetnColorTable_,
			const PFNGLGETNCONVOLUTIONFILTERPROC&						glGetnConvolutionFilter_,
			const PFNGLGETNSEPARABLEFILTERPROC&							glGetnSeparableFilter_,
			const PFNGLGETNHISTOGRAMPROC&								glGetnHistogram_,
			const PFNGLGETNMINMAXPROC&									glGetnMinmax_,
			const PFNGLTEXTUREBARRIERPROC&								glTextureBarrier_
		);
	};

#pragma region Interface
	void Interface::CheckForErrors() const
	{
		auto code = GetErrorCode();

		if (code != Error::Code::NoError)
		{
			throw Exception();
		}
	}
	
	Error::Code Interface::GetErrorCode() const
	{
		auto code = static_cast<Error::Code>(glGetError());

		return code;
	}
#pragma endregion
#pragma region Interface_1_0
	void Interface_1_0::ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const
	{
		glViewport(x_, y_, width_, height_);

		CheckForErrors();
	}
	void Interface_1_0::ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const
	{
		glClearColor(red_, green_, blue_, alpha_);

		CheckForErrors();
	}
	void Interface_1_0::Clear(const GLbitfield& mask_) const
	{
		glClear(mask_);

		CheckForErrors();
	}
	void Interface_1_0::DrawArrays(const PrimitiveType& primitiveType_, const Size& first_, const Size& count_)
	{
		glDrawArrays(static_cast<GLenum>(primitiveType_), first_, count_);

		CheckForErrors();
	}
	void Interface_1_0::Flush() const
	{
		glFlush();

		CheckForErrors();
	}
	void Interface_1_0::Finish() const
	{
		glFinish();

		CheckForErrors();
	}
#pragma endregion
#pragma region Interface_1_2
	Interface_1_2::Interface_1_2(
		const PFNGLDRAWRANGEELEMENTSPROC&	glDrawRangeElements_,
		const PFNGLTEXIMAGE3DPROC&			glTexImage3D_,
		const PFNGLTEXSUBIMAGE3DPROC&		glTexSubImage3D_,
		const PFNGLCOPYTEXSUBIMAGE3DPROC&	glCopyTexSubImage3D_
	):
		glDrawRangeElements		(glDrawRangeElements_	),
		glTexImage3D			(glTexImage3D_			),
		glTexSubImage3D			(glTexSubImage3D_		),
		glCopyTexSubImage3D		(glCopyTexSubImage3D_	)
	{
	}
#pragma endregion
#pragma region Interface_1_3
	Interface_1_3::Interface_1_3(
		const PFNGLACTIVETEXTUREPROC&			glActiveTexture_,
		const PFNGLSAMPLECOVERAGEPROC&			glSampleCoverage_,
		const PFNGLCOMPRESSEDTEXIMAGE3DPROC&	glCompressedTexImage3D_,
		const PFNGLCOMPRESSEDTEXIMAGE2DPROC&	glCompressedTexImage2D_,
		const PFNGLCOMPRESSEDTEXIMAGE1DPROC&	glCompressedTexImage1D_,
		const PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC&	glCompressedTexSubImage3D_,
		const PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC&	glCompressedTexSubImage2D_,
		const PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC&	glCompressedTexSubImage1D_,
		const PFNGLGETCOMPRESSEDTEXIMAGEPROC&	glGetCompressedTexImage_,
		const PFNGLCLIENTACTIVETEXTUREPROC&		glClientActiveTexture_,
		const PFNGLMULTITEXCOORD1DPROC&			glMultiTexCoord1d_,
		const PFNGLMULTITEXCOORD1DVPROC&		glMultiTexCoord1dv_,
		const PFNGLMULTITEXCOORD1FPROC&			glMultiTexCoord1f_,
		const PFNGLMULTITEXCOORD1FVPROC&		glMultiTexCoord1fv_,
		const PFNGLMULTITEXCOORD1IPROC&			glMultiTexCoord1i_,
		const PFNGLMULTITEXCOORD1IVPROC&		glMultiTexCoord1iv_,
		const PFNGLMULTITEXCOORD1SPROC&			glMultiTexCoord1s_,
		const PFNGLMULTITEXCOORD1SVPROC&		glMultiTexCoord1sv_,
		const PFNGLMULTITEXCOORD2DPROC&			glMultiTexCoord2d_,
		const PFNGLMULTITEXCOORD2DVPROC&		glMultiTexCoord2dv_,
		const PFNGLMULTITEXCOORD2FPROC&			glMultiTexCoord2f_,
		const PFNGLMULTITEXCOORD2FVPROC&		glMultiTexCoord2fv_,
		const PFNGLMULTITEXCOORD2IPROC&			glMultiTexCoord2i_,
		const PFNGLMULTITEXCOORD2IVPROC&		glMultiTexCoord2iv_,
		const PFNGLMULTITEXCOORD2SPROC&			glMultiTexCoord2s_,
		const PFNGLMULTITEXCOORD2SVPROC&		glMultiTexCoord2sv_,
		const PFNGLMULTITEXCOORD3DPROC&			glMultiTexCoord3d_,
		const PFNGLMULTITEXCOORD3DVPROC&		glMultiTexCoord3dv_,
		const PFNGLMULTITEXCOORD3FPROC&			glMultiTexCoord3f_,
		const PFNGLMULTITEXCOORD3FVPROC&		glMultiTexCoord3fv_,
		const PFNGLMULTITEXCOORD3IPROC&			glMultiTexCoord3i_,
		const PFNGLMULTITEXCOORD3IVPROC&		glMultiTexCoord3iv_,
		const PFNGLMULTITEXCOORD3SPROC&			glMultiTexCoord3s_,
		const PFNGLMULTITEXCOORD3SVPROC&		glMultiTexCoord3sv_,
		const PFNGLMULTITEXCOORD4DPROC&			glMultiTexCoord4d_,
		const PFNGLMULTITEXCOORD4DVPROC&		glMultiTexCoord4dv_,
		const PFNGLMULTITEXCOORD4FPROC&			glMultiTexCoord4f_,
		const PFNGLMULTITEXCOORD4FVPROC&		glMultiTexCoord4fv_,
		const PFNGLMULTITEXCOORD4IPROC&			glMultiTexCoord4i_,
		const PFNGLMULTITEXCOORD4IVPROC&		glMultiTexCoord4iv_,
		const PFNGLMULTITEXCOORD4SPROC&			glMultiTexCoord4s_,
		const PFNGLMULTITEXCOORD4SVPROC&		glMultiTexCoord4sv_,
		const PFNGLLOADTRANSPOSEMATRIXFPROC&	glLoadTransposeMatrixf_,
		const PFNGLLOADTRANSPOSEMATRIXDPROC&	glLoadTransposeMatrixd_,
		const PFNGLMULTTRANSPOSEMATRIXFPROC&	glMultTransposeMatrixf_,
		const PFNGLMULTTRANSPOSEMATRIXDPROC&	glMultTransposeMatrixd_
	):
		glActiveTexture					(glActiveTexture_),
		glSampleCoverage				(glSampleCoverage_),
		glCompressedTexImage3D			(glCompressedTexImage3D_),
		glCompressedTexImage2D			(glCompressedTexImage2D_),
		glCompressedTexImage1D			(glCompressedTexImage1D_),
		glCompressedTexSubImage3D		(glCompressedTexSubImage3D_),
		glCompressedTexSubImage2D		(glCompressedTexSubImage2D_),
		glCompressedTexSubImage1D		(glCompressedTexSubImage1D_),
		glGetCompressedTexImage			(glGetCompressedTexImage_),
		glClientActiveTexture			(glClientActiveTexture_),
		glMultiTexCoord1d				(glMultiTexCoord1d_),
		glMultiTexCoord1dv				(glMultiTexCoord1dv_),
		glMultiTexCoord1f				(glMultiTexCoord1f_),
		glMultiTexCoord1fv				(glMultiTexCoord1fv_),
		glMultiTexCoord1i				(glMultiTexCoord1i_),
		glMultiTexCoord1iv				(glMultiTexCoord1iv_),
		glMultiTexCoord1s				(glMultiTexCoord1s_),
		glMultiTexCoord1sv				(glMultiTexCoord1sv_),
		glMultiTexCoord2d				(glMultiTexCoord2d_),
		glMultiTexCoord2dv				(glMultiTexCoord2dv_),
		glMultiTexCoord2f				(glMultiTexCoord2f_),
		glMultiTexCoord2fv				(glMultiTexCoord2fv_),
		glMultiTexCoord2i				(glMultiTexCoord2i_),
		glMultiTexCoord2iv				(glMultiTexCoord2iv_),
		glMultiTexCoord2s				(glMultiTexCoord2s_),
		glMultiTexCoord2sv				(glMultiTexCoord2sv_),
		glMultiTexCoord3d				(glMultiTexCoord3d_),
		glMultiTexCoord3dv				(glMultiTexCoord3dv_),
		glMultiTexCoord3f				(glMultiTexCoord3f_),
		glMultiTexCoord3fv				(glMultiTexCoord3fv_),
		glMultiTexCoord3i				(glMultiTexCoord3i_),
		glMultiTexCoord3iv				(glMultiTexCoord3iv_),
		glMultiTexCoord3s				(glMultiTexCoord3s_),
		glMultiTexCoord3sv				(glMultiTexCoord3sv_),
		glMultiTexCoord4d				(glMultiTexCoord4d_),
		glMultiTexCoord4dv				(glMultiTexCoord4dv_),
		glMultiTexCoord4f				(glMultiTexCoord4f_),
		glMultiTexCoord4fv				(glMultiTexCoord4fv_),
		glMultiTexCoord4i				(glMultiTexCoord4i_),
		glMultiTexCoord4iv				(glMultiTexCoord4iv_),
		glMultiTexCoord4s				(glMultiTexCoord4s_),
		glMultiTexCoord4sv				(glMultiTexCoord4sv_),
		glLoadTransposeMatrixf			(glLoadTransposeMatrixf_),
		glLoadTransposeMatrixd			(glLoadTransposeMatrixd_),
		glMultTransposeMatrixf			(glMultTransposeMatrixf_),
		glMultTransposeMatrixd			(glMultTransposeMatrixd_)
	{
	}
#pragma endregion
#pragma region Interface_1_4
	Interface_1_4::Interface_1_4(
		const PFNGLBLENDFUNCSEPARATEPROC		glBlendFuncSeparate_,
		const PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays_,
		const PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements_,
		const PFNGLPOINTPARAMETERFPROC			glPointParameterf_,
		const PFNGLPOINTPARAMETERFVPROC			glPointParameterfv_,
		const PFNGLPOINTPARAMETERIPROC			glPointParameteri_,
		const PFNGLPOINTPARAMETERIVPROC			glPointParameteriv_,
		const PFNGLFOGCOORDFPROC				glFogCoordf_,
		const PFNGLFOGCOORDFVPROC				glFogCoordfv_,
		const PFNGLFOGCOORDDPROC				glFogCoordd_,
		const PFNGLFOGCOORDDVPROC				glFogCoorddv_,
		const PFNGLFOGCOORDPOINTERPROC			glFogCoordPointer_,
		const PFNGLSECONDARYCOLOR3BPROC			glSecondaryColor3b_,
		const PFNGLSECONDARYCOLOR3BVPROC		glSecondaryColor3bv_,
		const PFNGLSECONDARYCOLOR3DPROC			glSecondaryColor3d_,
		const PFNGLSECONDARYCOLOR3DVPROC		glSecondaryColor3dv_,
		const PFNGLSECONDARYCOLOR3FPROC			glSecondaryColor3f_,
		const PFNGLSECONDARYCOLOR3FVPROC		glSecondaryColor3fv_,
		const PFNGLSECONDARYCOLOR3IPROC			glSecondaryColor3i_,
		const PFNGLSECONDARYCOLOR3IVPROC		glSecondaryColor3iv_,
		const PFNGLSECONDARYCOLOR3SPROC			glSecondaryColor3s_,
		const PFNGLSECONDARYCOLOR3SVPROC		glSecondaryColor3sv_,
		const PFNGLSECONDARYCOLOR3UBPROC		glSecondaryColor3ub_,
		const PFNGLSECONDARYCOLOR3UBVPROC		glSecondaryColor3ubv_,
		const PFNGLSECONDARYCOLOR3UIPROC		glSecondaryColor3ui_,
		const PFNGLSECONDARYCOLOR3UIVPROC		glSecondaryColor3uiv_,
		const PFNGLSECONDARYCOLOR3USPROC		glSecondaryColor3us_,
		const PFNGLSECONDARYCOLOR3USVPROC		glSecondaryColor3usv_,
		const PFNGLSECONDARYCOLORPOINTERPROC	glSecondaryColorPointer_,
		const PFNGLWINDOWPOS2DPROC				glWindowPos2d_,
		const PFNGLWINDOWPOS2DVPROC				glWindowPos2dv_,
		const PFNGLWINDOWPOS2FPROC				glWindowPos2f_,
		const PFNGLWINDOWPOS2FVPROC				glWindowPos2fv_,
		const PFNGLWINDOWPOS2IPROC				glWindowPos2i_,
		const PFNGLWINDOWPOS2IVPROC				glWindowPos2iv_,
		const PFNGLWINDOWPOS2SPROC				glWindowPos2s_,
		const PFNGLWINDOWPOS2SVPROC				glWindowPos2sv_,
		const PFNGLWINDOWPOS3DPROC				glWindowPos3d_,
		const PFNGLWINDOWPOS3DVPROC				glWindowPos3dv_,
		const PFNGLWINDOWPOS3FPROC				glWindowPos3f_,
		const PFNGLWINDOWPOS3FVPROC				glWindowPos3fv_,
		const PFNGLWINDOWPOS3IPROC				glWindowPos3i_,
		const PFNGLWINDOWPOS3IVPROC				glWindowPos3iv_,
		const PFNGLWINDOWPOS3SPROC				glWindowPos3s_,
		const PFNGLWINDOWPOS3SVPROC				glWindowPos3sv_,
		const PFNGLBLENDCOLORPROC				glBlendColor_,
		const PFNGLBLENDEQUATIONPROC			glBlendEquation_
	):
		glBlendFuncSeparate		(glBlendFuncSeparate_),
		glMultiDrawArrays		(glMultiDrawArrays_),
		glMultiDrawElements		(glMultiDrawElements_),
		glPointParameterf		(glPointParameterf_),
		glPointParameterfv		(glPointParameterfv_),
		glPointParameteri		(glPointParameteri_),
		glPointParameteriv		(glPointParameteriv_),
		glFogCoordf				(glFogCoordf_),
		glFogCoordfv			(glFogCoordfv_),
		glFogCoordd				(glFogCoordd_),
		glFogCoorddv			(glFogCoorddv_),
		glFogCoordPointer		(glFogCoordPointer_),
		glSecondaryColor3b		(glSecondaryColor3b_),
		glSecondaryColor3bv		(glSecondaryColor3bv_),
		glSecondaryColor3d		(glSecondaryColor3d_),
		glSecondaryColor3dv		(glSecondaryColor3dv_),
		glSecondaryColor3f		(glSecondaryColor3f_),
		glSecondaryColor3fv		(glSecondaryColor3fv_),
		glSecondaryColor3i		(glSecondaryColor3i_),
		glSecondaryColor3iv		(glSecondaryColor3iv_),
		glSecondaryColor3s		(glSecondaryColor3s_),
		glSecondaryColor3sv		(glSecondaryColor3sv_),
		glSecondaryColor3ub		(glSecondaryColor3ub_),
		glSecondaryColor3ubv	(glSecondaryColor3ubv_),
		glSecondaryColor3ui		(glSecondaryColor3ui_),
		glSecondaryColor3uiv	(glSecondaryColor3uiv_),
		glSecondaryColor3us		(glSecondaryColor3us_),
		glSecondaryColor3usv	(glSecondaryColor3usv_),
		glSecondaryColorPointer	(glSecondaryColorPointer_),
		glWindowPos2d			(glWindowPos2d_),
		glWindowPos2dv			(glWindowPos2dv_),
		glWindowPos2f			(glWindowPos2f_),
		glWindowPos2fv			(glWindowPos2fv_),
		glWindowPos2i			(glWindowPos2i_),
		glWindowPos2iv			(glWindowPos2iv_),
		glWindowPos2s			(glWindowPos2s_),
		glWindowPos2sv			(glWindowPos2sv_),
		glWindowPos3d			(glWindowPos3d_),
		glWindowPos3dv			(glWindowPos3dv_),
		glWindowPos3f			(glWindowPos3f_),
		glWindowPos3fv			(glWindowPos3fv_),
		glWindowPos3i			(glWindowPos3i_),
		glWindowPos3iv			(glWindowPos3iv_),
		glWindowPos3s			(glWindowPos3s_),
		glWindowPos3sv			(glWindowPos3sv_),
		glBlendColor			(glBlendColor_),
		glBlendEquation			(glBlendEquation_)
	{
	}
#pragma endregion
#pragma region Interface_1_5
	Interface_1_5::Interface_1_5(
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
		glGenQueries				(glGenQueries_),
		glDeleteQueries				(glDeleteQueries_),
		glIsQuery					(glIsQuery_),
		glBeginQuery				(glBeginQuery_),
		glEndQuery					(glEndQuery_),
		glGetQueryiv				(glGetQueryiv_),
		glGetQueryObjectiv			(glGetQueryObjectiv_),
		glGetQueryObjectuiv			(glGetQueryObjectuiv_),
		glBindBuffer				(glBindBuffer_),
		glDeleteBuffers				(glDeleteBuffers_),
		glGenBuffers				(glGenBuffers_),
		glIsBuffer					(glIsBuffer_),
		glBufferData				(glBufferData_),
		glBufferSubData				(glBufferSubData_),
		glGetBufferSubData			(glGetBufferSubData_),
		glMapBuffer					(glMapBuffer_),
		glUnmapBuffer				(glUnmapBuffer_),
		glGetBufferParameteriv		(glGetBufferParameteriv_),
		glGetBufferPointerv			(glGetBufferPointerv_)
	{
	}

	void Interface_1_5::BindBuffer(const Buffer::Type& type_, const Null&) const
	{
		glBindBuffer(static_cast<GLenum>(type_), 0);

		CheckForErrors();
	}
	void Interface_1_5::BindBuffer(const Buffer::Type& type_, const Buffer::Handle& handle_) const
	{
		glBindBuffer(static_cast<GLenum>(type_), static_cast<Buffer::Handle::Value>(handle_));

		CheckForErrors();
	}
	Buffer::Handle Interface_1_5::GenBuffer() const
	{
		Buffer::Handle handle;

		glGenBuffers(1, static_cast<Memory<Buffer::Handle::Value>>(handle));

		CheckForErrors();

		return handle;
	}
	void Interface_1_5::DeleteBuffer(const Buffer::Handle& handle_) const
	{
		glDeleteBuffers(1, static_cast<Memory<const Buffer::Handle::Value>>(handle_));

		CheckForErrors();
	}
	void Interface_1_5::BufferData(const Buffer::Type& type_, const GLsizeiptr& size_, const Memory<const void>& data_, const Buffer::Usage& usage_) const
	{
		glBufferData(static_cast<GLenum>(type_), size_, data_, static_cast<GLenum>(usage_));

		CheckForErrors();
	}
	template<class Type_> void Interface_1_5::BufferData(const Buffer::Type& type_, const Vector<Type_>& data_, const Buffer::Usage& usage_) const
	{
		glBufferData(static_cast<GLenum>(type_), sizeof(Type_) * data_.size(), data_.data(), static_cast<GLenum>(usage_));
		
		CheckForErrors();
	}
#pragma endregion
#pragma region Interface_2_0
	Interface_2_0::Interface_2_0(
		const PFNGLBLENDEQUATIONSEPARATEPROC&			glBlendEquationSeparate_,
		const PFNGLDRAWBUFFERSPROC&						glDrawBuffers_,
		const PFNGLSTENCILOPSEPARATEPROC&				glStencilOpSeparate_,
		const PFNGLSTENCILFUNCSEPARATEPROC&				glStencilFuncSeparate_,
		const PFNGLSTENCILMASKSEPARATEPROC&				glStencilMaskSeparate_,
		const PFNGLATTACHSHADERPROC&					glAttachShader_,
		const PFNGLBINDATTRIBLOCATIONPROC&				glBindAttribLocation_,
		const PFNGLCOMPILESHADERPROC&					glCompileShader_,
		const PFNGLCREATEPROGRAMPROC&					glCreateProgram_,
		const PFNGLCREATESHADERPROC&					glCreateShader_,
		const PFNGLDELETEPROGRAMPROC&					glDeleteProgram_,
		const PFNGLDELETESHADERPROC&					glDeleteShader_,
		const PFNGLDETACHSHADERPROC&					glDetachShader_,
		const PFNGLDISABLEVERTEXATTRIBARRAYPROC&		glDisableVertexAttribArray_,
		const PFNGLENABLEVERTEXATTRIBARRAYPROC&			glEnableVertexAttribArray_,
		const PFNGLGETACTIVEATTRIBPROC&					glGetActiveAttrib_,
		const PFNGLGETACTIVEUNIFORMPROC&				glGetActiveUniform_,
		const PFNGLGETATTACHEDSHADERSPROC&				glGetAttachedShaders_,
		const PFNGLGETATTRIBLOCATIONPROC&				glGetAttribLocation_,
		const PFNGLGETPROGRAMIVPROC&					glGetProgramiv_,
		const PFNGLGETPROGRAMINFOLOGPROC&				glGetProgramInfoLog_,
		const PFNGLGETSHADERIVPROC&						glGetShaderiv_,
		const PFNGLGETSHADERINFOLOGPROC&				glGetShaderInfoLog_,
		const PFNGLGETSHADERSOURCEPROC&					glGetShaderSource_,
		const PFNGLGETUNIFORMLOCATIONPROC&				glGetUniformLocation_,
		const PFNGLGETUNIFORMFVPROC&					glGetUniformfv_,
		const PFNGLGETUNIFORMIVPROC&					glGetUniformiv_,
		const PFNGLGETVERTEXATTRIBDVPROC&				glGetVertexAttribdv_,
		const PFNGLGETVERTEXATTRIBFVPROC&				glGetVertexAttribfv_,
		const PFNGLGETVERTEXATTRIBIVPROC&				glGetVertexAttribiv_,
		const PFNGLGETVERTEXATTRIBPOINTERVPROC&			glGetVertexAttribPointerv_,
		const PFNGLISPROGRAMPROC&						glIsProgram_,
		const PFNGLISSHADERPROC&						glIsShader_,
		const PFNGLLINKPROGRAMPROC&						glLinkProgram_,
		const PFNGLSHADERSOURCEPROC&					glShaderSource_,
		const PFNGLUSEPROGRAMPROC&						glUseProgram_,
		const PFNGLUNIFORM1FPROC&						glUniform1f_,
		const PFNGLUNIFORM2FPROC&						glUniform2f_,
		const PFNGLUNIFORM3FPROC&						glUniform3f_,
		const PFNGLUNIFORM4FPROC&						glUniform4f_,
		const PFNGLUNIFORM1IPROC&						glUniform1i_,
		const PFNGLUNIFORM2IPROC&						glUniform2i_,
		const PFNGLUNIFORM3IPROC&						glUniform3i_,
		const PFNGLUNIFORM4IPROC&						glUniform4i_,
		const PFNGLUNIFORM1FVPROC&						glUniform1fv_,
		const PFNGLUNIFORM2FVPROC&						glUniform2fv_,
		const PFNGLUNIFORM3FVPROC&						glUniform3fv_,
		const PFNGLUNIFORM4FVPROC&						glUniform4fv_,
		const PFNGLUNIFORM1IVPROC&						glUniform1iv_,
		const PFNGLUNIFORM2IVPROC&						glUniform2iv_,
		const PFNGLUNIFORM3IVPROC&						glUniform3iv_,
		const PFNGLUNIFORM4IVPROC&						glUniform4iv_,
		const PFNGLUNIFORMMATRIX2FVPROC&				glUniformMatrix2fv_,
		const PFNGLUNIFORMMATRIX3FVPROC&				glUniformMatrix3fv_,
		const PFNGLUNIFORMMATRIX4FVPROC&				glUniformMatrix4fv_,
		const PFNGLVALIDATEPROGRAMPROC&					glValidateProgram_,
		const PFNGLVERTEXATTRIB1DPROC&					glVertexAttrib1d_,
		const PFNGLVERTEXATTRIB1DVPROC&					glVertexAttrib1dv_,
		const PFNGLVERTEXATTRIB1FPROC&					glVertexAttrib1f_,
		const PFNGLVERTEXATTRIB1FVPROC&					glVertexAttrib1fv_,
		const PFNGLVERTEXATTRIB1SPROC&					glVertexAttrib1s_,
		const PFNGLVERTEXATTRIB1SVPROC&					glVertexAttrib1sv_,
		const PFNGLVERTEXATTRIB2DPROC&					glVertexAttrib2d_,
		const PFNGLVERTEXATTRIB2DVPROC&					glVertexAttrib2dv_,
		const PFNGLVERTEXATTRIB2FPROC&					glVertexAttrib2f_,
		const PFNGLVERTEXATTRIB2FVPROC&					glVertexAttrib2fv_,
		const PFNGLVERTEXATTRIB2SPROC&					glVertexAttrib2s_,
		const PFNGLVERTEXATTRIB2SVPROC&					glVertexAttrib2sv_,
		const PFNGLVERTEXATTRIB3DPROC&					glVertexAttrib3d_,
		const PFNGLVERTEXATTRIB3DVPROC&					glVertexAttrib3dv_,
		const PFNGLVERTEXATTRIB3FPROC&					glVertexAttrib3f_,
		const PFNGLVERTEXATTRIB3FVPROC&					glVertexAttrib3fv_,
		const PFNGLVERTEXATTRIB3SPROC&					glVertexAttrib3s_,
		const PFNGLVERTEXATTRIB3SVPROC&					glVertexAttrib3sv_,
		const PFNGLVERTEXATTRIB4NBVPROC&				glVertexAttrib4Nbv_,
		const PFNGLVERTEXATTRIB4NIVPROC&				glVertexAttrib4Niv_,
		const PFNGLVERTEXATTRIB4NSVPROC&				glVertexAttrib4Nsv_,
		const PFNGLVERTEXATTRIB4NUBPROC&				glVertexAttrib4Nub_,
		const PFNGLVERTEXATTRIB4NUBVPROC&				glVertexAttrib4Nubv_,
		const PFNGLVERTEXATTRIB4NUIVPROC&				glVertexAttrib4Nuiv_,
		const PFNGLVERTEXATTRIB4NUSVPROC&				glVertexAttrib4Nusv_,
		const PFNGLVERTEXATTRIB4BVPROC&					glVertexAttrib4bv_,
		const PFNGLVERTEXATTRIB4DPROC&					glVertexAttrib4d_,
		const PFNGLVERTEXATTRIB4DVPROC&					glVertexAttrib4dv_,
		const PFNGLVERTEXATTRIB4FPROC&					glVertexAttrib4f_,
		const PFNGLVERTEXATTRIB4FVPROC&					glVertexAttrib4fv_,
		const PFNGLVERTEXATTRIB4IVPROC&					glVertexAttrib4iv_,
		const PFNGLVERTEXATTRIB4SPROC&					glVertexAttrib4s_,
		const PFNGLVERTEXATTRIB4SVPROC&					glVertexAttrib4sv_,
		const PFNGLVERTEXATTRIB4UBVPROC&				glVertexAttrib4ubv_,
		const PFNGLVERTEXATTRIB4UIVPROC&				glVertexAttrib4uiv_,
		const PFNGLVERTEXATTRIB4USVPROC&				glVertexAttrib4usv_,
		const PFNGLVERTEXATTRIBPOINTERPROC&				glVertexAttribPointer_
	):
		glBlendEquationSeparate				(glBlendEquationSeparate_),
		glDrawBuffers						(glDrawBuffers_),
		glStencilOpSeparate					(glStencilOpSeparate_),
		glStencilFuncSeparate				(glStencilFuncSeparate_),
		glStencilMaskSeparate				(glStencilMaskSeparate_),
		glAttachShader						(glAttachShader_),
		glBindAttribLocation				(glBindAttribLocation_),
		glCompileShader						(glCompileShader_),
		glCreateProgram						(glCreateProgram_),
		glCreateShader						(glCreateShader_),
		glDeleteProgram						(glDeleteProgram_),
		glDeleteShader						(glDeleteShader_),
		glDetachShader						(glDetachShader_),
		glDisableVertexAttribArray			(glDisableVertexAttribArray_),
		glEnableVertexAttribArray			(glEnableVertexAttribArray_),
		glGetActiveAttrib					(glGetActiveAttrib_),
		glGetActiveUniform					(glGetActiveUniform_),
		glGetAttachedShaders				(glGetAttachedShaders_),
		glGetAttribLocation					(glGetAttribLocation_),
		glGetProgramiv						(glGetProgramiv_),
		glGetProgramInfoLog					(glGetProgramInfoLog_),
		glGetShaderiv						(glGetShaderiv_),
		glGetShaderInfoLog					(glGetShaderInfoLog_),
		glGetShaderSource					(glGetShaderSource_),
		glGetUniformLocation				(glGetUniformLocation_),
		glGetUniformfv						(glGetUniformfv_),
		glGetUniformiv						(glGetUniformiv_),
		glGetVertexAttribdv					(glGetVertexAttribdv_),
		glGetVertexAttribfv					(glGetVertexAttribfv_),
		glGetVertexAttribiv					(glGetVertexAttribiv_),
		glGetVertexAttribPointerv			(glGetVertexAttribPointerv_),
		glIsProgram							(glIsProgram_),
		glIsShader							(glIsShader_),
		glLinkProgram						(glLinkProgram_),
		glShaderSource						(glShaderSource_),
		glUseProgram						(glUseProgram_),
		glUniform1f							(glUniform1f_),
		glUniform2f							(glUniform2f_),
		glUniform3f							(glUniform3f_),
		glUniform4f							(glUniform4f_),
		glUniform1i							(glUniform1i_),
		glUniform2i							(glUniform2i_),
		glUniform3i							(glUniform3i_),
		glUniform4i							(glUniform4i_),
		glUniform1fv						(glUniform1fv_),
		glUniform2fv						(glUniform2fv_),
		glUniform3fv						(glUniform3fv_),
		glUniform4fv						(glUniform4fv_),
		glUniform1iv						(glUniform1iv_),
		glUniform2iv						(glUniform2iv_),
		glUniform3iv						(glUniform3iv_),
		glUniform4iv						(glUniform4iv_),
		glUniformMatrix2fv					(glUniformMatrix2fv_),
		glUniformMatrix3fv					(glUniformMatrix3fv_),
		glUniformMatrix4fv					(glUniformMatrix4fv_),
		glValidateProgram					(glValidateProgram_),
		glVertexAttrib1d					(glVertexAttrib1d_),
		glVertexAttrib1dv					(glVertexAttrib1dv_),
		glVertexAttrib1f					(glVertexAttrib1f_),
		glVertexAttrib1fv					(glVertexAttrib1fv_),
		glVertexAttrib1s					(glVertexAttrib1s_),
		glVertexAttrib1sv					(glVertexAttrib1sv_),
		glVertexAttrib2d					(glVertexAttrib2d_),
		glVertexAttrib2dv					(glVertexAttrib2dv_),
		glVertexAttrib2f					(glVertexAttrib2f_),
		glVertexAttrib2fv					(glVertexAttrib2fv_),
		glVertexAttrib2s					(glVertexAttrib2s_),
		glVertexAttrib2sv					(glVertexAttrib2sv_),
		glVertexAttrib3d					(glVertexAttrib3d_),
		glVertexAttrib3dv					(glVertexAttrib3dv_),
		glVertexAttrib3f					(glVertexAttrib3f_),
		glVertexAttrib3fv					(glVertexAttrib3fv_),
		glVertexAttrib3s					(glVertexAttrib3s_),
		glVertexAttrib3sv					(glVertexAttrib3sv_),
		glVertexAttrib4Nbv					(glVertexAttrib4Nbv_),
		glVertexAttrib4Niv					(glVertexAttrib4Niv_),
		glVertexAttrib4Nsv					(glVertexAttrib4Nsv_),
		glVertexAttrib4Nub					(glVertexAttrib4Nub_),
		glVertexAttrib4Nubv					(glVertexAttrib4Nubv_),
		glVertexAttrib4Nuiv					(glVertexAttrib4Nuiv_),
		glVertexAttrib4Nusv					(glVertexAttrib4Nusv_),
		glVertexAttrib4bv					(glVertexAttrib4bv_),
		glVertexAttrib4d					(glVertexAttrib4d_),
		glVertexAttrib4dv					(glVertexAttrib4dv_),
		glVertexAttrib4f					(glVertexAttrib4f_),
		glVertexAttrib4fv					(glVertexAttrib4fv_),
		glVertexAttrib4iv					(glVertexAttrib4iv_),
		glVertexAttrib4s					(glVertexAttrib4s_),
		glVertexAttrib4sv					(glVertexAttrib4sv_),
		glVertexAttrib4ubv					(glVertexAttrib4ubv_),
		glVertexAttrib4uiv					(glVertexAttrib4uiv_),
		glVertexAttrib4usv					(glVertexAttrib4usv_),
		glVertexAttribPointer				(glVertexAttribPointer_)
	{
	}
#pragma endregion
#pragma region Interface_2_1
	Interface_2_1::Interface_2_1(
		const PFNGLUNIFORMMATRIX2X3FVPROC& glUniformMatrix2x3fv_,
		const PFNGLUNIFORMMATRIX3X2FVPROC& glUniformMatrix3x2fv_,
		const PFNGLUNIFORMMATRIX2X4FVPROC& glUniformMatrix2x4fv_,
		const PFNGLUNIFORMMATRIX4X2FVPROC& glUniformMatrix4x2fv_,
		const PFNGLUNIFORMMATRIX3X4FVPROC& glUniformMatrix3x4fv_,
		const PFNGLUNIFORMMATRIX4X3FVPROC& glUniformMatrix4x3fv_
	):
		glUniformMatrix2x3fv(glUniformMatrix2x3fv_),
		glUniformMatrix3x2fv(glUniformMatrix3x2fv_),
		glUniformMatrix2x4fv(glUniformMatrix2x4fv_),
		glUniformMatrix4x2fv(glUniformMatrix4x2fv_),
		glUniformMatrix3x4fv(glUniformMatrix3x4fv_),
		glUniformMatrix4x3fv(glUniformMatrix4x3fv_)
	{
	}
#pragma endregion
#pragma region Interface_3_0
	Interface_3_0::Interface_3_0(
		const PFNGLCOLORMASKIPROC&										glColorMaski_,
		const PFNGLGETBOOLEANI_VPROC&									glGetBooleani_v_,
		const PFNGLGETINTEGERI_VPROC&									glGetIntegeri_v_,
		const PFNGLENABLEIPROC&											glEnablei_,
		const PFNGLDISABLEIPROC&										glDisablei_,
		const PFNGLISENABLEDIPROC&										glIsEnabledi_,
		const PFNGLBEGINTRANSFORMFEEDBACKPROC&							glBeginTransformFeedback_,
		const PFNGLENDTRANSFORMFEEDBACKPROC&							glEndTransformFeedback_,
		const PFNGLBINDBUFFERRANGEPROC&									glBindBufferRange_,
		const PFNGLBINDBUFFERBASEPROC&									glBindBufferBase_,
		const PFNGLTRANSFORMFEEDBACKVARYINGSPROC&						glTransformFeedbackVaryings_,
		const PFNGLGETTRANSFORMFEEDBACKVARYINGPROC&						glGetTransformFeedbackVarying_,
		const PFNGLCLAMPCOLORPROC&										glClampColor_,
		const PFNGLBEGINCONDITIONALRENDERPROC&							glBeginConditionalRender_,
		const PFNGLENDCONDITIONALRENDERPROC&							glEndConditionalRender_,
		const PFNGLVERTEXATTRIBIPOINTERPROC&							glVertexAttribIPointer_,
		const PFNGLGETVERTEXATTRIBIIVPROC&								glGetVertexAttribIiv_,
		const PFNGLGETVERTEXATTRIBIUIVPROC&								glGetVertexAttribIuiv_,
		const PFNGLVERTEXATTRIBI1IPROC&									glVertexAttribI1i_,
		const PFNGLVERTEXATTRIBI2IPROC&									glVertexAttribI2i_,
		const PFNGLVERTEXATTRIBI3IPROC&									glVertexAttribI3i_,
		const PFNGLVERTEXATTRIBI4IPROC&									glVertexAttribI4i_,
		const PFNGLVERTEXATTRIBI1UIPROC&								glVertexAttribI1ui_,
		const PFNGLVERTEXATTRIBI2UIPROC&								glVertexAttribI2ui_,
		const PFNGLVERTEXATTRIBI3UIPROC&								glVertexAttribI3ui_,
		const PFNGLVERTEXATTRIBI4UIPROC&								glVertexAttribI4ui_,
		const PFNGLVERTEXATTRIBI1IVPROC&								glVertexAttribI1iv_,
		const PFNGLVERTEXATTRIBI2IVPROC&								glVertexAttribI2iv_,
		const PFNGLVERTEXATTRIBI3IVPROC&								glVertexAttribI3iv_,
		const PFNGLVERTEXATTRIBI4IVPROC&								glVertexAttribI4iv_,
		const PFNGLVERTEXATTRIBI1UIVPROC&								glVertexAttribI1uiv_,
		const PFNGLVERTEXATTRIBI2UIVPROC&								glVertexAttribI2uiv_,
		const PFNGLVERTEXATTRIBI3UIVPROC&								glVertexAttribI3uiv_,
		const PFNGLVERTEXATTRIBI4UIVPROC&								glVertexAttribI4uiv_,
		const PFNGLVERTEXATTRIBI4BVPROC&								glVertexAttribI4bv_,
		const PFNGLVERTEXATTRIBI4SVPROC&								glVertexAttribI4sv_,
		const PFNGLVERTEXATTRIBI4UBVPROC&								glVertexAttribI4ubv_,
		const PFNGLVERTEXATTRIBI4USVPROC&								glVertexAttribI4usv_,
		const PFNGLGETUNIFORMUIVPROC&									glGetUniformuiv_,
		const PFNGLBINDFRAGDATALOCATIONPROC&							glBindFragDataLocation_,
		const PFNGLGETFRAGDATALOCATIONPROC&								glGetFragDataLocation_,
		const PFNGLUNIFORM1UIPROC&										glUniform1ui_,
		const PFNGLUNIFORM2UIPROC&										glUniform2ui_,
		const PFNGLUNIFORM3UIPROC&										glUniform3ui_,
		const PFNGLUNIFORM4UIPROC&										glUniform4ui_,
		const PFNGLUNIFORM1UIVPROC&										glUniform1uiv_,
		const PFNGLUNIFORM2UIVPROC&										glUniform2uiv_,
		const PFNGLUNIFORM3UIVPROC&										glUniform3uiv_,
		const PFNGLUNIFORM4UIVPROC&										glUniform4uiv_,
		const PFNGLTEXPARAMETERIIVPROC&									glTexParameterIiv_,
		const PFNGLTEXPARAMETERIUIVPROC&								glTexParameterIuiv_,
		const PFNGLGETTEXPARAMETERIIVPROC&								glGetTexParameterIiv_,
		const PFNGLGETTEXPARAMETERIUIVPROC&								glGetTexParameterIuiv_,
		const PFNGLCLEARBUFFERIVPROC&									glClearBufferiv_,
		const PFNGLCLEARBUFFERUIVPROC&									glClearBufferuiv_,
		const PFNGLCLEARBUFFERFVPROC&									glClearBufferfv_,
		const PFNGLCLEARBUFFERFIPROC&									glClearBufferfi_,
		const PFNGLGETSTRINGIPROC&										glGetStringi_,
		const PFNGLISRENDERBUFFERPROC&									glIsRenderbuffer_,
		const PFNGLBINDRENDERBUFFERPROC&								glBindRenderbuffer_,
		const PFNGLDELETERENDERBUFFERSPROC&								glDeleteRenderbuffers_,
		const PFNGLGENRENDERBUFFERSPROC&								glGenRenderbuffers_,
		const PFNGLRENDERBUFFERSTORAGEPROC&								glRenderbufferStorage_,
		const PFNGLGETRENDERBUFFERPARAMETERIVPROC&						glGetRenderbufferParameteriv_,
		const PFNGLISFRAMEBUFFERPROC&									glIsFramebuffer_,
		const PFNGLBINDFRAMEBUFFERPROC&									glBindFramebuffer_,
		const PFNGLDELETEFRAMEBUFFERSPROC&								glDeleteFramebuffers_,
		const PFNGLGENFRAMEBUFFERSPROC&									glGenFramebuffers_,
		const PFNGLCHECKFRAMEBUFFERSTATUSPROC&							glCheckFramebufferStatus_,
		const PFNGLFRAMEBUFFERTEXTURE1DPROC&							glFramebufferTexture1D_,
		const PFNGLFRAMEBUFFERTEXTURE2DPROC&							glFramebufferTexture2D_,
		const PFNGLFRAMEBUFFERTEXTURE3DPROC&							glFramebufferTexture3D_,
		const PFNGLFRAMEBUFFERRENDERBUFFERPROC&							glFramebufferRenderbuffer_,
		const PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC&				glGetFramebufferAttachmentParameteriv_,
		const PFNGLGENERATEMIPMAPPROC&									glGenerateMipmap_,
		const PFNGLBLITFRAMEBUFFERPROC&									glBlitFramebuffer_,
		const PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC&					glRenderbufferStorageMultisample_,
		const PFNGLFRAMEBUFFERTEXTURELAYERPROC&							glFramebufferTextureLayer_,
		const PFNGLMAPBUFFERRANGEPROC&									glMapBufferRange_,
		const PFNGLFLUSHMAPPEDBUFFERRANGEPROC&							glFlushMappedBufferRange_,
		const PFNGLBINDVERTEXARRAYPROC&									glBindVertexArray_,
		const PFNGLDELETEVERTEXARRAYSPROC&								glDeleteVertexArrays_,
		const PFNGLGENVERTEXARRAYSPROC&									glGenVertexArrays_,
		const PFNGLISVERTEXARRAYPROC&									glIsVertexArray_
	):
		glColorMaski							(glColorMaski_),
		glGetBooleani_v							(glGetBooleani_v_),
		glGetIntegeri_v							(glGetIntegeri_v_),
		glEnablei								(glEnablei_),
		glDisablei								(glDisablei_),
		glIsEnabledi							(glIsEnabledi_),
		glBeginTransformFeedback				(glBeginTransformFeedback_),
		glEndTransformFeedback					(glEndTransformFeedback_),
		glBindBufferRange						(glBindBufferRange_),
		glBindBufferBase						(glBindBufferBase_),
		glTransformFeedbackVaryings				(glTransformFeedbackVaryings_),
		glGetTransformFeedbackVarying			(glGetTransformFeedbackVarying_),
		glClampColor							(glClampColor_),
		glBeginConditionalRender				(glBeginConditionalRender_),
		glEndConditionalRender					(glEndConditionalRender_),
		glVertexAttribIPointer					(glVertexAttribIPointer_),
		glGetVertexAttribIiv					(glGetVertexAttribIiv_),
		glGetVertexAttribIuiv					(glGetVertexAttribIuiv_),
		glVertexAttribI1i						(glVertexAttribI1i_),
		glVertexAttribI2i						(glVertexAttribI2i_),
		glVertexAttribI3i						(glVertexAttribI3i_),
		glVertexAttribI4i						(glVertexAttribI4i_),
		glVertexAttribI1ui						(glVertexAttribI1ui_),
		glVertexAttribI2ui						(glVertexAttribI2ui_),
		glVertexAttribI3ui						(glVertexAttribI3ui_),
		glVertexAttribI4ui						(glVertexAttribI4ui_),
		glVertexAttribI1iv						(glVertexAttribI1iv_),
		glVertexAttribI2iv						(glVertexAttribI2iv_),
		glVertexAttribI3iv						(glVertexAttribI3iv_),
		glVertexAttribI4iv						(glVertexAttribI4iv_),
		glVertexAttribI1uiv						(glVertexAttribI1uiv_),
		glVertexAttribI2uiv						(glVertexAttribI2uiv_),
		glVertexAttribI3uiv						(glVertexAttribI3uiv_),
		glVertexAttribI4uiv						(glVertexAttribI4uiv_),
		glVertexAttribI4bv						(glVertexAttribI4bv_),
		glVertexAttribI4sv						(glVertexAttribI4sv_),
		glVertexAttribI4ubv						(glVertexAttribI4ubv_),
		glVertexAttribI4usv						(glVertexAttribI4usv_),
		glGetUniformuiv							(glGetUniformuiv_),
		glBindFragDataLocation					(glBindFragDataLocation_),
		glGetFragDataLocation					(glGetFragDataLocation_),
		glUniform1ui							(glUniform1ui_),
		glUniform2ui							(glUniform2ui_),
		glUniform3ui							(glUniform3ui_),
		glUniform4ui							(glUniform4ui_),
		glUniform1uiv							(glUniform1uiv_),
		glUniform2uiv							(glUniform2uiv_),
		glUniform3uiv							(glUniform3uiv_),
		glUniform4uiv							(glUniform4uiv_),
		glTexParameterIiv						(glTexParameterIiv_),
		glTexParameterIuiv						(glTexParameterIuiv_),
		glGetTexParameterIiv					(glGetTexParameterIiv_),
		glGetTexParameterIuiv					(glGetTexParameterIuiv_),
		glClearBufferiv							(glClearBufferiv_),
		glClearBufferuiv						(glClearBufferuiv_),
		glClearBufferfv							(glClearBufferfv_),
		glClearBufferfi							(glClearBufferfi_),
		glGetStringi							(glGetStringi_),
		glIsRenderbuffer						(glIsRenderbuffer_),
		glBindRenderbuffer						(glBindRenderbuffer_),
		glDeleteRenderbuffers					(glDeleteRenderbuffers_),
		glGenRenderbuffers						(glGenRenderbuffers_),
		glRenderbufferStorage					(glRenderbufferStorage_),
		glGetRenderbufferParameteriv			(glGetRenderbufferParameteriv_),
		glIsFramebuffer							(glIsFramebuffer_),
		glBindFramebuffer						(glBindFramebuffer_),
		glDeleteFramebuffers					(glDeleteFramebuffers_),
		glGenFramebuffers						(glGenFramebuffers_),
		glCheckFramebufferStatus				(glCheckFramebufferStatus_),
		glFramebufferTexture1D					(glFramebufferTexture1D_),
		glFramebufferTexture2D					(glFramebufferTexture2D_),
		glFramebufferTexture3D					(glFramebufferTexture3D_),
		glFramebufferRenderbuffer				(glFramebufferRenderbuffer_),
		glGetFramebufferAttachmentParameteriv	(glGetFramebufferAttachmentParameteriv_),
		glGenerateMipmap						(glGenerateMipmap_),
		glBlitFramebuffer						(glBlitFramebuffer_),
		glRenderbufferStorageMultisample		(glRenderbufferStorageMultisample_),
		glFramebufferTextureLayer				(glFramebufferTextureLayer_),
		glMapBufferRange						(glMapBufferRange_),
		glFlushMappedBufferRange				(glFlushMappedBufferRange_),
		glBindVertexArray						(glBindVertexArray_),
		glDeleteVertexArrays					(glDeleteVertexArrays_),
		glGenVertexArrays						(glGenVertexArrays_),
		glIsVertexArray							(glIsVertexArray_)
	{
	}
#pragma endregion
#pragma region Interface_3_1
	Interface_3_1::Interface_3_1(
		const PFNGLDRAWARRAYSINSTANCEDPROC&			glDrawArraysInstanced_,
		const PFNGLDRAWELEMENTSINSTANCEDPROC&		glDrawElementsInstanced_,
		const PFNGLTEXBUFFERPROC&					glTexBuffer_,
		const PFNGLPRIMITIVERESTARTINDEXPROC&		glPrimitiveRestartIndex_,
		const PFNGLCOPYBUFFERSUBDATAPROC&			glCopyBufferSubData_,
		const PFNGLGETUNIFORMINDICESPROC&			glGetUniformIndices_,
		const PFNGLGETACTIVEUNIFORMSIVPROC&			glGetActiveUniformsiv_,
		const PFNGLGETACTIVEUNIFORMNAMEPROC&		glGetActiveUniformName_,
		const PFNGLGETUNIFORMBLOCKINDEXPROC&		glGetUniformBlockIndex_,
		const PFNGLGETACTIVEUNIFORMBLOCKIVPROC&		glGetActiveUniformBlockiv_,
		const PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC&	glGetActiveUniformBlockName_,
		const PFNGLUNIFORMBLOCKBINDINGPROC&			glUniformBlockBinding_
	):
		glDrawArraysInstanced		(glDrawArraysInstanced_),
		glDrawElementsInstanced		(glDrawElementsInstanced_),
		glTexBuffer					(glTexBuffer_),
		glPrimitiveRestartIndex		(glPrimitiveRestartIndex_),
		glCopyBufferSubData			(glCopyBufferSubData_),
		glGetUniformIndices			(glGetUniformIndices_),
		glGetActiveUniformsiv		(glGetActiveUniformsiv_),
		glGetActiveUniformName		(glGetActiveUniformName_),
		glGetUniformBlockIndex		(glGetUniformBlockIndex_),
		glGetActiveUniformBlockiv	(glGetActiveUniformBlockiv_),
		glGetActiveUniformBlockName	(glGetActiveUniformBlockName_),
		glUniformBlockBinding		(glUniformBlockBinding_)
	{
	}
#pragma endregion
#pragma region Interface_3_2
	Interface_3_2::Interface_3_2(
		const PFNGLDRAWELEMENTSBASEVERTEXPROC&			glDrawElementsBaseVertex_,
		const PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC&		glDrawRangeElementsBaseVertex_,
		const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC&	glDrawElementsInstancedBaseVertex_,
		const PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC&		glMultiDrawElementsBaseVertex_,
		const PFNGLPROVOKINGVERTEXPROC&					glProvokingVertex_,
		const PFNGLFENCESYNCPROC&						glFenceSync_,
		const PFNGLISSYNCPROC&							glIsSync_,
		const PFNGLDELETESYNCPROC&						glDeleteSync_,
		const PFNGLCLIENTWAITSYNCPROC&					glClientWaitSync_,
		const PFNGLWAITSYNCPROC&						glWaitSync_,
		const PFNGLGETINTEGER64VPROC&					glGetInteger64v_,
		const PFNGLGETSYNCIVPROC&						glGetSynciv_,
		const PFNGLGETINTEGER64I_VPROC&					glGetInteger64i_v_,
		const PFNGLGETBUFFERPARAMETERI64VPROC&			glGetBufferParameteri64v_,
		const PFNGLFRAMEBUFFERTEXTUREPROC&				glFramebufferTexture_,
		const PFNGLTEXIMAGE2DMULTISAMPLEPROC&			glTexImage2DMultisample_,
		const PFNGLTEXIMAGE3DMULTISAMPLEPROC&			glTexImage3DMultisample_,
		const PFNGLGETMULTISAMPLEFVPROC&				glGetMultisamplefv_,
		const PFNGLSAMPLEMASKIPROC&						glSampleMaski_
	):
		glDrawElementsBaseVertex			(glDrawElementsBaseVertex_),
		glDrawRangeElementsBaseVertex		(glDrawRangeElementsBaseVertex_),
		glDrawElementsInstancedBaseVertex	(glDrawElementsInstancedBaseVertex_),
		glMultiDrawElementsBaseVertex		(glMultiDrawElementsBaseVertex_),
		glProvokingVertex					(glProvokingVertex_),
		glFenceSync							(glFenceSync_),
		glIsSync							(glIsSync_),
		glDeleteSync						(glDeleteSync_),
		glClientWaitSync					(glClientWaitSync_),
		glWaitSync							(glWaitSync_),
		glGetInteger64v						(glGetInteger64v_),
		glGetSynciv							(glGetSynciv_),
		glGetInteger64i_v					(glGetInteger64i_v_),
		glGetBufferParameteri64v			(glGetBufferParameteri64v_),
		glFramebufferTexture				(glFramebufferTexture_),
		glTexImage2DMultisample				(glTexImage2DMultisample_),
		glTexImage3DMultisample				(glTexImage3DMultisample_),
		glGetMultisamplefv					(glGetMultisamplefv_),
		glSampleMaski						(glSampleMaski_)
	{
	}
#pragma endregion
#pragma region Interface_3_3
	Interface_3_3::Interface_3_3(
		const PFNGLBINDFRAGDATALOCATIONINDEXEDPROC&		glBindFragDataLocationIndexed_,
		const PFNGLGETFRAGDATAINDEXPROC&				glGetFragDataIndex_,	
		const PFNGLGENSAMPLERSPROC&						glGenSamplers_,
		const PFNGLDELETESAMPLERSPROC&					glDeleteSamplers_,
		const PFNGLISSAMPLERPROC&						glIsSampler_,
		const PFNGLBINDSAMPLERPROC&						glBindSampler_,
		const PFNGLSAMPLERPARAMETERIPROC&				glSamplerParameteri_,
		const PFNGLSAMPLERPARAMETERIVPROC&				glSamplerParameteriv_,
		const PFNGLSAMPLERPARAMETERFPROC&				glSamplerParameterf_,
		const PFNGLSAMPLERPARAMETERFVPROC&				glSamplerParameterfv_,
		const PFNGLSAMPLERPARAMETERIIVPROC&				glSamplerParameterIiv_,
		const PFNGLSAMPLERPARAMETERIUIVPROC&			glSamplerParameterIuiv_,	
		const PFNGLGETSAMPLERPARAMETERIVPROC&			glGetSamplerParameteriv_,
		const PFNGLGETSAMPLERPARAMETERIIVPROC&			glGetSamplerParameterIiv_,
		const PFNGLGETSAMPLERPARAMETERFVPROC&			glGetSamplerParameterfv_,
		const PFNGLGETSAMPLERPARAMETERIUIVPROC&			glGetSamplerParameterIuiv_,
		const PFNGLQUERYCOUNTERPROC&					glQueryCounter_,	
		const PFNGLGETQUERYOBJECTI64VPROC&				glGetQueryObjecti64v_,
		const PFNGLGETQUERYOBJECTUI64VPROC&				glGetQueryObjectui64v_,
		const PFNGLVERTEXATTRIBDIVISORPROC&				glVertexAttribDivisor_,
		const PFNGLVERTEXATTRIBP1UIPROC&				glVertexAttribP1ui_,	
		const PFNGLVERTEXATTRIBP1UIVPROC&				glVertexAttribP1uiv_,
		const PFNGLVERTEXATTRIBP2UIPROC&				glVertexAttribP2ui_,	
		const PFNGLVERTEXATTRIBP2UIVPROC&				glVertexAttribP2uiv_,
		const PFNGLVERTEXATTRIBP3UIPROC&				glVertexAttribP3ui_,	
		const PFNGLVERTEXATTRIBP3UIVPROC&				glVertexAttribP3uiv_,
		const PFNGLVERTEXATTRIBP4UIPROC&				glVertexAttribP4ui_,	
		const PFNGLVERTEXATTRIBP4UIVPROC&				glVertexAttribP4uiv_,
		const PFNGLVERTEXP2UIPROC&						glVertexP2ui_,
		const PFNGLVERTEXP2UIVPROC&						glVertexP2uiv_,
		const PFNGLVERTEXP3UIPROC&						glVertexP3ui_,
		const PFNGLVERTEXP3UIVPROC&						glVertexP3uiv_,
		const PFNGLVERTEXP4UIPROC&						glVertexP4ui_,
		const PFNGLVERTEXP4UIVPROC&						glVertexP4uiv_,
		const PFNGLTEXCOORDP1UIPROC&					glTexCoordP1ui_,	
		const PFNGLTEXCOORDP1UIVPROC&					glTexCoordP1uiv_,
		const PFNGLTEXCOORDP2UIPROC&					glTexCoordP2ui_,	
		const PFNGLTEXCOORDP2UIVPROC&					glTexCoordP2uiv_,
		const PFNGLTEXCOORDP3UIPROC&					glTexCoordP3ui_,	
		const PFNGLTEXCOORDP3UIVPROC&					glTexCoordP3uiv_,
		const PFNGLTEXCOORDP4UIPROC&					glTexCoordP4ui_,	
		const PFNGLTEXCOORDP4UIVPROC&					glTexCoordP4uiv_,
		const PFNGLMULTITEXCOORDP1UIPROC&				glMultiTexCoordP1ui_,
		const PFNGLMULTITEXCOORDP1UIVPROC&				glMultiTexCoordP1uiv_,
		const PFNGLMULTITEXCOORDP2UIPROC&				glMultiTexCoordP2ui_,
		const PFNGLMULTITEXCOORDP2UIVPROC&				glMultiTexCoordP2uiv_,
		const PFNGLMULTITEXCOORDP3UIPROC&				glMultiTexCoordP3ui_,
		const PFNGLMULTITEXCOORDP3UIVPROC&				glMultiTexCoordP3uiv_,
		const PFNGLMULTITEXCOORDP4UIPROC&				glMultiTexCoordP4ui_,
		const PFNGLMULTITEXCOORDP4UIVPROC&				glMultiTexCoordP4uiv_,
		const PFNGLNORMALP3UIPROC&						glNormalP3ui_,
		const PFNGLNORMALP3UIVPROC&						glNormalP3uiv_,
		const PFNGLCOLORP3UIPROC&						glColorP3ui_,
		const PFNGLCOLORP3UIVPROC&						glColorP3uiv_,
		const PFNGLCOLORP4UIPROC&						glColorP4ui_,
		const PFNGLCOLORP4UIVPROC&						glColorP4uiv_,
		const PFNGLSECONDARYCOLORP3UIPROC&				glSecondaryColorP3ui_,
		const PFNGLSECONDARYCOLORP3UIVPROC&				glSecondaryColorP3uiv_
	):
		glBindFragDataLocationIndexed	(glBindFragDataLocationIndexed_),
		glGetFragDataIndex				(glGetFragDataIndex_	),
		glGenSamplers					(glGenSamplers_),
		glDeleteSamplers				(glDeleteSamplers_),
		glIsSampler						(glIsSampler_),
		glBindSampler					(glBindSampler_),
		glSamplerParameteri				(glSamplerParameteri_),
		glSamplerParameteriv			(glSamplerParameteriv_),
		glSamplerParameterf				(glSamplerParameterf_),
		glSamplerParameterfv			(glSamplerParameterfv_),
		glSamplerParameterIiv			(glSamplerParameterIiv_),
		glSamplerParameterIuiv			(glSamplerParameterIuiv_	),
		glGetSamplerParameteriv			(glGetSamplerParameteriv_),
		glGetSamplerParameterIiv		(glGetSamplerParameterIiv_),
		glGetSamplerParameterfv			(glGetSamplerParameterfv_),
		glGetSamplerParameterIuiv		(glGetSamplerParameterIuiv_),
		glQueryCounter					(glQueryCounter_	),
		glGetQueryObjecti64v			(glGetQueryObjecti64v_),
		glGetQueryObjectui64v			(glGetQueryObjectui64v_),
		glVertexAttribDivisor			(glVertexAttribDivisor_),
		glVertexAttribP1ui				(glVertexAttribP1ui_	),
		glVertexAttribP1uiv				(glVertexAttribP1uiv_),
		glVertexAttribP2ui				(glVertexAttribP2ui_	),
		glVertexAttribP2uiv				(glVertexAttribP2uiv_),
		glVertexAttribP3ui				(glVertexAttribP3ui_	),
		glVertexAttribP3uiv				(glVertexAttribP3uiv_),
		glVertexAttribP4ui				(glVertexAttribP4ui_	),
		glVertexAttribP4uiv				(glVertexAttribP4uiv_),
		glVertexP2ui					(glVertexP2ui_),
		glVertexP2uiv					(glVertexP2uiv_),
		glVertexP3ui					(glVertexP3ui_),
		glVertexP3uiv					(glVertexP3uiv_),
		glVertexP4ui					(glVertexP4ui_),
		glVertexP4uiv					(glVertexP4uiv_),
		glTexCoordP1ui					(glTexCoordP1ui_	),
		glTexCoordP1uiv					(glTexCoordP1uiv_),
		glTexCoordP2ui					(glTexCoordP2ui_	),
		glTexCoordP2uiv					(glTexCoordP2uiv_),
		glTexCoordP3ui					(glTexCoordP3ui_	),
		glTexCoordP3uiv					(glTexCoordP3uiv_),
		glTexCoordP4ui					(glTexCoordP4ui_	),
		glTexCoordP4uiv					(glTexCoordP4uiv_),
		glMultiTexCoordP1ui				(glMultiTexCoordP1ui_),
		glMultiTexCoordP1uiv			(glMultiTexCoordP1uiv_),
		glMultiTexCoordP2ui				(glMultiTexCoordP2ui_),
		glMultiTexCoordP2uiv			(glMultiTexCoordP2uiv_),
		glMultiTexCoordP3ui				(glMultiTexCoordP3ui_),
		glMultiTexCoordP3uiv			(glMultiTexCoordP3uiv_),
		glMultiTexCoordP4ui				(glMultiTexCoordP4ui_),
		glMultiTexCoordP4uiv			(glMultiTexCoordP4uiv_),
		glNormalP3ui					(glNormalP3ui_),
		glNormalP3uiv					(glNormalP3uiv_),
		glColorP3ui						(glColorP3ui_),
		glColorP3uiv					(glColorP3uiv_),
		glColorP4ui						(glColorP4ui_),
		glColorP4uiv					(glColorP4uiv_),
		glSecondaryColorP3ui			(glSecondaryColorP3ui_),
		glSecondaryColorP3uiv			(glSecondaryColorP3uiv_)
	{
	}
#pragma endregion
#pragma region Interface_4_0
	Interface_4_0::Interface_4_0(
		const PFNGLMINSAMPLESHADINGPROC&					glMinSampleShading_,
		const PFNGLBLENDEQUATIONIPROC&						glBlendEquationi_,
		const PFNGLBLENDEQUATIONSEPARATEIPROC&				glBlendEquationSeparatei_,
		const PFNGLBLENDFUNCIPROC&							glBlendFunci_,
		const PFNGLBLENDFUNCSEPARATEIPROC&					glBlendFuncSeparatei_,
		const PFNGLDRAWARRAYSINDIRECTPROC&					glDrawArraysIndirect_,
		const PFNGLDRAWELEMENTSINDIRECTPROC&				glDrawElementsIndirect_,
		const PFNGLUNIFORM1DPROC&							glUniform1d_,
		const PFNGLUNIFORM2DPROC&							glUniform2d_,
		const PFNGLUNIFORM3DPROC&							glUniform3d_,
		const PFNGLUNIFORM4DPROC&							glUniform4d_,
		const PFNGLUNIFORM1DVPROC&							glUniform1dv_,
		const PFNGLUNIFORM2DVPROC&							glUniform2dv_,
		const PFNGLUNIFORM3DVPROC&							glUniform3dv_,
		const PFNGLUNIFORM4DVPROC&							glUniform4dv_,
		const PFNGLUNIFORMMATRIX2DVPROC&					glUniformMatrix2dv_,
		const PFNGLUNIFORMMATRIX3DVPROC&					glUniformMatrix3dv_,
		const PFNGLUNIFORMMATRIX4DVPROC&					glUniformMatrix4dv_,
		const PFNGLUNIFORMMATRIX2X3DVPROC&					glUniformMatrix2x3dv_,
		const PFNGLUNIFORMMATRIX2X4DVPROC&					glUniformMatrix2x4dv_,
		const PFNGLUNIFORMMATRIX3X2DVPROC&					glUniformMatrix3x2dv_,
		const PFNGLUNIFORMMATRIX3X4DVPROC&					glUniformMatrix3x4dv_,
		const PFNGLUNIFORMMATRIX4X2DVPROC&					glUniformMatrix4x2dv_,
		const PFNGLUNIFORMMATRIX4X3DVPROC&					glUniformMatrix4x3dv_,
		const PFNGLGETUNIFORMDVPROC&						glGetUniformdv_,
		const PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC&		glGetSubroutineUniformLocation_,
		const PFNGLGETSUBROUTINEINDEXPROC&					glGetSubroutineIndex_,
		const PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC&		glGetActiveSubroutineUniformiv_,
		const PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC&		glGetActiveSubroutineUniformName_,
		const PFNGLGETACTIVESUBROUTINENAMEPROC&				glGetActiveSubroutineName_,
		const PFNGLUNIFORMSUBROUTINESUIVPROC&				glUniformSubroutinesuiv_,
		const PFNGLGETUNIFORMSUBROUTINEUIVPROC&				glGetUniformSubroutineuiv_,
		const PFNGLGETPROGRAMSTAGEIVPROC&					glGetProgramStageiv_,
		const PFNGLPATCHPARAMETERIPROC&						glPatchParameteri_,
		const PFNGLPATCHPARAMETERFVPROC&					glPatchParameterfv_,
		const PFNGLBINDTRANSFORMFEEDBACKPROC&				glBindTransformFeedback_,
		const PFNGLDELETETRANSFORMFEEDBACKSPROC&			glDeleteTransformFeedbacks_,
		const PFNGLGENTRANSFORMFEEDBACKSPROC&				glGenTransformFeedbacks_,
		const PFNGLISTRANSFORMFEEDBACKPROC&					glIsTransformFeedback_,
		const PFNGLPAUSETRANSFORMFEEDBACKPROC&				glPauseTransformFeedback_,
		const PFNGLRESUMETRANSFORMFEEDBACKPROC&				glResumeTransformFeedback_,
		const PFNGLDRAWTRANSFORMFEEDBACKPROC&				glDrawTransformFeedback_,
		const PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC&			glDrawTransformFeedbackStream_,
		const PFNGLBEGINQUERYINDEXEDPROC&					glBeginQueryIndexed_,
		const PFNGLENDQUERYINDEXEDPROC&						glEndQueryIndexed_,
		const PFNGLGETQUERYINDEXEDIVPROC&					glGetQueryIndexediv_
	):
		glMinSampleShading					(glMinSampleShading_),
		glBlendEquationi					(glBlendEquationi_),
		glBlendEquationSeparatei			(glBlendEquationSeparatei_),
		glBlendFunci						(glBlendFunci_),
		glBlendFuncSeparatei				(glBlendFuncSeparatei_),
		glDrawArraysIndirect				(glDrawArraysIndirect_),
		glDrawElementsIndirect				(glDrawElementsIndirect_),
		glUniform1d							(glUniform1d_),
		glUniform2d							(glUniform2d_),
		glUniform3d							(glUniform3d_),
		glUniform4d							(glUniform4d_),
		glUniform1dv						(glUniform1dv_),
		glUniform2dv						(glUniform2dv_),
		glUniform3dv						(glUniform3dv_),
		glUniform4dv						(glUniform4dv_),
		glUniformMatrix2dv					(glUniformMatrix2dv_),
		glUniformMatrix3dv					(glUniformMatrix3dv_),
		glUniformMatrix4dv					(glUniformMatrix4dv_),
		glUniformMatrix2x3dv				(glUniformMatrix2x3dv_),
		glUniformMatrix2x4dv				(glUniformMatrix2x4dv_),
		glUniformMatrix3x2dv				(glUniformMatrix3x2dv_),
		glUniformMatrix3x4dv				(glUniformMatrix3x4dv_),
		glUniformMatrix4x2dv				(glUniformMatrix4x2dv_),
		glUniformMatrix4x3dv				(glUniformMatrix4x3dv_),
		glGetUniformdv						(glGetUniformdv_),
		glGetSubroutineUniformLocation		(glGetSubroutineUniformLocation_),
		glGetSubroutineIndex				(glGetSubroutineIndex_),
		glGetActiveSubroutineUniformiv		(glGetActiveSubroutineUniformiv_),
		glGetActiveSubroutineUniformName	(glGetActiveSubroutineUniformName_),
		glGetActiveSubroutineName			(glGetActiveSubroutineName_),
		glUniformSubroutinesuiv				(glUniformSubroutinesuiv_),
		glGetUniformSubroutineuiv			(glGetUniformSubroutineuiv_),
		glGetProgramStageiv					(glGetProgramStageiv_),
		glPatchParameteri					(glPatchParameteri_),
		glPatchParameterfv					(glPatchParameterfv_),
		glBindTransformFeedback				(glBindTransformFeedback_),
		glDeleteTransformFeedbacks			(glDeleteTransformFeedbacks_),
		glGenTransformFeedbacks				(glGenTransformFeedbacks_),
		glIsTransformFeedback				(glIsTransformFeedback_),
		glPauseTransformFeedback			(glPauseTransformFeedback_),
		glResumeTransformFeedback			(glResumeTransformFeedback_),
		glDrawTransformFeedback				(glDrawTransformFeedback_),
		glDrawTransformFeedbackStream		(glDrawTransformFeedbackStream_),
		glBeginQueryIndexed					(glBeginQueryIndexed_),
		glEndQueryIndexed					(glEndQueryIndexed_),
		glGetQueryIndexediv					(glGetQueryIndexediv_)
	{
	}
#pragma endregion
#pragma region Interface_4_1
	Interface_4_1::Interface_4_1(
		const PFNGLRELEASESHADERCOMPILERPROC&			glReleaseShaderCompiler_,
		const PFNGLSHADERBINARYPROC&					glShaderBinary_,	
		const PFNGLGETSHADERPRECISIONFORMATPROC&		glGetShaderPrecisionFormat_,	
		const PFNGLDEPTHRANGEFPROC&						glDepthRangef_,
		const PFNGLCLEARDEPTHFPROC&						glClearDepthf_,
		const PFNGLGETPROGRAMBINARYPROC&				glGetProgramBinary_,	
		const PFNGLPROGRAMBINARYPROC&					glProgramBinary_,
		const PFNGLPROGRAMPARAMETERIPROC&				glProgramParameteri_,
		const PFNGLUSEPROGRAMSTAGESPROC&				glUseProgramStages_,	
		const PFNGLACTIVESHADERPROGRAMPROC&				glActiveShaderProgram_,
		const PFNGLCREATESHADERPROGRAMVPROC&			glCreateShaderProgramv_,	
		const PFNGLBINDPROGRAMPIPELINEPROC&				glBindProgramPipeline_,
		const PFNGLDELETEPROGRAMPIPELINESPROC&			glDeleteProgramPipelines_,
		const PFNGLGENPROGRAMPIPELINESPROC&				glGenProgramPipelines_,
		const PFNGLISPROGRAMPIPELINEPROC&				glIsProgramPipeline_,
		const PFNGLGETPROGRAMPIPELINEIVPROC&			glGetProgramPipelineiv_,	
		const PFNGLPROGRAMUNIFORM1IPROC&				glProgramUniform1i_,	
		const PFNGLPROGRAMUNIFORM1IVPROC&				glProgramUniform1iv_,
		const PFNGLPROGRAMUNIFORM1FPROC&				glProgramUniform1f_,	
		const PFNGLPROGRAMUNIFORM1FVPROC&				glProgramUniform1fv_,
		const PFNGLPROGRAMUNIFORM1DPROC&				glProgramUniform1d_,	
		const PFNGLPROGRAMUNIFORM1DVPROC&				glProgramUniform1dv_,
		const PFNGLPROGRAMUNIFORM1UIPROC&				glProgramUniform1ui_,
		const PFNGLPROGRAMUNIFORM1UIVPROC&				glProgramUniform1uiv_,
		const PFNGLPROGRAMUNIFORM2IPROC&				glProgramUniform2i_,	
		const PFNGLPROGRAMUNIFORM2IVPROC&				glProgramUniform2iv_,
		const PFNGLPROGRAMUNIFORM2FPROC&				glProgramUniform2f_,	
		const PFNGLPROGRAMUNIFORM2FVPROC&				glProgramUniform2fv_,
		const PFNGLPROGRAMUNIFORM2DPROC&				glProgramUniform2d_,	
		const PFNGLPROGRAMUNIFORM2DVPROC&				glProgramUniform2dv_,
		const PFNGLPROGRAMUNIFORM2UIPROC&				glProgramUniform2ui_,
		const PFNGLPROGRAMUNIFORM2UIVPROC&				glProgramUniform2uiv_,
		const PFNGLPROGRAMUNIFORM3IPROC&				glProgramUniform3i_,	
		const PFNGLPROGRAMUNIFORM3IVPROC&				glProgramUniform3iv_,
		const PFNGLPROGRAMUNIFORM3FPROC&				glProgramUniform3f_,	
		const PFNGLPROGRAMUNIFORM3FVPROC&				glProgramUniform3fv_,
		const PFNGLPROGRAMUNIFORM3DPROC&				glProgramUniform3d_,	
		const PFNGLPROGRAMUNIFORM3DVPROC&				glProgramUniform3dv_,
		const PFNGLPROGRAMUNIFORM3UIPROC&				glProgramUniform3ui_,
		const PFNGLPROGRAMUNIFORM3UIVPROC&				glProgramUniform3uiv_,
		const PFNGLPROGRAMUNIFORM4IPROC&				glProgramUniform4i_,	
		const PFNGLPROGRAMUNIFORM4IVPROC&				glProgramUniform4iv_,
		const PFNGLPROGRAMUNIFORM4FPROC&				glProgramUniform4f_,	
		const PFNGLPROGRAMUNIFORM4FVPROC&				glProgramUniform4fv_,
		const PFNGLPROGRAMUNIFORM4DPROC&				glProgramUniform4d_,	
		const PFNGLPROGRAMUNIFORM4DVPROC&				glProgramUniform4dv_,
		const PFNGLPROGRAMUNIFORM4UIPROC&				glProgramUniform4ui_,
		const PFNGLPROGRAMUNIFORM4UIVPROC&				glProgramUniform4uiv_,
		const PFNGLPROGRAMUNIFORMMATRIX2FVPROC&			glProgramUniformMatrix2fv_,
		const PFNGLPROGRAMUNIFORMMATRIX3FVPROC&			glProgramUniformMatrix3fv_,
		const PFNGLPROGRAMUNIFORMMATRIX4FVPROC&			glProgramUniformMatrix4fv_,
		const PFNGLPROGRAMUNIFORMMATRIX2DVPROC&			glProgramUniformMatrix2dv_,
		const PFNGLPROGRAMUNIFORMMATRIX3DVPROC&			glProgramUniformMatrix3dv_,
		const PFNGLPROGRAMUNIFORMMATRIX4DVPROC&			glProgramUniformMatrix4dv_,
		const PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC&		glProgramUniformMatrix2x3fv_,
		const PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC&		glProgramUniformMatrix3x2fv_,
		const PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC&		glProgramUniformMatrix2x4fv_,
		const PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC&		glProgramUniformMatrix4x2fv_,
		const PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC&		glProgramUniformMatrix3x4fv_,
		const PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC&		glProgramUniformMatrix4x3fv_,
		const PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC&		glProgramUniformMatrix2x3dv_,
		const PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC&		glProgramUniformMatrix3x2dv_,
		const PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC&		glProgramUniformMatrix2x4dv_,
		const PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC&		glProgramUniformMatrix4x2dv_,
		const PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC&		glProgramUniformMatrix3x4dv_,
		const PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC&		glProgramUniformMatrix4x3dv_,
		const PFNGLVALIDATEPROGRAMPIPELINEPROC&			glValidateProgramPipeline_,
		const PFNGLGETPROGRAMPIPELINEINFOLOGPROC&		glGetProgramPipelineInfoLog_,
		const PFNGLVERTEXATTRIBL1DPROC&					glVertexAttribL1d_,
		const PFNGLVERTEXATTRIBL2DPROC&					glVertexAttribL2d_,
		const PFNGLVERTEXATTRIBL3DPROC&					glVertexAttribL3d_,
		const PFNGLVERTEXATTRIBL4DPROC&					glVertexAttribL4d_,
		const PFNGLVERTEXATTRIBL1DVPROC&				glVertexAttribL1dv_,	
		const PFNGLVERTEXATTRIBL2DVPROC&				glVertexAttribL2dv_,	
		const PFNGLVERTEXATTRIBL3DVPROC&				glVertexAttribL3dv_,	
		const PFNGLVERTEXATTRIBL4DVPROC&				glVertexAttribL4dv_,	
		const PFNGLVERTEXATTRIBLPOINTERPROC&			glVertexAttribLPointer_,	
		const PFNGLGETVERTEXATTRIBLDVPROC&				glGetVertexAttribLdv_,
		const PFNGLVIEWPORTARRAYVPROC&					glViewportArrayv_,
		const PFNGLVIEWPORTINDEXEDFPROC&				glViewportIndexedf_,	
		const PFNGLVIEWPORTINDEXEDFVPROC&				glViewportIndexedfv_,
		const PFNGLSCISSORARRAYVPROC&					glScissorArrayv_,
		const PFNGLSCISSORINDEXEDPROC&					glScissorIndexed_,
		const PFNGLSCISSORINDEXEDVPROC&					glScissorIndexedv_,
		const PFNGLDEPTHRANGEARRAYVPROC&				glDepthRangeArrayv_,
		const PFNGLDEPTHRANGEINDEXEDPROC&				glDepthRangeIndexed_,
		const PFNGLGETFLOATI_VPROC&						glGetFloati_v_,
		const PFNGLGETDOUBLEI_VPROC&					glGetDoublei_v_
	):
		glReleaseShaderCompiler			(glReleaseShaderCompiler_),
		glShaderBinary					(glShaderBinary_),
		glGetShaderPrecisionFormat		(glGetShaderPrecisionFormat_),
		glDepthRangef					(glDepthRangef_),
		glClearDepthf					(glClearDepthf_),
		glGetProgramBinary				(glGetProgramBinary_),
		glProgramBinary					(glProgramBinary_),
		glProgramParameteri				(glProgramParameteri_),
		glUseProgramStages				(glUseProgramStages_),
		glActiveShaderProgram			(glActiveShaderProgram_),
		glCreateShaderProgramv			(glCreateShaderProgramv_),
		glBindProgramPipeline			(glBindProgramPipeline_),
		glDeleteProgramPipelines		(glDeleteProgramPipelines_),
		glGenProgramPipelines			(glGenProgramPipelines_),
		glIsProgramPipeline				(glIsProgramPipeline_),
		glGetProgramPipelineiv			(glGetProgramPipelineiv_),
		glProgramUniform1i				(glProgramUniform1i_),
		glProgramUniform1iv				(glProgramUniform1iv_),
		glProgramUniform1f				(glProgramUniform1f_),
		glProgramUniform1fv				(glProgramUniform1fv_),
		glProgramUniform1d				(glProgramUniform1d_),
		glProgramUniform1dv				(glProgramUniform1dv_),
		glProgramUniform1ui				(glProgramUniform1ui_),
		glProgramUniform1uiv			(glProgramUniform1uiv_),
		glProgramUniform2i				(glProgramUniform2i_),
		glProgramUniform2iv				(glProgramUniform2iv_),
		glProgramUniform2f				(glProgramUniform2f_),
		glProgramUniform2fv				(glProgramUniform2fv_),
		glProgramUniform2d				(glProgramUniform2d_),
		glProgramUniform2dv				(glProgramUniform2dv_),
		glProgramUniform2ui				(glProgramUniform2ui_),
		glProgramUniform2uiv			(glProgramUniform2uiv_),
		glProgramUniform3i				(glProgramUniform3i_),
		glProgramUniform3iv				(glProgramUniform3iv_),
		glProgramUniform3f				(glProgramUniform3f_),
		glProgramUniform3fv				(glProgramUniform3fv_),
		glProgramUniform3d				(glProgramUniform3d_),
		glProgramUniform3dv				(glProgramUniform3dv_),
		glProgramUniform3ui				(glProgramUniform3ui_),
		glProgramUniform3uiv			(glProgramUniform3uiv_),
		glProgramUniform4i				(glProgramUniform4i_),
		glProgramUniform4iv				(glProgramUniform4iv_),
		glProgramUniform4f				(glProgramUniform4f_),
		glProgramUniform4fv				(glProgramUniform4fv_),
		glProgramUniform4d				(glProgramUniform4d_),
		glProgramUniform4dv				(glProgramUniform4dv_),
		glProgramUniform4ui				(glProgramUniform4ui_),
		glProgramUniform4uiv			(glProgramUniform4uiv_),
		glProgramUniformMatrix2fv		(glProgramUniformMatrix2fv_),
		glProgramUniformMatrix3fv		(glProgramUniformMatrix3fv_),
		glProgramUniformMatrix4fv		(glProgramUniformMatrix4fv_),
		glProgramUniformMatrix2dv		(glProgramUniformMatrix2dv_),
		glProgramUniformMatrix3dv		(glProgramUniformMatrix3dv_),
		glProgramUniformMatrix4dv		(glProgramUniformMatrix4dv_),
		glProgramUniformMatrix2x3fv		(glProgramUniformMatrix2x3fv_),
		glProgramUniformMatrix3x2fv		(glProgramUniformMatrix3x2fv_),
		glProgramUniformMatrix2x4fv		(glProgramUniformMatrix2x4fv_),
		glProgramUniformMatrix4x2fv		(glProgramUniformMatrix4x2fv_),
		glProgramUniformMatrix3x4fv		(glProgramUniformMatrix3x4fv_),
		glProgramUniformMatrix4x3fv		(glProgramUniformMatrix4x3fv_),
		glProgramUniformMatrix2x3dv		(glProgramUniformMatrix2x3dv_),
		glProgramUniformMatrix3x2dv		(glProgramUniformMatrix3x2dv_),
		glProgramUniformMatrix2x4dv		(glProgramUniformMatrix2x4dv_),
		glProgramUniformMatrix4x2dv		(glProgramUniformMatrix4x2dv_),
		glProgramUniformMatrix3x4dv		(glProgramUniformMatrix3x4dv_),
		glProgramUniformMatrix4x3dv		(glProgramUniformMatrix4x3dv_),
		glValidateProgramPipeline		(glValidateProgramPipeline_),
		glGetProgramPipelineInfoLog		(glGetProgramPipelineInfoLog_),
		glVertexAttribL1d				(glVertexAttribL1d_),
		glVertexAttribL2d				(glVertexAttribL2d_),
		glVertexAttribL3d				(glVertexAttribL3d_),
		glVertexAttribL4d				(glVertexAttribL4d_),
		glVertexAttribL1dv				(glVertexAttribL1dv_),
		glVertexAttribL2dv				(glVertexAttribL2dv_),
		glVertexAttribL3dv				(glVertexAttribL3dv_),
		glVertexAttribL4dv				(glVertexAttribL4dv_),
		glVertexAttribLPointer			(glVertexAttribLPointer_),
		glGetVertexAttribLdv			(glGetVertexAttribLdv_),
		glViewportArrayv				(glViewportArrayv_),
		glViewportIndexedf				(glViewportIndexedf_),
		glViewportIndexedfv				(glViewportIndexedfv_),
		glScissorArrayv					(glScissorArrayv_),
		glScissorIndexed				(glScissorIndexed_),
		glScissorIndexedv				(glScissorIndexedv_),
		glDepthRangeArrayv				(glDepthRangeArrayv_),
		glDepthRangeIndexed				(glDepthRangeIndexed_),
		glGetFloati_v					(glGetFloati_v_),
		glGetDoublei_v					(glGetDoublei_v_)
	{
	}
#pragma endregion
#pragma region Interface_4_2
	Interface_4_2::Interface_4_2(
		const PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC&				glDrawArraysInstancedBaseInstance_,
		const PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC&			glDrawElementsInstancedBaseInstance_,
		const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC&	glDrawElementsInstancedBaseVertexBaseInstance_,
		const PFNGLGETINTERNALFORMATIVPROC&							glGetInternalformativ_,
		const PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC&				glGetActiveAtomicCounterBufferiv_,
		const PFNGLBINDIMAGETEXTUREPROC&							glBindImageTexture_,
		const PFNGLMEMORYBARRIERPROC&								glMemoryBarrier_,
		const PFNGLTEXSTORAGE1DPROC&								glTexStorage1D_,
		const PFNGLTEXSTORAGE2DPROC&								glTexStorage2D_,
		const PFNGLTEXSTORAGE3DPROC&								glTexStorage3D_,
		const PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC&				glDrawTransformFeedbackInstanced_,
		const PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC&		glDrawTransformFeedbackStreamInstanced_
	):
		glDrawArraysInstancedBaseInstance				(glDrawArraysInstancedBaseInstance_),
		glDrawElementsInstancedBaseInstance				(glDrawElementsInstancedBaseInstance_),
		glDrawElementsInstancedBaseVertexBaseInstance	(glDrawElementsInstancedBaseVertexBaseInstance_),
		glGetInternalformativ							(glGetInternalformativ_),
		glGetActiveAtomicCounterBufferiv				(glGetActiveAtomicCounterBufferiv_),
		glBindImageTexture								(glBindImageTexture_),
		glMemoryBarrier									(glMemoryBarrier_),
		glTexStorage1D									(glTexStorage1D_),
		glTexStorage2D									(glTexStorage2D_),
		glTexStorage3D									(glTexStorage3D_),
		glDrawTransformFeedbackInstanced				(glDrawTransformFeedbackInstanced_),
		glDrawTransformFeedbackStreamInstanced			(glDrawTransformFeedbackStreamInstanced_)
	{
	}
#pragma endregion
#pragma region Interface_4_3
	Interface_4_3::Interface_4_3(
		const PFNGLCLEARBUFFERDATAPROC&						glClearBufferData_,
		const PFNGLCLEARBUFFERSUBDATAPROC&					glClearBufferSubData_,
		const PFNGLDISPATCHCOMPUTEPROC&						glDispatchCompute_,
		const PFNGLDISPATCHCOMPUTEINDIRECTPROC&				glDispatchComputeIndirect_,
		const PFNGLCOPYIMAGESUBDATAPROC&					glCopyImageSubData_,
		const PFNGLFRAMEBUFFERPARAMETERIPROC&				glFramebufferParameteri_,
		const PFNGLGETFRAMEBUFFERPARAMETERIVPROC&			glGetFramebufferParameteriv_,
		const PFNGLGETINTERNALFORMATI64VPROC&				glGetInternalformati64v_,
		const PFNGLINVALIDATETEXSUBIMAGEPROC&				glInvalidateTexSubImage_,
		const PFNGLINVALIDATETEXIMAGEPROC&					glInvalidateTexImage_,
		const PFNGLINVALIDATEBUFFERSUBDATAPROC&				glInvalidateBufferSubData_,
		const PFNGLINVALIDATEBUFFERDATAPROC&				glInvalidateBufferData_,
		const PFNGLINVALIDATEFRAMEBUFFERPROC&				glInvalidateFramebuffer_,
		const PFNGLINVALIDATESUBFRAMEBUFFERPROC&			glInvalidateSubFramebuffer_,
		const PFNGLMULTIDRAWARRAYSINDIRECTPROC&				glMultiDrawArraysIndirect_,
		const PFNGLMULTIDRAWELEMENTSINDIRECTPROC&			glMultiDrawElementsIndirect_,
		const PFNGLGETPROGRAMINTERFACEIVPROC&				glGetProgramInterfaceiv_,
		const PFNGLGETPROGRAMRESOURCEINDEXPROC&				glGetProgramResourceIndex_,
		const PFNGLGETPROGRAMRESOURCENAMEPROC&				glGetProgramResourceName_,
		const PFNGLGETPROGRAMRESOURCEIVPROC&				glGetProgramResourceiv_,
		const PFNGLGETPROGRAMRESOURCELOCATIONPROC&			glGetProgramResourceLocation_,
		const PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC&		glGetProgramResourceLocationIndex_,
		const PFNGLSHADERSTORAGEBLOCKBINDINGPROC&			glShaderStorageBlockBinding_,
		const PFNGLTEXBUFFERRANGEPROC&						glTexBufferRange_,
		const PFNGLTEXSTORAGE2DMULTISAMPLEPROC&				glTexStorage2DMultisample_,
		const PFNGLTEXSTORAGE3DMULTISAMPLEPROC&				glTexStorage3DMultisample_,
		const PFNGLTEXTUREVIEWPROC&							glTextureView_,
		const PFNGLBINDVERTEXBUFFERPROC&					glBindVertexBuffer_,
		const PFNGLVERTEXATTRIBFORMATPROC&					glVertexAttribFormat_,
		const PFNGLVERTEXATTRIBIFORMATPROC&					glVertexAttribIFormat_,
		const PFNGLVERTEXATTRIBLFORMATPROC&					glVertexAttribLFormat_,
		const PFNGLVERTEXATTRIBBINDINGPROC&					glVertexAttribBinding_,
		const PFNGLVERTEXBINDINGDIVISORPROC&				glVertexBindingDivisor_,
		const PFNGLDEBUGMESSAGECONTROLPROC&					glDebugMessageControl_,
		const PFNGLDEBUGMESSAGEINSERTPROC&					glDebugMessageInsert_,
		const PFNGLDEBUGMESSAGECALLBACKPROC&				glDebugMessageCallback_,
		const PFNGLGETDEBUGMESSAGELOGPROC&					glGetDebugMessageLog_,
		const PFNGLPUSHDEBUGGROUPPROC&						glPushDebugGroup_,
		const PFNGLPOPDEBUGGROUPPROC&						glPopDebugGroup_,
		const PFNGLOBJECTLABELPROC&							glObjectLabel_,
		const PFNGLGETOBJECTLABELPROC&						glGetObjectLabel_,
		const PFNGLOBJECTPTRLABELPROC&						glObjectPtrLabel_,
		const PFNGLGETOBJECTPTRLABELPROC&					glGetObjectPtrLabel_
	):
		glClearBufferData					(glClearBufferData_),
		glClearBufferSubData				(glClearBufferSubData_),
		glDispatchCompute					(glDispatchCompute_),
		glDispatchComputeIndirect			(glDispatchComputeIndirect_),
		glCopyImageSubData					(glCopyImageSubData_),
		glFramebufferParameteri				(glFramebufferParameteri_),
		glGetFramebufferParameteriv			(glGetFramebufferParameteriv_),
		glGetInternalformati64v				(glGetInternalformati64v_),
		glInvalidateTexSubImage				(glInvalidateTexSubImage_),
		glInvalidateTexImage				(glInvalidateTexImage_),
		glInvalidateBufferSubData			(glInvalidateBufferSubData_),
		glInvalidateBufferData				(glInvalidateBufferData_),
		glInvalidateFramebuffer				(glInvalidateFramebuffer_),
		glInvalidateSubFramebuffer			(glInvalidateSubFramebuffer_),
		glMultiDrawArraysIndirect			(glMultiDrawArraysIndirect_),
		glMultiDrawElementsIndirect			(glMultiDrawElementsIndirect_),
		glGetProgramInterfaceiv				(glGetProgramInterfaceiv_),
		glGetProgramResourceIndex			(glGetProgramResourceIndex_),
		glGetProgramResourceName			(glGetProgramResourceName_),
		glGetProgramResourceiv				(glGetProgramResourceiv_),
		glGetProgramResourceLocation		(glGetProgramResourceLocation_),
		glGetProgramResourceLocationIndex	(glGetProgramResourceLocationIndex_),
		glShaderStorageBlockBinding			(glShaderStorageBlockBinding_),
		glTexBufferRange					(glTexBufferRange_),
		glTexStorage2DMultisample			(glTexStorage2DMultisample_),
		glTexStorage3DMultisample			(glTexStorage3DMultisample_),
		glTextureView						(glTextureView_),
		glBindVertexBuffer					(glBindVertexBuffer_),
		glVertexAttribFormat				(glVertexAttribFormat_),
		glVertexAttribIFormat				(glVertexAttribIFormat_),
		glVertexAttribLFormat				(glVertexAttribLFormat_),
		glVertexAttribBinding				(glVertexAttribBinding_),
		glVertexBindingDivisor				(glVertexBindingDivisor_),
		glDebugMessageControl				(glDebugMessageControl_),
		glDebugMessageInsert				(glDebugMessageInsert_),
		glDebugMessageCallback				(glDebugMessageCallback_),
		glGetDebugMessageLog				(glGetDebugMessageLog_),
		glPushDebugGroup					(glPushDebugGroup_),
		glPopDebugGroup						(glPopDebugGroup_),
		glObjectLabel						(glObjectLabel_),
		glGetObjectLabel					(glGetObjectLabel_),
		glObjectPtrLabel					(glObjectPtrLabel_),
		glGetObjectPtrLabel					(glGetObjectPtrLabel_)
	{
	}
#pragma endregion
#pragma region Interface_4_4
	Interface_4_4::Interface_4_4(
		const PFNGLBUFFERSTORAGEPROC&		glBufferStorage_,
		const PFNGLCLEARTEXIMAGEPROC&		glClearTexImage_,
		const PFNGLCLEARTEXSUBIMAGEPROC&	glClearTexSubImage_,
		const PFNGLBINDBUFFERSBASEPROC&		glBindBuffersBase_,
		const PFNGLBINDBUFFERSRANGEPROC&	glBindBuffersRange_,
		const PFNGLBINDTEXTURESPROC&		glBindTextures_,
		const PFNGLBINDSAMPLERSPROC&		glBindSamplers_,
		const PFNGLBINDIMAGETEXTURESPROC&	glBindImageTextures_,
		const PFNGLBINDVERTEXBUFFERSPROC&	glBindVertexBuffers_
	):
		glBufferStorage		(glBufferStorage_),
		glClearTexImage		(glClearTexImage_),
		glClearTexSubImage	(glClearTexSubImage_),
		glBindBuffersBase	(glBindBuffersBase_),
		glBindBuffersRange	(glBindBuffersRange_),
		glBindTextures		(glBindTextures_),
		glBindSamplers		(glBindSamplers_),
		glBindImageTextures	(glBindImageTextures_),
		glBindVertexBuffers	(glBindVertexBuffers_)
	{
	}
#pragma endregion
#pragma region Interface_4_5
	Interface_4_5::Interface_4_5(
		const PFNGLCLIPCONTROLPROC&									glClipControl_,
		const PFNGLCREATETRANSFORMFEEDBACKSPROC&					glCreateTransformFeedbacks_,
		const PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC&					glTransformFeedbackBufferBase_,
		const PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC&				glTransformFeedbackBufferRange_,
		const PFNGLGETTRANSFORMFEEDBACKIVPROC&						glGetTransformFeedbackiv_,
		const PFNGLGETTRANSFORMFEEDBACKI_VPROC&						glGetTransformFeedbacki_v_,
		const PFNGLGETTRANSFORMFEEDBACKI64_VPROC&					glGetTransformFeedbacki64_v_,
		const PFNGLCREATEBUFFERSPROC&								glCreateBuffers_,
		const PFNGLNAMEDBUFFERSTORAGEPROC&							glNamedBufferStorage_,
		const PFNGLNAMEDBUFFERDATAPROC&								glNamedBufferData_,
		const PFNGLNAMEDBUFFERSUBDATAPROC&							glNamedBufferSubData_,
		const PFNGLCOPYNAMEDBUFFERSUBDATAPROC&						glCopyNamedBufferSubData_,
		const PFNGLCLEARNAMEDBUFFERDATAPROC&						glClearNamedBufferData_,
		const PFNGLCLEARNAMEDBUFFERSUBDATAPROC&						glClearNamedBufferSubData_,
		const PFNGLMAPNAMEDBUFFERPROC&								glMapNamedBuffer_,
		const PFNGLMAPNAMEDBUFFERRANGEPROC&							glMapNamedBufferRange_,
		const PFNGLUNMAPNAMEDBUFFERPROC&							glUnmapNamedBuffer_,
		const PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC&					glFlushMappedNamedBufferRange_,
		const PFNGLGETNAMEDBUFFERPARAMETERIVPROC&					glGetNamedBufferParameteriv_,
		const PFNGLGETNAMEDBUFFERPARAMETERI64VPROC&					glGetNamedBufferParameteri64v_,
		const PFNGLGETNAMEDBUFFERPOINTERVPROC&						glGetNamedBufferPointerv_,
		const PFNGLGETNAMEDBUFFERSUBDATAPROC&						glGetNamedBufferSubData_,
		const PFNGLCREATEFRAMEBUFFERSPROC&							glCreateFramebuffers_,
		const PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC&				glNamedFramebufferRenderbuffer_,
		const PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC&					glNamedFramebufferParameteri_,
		const PFNGLNAMEDFRAMEBUFFERTEXTUREPROC&						glNamedFramebufferTexture_,
		const PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC&				glNamedFramebufferTextureLayer_,
		const PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC&					glNamedFramebufferDrawBuffer_,
		const PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC&					glNamedFramebufferDrawBuffers_,
		const PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC&					glNamedFramebufferReadBuffer_,
		const PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC&				glInvalidateNamedFramebufferData_,
		const PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC&			glInvalidateNamedFramebufferSubData_,
		const PFNGLCLEARNAMEDFRAMEBUFFERIVPROC&						glClearNamedFramebufferiv_,
		const PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC&					glClearNamedFramebufferuiv_,
		const PFNGLCLEARNAMEDFRAMEBUFFERFVPROC&						glClearNamedFramebufferfv_,
		const PFNGLCLEARNAMEDFRAMEBUFFERFIPROC&						glClearNamedFramebufferfi_,
		const PFNGLBLITNAMEDFRAMEBUFFERPROC&						glBlitNamedFramebuffer_,
		const PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC&					glCheckNamedFramebufferStatus_,
		const PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC&				glGetNamedFramebufferParameteriv_,
		const PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC&	glGetNamedFramebufferAttachmentParameteriv_,
		const PFNGLCREATERENDERBUFFERSPROC&							glCreateRenderbuffers_,
		const PFNGLNAMEDRENDERBUFFERSTORAGEPROC&					glNamedRenderbufferStorage_,
		const PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC&			glNamedRenderbufferStorageMultisample_,
		const PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC&				glGetNamedRenderbufferParameteriv_,
		const PFNGLCREATETEXTURESPROC&								glCreateTextures_,
		const PFNGLTEXTUREBUFFERPROC&								glTextureBuffer_,
		const PFNGLTEXTUREBUFFERRANGEPROC&							glTextureBufferRange_,
		const PFNGLTEXTURESTORAGE1DPROC&							glTextureStorage1D_,
		const PFNGLTEXTURESTORAGE2DPROC&							glTextureStorage2D_,
		const PFNGLTEXTURESTORAGE3DPROC&							glTextureStorage3D_,
		const PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC&					glTextureStorage2DMultisample_,
		const PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC&					glTextureStorage3DMultisample_,
		const PFNGLTEXTURESUBIMAGE1DPROC&							glTextureSubImage1D_,
		const PFNGLTEXTURESUBIMAGE2DPROC&							glTextureSubImage2D_,
		const PFNGLTEXTURESUBIMAGE3DPROC&							glTextureSubImage3D_,
		const PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC&					glCompressedTextureSubImage1D_,
		const PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC&					glCompressedTextureSubImage2D_,
		const PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC&					glCompressedTextureSubImage3D_,
		const PFNGLCOPYTEXTURESUBIMAGE1DPROC&						glCopyTextureSubImage1D_,
		const PFNGLCOPYTEXTURESUBIMAGE2DPROC&						glCopyTextureSubImage2D_,
		const PFNGLCOPYTEXTURESUBIMAGE3DPROC&						glCopyTextureSubImage3D_,
		const PFNGLTEXTUREPARAMETERFPROC&							glTextureParameterf_,
		const PFNGLTEXTUREPARAMETERFVPROC&							glTextureParameterfv_,
		const PFNGLTEXTUREPARAMETERIPROC&							glTextureParameteri_,
		const PFNGLTEXTUREPARAMETERIIVPROC&							glTextureParameterIiv_,
		const PFNGLTEXTUREPARAMETERIUIVPROC&						glTextureParameterIuiv_,
		const PFNGLTEXTUREPARAMETERIVPROC&							glTextureParameteriv_,
		const PFNGLGENERATETEXTUREMIPMAPPROC&						glGenerateTextureMipmap_,
		const PFNGLBINDTEXTUREUNITPROC&								glBindTextureUnit_,
		const PFNGLGETTEXTUREIMAGEPROC&								glGetTextureImage_,
		const PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC&					glGetCompressedTextureImage_,
		const PFNGLGETTEXTURELEVELPARAMETERFVPROC&					glGetTextureLevelParameterfv_,
		const PFNGLGETTEXTURELEVELPARAMETERIVPROC&					glGetTextureLevelParameteriv_,
		const PFNGLGETTEXTUREPARAMETERFVPROC&						glGetTextureParameterfv_,
		const PFNGLGETTEXTUREPARAMETERIIVPROC&						glGetTextureParameterIiv_,
		const PFNGLGETTEXTUREPARAMETERIUIVPROC&						glGetTextureParameterIuiv_,
		const PFNGLGETTEXTUREPARAMETERIVPROC&						glGetTextureParameteriv_,
		const PFNGLCREATEVERTEXARRAYSPROC&							glCreateVertexArrays_,
		const PFNGLDISABLEVERTEXARRAYATTRIBPROC&					glDisableVertexArrayAttrib_,
		const PFNGLENABLEVERTEXARRAYATTRIBPROC&						glEnableVertexArrayAttrib_,
		const PFNGLVERTEXARRAYELEMENTBUFFERPROC&					glVertexArrayElementBuffer_,
		const PFNGLVERTEXARRAYVERTEXBUFFERPROC&						glVertexArrayVertexBuffer_,
		const PFNGLVERTEXARRAYVERTEXBUFFERSPROC&					glVertexArrayVertexBuffers_,
		const PFNGLVERTEXARRAYATTRIBBINDINGPROC&					glVertexArrayAttribBinding_,
		const PFNGLVERTEXARRAYATTRIBFORMATPROC&						glVertexArrayAttribFormat_,
		const PFNGLVERTEXARRAYATTRIBIFORMATPROC&					glVertexArrayAttribIFormat_,
		const PFNGLVERTEXARRAYATTRIBLFORMATPROC&					glVertexArrayAttribLFormat_,
		const PFNGLVERTEXARRAYBINDINGDIVISORPROC&					glVertexArrayBindingDivisor_,
		const PFNGLGETVERTEXARRAYIVPROC&							glGetVertexArrayiv_,
		const PFNGLGETVERTEXARRAYINDEXEDIVPROC&						glGetVertexArrayIndexediv_,
		const PFNGLGETVERTEXARRAYINDEXED64IVPROC&					glGetVertexArrayIndexed64iv_,
		const PFNGLCREATESAMPLERSPROC&								glCreateSamplers_,
		const PFNGLCREATEPROGRAMPIPELINESPROC&						glCreateProgramPipelines_,
		const PFNGLCREATEQUERIESPROC&								glCreateQueries_,
		const PFNGLGETQUERYBUFFEROBJECTI64VPROC&					glGetQueryBufferObjecti64v_,
		const PFNGLGETQUERYBUFFEROBJECTIVPROC&						glGetQueryBufferObjectiv_,
		const PFNGLGETQUERYBUFFEROBJECTUI64VPROC&					glGetQueryBufferObjectui64v_,
		const PFNGLGETQUERYBUFFEROBJECTUIVPROC&						glGetQueryBufferObjectuiv_,
		const PFNGLMEMORYBARRIERBYREGIONPROC&						glMemoryBarrierByRegion_,
		const PFNGLGETTEXTURESUBIMAGEPROC&							glGetTextureSubImage_,
		const PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC&				glGetCompressedTextureSubImage_,
		const PFNGLGETGRAPHICSRESETSTATUSPROC&						glGetGraphicsResetStatus_,
		const PFNGLGETNCOMPRESSEDTEXIMAGEPROC&						glGetnCompressedTexImage_,
		const PFNGLGETNTEXIMAGEPROC&								glGetnTexImage_,
		const PFNGLGETNUNIFORMDVPROC&								glGetnUniformdv_,
		const PFNGLGETNUNIFORMFVPROC&								glGetnUniformfv_,
		const PFNGLGETNUNIFORMIVPROC&								glGetnUniformiv_,
		const PFNGLGETNUNIFORMUIVPROC&								glGetnUniformuiv_,
		const PFNGLREADNPIXELSPROC&									glReadnPixels_,
		const PFNGLGETNMAPDVPROC&									glGetnMapdv_,
		const PFNGLGETNMAPFVPROC&									glGetnMapfv_,
		const PFNGLGETNMAPIVPROC&									glGetnMapiv_,
		const PFNGLGETNPIXELMAPFVPROC&								glGetnPixelMapfv_,
		const PFNGLGETNPIXELMAPUIVPROC&								glGetnPixelMapuiv_,
		const PFNGLGETNPIXELMAPUSVPROC&								glGetnPixelMapusv_,
		const PFNGLGETNPOLYGONSTIPPLEPROC&							glGetnPolygonStipple_,
		const PFNGLGETNCOLORTABLEPROC&								glGetnColorTable_,
		const PFNGLGETNCONVOLUTIONFILTERPROC&						glGetnConvolutionFilter_,
		const PFNGLGETNSEPARABLEFILTERPROC&							glGetnSeparableFilter_,
		const PFNGLGETNHISTOGRAMPROC&								glGetnHistogram_,
		const PFNGLGETNMINMAXPROC&									glGetnMinmax_,
		const PFNGLTEXTUREBARRIERPROC&								glTextureBarrier_
	):
		glClipControl									(glClipControl_),
		glCreateTransformFeedbacks						(glCreateTransformFeedbacks_),
		glTransformFeedbackBufferBase					(glTransformFeedbackBufferBase_),
		glTransformFeedbackBufferRange					(glTransformFeedbackBufferRange_),
		glGetTransformFeedbackiv						(glGetTransformFeedbackiv_),
		glGetTransformFeedbacki_v						(glGetTransformFeedbacki_v_),
		glGetTransformFeedbacki64_v						(glGetTransformFeedbacki64_v_),
		glCreateBuffers									(glCreateBuffers_),
		glNamedBufferStorage							(glNamedBufferStorage_),
		glNamedBufferData								(glNamedBufferData_),
		glNamedBufferSubData							(glNamedBufferSubData_),
		glCopyNamedBufferSubData						(glCopyNamedBufferSubData_),
		glClearNamedBufferData							(glClearNamedBufferData_),
		glClearNamedBufferSubData						(glClearNamedBufferSubData_),
		glMapNamedBuffer								(glMapNamedBuffer_),
		glMapNamedBufferRange							(glMapNamedBufferRange_),
		glUnmapNamedBuffer								(glUnmapNamedBuffer_),
		glFlushMappedNamedBufferRange					(glFlushMappedNamedBufferRange_),
		glGetNamedBufferParameteriv						(glGetNamedBufferParameteriv_),
		glGetNamedBufferParameteri64v					(glGetNamedBufferParameteri64v_),
		glGetNamedBufferPointerv						(glGetNamedBufferPointerv_),
		glGetNamedBufferSubData							(glGetNamedBufferSubData_),
		glCreateFramebuffers							(glCreateFramebuffers_),
		glNamedFramebufferRenderbuffer					(glNamedFramebufferRenderbuffer_),
		glNamedFramebufferParameteri					(glNamedFramebufferParameteri_),
		glNamedFramebufferTexture						(glNamedFramebufferTexture_),
		glNamedFramebufferTextureLayer					(glNamedFramebufferTextureLayer_),
		glNamedFramebufferDrawBuffer					(glNamedFramebufferDrawBuffer_),
		glNamedFramebufferDrawBuffers					(glNamedFramebufferDrawBuffers_),
		glNamedFramebufferReadBuffer					(glNamedFramebufferReadBuffer_),
		glInvalidateNamedFramebufferData				(glInvalidateNamedFramebufferData_),
		glInvalidateNamedFramebufferSubData				(glInvalidateNamedFramebufferSubData_),
		glClearNamedFramebufferiv						(glClearNamedFramebufferiv_),
		glClearNamedFramebufferuiv						(glClearNamedFramebufferuiv_),
		glClearNamedFramebufferfv						(glClearNamedFramebufferfv_),
		glClearNamedFramebufferfi						(glClearNamedFramebufferfi_),
		glBlitNamedFramebuffer							(glBlitNamedFramebuffer_),
		glCheckNamedFramebufferStatus					(glCheckNamedFramebufferStatus_),
		glGetNamedFramebufferParameteriv				(glGetNamedFramebufferParameteriv_),
		glGetNamedFramebufferAttachmentParameteriv		(glGetNamedFramebufferAttachmentParameteriv_),
		glCreateRenderbuffers							(glCreateRenderbuffers_),
		glNamedRenderbufferStorage						(glNamedRenderbufferStorage_),
		glNamedRenderbufferStorageMultisample			(glNamedRenderbufferStorageMultisample_),
		glGetNamedRenderbufferParameteriv				(glGetNamedRenderbufferParameteriv_),
		glCreateTextures								(glCreateTextures_),
		glTextureBuffer									(glTextureBuffer_),
		glTextureBufferRange							(glTextureBufferRange_),
		glTextureStorage1D								(glTextureStorage1D_),
		glTextureStorage2D								(glTextureStorage2D_),
		glTextureStorage3D								(glTextureStorage3D_),
		glTextureStorage2DMultisample					(glTextureStorage2DMultisample_),
		glTextureStorage3DMultisample					(glTextureStorage3DMultisample_),
		glTextureSubImage1D								(glTextureSubImage1D_),
		glTextureSubImage2D								(glTextureSubImage2D_),
		glTextureSubImage3D								(glTextureSubImage3D_),
		glCompressedTextureSubImage1D					(glCompressedTextureSubImage1D_),
		glCompressedTextureSubImage2D					(glCompressedTextureSubImage2D_),
		glCompressedTextureSubImage3D					(glCompressedTextureSubImage3D_),
		glCopyTextureSubImage1D							(glCopyTextureSubImage1D_),
		glCopyTextureSubImage2D							(glCopyTextureSubImage2D_),
		glCopyTextureSubImage3D							(glCopyTextureSubImage3D_),
		glTextureParameterf								(glTextureParameterf_),
		glTextureParameterfv							(glTextureParameterfv_),
		glTextureParameteri								(glTextureParameteri_),
		glTextureParameterIiv							(glTextureParameterIiv_),
		glTextureParameterIuiv							(glTextureParameterIuiv_),
		glTextureParameteriv							(glTextureParameteriv_),
		glGenerateTextureMipmap							(glGenerateTextureMipmap_),
		glBindTextureUnit								(glBindTextureUnit_),
		glGetTextureImage								(glGetTextureImage_),
		glGetCompressedTextureImage						(glGetCompressedTextureImage_),
		glGetTextureLevelParameterfv					(glGetTextureLevelParameterfv_),
		glGetTextureLevelParameteriv					(glGetTextureLevelParameteriv_),
		glGetTextureParameterfv							(glGetTextureParameterfv_),
		glGetTextureParameterIiv						(glGetTextureParameterIiv_),
		glGetTextureParameterIuiv						(glGetTextureParameterIuiv_),
		glGetTextureParameteriv							(glGetTextureParameteriv_),
		glCreateVertexArrays							(glCreateVertexArrays_),
		glDisableVertexArrayAttrib						(glDisableVertexArrayAttrib_),
		glEnableVertexArrayAttrib						(glEnableVertexArrayAttrib_),
		glVertexArrayElementBuffer						(glVertexArrayElementBuffer_),
		glVertexArrayVertexBuffer						(glVertexArrayVertexBuffer_),
		glVertexArrayVertexBuffers						(glVertexArrayVertexBuffers_),
		glVertexArrayAttribBinding						(glVertexArrayAttribBinding_),
		glVertexArrayAttribFormat						(glVertexArrayAttribFormat_),
		glVertexArrayAttribIFormat						(glVertexArrayAttribIFormat_),
		glVertexArrayAttribLFormat						(glVertexArrayAttribLFormat_),
		glVertexArrayBindingDivisor						(glVertexArrayBindingDivisor_),
		glGetVertexArrayiv								(glGetVertexArrayiv_),
		glGetVertexArrayIndexediv						(glGetVertexArrayIndexediv_),
		glGetVertexArrayIndexed64iv						(glGetVertexArrayIndexed64iv_),
		glCreateSamplers								(glCreateSamplers_),
		glCreateProgramPipelines						(glCreateProgramPipelines_),
		glCreateQueries									(glCreateQueries_),
		glGetQueryBufferObjecti64v						(glGetQueryBufferObjecti64v_),
		glGetQueryBufferObjectiv						(glGetQueryBufferObjectiv_),
		glGetQueryBufferObjectui64v						(glGetQueryBufferObjectui64v_),
		glGetQueryBufferObjectuiv						(glGetQueryBufferObjectuiv_),
		glMemoryBarrierByRegion							(glMemoryBarrierByRegion_),
		glGetTextureSubImage							(glGetTextureSubImage_),
		glGetCompressedTextureSubImage					(glGetCompressedTextureSubImage_),
		glGetGraphicsResetStatus						(glGetGraphicsResetStatus_),
		glGetnCompressedTexImage						(glGetnCompressedTexImage_),
		glGetnTexImage									(glGetnTexImage_),
		glGetnUniformdv									(glGetnUniformdv_),
		glGetnUniformfv									(glGetnUniformfv_),
		glGetnUniformiv									(glGetnUniformiv_),
		glGetnUniformuiv								(glGetnUniformuiv_),
		glReadnPixels									(glReadnPixels_),
		glGetnMapdv										(glGetnMapdv_),
		glGetnMapfv										(glGetnMapfv_),
		glGetnMapiv										(glGetnMapiv_),
		glGetnPixelMapfv								(glGetnPixelMapfv_),
		glGetnPixelMapuiv								(glGetnPixelMapuiv_),
		glGetnPixelMapusv								(glGetnPixelMapusv_),
		glGetnPolygonStipple							(glGetnPolygonStipple_),
		glGetnColorTable								(glGetnColorTable_),
		glGetnConvolutionFilter							(glGetnConvolutionFilter_),
		glGetnSeparableFilter							(glGetnSeparableFilter_),
		glGetnHistogram									(glGetnHistogram_),
		glGetnMinmax									(glGetnMinmax_),
		glTextureBarrier								(glTextureBarrier_)
	{
	}
#pragma endregion

	class Context_1_0:
		public virtual Interface_1_0
	{
	};
	class Context_1_2:
		public Context_1_0,
		public virtual Interface_1_2
	{
	};
	class Context_1_3:
		public Context_1_2,
		public virtual Interface_1_3
	{
	};
	class Context_1_4:
		public Context_1_3,
		public virtual Interface_1_4
	{
	};
	class Context_1_5:
		public Context_1_4,
		public virtual Interface_1_5
	{
	};
	class Context_2_0:
		public Context_1_5,
		public virtual Interface_2_0
	{
	};
	class Context_2_1:
		public Context_2_0,
		public virtual Interface_2_1
	{
	};
	class Context_3_0:
		public Context_2_1,
		public virtual Interface_3_0
	{
	};
	class Context_3_1:
		public Context_3_0,
		public virtual Interface_3_1
	{
	};
	class Context_3_2:
		public Context_3_1,
		public virtual Interface_3_2
	{
	};
	class Context_3_3:
		public Context_3_2,
		public virtual Interface_3_3
	{
	};
	class Context_4_0:
		public Context_3_3,
		public virtual Interface_4_0
	{
	};
	class Context_4_1:
		public Context_4_0,
		public virtual Interface_4_1
	{
	};
	class Context_4_2:
		public Context_4_1,
		public virtual Interface_4_2
	{
	};
	class Context_4_3:
		public Context_4_2,
		public virtual Interface_4_3
	{
	};
	class Context_4_4:
		public Context_4_3,
		public virtual Interface_4_4
	{
	};
	class Context_4_5:
		public Context_4_4,
		public virtual Interface_4_5
	{
	};

#pragma region Context_1_0
#pragma endregion
#pragma region Context_1_2
#pragma endregion
#pragma region Context_1_3
#pragma endregion
#pragma region Context_1_4
#pragma endregion
#pragma region Context_1_5
#pragma endregion
#pragma region Context_2_0
#pragma endregion
#pragma region Context_2_1
#pragma endregion
#pragma region Context_3_0
#pragma endregion
#pragma region Context_3_1
#pragma endregion
#pragma region Context_3_2
#pragma endregion
#pragma region Context_3_3
#pragma endregion
#pragma region Context_4_0
#pragma endregion
#pragma region Context_4_1
#pragma endregion
#pragma region Context_4_2
#pragma endregion
#pragma region Context_4_3
#pragma endregion
#pragma region Context_4_4
#pragma endregion
#pragma region Context_4_5
#pragma endregion

	namespace OSs
	{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
		namespace Windows
		{
			class Context
			{
			protected:
				class EmptyTag {};
			protected:
				using Attributes			= Vector<GLint>;
			public:
				using Handle				= HGLRC;
				using DeviceContextHandle	= HDC;
				using Procedure				= PROC;
			};
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
				const Handle				handle;
			protected:
				inline						Context_1_0(const Handle& handle_);
			public:
				inline						Context_1_0(const DeviceContextHandle& deviceContextHandle_);
				inline						~Context_1_0();
			protected:
				inline void					CheckForCurrentContext() const;
				inline void					CheckForCurrentContext(const Handle& handle_) const; // TODO: remove this workaround
			public:
				inline Handle				GetHandle() const;
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
			class Context_1_2:
				public Context_1_0,
				protected OpenGL::Context_1_2
			{
			private:
				inline static Attributes GetAttributes();
			private:
				inline Context_1_2(const Handle& handle_);
			protected:
				inline Context_1_2(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_1_2(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_1_3:
				public Context_1_2,
				public OpenGL::Context_1_3
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_1_3(const Handle& handle_);
			protected:
				inline Context_1_3(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_1_3(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_1_4:
				public Context_1_3,
				public OpenGL::Context_1_4
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_1_4(const Handle& handle_);
			protected:
				inline Context_1_4(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_1_4(const DeviceContextHandle& deviceContextHandle_);
			};
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
			class Context_2_0:
				public Context_1_5,
				public OpenGL::Context_2_0
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_2_0(const Handle& handle_);
			protected:
				inline Context_2_0(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_2_0(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_2_1:
				public Context_2_0,
				public OpenGL::Context_2_1
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_2_1(const Handle& handle_);
			protected:
				inline Context_2_1(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_2_1(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_3_0:
				public Context_2_1,
				public OpenGL::Context_3_0
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_3_0(const Handle& handle_);
			protected:
				inline Context_3_0(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_3_0(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_3_1:
				public Context_3_0,
				public OpenGL::Context_3_1
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_3_1(const Handle& handle_);
			protected:
				inline Context_3_1(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_3_1(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_3_2:
				public Context_3_1,
				public OpenGL::Context_3_2
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_3_2(const Handle& handle_);
			protected:
				inline Context_3_2(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_3_2(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_3_3:
				public Context_3_2,
				public OpenGL::Context_3_3
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_3_3(const Handle& handle_);
			protected:
				inline Context_3_3(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_3_3(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_4_0:
				public Context_3_3,
				public OpenGL::Context_4_0
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_4_0(const Handle& handle_);
			protected:
				inline Context_4_0(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_4_0(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_4_1:
				public Context_4_0,
				public OpenGL::Context_4_1
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_4_1(const Handle& handle_);
			protected:
				inline Context_4_1(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_4_1(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_4_2:
				public Context_4_1,
				public OpenGL::Context_4_2
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_4_2(const Handle& handle_);
			protected:
				inline Context_4_2(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_4_2(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_4_3:
				public Context_4_2,
				public OpenGL::Context_4_3
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_4_3(const Handle& handle_);
			protected:
				inline Context_4_3(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_4_3(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_4_4:
				public Context_4_3,
				public OpenGL::Context_4_4
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_4_4(const Handle& handle_);
			protected:
				inline Context_4_4(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_4_4(const DeviceContextHandle& deviceContextHandle_);
			};
			class Context_4_5:
				public Context_4_4,
				public OpenGL::Context_4_5
			{
			protected:
				inline static Attributes GetAttributes();
			private:
				inline Context_4_5(const Handle& handle_);
			protected:
				inline Context_4_5(const Handle& handle_, const EmptyTag&);
			public:
				inline Context_4_5(const DeviceContextHandle& deviceContextHandle_);
			};

			
			inline Context::Handle		CreateContext(const Context::DeviceContextHandle& deviceContextHandle_); // TODO: move this functions to Windows namespace
			inline void					DeleteContext(const Context::Handle& handle_);
			inline Context::Handle		GetCurrentHandle();
			inline void					MakeCurrent(const Context::DeviceContextHandle& deviceContextHandle_, const Context::Handle& handle_);


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
				handle(handle_)
			{
			}
			Context_1_0::Context_1_0(const DeviceContextHandle& deviceContextHandle_):
				Context_1_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_1_0::~Context_1_0()
			{
				const auto &currentHandle = GetCurrentHandle();

				if (handle == currentHandle)
				{
					throw Exception();
				}
			}

			void Context_1_0::CheckForCurrentContext() const
			{
#if __GREAT_V_ENGINE_2__DEBUG__
				auto currentHandle = GetCurrentHandle();

				if (currentHandle != handle)
				{
					throw Exception();
				}
#endif
			}
			void Context_1_0::CheckForCurrentContext(const Handle& handle_) const
			{
#if __GREAT_V_ENGINE_2__DEBUG__
				auto currentHandle = GetCurrentHandle();

				if (currentHandle != handle_)
				{
					throw Exception();
				}
#endif
			}

			Context_1_0::Handle Context_1_0::GetHandle() const
			{
				return handle;
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
#pragma region Context_1_2
			Context_1_2::Attributes Context_1_2::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	1,
					WGL_CONTEXT_MINOR_VERSION_ARB,	2,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_1_2::Context_1_2(const Handle& handle_):
				Windows::Context_1_0(handle_),		// TODO: need to call this before GetProcedureAddress in Interface_1_2 constructor
				OpenGL::Context_1_2(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_1_2::Context_1_2(const Handle& handle_, const EmptyTag&):
				Windows::Context_1_0(handle_),
				OpenGL::Context_1_2(),
				Interface_1_2()
			{
			}
			Context_1_2::Context_1_2(const DeviceContextHandle& deviceContextHandle_):
				Context_1_2(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_1_3
			Context_1_3::Attributes Context_1_3::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	1,
					WGL_CONTEXT_MINOR_VERSION_ARB,	3,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_1_3::Context_1_3(const Handle& handle_, const EmptyTag&):
				Windows::Context_1_2(handle_, EmptyTag()),
				OpenGL::Context_1_3(),
				Interface_1_2(),
				Interface_1_3()
			{
			}
			Context_1_3::Context_1_3(const Handle& handle_):
				Windows::Context_1_2(handle_, EmptyTag()),
				OpenGL::Context_1_3(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_1_3::Context_1_3(const DeviceContextHandle& deviceContextHandle_):
				Context_1_3(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_1_4
			Context_1_4::Attributes Context_1_4::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	1,
					WGL_CONTEXT_MINOR_VERSION_ARB,	4,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_1_4::Context_1_4(const Handle& handle_, const EmptyTag&):
				Windows::Context_1_3(handle_, EmptyTag()),
				OpenGL::Context_1_4(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4()
			{
			}
			Context_1_4::Context_1_4(const Handle& handle_):
				Windows::Context_1_3(handle_, EmptyTag()),
				OpenGL::Context_1_4(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_1_4::Context_1_4(const DeviceContextHandle& deviceContextHandle_):
				Context_1_4(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_1_5
			Context_1_5::Attributes Context_1_5::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	1,
					WGL_CONTEXT_MINOR_VERSION_ARB,	5,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_1_5::Context_1_5(const Handle& handle_, const EmptyTag&):
				Windows::Context_1_4(handle_, EmptyTag()),
				OpenGL::Context_1_5(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5()
			{
			}
			Context_1_5::Context_1_5(const Handle& handle_):
				Windows::Context_1_4(handle_, EmptyTag()),
				OpenGL::Context_1_5(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
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
#pragma region Context_2_0
			Context_2_0::Attributes Context_2_0::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	2,
					WGL_CONTEXT_MINOR_VERSION_ARB,	0,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_2_0::Context_2_0(const Handle& handle_, const EmptyTag&):
				Windows::Context_1_5(handle_, EmptyTag()),
				OpenGL::Context_2_0(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0()
			{
			}
			Context_2_0::Context_2_0(const Handle& handle_):
				Windows::Context_1_5(handle_, EmptyTag()),
				OpenGL::Context_2_0(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_2_0::Context_2_0(const DeviceContextHandle& deviceContextHandle_):
				Context_2_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_2_1
			Context_2_1::Attributes Context_2_1::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	2,
					WGL_CONTEXT_MINOR_VERSION_ARB,	1,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_2_1::Context_2_1(const Handle& handle_, const EmptyTag&):
				Windows::Context_2_0(handle_, EmptyTag()),
				OpenGL::Context_2_1(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1()
			{
			}
			Context_2_1::Context_2_1(const Handle& handle_):
				Windows::Context_2_0(handle_, EmptyTag()),
				OpenGL::Context_2_1(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_2_1::Context_2_1(const DeviceContextHandle& deviceContextHandle_):
				Context_2_1(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_3_0
			Context_3_0::Attributes Context_3_0::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	3,
					WGL_CONTEXT_MINOR_VERSION_ARB,	0,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_3_0::Context_3_0(const Handle& handle_, const EmptyTag&):
				Windows::Context_2_1(handle_, EmptyTag()),
				OpenGL::Context_3_0(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0()
			{
			}
			Context_3_0::Context_3_0(const Handle& handle_):
				Windows::Context_2_1(handle_, EmptyTag()),
				OpenGL::Context_3_0(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_3_0::Context_3_0(const DeviceContextHandle& deviceContextHandle_):
				Context_3_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_3_1
			Context_3_1::Attributes Context_3_1::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	3,
					WGL_CONTEXT_MINOR_VERSION_ARB,	1,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_3_1::Context_3_1(const Handle& handle_, const EmptyTag&):
				Windows::Context_3_0(handle_, EmptyTag()),
				OpenGL::Context_3_1(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1()
			{
			}
			Context_3_1::Context_3_1(const Handle& handle_):
				Windows::Context_3_0(handle_, EmptyTag()),
				OpenGL::Context_3_1(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_3_1::Context_3_1(const DeviceContextHandle& deviceContextHandle_):
				Context_3_1(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_3_2
			Context_3_2::Attributes Context_3_2::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	3,
					WGL_CONTEXT_MINOR_VERSION_ARB,	2,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_3_2::Context_3_2(const Handle& handle_, const EmptyTag&):
				Windows::Context_3_1(handle_, EmptyTag()),
				OpenGL::Context_3_2(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2()
			{
			}
			Context_3_2::Context_3_2(const Handle& handle_):
				Windows::Context_3_1(handle_, EmptyTag()),
				OpenGL::Context_3_2(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_3_2::Context_3_2(const DeviceContextHandle& deviceContextHandle_):
				Context_3_2(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_3_3
			Context_3_3::Attributes Context_3_3::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	3,
					WGL_CONTEXT_MINOR_VERSION_ARB,	3,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_3_3::Context_3_3(const Handle& handle_, const EmptyTag&):
				Windows::Context_3_2(handle_, EmptyTag()),
				OpenGL::Context_3_3(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3()
			{
			}
			Context_3_3::Context_3_3(const Handle& handle_):
				Windows::Context_3_2(handle_, EmptyTag()),
				OpenGL::Context_3_3(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_3_3::Context_3_3(const DeviceContextHandle& deviceContextHandle_):
				Context_3_3(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_4_0
			Context_4_0::Attributes Context_4_0::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
					WGL_CONTEXT_MINOR_VERSION_ARB,	0,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_4_0::Context_4_0(const Handle& handle_, const EmptyTag&):
				Windows::Context_3_3(handle_, EmptyTag()),
				OpenGL::Context_4_0(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3(),
				Interface_4_0()
			{
			}
			Context_4_0::Context_4_0(const Handle& handle_):
				Windows::Context_3_3(handle_, EmptyTag()),
				OpenGL::Context_4_0(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				),
				Interface_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv,						handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_4_0::Context_4_0(const DeviceContextHandle& deviceContextHandle_):
				Context_4_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_4_1
			Context_4_1::Attributes Context_4_1::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
					WGL_CONTEXT_MINOR_VERSION_ARB,	1,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_4_1::Context_4_1(const Handle& handle_, const EmptyTag&):
				Windows::Context_4_0(handle_, EmptyTag()),
				OpenGL::Context_4_1(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3(),
				Interface_4_0(),
				Interface_4_1()
			{
			}
			Context_4_1::Context_4_1(const Handle& handle_):
				Windows::Context_4_0(handle_, EmptyTag()),
				OpenGL::Context_4_1(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				),
				Interface_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv,						handle_)
				),
				Interface_4_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReleaseShaderCompiler,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderPrecisionFormat,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangef,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearDepthf,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramBinary,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgramStages,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveShaderProgram,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShaderProgramv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgramPipelines,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenProgramPipelines,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgramPipeline,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineInfoLog,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLPointer,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribLdv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexed,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexedv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeArrayv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeIndexed,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFloati_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDoublei_v,				handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_4_1::Context_4_1(const DeviceContextHandle& deviceContextHandle_):
				Context_4_1(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_4_2
			Context_4_2::Attributes Context_4_2::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
					WGL_CONTEXT_MINOR_VERSION_ARB,	2,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_4_2::Context_4_2(const Handle& handle_, const EmptyTag&):
				Windows::Context_4_1(handle_, EmptyTag()),
				OpenGL::Context_4_2(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3(),
				Interface_4_0(),
				Interface_4_1(),
				Interface_4_2()
			{
			}
			Context_4_2::Context_4_2(const Handle& handle_):
				Windows::Context_4_1(handle_, EmptyTag()),
				OpenGL::Context_4_2(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				),
				Interface_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv,						handle_)
				),
				Interface_4_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReleaseShaderCompiler,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderPrecisionFormat,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangef,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearDepthf,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramBinary,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgramStages,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveShaderProgram,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShaderProgramv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgramPipelines,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenProgramPipelines,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgramPipeline,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineInfoLog,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLPointer,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribLdv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexed,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexedv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeArrayv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeIndexed,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFloati_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDoublei_v,				handle_)
				),
				Interface_4_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstancedBaseInstance,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseInstance,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertexBaseInstance,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformativ,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAtomicCounterBufferiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindImageTexture,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMemoryBarrier,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage1D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackInstanced,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStreamInstanced,		handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_4_2::Context_4_2(const DeviceContextHandle& deviceContextHandle_):
				Context_4_2(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_4_3
			Context_4_3::Attributes Context_4_3::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
					WGL_CONTEXT_MINOR_VERSION_ARB,	3,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_4_3::Context_4_3(const Handle& handle_, const EmptyTag&):
				Windows::Context_4_2(handle_, EmptyTag()),
				OpenGL::Context_4_3(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3(),
				Interface_4_0(),
				Interface_4_1(),
				Interface_4_2(),
				Interface_4_3()
			{
			}
			Context_4_3::Context_4_3(const Handle& handle_):
				Windows::Context_4_2(handle_, EmptyTag()),
				OpenGL::Context_4_3(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				),
				Interface_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv,						handle_)
				),
				Interface_4_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReleaseShaderCompiler,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderPrecisionFormat,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangef,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearDepthf,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramBinary,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgramStages,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveShaderProgram,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShaderProgramv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgramPipelines,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenProgramPipelines,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgramPipeline,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineInfoLog,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLPointer,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribLdv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexed,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexedv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeArrayv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeIndexed,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFloati_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDoublei_v,				handle_)
				),
				Interface_4_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstancedBaseInstance,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseInstance,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertexBaseInstance,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformativ,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAtomicCounterBufferiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindImageTexture,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMemoryBarrier,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage1D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackInstanced,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStreamInstanced,		handle_)
				),
				Interface_4_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferSubData,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDispatchCompute,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDispatchComputeIndirect,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyImageSubData,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferParameteri,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformati64v,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateTexSubImage,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateTexImage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateBufferSubData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateFramebuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateSubFramebuffer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArraysIndirect,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsIndirect,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInterfaceiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceIndex,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceName,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceLocationIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderStorageBlockBinding,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBufferRange,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2DMultisample,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3DMultisample,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureView,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribBinding,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexBindingDivisor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageControl,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageInsert,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageCallback,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDebugMessageLog,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPushDebugGroup,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPopDebugGroup,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glObjectLabel,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetObjectLabel,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glObjectPtrLabel,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetObjectPtrLabel,					handle_)
				)
				/*Interface_4_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClipControl,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackBufferBase,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackBufferRange,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbacki_v,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbacki64_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateBuffers,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedBufferStorage,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedBufferData,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedBufferSubData,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyNamedBufferSubData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedBufferData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedBufferSubData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapNamedBuffer,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapNamedBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapNamedBuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedNamedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferParameteriv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferParameteri64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferPointerv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferSubData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferRenderbuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferParameteri,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferTexture,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferTextureLayer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferDrawBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferDrawBuffers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferReadBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateNamedFramebufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateNamedFramebufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferfi,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitNamedFramebuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckNamedFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedFramebufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedFramebufferAttachmentParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateRenderbuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedRenderbufferStorage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateTextures,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureBuffer,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage1D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage2D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage3D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage2DMultisample,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage3DMultisample,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureSubImage1D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureSubImage2D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureSubImage3D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTextureSubImage1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTextureSubImage2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTextureSubImage3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTextureSubImage1D,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTextureSubImage2D,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTextureSubImage3D,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterf,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameteriv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateTextureMipmap,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTextureUnit,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureImage,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTextureImage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureLevelParameterfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureLevelParameteriv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameteriv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexArrayAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexArrayAttrib,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayElementBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayVertexBuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayVertexBuffers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribBinding,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribFormat,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribIFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribLFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayBindingDivisor,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexArrayiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexArrayIndexediv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexArrayIndexed64iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateSamplers,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgramPipelines,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateQueries,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjecti64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjectiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjectui64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjectuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMemoryBarrierByRegion,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureSubImage,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTextureSubImage,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetGraphicsResetStatus,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnCompressedTexImage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnTexImage,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformdv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformfv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformuiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReadnPixels,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMapdv,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMapfv,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMapiv,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPixelMapfv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPixelMapuiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPixelMapusv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPolygonStipple,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnColorTable,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnConvolutionFilter,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnSeparableFilter,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnHistogram,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMinmax,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureBarrier,								handle_)
				)*/
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_4_3::Context_4_3(const DeviceContextHandle& deviceContextHandle_):
				Context_4_3(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_4_4
			Context_4_4::Attributes Context_4_4::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
					WGL_CONTEXT_MINOR_VERSION_ARB,	4,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_4_4::Context_4_4(const Handle& handle_, const EmptyTag&):
				Windows::Context_4_3(handle_, EmptyTag()),
				OpenGL::Context_4_4(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3(),
				Interface_4_0(),
				Interface_4_1(),
				Interface_4_2(),
				Interface_4_4()
			{
			}
			Context_4_4::Context_4_4(const Handle& handle_):
				Windows::Context_4_3(handle_, EmptyTag()),
				OpenGL::Context_4_4(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				),
				Interface_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv,						handle_)
				),
				Interface_4_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReleaseShaderCompiler,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderPrecisionFormat,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangef,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearDepthf,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramBinary,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgramStages,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveShaderProgram,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShaderProgramv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgramPipelines,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenProgramPipelines,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgramPipeline,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineInfoLog,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLPointer,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribLdv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexed,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexedv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeArrayv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeIndexed,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFloati_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDoublei_v,				handle_)
				),
				Interface_4_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstancedBaseInstance,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseInstance,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertexBaseInstance,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformativ,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAtomicCounterBufferiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindImageTexture,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMemoryBarrier,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage1D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackInstanced,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStreamInstanced,		handle_)
				),
				Interface_4_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferSubData,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDispatchCompute,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDispatchComputeIndirect,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyImageSubData,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferParameteri,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformati64v,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateTexSubImage,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateTexImage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateBufferSubData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateFramebuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateSubFramebuffer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArraysIndirect,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsIndirect,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInterfaceiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceIndex,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceName,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceLocationIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderStorageBlockBinding,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBufferRange,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2DMultisample,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3DMultisample,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureView,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribBinding,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexBindingDivisor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageControl,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageInsert,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageCallback,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDebugMessageLog,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPushDebugGroup,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPopDebugGroup,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glObjectLabel,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetObjectLabel,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glObjectPtrLabel,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetObjectPtrLabel,					handle_)
				),
				Interface_4_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferStorage,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearTexImage,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearTexSubImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffersBase,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffersRange,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTextures,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSamplers,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindImageTextures,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexBuffers,	handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_4_4::Context_4_4(const DeviceContextHandle& deviceContextHandle_):
				Context_4_4(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion
#pragma region Context_4_5
			Context_4_5::Attributes Context_4_5::GetAttributes()
			{
				return {
					WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
					WGL_CONTEXT_MINOR_VERSION_ARB,	5,
					WGL_CONTEXT_FLAGS_ARB,			0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
					0, 0,
				};
			}

			Context_4_5::Context_4_5(const Handle& handle_, const EmptyTag&):
				Windows::Context_4_4(handle_, EmptyTag()),
				OpenGL::Context_4_5(),
				Interface_1_2(),
				Interface_1_3(),
				Interface_1_4(),
				Interface_1_5(),
				Interface_2_0(),
				Interface_2_1(),
				Interface_3_0(),
				Interface_3_1(),
				Interface_3_2(),
				Interface_3_3(),
				Interface_4_0(),
				Interface_4_1(),
				Interface_4_2(),
				Interface_4_5()
			{
			}
			Context_4_5::Context_4_5(const Handle& handle_):
				Windows::Context_4_4(handle_, EmptyTag()),
				OpenGL::Context_4_5(),
				Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				Interface_1_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveTexture,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleCoverage,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage3D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage2D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTexSubImage1D,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTexImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientActiveTexture,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord1sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord2sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4s,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoord4sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLoadTransposeMatrixd,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixf,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultTransposeMatrixd,	handle_)
				),
				Interface_1_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparate,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArrays,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElements,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPointParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordf,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordd,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoorddv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFogCoordPointer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3b,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3bv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3d,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3f,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3i,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3iv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3s,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3sv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ub,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ubv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3ui,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3uiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3us,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColor3usv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorPointer,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos2sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3f,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3i,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3s,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWindowPos3sv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendColor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquation,			handle_)
				),
				Interface_1_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenQueries,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteQueries,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsQuery,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQuery,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteBuffers,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenBuffers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferSubData,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapBuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferPointerv,		handle_)
				),
				Interface_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer,				handle_)
				),
				Interface_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv,	handle_)
				),
				Interface_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray,							handle_)
				),
				Interface_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding,			handle_)
				),
				Interface_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski,						handle_)
				),
				Interface_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv,			handle_)
				),
				Interface_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv,						handle_)
				),
				Interface_4_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReleaseShaderCompiler,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderPrecisionFormat,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangef,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearDepthf,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramBinary,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramBinary,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramParameteri,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgramStages,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveShaderProgram,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShaderProgramv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgramPipelines,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenProgramPipelines,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgramPipeline,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineiv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4i,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4iv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4f,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4fv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4d,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4ui,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4uiv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4fv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4dv,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3fv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3dv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgramPipeline,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineInfoLog,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4d,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4dv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLPointer,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribLdv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedf,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedfv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorArrayv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexed,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexedv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeArrayv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeIndexed,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFloati_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDoublei_v,				handle_)
				),
				Interface_4_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstancedBaseInstance,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseInstance,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertexBaseInstance,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformativ,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAtomicCounterBufferiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindImageTexture,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMemoryBarrier,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage1D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3D,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackInstanced,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStreamInstanced,		handle_)
				),
				Interface_4_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferSubData,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDispatchCompute,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDispatchComputeIndirect,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyImageSubData,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferParameteri,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferParameteriv,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInternalformati64v,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateTexSubImage,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateTexImage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateBufferSubData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateBufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateFramebuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateSubFramebuffer,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawArraysIndirect,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsIndirect,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInterfaceiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceIndex,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceName,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceiv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceLocation,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramResourceLocationIndex,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderStorageBlockBinding,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBufferRange,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage2DMultisample,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexStorage3DMultisample,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureView,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribBinding,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexBindingDivisor,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageControl,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageInsert,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDebugMessageCallback,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDebugMessageLog,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPushDebugGroup,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPopDebugGroup,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glObjectLabel,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetObjectLabel,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glObjectPtrLabel,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetObjectPtrLabel,					handle_)
				),
				Interface_4_4(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBufferStorage,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearTexImage,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearTexSubImage,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffersBase,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBuffersRange,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTextures,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSamplers,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindImageTextures,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexBuffers,	handle_)
				),
				Interface_4_5(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClipControl,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateTransformFeedbacks,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackBufferBase,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackBufferRange,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbacki_v,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbacki64_v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateBuffers,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedBufferStorage,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedBufferData,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedBufferSubData,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyNamedBufferSubData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedBufferData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedBufferSubData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapNamedBuffer,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapNamedBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUnmapNamedBuffer,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedNamedBufferRange,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferParameteriv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferParameteri64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferPointerv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedBufferSubData,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateFramebuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferRenderbuffer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferParameteri,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferTexture,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferTextureLayer,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferDrawBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferDrawBuffers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedFramebufferReadBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateNamedFramebufferData,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glInvalidateNamedFramebufferSubData,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferuiv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearNamedFramebufferfi,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitNamedFramebuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckNamedFramebufferStatus,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedFramebufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedFramebufferAttachmentParameteriv,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateRenderbuffers,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedRenderbufferStorage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNamedRenderbufferStorageMultisample,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetNamedRenderbufferParameteriv,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateTextures,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureBuffer,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureBufferRange,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage1D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage2D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage3D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage2DMultisample,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureStorage3DMultisample,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureSubImage1D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureSubImage2D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureSubImage3D,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTextureSubImage1D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTextureSubImage2D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompressedTextureSubImage3D,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTextureSubImage1D,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTextureSubImage2D,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTextureSubImage3D,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterf,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterfv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameteri,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterIiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureParameteriv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateTextureMipmap,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTextureUnit,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureImage,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTextureImage,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureLevelParameterfv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureLevelParameteriv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameterfv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameterIiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameterIuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureParameteriv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateVertexArrays,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexArrayAttrib,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexArrayAttrib,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayElementBuffer,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayVertexBuffer,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayVertexBuffers,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribBinding,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribFormat,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribIFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayAttribLFormat,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexArrayBindingDivisor,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexArrayiv,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexArrayIndexediv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexArrayIndexed64iv,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateSamplers,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgramPipelines,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateQueries,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjecti64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjectiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjectui64v,					handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryBufferObjectuiv,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMemoryBarrierByRegion,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTextureSubImage,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetCompressedTextureSubImage,				handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetGraphicsResetStatus,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnCompressedTexImage,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnTexImage,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformdv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformfv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnUniformuiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReadnPixels,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMapdv,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMapfv,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMapiv,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPixelMapfv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPixelMapuiv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPixelMapusv,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnPolygonStipple,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnColorTable,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnConvolutionFilter,						handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnSeparableFilter,							handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnHistogram,								handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetnMinmax,									handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTextureBarrier,								handle_)
				)
			{
				MakeCurrent(nullptr, nullptr);
			}
			Context_4_5::Context_4_5(const DeviceContextHandle& deviceContextHandle_):
				Context_4_5(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
			{
			}
#pragma endregion


			Context::Handle CreateContext(const Context::DeviceContextHandle& deviceContextHandle_)
			{
				auto handle = wglCreateContext(deviceContextHandle_);

				if (!handle)
				{
					throw Exception();
				}

				return handle;
			}
			void DeleteContext(const Context::Handle& handle_)
			{
				auto result = wglDeleteContext(handle_);

				if (!result)
				{
					throw Exception();
				}
			}
			Context::Handle GetCurrentHandle()
			{
				auto handle = wglGetCurrentContext();

				return handle;
			}
			void MakeCurrent(const Context::DeviceContextHandle& deviceContextHandle_, const Context::Handle& handle_)
			{
				auto result = wglMakeCurrent(deviceContextHandle_, handle_);

				if (!result)
				{
					throw Exception();
				}
			}
		}
#endif
	}
}


const Size2 windowSize = Size2(200, 120);
const Size2 windowOffset = Size2(30, 50);

HWND GetWindow(HINSTANCE instanceHandle, const std::string& windowClassName, String title, int x, int y)
{
	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	RECT rect;
	{
		rect.left = x;
		rect.right = x + windowSize.x;
		rect.top = y;
		rect.bottom = y + windowSize.y;
	}

	if (!AdjustWindowRect(&rect, style, NULL))
	{
		throw Exception();
	}

	HWND windowHandle = CreateWindowA(
		windowClassName.c_str(),
		title.c_str(),
		style,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
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
HDC GetDeviceContext(HWND windowHandle)
{
	auto deviceContextHandle = GetDC(windowHandle);

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


void main()
{
	namespace GL = OpenGL::OSs::Windows;

	auto instanceHandle = GetModuleHandleA(NULL);

	std::string windowClassName = "window class";
	{
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
	}

	auto window_1_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_0_Handle		= GetDeviceContext(window_1_0_Handle);
	auto renderContext_1_0_Handle		= MakeStrong<GL::Context_1_0>(deviceContext_1_0_Handle);

	auto window_1_2_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.2", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_2_Handle		= GetDeviceContext(window_1_2_Handle);
	auto renderContext_1_2_Handle		= MakeStrong<GL::Context_1_2>(deviceContext_1_2_Handle);

	auto window_1_3_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.3", windowOffset.x + (windowSize.x + windowOffset.x) * 2, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_3_Handle		= GetDeviceContext(window_1_3_Handle);
	auto renderContext_1_3_Handle		= MakeStrong<GL::Context_1_3>(deviceContext_1_3_Handle);

	auto window_1_4_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.4", windowOffset.x + (windowSize.x + windowOffset.x) * 3, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_4_Handle		= GetDeviceContext(window_1_4_Handle);
	auto renderContext_1_4_Handle		= MakeStrong<GL::Context_1_4>(deviceContext_1_4_Handle);

	auto window_1_5_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 1.5", windowOffset.x + (windowSize.x + windowOffset.x) * 4, windowOffset.y + (windowSize.y + windowOffset.y) * 0);
	auto deviceContext_1_5_Handle		= GetDeviceContext(window_1_5_Handle);
	auto renderContext_1_5_Handle		= MakeStrong<GL::Context_1_5>(deviceContext_1_5_Handle);

	auto window_2_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 2.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 1);
	auto deviceContext_2_0_Handle		= GetDeviceContext(window_2_0_Handle);
	auto renderContext_2_0_Handle		= MakeStrong<GL::Context_2_0>(deviceContext_2_0_Handle);

	auto window_2_1_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 2.1", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 1);
	auto deviceContext_2_1_Handle		= GetDeviceContext(window_2_1_Handle);
	auto renderContext_2_1_Handle		= MakeStrong<GL::Context_2_1>(deviceContext_2_1_Handle);

	auto window_3_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_0_Handle		= GetDeviceContext(window_3_0_Handle);
	auto renderContext_3_0_Handle		= MakeStrong<GL::Context_3_0>(deviceContext_3_0_Handle);

	auto window_3_1_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.1", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_1_Handle		= GetDeviceContext(window_3_1_Handle);
	auto renderContext_3_1_Handle		= MakeStrong<GL::Context_3_1>(deviceContext_3_1_Handle);

	auto window_3_2_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.2", windowOffset.x + (windowSize.x + windowOffset.x) * 2, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_2_Handle		= GetDeviceContext(window_3_2_Handle);
	auto renderContext_3_2_Handle		= MakeStrong<GL::Context_3_2>(deviceContext_3_2_Handle);

	auto window_3_3_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 3.3", windowOffset.x + (windowSize.x + windowOffset.x) * 3, windowOffset.y + (windowSize.y + windowOffset.y) * 2);
	auto deviceContext_3_3_Handle		= GetDeviceContext(window_3_3_Handle);
	auto renderContext_3_3_Handle		= MakeStrong<GL::Context_3_3>(deviceContext_3_3_Handle);

	auto window_4_0_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.0", windowOffset.x + (windowSize.x + windowOffset.x) * 0, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_0_Handle		= GetDeviceContext(window_4_0_Handle);
	auto renderContext_4_0_Handle		= MakeStrong<GL::Context_4_0>(deviceContext_4_0_Handle);

	auto window_4_1_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.1", windowOffset.x + (windowSize.x + windowOffset.x) * 1, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_1_Handle		= GetDeviceContext(window_4_1_Handle);
	auto renderContext_4_1_Handle		= MakeStrong<GL::Context_4_1>(deviceContext_4_1_Handle);

	auto window_4_2_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.2", windowOffset.x + (windowSize.x + windowOffset.x) * 2, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_2_Handle		= GetDeviceContext(window_4_2_Handle);
	auto renderContext_4_2_Handle		= MakeStrong<GL::Context_4_2>(deviceContext_4_2_Handle);

	auto window_4_3_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.3", windowOffset.x + (windowSize.x + windowOffset.x) * 3, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_3_Handle		= GetDeviceContext(window_4_3_Handle);
	auto renderContext_4_3_Handle		= MakeStrong<GL::Context_4_3>(deviceContext_4_3_Handle);

	auto window_4_4_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.4", windowOffset.x + (windowSize.x + windowOffset.x) * 4, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_4_Handle		= GetDeviceContext(window_4_4_Handle);
	auto renderContext_4_4_Handle		= MakeStrong<GL::Context_4_4>(deviceContext_4_4_Handle);

	auto window_4_5_Handle				= GetWindow(instanceHandle, windowClassName, "OpenGL 4.5", windowOffset.x + (windowSize.x + windowOffset.x) * 5, windowOffset.y + (windowSize.y + windowOffset.y) * 3);
	auto deviceContext_4_5_Handle		= GetDeviceContext(window_4_5_Handle);
	auto renderContext_4_5_Handle		= MakeStrong<GL::Context_4_5>(deviceContext_4_5_Handle);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while (PeekMessageA(&msg, window_1_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_2_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_3_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_4_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_1_5_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			
			while (PeekMessageA(&msg, window_2_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_2_1_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}

			while (PeekMessageA(&msg, window_3_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_3_1_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_3_2_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_3_3_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}

			while (PeekMessageA(&msg, window_4_0_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_1_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_2_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_3_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_4_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window_4_5_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		// OpenGL 1.*
		GL::MakeCurrent(deviceContext_1_0_Handle, renderContext_1_0_Handle->GetHandle());
		{
			renderContext_1_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_0_Handle->ClearColor(1, 0, 0, 0);
			renderContext_1_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_0_Handle->Flush();
			
			SwapBuffers(deviceContext_1_0_Handle);
		}
		GL::MakeCurrent(deviceContext_1_2_Handle, renderContext_1_2_Handle->GetHandle());
		{
			renderContext_1_2_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_2_Handle->ClearColor(1, 0.15f, 0, 0);
			renderContext_1_2_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_2_Handle->Flush();

			SwapBuffers(deviceContext_1_2_Handle);
		}
		GL::MakeCurrent(deviceContext_1_3_Handle, renderContext_1_3_Handle->GetHandle());
		{
			renderContext_1_3_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_3_Handle->ClearColor(1, 0.3f, 0, 0);
			renderContext_1_3_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_3_Handle->Flush();

			SwapBuffers(deviceContext_1_3_Handle);
		}
		GL::MakeCurrent(deviceContext_1_4_Handle, renderContext_1_4_Handle->GetHandle());
		{
			renderContext_1_4_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_4_Handle->ClearColor(1, 0.45f, 0, 0);
			renderContext_1_4_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_4_Handle->Flush();

			SwapBuffers(deviceContext_1_4_Handle);
		}
		GL::MakeCurrent(deviceContext_1_5_Handle, renderContext_1_5_Handle->GetHandle());
		{
			renderContext_1_5_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_1_5_Handle->ClearColor(1, 0.6f, 0, 0);
			renderContext_1_5_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				auto bufferHandle = renderContext_1_5_Handle->GenBuffer();

				renderContext_1_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
				renderContext_1_5_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({}), OpenGL::Buffer::Usage::Static);

				// TODO

				renderContext_1_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_1_5_Handle->DeleteBuffer(bufferHandle);
			}
			{
				glBegin(GL_TRIANGLES);

				glVertex2f(-0.5f, -0.5f);
				glVertex2f(+0.5f, -0.5f);
				glVertex2f(+0.0f, +0.5f);

				glEnd();
			}
			renderContext_1_5_Handle->Flush();

			SwapBuffers(deviceContext_1_5_Handle);
		}

		// OpenGL 2.*
		GL::MakeCurrent(deviceContext_2_0_Handle, renderContext_2_0_Handle->GetHandle());
		{
			renderContext_2_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_2_0_Handle->ClearColor(0, 1, 0, 0);
			renderContext_2_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				auto bufferHandle = renderContext_2_0_Handle->GenBuffer();
				{
					renderContext_2_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_2_0_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_2_0_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_2_0_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_2_0_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_2_0_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_0_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_2_0_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_2_0_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_2_0_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_2_0_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_0_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_2_0_Handle->CreateProgram();
				{
					renderContext_2_0_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_2_0_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_2_0_Handle->LinkProgram(programHandle);

					if (auto linkStatus = renderContext_2_0_Handle->GetProgramLinkStatus(programHandle)); else
					{
						auto programInfoLog = renderContext_2_0_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_2_0_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_2_0_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_2_0_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_2_0_Handle->DeleteShader(vertexShaderHandle);
				renderContext_2_0_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_2_0_Handle->UseProgram(programHandle);
				
				renderContext_2_0_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_2_0_Handle->UseProgram(nullptr);
				renderContext_2_0_Handle->DeleteProgram(programHandle);

				renderContext_2_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_2_0_Handle->DeleteBuffer(bufferHandle);
			}
			renderContext_2_0_Handle->Flush();

			SwapBuffers(deviceContext_2_0_Handle);
		}
		GL::MakeCurrent(deviceContext_2_1_Handle, renderContext_2_1_Handle->GetHandle());
		{
			renderContext_2_1_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_2_1_Handle->ClearColor(0, 1, 0.5f, 0);
			renderContext_2_1_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				auto bufferHandle = renderContext_2_1_Handle->GenBuffer();
				{
					renderContext_2_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_2_1_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_2_1_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_2_1_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_2_1_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_2_1_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_1_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_2_1_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_2_1_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_2_1_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_2_1_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_2_1_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_2_1_Handle->CreateProgram();
				{
					renderContext_2_1_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_2_1_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_2_1_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_2_1_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_2_1_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_2_1_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_2_1_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_2_1_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_2_1_Handle->DeleteShader(vertexShaderHandle);
				renderContext_2_1_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_2_1_Handle->UseProgram(programHandle);
				
				renderContext_2_1_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_2_1_Handle->UseProgram(nullptr);
				renderContext_2_1_Handle->DeleteProgram(programHandle);

				renderContext_2_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_2_1_Handle->DeleteBuffer(bufferHandle);
			}
			renderContext_2_1_Handle->Flush();

			SwapBuffers(deviceContext_2_1_Handle);
		}

		// OpenGL 3.*
		GL::MakeCurrent(deviceContext_3_0_Handle, renderContext_3_0_Handle->GetHandle());
		{
			renderContext_3_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_0_Handle->ClearColor(0, 0, 1, 0);
			renderContext_3_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_0_Handle->GenVertexArray();
				{
					renderContext_3_0_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_0_Handle->GenBuffer();
				{
					renderContext_3_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_0_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_0_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_0_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_0_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_0_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_0_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_0_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_0_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_0_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_0_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_0_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_0_Handle->CreateProgram();
				{
					renderContext_3_0_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_0_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_0_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_0_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_0_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_0_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_0_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_0_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_0_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_0_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_0_Handle->UseProgram(programHandle);
				
				renderContext_3_0_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_0_Handle->UseProgram(nullptr);
				renderContext_3_0_Handle->DeleteProgram(programHandle);

				renderContext_3_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_0_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_0_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_0_Handle->Flush();

			SwapBuffers(deviceContext_3_0_Handle);
		}
		GL::MakeCurrent(deviceContext_3_1_Handle, renderContext_3_1_Handle->GetHandle());
		{
			renderContext_3_1_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_1_Handle->ClearColor(0, 0.2f, 1, 0);
			renderContext_3_1_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_1_Handle->GenVertexArray();
				{
					renderContext_3_1_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_1_Handle->GenBuffer();
				{
					renderContext_3_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_1_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_1_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_1_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_1_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_1_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_1_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_1_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_1_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_1_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_1_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_1_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_1_Handle->CreateProgram();
				{
					renderContext_3_1_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_1_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_1_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_1_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_1_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_1_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_1_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_1_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_1_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_1_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_1_Handle->UseProgram(programHandle);
				
				renderContext_3_1_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_1_Handle->UseProgram(nullptr);
				renderContext_3_1_Handle->DeleteProgram(programHandle);

				renderContext_3_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_1_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_1_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_1_Handle->Flush();

			SwapBuffers(deviceContext_3_1_Handle);
		}
		GL::MakeCurrent(deviceContext_3_2_Handle, renderContext_3_2_Handle->GetHandle());
		{
			renderContext_3_2_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_2_Handle->ClearColor(0, 0.4f, 1, 0);
			renderContext_3_2_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_2_Handle->GenVertexArray();
				{
					renderContext_3_2_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_2_Handle->GenBuffer();
				{
					renderContext_3_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_2_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_2_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_2_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_2_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_2_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_2_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_2_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_2_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_2_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_2_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_2_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_2_Handle->CreateProgram();
				{
					renderContext_3_2_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_2_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_2_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_2_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_2_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_2_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_2_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_2_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_2_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_2_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_2_Handle->UseProgram(programHandle);
				
				renderContext_3_2_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_2_Handle->UseProgram(nullptr);
				renderContext_3_2_Handle->DeleteProgram(programHandle);

				renderContext_3_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_2_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_2_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_2_Handle->Flush();

			SwapBuffers(deviceContext_3_2_Handle);
		}
		GL::MakeCurrent(deviceContext_3_3_Handle, renderContext_3_3_Handle->GetHandle());
		{
			renderContext_3_3_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_3_3_Handle->ClearColor(0, 0.6f, 1, 0);
			renderContext_3_3_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_3_3_Handle->GenVertexArray();
				{
					renderContext_3_3_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_3_3_Handle->GenBuffer();
				{
					renderContext_3_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_3_3_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_3_3_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_3_3_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_3_3_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_3_3_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_3_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_3_3_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_3_3_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_3_3_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_3_3_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_3_3_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_3_3_Handle->CreateProgram();
				{
					renderContext_3_3_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_3_3_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_3_3_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_3_3_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_3_3_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_3_3_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_3_3_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_3_3_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_3_3_Handle->DeleteShader(vertexShaderHandle);
				renderContext_3_3_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_3_3_Handle->UseProgram(programHandle);
				
				renderContext_3_3_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_3_3_Handle->UseProgram(nullptr);
				renderContext_3_3_Handle->DeleteProgram(programHandle);

				renderContext_3_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_3_3_Handle->DeleteBuffer(bufferHandle);

				renderContext_3_3_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_3_3_Handle->Flush();

			SwapBuffers(deviceContext_3_3_Handle);
		}

		// OpenGL 4.*
		GL::MakeCurrent(deviceContext_4_0_Handle, renderContext_4_0_Handle->GetHandle());
		{
			renderContext_4_0_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_0_Handle->ClearColor(0.5f, 0, 1, 0);
			renderContext_4_0_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_0_Handle->GenVertexArray();
				{
					renderContext_4_0_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_0_Handle->GenBuffer();
				{
					renderContext_4_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_0_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_0_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_0_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_0_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_0_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_0_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_0_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_0_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_0_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_0_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_0_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_0_Handle->CreateProgram();
				{
					renderContext_4_0_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_0_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_0_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_0_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_0_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_0_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_0_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_0_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_0_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_0_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_0_Handle->UseProgram(programHandle);
				
				renderContext_4_0_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_0_Handle->UseProgram(nullptr);
				renderContext_4_0_Handle->DeleteProgram(programHandle);

				renderContext_4_0_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_0_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_0_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_0_Handle->Flush();

			SwapBuffers(deviceContext_4_0_Handle);
		}
		GL::MakeCurrent(deviceContext_4_1_Handle, renderContext_4_1_Handle->GetHandle());
		{
			renderContext_4_1_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_1_Handle->ClearColor(0.6f, 0, 0.9f, 0);
			renderContext_4_1_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_1_Handle->GenVertexArray();
				{
					renderContext_4_1_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_1_Handle->GenBuffer();
				{
					renderContext_4_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_1_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_1_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_1_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_1_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_1_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_1_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_1_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_1_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_1_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_1_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_1_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_1_Handle->CreateProgram();
				{
					renderContext_4_1_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_1_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_1_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_1_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_1_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_1_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_1_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_1_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_1_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_1_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_1_Handle->UseProgram(programHandle);
				
				renderContext_4_1_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_1_Handle->UseProgram(nullptr);
				renderContext_4_1_Handle->DeleteProgram(programHandle);

				renderContext_4_1_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_1_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_1_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_1_Handle->Flush();

			SwapBuffers(deviceContext_4_1_Handle);
		}
		GL::MakeCurrent(deviceContext_4_2_Handle, renderContext_4_2_Handle->GetHandle());
		{
			renderContext_4_2_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_2_Handle->ClearColor(0.7f, 0, 0.8f, 0);
			renderContext_4_2_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_2_Handle->GenVertexArray();
				{
					renderContext_4_2_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_2_Handle->GenBuffer();
				{
					renderContext_4_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_2_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_2_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_2_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_2_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_2_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_2_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_2_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_2_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_2_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_2_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_2_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_2_Handle->CreateProgram();
				{
					renderContext_4_2_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_2_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_2_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_2_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_2_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_2_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_2_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_2_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_2_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_2_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_2_Handle->UseProgram(programHandle);
				
				renderContext_4_2_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_2_Handle->UseProgram(nullptr);
				renderContext_4_2_Handle->DeleteProgram(programHandle);

				renderContext_4_2_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_2_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_2_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_2_Handle->Flush();

			SwapBuffers(deviceContext_4_2_Handle);
		}
		GL::MakeCurrent(deviceContext_4_3_Handle, renderContext_4_3_Handle->GetHandle());
		{
			renderContext_4_3_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_3_Handle->ClearColor(0.8f, 0, 0.7f, 0);
			renderContext_4_3_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_3_Handle->GenVertexArray();
				{
					renderContext_4_3_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_3_Handle->GenBuffer();
				{
					renderContext_4_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_3_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_3_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_3_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_3_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_3_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_3_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_3_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_3_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_3_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_3_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_3_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_3_Handle->CreateProgram();
				{
					renderContext_4_3_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_3_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_3_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_3_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_3_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_3_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_3_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_3_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_3_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_3_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_3_Handle->UseProgram(programHandle);
				
				renderContext_4_3_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_3_Handle->UseProgram(nullptr);
				renderContext_4_3_Handle->DeleteProgram(programHandle);

				renderContext_4_3_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_3_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_3_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_3_Handle->Flush();

			SwapBuffers(deviceContext_4_3_Handle);
		}
		GL::MakeCurrent(deviceContext_4_4_Handle, renderContext_4_4_Handle->GetHandle());
		{
			renderContext_4_4_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_4_Handle->ClearColor(0.9f, 0, 0.6f, 0);
			renderContext_4_4_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_4_Handle->GenVertexArray();
				{
					renderContext_4_4_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_4_Handle->GenBuffer();
				{
					renderContext_4_4_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_4_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_4_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_4_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_4_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_4_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_4_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_4_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_4_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_4_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_4_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_4_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_4_Handle->CreateProgram();
				{
					renderContext_4_4_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_4_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_4_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_4_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_4_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_4_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_4_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_4_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_4_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_4_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_4_Handle->UseProgram(programHandle);
				
				renderContext_4_4_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_4_Handle->UseProgram(nullptr);
				renderContext_4_4_Handle->DeleteProgram(programHandle);

				renderContext_4_4_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_4_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_4_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_4_Handle->Flush();

			SwapBuffers(deviceContext_4_4_Handle);
		}
		GL::MakeCurrent(deviceContext_4_5_Handle, renderContext_4_5_Handle->GetHandle());
		{
			renderContext_4_5_Handle->ConfigureViewport(0, 0, windowSize.x, windowSize.y);
			renderContext_4_5_Handle->ClearColor(1, 0, 0.5f, 0);
			renderContext_4_5_Handle->Clear(GL_COLOR_BUFFER_BIT);
			{
				const auto vertexArrayHandle = renderContext_4_5_Handle->GenVertexArray();
				{
					renderContext_4_5_Handle->BindVertexArray(vertexArrayHandle);
				}

				auto bufferHandle = renderContext_4_5_Handle->GenBuffer();
				{
					renderContext_4_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, bufferHandle);
					renderContext_4_5_Handle->BufferData(OpenGL::Buffer::Type::Array, Vector<Vec2>({ Vec2(-0.5f, -0.5f), Vec2(+0.5f, -0.5f), Vec2(+0.0f, +0.5f) }), OpenGL::Buffer::Usage::Static);
				}

				auto vertexShaderHandle = renderContext_4_5_Handle->CreateShader(OpenGL::Shader::Type::Vertex);
				{
					renderContext_4_5_Handle->ShaderSource(vertexShaderHandle, "#version 110\n#extension all:disable\nin vec2 vPos; void main(){ gl_Position = vec4(vPos,0,1); }");
					renderContext_4_5_Handle->CompileShader(vertexShaderHandle);

					if (auto compileStatus = renderContext_4_5_Handle->GetShaderCompileStatus(vertexShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_5_Handle->GetShaderInfoLog(vertexShaderHandle);

						throw Exception("Exception during vertex shader compilation: " + shaderInfoLog);
					}
				}
				auto fragmentShaderHandle = renderContext_4_5_Handle->CreateShader(OpenGL::Shader::Type::Fragment);
				{
					renderContext_4_5_Handle->ShaderSource(fragmentShaderHandle, "#version 110\n#extension all:disable\nvoid main(){ gl_FragColor = vec4(1); }");
					renderContext_4_5_Handle->CompileShader(fragmentShaderHandle);

					if (auto compileStatus = renderContext_4_5_Handle->GetShaderCompileStatus(fragmentShaderHandle)); else
					{
						auto shaderInfoLog = renderContext_4_5_Handle->GetShaderInfoLog(fragmentShaderHandle);

						throw Exception("Exception during fragment shader compilation: " + shaderInfoLog);
					}
				}
				auto programHandle = renderContext_4_5_Handle->CreateProgram();
				{
					renderContext_4_5_Handle->AttachShader(programHandle, vertexShaderHandle);
					renderContext_4_5_Handle->AttachShader(programHandle, fragmentShaderHandle);
					renderContext_4_5_Handle->LinkProgram(programHandle);

					if (const auto linkStatus = renderContext_4_5_Handle->GetProgramLinkStatus(programHandle)); else
					{
						const auto programInfoLog = renderContext_4_5_Handle->GetProgramInfoLog(programHandle);

						throw Exception("Exception during program linking" + programInfoLog);
					}

					if (const auto attributeLocation = renderContext_4_5_Handle->GetAttributeLocation(programHandle, "vPos"))
					{
						renderContext_4_5_Handle->VertexAttributePointer(attributeLocation, 2, OpenGL::Program::Attribute::Type::Float, false, 0, 0);
						renderContext_4_5_Handle->EnableVertexAttributeArray(attributeLocation);
					}
				}

				renderContext_4_5_Handle->DeleteShader(vertexShaderHandle);
				renderContext_4_5_Handle->DeleteShader(fragmentShaderHandle);

				renderContext_4_5_Handle->UseProgram(programHandle);
				
				renderContext_4_5_Handle->DrawArrays(OpenGL::PrimitiveType::Triangles, 0, 3);

				renderContext_4_5_Handle->UseProgram(nullptr);
				renderContext_4_5_Handle->DeleteProgram(programHandle);

				renderContext_4_5_Handle->BindBuffer(OpenGL::Buffer::Type::Array, nullptr);
				renderContext_4_5_Handle->DeleteBuffer(bufferHandle);

				renderContext_4_5_Handle->DeleteVertexArray(vertexArrayHandle);
			}
			renderContext_4_5_Handle->Flush();

			SwapBuffers(deviceContext_4_5_Handle);
		}

		Sleep(1000 / 60);
	}

	GL::MakeCurrent(nullptr, nullptr);
}


#pragma region
#pragma endregion



