#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macro

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenIL
	{
		enum class ErrorCode
		{
			NoError					= IL_NO_ERROR,

			InvalidEnum				= IL_INVALID_ENUM,
			OutOfMemory				= IL_OUT_OF_MEMORY,
			FormatNotSupported		= IL_FORMAT_NOT_SUPPORTED,
			InvalidValue			= IL_INVALID_VALUE,
			IllegalOperation		= IL_ILLEGAL_OPERATION,
			IllegalFileValue		= IL_ILLEGAL_FILE_VALUE,
			InvalidFileHeader		= IL_INVALID_FILE_HEADER,
			InvalidParam			= IL_INVALID_PARAM,
			CouldNotOpenFile		= IL_COULD_NOT_OPEN_FILE,
			InvalidExtension		= IL_INVALID_EXTENSION,
			FileAlreadyExist		= IL_FILE_ALREADY_EXISTS,
			OutFormatSame			= IL_OUT_FORMAT_SAME,
			StackOverflow			= IL_STACK_OVERFLOW,
			StakUnderflow			= IL_STACK_UNDERFLOW,
			InvalidConversion		= IL_INVALID_CONVERSION,
			LibTIFF_Error			= IL_LIB_TIFF_ERROR,
			LibJPEG_Error			= IL_LIB_JPEG_ERROR,
			LibPNG_Error			= IL_LIB_PNG_ERROR,
			UnknownError			= IL_UNKNOWN_ERROR,
			ILUT_NotSupported		= ILUT_NOT_SUPPORTED,

			UndefinedError,
		};

		using ErrorText = String;

		class Exception:
			public GreatVEngine2::Exception
		{
		public:
			using Code = ErrorCode;
		protected:
			const Code code = Code::UndefinedError;
		public:
			inline Exception();
			inline Exception(const Exception&) = default;
			inline ~Exception() = default;
		public:
			inline Exception(const Code& code_);
		public:
			inline Exception& operator = (const Exception&) = delete;
		public:
			inline Code GetCode() const;
		};

		inline ErrorCode	GetError();
		inline bool			IsSuccessful(const ErrorCode& errorCode_);
		inline ErrorText	GetErrorText(const ErrorCode& errorCode_);
		inline void			ErrorTest(const ErrorCode& errorCode_);
		inline void			ErrorTest();
	}
}


#pragma region GreatVEngine2

#pragma region OpenIL

#pragma region Exception

GreatVEngine2::OpenIL::Exception::Exception():
	Exception(Code::UndefinedError)
{
}
GreatVEngine2::OpenIL::Exception::Exception(const Code& code_):
	GreatVEngine2::Exception(GetErrorText(code_)),
	code(code_)
{
}

GreatVEngine2::OpenIL::Exception::Code GreatVEngine2::OpenIL::Exception::GetCode() const
{
	return code;
}

#pragma endregion


GreatVEngine2::OpenIL::ErrorCode GreatVEngine2::OpenIL::GetError()
{
	auto errorCode = ilGetError();

	return static_cast<ErrorCode>(errorCode);
}
bool GreatVEngine2::OpenIL::IsSuccessful(const ErrorCode& errorCode_)
{
	return errorCode_ == ErrorCode::NoError;
}
GreatVEngine2::OpenIL::ErrorText GreatVEngine2::OpenIL::GetErrorText(const ErrorCode& errorCode_)
{
	switch (errorCode_)
	{
		case ErrorCode::InvalidEnum:			return "IL_INVALID_ENUM";
		case ErrorCode::OutOfMemory:			return "IL_OUT_OF_MEMORY";
		case ErrorCode::FormatNotSupported:		return "IL_FORMAT_NOT_SUPPORTED";
		case ErrorCode::InvalidValue:			return "IL_INVALID_VALUE";
		case ErrorCode::IllegalOperation:		return "IL_ILLEGAL_OPERATION";
		case ErrorCode::IllegalFileValue:		return "IL_ILLEGAL_FILE_VALUE";
		case ErrorCode::InvalidFileHeader:		return "IL_INVALID_FILE_HEADER";
		case ErrorCode::InvalidParam:			return "IL_INVALID_PARAM";
		case ErrorCode::CouldNotOpenFile:		return "IL_COULD_NOT_OPEN_FILE";
		case ErrorCode::InvalidExtension:		return "IL_INVALID_EXTENSION";
		case ErrorCode::FileAlreadyExist:		return "IL_FILE_ALREADY_EXISTS";
		case ErrorCode::OutFormatSame:			return "IL_OUT_FORMAT_SAME";
		case ErrorCode::StackOverflow:			return "IL_STACK_OVERFLOW";
		case ErrorCode::StakUnderflow:			return "IL_STACK_UNDERFLOW";
		case ErrorCode::InvalidConversion:		return "IL_INVALID_CONVERSION";
		case ErrorCode::LibTIFF_Error:			return "IL_LIB_TIFF_ERROR";
		case ErrorCode::LibJPEG_Error:			return "IL_LIB_JPEG_ERROR";
		case ErrorCode::LibPNG_Error:			return "IL_LIB_PNG_ERROR";
		case ErrorCode::UnknownError:			return "IL_UNKNOWN_ERROR";
		case ErrorCode::ILUT_NotSupported:		return "ILUT_NOT_SUPPORTED";
		case ErrorCode::UndefinedError:			return "Undefined error";
		default: throw GreatVEngine2::Exception("Unknown error code");
	}
}
void GreatVEngine2::OpenIL::ErrorTest(const ErrorCode& errorCode_)
{
	if (!IsSuccessful(errorCode_))
	{
		throw Exception(errorCode_);
	}
}
void GreatVEngine2::OpenIL::ErrorTest()
{
	auto errorCode = GetError(); // TODO: #if _DEBUG

	ErrorTest(errorCode);
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


