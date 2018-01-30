#pragma region Include

#pragma once

#include "Header.hpp"

#include <cstring>
#include <vector>

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	using Size = std::size_t;

	class Range:
		public std::vector<int>
	{
	protected:
		struct ZeroToLastTag
		{
		};
		struct FirstLastTag
		{
		};
	protected:
		inline Range(const int& count_, const ZeroToLastTag&): std::vector<int>(count_)
		{
			for (int i = 0; i < static_cast<int>(size()); ++i)
			{
				(*this)[i] = i;
			}
		}
		inline Range(const int& first_, const int& last_, const FirstLastTag&)
		{
			if (last_ > first_)
			{
				resize(last_ - first_);

				for (int i = 0; i < static_cast<int>(size()); ++i)
				{
					(*this)[i] = first_ + i;
				}
			}
			else
			{
				resize(first_ - last_);

				for (int i = 0; i < static_cast<int>(size()); ++i)
				{
					(*this)[i] = first_ - i;
				}
			}
		}
	public:
		inline Range(const int& count_): Range(count_, ZeroToLastTag())
		{
		}
		inline Range(const int& first_, const int& last_) : Range(first_, last_, FirstLastTag())
		{
		}
	};
}


#pragma region GreatVEngine2
#pragma endregion


#pragma region
#pragma endregion


