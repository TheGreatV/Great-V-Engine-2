#pragma region Include

#pragma once

#include "Core_1_2.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Core_1_3:
			public virtual Core
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
			inline Core_1_3() = default;
			inline Core_1_3(
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
#pragma region Core_1_3
		Core_1_3::Core_1_3(
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

		class Context_1_3:
			public Context_1_2,
			public virtual Core_1_3
		{
		};
#pragma region Context_1_3
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_1_3
				Context_1_3::Attributes Context_1_3::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
						WGL_CONTEXT_MINOR_VERSION_ARB, 3,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_1_3::Context_1_3(const Handle& handle_, const EmptyTag&):
					Windows::Context_1_2(handle_, EmptyTag()),
					OpenGL::Context_1_3(),
					Core_1_2(),
					Core_1_3()
				{
					}
				Context_1_3::Context_1_3(const Handle& handle_):
					Windows::Context_1_2(handle_, EmptyTag()),
					OpenGL::Context_1_3(),
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
					)
				{
						MakeCurrent(nullptr, nullptr);
					}
				Context_1_3::Context_1_3(const DeviceContextHandle& deviceContextHandle_):
					Context_1_3(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
				{
				}
#pragma endregion
			}
#endif
		}
	}
}


#pragma region
#pragma endregion


