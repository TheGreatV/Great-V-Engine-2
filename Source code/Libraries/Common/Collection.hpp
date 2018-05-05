#pragma region Include

#pragma once

#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <initializer_list>

#include "Header.hpp"
#include "Size.hpp"
#include "Move.hpp"

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
	template<class Type_> using					Queue = std::queue<Type_>;
	template<class Type_> using					Initializer = std::initializer_list<Type_>;


	template <typename T> Vector<T> operator + (const Vector<T>& a_, const Vector<T>& b_)
	{
		Vector<T> ab;

		ab.reserve(a_.size() + b_.size());
		ab.insert(ab.end(), a_.begin(), a_.end());
		ab.insert(ab.end(), b_.begin(), b_.end());

		return Move(ab);
	}
	template <typename T> Vector<T> operator + (const Vector<T>& a_, const T& b_)
	{
		Vector<T> ab;

		ab.reserve(a_.size() + 1);
		ab.insert(ab.end(), a_.begin(), a_.end());
		ab.push_back(b_);

		return Move(ab);
	}


	template<class Type_, class Predicate_> Vector<Type_> Filter(const Vector<Type_>& source_, Predicate_ predicate_)
	{
		Vector<Type_> output;

		for (auto &value : source_)
		{
			if (predicate_(value))
			{
				output.push_back(value);
			}
		}

		return Move(output);
	}
	template<class Result_, class Type_> Vector<typename Result_> Transform(const Vector<Type_>& source_, typename Result_ functor_(const typename Type_&))
	{
		Vector<Result_> output;

		for (auto &value : source_)
		{
			output.push_back(functor_(value));
		}
		
		return Move(output);
	}
}


#pragma region GreatVEngine2

#pragma endregion


#pragma region
#pragma endregion


