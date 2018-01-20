#pragma region Include

#pragma once

#include "Header.hpp"
#include "String.hpp"

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	class Exception
	{
	public:
		using Text = String;
	protected:
		const Text text;
	public:
		inline Exception();
		inline Exception(const Text& text_);
	public:
		inline Text GetText() const;
	};
	class NotImplementedException:
		public Exception
	{
	public:
		inline NotImplementedException();
	};

}


#pragma region GreatVEngine2

#pragma region Exception

GreatVEngine2::Exception::Exception():
	Exception("Unknown exception.")
{
}
GreatVEngine2::Exception::Exception(const Text& text_):
	text(text_)
{
}
GreatVEngine2::Exception::Text GreatVEngine2::Exception::GetText() const
{
	return text;
}

#pragma endregion

#pragma region Exception

GreatVEngine2::NotImplementedException::NotImplementedException():
	Exception("Not implemented.")
{
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


