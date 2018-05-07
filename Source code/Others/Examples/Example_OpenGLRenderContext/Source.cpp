#include <iostream>
#include <thread>
#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__

#include <Windows.h>

#endif

// #define __GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(x) if((x = reinterpret_cast<decltype(x)>(wglGetProcAddress(#x))) == nullptr) throw Exception() // ("Failed to get function pointer for \""#x"\"");
// #define OBTAIN(x) x(wglGetProcAddress(#x) ? reinterpret_cast<decltype(x)>(wglGetProcAddress(#x)) : throw Exception())
#define __GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS__(x) reinterpret_cast<decltype(x)>(GetProcedureAddress(#x))
#define __GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(x, h) reinterpret_cast<decltype(x)>(GetProcedureAddress(#x, h))

#include <gl/gl.h>
#include <gl/glext.h>
#include <gl/wglext.h>


/*class RenderContext
{
public:
	using Handle = HGLRC;
	using Attributes = Vector<GLint>;
public:
	inline static PFNWGLCREATECONTEXTATTRIBSARBPROC ObtainWglCreateContextAttribsARB()
	{
		auto instanceHandle = GetModuleHandleA(NULL);

		std::string windowClassName = "OpenGL Functions Obtainer";
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

		HWND windowHandle = CreateWindowA(
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
			throw Exception();
		}

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

		auto openGLRenderContextHandle = wglCreateContext(deviceContextHandle);

		if (!wglMakeCurrent(deviceContextHandle, openGLRenderContextHandle))
		{
			throw Exception();
		}

		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = reinterpret_cast<decltype(wglCreateContextAttribsARB)>(wglGetProcAddress("wglCreateContextAttribsARB"));

		if (wglCreateContextAttribsARB == nullptr)
		{
			throw Exception();
		}

		auto t = wglGetProcAddress("glDrawRangeElements");

		if (!wglMakeCurrent(nullptr, nullptr))
		{
			throw Exception();
		}

		DestroyWindow(windowHandle);
		UnregisterClassA(windowClassName.c_str(), instanceHandle);

		return wglCreateContextAttribsARB;
	}
	inline static Handle wglCreateContextAttribsARB(const HDC& deviceContextHandle_, const Handle& sharedContextHandle_, const Attributes& attributes_)
	{
		static PFNWGLCREATECONTEXTATTRIBSARBPROC create = ObtainWglCreateContextAttribsARB();
		
		auto renderContext = create(deviceContextHandle_, sharedContextHandle_, attributes_.data());

		return renderContext;
	}
	inline static Handle MakeCurrentAndReturn(const Handle& handle_, const HDC& deviceContextHandle_)
	{
		if (!wglMakeCurrent(deviceContextHandle_, handle_))
		{
			throw Exception();
		}
	}
protected:
	const Handle handle;
protected:
	inline RenderContext(const Handle& handle_):
		handle(handle_)
	{
	}
	inline ~RenderContext()
	{
		wglMakeCurrent(nullptr, nullptr);

		wglDeleteContext(handle);
	}
};
class RenderContext1_2:
	public RenderContext
{
public:
	inline static Attributes GetAttributes()
	{
		return{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
			WGL_CONTEXT_MINOR_VERSION_ARB, 2,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0, 0,
		};
	}
protected:
	PFNGLDRAWRANGEELEMENTSPROC											glDrawRangeElements;
	PFNGLTEXIMAGE3DPROC													glTexImage3D;
	PFNGLTEXSUBIMAGE3DPROC												glTexSubImage3D;
	PFNGLCOPYTEXSUBIMAGE3DPROC											glCopyTexSubImage3D;
protected:
	inline RenderContext1_2(const Handle& handle_):
		RenderContext(handle_) // ,
		// OBTAIN(glDrawRangeElements),
		// OBTAIN(glTexImage3D),
		// OBTAIN(glTexSubImage3D),
		// OBTAIN(glCopyTexSubImage3D)
	{
		glDrawRangeElements = reinterpret_cast<decltype(glDrawRangeElements)>(wglGetProcAddress("glDrawRangeElements"));
	}
public:
	inline RenderContext1_2(const HDC& deviceContextHandle_):
		RenderContext1_2(MakeCurrentAndReturn(wglCreateContextAttribsARB(deviceContextHandle_, nullptr, GetAttributes()), deviceContextHandle_))
	{
	}
};*/


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

	class Interface
	{
	protected:
		class EmptyTag {};
	};
	class Interface_1_0:
		public virtual Interface
	{
	protected:
		inline void				CheckForErrors() const;
	public:
		inline Error::Code		GetErrorCode() const;
		inline void				ConfigureViewport(const GLint& x_, const GLint& y_, const GLsizei& width_, const GLsizei& height_) const;
		inline void				ClearColor(const GLclampf& red_, const GLclampf& green_, const GLclampf& blue_, const GLclampf& alpha_) const;
		inline void				Clear(const GLbitfield& mask_) const;
		inline void				Flush() const;
		inline void				Finish() const;
	};
	class Interface_1_2:
		public virtual Interface
	{
	protected:
		const PFNGLDRAWRANGEELEMENTSPROC	glDrawRangeElements;
		const PFNGLTEXIMAGE3DPROC			glTexImage3D;
		const PFNGLTEXSUBIMAGE3DPROC		glTexSubImage3D;
		const PFNGLCOPYTEXSUBIMAGE3DPROC	glCopyTexSubImage3D;
	protected:
		inline explicit Interface_1_2(const EmptyTag&);
		inline Interface_1_2(
			// Version 1.2
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
		const PFNGLACTIVETEXTUREPROC			glActiveTexture;
		const PFNGLSAMPLECOVERAGEPROC			glSampleCoverage;
		const PFNGLCOMPRESSEDTEXIMAGE3DPROC		glCompressedTexImage3D;
		const PFNGLCOMPRESSEDTEXIMAGE2DPROC		glCompressedTexImage2D;
		const PFNGLCOMPRESSEDTEXIMAGE1DPROC		glCompressedTexImage1D;
		const PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC	glCompressedTexSubImage3D;
		const PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC	glCompressedTexSubImage2D;
		const PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC	glCompressedTexSubImage1D;
		const PFNGLGETCOMPRESSEDTEXIMAGEPROC	glGetCompressedTexImage;
		const PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture;
		const PFNGLMULTITEXCOORD1DPROC			glMultiTexCoord1d;
		const PFNGLMULTITEXCOORD1DVPROC			glMultiTexCoord1dv;
		const PFNGLMULTITEXCOORD1FPROC			glMultiTexCoord1f;
		const PFNGLMULTITEXCOORD1FVPROC			glMultiTexCoord1fv;
		const PFNGLMULTITEXCOORD1IPROC			glMultiTexCoord1i;
		const PFNGLMULTITEXCOORD1IVPROC			glMultiTexCoord1iv;
		const PFNGLMULTITEXCOORD1SPROC			glMultiTexCoord1s;
		const PFNGLMULTITEXCOORD1SVPROC			glMultiTexCoord1sv;
		const PFNGLMULTITEXCOORD2DPROC			glMultiTexCoord2d;
		const PFNGLMULTITEXCOORD2DVPROC			glMultiTexCoord2dv;
		const PFNGLMULTITEXCOORD2FPROC			glMultiTexCoord2f;
		const PFNGLMULTITEXCOORD2FVPROC			glMultiTexCoord2fv;
		const PFNGLMULTITEXCOORD2IPROC			glMultiTexCoord2i;
		const PFNGLMULTITEXCOORD2IVPROC			glMultiTexCoord2iv;
		const PFNGLMULTITEXCOORD2SPROC			glMultiTexCoord2s;
		const PFNGLMULTITEXCOORD2SVPROC			glMultiTexCoord2sv;
		const PFNGLMULTITEXCOORD3DPROC			glMultiTexCoord3d;
		const PFNGLMULTITEXCOORD3DVPROC			glMultiTexCoord3dv;
		const PFNGLMULTITEXCOORD3FPROC			glMultiTexCoord3f;
		const PFNGLMULTITEXCOORD3FVPROC			glMultiTexCoord3fv;
		const PFNGLMULTITEXCOORD3IPROC			glMultiTexCoord3i;
		const PFNGLMULTITEXCOORD3IVPROC			glMultiTexCoord3iv;
		const PFNGLMULTITEXCOORD3SPROC			glMultiTexCoord3s;
		const PFNGLMULTITEXCOORD3SVPROC			glMultiTexCoord3sv;
		const PFNGLMULTITEXCOORD4DPROC			glMultiTexCoord4d;
		const PFNGLMULTITEXCOORD4DVPROC			glMultiTexCoord4dv;
		const PFNGLMULTITEXCOORD4FPROC			glMultiTexCoord4f;
		const PFNGLMULTITEXCOORD4FVPROC			glMultiTexCoord4fv;
		const PFNGLMULTITEXCOORD4IPROC			glMultiTexCoord4i;
		const PFNGLMULTITEXCOORD4IVPROC			glMultiTexCoord4iv;
		const PFNGLMULTITEXCOORD4SPROC			glMultiTexCoord4s;
		const PFNGLMULTITEXCOORD4SVPROC			glMultiTexCoord4sv;
		const PFNGLLOADTRANSPOSEMATRIXFPROC		glLoadTransposeMatrixf;
		const PFNGLLOADTRANSPOSEMATRIXDPROC		glLoadTransposeMatrixd;
		const PFNGLMULTTRANSPOSEMATRIXFPROC		glMultTransposeMatrixf;
		const PFNGLMULTTRANSPOSEMATRIXDPROC		glMultTransposeMatrixd;
	protected:
		inline explicit Interface_1_3(const EmptyTag&);
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

#pragma region Interface_1_0
	void Interface_1_0::CheckForErrors() const
	{
		auto code = GetErrorCode();

		if (code != Error::Code::NoError)
		{
			throw Exception();
		}
	}
	
	Error::Code Interface_1_0::GetErrorCode() const
	{
		auto code = static_cast<Error::Code>(glGetError());

		return code;
	}
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
	Interface_1_2::Interface_1_2(const EmptyTag&):
		glDrawRangeElements		(),
		glTexImage3D			(),
		glTexSubImage3D			(),
		glCopyTexSubImage3D		()
	{
	}
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
	Interface_1_3::Interface_1_3(const EmptyTag&):
		glActiveTexture					(),
		glSampleCoverage				(),
		glCompressedTexImage3D			(),
		glCompressedTexImage2D			(),
		glCompressedTexImage1D			(),
		glCompressedTexSubImage3D		(),
		glCompressedTexSubImage2D		(),
		glCompressedTexSubImage1D		(),
		glGetCompressedTexImage			(),
		glClientActiveTexture			(),
		glMultiTexCoord1d				(),
		glMultiTexCoord1dv				(),
		glMultiTexCoord1f				(),
		glMultiTexCoord1fv				(),
		glMultiTexCoord1i				(),
		glMultiTexCoord1iv				(),
		glMultiTexCoord1s				(),
		glMultiTexCoord1sv				(),
		glMultiTexCoord2d				(),
		glMultiTexCoord2dv				(),
		glMultiTexCoord2f				(),
		glMultiTexCoord2fv				(),
		glMultiTexCoord2i				(),
		glMultiTexCoord2iv				(),
		glMultiTexCoord2s				(),
		glMultiTexCoord2sv				(),
		glMultiTexCoord3d				(),
		glMultiTexCoord3dv				(),
		glMultiTexCoord3f				(),
		glMultiTexCoord3fv				(),
		glMultiTexCoord3i				(),
		glMultiTexCoord3iv				(),
		glMultiTexCoord3s				(),
		glMultiTexCoord3sv				(),
		glMultiTexCoord4d				(),
		glMultiTexCoord4dv				(),
		glMultiTexCoord4f				(),
		glMultiTexCoord4fv				(),
		glMultiTexCoord4i				(),
		glMultiTexCoord4iv				(),
		glMultiTexCoord4s				(),
		glMultiTexCoord4sv				(),
		glLoadTransposeMatrixf			(),
		glLoadTransposeMatrixd			(),
		glMultTransposeMatrixf			(),
		glMultTransposeMatrixd			()
	{
	}
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

	class Context_1_0:
		public virtual Interface_1_0
	{
	};
	class Context_1_2:
		public Context_1_0,
		public virtual Interface_1_2
	{
	protected:
		inline explicit Context_1_2(const EmptyTag&);
		inline Context_1_2(
			// Version 1.2
			const PFNGLDRAWRANGEELEMENTSPROC&	glDrawRangeElements_,
			const PFNGLTEXIMAGE3DPROC&			glTexImage3D_,
			const PFNGLTEXSUBIMAGE3DPROC&		glTexSubImage3D_,
			const PFNGLCOPYTEXSUBIMAGE3DPROC&	glCopyTexSubImage3D_
		);
	};
	class Context_1_3:
		public Context_1_2,
		public virtual Interface_1_3
	{
	protected:
		inline Context_1_3(const EmptyTag&);
		inline Context_1_3(
			// Version 1.2
			const PFNGLDRAWRANGEELEMENTSPROC&		glDrawRangeElements_,
			const PFNGLTEXIMAGE3DPROC&				glTexImage3D_,
			const PFNGLTEXSUBIMAGE3DPROC&			glTexSubImage3D_,
			const PFNGLCOPYTEXSUBIMAGE3DPROC&		glCopyTexSubImage3D_,
			// Version 1.3
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

#pragma region Context_1_0
#pragma endregion
#pragma region Context_1_2
	Context_1_2::Context_1_2(const EmptyTag&):
		Context_1_0(),
		Interface_1_0(),
		Interface_1_2(EmptyTag())
	{
	}
	Context_1_2::Context_1_2(
		// Version 1.2
		const PFNGLDRAWRANGEELEMENTSPROC&	glDrawRangeElements_,
		const PFNGLTEXIMAGE3DPROC&			glTexImage3D_,
		const PFNGLTEXSUBIMAGE3DPROC&		glTexSubImage3D_,
		const PFNGLCOPYTEXSUBIMAGE3DPROC&	glCopyTexSubImage3D_
	):
		Context_1_0(),
		Interface_1_0(),
		Interface_1_2(
			glDrawRangeElements_	,
			glTexImage3D_			,
			glTexSubImage3D_		,
			glCopyTexSubImage3D_	
		)
	{
	}
#pragma endregion
#pragma region Context_1_3
	Context_1_3::Context_1_3(const EmptyTag&):
		Context_1_2(EmptyTag()),
		Interface_1_0(),
		Interface_1_2(EmptyTag()),
		Interface_1_3(EmptyTag())
	{
	}
	Context_1_3::Context_1_3(
		// Version 1.2
		const PFNGLDRAWRANGEELEMENTSPROC&		glDrawRangeElements_,
		const PFNGLTEXIMAGE3DPROC&				glTexImage3D_,
		const PFNGLTEXSUBIMAGE3DPROC&			glTexSubImage3D_,
		const PFNGLCOPYTEXSUBIMAGE3DPROC&		glCopyTexSubImage3D_,
		// Version 1.3
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
		Context_1_2(EmptyTag()),
		Interface_1_2(
			glDrawRangeElements_,
			glTexImage3D_,
			glTexSubImage3D_,
			glCopyTexSubImage3D_
		),
		Interface_1_3(
			glActiveTexture_,
			glSampleCoverage_,
			glCompressedTexImage3D_,
			glCompressedTexImage2D_,
			glCompressedTexImage1D_,
			glCompressedTexSubImage3D_,
			glCompressedTexSubImage2D_,
			glCompressedTexSubImage1D_,
			glGetCompressedTexImage_,
			glClientActiveTexture_,
			glMultiTexCoord1d_,
			glMultiTexCoord1dv_,
			glMultiTexCoord1f_,
			glMultiTexCoord1fv_,
			glMultiTexCoord1i_,
			glMultiTexCoord1iv_,
			glMultiTexCoord1s_,
			glMultiTexCoord1sv_,
			glMultiTexCoord2d_,
			glMultiTexCoord2dv_,
			glMultiTexCoord2f_,
			glMultiTexCoord2fv_,
			glMultiTexCoord2i_,
			glMultiTexCoord2iv_,
			glMultiTexCoord2s_,
			glMultiTexCoord2sv_,
			glMultiTexCoord3d_,
			glMultiTexCoord3dv_,
			glMultiTexCoord3f_,
			glMultiTexCoord3fv_,
			glMultiTexCoord3i_,
			glMultiTexCoord3iv_,
			glMultiTexCoord3s_,
			glMultiTexCoord3sv_,
			glMultiTexCoord4d_,
			glMultiTexCoord4dv_,
			glMultiTexCoord4f_,
			glMultiTexCoord4fv_,
			glMultiTexCoord4i_,
			glMultiTexCoord4iv_,
			glMultiTexCoord4s_,
			glMultiTexCoord4sv_,
			glLoadTransposeMatrixf_,
			glLoadTransposeMatrixd_,
			glMultTransposeMatrixf_,
			glMultTransposeMatrixd_
		)
	{
	}
#pragma endregion

	namespace OSs
	{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
		namespace Windows
		{
			class Context
			{
			protected:
				using Attributes			= Vector<GLint>;
			public:
				using Handle				= HGLRC;
				using DeviceContextHandle	= HDC;
				using Procedure				= PROC;
			};
			class Context_1_0:
				public Context,
				protected virtual OpenGL::Context_1_0
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
				protected virtual OpenGL::Context_1_2
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
				public virtual OpenGL::Context_1_3
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
				OpenGL::Context_1_2(EmptyTag()),
				OpenGL::Interface_1_2(
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
				OpenGL::Context_1_2(EmptyTag()),
				OpenGL::Interface_1_2(EmptyTag())
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

			Context_1_3::Context_1_3(const Handle& handle_):
				Windows::Context_1_2(handle_, EmptyTag()),
				OpenGL::Context_1_2(EmptyTag()),
				OpenGL::Context_1_3(EmptyTag()),
				OpenGL::Interface_1_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElements,	handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3D,			handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexSubImage3D,		handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyTexSubImage3D,	handle_)
				),
				OpenGL::Interface_1_3(
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


HWND GetWindow(HINSTANCE instanceHandle, const std::string& windowClassName)
{
	HWND windowHandle = CreateWindowA(
		windowClassName.c_str(),
		"window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600,
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

	auto windowHandle				= GetWindow(instanceHandle, windowClassName);
	auto deviceContextHandle		= GetDeviceContext(windowHandle);
	auto renderContext1Handle		= GL::Context_1_0(deviceContextHandle);

	auto window2Handle				= GetWindow(instanceHandle, windowClassName);
	auto deviceContext2Handle		= GetDeviceContext(window2Handle);
	auto renderContext2Handle		= GL::Context_1_2(deviceContext2Handle);

	auto window3Handle				= GetWindow(instanceHandle, windowClassName);
	auto deviceContext3Handle		= GetDeviceContext(window3Handle);
	auto renderContext3Handle		= GL::Context_1_3(deviceContext3Handle);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MSG msg;
		{
			while (PeekMessageA(&msg, windowHandle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window2Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			while (PeekMessageA(&msg, window3Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		GL::MakeCurrent(deviceContextHandle, renderContext1Handle.GetHandle());

		renderContext1Handle.ConfigureViewport(0, 0, 800, 600);
		renderContext1Handle.ClearColor(1, 0, 0, 0);
		renderContext1Handle.Clear(GL_COLOR_BUFFER_BIT);
		renderContext1Handle.Flush();

		SwapBuffers(deviceContextHandle);

		GL::MakeCurrent(deviceContext2Handle, renderContext2Handle.GetHandle());

		renderContext2Handle.ConfigureViewport(0, 0, 800, 600);
		renderContext2Handle.ClearColor(0, 1, 0, 0);
		renderContext2Handle.Clear(GL_COLOR_BUFFER_BIT);
		renderContext2Handle.Flush();

		SwapBuffers(deviceContext2Handle);

		GL::MakeCurrent(deviceContext3Handle, renderContext3Handle.GetHandle());

		renderContext3Handle.ConfigureViewport(0, 0, 800, 600);
		renderContext3Handle.ClearColor(0, 0, 1, 0);
		renderContext3Handle.Clear(GL_COLOR_BUFFER_BIT);
		renderContext3Handle.Flush();

		SwapBuffers(deviceContext3Handle);
	}

	GL::MakeCurrent(nullptr, nullptr);
}


#pragma region
#pragma endregion



