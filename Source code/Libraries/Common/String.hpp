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


