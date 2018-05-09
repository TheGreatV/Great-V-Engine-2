#pragma region Include

#pragma once

#include "Core_1_3.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Core_1_4:
			public virtual Core
		{
		protected:
			const PFNGLBLENDFUNCSEPARATEPROC		glBlendFuncSeparate = nullptr;
			const PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays = nullptr;
			const PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements = nullptr;
			const PFNGLPOINTPARAMETERFPROC			glPointParameterf = nullptr;
			const PFNGLPOINTPARAMETERFVPROC			glPointParameterfv = nullptr;
			const PFNGLPOINTPARAMETERIPROC			glPointParameteri = nullptr;
			const PFNGLPOINTPARAMETERIVPROC			glPointParameteriv = nullptr;
			const PFNGLFOGCOORDFPROC				glFogCoordf = nullptr;
			const PFNGLFOGCOORDFVPROC				glFogCoordfv = nullptr;
			const PFNGLFOGCOORDDPROC				glFogCoordd = nullptr;
			const PFNGLFOGCOORDDVPROC				glFogCoorddv = nullptr;
			const PFNGLFOGCOORDPOINTERPROC			glFogCoordPointer = nullptr;
			const PFNGLSECONDARYCOLOR3BPROC			glSecondaryColor3b = nullptr;
			const PFNGLSECONDARYCOLOR3BVPROC		glSecondaryColor3bv = nullptr;
			const PFNGLSECONDARYCOLOR3DPROC			glSecondaryColor3d = nullptr;
			const PFNGLSECONDARYCOLOR3DVPROC		glSecondaryColor3dv = nullptr;
			const PFNGLSECONDARYCOLOR3FPROC			glSecondaryColor3f = nullptr;
			const PFNGLSECONDARYCOLOR3FVPROC		glSecondaryColor3fv = nullptr;
			const PFNGLSECONDARYCOLOR3IPROC			glSecondaryColor3i = nullptr;
			const PFNGLSECONDARYCOLOR3IVPROC		glSecondaryColor3iv = nullptr;
			const PFNGLSECONDARYCOLOR3SPROC			glSecondaryColor3s = nullptr;
			const PFNGLSECONDARYCOLOR3SVPROC		glSecondaryColor3sv = nullptr;
			const PFNGLSECONDARYCOLOR3UBPROC		glSecondaryColor3ub = nullptr;
			const PFNGLSECONDARYCOLOR3UBVPROC		glSecondaryColor3ubv = nullptr;
			const PFNGLSECONDARYCOLOR3UIPROC		glSecondaryColor3ui = nullptr;
			const PFNGLSECONDARYCOLOR3UIVPROC		glSecondaryColor3uiv = nullptr;
			const PFNGLSECONDARYCOLOR3USPROC		glSecondaryColor3us = nullptr;
			const PFNGLSECONDARYCOLOR3USVPROC		glSecondaryColor3usv = nullptr;
			const PFNGLSECONDARYCOLORPOINTERPROC	glSecondaryColorPointer = nullptr;
			const PFNGLWINDOWPOS2DPROC				glWindowPos2d = nullptr;
			const PFNGLWINDOWPOS2DVPROC				glWindowPos2dv = nullptr;
			const PFNGLWINDOWPOS2FPROC				glWindowPos2f = nullptr;
			const PFNGLWINDOWPOS2FVPROC				glWindowPos2fv = nullptr;
			const PFNGLWINDOWPOS2IPROC				glWindowPos2i = nullptr;
			const PFNGLWINDOWPOS2IVPROC				glWindowPos2iv = nullptr;
			const PFNGLWINDOWPOS2SPROC				glWindowPos2s = nullptr;
			const PFNGLWINDOWPOS2SVPROC				glWindowPos2sv = nullptr;
			const PFNGLWINDOWPOS3DPROC				glWindowPos3d = nullptr;
			const PFNGLWINDOWPOS3DVPROC				glWindowPos3dv = nullptr;
			const PFNGLWINDOWPOS3FPROC				glWindowPos3f = nullptr;
			const PFNGLWINDOWPOS3FVPROC				glWindowPos3fv = nullptr;
			const PFNGLWINDOWPOS3IPROC				glWindowPos3i = nullptr;
			const PFNGLWINDOWPOS3IVPROC				glWindowPos3iv = nullptr;
			const PFNGLWINDOWPOS3SPROC				glWindowPos3s = nullptr;
			const PFNGLWINDOWPOS3SVPROC				glWindowPos3sv = nullptr;
			const PFNGLBLENDCOLORPROC				glBlendColor = nullptr;
			const PFNGLBLENDEQUATIONPROC			glBlendEquation = nullptr;
		protected:
			inline Core_1_4() = default;
			inline Core_1_4(
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
#pragma region Core_1_4
		Core_1_4::Core_1_4(
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
		glBlendFuncSeparate(glBlendFuncSeparate_),
			glMultiDrawArrays(glMultiDrawArrays_),
			glMultiDrawElements(glMultiDrawElements_),
			glPointParameterf(glPointParameterf_),
			glPointParameterfv(glPointParameterfv_),
			glPointParameteri(glPointParameteri_),
			glPointParameteriv(glPointParameteriv_),
			glFogCoordf(glFogCoordf_),
			glFogCoordfv(glFogCoordfv_),
			glFogCoordd(glFogCoordd_),
			glFogCoorddv(glFogCoorddv_),
			glFogCoordPointer(glFogCoordPointer_),
			glSecondaryColor3b(glSecondaryColor3b_),
			glSecondaryColor3bv(glSecondaryColor3bv_),
			glSecondaryColor3d(glSecondaryColor3d_),
			glSecondaryColor3dv(glSecondaryColor3dv_),
			glSecondaryColor3f(glSecondaryColor3f_),
			glSecondaryColor3fv(glSecondaryColor3fv_),
			glSecondaryColor3i(glSecondaryColor3i_),
			glSecondaryColor3iv(glSecondaryColor3iv_),
			glSecondaryColor3s(glSecondaryColor3s_),
			glSecondaryColor3sv(glSecondaryColor3sv_),
			glSecondaryColor3ub(glSecondaryColor3ub_),
			glSecondaryColor3ubv(glSecondaryColor3ubv_),
			glSecondaryColor3ui(glSecondaryColor3ui_),
			glSecondaryColor3uiv(glSecondaryColor3uiv_),
			glSecondaryColor3us(glSecondaryColor3us_),
			glSecondaryColor3usv(glSecondaryColor3usv_),
			glSecondaryColorPointer(glSecondaryColorPointer_),
			glWindowPos2d(glWindowPos2d_),
			glWindowPos2dv(glWindowPos2dv_),
			glWindowPos2f(glWindowPos2f_),
			glWindowPos2fv(glWindowPos2fv_),
			glWindowPos2i(glWindowPos2i_),
			glWindowPos2iv(glWindowPos2iv_),
			glWindowPos2s(glWindowPos2s_),
			glWindowPos2sv(glWindowPos2sv_),
			glWindowPos3d(glWindowPos3d_),
			glWindowPos3dv(glWindowPos3dv_),
			glWindowPos3f(glWindowPos3f_),
			glWindowPos3fv(glWindowPos3fv_),
			glWindowPos3i(glWindowPos3i_),
			glWindowPos3iv(glWindowPos3iv_),
			glWindowPos3s(glWindowPos3s_),
			glWindowPos3sv(glWindowPos3sv_),
			glBlendColor(glBlendColor_),
			glBlendEquation(glBlendEquation_)
		{
		}
#pragma endregion

		class Context_1_4:
			public Context_1_3,
			public virtual Core_1_4
		{
		};
#pragma region Context_1_4
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_1_4
				Context_1_4::Attributes Context_1_4::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
						WGL_CONTEXT_MINOR_VERSION_ARB, 4,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_1_4::Context_1_4(const Handle& handle_, const EmptyTag&):
					Windows::Context_1_3(handle_, EmptyTag()),
					OpenGL::Context_1_4(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4()
				{
					}
				Context_1_4::Context_1_4(const Handle& handle_):
					Windows::Context_1_3(handle_, EmptyTag()),
					OpenGL::Context_1_4(),
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
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_1_4::Context_1_4(const DeviceContextHandle& deviceContextHandle_):
					Context_1_4(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
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


