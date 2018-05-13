#pragma region Include

#pragma once

#include "Core_2_1.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
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
		class UniformBlock
		{
		public:
			class Index
			{
			public:
				using Value = GLuint;
			protected:
				Value value;
			public:
				inline Index() = default;
				inline explicit Index(const Value& value_):
					value(value_)
				{
				}
				inline Index(const Index&) = default;
				inline ~Index() = default;
			public:
				inline Index& operator = (const Index&) = default;
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
			class Binding
			{
			public:
				using Value = GLuint;
			protected:
				Value value;
			public:
				inline Binding() = default;
				inline explicit Binding(const Value& value_):
					value(value_)
				{
				}
				inline Binding(const Binding&) = default;
				inline ~Binding() = default;
			public:
				inline Binding& operator = (const Binding&) = default;
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
		};



		class Core_3_0:
			public virtual Core
		{
		protected:
			const PFNGLCOLORMASKIPROC										glColorMaski = nullptr;
			const PFNGLGETBOOLEANI_VPROC									glGetBooleani_v = nullptr;
			const PFNGLGETINTEGERI_VPROC									glGetIntegeri_v = nullptr;
			const PFNGLENABLEIPROC											glEnablei = nullptr;
			const PFNGLDISABLEIPROC											glDisablei = nullptr;
			const PFNGLISENABLEDIPROC										glIsEnabledi = nullptr;
			const PFNGLBEGINTRANSFORMFEEDBACKPROC							glBeginTransformFeedback = nullptr;
			const PFNGLENDTRANSFORMFEEDBACKPROC								glEndTransformFeedback = nullptr;
			const PFNGLBINDBUFFERRANGEPROC									glBindBufferRange = nullptr;
			const PFNGLBINDBUFFERBASEPROC									glBindBufferBase = nullptr;
			const PFNGLTRANSFORMFEEDBACKVARYINGSPROC						glTransformFeedbackVaryings = nullptr;
			const PFNGLGETTRANSFORMFEEDBACKVARYINGPROC						glGetTransformFeedbackVarying = nullptr;
			const PFNGLCLAMPCOLORPROC										glClampColor = nullptr;
			const PFNGLBEGINCONDITIONALRENDERPROC							glBeginConditionalRender = nullptr;
			const PFNGLENDCONDITIONALRENDERPROC								glEndConditionalRender = nullptr;
			const PFNGLVERTEXATTRIBIPOINTERPROC								glVertexAttribIPointer = nullptr;
			const PFNGLGETVERTEXATTRIBIIVPROC								glGetVertexAttribIiv = nullptr;
			const PFNGLGETVERTEXATTRIBIUIVPROC								glGetVertexAttribIuiv = nullptr;
			const PFNGLVERTEXATTRIBI1IPROC									glVertexAttribI1i = nullptr;
			const PFNGLVERTEXATTRIBI2IPROC									glVertexAttribI2i = nullptr;
			const PFNGLVERTEXATTRIBI3IPROC									glVertexAttribI3i = nullptr;
			const PFNGLVERTEXATTRIBI4IPROC									glVertexAttribI4i = nullptr;
			const PFNGLVERTEXATTRIBI1UIPROC									glVertexAttribI1ui = nullptr;
			const PFNGLVERTEXATTRIBI2UIPROC									glVertexAttribI2ui = nullptr;
			const PFNGLVERTEXATTRIBI3UIPROC									glVertexAttribI3ui = nullptr;
			const PFNGLVERTEXATTRIBI4UIPROC									glVertexAttribI4ui = nullptr;
			const PFNGLVERTEXATTRIBI1IVPROC									glVertexAttribI1iv = nullptr;
			const PFNGLVERTEXATTRIBI2IVPROC									glVertexAttribI2iv = nullptr;
			const PFNGLVERTEXATTRIBI3IVPROC									glVertexAttribI3iv = nullptr;
			const PFNGLVERTEXATTRIBI4IVPROC									glVertexAttribI4iv = nullptr;
			const PFNGLVERTEXATTRIBI1UIVPROC								glVertexAttribI1uiv = nullptr;
			const PFNGLVERTEXATTRIBI2UIVPROC								glVertexAttribI2uiv = nullptr;
			const PFNGLVERTEXATTRIBI3UIVPROC								glVertexAttribI3uiv = nullptr;
			const PFNGLVERTEXATTRIBI4UIVPROC								glVertexAttribI4uiv = nullptr;
			const PFNGLVERTEXATTRIBI4BVPROC									glVertexAttribI4bv = nullptr;
			const PFNGLVERTEXATTRIBI4SVPROC									glVertexAttribI4sv = nullptr;
			const PFNGLVERTEXATTRIBI4UBVPROC								glVertexAttribI4ubv = nullptr;
			const PFNGLVERTEXATTRIBI4USVPROC								glVertexAttribI4usv = nullptr;
			const PFNGLGETUNIFORMUIVPROC									glGetUniformuiv = nullptr;
			const PFNGLBINDFRAGDATALOCATIONPROC								glBindFragDataLocation = nullptr;
			const PFNGLGETFRAGDATALOCATIONPROC								glGetFragDataLocation = nullptr;
			const PFNGLUNIFORM1UIPROC										glUniform1ui = nullptr;
			const PFNGLUNIFORM2UIPROC										glUniform2ui = nullptr;
			const PFNGLUNIFORM3UIPROC										glUniform3ui = nullptr;
			const PFNGLUNIFORM4UIPROC										glUniform4ui = nullptr;
			const PFNGLUNIFORM1UIVPROC										glUniform1uiv = nullptr;
			const PFNGLUNIFORM2UIVPROC										glUniform2uiv = nullptr;
			const PFNGLUNIFORM3UIVPROC										glUniform3uiv = nullptr;
			const PFNGLUNIFORM4UIVPROC										glUniform4uiv = nullptr;
			const PFNGLTEXPARAMETERIIVPROC									glTexParameterIiv = nullptr;
			const PFNGLTEXPARAMETERIUIVPROC									glTexParameterIuiv = nullptr;
			const PFNGLGETTEXPARAMETERIIVPROC								glGetTexParameterIiv = nullptr;
			const PFNGLGETTEXPARAMETERIUIVPROC								glGetTexParameterIuiv = nullptr;
			const PFNGLCLEARBUFFERIVPROC									glClearBufferiv = nullptr;
			const PFNGLCLEARBUFFERUIVPROC									glClearBufferuiv = nullptr;
			const PFNGLCLEARBUFFERFVPROC									glClearBufferfv = nullptr;
			const PFNGLCLEARBUFFERFIPROC									glClearBufferfi = nullptr;
			const PFNGLGETSTRINGIPROC										glGetStringi = nullptr;
			const PFNGLISRENDERBUFFERPROC									glIsRenderbuffer = nullptr;
			const PFNGLBINDRENDERBUFFERPROC									glBindRenderbuffer = nullptr;
			const PFNGLDELETERENDERBUFFERSPROC								glDeleteRenderbuffers = nullptr;
			const PFNGLGENRENDERBUFFERSPROC									glGenRenderbuffers = nullptr;
			const PFNGLRENDERBUFFERSTORAGEPROC								glRenderbufferStorage = nullptr;
			const PFNGLGETRENDERBUFFERPARAMETERIVPROC						glGetRenderbufferParameteriv = nullptr;
			const PFNGLISFRAMEBUFFERPROC									glIsFramebuffer = nullptr;
			const PFNGLBINDFRAMEBUFFERPROC									glBindFramebuffer = nullptr;
			const PFNGLDELETEFRAMEBUFFERSPROC								glDeleteFramebuffers = nullptr;
			const PFNGLGENFRAMEBUFFERSPROC									glGenFramebuffers = nullptr;
			const PFNGLCHECKFRAMEBUFFERSTATUSPROC							glCheckFramebufferStatus = nullptr;
			const PFNGLFRAMEBUFFERTEXTURE1DPROC								glFramebufferTexture1D = nullptr;
			const PFNGLFRAMEBUFFERTEXTURE2DPROC								glFramebufferTexture2D = nullptr;
			const PFNGLFRAMEBUFFERTEXTURE3DPROC								glFramebufferTexture3D = nullptr;
			const PFNGLFRAMEBUFFERRENDERBUFFERPROC							glFramebufferRenderbuffer = nullptr;
			const PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC				glGetFramebufferAttachmentParameteriv = nullptr;
			const PFNGLGENERATEMIPMAPPROC									glGenerateMipmap = nullptr;
			const PFNGLBLITFRAMEBUFFERPROC									glBlitFramebuffer = nullptr;
			const PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC					glRenderbufferStorageMultisample = nullptr;
			const PFNGLFRAMEBUFFERTEXTURELAYERPROC							glFramebufferTextureLayer = nullptr;
			const PFNGLMAPBUFFERRANGEPROC									glMapBufferRange = nullptr;
			const PFNGLFLUSHMAPPEDBUFFERRANGEPROC							glFlushMappedBufferRange = nullptr;
			const PFNGLBINDVERTEXARRAYPROC									glBindVertexArray = nullptr;
			const PFNGLDELETEVERTEXARRAYSPROC								glDeleteVertexArrays = nullptr;
			const PFNGLGENVERTEXARRAYSPROC									glGenVertexArrays = nullptr;
			const PFNGLISVERTEXARRAYPROC									glIsVertexArray = nullptr;
		protected:
			inline Core_3_0() = default;
			inline Core_3_0(
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
			inline void														BindBufferBase(const Buffer::Type& type_, const UniformBlock::Index& index_, const Buffer::Handle& bufferHandle_) const
			{
				glBindBufferBase(static_cast<GLenum>(type_), index_, static_cast<Buffer::Handle::Value>(bufferHandle_));

				CheckForErrors();
			}
		};
#pragma region Core_3_0
		Core_3_0::Core_3_0(
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
		glColorMaski(glColorMaski_),
			glGetBooleani_v(glGetBooleani_v_),
			glGetIntegeri_v(glGetIntegeri_v_),
			glEnablei(glEnablei_),
			glDisablei(glDisablei_),
			glIsEnabledi(glIsEnabledi_),
			glBeginTransformFeedback(glBeginTransformFeedback_),
			glEndTransformFeedback(glEndTransformFeedback_),
			glBindBufferRange(glBindBufferRange_),
			glBindBufferBase(glBindBufferBase_),
			glTransformFeedbackVaryings(glTransformFeedbackVaryings_),
			glGetTransformFeedbackVarying(glGetTransformFeedbackVarying_),
			glClampColor(glClampColor_),
			glBeginConditionalRender(glBeginConditionalRender_),
			glEndConditionalRender(glEndConditionalRender_),
			glVertexAttribIPointer(glVertexAttribIPointer_),
			glGetVertexAttribIiv(glGetVertexAttribIiv_),
			glGetVertexAttribIuiv(glGetVertexAttribIuiv_),
			glVertexAttribI1i(glVertexAttribI1i_),
			glVertexAttribI2i(glVertexAttribI2i_),
			glVertexAttribI3i(glVertexAttribI3i_),
			glVertexAttribI4i(glVertexAttribI4i_),
			glVertexAttribI1ui(glVertexAttribI1ui_),
			glVertexAttribI2ui(glVertexAttribI2ui_),
			glVertexAttribI3ui(glVertexAttribI3ui_),
			glVertexAttribI4ui(glVertexAttribI4ui_),
			glVertexAttribI1iv(glVertexAttribI1iv_),
			glVertexAttribI2iv(glVertexAttribI2iv_),
			glVertexAttribI3iv(glVertexAttribI3iv_),
			glVertexAttribI4iv(glVertexAttribI4iv_),
			glVertexAttribI1uiv(glVertexAttribI1uiv_),
			glVertexAttribI2uiv(glVertexAttribI2uiv_),
			glVertexAttribI3uiv(glVertexAttribI3uiv_),
			glVertexAttribI4uiv(glVertexAttribI4uiv_),
			glVertexAttribI4bv(glVertexAttribI4bv_),
			glVertexAttribI4sv(glVertexAttribI4sv_),
			glVertexAttribI4ubv(glVertexAttribI4ubv_),
			glVertexAttribI4usv(glVertexAttribI4usv_),
			glGetUniformuiv(glGetUniformuiv_),
			glBindFragDataLocation(glBindFragDataLocation_),
			glGetFragDataLocation(glGetFragDataLocation_),
			glUniform1ui(glUniform1ui_),
			glUniform2ui(glUniform2ui_),
			glUniform3ui(glUniform3ui_),
			glUniform4ui(glUniform4ui_),
			glUniform1uiv(glUniform1uiv_),
			glUniform2uiv(glUniform2uiv_),
			glUniform3uiv(glUniform3uiv_),
			glUniform4uiv(glUniform4uiv_),
			glTexParameterIiv(glTexParameterIiv_),
			glTexParameterIuiv(glTexParameterIuiv_),
			glGetTexParameterIiv(glGetTexParameterIiv_),
			glGetTexParameterIuiv(glGetTexParameterIuiv_),
			glClearBufferiv(glClearBufferiv_),
			glClearBufferuiv(glClearBufferuiv_),
			glClearBufferfv(glClearBufferfv_),
			glClearBufferfi(glClearBufferfi_),
			glGetStringi(glGetStringi_),
			glIsRenderbuffer(glIsRenderbuffer_),
			glBindRenderbuffer(glBindRenderbuffer_),
			glDeleteRenderbuffers(glDeleteRenderbuffers_),
			glGenRenderbuffers(glGenRenderbuffers_),
			glRenderbufferStorage(glRenderbufferStorage_),
			glGetRenderbufferParameteriv(glGetRenderbufferParameteriv_),
			glIsFramebuffer(glIsFramebuffer_),
			glBindFramebuffer(glBindFramebuffer_),
			glDeleteFramebuffers(glDeleteFramebuffers_),
			glGenFramebuffers(glGenFramebuffers_),
			glCheckFramebufferStatus(glCheckFramebufferStatus_),
			glFramebufferTexture1D(glFramebufferTexture1D_),
			glFramebufferTexture2D(glFramebufferTexture2D_),
			glFramebufferTexture3D(glFramebufferTexture3D_),
			glFramebufferRenderbuffer(glFramebufferRenderbuffer_),
			glGetFramebufferAttachmentParameteriv(glGetFramebufferAttachmentParameteriv_),
			glGenerateMipmap(glGenerateMipmap_),
			glBlitFramebuffer(glBlitFramebuffer_),
			glRenderbufferStorageMultisample(glRenderbufferStorageMultisample_),
			glFramebufferTextureLayer(glFramebufferTextureLayer_),
			glMapBufferRange(glMapBufferRange_),
			glFlushMappedBufferRange(glFlushMappedBufferRange_),
			glBindVertexArray(glBindVertexArray_),
			glDeleteVertexArrays(glDeleteVertexArrays_),
			glGenVertexArrays(glGenVertexArrays_),
			glIsVertexArray(glIsVertexArray_)
		{
		}
#pragma endregion

		class Context_3_0:
			public Context_2_1,
			public virtual Core_3_0
		{
		};
#pragma region Context_3_0
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_3_0
				Context_3_0::Attributes Context_3_0::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
						WGL_CONTEXT_MINOR_VERSION_ARB, 0,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_3_0::Context_3_0(const Handle& handle_, const EmptyTag&):
					Windows::Context_2_1(handle_, EmptyTag()),
					OpenGL::Context_3_0(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4(),
					Core_1_5(),
					Core_2_0(),
					Core_2_1(),
					Core_3_0()
				{
					}
				Context_3_0::Context_3_0(const Handle& handle_):
					Windows::Context_2_1(handle_, EmptyTag()),
					OpenGL::Context_3_0(),
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
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_3_0::Context_3_0(const DeviceContextHandle& deviceContextHandle_):
					Context_3_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
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


