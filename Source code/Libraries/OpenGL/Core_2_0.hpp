#pragma region Include

#pragma once

#include "Core_1_5.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Shader
		{
		public:
			enum class Type: GLenum
			{
				Vertex = GL_VERTEX_SHADER,
				Geometry = GL_GEOMETRY_SHADER,
				Fragment = GL_FRAGMENT_SHADER,
			};
			enum class Parameter: GLenum
			{
				CompilseStatus = GL_COMPILE_STATUS,
				InfoLogLength = GL_INFO_LOG_LENGTH,
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
		class Program
		{
		public:
			enum class Parameter: GLenum
			{
				LinkStatus = GL_LINK_STATUS,
				ValidateStatus = GL_VALIDATE_STATUS,
				InfoLogLength = GL_INFO_LOG_LENGTH,
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
					Float = GL_FLOAT,
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

		class Core_2_0:
			public virtual Core
		{
		protected:
			const PFNGLBLENDEQUATIONSEPARATEPROC			glBlendEquationSeparate = nullptr;
			const PFNGLDRAWBUFFERSPROC						glDrawBuffers = nullptr;
			const PFNGLSTENCILOPSEPARATEPROC				glStencilOpSeparate = nullptr;
			const PFNGLSTENCILFUNCSEPARATEPROC				glStencilFuncSeparate = nullptr;
			const PFNGLSTENCILMASKSEPARATEPROC				glStencilMaskSeparate = nullptr;
			const PFNGLATTACHSHADERPROC						glAttachShader = nullptr;
			const PFNGLBINDATTRIBLOCATIONPROC				glBindAttribLocation = nullptr;
			const PFNGLCOMPILESHADERPROC					glCompileShader = nullptr;
			const PFNGLCREATEPROGRAMPROC					glCreateProgram = nullptr;
			const PFNGLCREATESHADERPROC						glCreateShader = nullptr;
			const PFNGLDELETEPROGRAMPROC					glDeleteProgram = nullptr;
			const PFNGLDELETESHADERPROC						glDeleteShader = nullptr;
			const PFNGLDETACHSHADERPROC						glDetachShader = nullptr;
			const PFNGLDISABLEVERTEXATTRIBARRAYPROC			glDisableVertexAttribArray = nullptr;
			const PFNGLENABLEVERTEXATTRIBARRAYPROC			glEnableVertexAttribArray = nullptr;
			const PFNGLGETACTIVEATTRIBPROC					glGetActiveAttrib = nullptr;
			const PFNGLGETACTIVEUNIFORMPROC					glGetActiveUniform = nullptr;
			const PFNGLGETATTACHEDSHADERSPROC				glGetAttachedShaders = nullptr;
			const PFNGLGETATTRIBLOCATIONPROC				glGetAttribLocation = nullptr;
			const PFNGLGETPROGRAMIVPROC						glGetProgramiv = nullptr;
			const PFNGLGETPROGRAMINFOLOGPROC				glGetProgramInfoLog = nullptr;
			const PFNGLGETSHADERIVPROC						glGetShaderiv = nullptr;
			const PFNGLGETSHADERINFOLOGPROC					glGetShaderInfoLog = nullptr;
			const PFNGLGETSHADERSOURCEPROC					glGetShaderSource = nullptr;
			const PFNGLGETUNIFORMLOCATIONPROC				glGetUniformLocation = nullptr;
			const PFNGLGETUNIFORMFVPROC						glGetUniformfv = nullptr;
			const PFNGLGETUNIFORMIVPROC						glGetUniformiv = nullptr;
			const PFNGLGETVERTEXATTRIBDVPROC				glGetVertexAttribdv = nullptr;
			const PFNGLGETVERTEXATTRIBFVPROC				glGetVertexAttribfv = nullptr;
			const PFNGLGETVERTEXATTRIBIVPROC				glGetVertexAttribiv = nullptr;
			const PFNGLGETVERTEXATTRIBPOINTERVPROC			glGetVertexAttribPointerv = nullptr;
			const PFNGLISPROGRAMPROC						glIsProgram = nullptr;
			const PFNGLISSHADERPROC							glIsShader = nullptr;
			const PFNGLLINKPROGRAMPROC						glLinkProgram = nullptr;
			const PFNGLSHADERSOURCEPROC						glShaderSource = nullptr;
			const PFNGLUSEPROGRAMPROC						glUseProgram = nullptr;
			const PFNGLUNIFORM1FPROC						glUniform1f = nullptr;
			const PFNGLUNIFORM2FPROC						glUniform2f = nullptr;
			const PFNGLUNIFORM3FPROC						glUniform3f = nullptr;
			const PFNGLUNIFORM4FPROC						glUniform4f = nullptr;
			const PFNGLUNIFORM1IPROC						glUniform1i = nullptr;
			const PFNGLUNIFORM2IPROC						glUniform2i = nullptr;
			const PFNGLUNIFORM3IPROC						glUniform3i = nullptr;
			const PFNGLUNIFORM4IPROC						glUniform4i = nullptr;
			const PFNGLUNIFORM1FVPROC						glUniform1fv = nullptr;
			const PFNGLUNIFORM2FVPROC						glUniform2fv = nullptr;
			const PFNGLUNIFORM3FVPROC						glUniform3fv = nullptr;
			const PFNGLUNIFORM4FVPROC						glUniform4fv = nullptr;
			const PFNGLUNIFORM1IVPROC						glUniform1iv = nullptr;
			const PFNGLUNIFORM2IVPROC						glUniform2iv = nullptr;
			const PFNGLUNIFORM3IVPROC						glUniform3iv = nullptr;
			const PFNGLUNIFORM4IVPROC						glUniform4iv = nullptr;
			const PFNGLUNIFORMMATRIX2FVPROC					glUniformMatrix2fv = nullptr;
			const PFNGLUNIFORMMATRIX3FVPROC					glUniformMatrix3fv = nullptr;
			const PFNGLUNIFORMMATRIX4FVPROC					glUniformMatrix4fv = nullptr;
			const PFNGLVALIDATEPROGRAMPROC					glValidateProgram = nullptr;
			const PFNGLVERTEXATTRIB1DPROC					glVertexAttrib1d = nullptr;
			const PFNGLVERTEXATTRIB1DVPROC					glVertexAttrib1dv = nullptr;
			const PFNGLVERTEXATTRIB1FPROC					glVertexAttrib1f = nullptr;
			const PFNGLVERTEXATTRIB1FVPROC					glVertexAttrib1fv = nullptr;
			const PFNGLVERTEXATTRIB1SPROC					glVertexAttrib1s = nullptr;
			const PFNGLVERTEXATTRIB1SVPROC					glVertexAttrib1sv = nullptr;
			const PFNGLVERTEXATTRIB2DPROC					glVertexAttrib2d = nullptr;
			const PFNGLVERTEXATTRIB2DVPROC					glVertexAttrib2dv = nullptr;
			const PFNGLVERTEXATTRIB2FPROC					glVertexAttrib2f = nullptr;
			const PFNGLVERTEXATTRIB2FVPROC					glVertexAttrib2fv = nullptr;
			const PFNGLVERTEXATTRIB2SPROC					glVertexAttrib2s = nullptr;
			const PFNGLVERTEXATTRIB2SVPROC					glVertexAttrib2sv = nullptr;
			const PFNGLVERTEXATTRIB3DPROC					glVertexAttrib3d = nullptr;
			const PFNGLVERTEXATTRIB3DVPROC					glVertexAttrib3dv = nullptr;
			const PFNGLVERTEXATTRIB3FPROC					glVertexAttrib3f = nullptr;
			const PFNGLVERTEXATTRIB3FVPROC					glVertexAttrib3fv = nullptr;
			const PFNGLVERTEXATTRIB3SPROC					glVertexAttrib3s = nullptr;
			const PFNGLVERTEXATTRIB3SVPROC					glVertexAttrib3sv = nullptr;
			const PFNGLVERTEXATTRIB4NBVPROC					glVertexAttrib4Nbv = nullptr;
			const PFNGLVERTEXATTRIB4NIVPROC					glVertexAttrib4Niv = nullptr;
			const PFNGLVERTEXATTRIB4NSVPROC					glVertexAttrib4Nsv = nullptr;
			const PFNGLVERTEXATTRIB4NUBPROC					glVertexAttrib4Nub = nullptr;
			const PFNGLVERTEXATTRIB4NUBVPROC				glVertexAttrib4Nubv = nullptr;
			const PFNGLVERTEXATTRIB4NUIVPROC				glVertexAttrib4Nuiv = nullptr;
			const PFNGLVERTEXATTRIB4NUSVPROC				glVertexAttrib4Nusv = nullptr;
			const PFNGLVERTEXATTRIB4BVPROC					glVertexAttrib4bv = nullptr;
			const PFNGLVERTEXATTRIB4DPROC					glVertexAttrib4d = nullptr;
			const PFNGLVERTEXATTRIB4DVPROC					glVertexAttrib4dv = nullptr;
			const PFNGLVERTEXATTRIB4FPROC					glVertexAttrib4f = nullptr;
			const PFNGLVERTEXATTRIB4FVPROC					glVertexAttrib4fv = nullptr;
			const PFNGLVERTEXATTRIB4IVPROC					glVertexAttrib4iv = nullptr;
			const PFNGLVERTEXATTRIB4SPROC					glVertexAttrib4s = nullptr;
			const PFNGLVERTEXATTRIB4SVPROC					glVertexAttrib4sv = nullptr;
			const PFNGLVERTEXATTRIB4UBVPROC					glVertexAttrib4ubv = nullptr;
			const PFNGLVERTEXATTRIB4UIVPROC					glVertexAttrib4uiv = nullptr;
			const PFNGLVERTEXATTRIB4USVPROC					glVertexAttrib4usv = nullptr;
			const PFNGLVERTEXATTRIBPOINTERPROC				glVertexAttribPointer = nullptr;
		protected:
			inline Core_2_0() = default;
			inline Core_2_0(
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
				const auto value = glCreateProgram();

				CheckForErrors();

				const auto handle = Program::Handle(value);

				return handle;
			}
			inline Shader::Handle					CreateShader(const Shader::Type& type_) const
			{
				const auto value = glCreateShader(static_cast<GLenum>(type_));

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
				const GLchar*const	data = source_.c_str();
				const GLint			length = source_.length();

				glShaderSource(static_cast<Shader::Handle::Value>(handle_), 1, &data, &length);

				CheckForErrors();
			}
			inline void								UseProgram(const Null&) const
			{
				glUseProgram(0);

				CheckForErrors();
			}
			inline void								UseProgram(const Program::Handle& handle_) const
			{
				glUseProgram(static_cast<Program::Handle::Value>(handle_));

				CheckForErrors();
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
#pragma region Core_2_0
		Core_2_0::Core_2_0(
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
		glBlendEquationSeparate(glBlendEquationSeparate_),
			glDrawBuffers(glDrawBuffers_),
			glStencilOpSeparate(glStencilOpSeparate_),
			glStencilFuncSeparate(glStencilFuncSeparate_),
			glStencilMaskSeparate(glStencilMaskSeparate_),
			glAttachShader(glAttachShader_),
			glBindAttribLocation(glBindAttribLocation_),
			glCompileShader(glCompileShader_),
			glCreateProgram(glCreateProgram_),
			glCreateShader(glCreateShader_),
			glDeleteProgram(glDeleteProgram_),
			glDeleteShader(glDeleteShader_),
			glDetachShader(glDetachShader_),
			glDisableVertexAttribArray(glDisableVertexAttribArray_),
			glEnableVertexAttribArray(glEnableVertexAttribArray_),
			glGetActiveAttrib(glGetActiveAttrib_),
			glGetActiveUniform(glGetActiveUniform_),
			glGetAttachedShaders(glGetAttachedShaders_),
			glGetAttribLocation(glGetAttribLocation_),
			glGetProgramiv(glGetProgramiv_),
			glGetProgramInfoLog(glGetProgramInfoLog_),
			glGetShaderiv(glGetShaderiv_),
			glGetShaderInfoLog(glGetShaderInfoLog_),
			glGetShaderSource(glGetShaderSource_),
			glGetUniformLocation(glGetUniformLocation_),
			glGetUniformfv(glGetUniformfv_),
			glGetUniformiv(glGetUniformiv_),
			glGetVertexAttribdv(glGetVertexAttribdv_),
			glGetVertexAttribfv(glGetVertexAttribfv_),
			glGetVertexAttribiv(glGetVertexAttribiv_),
			glGetVertexAttribPointerv(glGetVertexAttribPointerv_),
			glIsProgram(glIsProgram_),
			glIsShader(glIsShader_),
			glLinkProgram(glLinkProgram_),
			glShaderSource(glShaderSource_),
			glUseProgram(glUseProgram_),
			glUniform1f(glUniform1f_),
			glUniform2f(glUniform2f_),
			glUniform3f(glUniform3f_),
			glUniform4f(glUniform4f_),
			glUniform1i(glUniform1i_),
			glUniform2i(glUniform2i_),
			glUniform3i(glUniform3i_),
			glUniform4i(glUniform4i_),
			glUniform1fv(glUniform1fv_),
			glUniform2fv(glUniform2fv_),
			glUniform3fv(glUniform3fv_),
			glUniform4fv(glUniform4fv_),
			glUniform1iv(glUniform1iv_),
			glUniform2iv(glUniform2iv_),
			glUniform3iv(glUniform3iv_),
			glUniform4iv(glUniform4iv_),
			glUniformMatrix2fv(glUniformMatrix2fv_),
			glUniformMatrix3fv(glUniformMatrix3fv_),
			glUniformMatrix4fv(glUniformMatrix4fv_),
			glValidateProgram(glValidateProgram_),
			glVertexAttrib1d(glVertexAttrib1d_),
			glVertexAttrib1dv(glVertexAttrib1dv_),
			glVertexAttrib1f(glVertexAttrib1f_),
			glVertexAttrib1fv(glVertexAttrib1fv_),
			glVertexAttrib1s(glVertexAttrib1s_),
			glVertexAttrib1sv(glVertexAttrib1sv_),
			glVertexAttrib2d(glVertexAttrib2d_),
			glVertexAttrib2dv(glVertexAttrib2dv_),
			glVertexAttrib2f(glVertexAttrib2f_),
			glVertexAttrib2fv(glVertexAttrib2fv_),
			glVertexAttrib2s(glVertexAttrib2s_),
			glVertexAttrib2sv(glVertexAttrib2sv_),
			glVertexAttrib3d(glVertexAttrib3d_),
			glVertexAttrib3dv(glVertexAttrib3dv_),
			glVertexAttrib3f(glVertexAttrib3f_),
			glVertexAttrib3fv(glVertexAttrib3fv_),
			glVertexAttrib3s(glVertexAttrib3s_),
			glVertexAttrib3sv(glVertexAttrib3sv_),
			glVertexAttrib4Nbv(glVertexAttrib4Nbv_),
			glVertexAttrib4Niv(glVertexAttrib4Niv_),
			glVertexAttrib4Nsv(glVertexAttrib4Nsv_),
			glVertexAttrib4Nub(glVertexAttrib4Nub_),
			glVertexAttrib4Nubv(glVertexAttrib4Nubv_),
			glVertexAttrib4Nuiv(glVertexAttrib4Nuiv_),
			glVertexAttrib4Nusv(glVertexAttrib4Nusv_),
			glVertexAttrib4bv(glVertexAttrib4bv_),
			glVertexAttrib4d(glVertexAttrib4d_),
			glVertexAttrib4dv(glVertexAttrib4dv_),
			glVertexAttrib4f(glVertexAttrib4f_),
			glVertexAttrib4fv(glVertexAttrib4fv_),
			glVertexAttrib4iv(glVertexAttrib4iv_),
			glVertexAttrib4s(glVertexAttrib4s_),
			glVertexAttrib4sv(glVertexAttrib4sv_),
			glVertexAttrib4ubv(glVertexAttrib4ubv_),
			glVertexAttrib4uiv(glVertexAttrib4uiv_),
			glVertexAttrib4usv(glVertexAttrib4usv_),
			glVertexAttribPointer(glVertexAttribPointer_)
		{
		}
#pragma endregion

		class Context_2_0:
			public Context_1_5,
			public virtual Core_2_0
		{
		};
#pragma region Context_2_0
#pragma endregion

		namespace OSs
		{
#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__
			namespace Windows
			{
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
#pragma region Context_2_0
				Context_2_0::Attributes Context_2_0::GetAttributes()
				{
					return{
						WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
						WGL_CONTEXT_MINOR_VERSION_ARB, 0,
						WGL_CONTEXT_FLAGS_ARB, 0, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB (???) | WGL_CONTEXT_DEBUG_BIT_ARB
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB / WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
						0, 0,
					};
				}

				Context_2_0::Context_2_0(const Handle& handle_, const EmptyTag&):
					Windows::Context_1_5(handle_, EmptyTag()),
					OpenGL::Context_2_0(),
					Core_1_2(),
					Core_1_3(),
					Core_1_4(),
					Core_1_5(),
					Core_2_0()
				{
					}
				Context_2_0::Context_2_0(const Handle& handle_):
					Windows::Context_1_5(handle_, EmptyTag()),
					OpenGL::Context_2_0(),
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
					)
				{
					MakeCurrent(nullptr, nullptr);
				}
				Context_2_0::Context_2_0(const DeviceContextHandle& deviceContextHandle_):
					Context_2_0(MakeCurrentAndReturn(deviceContextHandle_, ObtainHandle(deviceContextHandle_, nullptr, GetAttributes())))
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


