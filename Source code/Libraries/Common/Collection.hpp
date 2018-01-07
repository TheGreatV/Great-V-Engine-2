#pragma region Include

#pragma once

#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <initializer_list>

#include "Header.hpp"
#include "Size.hpp"

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	template<class Type1_, class Type2_> using	Pair = std::pair<Type1_, Type2_>;
	template<class Type_, Size Size_> using		Array = std::array<Type_, Size_>;
	template<class Type_> using					Vector = std::vector<Type_>;
	template<class Type_> using					List = std::list<Type_>;
	template<class Key_, class Value_> using	Map = std::map<Key_, Value_>;
	template<class Type_> using					Set = std::set<Type_>;
	template<class Type_> using					Initializer = std::initializer_list<Type_>;
}


#pragma region GreatVEngine2

#pragma endregion


#pragma region
#pragma endregion


