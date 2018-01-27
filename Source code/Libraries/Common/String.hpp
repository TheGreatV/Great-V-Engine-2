#pragma region Include

#pragma once

#include "Header.hpp"
#include "Size.hpp"
#include "Move.hpp"

#include <string>

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	using String = std::string;
	using WideString = std::wstring;


	inline String ToString(const Size& value_);
	inline bool Has(const String& source_, const String& value_)
	{
		return source_.find(value_) != String::npos;
	}
}


#pragma region GreatVEngine2

GreatVEngine2::String GreatVEngine2::ToString(const Size& value_)
{
	auto string = std::to_string(value_);

	return Move(string);
}

#pragma endregion


#pragma region
#pragma endregion


