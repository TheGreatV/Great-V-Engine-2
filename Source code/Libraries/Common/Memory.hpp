#pragma region Include

#pragma once

#include <cstdlib>

#include "Header.hpp"
#include "Size.hpp"

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	template<class Type> using Memory = Type*;


	template<class Type> inline Memory<Type>	AllocateMemory(const Size& size_);
	template<class Type> inline void			ReleaseMemory(const Memory<Type>& memory_);
	template<class Type> inline void			CopyMemory(const Memory<Type>& destination_, const Memory<Type>& source_, const Size& amount_);
	template<class Type> inline bool			CompareMemory(const Memory<Type>& memory1_, const Memory<Type>& memory2_, const Size& amount_);
}


#pragma region GreatVEngine2

template<class Type>
inline GreatVEngine2::Memory<Type> GreatVEngine2::AllocateMemory(const Size& size_)
{
	auto memoryAmount = sizeof(Type) * size_;
	auto rawMemory = std::malloc(memoryAmount);
	auto memory = static_cast<Memory<Type>>(rawMemory);

	return memory;
}
template<class Type>
inline void GreatVEngine2::ReleaseMemory(const Memory<Type>& memory_)
{
	std::free(memory_);
}
template<class Type>
inline void GreatVEngine2::CopyMemory(const Memory<Type>& destination_, const Memory<Type>& source_, const Size& amount_)
{
	std::memcpy(destination_, source_, sizeof(Type)* amount_);
}
template<class Type>
inline bool GreatVEngine2::CompareMemory(const Memory<Type>& memory1_, const Memory<Type>& memory2_, const Size& amount_)
{
	auto rawCompareResult = std::memcmp(memory1_, memory2_, sizeof(Type) * amount_);

	return rawCompareResult == 0;
}

#pragma endregion


#pragma region
#pragma endregion


