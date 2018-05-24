#pragma region Include

#pragma once

#include <../Common/Common.hpp>

#if __GREAT_V_ENGINE_2__PLATFORM__ == __GREAT_V_ENGINE_2__PLATFORM_WINDOWS__

#include <Windows.h>

#endif

#include <gl/gl.h>
#include <gl/glext.h>
#include <gl/wglext.h>

#pragma endregion


#pragma region Macros

#define __GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS__(x) reinterpret_cast<decltype(x)>(GetProcedureAddress(#x))
#define __GREAT_V_ENGINE_2__GET_PROCEDURE_ADDRESS2__(x, h) reinterpret_cast<decltype(x)>(GetProcedureAddress(#x, h))

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		enum class PrimitiveType: GLenum
		{
			Triangles = GL_TRIANGLES,
		};
		enum class IndexType: GLenum
		{
			UInt8 = GL_UNSIGNED_BYTE,
			UInt16 = GL_UNSIGNED_SHORT,
			UInt32 = GL_UNSIGNED_INT,
		};


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


		class Core
		{
		protected:
			inline void				CheckForErrors() const;
		public:
			inline Error::Code		GetErrorCode() const;
		};
#pragma region Core
		void Core::CheckForErrors() const
		{
#if __GREAT_V_ENGINE_2__DEBUG__
			auto code = GetErrorCode();

			if (code != Error::Code::NoError)
			{
				throw Exception();
			}
#endif
		}

		Error::Code Core::GetErrorCode() const
		{
			auto code = static_cast<Error::Code>(glGetError());

			return code;
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
					class EmptyTag {};
				protected:
					using Attributes = Vector<GLint>;
				public:
					using Handle = HGLRC;
					using DeviceContextHandle = HDC;
					using Procedure = PROC;
					using RestorePoint = Pair<DeviceContextHandle, Handle>;
				protected:
					const Handle				handle;
				protected:
					inline						Context(const Handle& handle_):
						handle(handle_)
					{
					}
				public:
					inline Handle				GetHandle() const
					{
						return handle;
					}
				};


				inline Context::Handle					CreateContext(const Context::DeviceContextHandle& deviceContextHandle_) // TODO: move this functions to Windows namespace
				{
					auto handle = wglCreateContext(deviceContextHandle_);

					if (!handle)
					{
						throw Exception();
					}

					return handle;
				}
				inline void								DeleteContext(const Context::Handle& handle_)
				{
					auto result = wglDeleteContext(handle_);

					if (!result)
					{
						throw Exception();
					}
				}
				inline Context::Handle					GetCurrentContextHandle()
				{
					auto handle = wglGetCurrentContext();

					return handle;
				}
				inline Context::DeviceContextHandle		GetCurrentDeviceContextHandle()
				{
					auto handle = wglGetCurrentDC();

					return handle;
				}
				inline void								MakeCurrent(const Context::DeviceContextHandle& deviceContextHandle_, const Context::Handle& handle_)
				{
					auto result = wglMakeCurrent(deviceContextHandle_, handle_);

					if (!result)
					{
						throw Exception();
					}
				}


				class Lock
				{
				protected:
					const Context::Handle				previousContextHandle;
					const Context::DeviceContextHandle	previousDeviceContextHandle;
					const Context::Handle				currentContextHandle;
					const Context::DeviceContextHandle	currentDeviceContextHandle;
				public:
					inline Lock(const Context& context_, const Context::DeviceContextHandle& deviceContextHandle_):
						previousContextHandle(GetCurrentContextHandle()),
						previousDeviceContextHandle(GetCurrentDeviceContextHandle()),
						currentContextHandle(context_.GetHandle()),
						currentDeviceContextHandle(deviceContextHandle_)
					{
						if (previousContextHandle != currentContextHandle || previousDeviceContextHandle != currentDeviceContextHandle)
						{
							MakeCurrent(currentDeviceContextHandle, currentContextHandle);
						}
					}
					inline Lock(const StrongPointer<Context>& context_, const Context::DeviceContextHandle& deviceContextHandle_):
						Lock(*context_.GetValue(), deviceContextHandle_)
					{
					}
					inline Lock(const Lock&) = delete;
					inline ~Lock()
					{
						if (previousContextHandle != currentContextHandle || previousDeviceContextHandle != currentDeviceContextHandle)
						{
							MakeCurrent(previousDeviceContextHandle, previousContextHandle);
						}
					}
				};
			}
#endif
		}
	}
}


#pragma region
#pragma endregion


