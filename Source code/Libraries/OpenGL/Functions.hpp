#pragma region Include

#pragma once

#include "Header.hpp"
#include "Exception.hpp"

#pragma endregion


#pragma region Macros

#define __GREAT_V_ENGINE_2__DECLARE_OPENGL_FUNCTION__(x) decltype(GreatVEngine2::OpenGL::x) GreatVEngine2::OpenGL::x = nullptr
#define __GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(x) if((x = reinterpret_cast<decltype(x)>(wglGetProcAddress(#x))) == nullptr) throw Exception() // ("Failed to get function pointer for \""#x"\"");

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		extern PFNWGLCREATECONTEXTATTRIBSARBPROC									wglCreateContextAttribsARB;

		// Version 1.2
		extern PFNGLDRAWRANGEELEMENTSPROC											glDrawRangeElements;
		extern PFNGLTEXIMAGE3DPROC													glTexImage3D;
		extern PFNGLTEXSUBIMAGE3DPROC												glTexSubImage3D;
		extern PFNGLCOPYTEXSUBIMAGE3DPROC											glCopyTexSubImage3D;

		// Version 1.3
		extern PFNGLACTIVETEXTUREPROC												glActiveTexture;
		extern PFNGLSAMPLECOVERAGEPROC												glSampleCoverage;
		extern PFNGLCOMPRESSEDTEXIMAGE3DPROC										glCompressedTexImage3D;
		extern PFNGLCOMPRESSEDTEXIMAGE2DPROC										glCompressedTexImage2D;
		extern PFNGLCOMPRESSEDTEXIMAGE1DPROC										glCompressedTexImage1D;
		extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC										glCompressedTexSubImage3D;
		extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC										glCompressedTexSubImage2D;
		extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC										glCompressedTexSubImage1D;
		extern PFNGLGETCOMPRESSEDTEXIMAGEPROC										glGetCompressedTexImage;
		extern PFNGLCLIENTACTIVETEXTUREPROC											glClientActiveTexture;
		extern PFNGLMULTITEXCOORD1DPROC												glMultiTexCoord1d;
		extern PFNGLMULTITEXCOORD1DVPROC											glMultiTexCoord1dv;
		extern PFNGLMULTITEXCOORD1FPROC												glMultiTexCoord1f;
		extern PFNGLMULTITEXCOORD1FVPROC											glMultiTexCoord1fv;
		extern PFNGLMULTITEXCOORD1IPROC												glMultiTexCoord1i;
		extern PFNGLMULTITEXCOORD1IVPROC											glMultiTexCoord1iv;
		extern PFNGLMULTITEXCOORD1SPROC												glMultiTexCoord1s;
		extern PFNGLMULTITEXCOORD1SVPROC											glMultiTexCoord1sv;
		extern PFNGLMULTITEXCOORD2DPROC												glMultiTexCoord2d;
		extern PFNGLMULTITEXCOORD2DVPROC											glMultiTexCoord2dv;
		extern PFNGLMULTITEXCOORD2FPROC												glMultiTexCoord2f;
		extern PFNGLMULTITEXCOORD2FVPROC											glMultiTexCoord2fv;
		extern PFNGLMULTITEXCOORD2IPROC												glMultiTexCoord2i;
		extern PFNGLMULTITEXCOORD2IVPROC											glMultiTexCoord2iv;
		extern PFNGLMULTITEXCOORD2SPROC												glMultiTexCoord2s;
		extern PFNGLMULTITEXCOORD2SVPROC											glMultiTexCoord2sv;
		extern PFNGLMULTITEXCOORD3DPROC												glMultiTexCoord3d;
		extern PFNGLMULTITEXCOORD3DVPROC											glMultiTexCoord3dv;
		extern PFNGLMULTITEXCOORD3FPROC												glMultiTexCoord3f;
		extern PFNGLMULTITEXCOORD3FVPROC											glMultiTexCoord3fv;
		extern PFNGLMULTITEXCOORD3IPROC												glMultiTexCoord3i;
		extern PFNGLMULTITEXCOORD3IVPROC											glMultiTexCoord3iv;
		extern PFNGLMULTITEXCOORD3SPROC												glMultiTexCoord3s;
		extern PFNGLMULTITEXCOORD3SVPROC											glMultiTexCoord3sv;
		extern PFNGLMULTITEXCOORD4DPROC												glMultiTexCoord4d;
		extern PFNGLMULTITEXCOORD4DVPROC											glMultiTexCoord4dv;
		extern PFNGLMULTITEXCOORD4FPROC												glMultiTexCoord4f;
		extern PFNGLMULTITEXCOORD4FVPROC											glMultiTexCoord4fv;
		extern PFNGLMULTITEXCOORD4IPROC												glMultiTexCoord4i;
		extern PFNGLMULTITEXCOORD4IVPROC											glMultiTexCoord4iv;
		extern PFNGLMULTITEXCOORD4SPROC												glMultiTexCoord4s;
		extern PFNGLMULTITEXCOORD4SVPROC											glMultiTexCoord4sv;
		extern PFNGLLOADTRANSPOSEMATRIXFPROC										glLoadTransposeMatrixf;
		extern PFNGLLOADTRANSPOSEMATRIXDPROC										glLoadTransposeMatrixd;
		extern PFNGLMULTTRANSPOSEMATRIXFPROC										glMultTransposeMatrixf;
		extern PFNGLMULTTRANSPOSEMATRIXDPROC										glMultTransposeMatrixd;

		// Version 1.4
		extern PFNGLBLENDFUNCSEPARATEPROC											glBlendFuncSeparate;
		extern PFNGLMULTIDRAWARRAYSPROC												glMultiDrawArrays;
		extern PFNGLMULTIDRAWELEMENTSPROC											glMultiDrawElements;
		extern PFNGLPOINTPARAMETERFPROC												glPointParameterf;
		extern PFNGLPOINTPARAMETERFVPROC											glPointParameterfv;
		extern PFNGLPOINTPARAMETERIPROC												glPointParameteri;
		extern PFNGLPOINTPARAMETERIVPROC											glPointParameteriv;
		extern PFNGLFOGCOORDFPROC													glFogCoordf;
		extern PFNGLFOGCOORDFVPROC													glFogCoordfv;
		extern PFNGLFOGCOORDDPROC													glFogCoordd;
		extern PFNGLFOGCOORDDVPROC													glFogCoorddv;
		extern PFNGLFOGCOORDPOINTERPROC												glFogCoordPointer;
		extern PFNGLSECONDARYCOLOR3BPROC											glSecondaryColor3b;
		extern PFNGLSECONDARYCOLOR3BVPROC											glSecondaryColor3bv;
		extern PFNGLSECONDARYCOLOR3DPROC											glSecondaryColor3d;
		extern PFNGLSECONDARYCOLOR3DVPROC											glSecondaryColor3dv;
		extern PFNGLSECONDARYCOLOR3FPROC											glSecondaryColor3f;
		extern PFNGLSECONDARYCOLOR3FVPROC											glSecondaryColor3fv;
		extern PFNGLSECONDARYCOLOR3IPROC											glSecondaryColor3i;
		extern PFNGLSECONDARYCOLOR3IVPROC											glSecondaryColor3iv;
		extern PFNGLSECONDARYCOLOR3SPROC											glSecondaryColor3s;
		extern PFNGLSECONDARYCOLOR3SVPROC											glSecondaryColor3sv;
		extern PFNGLSECONDARYCOLOR3UBPROC											glSecondaryColor3ub;
		extern PFNGLSECONDARYCOLOR3UBVPROC											glSecondaryColor3ubv;
		extern PFNGLSECONDARYCOLOR3UIPROC											glSecondaryColor3ui;
		extern PFNGLSECONDARYCOLOR3UIVPROC											glSecondaryColor3uiv;
		extern PFNGLSECONDARYCOLOR3USPROC											glSecondaryColor3us;
		extern PFNGLSECONDARYCOLOR3USVPROC											glSecondaryColor3usv;
		extern PFNGLSECONDARYCOLORPOINTERPROC										glSecondaryColorPointer;
		extern PFNGLWINDOWPOS2DPROC													glWindowPos2d;
		extern PFNGLWINDOWPOS2DVPROC												glWindowPos2dv;
		extern PFNGLWINDOWPOS2FPROC													glWindowPos2f;
		extern PFNGLWINDOWPOS2FVPROC												glWindowPos2fv;
		extern PFNGLWINDOWPOS2IPROC													glWindowPos2i;
		extern PFNGLWINDOWPOS2IVPROC												glWindowPos2iv;
		extern PFNGLWINDOWPOS2SPROC													glWindowPos2s;
		extern PFNGLWINDOWPOS2SVPROC												glWindowPos2sv;
		extern PFNGLWINDOWPOS3DPROC													glWindowPos3d;
		extern PFNGLWINDOWPOS3DVPROC												glWindowPos3dv;
		extern PFNGLWINDOWPOS3FPROC													glWindowPos3f;
		extern PFNGLWINDOWPOS3FVPROC												glWindowPos3fv;
		extern PFNGLWINDOWPOS3IPROC													glWindowPos3i;
		extern PFNGLWINDOWPOS3IVPROC												glWindowPos3iv;
		extern PFNGLWINDOWPOS3SPROC													glWindowPos3s;
		extern PFNGLWINDOWPOS3SVPROC												glWindowPos3sv;
		extern PFNGLBLENDCOLORPROC													glBlendColor;
		extern PFNGLBLENDEQUATIONPROC												glBlendEquation;

		// Version 1.5
		extern PFNGLGENQUERIESPROC													glGenQueries;
		extern PFNGLDELETEQUERIESPROC												glDeleteQueries;
		extern PFNGLISQUERYPROC														glIsQuery;
		extern PFNGLBEGINQUERYPROC													glBeginQuery;
		extern PFNGLENDQUERYPROC													glEndQuery;
		extern PFNGLGETQUERYIVPROC													glGetQueryiv;
		extern PFNGLGETQUERYOBJECTIVPROC											glGetQueryObjectiv;
		extern PFNGLGETQUERYOBJECTUIVPROC											glGetQueryObjectuiv;
		extern PFNGLBINDBUFFERPROC													glBindBuffer;
		extern PFNGLDELETEBUFFERSPROC												glDeleteBuffers;
		extern PFNGLGENBUFFERSPROC													glGenBuffers;
		extern PFNGLISBUFFERPROC													glIsBuffer;
		extern PFNGLBUFFERDATAPROC													glBufferData;
		extern PFNGLBUFFERSUBDATAPROC												glBufferSubData;
		extern PFNGLGETBUFFERSUBDATAPROC											glGetBufferSubData;
		extern PFNGLMAPBUFFERPROC													glMapBuffer;
		extern PFNGLUNMAPBUFFERPROC													glUnmapBuffer;
		extern PFNGLGETBUFFERPARAMETERIVPROC										glGetBufferParameteriv;
		extern PFNGLGETBUFFERPOINTERVPROC											glGetBufferPointerv;

		// Version 2.0
		extern PFNGLBLENDEQUATIONSEPARATEPROC										glBlendEquationSeparate;
		extern PFNGLDRAWBUFFERSPROC													glDrawBuffers;
		extern PFNGLSTENCILOPSEPARATEPROC											glStencilOpSeparate;
		extern PFNGLSTENCILFUNCSEPARATEPROC											glStencilFuncSeparate;
		extern PFNGLSTENCILMASKSEPARATEPROC											glStencilMaskSeparate;
		extern PFNGLATTACHSHADERPROC												glAttachShader;
		extern PFNGLBINDATTRIBLOCATIONPROC											glBindAttribLocation;
		extern PFNGLCOMPILESHADERPROC												glCompileShader;
		extern PFNGLCREATEPROGRAMPROC												glCreateProgram;
		extern PFNGLCREATESHADERPROC												glCreateShader;
		extern PFNGLDELETEPROGRAMPROC												glDeleteProgram;
		extern PFNGLDELETESHADERPROC												glDeleteShader;
		extern PFNGLDETACHSHADERPROC												glDetachShader;
		extern PFNGLDISABLEVERTEXATTRIBARRAYPROC									glDisableVertexAttribArray;
		extern PFNGLENABLEVERTEXATTRIBARRAYPROC										glEnableVertexAttribArray;
		extern PFNGLGETACTIVEATTRIBPROC												glGetActiveAttrib;
		extern PFNGLGETACTIVEUNIFORMPROC											glGetActiveUniform;
		extern PFNGLGETATTACHEDSHADERSPROC											glGetAttachedShaders;
		extern PFNGLGETATTRIBLOCATIONPROC											glGetAttribLocation;
		extern PFNGLGETPROGRAMIVPROC												glGetProgramiv;
		extern PFNGLGETPROGRAMINFOLOGPROC											glGetProgramInfoLog;
		extern PFNGLGETSHADERIVPROC													glGetShaderiv;
		extern PFNGLGETSHADERINFOLOGPROC											glGetShaderInfoLog;
		extern PFNGLGETSHADERSOURCEPROC												glGetShaderSource;
		extern PFNGLGETUNIFORMLOCATIONPROC											glGetUniformLocation;
		extern PFNGLGETUNIFORMFVPROC												glGetUniformfv;
		extern PFNGLGETUNIFORMIVPROC												glGetUniformiv;
		extern PFNGLGETVERTEXATTRIBDVPROC											glGetVertexAttribdv;
		extern PFNGLGETVERTEXATTRIBFVPROC											glGetVertexAttribfv;
		extern PFNGLGETVERTEXATTRIBIVPROC											glGetVertexAttribiv;
		extern PFNGLGETVERTEXATTRIBPOINTERVPROC										glGetVertexAttribPointerv;
		extern PFNGLISPROGRAMPROC													glIsProgram;
		extern PFNGLISSHADERPROC													glIsShader;
		extern PFNGLLINKPROGRAMPROC													glLinkProgram;
		extern PFNGLSHADERSOURCEPROC												glShaderSource;
		extern PFNGLUSEPROGRAMPROC													glUseProgram;
		extern PFNGLUNIFORM1FPROC													glUniform1f;
		extern PFNGLUNIFORM2FPROC													glUniform2f;
		extern PFNGLUNIFORM3FPROC													glUniform3f;
		extern PFNGLUNIFORM4FPROC													glUniform4f;
		extern PFNGLUNIFORM1IPROC													glUniform1i;
		extern PFNGLUNIFORM2IPROC													glUniform2i;
		extern PFNGLUNIFORM3IPROC													glUniform3i;
		extern PFNGLUNIFORM4IPROC													glUniform4i;
		extern PFNGLUNIFORM1FVPROC													glUniform1fv;
		extern PFNGLUNIFORM2FVPROC													glUniform2fv;
		extern PFNGLUNIFORM3FVPROC													glUniform3fv;
		extern PFNGLUNIFORM4FVPROC													glUniform4fv;
		extern PFNGLUNIFORM1IVPROC													glUniform1iv;
		extern PFNGLUNIFORM2IVPROC													glUniform2iv;
		extern PFNGLUNIFORM3IVPROC													glUniform3iv;
		extern PFNGLUNIFORM4IVPROC													glUniform4iv;
		extern PFNGLUNIFORMMATRIX2FVPROC											glUniformMatrix2fv;
		extern PFNGLUNIFORMMATRIX3FVPROC											glUniformMatrix3fv;
		extern PFNGLUNIFORMMATRIX4FVPROC											glUniformMatrix4fv;
		extern PFNGLVALIDATEPROGRAMPROC												glValidateProgram;
		extern PFNGLVERTEXATTRIB1DPROC												glVertexAttrib1d;
		extern PFNGLVERTEXATTRIB1DVPROC												glVertexAttrib1dv;
		extern PFNGLVERTEXATTRIB1FPROC												glVertexAttrib1f;
		extern PFNGLVERTEXATTRIB1FVPROC												glVertexAttrib1fv;
		extern PFNGLVERTEXATTRIB1SPROC												glVertexAttrib1s;
		extern PFNGLVERTEXATTRIB1SVPROC												glVertexAttrib1sv;
		extern PFNGLVERTEXATTRIB2DPROC												glVertexAttrib2d;
		extern PFNGLVERTEXATTRIB2DVPROC												glVertexAttrib2dv;
		extern PFNGLVERTEXATTRIB2FPROC												glVertexAttrib2f;
		extern PFNGLVERTEXATTRIB2FVPROC												glVertexAttrib2fv;
		extern PFNGLVERTEXATTRIB2SPROC												glVertexAttrib2s;
		extern PFNGLVERTEXATTRIB2SVPROC												glVertexAttrib2sv;
		extern PFNGLVERTEXATTRIB3DPROC												glVertexAttrib3d;
		extern PFNGLVERTEXATTRIB3DVPROC												glVertexAttrib3dv;
		extern PFNGLVERTEXATTRIB3FPROC												glVertexAttrib3f;
		extern PFNGLVERTEXATTRIB3FVPROC												glVertexAttrib3fv;
		extern PFNGLVERTEXATTRIB3SPROC												glVertexAttrib3s;
		extern PFNGLVERTEXATTRIB3SVPROC												glVertexAttrib3sv;
		extern PFNGLVERTEXATTRIB4NBVPROC											glVertexAttrib4Nbv;
		extern PFNGLVERTEXATTRIB4NIVPROC											glVertexAttrib4Niv;
		extern PFNGLVERTEXATTRIB4NSVPROC											glVertexAttrib4Nsv;
		extern PFNGLVERTEXATTRIB4NUBPROC											glVertexAttrib4Nub;
		extern PFNGLVERTEXATTRIB4NUBVPROC											glVertexAttrib4Nubv;
		extern PFNGLVERTEXATTRIB4NUIVPROC											glVertexAttrib4Nuiv;
		extern PFNGLVERTEXATTRIB4NUSVPROC											glVertexAttrib4Nusv;
		extern PFNGLVERTEXATTRIB4BVPROC												glVertexAttrib4bv;
		extern PFNGLVERTEXATTRIB4DPROC												glVertexAttrib4d;
		extern PFNGLVERTEXATTRIB4DVPROC												glVertexAttrib4dv;
		extern PFNGLVERTEXATTRIB4FPROC												glVertexAttrib4f;
		extern PFNGLVERTEXATTRIB4FVPROC												glVertexAttrib4fv;
		extern PFNGLVERTEXATTRIB4IVPROC												glVertexAttrib4iv;
		extern PFNGLVERTEXATTRIB4SPROC												glVertexAttrib4s;
		extern PFNGLVERTEXATTRIB4SVPROC												glVertexAttrib4sv;
		extern PFNGLVERTEXATTRIB4UBVPROC											glVertexAttrib4ubv;
		extern PFNGLVERTEXATTRIB4UIVPROC											glVertexAttrib4uiv;
		extern PFNGLVERTEXATTRIB4USVPROC											glVertexAttrib4usv;
		extern PFNGLVERTEXATTRIBPOINTERPROC											glVertexAttribPointer;

		// Version 2.1
		extern PFNGLUNIFORMMATRIX2X3FVPROC											glUniformMatrix2x3fv;
		extern PFNGLUNIFORMMATRIX3X2FVPROC											glUniformMatrix3x2fv;
		extern PFNGLUNIFORMMATRIX2X4FVPROC											glUniformMatrix2x4fv;
		extern PFNGLUNIFORMMATRIX4X2FVPROC											glUniformMatrix4x2fv;
		extern PFNGLUNIFORMMATRIX3X4FVPROC											glUniformMatrix3x4fv;
		extern PFNGLUNIFORMMATRIX4X3FVPROC											glUniformMatrix4x3fv;

		// Version 3.0
		extern PFNGLCOLORMASKIPROC													glColorMaski;
		extern PFNGLGETBOOLEANI_VPROC												glGetBooleani_v;
		extern PFNGLGETINTEGERI_VPROC												glGetIntegeri_v;
		extern PFNGLENABLEIPROC														glEnablei;
		extern PFNGLDISABLEIPROC													glDisablei;
		extern PFNGLISENABLEDIPROC													glIsEnabledi;
		extern PFNGLBEGINTRANSFORMFEEDBACKPROC										glBeginTransformFeedback;
		extern PFNGLENDTRANSFORMFEEDBACKPROC										glEndTransformFeedback;
		extern PFNGLBINDBUFFERRANGEPROC												glBindBufferRange;
		extern PFNGLBINDBUFFERBASEPROC												glBindBufferBase;
		extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC									glTransformFeedbackVaryings;
		extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC									glGetTransformFeedbackVarying;
		extern PFNGLCLAMPCOLORPROC													glClampColor;
		extern PFNGLBEGINCONDITIONALRENDERPROC										glBeginConditionalRender;
		extern PFNGLENDCONDITIONALRENDERPROC										glEndConditionalRender;
		extern PFNGLVERTEXATTRIBIPOINTERPROC										glVertexAttribIPointer;
		extern PFNGLGETVERTEXATTRIBIIVPROC											glGetVertexAttribIiv;
		extern PFNGLGETVERTEXATTRIBIUIVPROC											glGetVertexAttribIuiv;
		extern PFNGLVERTEXATTRIBI1IPROC												glVertexAttribI1i;
		extern PFNGLVERTEXATTRIBI2IPROC												glVertexAttribI2i;
		extern PFNGLVERTEXATTRIBI3IPROC												glVertexAttribI3i;
		extern PFNGLVERTEXATTRIBI4IPROC												glVertexAttribI4i;
		extern PFNGLVERTEXATTRIBI1UIPROC											glVertexAttribI1ui;
		extern PFNGLVERTEXATTRIBI2UIPROC											glVertexAttribI2ui;
		extern PFNGLVERTEXATTRIBI3UIPROC											glVertexAttribI3ui;
		extern PFNGLVERTEXATTRIBI4UIPROC											glVertexAttribI4ui;
		extern PFNGLVERTEXATTRIBI1IVPROC											glVertexAttribI1iv;
		extern PFNGLVERTEXATTRIBI2IVPROC											glVertexAttribI2iv;
		extern PFNGLVERTEXATTRIBI3IVPROC											glVertexAttribI3iv;
		extern PFNGLVERTEXATTRIBI4IVPROC											glVertexAttribI4iv;
		extern PFNGLVERTEXATTRIBI1UIVPROC											glVertexAttribI1uiv;
		extern PFNGLVERTEXATTRIBI2UIVPROC											glVertexAttribI2uiv;
		extern PFNGLVERTEXATTRIBI3UIVPROC											glVertexAttribI3uiv;
		extern PFNGLVERTEXATTRIBI4UIVPROC											glVertexAttribI4uiv;
		extern PFNGLVERTEXATTRIBI4BVPROC											glVertexAttribI4bv;
		extern PFNGLVERTEXATTRIBI4SVPROC											glVertexAttribI4sv;
		extern PFNGLVERTEXATTRIBI4UBVPROC											glVertexAttribI4ubv;
		extern PFNGLVERTEXATTRIBI4USVPROC											glVertexAttribI4usv;
		extern PFNGLGETUNIFORMUIVPROC												glGetUniformuiv;
		extern PFNGLBINDFRAGDATALOCATIONPROC										glBindFragDataLocation;
		extern PFNGLGETFRAGDATALOCATIONPROC											glGetFragDataLocation;
		extern PFNGLUNIFORM1UIPROC													glUniform1ui;
		extern PFNGLUNIFORM2UIPROC													glUniform2ui;
		extern PFNGLUNIFORM3UIPROC													glUniform3ui;
		extern PFNGLUNIFORM4UIPROC													glUniform4ui;
		extern PFNGLUNIFORM1UIVPROC													glUniform1uiv;
		extern PFNGLUNIFORM2UIVPROC													glUniform2uiv;
		extern PFNGLUNIFORM3UIVPROC													glUniform3uiv;
		extern PFNGLUNIFORM4UIVPROC													glUniform4uiv;
		extern PFNGLTEXPARAMETERIIVPROC												glTexParameterIiv;
		extern PFNGLTEXPARAMETERIUIVPROC											glTexParameterIuiv;
		extern PFNGLGETTEXPARAMETERIIVPROC											glGetTexParameterIiv;
		extern PFNGLGETTEXPARAMETERIUIVPROC											glGetTexParameterIuiv;
		extern PFNGLCLEARBUFFERIVPROC												glClearBufferiv;
		extern PFNGLCLEARBUFFERUIVPROC												glClearBufferuiv;
		extern PFNGLCLEARBUFFERFVPROC												glClearBufferfv;
		extern PFNGLCLEARBUFFERFIPROC												glClearBufferfi;
		extern PFNGLGETSTRINGIPROC													glGetStringi;
		extern PFNGLISRENDERBUFFERPROC												glIsRenderbuffer;
		extern PFNGLBINDRENDERBUFFERPROC											glBindRenderbuffer;
		extern PFNGLDELETERENDERBUFFERSPROC											glDeleteRenderbuffers;
		extern PFNGLGENRENDERBUFFERSPROC											glGenRenderbuffers;
		extern PFNGLRENDERBUFFERSTORAGEPROC											glRenderbufferStorage;
		extern PFNGLGETRENDERBUFFERPARAMETERIVPROC									glGetRenderbufferParameteriv;
		extern PFNGLISFRAMEBUFFERPROC												glIsFramebuffer;
		extern PFNGLBINDFRAMEBUFFERPROC												glBindFramebuffer;
		extern PFNGLDELETEFRAMEBUFFERSPROC											glDeleteFramebuffers;
		extern PFNGLGENFRAMEBUFFERSPROC												glGenFramebuffers;
		extern PFNGLCHECKFRAMEBUFFERSTATUSPROC										glCheckFramebufferStatus;
		extern PFNGLFRAMEBUFFERTEXTURE1DPROC										glFramebufferTexture1D;
		extern PFNGLFRAMEBUFFERTEXTURE2DPROC										glFramebufferTexture2D;
		extern PFNGLFRAMEBUFFERTEXTURE3DPROC										glFramebufferTexture3D;
		extern PFNGLFRAMEBUFFERRENDERBUFFERPROC										glFramebufferRenderbuffer;
		extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC							glGetFramebufferAttachmentParameteriv;
		extern PFNGLGENERATEMIPMAPPROC												glGenerateMipmap;
		extern PFNGLBLITFRAMEBUFFERPROC												glBlitFramebuffer;
		extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC								glRenderbufferStorageMultisample;
		extern PFNGLFRAMEBUFFERTEXTURELAYERPROC										glFramebufferTextureLayer;
		extern PFNGLMAPBUFFERRANGEPROC												glMapBufferRange;
		extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC										glFlushMappedBufferRange;
		extern PFNGLBINDVERTEXARRAYPROC												glBindVertexArray;
		extern PFNGLDELETEVERTEXARRAYSPROC											glDeleteVertexArrays;
		extern PFNGLGENVERTEXARRAYSPROC												glGenVertexArrays;
		extern PFNGLISVERTEXARRAYPROC												glIsVertexArray;

		// Version 3.1
		extern PFNGLDRAWARRAYSINSTANCEDPROC											glDrawArraysInstanced;
		extern PFNGLDRAWELEMENTSINSTANCEDPROC										glDrawElementsInstanced;
		extern PFNGLTEXBUFFERPROC													glTexBuffer;
		extern PFNGLPRIMITIVERESTARTINDEXPROC										glPrimitiveRestartIndex;
		extern PFNGLCOPYBUFFERSUBDATAPROC											glCopyBufferSubData;
		extern PFNGLGETUNIFORMINDICESPROC											glGetUniformIndices;
		extern PFNGLGETACTIVEUNIFORMSIVPROC											glGetActiveUniformsiv;
		extern PFNGLGETACTIVEUNIFORMNAMEPROC										glGetActiveUniformName;
		extern PFNGLGETUNIFORMBLOCKINDEXPROC										glGetUniformBlockIndex;
		extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC										glGetActiveUniformBlockiv;
		extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC									glGetActiveUniformBlockName;
		extern PFNGLUNIFORMBLOCKBINDINGPROC											glUniformBlockBinding;

		// Version 3.2
		extern PFNGLDRAWELEMENTSBASEVERTEXPROC										glDrawElementsBaseVertex;
		extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC									glDrawRangeElementsBaseVertex;
		extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC								glDrawElementsInstancedBaseVertex;
		extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC									glMultiDrawElementsBaseVertex;
		extern PFNGLPROVOKINGVERTEXPROC												glProvokingVertex;
		extern PFNGLFENCESYNCPROC													glFenceSync;
		extern PFNGLISSYNCPROC														glIsSync;
		extern PFNGLDELETESYNCPROC													glDeleteSync;
		extern PFNGLCLIENTWAITSYNCPROC												glClientWaitSync;
		extern PFNGLWAITSYNCPROC													glWaitSync;
		extern PFNGLGETINTEGER64VPROC												glGetInteger64v;
		extern PFNGLGETSYNCIVPROC													glGetSynciv;
		extern PFNGLGETINTEGER64I_VPROC												glGetInteger64i_v;
		extern PFNGLGETBUFFERPARAMETERI64VPROC										glGetBufferParameteri64v;
		extern PFNGLFRAMEBUFFERTEXTUREPROC											glFramebufferTexture;
		extern PFNGLTEXIMAGE2DMULTISAMPLEPROC										glTexImage2DMultisample;
		extern PFNGLTEXIMAGE3DMULTISAMPLEPROC										glTexImage3DMultisample;
		extern PFNGLGETMULTISAMPLEFVPROC											glGetMultisamplefv;
		extern PFNGLSAMPLEMASKIPROC													glSampleMaski;

		// Version 3.3
		extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC									glBindFragDataLocationIndexed;
		extern PFNGLGETFRAGDATAINDEXPROC											glGetFragDataIndex;
		extern PFNGLGENSAMPLERSPROC													glGenSamplers;
		extern PFNGLDELETESAMPLERSPROC												glDeleteSamplers;
		extern PFNGLISSAMPLERPROC													glIsSampler;
		extern PFNGLBINDSAMPLERPROC													glBindSampler;
		extern PFNGLSAMPLERPARAMETERIPROC											glSamplerParameteri;
		extern PFNGLSAMPLERPARAMETERIVPROC											glSamplerParameteriv;
		extern PFNGLSAMPLERPARAMETERFPROC											glSamplerParameterf;
		extern PFNGLSAMPLERPARAMETERFVPROC											glSamplerParameterfv;
		extern PFNGLSAMPLERPARAMETERIIVPROC											glSamplerParameterIiv;
		extern PFNGLSAMPLERPARAMETERIUIVPROC										glSamplerParameterIuiv;
		extern PFNGLGETSAMPLERPARAMETERIVPROC										glGetSamplerParameteriv;
		extern PFNGLGETSAMPLERPARAMETERIIVPROC										glGetSamplerParameterIiv;
		extern PFNGLGETSAMPLERPARAMETERFVPROC										glGetSamplerParameterfv;
		extern PFNGLGETSAMPLERPARAMETERIUIVPROC										glGetSamplerParameterIuiv;
		extern PFNGLQUERYCOUNTERPROC												glQueryCounter;
		extern PFNGLGETQUERYOBJECTI64VPROC											glGetQueryObjecti64v;
		extern PFNGLGETQUERYOBJECTUI64VPROC											glGetQueryObjectui64v;
		extern PFNGLVERTEXATTRIBDIVISORPROC											glVertexAttribDivisor;
		extern PFNGLVERTEXATTRIBP1UIPROC											glVertexAttribP1ui;
		extern PFNGLVERTEXATTRIBP1UIVPROC											glVertexAttribP1uiv;
		extern PFNGLVERTEXATTRIBP2UIPROC											glVertexAttribP2ui;
		extern PFNGLVERTEXATTRIBP2UIVPROC											glVertexAttribP2uiv;
		extern PFNGLVERTEXATTRIBP3UIPROC											glVertexAttribP3ui;
		extern PFNGLVERTEXATTRIBP3UIVPROC											glVertexAttribP3uiv;
		extern PFNGLVERTEXATTRIBP4UIPROC											glVertexAttribP4ui;
		extern PFNGLVERTEXATTRIBP4UIVPROC											glVertexAttribP4uiv;
		extern PFNGLVERTEXP2UIPROC													glVertexP2ui;
		extern PFNGLVERTEXP2UIVPROC													glVertexP2uiv;
		extern PFNGLVERTEXP3UIPROC													glVertexP3ui;
		extern PFNGLVERTEXP3UIVPROC													glVertexP3uiv;
		extern PFNGLVERTEXP4UIPROC													glVertexP4ui;
		extern PFNGLVERTEXP4UIVPROC													glVertexP4uiv;
		extern PFNGLTEXCOORDP1UIPROC												glTexCoordP1ui;
		extern PFNGLTEXCOORDP1UIVPROC												glTexCoordP1uiv;
		extern PFNGLTEXCOORDP2UIPROC												glTexCoordP2ui;
		extern PFNGLTEXCOORDP2UIVPROC												glTexCoordP2uiv;
		extern PFNGLTEXCOORDP3UIPROC												glTexCoordP3ui;
		extern PFNGLTEXCOORDP3UIVPROC												glTexCoordP3uiv;
		extern PFNGLTEXCOORDP4UIPROC												glTexCoordP4ui;
		extern PFNGLTEXCOORDP4UIVPROC												glTexCoordP4uiv;
		extern PFNGLMULTITEXCOORDP1UIPROC											glMultiTexCoordP1ui;
		extern PFNGLMULTITEXCOORDP1UIVPROC											glMultiTexCoordP1uiv;
		extern PFNGLMULTITEXCOORDP2UIPROC											glMultiTexCoordP2ui;
		extern PFNGLMULTITEXCOORDP2UIVPROC											glMultiTexCoordP2uiv;
		extern PFNGLMULTITEXCOORDP3UIPROC											glMultiTexCoordP3ui;
		extern PFNGLMULTITEXCOORDP3UIVPROC											glMultiTexCoordP3uiv;
		extern PFNGLMULTITEXCOORDP4UIPROC											glMultiTexCoordP4ui;
		extern PFNGLMULTITEXCOORDP4UIVPROC											glMultiTexCoordP4uiv;
		extern PFNGLNORMALP3UIPROC													glNormalP3ui;
		extern PFNGLNORMALP3UIVPROC													glNormalP3uiv;
		extern PFNGLCOLORP3UIPROC													glColorP3ui;
		extern PFNGLCOLORP3UIVPROC													glColorP3uiv;
		extern PFNGLCOLORP4UIPROC													glColorP4ui;
		extern PFNGLCOLORP4UIVPROC													glColorP4uiv;
		extern PFNGLSECONDARYCOLORP3UIPROC											glSecondaryColorP3ui;
		extern PFNGLSECONDARYCOLORP3UIVPROC											glSecondaryColorP3uiv;


		inline void Init();
	}
	namespace OpenGL // functions wrappers
	{
		// types
		class BufferHandle
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline BufferHandle() = default;
			inline explicit BufferHandle(const Value& value_):
				value(value_)
			{
			}
			inline BufferHandle(const BufferHandle&) = default;
			inline ~BufferHandle() = default;
		public:
			inline BufferHandle& operator = (const BufferHandle&) = default;
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
		class VertexArrayHandle
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline VertexArrayHandle() = default;
			inline explicit VertexArrayHandle(const Value& value_):
				value(value_)
			{
			}
			inline VertexArrayHandle(const VertexArrayHandle&) = default;
			inline ~VertexArrayHandle() = default;
		public:
			inline VertexArrayHandle& operator = (const VertexArrayHandle&) = default;
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
		class ProgramHandle
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline ProgramHandle() = default;
			inline explicit ProgramHandle(const Value& value_):
				value(value_)
			{
			}
			inline ProgramHandle(const ProgramHandle&) = default;
			inline ~ProgramHandle() = default;
		public:
			inline ProgramHandle& operator = (const ProgramHandle&) = default;
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
		class ShaderHandle
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline ShaderHandle() = default;
			inline explicit ShaderHandle(const Value& value_):
				value(value_)
			{
			}
			inline ShaderHandle(const ShaderHandle&) = default;
			inline ~ShaderHandle() = default;
		public:
			inline ShaderHandle& operator = (const ShaderHandle&) = default;
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
		class AttributeLocation
		{
		public:
			using Value = GLint;
		protected:
			Value value;
		public:
			inline AttributeLocation() = default;
			inline explicit AttributeLocation(const Value& value_):
				value(value_)
			{
			}
			inline AttributeLocation(const AttributeLocation&) = default;
			inline ~AttributeLocation() = default;
		public:
			inline AttributeLocation& operator = (const AttributeLocation&) = default;
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
		class UniformLocation
		{
		public:
			using Value = GLint;
		protected:
			Value value;
		public:
			inline UniformLocation() = default;
			inline explicit UniformLocation(const Value& value_):
				value(value_)
			{
			}
			inline UniformLocation(const UniformLocation&) = default;
			inline ~UniformLocation() = default;
		public:
			inline UniformLocation& operator = (const UniformLocation&) = default;
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
		class UniformBlockIndex
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline UniformBlockIndex() = default;
			inline explicit UniformBlockIndex(const Value& value_):
				value(value_)
			{
			}
			inline UniformBlockIndex(const UniformBlockIndex&) = default;
			inline ~UniformBlockIndex() = default;
		public:
			inline UniformBlockIndex& operator = (const UniformBlockIndex&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator bool() const
			{
				return value != GL_INVALID_INDEX;
			}
		};
		class UniformBlockBindingPoint
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline UniformBlockBindingPoint() = default;
			inline explicit UniformBlockBindingPoint(const Value& value_):
				value(value_)
			{
			}
			inline UniformBlockBindingPoint(const UniformBlockBindingPoint&) = default;
			inline ~UniformBlockBindingPoint() = default;
		public:
			inline UniformBlockBindingPoint& operator = (const UniformBlockBindingPoint&) = default;
		public:
			inline operator Value() const
			{
				return value;
			}
			inline operator bool() const
			{
				return value != GL_INVALID_INDEX;
			}
		};
		class TextureHandle
		{
		public:
			using Value = GLuint;
		protected:
			Value value;
		public:
			inline TextureHandle() = default;
			inline explicit TextureHandle(const Value& value_):
				value(value_)
			{
			}
			inline TextureHandle(const TextureHandle&) = default;
			inline ~TextureHandle() = default;
		public:
			inline TextureHandle& operator = (const TextureHandle&) = default;
		public:
			inline operator const Value&() const
			{
				return value;
			}
			inline operator Value&()
			{
				return value;
			}
		};

		
		// enums
		enum class BufferType: GLenum
		{
			Array				= GL_ARRAY_BUFFER,
			ElementArray		= GL_ELEMENT_ARRAY_BUFFER,
			Uniform				= GL_UNIFORM_BUFFER,
		};
		enum class BufferUsage: GLenum
		{
			Static				= GL_STATIC_DRAW,
			Dynamic				= GL_DYNAMIC_DRAW,
			Stream				= GL_STREAM_DRAW,
		};
		enum class TextureType: GLenum
		{
			D1					= GL_TEXTURE_1D,
			D1Array				= GL_TEXTURE_1D_ARRAY,
			D2					= GL_TEXTURE_2D,
			D2Array				= GL_TEXTURE_2D_ARRAY,
			D2Multisample		= GL_TEXTURE_2D_MULTISAMPLE,
			D2MultisampleArray	= GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
			D3					= GL_TEXTURE_3D,
			Cubemap				= GL_TEXTURE_CUBE_MAP,
			CubemapArray		= GL_TEXTURE_CUBE_MAP_ARRAY,
			Rectangle			= GL_TEXTURE_RECTANGLE,
		};
		enum class CubemapFace
		{
			NegativeX			= GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			PositiveX			= GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			NegativeY			= GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			PositiveY			= GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			NegativeZ			= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			PositiveZ			= GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		};
		enum class TextureParameter: GLenum
		{
			DepthStencilTextureMode		= GL_DEPTH_STENCIL_TEXTURE_MODE,
			TextureBaseLevel			= GL_TEXTURE_BASE_LEVEL,
			TextureCompareFunc			= GL_TEXTURE_COMPARE_FUNC,
			TextureCompareMode			= GL_TEXTURE_COMPARE_MODE,
			TextureLodBias				= GL_TEXTURE_LOD_BIAS,
			TextureMinFilter			= GL_TEXTURE_MIN_FILTER,
			TextureMagFilter			= GL_TEXTURE_MAG_FILTER,
			TextureMinLod				= GL_TEXTURE_MIN_LOD,
			TextureMaxLod				= GL_TEXTURE_MAX_LOD,
			TextureMaxLevel				= GL_TEXTURE_MAX_LEVEL,
			TextureSwizzleR				= GL_TEXTURE_SWIZZLE_R,
			TextureSwizzleG				= GL_TEXTURE_SWIZZLE_G,
			TextureSwizzleB				= GL_TEXTURE_SWIZZLE_B,
			TextureSwizzleA				= GL_TEXTURE_SWIZZLE_A,
			TextureWrapS				= GL_TEXTURE_WRAP_S,
			TextureWrapT				= GL_TEXTURE_WRAP_T,
			TextureWrapR				= GL_TEXTURE_WRAP_R,
		};
		enum class TextureWrap: GLint
		{
			ClampToEdge					= GL_CLAMP_TO_EDGE,
			ClampToBorder				= GL_CLAMP_TO_BORDER,
			MirroredRepeat				= GL_MIRRORED_REPEAT,
			Repeat						= GL_REPEAT,
			MirrorClampToEdge			= GL_MIRROR_CLAMP_TO_EDGE,
		};
		enum class TextureMinificationFilter: GLint
		{
			Nearest					= GL_NEAREST,
			Linear					= GL_LINEAR,
			NearestMipmapNearest	= GL_NEAREST_MIPMAP_NEAREST,
			LinearMipmapNearest		= GL_LINEAR_MIPMAP_NEAREST,
			NearestMipmapLinear		= GL_NEAREST_MIPMAP_LINEAR,
			LinearMipmapLinear		= GL_LINEAR_MIPMAP_LINEAR,
		};
		enum class TextureMagnificationFilter: GLint
		{
			Nearest				= GL_NEAREST,
			Linear				= GL_LINEAR,
		};
		enum class TextureInternalFormat: GLint
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
		enum class TextureFormat: GLenum
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
		enum class TextureDataType: GLenum
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
		enum class ProgramParameter: GLenum
		{
			LinkStatus			= GL_LINK_STATUS,
			ValidateStatus		= GL_VALIDATE_STATUS,
			InfoLogLength		= GL_INFO_LOG_LENGTH,
		};
		enum class ShaderType: GLenum
		{
			Vertex				= GL_VERTEX_SHADER,
			Geometry			= GL_GEOMETRY_SHADER,
			Fragment			= GL_FRAGMENT_SHADER,
		};
		enum class ShaderParameter: GLenum
		{
			CompilseStatus		= GL_COMPILE_STATUS,
			InfoLogLength		= GL_INFO_LOG_LENGTH,
		};
		enum class ComponentType
		{
			Float			= GL_FLOAT,
		};


		// functions
		inline Size GetMaxUniformBlockSize()
		{
			GLint value;

			glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &value);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			return value;
		}

		inline BufferHandle GenBuffer()
		{
			BufferHandle bufferHandle;

			glGenBuffers(1, static_cast<GLuint*>(bufferHandle));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			return bufferHandle;
		}
		inline void DeleteBuffer(const BufferHandle& bufferHandle_)
		{
			glDeleteBuffers(1, static_cast<const GLuint*>(bufferHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BindBuffer(const BufferType& bufferType_, const BufferHandle& bufferHandle_)
		{
			glBindBuffer(static_cast<GLenum>(bufferType_), static_cast<GLuint>(bufferHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BindBuffer(const BufferType& bufferType_, const Null&)
		{
			glBindBuffer(static_cast<GLenum>(bufferType_), 0);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BufferData(const BufferType& bufferType_, const Size& dataSize_, const Memory<const void>& data_, const BufferUsage& bufferUsage_)
		{
			glBufferData(static_cast<GLenum>(bufferType_), dataSize_, data_, static_cast<GLenum>(bufferUsage_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BufferSubData(const BufferType& bufferType_, const Size& offset_, const Size& dataSize_, const Memory<const void>& data_)
		{
			glBufferSubData(static_cast<GLenum>(bufferType_), offset_, dataSize_, data_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BindBufferBase(const BufferType& bufferType_, const UniformBlockIndex& uniformBlockIndex_, const BufferHandle& bufferHandle_)
		{
			glBindBufferBase(static_cast<GLenum>(bufferType_), static_cast<GLuint>(uniformBlockIndex_), static_cast<GLuint>(bufferHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}

		inline VertexArrayHandle GenVertexArray()
		{
			VertexArrayHandle vertexArrayHandle;

			glGenVertexArrays(1, static_cast<GLuint*>(vertexArrayHandle));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			return vertexArrayHandle;
		}
		inline void BindVertexArray(const VertexArrayHandle& vertexArrayHandle_)
		{
			glBindVertexArray(static_cast<GLuint>(vertexArrayHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BindVertexArray(const Null&)
		{
			glBindVertexArray(0);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void DeleteVertexArray(const VertexArrayHandle& vertexArrayHandle_)
		{
			glDeleteVertexArrays(1, static_cast<const GLuint*>(vertexArrayHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}

		inline TextureHandle GenTexture()
		{
			TextureHandle textureHandle;

			glGenTextures(1, &static_cast<TextureHandle::Value&>(textureHandle));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
			
			return textureHandle;
		}
		inline void DeleteTexture(const TextureHandle& textureHandle_)
		{
			glDeleteTextures(1, &static_cast<const TextureHandle::Value&>(textureHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void ActiveTexture(const Size& index_)
		{
			glActiveTexture(GL_TEXTURE0 + index_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BindTexture(const TextureType& textureType_, const TextureHandle& textureHandle_)
		{
			glBindTexture(static_cast<GLenum>(textureType_), textureHandle_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void BindTexture(const TextureType& textureType_, const Null&)
		{
			glBindTexture(static_cast<GLenum>(textureType_), 0);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void TextureParameterWrap(const TextureType& textureType_, const TextureWrap& textureWrapS_, const TextureWrap& textureWrapT_, const TextureWrap& textureWrapR_)
		{
			glTexParameteri(static_cast<GLenum>(textureType_), static_cast<GLenum>(TextureParameter::TextureWrapS), static_cast<GLint>(textureWrapS_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			glTexParameteri(static_cast<GLenum>(textureType_), static_cast<GLenum>(TextureParameter::TextureWrapT), static_cast<GLint>(textureWrapT_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			glTexParameteri(static_cast<GLenum>(textureType_), static_cast<GLenum>(TextureParameter::TextureWrapR), static_cast<GLint>(textureWrapR_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void TextureParameterFilter(const TextureType& textureType_, const TextureMinificationFilter& textureMinificationFilter_, const TextureMagnificationFilter& textureMagnificationFilter_)
		{
			glTexParameteri(static_cast<GLenum>(textureType_), static_cast<GLenum>(TextureParameter::TextureMinFilter), static_cast<GLint>(textureMinificationFilter_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			glTexParameteri(static_cast<GLenum>(textureType_), static_cast<GLenum>(TextureParameter::TextureMagFilter), static_cast<GLint>(textureMagnificationFilter_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void TextureImage(const Size& level_, const TextureInternalFormat& textureInternalFormat_, const Size2& size_, const TextureFormat& textureFormat_, const TextureDataType& textureDataType_, const Memory<const void>& data_ = nullptr) // TexImage2D
		{
			glTexImage2D(static_cast<GLenum>(TextureType::D2), level_, static_cast<GLint>(textureInternalFormat_), size_.x, size_.y, 0, static_cast<GLenum>(textureFormat_), static_cast<GLenum>(textureDataType_), data_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void TextureImage(const CubemapFace& face_, const Size& level_, const TextureInternalFormat& textureInternalFormat_, const Size& size_, const TextureFormat& textureFormat_, const TextureDataType& textureDataType_, const Memory<const void>& data_ = nullptr) // TexImage2D + Cubemap
		{
			glTexImage2D(static_cast<GLenum>(face_), level_, static_cast<GLint>(textureInternalFormat_), size_, size_, 0, static_cast<GLenum>(textureFormat_), static_cast<GLenum>(textureDataType_), data_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}

		inline TextureInternalFormat GetInternalFormat(const StrongPointer<Image>& image_)
		{
			if (DynamicCast<Image2DX<Pixel<UInt8>>>(image_) || DynamicCast<ImageCubeX<Pixel<UInt8>>>(image_))
			{
				return TextureInternalFormat::R8;
			}
			else if (DynamicCast<Image2DX<Pixel<UInt8, UInt8, UInt8>>>(image_) || DynamicCast<ImageCubeX<Pixel<UInt8, UInt8, UInt8>>>(image_))
			{
				return TextureInternalFormat::RGB8;
			}
			else if (DynamicCast<Image2DX<Pixel<UInt8, UInt8, UInt8, UInt8>>>(image_) || DynamicCast<ImageCubeX<Pixel<UInt8, UInt8, UInt8, UInt8>>>(image_))
			{
				return TextureInternalFormat::RGBA8;
			}
			else if (DynamicCast<Image2DX<Pixel<UInt16>>>(image_) || DynamicCast<ImageCubeX<Pixel<UInt16>>>(image_))
			{
				return TextureInternalFormat::R16;
			}
			else if (DynamicCast<Image2DX<Pixel<UInt16, UInt16, UInt16>>>(image_) || DynamicCast<ImageCubeX<Pixel<UInt16, UInt16, UInt16>>>(image_))
			{
				return TextureInternalFormat::RGB16;
			}
			else if (DynamicCast<Image2DX<Pixel<UInt16, UInt16, UInt16, UInt16>>>(image_) || DynamicCast<ImageCubeX<Pixel<UInt16, UInt16, UInt16, UInt16>>>(image_))
			{
				return TextureInternalFormat::RGBA16;
			}

			throw Exception();
		};
		inline TextureFormat GetFormat(const StrongPointer<Image>& image_)
		{
			if (
				DynamicCast<Image2DX<Pixel<UInt8>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt16>>>(image_)
			) {
				return TextureFormat::R;
			}
			else if (
				DynamicCast<Image2DX<Pixel<UInt8, UInt8, UInt8>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt16, UInt16, UInt16>>>(image_)
			) {
				return TextureFormat::RGB;
			}
			else if (
				DynamicCast<Image2DX<Pixel<UInt8, UInt8, UInt8, UInt8>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt16, UInt16, UInt16, UInt16>>>(image_) ||
				DynamicCast<ImageCubeX<Pixel<UInt8, UInt8, UInt8, UInt8>>>(image_) ||
				DynamicCast<ImageCubeX<Pixel<UInt16, UInt16, UInt16, UInt16>>>(image_)
			) {
				return TextureFormat::RGBA;
			}

			throw Exception();
		};
		inline TextureDataType GetDataType(const StrongPointer<Image>& image_)
		{
			if (
				DynamicCast<Image2DX<Pixel<UInt8>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt8, UInt8>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt8, UInt8, UInt8>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt8, UInt8, UInt8, UInt8>>>(image_) ||
				DynamicCast<ImageCubeX<Pixel<UInt8, UInt8, UInt8, UInt8>>>(image_)
			) {
				return TextureDataType::UInt8;
			}
			else if (
				DynamicCast<Image2DX<Pixel<UInt16>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt16, UInt16>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt16, UInt16, UInt16>>>(image_) ||
				DynamicCast<Image2DX<Pixel<UInt16, UInt16, UInt16, UInt16>>>(image_)
			) {
				return TextureDataType::UInt16;
			}

			throw Exception();
		};

		inline ProgramHandle CreateProgram()
		{
			auto value = glCreateProgram();

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
			auto programHandle = ProgramHandle(value);

			return programHandle;
		}
		inline void UseProgram(const ProgramHandle& programHandle_)
		{
			glUseProgram(static_cast<GLuint>(programHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void UseProgram(const Null&)
		{
			glUseProgram(0);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void LinkProgram(const ProgramHandle& programHandle_)
		{
			glLinkProgram(static_cast<GLuint>(programHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void ValidateProgram(const ProgramHandle& programHandle_)
		{
			glValidateProgram(static_cast<GLuint>(programHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void DeleteProgram(const ProgramHandle& programHandle_)
		{
			glDeleteProgram(static_cast<GLuint>(programHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}

		inline bool GetProgramLinkStatus(const ProgramHandle& programHandle_)
		{
			GLint result;

			glGetProgramiv(static_cast<GLuint>(programHandle_), static_cast<GLenum>(ProgramParameter::LinkStatus), &result);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

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
		inline bool GetProgramValidateStatus(const ProgramHandle& programHandle_)
		{
			GLint result;

			glGetProgramiv(static_cast<GLuint>(programHandle_), static_cast<GLenum>(ProgramParameter::ValidateStatus), &result);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

#if __GREAT_V_ENGINE_2__DEBUG__
			return
				result == GL_TRUE ? true :
				result == GL_FALSE ? false :
				throw Exception("Unexpected \"glGetProgramiv\" + \"GL_VALIDATE_STATUS\" result: " + ToString(static_cast<Size>(result)));
#else
			return result == GL_TRUE
				? true
				: false;
#endif
		}
		inline Size GetProgramInfoLogLength(const ProgramHandle& programHandle_)
		{
			GLint result;

			glGetProgramiv(static_cast<GLuint>(programHandle_), static_cast<GLenum>(ProgramParameter::InfoLogLength), &result);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

#if __GREAT_V_ENGINE_2__DEBUG__
			return result >= 0
				? static_cast<Size>(result)
				: throw Exception("Unexpected \"glGetProgramiv\" + \"GL_INFO_LOG_LENGTH\" result: " + ToString(static_cast<Size>(result)));
#else
			return static_cast<Size>(result);
#endif
		}
		inline String GetProgramInfoLog(const ProgramHandle& programHandle_)
		{
			auto length = GetProgramInfoLogLength(programHandle_);

			Vector<char> buffer(length);

			glGetProgramInfoLog(static_cast<GLuint>(programHandle_), buffer.size(), nullptr, buffer.data());

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			auto text = String(buffer.begin(), buffer.end());

			return Move(text);
		}

		inline AttributeLocation GetAttributeLocation(const ProgramHandle& programHandle_, const String& attributeName_)
		{
			auto value = glGetAttribLocation(static_cast<GLuint>(programHandle_), attributeName_.c_str());

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			auto attributeLocation = AttributeLocation(value);

			return attributeLocation;
		}
		inline void VertexAttribPointer(const AttributeLocation& attributeLocation_, const Size& componentsCount_, const ComponentType& componentsType_, const bool& isNormalized_, const Size& stride_, const Size& offset_)
		{
			glVertexAttribPointer(static_cast<AttributeLocation::Value>(attributeLocation_), componentsCount_, static_cast<GLenum>(componentsType_), isNormalized_ ? GL_TRUE : GL_FALSE, stride_, reinterpret_cast<GLvoid*>(offset_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void EnableVertexAttribArray(const AttributeLocation& attributeLocation_)
		{
			glEnableVertexAttribArray(static_cast<AttributeLocation::Value>(attributeLocation_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void DisableVertexAttribArray(const AttributeLocation& attributeLocation_)
		{
			glDisableVertexAttribArray(static_cast<AttributeLocation::Value>(attributeLocation_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline UniformLocation GetUniformLocation(const ProgramHandle& programHandle_, const String& uniformName_)
		{
			auto value = glGetUniformLocation(static_cast<GLuint>(programHandle_), uniformName_.c_str());

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			auto uniformLocation = UniformLocation(value);

			return uniformLocation;
		}
		inline void SetUniform(const UniformLocation& uniformLocation_, const UInt32& value_)
		{
			glUniform1ui(uniformLocation_, value_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void SetUniform(const UniformLocation& uniformLocation_, const SInt32& value_)
		{
			glUniform1i(uniformLocation_, value_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void SetUniform(const UniformLocation& uniformLocation_, const Float32& value_)
		{
			glUniform1f(uniformLocation_, value_);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void SetUniform(const UniformLocation& uniformLocation_, const Mat4& mat_, const bool& isTransposed_ = false)
		{
			glUniformMatrix4fv(uniformLocation_, 1, isTransposed_ ? GL_TRUE : GL_FALSE, reinterpret_cast<const GLfloat*>(&mat_));

#if __GREAT_V_ENGINE_2__DEBUG__
				Error::Check();
#endif
		}
		inline void SetUniform(const UniformLocation& uniformLocation_, const Mat3& mat_, const bool& isTransposed_ = false)
		{
			glUniformMatrix3fv(uniformLocation_, 1, isTransposed_ ? GL_TRUE : GL_FALSE, reinterpret_cast<const GLfloat*>(&mat_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline UniformBlockIndex GetUniformBlockIndex(const ProgramHandle& programHandle_, const String& uniformBlockName_)
		{
			auto value = glGetUniformBlockIndex(static_cast<GLuint>(programHandle_), uniformBlockName_.c_str());

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			auto uniformBlockIndex = UniformBlockIndex(value);

			return uniformBlockIndex;
		}
		inline void UniformBlockBinding(const ProgramHandle& programHandle_, const UniformBlockIndex& uniformBlockIndex_, const UniformBlockBindingPoint& uniformBlockBindingPoint_)
		{
			glUniformBlockBinding(static_cast<GLuint>(programHandle_), static_cast<GLuint>(uniformBlockIndex_), static_cast<GLuint>(uniformBlockBindingPoint_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}

		inline ShaderHandle CreateShader(const ShaderType& shaderType_)
		{
			auto value = glCreateShader(static_cast<GLenum>(shaderType_));
			
#if __GREAT_V_ENGINE_2__DEBUG__
			if (value == 0)
			{
				throw Exception("Error while creating shader.");
			}

			Error::Check();
#endif
			
			auto shaderHandle = ShaderHandle(value);

			return shaderHandle;
		}
		inline void ShaderSource(const ShaderHandle& shaderHandle_, const Vector<const String>& sources_)
		{
			Vector<const GLchar*const> datas(sources_.size());
			Vector<GLint> sizes(sources_.size());
			
			for (Size i = 0; i < sizes.size(); ++i)
			{
				datas[i] = sources_[i].data();
				sizes[i] = sources_[i].length();
			}

			glShaderSource(static_cast<GLuint>(shaderHandle_), sources_.size(), datas.data(), sizes.data());

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void CompileShader(const ShaderHandle& shaderHandle_)
		{
			glCompileShader(static_cast<GLuint>(shaderHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void AttachShader(const ProgramHandle& programHandle_, const ShaderHandle& shaderHandle_)
		{
			glAttachShader(static_cast<GLuint>(programHandle_), static_cast<GLuint>(shaderHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void DetachShader(const ProgramHandle& programHandle_, const ShaderHandle& shaderHandle_)
		{
			glDetachShader(static_cast<GLuint>(programHandle_), static_cast<GLuint>(shaderHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}
		inline void DeleteShader(const ShaderHandle& shaderHandle_)
		{
			glDeleteShader(static_cast<GLuint>(shaderHandle_));

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif
		}

		inline bool GetShaderCompileStatus(const ShaderHandle& shaderHandle_)
		{
			GLint result;

			glGetShaderiv(static_cast<GLuint>(shaderHandle_), static_cast<GLenum>(ShaderParameter::CompilseStatus), &result);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

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
		inline Size GetShaderInfoLogLength(const ShaderHandle& shaderHandle_)
		{
			GLint result;

			glGetShaderiv(static_cast<GLuint>(shaderHandle_), static_cast<GLenum>(ShaderParameter::InfoLogLength), &result);

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

#if __GREAT_V_ENGINE_2__DEBUG__
			return result >= 0
				? static_cast<Size>(result)
				: throw Exception("Unexpected \"glGetShaderiv\" + \"GL_INFO_LOG_LENGTH\" result: " + ToString(static_cast<Size>(result)));
#else
			return static_cast<Size>(result);
#endif
		}
		inline String GetShaderInfoLog(const ShaderHandle& shaderHandle_)
		{
			auto length = GetShaderInfoLogLength(shaderHandle_);

			Vector<char> buffer(length);

			glGetShaderInfoLog(static_cast<GLuint>(shaderHandle_), buffer.size(), nullptr, buffer.data());

#if __GREAT_V_ENGINE_2__DEBUG__
			Error::Check();
#endif

			auto text = String(buffer.begin(), buffer.end());

			return Move(text);
		}
	}
}


#pragma region GreatVEngine2

#pragma region OpenGL

void GreatVEngine2::OpenGL::Init()
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

	// Obtain functions
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(wglCreateContextAttribsARB);

	// Version 1.2
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDrawRangeElements);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glTexImage3D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glTexSubImage3D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCopyTexSubImage3D);

	// Version 1.3
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glActiveTexture);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSampleCoverage);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompressedTexImage3D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompressedTexImage2D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompressedTexImage1D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompressedTexSubImage3D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompressedTexSubImage2D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompressedTexSubImage1D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetCompressedTexImage);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glClientActiveTexture);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord1sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord2sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord3sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiTexCoord4sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glLoadTransposeMatrixf);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glLoadTransposeMatrixd);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultTransposeMatrixf);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultTransposeMatrixd);

	// Version 1.4
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBlendFuncSeparate);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiDrawArrays);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMultiDrawElements);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glPointParameterf);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glPointParameterfv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glPointParameteri);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glPointParameteriv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFogCoordf);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFogCoordfv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFogCoordd);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFogCoorddv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFogCoordPointer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3b);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3bv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3ub);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3ubv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3us);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColor3usv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glSecondaryColorPointer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos2sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glWindowPos3sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBlendColor);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBlendEquation);

	// Version 1.5
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGenQueries);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteQueries);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsQuery);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBeginQuery);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glEndQuery);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetQueryiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetQueryObjectiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetQueryObjectuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindBuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteBuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGenBuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsBuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBufferData);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBufferSubData);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetBufferSubData);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMapBuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUnmapBuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetBufferParameteriv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetBufferPointerv);

	// Version 2.0
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBlendEquationSeparate);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDrawBuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glStencilOpSeparate);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glStencilFuncSeparate);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glStencilMaskSeparate);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glAttachShader);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindAttribLocation);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCompileShader);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCreateProgram);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCreateShader);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteProgram);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteShader);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDetachShader);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDisableVertexAttribArray);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glEnableVertexAttribArray);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetActiveAttrib);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetActiveUniform);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetAttachedShaders);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetAttribLocation);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetProgramiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetProgramInfoLog);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetShaderiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetShaderInfoLog);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetShaderSource);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetUniformLocation);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetUniformfv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetUniformiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetVertexAttribdv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetVertexAttribfv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetVertexAttribiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetVertexAttribPointerv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsProgram);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsShader);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glLinkProgram);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glShaderSource);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUseProgram);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform1f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform2f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform3f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform4f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform1i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform2i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform3i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform4i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform1fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform4fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform1iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform2iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform3iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform4iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix4fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glValidateProgram);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib1d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib1dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib1f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib1fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib1s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib1sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib2d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib2dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib2f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib2s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib2sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib3d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib3dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib3f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib3s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib3sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Nbv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Niv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Nsv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Nub);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Nubv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Nuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4Nusv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4bv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4d);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4dv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4f);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4s);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4ubv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttrib4usv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribPointer);

	// Version 2.1
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix2x3fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix3x2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix2x4fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix4x2fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix3x4fv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformMatrix4x3fv);

	// Version 3.0
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glColorMaski);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetBooleani_v);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetIntegeri_v);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glEnablei);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDisablei);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsEnabledi);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBeginTransformFeedback);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glEndTransformFeedback);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindBufferRange);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindBufferBase);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glTransformFeedbackVaryings);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetTransformFeedbackVarying);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glClampColor);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBeginConditionalRender);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glEndConditionalRender);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribIPointer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetVertexAttribIiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetVertexAttribIuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI1i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI2i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI3i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4i);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI1ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI2ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI3ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI1iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI2iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI3iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4iv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI1uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI2uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI3uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4bv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4sv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4ubv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glVertexAttribI4usv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetUniformuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindFragDataLocation);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetFragDataLocation);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform1ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform2ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform3ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform4ui);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform1uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform2uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform3uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniform4uiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glTexParameterIiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glTexParameterIuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetTexParameterIiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetTexParameterIuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glClearBufferiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glClearBufferuiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glClearBufferfv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glClearBufferfi);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetStringi);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsRenderbuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindRenderbuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteRenderbuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGenRenderbuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glRenderbufferStorage);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetRenderbufferParameteriv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsFramebuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindFramebuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteFramebuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGenFramebuffers);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCheckFramebufferStatus);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFramebufferTexture1D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFramebufferTexture2D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFramebufferTexture3D);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFramebufferRenderbuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetFramebufferAttachmentParameteriv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGenerateMipmap);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBlitFramebuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glRenderbufferStorageMultisample);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFramebufferTextureLayer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glMapBufferRange);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glFlushMappedBufferRange);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glBindVertexArray);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDeleteVertexArrays);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGenVertexArrays);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glIsVertexArray);

	// Version 3.1
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDrawArraysInstanced);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glDrawElementsInstanced);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glTexBuffer);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glPrimitiveRestartIndex);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glCopyBufferSubData);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetUniformIndices);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetActiveUniformsiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetActiveUniformName);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetUniformBlockIndex);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetActiveUniformBlockiv);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glGetActiveUniformBlockName);
	__GREAT_V_ENGINE_2__OBTAIN_OPENGL_FUNCTION__(glUniformBlockBinding);


	if (!wglMakeCurrent(NULL, NULL))
	{
		throw Exception();
	}

	DestroyWindow(windowHandle);
	
	UnregisterClassA(windowClassName.c_str(), instanceHandle);
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


