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
	template<class Type_> class Pointer;			// base class
	template<class Type_> class ConstantPointer;	// can't be changed (without overhead)
	template<class Type_> class UniquePointer;		// can't have more than one owner
	template<class Type_> class SharedPointer;		// can have many owners
	template<class Type_> class UserPointer;		// can't be deleted
}


// ConstantPointer
template<class Type_>	inline bool operator == (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_);
template<class Type_>	inline bool operator != (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_);
template<class Type_>	inline bool operator == (const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_, const GreatVEngine2::ConstantPointer<Type_>& pointer_);
template<class Type_>	inline bool operator != (const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_, const GreatVEngine2::ConstantPointer<Type_>& pointer_);

template<class Type_>	inline bool operator == (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const GreatVEngine2::Null&);
template<class Type_>	inline bool operator != (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const GreatVEngine2::Null&);
template<class Type_>	inline bool operator == (const GreatVEngine2::Null&, const GreatVEngine2::ConstantPointer<Type_>& pointer_);
template<class Type_>	inline bool operator != (const GreatVEngine2::Null&, const GreatVEngine2::ConstantPointer<Type_>& pointer_);

// Unique Pointer
template<class Type_>	inline bool operator == (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_);
template<class Type_>	inline bool operator == (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_);
template<class Type_>	inline bool operator != (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_);
template<class Type_>	inline bool operator != (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_);


namespace GreatVEngine2
{
	template<class Type_> class Pointer
	{
	public:
		using Value = Memory<Type_>;
	};
	template<class Type_> class ConstantPointer:
		public Pointer<Type_>
	{
	protected:
		Value					value = nullptr;
	public:
		inline					ConstantPointer() = default;
		inline explicit			ConstantPointer(const Null&);
		inline explicit			ConstantPointer(const Value& value_);
		inline					ConstantPointer(const ConstantPointer&) = delete;
		inline					ConstantPointer(ConstantPointer&& source_);
		inline					~ConstantPointer();
	public:
		inline ConstantPointer&	operator = (const Null&) = delete;
		inline ConstantPointer& operator = (const ConstantPointer&) = delete;
		inline ConstantPointer& operator = (ConstantPointer&&) = delete;
	public:
		inline const Value		operator -> () const;
		inline Value			operator -> ();
		inline const Type_&		operator * () const;
		inline Type_&			operator * ();
	public:
		inline bool				operator == (const ConstantPointer& source_) const;
		inline bool				operator != (const ConstantPointer& source_) const;
	public:
		inline operator			bool () const;
		inline operator			Value () const;
	public:
		inline Value			GetValue() const;
		// TODO?: inline void				Release();
	};
	template<class Type_> class UniquePointer
		// TODO: inherit Pointer
	{
	public:
		using Value = Memory<Type_>;
	protected:
		Value					value = nullptr;
	public:
		inline					UniquePointer() = default;
		inline explicit			UniquePointer(const Null&);
		inline explicit			UniquePointer(const Value& value_);
		inline					UniquePointer(const UniquePointer&) = delete;
		inline					UniquePointer(UniquePointer&& source_);
		inline					~UniquePointer();
	public:
		inline UniquePointer&	operator = (const Null&);
		inline UniquePointer&	operator = (const UniquePointer&) = delete;
		inline UniquePointer&	operator = (UniquePointer&& source_);
	public:
		inline const Value		operator -> () const;
		inline Value			operator -> ();
		inline const Type_&		operator * () const;
		inline Type_&			operator * ();
	public:
		inline bool				operator == (const UniquePointer& source_) const;
		inline bool				operator != (const UniquePointer& source_) const;
		inline bool				operator == (const Null&) const;
		inline bool				operator != (const Null&) const;
	public:
		inline operator			bool () const;
		inline operator			Value () const;
	public:
		inline Value			GetValue() const;
		inline void				Release();
	};
	template<class Type_> class SharedPointer
	{
	public:
		using Value = Memory<Type_>;
	protected:
		class Holder;
	protected:
		Memory<Holder> holder = nullptr;
	protected:
		inline SharedPointer(const Memory<Holder>& holder_);
	public:
		inline SharedPointer() = default;
		inline SharedPointer(const Null&);
		inline SharedPointer(const Value& value_);
		inline SharedPointer(const SharedPointer& source_);
		inline SharedPointer(SharedPointer&& source_);
		inline ~SharedPointer();
	public:
		inline SharedPointer& operator = (const Null&);
		inline SharedPointer& operator = (const SharedPointer& source_);
		inline SharedPointer& operator = (SharedPointer&& source_);
	public:
		inline const Value		operator -> () const;
		inline Value			operator -> ();
	public:
		inline Value			GetValue() const;
		// TODO: inline void				Release();
	};

	template<class Type_>
	class GreatVEngine2::SharedPointer<Type_>::Holder
	{
	public:
		using Value = typename SharedPointer::Value;
		using Counter = Size;
	public:
		// TODO: protect new/delete operators
		static inline Memory<Holder> Obtain(const Value& value_);
	protected:
		const Value value;
		Counter counter;
	protected:
		inline Holder() = delete;
		inline Holder(const Value& value_);
		inline Holder(const Holder&) = delete;
		inline Holder(Holder&&) = delete;
		inline ~Holder();
	protected:
		inline Holder& operator = (const Holder&) = delete;
		inline Holder& operator = (Holder&&) = delete;
	public:
		inline void IncreaseCounter();
		inline void DecreaseCounter();
		inline Value GetValue() const;
	};


	template<class Type_, class... Arguments> inline ConstantPointer<Type_>		MakeConstant(Arguments&&... arguments);
	template<class Type_> inline ConstantPointer<Type_>							MakeConstant();
	template<class Type_, class... Arguments> inline UniquePointer<Type_>		MakeUnique(Arguments&&... arguments);
	template<class Type_> inline UniquePointer<Type_>							MakeUnique();
	template<class Type_, class... Arguments> inline SharedPointer<Type_>		MakeShared(Arguments&&... arguments);
	template<class Type_> inline SharedPointer<Type_>							MakeShared();
}


#pragma region GreatVEngine2

#pragma region ConstantPointer

template<class Type_>
inline bool operator == (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_)
{
	return pointer_.GetValue() == value_;
}
template<class Type_>
inline bool operator != (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_)
{
	return pointer_.GetValue() != value_;
}
template<class Type_>
inline bool operator == (const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_, const GreatVEngine2::ConstantPointer<Type_>& pointer_)
{
	return pointer_ == value_;
}
template<class Type_>
inline bool operator != (const typename GreatVEngine2::ConstantPointer<Type_>::Value& value_, const GreatVEngine2::ConstantPointer<Type_>& pointer_)
{
	return pointer_ != value_;
}

template<class Type_>
inline bool operator == (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const GreatVEngine2::Null&)
{
	return pointer_.GetValue() == nullptr;
}
template<class Type_>
inline bool operator != (const GreatVEngine2::ConstantPointer<Type_>& pointer_, const GreatVEngine2::Null&)
{
	return pointer_.GetValue() != nullptr;
}
template<class Type_>
inline bool operator == (const GreatVEngine2::Null&, const GreatVEngine2::ConstantPointer<Type_>& pointer_)
{
	return nullptr == pointer_.GetValue();
}
template<class Type_>
inline bool operator != (const GreatVEngine2::Null&, const GreatVEngine2::ConstantPointer<Type_>& pointer_)
{
	return nullptr != pointer_.GetValue();
}


template<class Type_>
inline GreatVEngine2::ConstantPointer<Type_>::ConstantPointer(const Null&):
	ConstantPointer()
{
}
template<class Type_>
inline GreatVEngine2::ConstantPointer<Type_>::ConstantPointer(const Value& value_):
	Pointer(),
	value(value_)
{
}
template<class Type_>
inline GreatVEngine2::ConstantPointer<Type_>::ConstantPointer(ConstantPointer&& source_):
	ConstantPointer(source_.value)
{
	source_.value = nullptr;
}
template<class Type_>
inline GreatVEngine2::ConstantPointer<Type_>::~ConstantPointer()
{
	delete value; // it is OK to delete nullptr
}

template<class Type_>
inline typename const GreatVEngine2::ConstantPointer<Type_>::Value GreatVEngine2::ConstantPointer<Type_>::operator -> () const
{
	return value;
}
template<class Type_>
inline typename GreatVEngine2::ConstantPointer<Type_>::Value GreatVEngine2::ConstantPointer<Type_>::operator -> ()
{
	return value;
}
template<class Type_>
inline const Type_& GreatVEngine2::ConstantPointer<Type_>::operator * () const
{
	return *value;
}
template<class Type_>
inline Type_& GreatVEngine2::ConstantPointer<Type_>::operator * ()
{
	return *value;
}

template<class Type_>
inline bool GreatVEngine2::ConstantPointer<Type_>::operator == (const ConstantPointer& source_) const
{
	return value == source_.value;
}
template<class Type_>
inline bool GreatVEngine2::ConstantPointer<Type_>::operator != (const ConstantPointer& source_) const
{
	return value != source_.value;
}

template<class Type_>
inline GreatVEngine2::ConstantPointer<Type_>::operator bool() const
{
	return value != nullptr;
}
template<class Type_>
inline GreatVEngine2::ConstantPointer<Type_>::operator Value() const
{
	return value;
}

template<class Type_>
inline typename GreatVEngine2::ConstantPointer<Type_>::Value GreatVEngine2::ConstantPointer<Type_>::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region UniquePointer

template<class Type_>
inline bool operator == (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_)
{
	return pointer_.GetValue() == value_;
}
template<class Type_>
inline bool operator == (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_)
{
	return pointer_ == value_;
}
template<class Type_>
inline bool operator != (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_)
{
	return pointer_.GetValue() != value_;
}
template<class Type_>
inline bool operator != (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_)
{
	return pointer_ != value_;
}

template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::UniquePointer(const Null&):
	value(nullptr)
{
}
template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::UniquePointer(const Value& value_):
	value(value_)
{
}
template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::UniquePointer(UniquePointer&& source_) :
	value(source_.value)
{
	source_.value = nullptr;
}
template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::~UniquePointer()
{
	delete value; // delete nullptr is okay
}

template<class Type_>
inline typename GreatVEngine2::UniquePointer<Type_>& GreatVEngine2::UniquePointer<Type_>::operator = (const Null&)
{
	delete value; // it is okay to delete nullptr

	value = nullptr;

	return *this;
}
template<class Type_>
inline typename GreatVEngine2::UniquePointer<Type_>& GreatVEngine2::UniquePointer<Type_>::operator = (UniquePointer&& source_)
{
	delete value; // it is okay to delete nullptr

	value = source_.value;
	source_.value = nullptr;

	return *this;
}

template<class Type_>
inline typename const GreatVEngine2::UniquePointer<Type_>::Value GreatVEngine2::UniquePointer<Type_>::operator -> () const
{
	return value;
}
template<class Type_>
inline typename GreatVEngine2::UniquePointer<Type_>::Value GreatVEngine2::UniquePointer<Type_>::operator -> ()
{
	return value;
}
template<class Type_>
inline const Type_& GreatVEngine2::UniquePointer<Type_>::operator * () const
{
	return *value;
}
template<class Type_>
inline Type_& GreatVEngine2::UniquePointer<Type_>::operator * ()
{
	return *value;
}

template<class Type_>
inline bool GreatVEngine2::UniquePointer<Type_>::operator == (const UniquePointer& source_) const
{
	return value == source_.value;
}
template<class Type_>
inline bool GreatVEngine2::UniquePointer<Type_>::operator != (const UniquePointer& source_) const
{
	return value != source_.value;
}
template<class Type_>
inline bool GreatVEngine2::UniquePointer<Type_>::operator == (const Null&) const
{
	return value == nullptr;
}
template<class Type_>
inline bool GreatVEngine2::UniquePointer<Type_>::operator != (const Null&) const
{
	return value != nullptr;
}

template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::operator bool() const
{
	return value != nullptr;
}
template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::operator Value() const
{
	return value;
}

template<class Type_>
inline typename GreatVEngine2::UniquePointer<Type_>::Value GreatVEngine2::UniquePointer<Type_>::GetValue() const
{
	return value;
}
template<class Type_>
inline void GreatVEngine2::UniquePointer<Type_>::Release()
{
	value = nullptr;
}

#pragma endregion

#pragma region SharedPointer

#pragma region Holder

template<class Type_>
inline GreatVEngine2::Memory<typename GreatVEngine2::SharedPointer<Type_>::Holder> GreatVEngine2::SharedPointer<Type_>::Holder::Obtain(const Value& value_)
{
	auto holder = new Holder(value_);

	return holder;
}

template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::Holder::Holder(const Value& value_):
	value(value_),
	counter(1)
{
}
template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::Holder::~Holder()
{
	delete value; // it is okay to delete nullptr
}

template<class Type_>
inline void GreatVEngine2::SharedPointer<Type_>::Holder::IncreaseCounter()
{
	++counter;
}
template<class Type_>
inline void GreatVEngine2::SharedPointer<Type_>::Holder::DecreaseCounter()
{
	--counter;

	if (counter == 0)
	{
		delete this; // suicide
	}
}
template<class Type_>
inline typename GreatVEngine2::SharedPointer<Type_>::Holder::Value GreatVEngine2::SharedPointer<Type_>::Holder::GetValue() const
{
	return value;
}


#pragma endregion


template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::SharedPointer(const Memory<Holder>& holder_):
	holder(holder_)
{
}
template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::SharedPointer(const Null& ):
	SharedPointer()
{
}
template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::SharedPointer(const Value& value_):
	SharedPointer(Holder::Obtain(value_))
{
}
template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::SharedPointer(const SharedPointer& source_):
	SharedPointer(source_.holder)
{
	if (holder)
	{
		holder->IncreaseCounter();
	}
}
/*template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::SharedPointer(SharedPointer&& source_)
{
	// TODO
}*/
template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::~SharedPointer()
{
	if (holder)
	{
		holder->DecreaseCounter();
	}
}
template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>& GreatVEngine2::SharedPointer<Type_>::operator = (const Null&)
{
	holder->DecreaseCounter();
	
	holder = nullptr;

	return *this;
}
/*template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>& GreatVEngine2::SharedPointer<Type_>::operator = (const SharedPointer& source_)
{
	// TODO

	return *this;
}*/
/*template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>& GreatVEngine2::SharedPointer<Type_>::operator = (SharedPointer&& source_)
{
	// TODO

	return *this;
}*/
template<class Type_>
inline typename const GreatVEngine2::SharedPointer<Type_>::Value GreatVEngine2::SharedPointer<Type_>::operator -> () const
{
	return holder->GetValue(); // TODO: check != nullptr
}
template<class Type_>
inline typename GreatVEngine2::SharedPointer<Type_>::Value GreatVEngine2::SharedPointer<Type_>::operator -> ()
{
	return holder->GetValue(); // TODO: check != nullptr
}
template<class Type_>
inline typename GreatVEngine2::SharedPointer<Type_>::Value GreatVEngine2::SharedPointer<Type_>::GetValue() const
{
	return holder
		? holder->GetValue()
		: nullptr;
}

#pragma endregion


template<class Type_, class... Arguments>
inline typename GreatVEngine2::ConstantPointer<Type_> GreatVEngine2::MakeConstant<Type_>(Arguments&&... arguments)
{
	return ConstantPointer<Type_>(new Type_(Forward<Arguments>(arguments)...));
}
template<class Type_>
inline typename GreatVEngine2::ConstantPointer<Type_> GreatVEngine2::MakeConstant<Type_>()
{
	return ConstantPointer<Type_>(new Type_());
}

template<class Type_, class... Arguments>
inline typename GreatVEngine2::UniquePointer<Type_> GreatVEngine2::MakeUnique<Type_>(Arguments&&... arguments)
{
	return UniquePointer<Type_>(new Type_(Forward<Arguments>(arguments)...));
}
template<class Type_>
inline typename GreatVEngine2::UniquePointer<Type_> GreatVEngine2::MakeUnique<Type_>()
{
	return UniquePointer<Type_>(new Type_());
}

template<class Type_, class... Arguments>
inline typename GreatVEngine2::SharedPointer<Type_> GreatVEngine2::MakeShared<Type_>(Arguments&&... arguments)
{
	return SharedPointer<Type_>(new Type_(Forward<Arguments>(arguments)...));
}
template<class Type_>
inline typename GreatVEngine2::SharedPointer<Type_> GreatVEngine2::MakeShared<Type_>()
{
	return SharedPointer<Type_>(new Type_());
}

#pragma endregion


#pragma region
#pragma endregion


