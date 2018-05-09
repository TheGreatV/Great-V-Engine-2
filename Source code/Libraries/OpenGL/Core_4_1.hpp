#pragma region Include

#pragma once

#include "Core_4_0.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Core_4_1:
			public virtual Core
		{
		protected:
			const PFNGLRELEASESHADERCOMPILERPROC			glReleaseShaderCompiler = nullptr;
			const PFNGLSHADERBINARYPROC						glShaderBinary = nullptr;
			const PFNGLGETSHADERPRECISIONFORMATPROC			glGetShaderPrecisionFormat = nullptr;
			const PFNGLDEPTHRANGEFPROC						glDepthRangef = nullptr;
			const PFNGLCLEARDEPTHFPROC						glClearDepthf = nullptr;
			const PFNGLGETPROGRAMBINARYPROC					glGetProgramBinary = nullptr;
			const PFNGLPROGRAMBINARYPROC					glProgramBinary = nullptr;
			const PFNGLPROGRAMPARAMETERIPROC				glProgramParameteri = nullptr;
			const PFNGLUSEPROGRAMSTAGESPROC					glUseProgramStages = nullptr;
			const PFNGLACTIVESHADERPROGRAMPROC				glActiveShaderProgram = nullptr;
			const PFNGLCREATESHADERPROGRAMVPROC				glCreateShaderProgramv = nullptr;
			const PFNGLBINDPROGRAMPIPELINEPROC				glBindProgramPipeline = nullptr;
			const PFNGLDELETEPROGRAMPIPELINESPROC			glDeleteProgramPipelines = nullptr;
			const PFNGLGENPROGRAMPIPELINESPROC				glGenProgramPipelines = nullptr;
			const PFNGLISPROGRAMPIPELINEPROC				glIsProgramPipeline = nullptr;
			const PFNGLGETPROGRAMPIPELINEIVPROC				glGetProgramPipelineiv = nullptr;
			const PFNGLPROGRAMUNIFORM1IPROC					glProgramUniform1i = nullptr;
			const PFNGLPROGRAMUNIFORM1IVPROC				glProgramUniform1iv = nullptr;
			const PFNGLPROGRAMUNIFORM1FPROC					glProgramUniform1f = nullptr;
			const PFNGLPROGRAMUNIFORM1FVPROC				glProgramUniform1fv = nullptr;
			const PFNGLPROGRAMUNIFORM1DPROC					glProgramUniform1d = nullptr;
			const PFNGLPROGRAMUNIFORM1DVPROC				glProgramUniform1dv = nullptr;
			const PFNGLPROGRAMUNIFORM1UIPROC				glProgramUniform1ui = nullptr;
			const PFNGLPROGRAMUNIFORM1UIVPROC				glProgramUniform1uiv = nullptr;
			const PFNGLPROGRAMUNIFORM2IPROC					glProgramUniform2i = nullptr;
			const PFNGLPROGRAMUNIFORM2IVPROC				glProgramUniform2iv = nullptr;
			const PFNGLPROGRAMUNIFORM2FPROC					glProgramUniform2f = nullptr;
			const PFNGLPROGRAMUNIFORM2FVPROC				glProgramUniform2fv = nullptr;
			const PFNGLPROGRAMUNIFORM2DPROC					glProgramUniform2d = nullptr;
			const PFNGLPROGRAMUNIFORM2DVPROC				glProgramUniform2dv = nullptr;
			const PFNGLPROGRAMUNIFORM2UIPROC				glProgramUniform2ui = nullptr;
			const PFNGLPROGRAMUNIFORM2UIVPROC				glProgramUniform2uiv = nullptr;
			const PFNGLPROGRAMUNIFORM3IPROC					glProgramUniform3i = nullptr;
			const PFNGLPROGRAMUNIFORM3IVPROC				glProgramUniform3iv = nullptr;
			const PFNGLPROGRAMUNIFORM3FPROC					glProgramUniform3f = nullptr;
			const PFNGLPROGRAMUNIFORM3FVPROC				glProgramUniform3fv = nullptr;
			const PFNGLPROGRAMUNIFORM3DPROC					glProgramUniform3d = nullptr;
			const PFNGLPROGRAMUNIFORM3DVPROC				glProgramUniform3dv = nullptr;
			const PFNGLPROGRAMUNIFORM3UIPROC				glProgramUniform3ui = nullptr;
			const PFNGLPROGRAMUNIFORM3UIVPROC				glProgramUniform3uiv = nullptr;
			const PFNGLPROGRAMUNIFORM4IPROC					glProgramUniform4i = nullptr;
			const PFNGLPROGRAMUNIFORM4IVPROC				glProgramUniform4iv = nullptr;
			const PFNGLPROGRAMUNIFORM4FPROC					glProgramUniform4f = nullptr;
			const PFNGLPROGRAMUNIFORM4FVPROC				glProgramUniform4fv = nullptr;
			const PFNGLPROGRAMUNIFORM4DPROC					glProgramUniform4d = nullptr;
			const PFNGLPROGRAMUNIFORM4DVPROC				glProgramUniform4dv = nullptr;
			const PFNGLPROGRAMUNIFORM4UIPROC				glProgramUniform4ui = nullptr;
			const PFNGLPROGRAMUNIFORM4UIVPROC				glProgramUniform4uiv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX2FVPROC			glProgramUniformMatrix2fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX3FVPROC			glProgramUniformMatrix3fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX4FVPROC			glProgramUniformMatrix4fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX2DVPROC			glProgramUniformMatrix2dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX3DVPROC			glProgramUniformMatrix3dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX4DVPROC			glProgramUniformMatrix4dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC		glProgramUniformMatrix2x3fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC		glProgramUniformMatrix3x2fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC		glProgramUniformMatrix2x4fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC		glProgramUniformMatrix4x2fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC		glProgramUniformMatrix3x4fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC		glProgramUniformMatrix4x3fv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC		glProgramUniformMatrix2x3dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC		glProgramUniformMatrix3x2dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC		glProgramUniformMatrix2x4dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC		glProgramUniformMatrix4x2dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC		glProgramUniformMatrix3x4dv = nullptr;
			const PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC		glProgramUniformMatrix4x3dv = nullptr;
			const PFNGLVALIDATEPROGRAMPIPELINEPROC			glValidateProgramPipeline = nullptr;
			const PFNGLGETPROGRAMPIPELINEINFOLOGPROC		glGetProgramPipelineInfoLog = nullptr;
			const PFNGLVERTEXATTRIBL1DPROC					glVertexAttribL1d = nullptr;
			const PFNGLVERTEXATTRIBL2DPROC					glVertexAttribL2d = nullptr;
			const PFNGLVERTEXATTRIBL3DPROC					glVertexAttribL3d = nullptr;
			const PFNGLVERTEXATTRIBL4DPROC					glVertexAttribL4d = nullptr;
			const PFNGLVERTEXATTRIBL1DVPROC					glVertexAttribL1dv = nullptr;
			const PFNGLVERTEXATTRIBL2DVPROC					glVertexAttribL2dv = nullptr;
			const PFNGLVERTEXATTRIBL3DVPROC					glVertexAttribL3dv = nullptr;
			const PFNGLVERTEXATTRIBL4DVPROC					glVertexAttribL4dv = nullptr;
			const PFNGLVERTEXATTRIBLPOINTERPROC				glVertexAttribLPointer = nullptr;
			const PFNGLGETVERTEXATTRIBLDVPROC				glGetVertexAttribLdv = nullptr;
			const PFNGLVIEWPORTARRAYVPROC					glViewportArrayv = nullptr;
			const PFNGLVIEWPORTINDEXEDFPROC					glViewportIndexedf = nullptr;
			const PFNGLVIEWPORTINDEXEDFVPROC				glViewportIndexedfv = nullptr;
			const PFNGLSCISSORARRAYVPROC					glScissorArrayv = nullptr;
			const PFNGLSCISSORINDEXEDPROC					glScissorIndexed = nullptr;
			const PFNGLSCISSORINDEXEDVPROC					glScissorIndexedv = nullptr;
			const PFNGLDEPTHRANGEARRAYVPROC					glDepthRangeArrayv = nullptr;
			const PFNGLDEPTHRANGEINDEXEDPROC				glDepthRangeIndexed = nullptr;
			const PFNGLGETFLOATI_VPROC						glGetFloati_v = nullptr;
			const PFNGLGETDOUBLEI_VPROC						glGetDoublei_v = nullptr;
		protected:
			inline Core_4_1() = default;
			inline Core_4_1(
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
#pragma region Core_4_1
		Core_4_1::Core_4_1(
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
		glReleaseShaderCompiler(glReleaseShaderCompiler_),
			glShaderBinary(glShaderBinary_),
			glGetShaderPrecisionFormat(glGetShaderPrecisionFormat_),
			glDepthRangef(glDepthRangef_),
			glClearDepthf(glClearDepthf_),
			glGetProgramBinary(glGetProgramBinary_),
			glProgramBinary(glProgramBinary_),
			glProgramParameteri(glProgramParameteri_),
			glUseProgramStages(glUseProgramStages_),
			glActiveShaderProgram(glActiveShaderProgram_),
			glCreateShaderProgramv(glCreateShaderProgramv_),
			glBindProgramPipeline(glBindProgramPipeline_),
			glDeleteProgramPipelines(glDeleteProgramPipelines_),
			glGenProgramPipelines(glGenProgramPipelines_),
			glIsProgramPipeline(glIsProgramPipeline_),
			glGetProgramPipelineiv(glGetProgramPipelineiv_),
			glProgramUniform1i(glProgramUniform1i_),
			glProgramUniform1iv(glProgramUniform1iv_),
			glProgramUniform1f(glProgramUniform1f_),
			glProgramUniform1fv(glProgramUniform1fv_),
			glProgramUniform1d(glProgramUniform1d_),
			glProgramUniform1dv(glProgramUniform1dv_),
			glProgramUniform1ui(glProgramUniform1ui_),
			glProgramUniform1uiv(glProgramUniform1uiv_),
			glProgramUniform2i(glProgramUniform2i_),
			glProgramUniform2iv(glProgramUniform2iv_),
			glProgramUniform2f(glProgramUniform2f_),
			glProgramUniform2fv(glProgramUniform2fv_),
			glProgramUniform2d(glProgramUniform2d_),
			glProgramUniform2dv(glProgramUniform2dv_),
			glProgramUniform2ui(glProgramUniform2ui_),
			glProgramUniform2uiv(glProgramUniform2uiv_),
			glProgramUniform3i(glProgramUniform3i_),
			glProgramUniform3iv(glProgramUniform3iv_),
			glProgramUniform3f(glProgramUniform3f_),
			glProgramUniform3fv(glProgramUniform3fv_),
			glProgramUniform3d(glProgramUniform3d_),
			glProgramUniform3dv(glProgramUniform3dv_),
			glProgramUniform3ui(glProgramUniform3ui_),
			glProgramUniform3uiv(glProgramUniform3uiv_),
			glProgramUniform4i(glProgramUniform4i_),
			glProgramUniform4iv(glProgramUniform4iv_),
			glProgramUniform4f(glProgramUniform4f_),
			glProgramUniform4fv(glProgramUniform4fv_),
			glProgramUniform4d(glProgramUniform4d_),
			glProgramUniform4dv(glProgramUniform4dv_),
			glProgramUniform4ui(glProgramUniform4ui_),
			glProgramUniform4uiv(glProgramUniform4uiv_),
			glProgramUniformMatrix2fv(glProgramUniformMatrix2fv_),
			glProgramUniformMatrix3fv(glProgramUniformMatrix3fv_),
			glProgramUniformMatrix4fv(glProgramUniformMatrix4fv_),
			glProgramUniformMatrix2dv(glProgramUniformMatrix2dv_),
			glProgramUniformMatrix3dv(glProgramUniformMatrix3dv_),
			glProgramUniformMatrix4dv(glProgramUniformMatrix4dv_),
			glProgramUniformMatrix2x3fv(glProgramUniformMatrix2x3fv_),
			glProgramUniformMatrix3x2fv(glProgramUniformMatrix3x2fv_),
			glProgramUniformMatrix2x4fv(glProgramUniformMatrix2x4fv_),
			glProgramUniformMatrix4x2fv(glProgramUniformMatrix4x2fv_),
			glProgramUniformMatrix3x4fv(glProgramUniformMatrix3x4fv_),
			glProgramUniformMatrix4x3fv(glProgramUniformMatrix4x3fv_),
			glProgramUniformMatrix2x3dv(glProgramUniformMatrix2x3dv_),
			glProgramUniformMatrix3x2dv(glProgramUniformMatrix3x2dv_),
			glProgramUniformMatrix2x4dv(glProgramUniformMatrix2x4dv_),
			glProgramUniformMatrix4x2dv(glProgramUniformMatrix4x2dv_),
			glProgramUniformMatrix3x4dv(glProgramUniformMatrix3x4dv_),
			glProgramUniformMatrix4x3dv(glProgramUniformMatrix4x3dv_),
			glValidateProgramPipeline(glValidateProgramPipeline_),
			glGetProgramPipelineInfoLog(glGetProgramPipelineInfoLog_),
			glVertexAttribL1d(glVertexAttribL1d_),
			glVertexAttribL2d(glVertexAttribL2d_),
			glVertexAttribL3d(glVertexAttribL3d_),
			glVertexAttribL4d(glVertexAttribL4d_),
			glVertexAttribL1dv(glVertexAttribL1dv_),
			glVertexAttribL2dv(glVertexAttribL2dv_),
			glVertexAttribL3dv(glVertexAttribL3dv_),
			glVertexAttribL4dv(glVertexAttribL4dv_),
			glVertexAttribLPointer(glVertexAttribLPointer_),
			glGetVertexAttribLdv(glGetVertexAttribLdv_),
			glViewportArrayv(glViewportArrayv_),
			glViewportIndexedf(glViewportIndexedf_),
			glViewportIndexedfv(glViewportIndexedfv_),
			glScissorArrayv(glScissorArrayv_),
			glScissorIndexed(glScissorIndexed_),
			glScissorIndexedv(glScissorIndexedv_),
			glDepthRangeArrayv(glDepthRangeArrayv_),
			glDepthRangeIndexed(glDepthRangeIndexed_),
			glGetFloati_v(glGetFloati_v_),
			glGetDoublei_v(glGetDoublei_v_)
		{
		}
#pragma endregion

		class Context_4_1:
			public Context_4_0,
			public virtual Core_4_1
		{
		};
#pragma region Context_4_1
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_4_1
				Context_4_1::Attributes Context_4_1::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
						WGL_CONTEXT_MINOR_VERSION_ARB, 1,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_4_1::Context_4_1(const Handle& handle_, const EmptyTag&):
					Windows::Context_4_0(handle_, EmptyTag()),
					OpenGL::Context_4_1(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4(),
					Core_1_5(),
					Core_2_0(),
					Core_2_1(),
					Core_3_0(),
					Core_3_1(),
					Core_3_2(),
					Core_3_3(),
					Core_4_0(),
					Core_4_1()
				{
					}
				Context_4_1::Context_4_1(const Handle& handle_):
					Windows::Context_4_0(handle_, EmptyTag()),
					OpenGL::Context_4_1(),
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
					),
					Core_4_0(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glMinSampleShading, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationi, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendEquationSeparatei, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFunci, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBlendFuncSeparatei, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawArraysIndirect, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawElementsIndirect, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform1dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniform4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix2x4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix3x4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformMatrix4x3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformdv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineUniformLocation, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetSubroutineIndex, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineUniformName, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetActiveSubroutineName, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUniformSubroutinesuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetUniformSubroutineuiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramStageiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameteri, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPatchParameterfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteTransformFeedbacks, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenTransformFeedbacks, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glPauseTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glResumeTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedback, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDrawTransformFeedbackStream, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBeginQueryIndexed, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glEndQueryIndexed, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetQueryIndexediv, handle_)
					),
					Core_4_1(
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glReleaseShaderCompiler, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glShaderBinary, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetShaderPrecisionFormat, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangef, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glClearDepthf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramBinary, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramBinary, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramParameteri, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glUseProgramStages, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glActiveShaderProgram, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glCreateShaderProgramv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glBindProgramPipeline, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDeleteProgramPipelines, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGenProgramPipelines, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glIsProgramPipeline, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform1uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform2uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform3uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4i, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4iv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4f, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4ui, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniform4uiv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3fv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix2x4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix3x4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glProgramUniformMatrix4x3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glValidateProgramPipeline, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetProgramPipelineInfoLog, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4d, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL1dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL2dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL3dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribL4dv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glVertexAttribLPointer, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetVertexAttribLdv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportArrayv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedf, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glViewportIndexedfv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorArrayv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexed, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glScissorIndexedv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeArrayv, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glDepthRangeIndexed, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetFloati_v, handle_),
					__GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(glGetDoublei_v, handle_)
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_4_1::Context_4_1(const DeviceContextHandle& deviceContextHandle_):
					Context_4_1(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
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


