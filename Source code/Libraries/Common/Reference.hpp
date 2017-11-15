#pragma region Include

#pragma once

#include <cstdlib>

#include "Header.hpp"
#include "Size.hpp"
#include "Memory.hpp"
#include "Move.hpp"

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	template<class Type> class UniquePointer;


	template<class Type> class UniquePointer
	{
	public:
		using Value = Type*;
	protected:
		Value					value = nullptr;
	public:
		inline					UniquePointer() = default;
		inline					UniquePointer(const Value& value_);
		inline					UniquePointer(const UniquePointer&) = delete;
		inline					UniquePointer(UniquePointer&& source_);
		inline					~UniquePointer();
	public:
		inline UniquePointer&	operator = (const UniquePointer&) = delete;
		inline UniquePointer&	operator = (UniquePointer&& source_);
	public:
		inline const Value		operator -> () const;
		inline Value			operator -> ();
	public:
		inline Value			GetValue() const;
		inline void				Release();
	};


	template<class Type, class... Arguments> inline UniquePointer<Type>		MakeUnique(Arguments&&... arguments);
	template<class Type> inline	UniquePointer<Type>							MakeUnique();
}


#pragma region GreatVEngine2

#pragma region UniquePointer

template<class Type>
inline GreatVEngine2::UniquePointer<Type>::UniquePointer(const Value& value_):
	value(value_)
{
}
template<class Type>
inline GreatVEngine2::UniquePointer<Type>::UniquePointer(UniquePointer&& source_) :
	value(source_.value)
{
	source_.value = nullptr;
}
template<class Type>
inline GreatVEngine2::UniquePointer<Type>::~UniquePointer()
{
	delete value; // delete nullptr is okay
}
template<class Type>
inline typename GreatVEngine2::UniquePointer<Type>& GreatVEngine2::UniquePointer<Type>::operator = (UniquePointer&& source_)
{
	delete value; // it is okay to delete nullptr

	value = source_.value;
	source_.value = nullptr;

	return *this;
}
template<class Type>
inline typename const GreatVEngine2::UniquePointer<Type>::Value GreatVEngine2::UniquePointer<Type>::operator -> () const
{
	return value;
}
template<class Type>
inline typename GreatVEngine2::UniquePointer<Type>::Value GreatVEngine2::UniquePointer<Type>::operator -> ()
{
	return value;
}
template<class Type>
inline typename GreatVEngine2::UniquePointer<Type>::Value GreatVEngine2::UniquePointer<Type>::GetValue() const
{
	return value;
}
template<class Type>
inline void GreatVEngine2::UniquePointer<Type>::Release()
{
	value = nullptr;
}

#pragma endregion


template<class Type, class... Arguments>
inline typename GreatVEngine2::UniquePointer<Type> GreatVEngine2::MakeUnique<Type>(Arguments&&... arguments)
{
	return UniquePointer<Type>(new Type(std::forward<Arguments>(arguments)...));
}
template<class Type>
inline typename GreatVEngine2::UniquePointer<Type> GreatVEngine2::MakeUnique<Type>()
{
	return UniquePointer<Type>(new Type());
}

#pragma endregion


#pragma region
#pragma endregion


