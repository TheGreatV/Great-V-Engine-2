#pragma region Include

#pragma once

#include "Core_3_1.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Core_3_2:
			public virtual Core
		{
		protected:
			const PFNGLDRAWELEMENTSBASEVERTEXPROC			glDrawElementsBaseVertex = nullptr;
			const PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC		glDrawRangeElementsBaseVertex = nullptr;
			const PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC	glDrawElementsInstancedBaseVertex = nullptr;
			const PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC		glMultiDrawElementsBaseVertex = nullptr;
			const PFNGLPROVOKINGVERTEXPROC					glProvokingVertex = nullptr;
			const PFNGLFENCESYNCPROC						glFenceSync = nullptr;
			const PFNGLISSYNCPROC							glIsSync = nullptr;
			const PFNGLDELETESYNCPROC						glDeleteSync = nullptr;
			const PFNGLCLIENTWAITSYNCPROC					glClientWaitSync = nullptr;
			const PFNGLWAITSYNCPROC							glWaitSync = nullptr;
			const PFNGLGETINTEGER64VPROC					glGetInteger64v = nullptr;
			const PFNGLGETSYNCIVPROC						glGetSynciv = nullptr;
			const PFNGLGETINTEGER64I_VPROC					glGetInteger64i_v = nullptr;
			const PFNGLGETBUFFERPARAMETERI64VPROC			glGetBufferParameteri64v = nullptr;
			const PFNGLFRAMEBUFFERTEXTUREPROC				glFramebufferTexture = nullptr;
			const PFNGLTEXIMAGE2DMULTISAMPLEPROC			glTexImage2DMultisample = nullptr;
			const PFNGLTEXIMAGE3DMULTISAMPLEPROC			glTexImage3DMultisample = nullptr;
			const PFNGLGETMULTISAMPLEFVPROC					glGetMultisamplefv = nullptr;
			const PFNGLSAMPLEMASKIPROC						glSampleMaski = nullptr;
		protected:
			inline Core_3_2() = default;
			inline Core_3_2(
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
		public:
			inline void DrawElementsBaseVertex(const PrimitiveType& primitiveType_, const Size& indicesCount_, const IndexType& indexType_, const Size& indicesOffset_, const Size& baseVertex_) const
			{
				glDrawElementsBaseVertex(static_cast<GLenum>(primitiveType_), indicesCount_, static_cast<GLenum>(indexType_), reinterpret_cast<const void*>(indicesOffset_), baseVertex_);

				CheckForErrors();
			}
		};
#pragma region Core_3_2
		Core_3_2::Core_3_2(
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
			glDrawElementsBaseVertex(glDrawElementsBaseVertex_),
			glDrawRangeElementsBaseVertex(glDrawRangeElementsBaseVertex_),
			glDrawElementsInstancedBaseVertex(glDrawElementsInstancedBaseVertex_),
			glMultiDrawElementsBaseVertex(glMultiDrawElementsBaseVertex_),
			glProvokingVertex(glProvokingVertex_),
			glFenceSync(glFenceSync_),
			glIsSync(glIsSync_),
			glDeleteSync(glDeleteSync_),
			glClientWaitSync(glClientWaitSync_),
			glWaitSync(glWaitSync_),
			glGetInteger64v(glGetInteger64v_),
			glGetSynciv(glGetSynciv_),
			glGetInteger64i_v(glGetInteger64i_v_),
			glGetBufferParameteri64v(glGetBufferParameteri64v_),
			glFramebufferTexture(glFramebufferTexture_),
			glTexImage2DMultisample(glTexImage2DMultisample_),
			glTexImage3DMultisample(glTexImage3DMultisample_),
			glGetMultisamplefv(glGetMultisamplefv_),
			glSampleMaski(glSampleMaski_)
		{
		}
#pragma endregion

		class Context_3_2:
			public Context_3_1,
			public virtual Core_3_2
		{
		};
#pragma region Context_3_2
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_3_2
				Context_3_2::Attributes Context_3_2::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
						WGL_CONTEXT_MINOR_VERSION_ARB, 2,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_3_2::Context_3_2(const Handle& handle_, const EmptyTag&):
					Windows::Context_3_1(handle_, EmptyTag()),
					OpenGL::Context_3_2(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4(),
					Core_1_5(),
					Core_2_0(),
					Core_2_1(),
					Core_3_0(),
					Core_3_1(),
					Core_3_2()
				{
					}
				Context_3_2::Context_3_2(const Handle& handle_):
					Windows::Context_3_1(handle_, EmptyTag()),
					OpenGL::Context_3_2(),
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
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_3_2::Context_3_2(const DeviceContextHandle& deviceContextHandle_):
					Context_3_2(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
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


