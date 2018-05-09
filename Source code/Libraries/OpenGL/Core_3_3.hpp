#pragma region Include

#pragma once

#include "Core_3_2.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Core_3_3:
			public virtual Core
		{
		protected:
			const PFNGLBINDFRAGDATALOCATIONINDEXEDPROC		glBindFragDataLocationIndexed = nullptr;
			const PFNGLGETFRAGDATAINDEXPROC					glGetFragDataIndex = nullptr;
			const PFNGLGENSAMPLERSPROC						glGenSamplers = nullptr;
			const PFNGLDELETESAMPLERSPROC					glDeleteSamplers = nullptr;
			const PFNGLISSAMPLERPROC						glIsSampler = nullptr;
			const PFNGLBINDSAMPLERPROC						glBindSampler = nullptr;
			const PFNGLSAMPLERPARAMETERIPROC				glSamplerParameteri = nullptr;
			const PFNGLSAMPLERPARAMETERIVPROC				glSamplerParameteriv = nullptr;
			const PFNGLSAMPLERPARAMETERFPROC				glSamplerParameterf = nullptr;
			const PFNGLSAMPLERPARAMETERFVPROC				glSamplerParameterfv = nullptr;
			const PFNGLSAMPLERPARAMETERIIVPROC				glSamplerParameterIiv = nullptr;
			const PFNGLSAMPLERPARAMETERIUIVPROC				glSamplerParameterIuiv = nullptr;
			const PFNGLGETSAMPLERPARAMETERIVPROC			glGetSamplerParameteriv = nullptr;
			const PFNGLGETSAMPLERPARAMETERIIVPROC			glGetSamplerParameterIiv = nullptr;
			const PFNGLGETSAMPLERPARAMETERFVPROC			glGetSamplerParameterfv = nullptr;
			const PFNGLGETSAMPLERPARAMETERIUIVPROC			glGetSamplerParameterIuiv = nullptr;
			const PFNGLQUERYCOUNTERPROC						glQueryCounter = nullptr;
			const PFNGLGETQUERYOBJECTI64VPROC				glGetQueryObjecti64v = nullptr;
			const PFNGLGETQUERYOBJECTUI64VPROC				glGetQueryObjectui64v = nullptr;
			const PFNGLVERTEXATTRIBDIVISORPROC				glVertexAttribDivisor = nullptr;
			const PFNGLVERTEXATTRIBP1UIPROC					glVertexAttribP1ui = nullptr;
			const PFNGLVERTEXATTRIBP1UIVPROC				glVertexAttribP1uiv = nullptr;
			const PFNGLVERTEXATTRIBP2UIPROC					glVertexAttribP2ui = nullptr;
			const PFNGLVERTEXATTRIBP2UIVPROC				glVertexAttribP2uiv = nullptr;
			const PFNGLVERTEXATTRIBP3UIPROC					glVertexAttribP3ui = nullptr;
			const PFNGLVERTEXATTRIBP3UIVPROC				glVertexAttribP3uiv = nullptr;
			const PFNGLVERTEXATTRIBP4UIPROC					glVertexAttribP4ui = nullptr;
			const PFNGLVERTEXATTRIBP4UIVPROC				glVertexAttribP4uiv = nullptr;
			const PFNGLVERTEXP2UIPROC						glVertexP2ui = nullptr;
			const PFNGLVERTEXP2UIVPROC						glVertexP2uiv = nullptr;
			const PFNGLVERTEXP3UIPROC						glVertexP3ui = nullptr;
			const PFNGLVERTEXP3UIVPROC						glVertexP3uiv = nullptr;
			const PFNGLVERTEXP4UIPROC						glVertexP4ui = nullptr;
			const PFNGLVERTEXP4UIVPROC						glVertexP4uiv = nullptr;
			const PFNGLTEXCOORDP1UIPROC						glTexCoordP1ui = nullptr;
			const PFNGLTEXCOORDP1UIVPROC					glTexCoordP1uiv = nullptr;
			const PFNGLTEXCOORDP2UIPROC						glTexCoordP2ui = nullptr;
			const PFNGLTEXCOORDP2UIVPROC					glTexCoordP2uiv = nullptr;
			const PFNGLTEXCOORDP3UIPROC						glTexCoordP3ui = nullptr;
			const PFNGLTEXCOORDP3UIVPROC					glTexCoordP3uiv = nullptr;
			const PFNGLTEXCOORDP4UIPROC						glTexCoordP4ui = nullptr;
			const PFNGLTEXCOORDP4UIVPROC					glTexCoordP4uiv = nullptr;
			const PFNGLMULTITEXCOORDP1UIPROC				glMultiTexCoordP1ui = nullptr;
			const PFNGLMULTITEXCOORDP1UIVPROC				glMultiTexCoordP1uiv = nullptr;
			const PFNGLMULTITEXCOORDP2UIPROC				glMultiTexCoordP2ui = nullptr;
			const PFNGLMULTITEXCOORDP2UIVPROC				glMultiTexCoordP2uiv = nullptr;
			const PFNGLMULTITEXCOORDP3UIPROC				glMultiTexCoordP3ui = nullptr;
			const PFNGLMULTITEXCOORDP3UIVPROC				glMultiTexCoordP3uiv = nullptr;
			const PFNGLMULTITEXCOORDP4UIPROC				glMultiTexCoordP4ui = nullptr;
			const PFNGLMULTITEXCOORDP4UIVPROC				glMultiTexCoordP4uiv = nullptr;
			const PFNGLNORMALP3UIPROC						glNormalP3ui = nullptr;
			const PFNGLNORMALP3UIVPROC						glNormalP3uiv = nullptr;
			const PFNGLCOLORP3UIPROC						glColorP3ui = nullptr;
			const PFNGLCOLORP3UIVPROC						glColorP3uiv = nullptr;
			const PFNGLCOLORP4UIPROC						glColorP4ui = nullptr;
			const PFNGLCOLORP4UIVPROC						glColorP4uiv = nullptr;
			const PFNGLSECONDARYCOLORP3UIPROC				glSecondaryColorP3ui = nullptr;
			const PFNGLSECONDARYCOLORP3UIVPROC				glSecondaryColorP3uiv = nullptr;
		protected:
			inline Core_3_3() = default;
			inline Core_3_3(
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
#pragma region Core_3_3
		Core_3_3::Core_3_3(
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
		glBindFragDataLocationIndexed(glBindFragDataLocationIndexed_),
			glGetFragDataIndex(glGetFragDataIndex_),
			glGenSamplers(glGenSamplers_),
			glDeleteSamplers(glDeleteSamplers_),
			glIsSampler(glIsSampler_),
			glBindSampler(glBindSampler_),
			glSamplerParameteri(glSamplerParameteri_),
			glSamplerParameteriv(glSamplerParameteriv_),
			glSamplerParameterf(glSamplerParameterf_),
			glSamplerParameterfv(glSamplerParameterfv_),
			glSamplerParameterIiv(glSamplerParameterIiv_),
			glSamplerParameterIuiv(glSamplerParameterIuiv_),
			glGetSamplerParameteriv(glGetSamplerParameteriv_),
			glGetSamplerParameterIiv(glGetSamplerParameterIiv_),
			glGetSamplerParameterfv(glGetSamplerParameterfv_),
			glGetSamplerParameterIuiv(glGetSamplerParameterIuiv_),
			glQueryCounter(glQueryCounter_),
			glGetQueryObjecti64v(glGetQueryObjecti64v_),
			glGetQueryObjectui64v(glGetQueryObjectui64v_),
			glVertexAttribDivisor(glVertexAttribDivisor_),
			glVertexAttribP1ui(glVertexAttribP1ui_),
			glVertexAttribP1uiv(glVertexAttribP1uiv_),
			glVertexAttribP2ui(glVertexAttribP2ui_),
			glVertexAttribP2uiv(glVertexAttribP2uiv_),
			glVertexAttribP3ui(glVertexAttribP3ui_),
			glVertexAttribP3uiv(glVertexAttribP3uiv_),
			glVertexAttribP4ui(glVertexAttribP4ui_),
			glVertexAttribP4uiv(glVertexAttribP4uiv_),
			glVertexP2ui(glVertexP2ui_),
			glVertexP2uiv(glVertexP2uiv_),
			glVertexP3ui(glVertexP3ui_),
			glVertexP3uiv(glVertexP3uiv_),
			glVertexP4ui(glVertexP4ui_),
			glVertexP4uiv(glVertexP4uiv_),
			glTexCoordP1ui(glTexCoordP1ui_),
			glTexCoordP1uiv(glTexCoordP1uiv_),
			glTexCoordP2ui(glTexCoordP2ui_),
			glTexCoordP2uiv(glTexCoordP2uiv_),
			glTexCoordP3ui(glTexCoordP3ui_),
			glTexCoordP3uiv(glTexCoordP3uiv_),
			glTexCoordP4ui(glTexCoordP4ui_),
			glTexCoordP4uiv(glTexCoordP4uiv_),
			glMultiTexCoordP1ui(glMultiTexCoordP1ui_),
			glMultiTexCoordP1uiv(glMultiTexCoordP1uiv_),
			glMultiTexCoordP2ui(glMultiTexCoordP2ui_),
			glMultiTexCoordP2uiv(glMultiTexCoordP2uiv_),
			glMultiTexCoordP3ui(glMultiTexCoordP3ui_),
			glMultiTexCoordP3uiv(glMultiTexCoordP3uiv_),
			glMultiTexCoordP4ui(glMultiTexCoordP4ui_),
			glMultiTexCoordP4uiv(glMultiTexCoordP4uiv_),
			glNormalP3ui(glNormalP3ui_),
			glNormalP3uiv(glNormalP3uiv_),
			glColorP3ui(glColorP3ui_),
			glColorP3uiv(glColorP3uiv_),
			glColorP4ui(glColorP4ui_),
			glColorP4uiv(glColorP4uiv_),
			glSecondaryColorP3ui(glSecondaryColorP3ui_),
			glSecondaryColorP3uiv(glSecondaryColorP3uiv_)
		{
		}
#pragma endregion

		class Context_3_3:
			public Context_3_2,
			public virtual Core_3_3
		{
		};
#pragma region Context_3_3
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_3_3
				Context_3_3::Attributes Context_3_3::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
						WGL_CONTEXT_MINOR_VERSION_ARB, 3,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_3_3::Context_3_3(const Handle& handle_, const EmptyTag&):
					Windows::Context_3_2(handle_, EmptyTag()),
					OpenGL::Context_3_3(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4(),
					Core_1_5(),
					Core_2_0(),
					Core_2_1(),
					Core_3_0(),
					Core_3_1(),
					Core_3_2(),
					Core_3_3()
				{
					}
				Context_3_3::Context_3_3(const Handle& handle_):
					Windows::Context_3_2(handle_, EmptyTag()),
					OpenGL::Context_3_3(),
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
					),
					Core_2_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparate, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawBuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilOpSeparate, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilFuncSeparate, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glStencilMaskSeparate, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glAttachShader, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindAttribLocation, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCompileShader, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShader, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteShader, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDetachShader, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisableVertexAttribArray, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnableVertexAttribArray, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveAttrib, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniform, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttachedShaders, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetAttribLocation, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramInfoLog, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderInfoLog, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderSource, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformLocation, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribdv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribPointerv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsShader, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glLinkProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderSource, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib1sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib2sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib3sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nbv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Niv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nsv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nub, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nubv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4Nusv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4bv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4s, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4ubv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttrib4usv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribPointer, handle_)
					),
					Core_2_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3fv, handle_)
					),
					Core_3_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorMaski, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBooleani_v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetIntegeri_v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEnablei, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDisablei, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsEnabledi, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferRange, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindBufferBase, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTransformFeedbackVaryings, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTransformFeedbackVarying, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClampColor, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginConditionalRender, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndConditionalRender, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribIPointer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribIuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI1uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4bv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4sv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4ubv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribI4usv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocation, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataLocation, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexParameterIuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetTexParameterIuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearBufferfi, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetStringi, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsRenderbuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindRenderbuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteRenderbuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenRenderbuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorage, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetRenderbufferParameteriv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsFramebuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFramebuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteFramebuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenFramebuffers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCheckFramebufferStatus, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture1D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture2D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture3D, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferRenderbuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFramebufferAttachmentParameteriv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenerateMipmap, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlitFramebuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glRenderbufferStorageMultisample, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTextureLayer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMapBufferRange, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFlushMappedBufferRange, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindVertexArray, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteVertexArrays, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenVertexArrays, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsVertexArray, handle_)
					),
					Core_3_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysInstanced, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstanced, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexBuffer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPrimitiveRestartIndex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCopyBufferSubData, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformIndices, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformsiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformName, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformBlockIndex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveUniformBlockName, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformBlockBinding, handle_)
					),
					Core_3_2(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsBaseVertex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawRangeElementsBaseVertex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsInstancedBaseVertex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiDrawElementsBaseVertex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProvokingVertex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFenceSync, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSync, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSync, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClientWaitSync, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glWaitSync, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSynciv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetInteger64i_v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetBufferParameteri64v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glFramebufferTexture, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage2DMultisample, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexImage3DMultisample, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetMultisamplefv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSampleMaski, handle_)
					),
					Core_3_3(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindFragDataLocationIndexed, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFragDataIndex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenSamplers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteSamplers, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsSampler, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindSampler, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteri, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameteriv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSamplerParameterIuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameteriv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSamplerParameterIuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glQueryCounter, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjecti64v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryObjectui64v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribDivisor, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP1uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribP4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexP4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP1uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glTexCoordP4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP1uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMultiTexCoordP4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glNormalP3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glColorP4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glSecondaryColorP3uiv, handle_)
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_3_3::Context_3_3(const DeviceContextHandle& deviceContextHandle_):
					Context_3_3(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
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


