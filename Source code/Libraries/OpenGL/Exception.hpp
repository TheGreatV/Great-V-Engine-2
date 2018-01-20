#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenGL
	{
		class Exception:
			public GreatVEngine2::Exception
		{
		public:
			inline Exception();
			inline Exception(const Text& text_);
		};

		class Error
		{
		public:
			enum class Code
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
			static inline void Check();
			static inline String GetText(const Code& code_);
		protected:
			const Code code;
		public:
			inline Error(const Code& code_);
		public:
			inline Code GetCode() const;
		};
	}
}


#pragma region GreatVEngine2

#pragma region OpenGL

#pragma region Exception

GreatVEngine2::OpenGL::Exception::Exception():
	Exception("Unknown OpenGL exception.")
{
}
GreatVEngine2::OpenGL::Exception::Exception(const Text& text_) :
	GreatVEngine2::Exception(text_)
{
}

#pragma endregion

#pragma region Error

void GreatVEngine2::OpenGL::Error::Check()
{
	auto code = static_cast<Code>(glGetError());

	if (code != Code::NoError)
	{
		auto error = Error(code);

		throw error;
	}
}
GreatVEngine2::String GreatVEngine2::OpenGL::Error::GetText(const Code& code_)
{
	switch (code_)
	{
		case GreatVEngine2::OpenGL::Error::Code::NoError:						return "No error.";
		case GreatVEngine2::OpenGL::Error::Code::InvalidOperation:				return "Invalid operation.";
		case GreatVEngine2::OpenGL::Error::Code::InvalidEnum:					return "Invalid enum.";
		case GreatVEngine2::OpenGL::Error::Code::InvalidValue:					return "Invalid value.";
		case GreatVEngine2::OpenGL::Error::Code::StackOverflow:					return "Stack overflow.";
		case GreatVEngine2::OpenGL::Error::Code::StackUnderflow:				return "Stack underflow.";
		case GreatVEngine2::OpenGL::Error::Code::OutOfMemory:					return "Out of memory.";
		case GreatVEngine2::OpenGL::Error::Code::InvalidFramebufferOperation:	return "Invalid framebuffer operation.";
		default: throw Exception("Invalid OpenGL error code: " + ToString(static_cast<Size>(code_)));
	}
}

GreatVEngine2::OpenGL::Error::Error(const Code& code_):
	code(code_)
{
}

GreatVEngine2::OpenGL::Error::Code GreatVEngine2::OpenGL::Error::GetCode() const
{
	return code;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


