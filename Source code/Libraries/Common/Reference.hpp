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
	template<class Type_> class StrongPointer;		// can have many owners
	template<class Type_> class WeakPointer;		// can be casted to shared
	template<class Type_> class UserPointer;		// can't be deleted


	template<class DestinationType_, class SourceType_> StrongPointer<DestinationType_>	StaticCast(const StrongPointer<SourceType_>& source_);
	template<class DestinationType_, class SourceType_> StrongPointer<DestinationType_>	DynamicCast(const StrongPointer<SourceType_>& source_);
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

// UniquePointer
template<class Type_>	inline bool operator == (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_);
template<class Type_>	inline bool operator != (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_);
template<class Type_>	inline bool operator == (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_);
template<class Type_>	inline bool operator != (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_);

template<class Type_>	inline bool operator == (const GreatVEngine2::UniquePointer<Type_>& pointer_, const GreatVEngine2::Null&);
template<class Type_>	inline bool operator != (const GreatVEngine2::UniquePointer<Type_>& pointer_, const GreatVEngine2::Null&);
template<class Type_>	inline bool operator == (const GreatVEngine2::Null&, const GreatVEngine2::UniquePointer<Type_>& pointer_);
template<class Type_>	inline bool operator != (const GreatVEngine2::Null&, const GreatVEngine2::UniquePointer<Type_>& pointer_);


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
		Value						value = nullptr;
	public:
		inline						ConstantPointer() = default;
		inline explicit				ConstantPointer(const Null&);
		inline explicit				ConstantPointer(const Value& value_);
		inline						ConstantPointer(const ConstantPointer&) = delete;
		inline						ConstantPointer(ConstantPointer&& source_);
		inline						~ConstantPointer();
	public:
		inline ConstantPointer&		operator = (const Null&) = delete;
		inline ConstantPointer&		operator = (const ConstantPointer&) = delete;
		inline ConstantPointer&		operator = (ConstantPointer&&) = delete;
	public:
		inline const Value			operator -> () const;
		inline Value				operator -> ();
		inline const Type_&			operator * () const;
		inline Type_&				operator * ();
	public:
		inline bool					operator == (const ConstantPointer& source_) const;
		inline bool					operator != (const ConstantPointer& source_) const;
	public:
		inline operator				bool () const;
		inline explicit operator	Value () const;
	public:
		inline Value				GetValue() const;
	};
	template<class Type_> class UniquePointer:
		public Pointer<Type_>
	{
	public:
		using Value = Memory<Type_>;
	protected:
		Value						value = nullptr;
	public:
		inline						UniquePointer() = default;
		inline explicit				UniquePointer(const Null&);
		inline explicit				UniquePointer(const Value& value_);
		inline						UniquePointer(const UniquePointer&) = delete;
		inline						UniquePointer(UniquePointer&& source_);
		inline						~UniquePointer();
	public:
		inline UniquePointer&		operator = (const Null&);
		inline UniquePointer&		operator = (const UniquePointer&) = delete;
		inline UniquePointer&		operator = (UniquePointer&& source_);
	public:
		inline const Value			operator -> () const;
		inline Value				operator -> ();
		inline const Type_&			operator * () const;
		inline Type_&				operator * ();
	public:
		inline bool					operator == (const UniquePointer& source_) const;
		inline bool					operator != (const UniquePointer& source_) const;
	public:
		inline operator				bool () const;
		inline explicit operator	Value () const;
	public:
		inline Value				GetValue() const;
		inline void					Release();
	};
	template<class Type_> class SharedPointer: // basic for strong & weak pointers
		public Pointer<Type_>
	{
	public:
		using Value = Memory<Type_>;
		using Counter = Size;
	protected:
		class CommonReferenceHolder;
	protected:
		static Counter						nullCounter;
	protected:
		static inline Memory<Counter>		ObtainCounter(const Counter& counter_ = 0);
	protected:
		Value								value;
		Memory<Counter>						counter;
	protected:
		inline								SharedPointer() = delete;
		inline								SharedPointer(const Value& value_, const Memory<Counter>& counter_);
		inline								SharedPointer(const SharedPointer&) = delete;
		inline								SharedPointer(SharedPointer&&) = delete;
		inline								~SharedPointer() = default;
	protected:
		inline SharedPointer&				operator = (const SharedPointer&) = delete;
		inline SharedPointer&				operator = (SharedPointer&&) = delete;
	protected:
		inline void							IncreaseCounter();
		inline void							DecreaseCounter();
	public:
		inline Value						GetValue() const;
		inline Counter						GetCounter() const;
		inline void							Release();
	};
	template<class Type_> class StrongPointer:
		public SharedPointer<Type_>
	{
	public:
		friend WeakPointer<Type_>;
		template<class DestinationType_, class SourceType_> friend StrongPointer<DestinationType_> StaticCast(const StrongPointer<SourceType_>& source_);
		template<class DestinationType_, class SourceType_> friend StrongPointer<DestinationType_> DynamicCast(const StrongPointer<SourceType_>& source_);
	protected:
		inline											StrongPointer(const Value& value_, const Memory<Counter>& counter_);
	public:
		inline											StrongPointer();
		inline explicit									StrongPointer(const Null&);
		inline explicit									StrongPointer(const Value& value_);
		inline explicit									StrongPointer(const WeakPointer<Type_>& source_);
		template<class DerivedType_> inline explicit	StrongPointer(const StrongPointer<DerivedType_>& source_);
		inline											StrongPointer(const StrongPointer& source_);
		inline											StrongPointer(StrongPointer&& source_);
		inline											~StrongPointer();
	public:
		inline StrongPointer&							operator = (const Null&);
		inline StrongPointer&							operator = (const StrongPointer& source_);
		inline StrongPointer&							operator = (const WeakPointer<Type_>& source_);
		inline StrongPointer&							operator = (StrongPointer&& source_);
	public:
		inline const Value								operator -> () const;
		inline Value									operator -> ();
		inline const Type_&								operator * () const;
		inline Type_&									operator * ();
	public:
		inline operator									bool () const;
		inline explicit operator						Value () const;
	};
	template<class Type_> class WeakPointer:
		public SharedPointer<Type_>
	{
	public:
		friend StrongPointer<Type_>;
	protected:
		inline					WeakPointer(const Value& value_, const Memory<Counter>& counter_);
	public:
		inline					WeakPointer();
		inline explicit			WeakPointer(const Null&);
		inline explicit			WeakPointer(const StrongPointer<Type_>& source_);
		inline					WeakPointer(const WeakPointer& source_);
		inline					WeakPointer(WeakPointer&& source_);
		inline					~WeakPointer() = default;
	public:
		inline WeakPointer&		operator = (const Null&);
		inline WeakPointer&		operator = (const StrongPointer<Type_>& source_);
		inline WeakPointer&		operator = (const WeakPointer& source_);
		inline WeakPointer&		operator = (WeakPointer&& source_);
	// public:
	// 	inline const Value		operator -> () const;
	// 	inline Value			operator -> ();
	};


	template<class Type_> class SharedPointer<Type_>::CommonReferenceHolder
	{
	public:
		using Value									= typename SharedPointer<Type_>;
		using Counter								= Size;
	public:
		static inline Memory<CommonReferenceHolder>	Obtain(const Value& value_)
		{
			return new CommonReferenceHolder(value_);
		}
	protected:
		Value										value;
		Counter										counter;
	protected:
		inline										CommonReferenceHolder() = delete;
		inline										CommonReferenceHolder(const Value& value_, const Counter& counter_ = 0):
			value(value_), counter(counter_)
		{
		}
		inline										CommonReferenceHolder(const CommonReferenceHolder&) = delete;
		inline										CommonReferenceHolder(CommonReferenceHolder&&) = delete;
		virtual										~CommonReferenceHolder()
		{
			delete value; // okay to delete nullptr
		}
	protected:
		inline CommonReferenceHolder&				operator = (const CommonReferenceHolder&) = delete;
		inline CommonReferenceHolder&				operator = (CommonReferenceHolder&&) = delete;
	public:
		inline void									IncreaseCounter()
		{
			++counter;
		}
		inline void									DecreaseCounter()
		{
			--counter;

			if (counter == 0)
			{
				delete this; // suicide
			}
		}
		inline void									Release()
		{
			value = nullptr;
		}
	public:
		inline Value								GetValue() const
		{
			return value;
		}
		inline Counter								GetCounter() const
		{
			return counter;
		}
	};


	template<class Type_, class... Arguments> inline ConstantPointer<Type_>						MakeConstant(Arguments&&... arguments_);
	template<class Type_> inline ConstantPointer<Type_>											MakeConstant();
	template<class Type_, class... Arguments> inline UniquePointer<Type_>						MakeUnique(Arguments&&... arguments_);
	template<class Type_> inline UniquePointer<Type_>											MakeUnique();
	template<class Type_, class... Arguments> inline StrongPointer<Type_>						MakeStrong(Arguments&&... arguments_);
	template<class Type_> inline StrongPointer<Type_>											MakeStrong();
	template<class Type_> inline StrongPointer<Type_>											MakeStrong(const WeakPointer<Type_>& source_);
	template<class Type_> inline WeakPointer<Type_>												MakeWeak(const StrongPointer<Type_>& source_);
}


#pragma region GreatVEngine2

#pragma region ConstantPointer

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
inline GreatVEngine2::UniquePointer<Type_>::UniquePointer(const Null&):
	UniquePointer(static_cast<Value>(nullptr))
{
}
template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::UniquePointer(const Value& value_):
	Pointer(),
	value(value_)
{
}
template<class Type_>
inline GreatVEngine2::UniquePointer<Type_>::UniquePointer(UniquePointer&& source_):
	UniquePointer(source_.value)
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

template<class Type_>
typename GreatVEngine2::SharedPointer<Type_>::Counter GreatVEngine2::SharedPointer<Type_>::nullCounter = 1;

template<class Type_>
inline GreatVEngine2::Memory<typename GreatVEngine2::SharedPointer<Type_>::Counter> GreatVEngine2::SharedPointer<Type_>::ObtainCounter(const Counter& counter_)
{
	return new Counter(counter_);
}

template<class Type_>
inline GreatVEngine2::SharedPointer<Type_>::SharedPointer(const Value& value_, const Memory<Counter>& counter_):
	value(value_),
	counter(counter_)
{
}

template<class Type_>
inline void GreatVEngine2::SharedPointer<Type_>::IncreaseCounter()
{
	++(*counter);
}
template<class Type_>
inline void GreatVEngine2::SharedPointer<Type_>::DecreaseCounter()
{
	--(*counter);

	if (*counter == 0)
	{
		delete value;
		delete counter;
	}
}
template<class Type_>
inline typename GreatVEngine2::SharedPointer<Type_>::Value GreatVEngine2::SharedPointer<Type_>::GetValue() const
{
	return value;
}
template<class Type_>
inline typename GreatVEngine2::SharedPointer<Type_>::Counter GreatVEngine2::SharedPointer<Type_>::GetCounter() const
{
	return *counter;
}
template<class Type_>
inline void GreatVEngine2::SharedPointer<Type_>::Release()
{
	if (value)
	{
		if (counter == 1)
		{
			value = nullptr;

			delete counter; // value != nullptr, thus counter != &nullCounter

			counter = &nullCounter;
		}
		else
		{
			throw 5; // TODO
		}
	}
}

#pragma endregion

#pragma region StrongPointer

template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(const Value& value_, const Memory<Counter>& counter_):
	SharedPointer(value_, counter_)
{
	IncreaseCounter();
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer():
	StrongPointer(nullptr)
{
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(const Null&):
	StrongPointer(nullptr, &nullCounter)
{
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(const Value& value_):
	StrongPointer(value_, ObtainCounter())
{
}
template<class Type_> template<class DerivedType_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(const StrongPointer<DerivedType_>& source_):
	StrongPointer(Move(StaticCast<Type_>(source_)))
{
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(const WeakPointer<Type_>& source_):
	StrongPointer(source_.value, source_.counter)
{
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(const StrongPointer& source_):
	StrongPointer(source_.value, source_.counter)
{
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::StrongPointer(StrongPointer&& source_):
	SharedPointer(source_.value, source_.counter)
{
	source_.value = nullptr;
	source_.counter = &nullCounter;
	
	source_.IncreaseCounter();
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::~StrongPointer()
{
	DecreaseCounter();
}

template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>& GreatVEngine2::StrongPointer<Type_>::operator = (const Null&)
{
	DecreaseCounter();

	value = nullptr;
	counter = &nullCounter;

	IncreaseCounter();

	return *this;
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>& GreatVEngine2::StrongPointer<Type_>::operator = (const WeakPointer<Type_>& source_)
{
	DecreaseCounter();
	
	value = source_.value;
	counter = source_.counter;

	IncreaseCounter();

	return *this;
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>& GreatVEngine2::StrongPointer<Type_>::operator = (const StrongPointer& source_)
{
	DecreaseCounter();

	value = source_.value;
	counter = source_.counter;

	IncreaseCounter();

	return *this;
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>& GreatVEngine2::StrongPointer<Type_>::operator = (StrongPointer&& source_)
{
	DecreaseCounter();

	value = source_.value;
	counter = source_.counter;

	source_.value = nullptr;
	source_.counter = &nullCounter;

	source_.IncreaseCounter();

	return *this;
}

template<class Type_>
inline typename const GreatVEngine2::StrongPointer<Type_>::Value GreatVEngine2::StrongPointer<Type_>::operator -> () const
{
	return value;
}
template<class Type_>
inline typename GreatVEngine2::StrongPointer<Type_>::Value GreatVEngine2::StrongPointer<Type_>::operator -> ()
{
	return value;
}
template<class Type_>
inline const Type_& GreatVEngine2::StrongPointer<Type_>::operator * () const
{
	return *value; // TODO: check != nullptr
}
template<class Type_>
inline Type_& GreatVEngine2::StrongPointer<Type_>::operator * ()
{
	return *value; // TODO: check != nullptr
}

template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::operator bool() const
{
	return static_cast<bool>(value);
}
template<class Type_>
inline GreatVEngine2::StrongPointer<Type_>::operator Value() const
{
	return value;
}

#pragma endregion

#pragma region WeakPointer

template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>::WeakPointer(const Value& value_, const Memory<Counter>& counter_):
	SharedPointer(value_, counter_)
{
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>::WeakPointer():
	WeakPointer(nullptr)
{
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>::WeakPointer(const Null&):
	WeakPointer(nullptr, &nullCounter)
{
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>::WeakPointer(const StrongPointer<Type_>& source_):
	WeakPointer(source_.value, source_.counter)
{
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>::WeakPointer(const WeakPointer& source_):
	WeakPointer(source_.value, source_.counter)
{
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>::WeakPointer(WeakPointer&& source_):
	WeakPointer(source_.value, source_.counter)
{
	source_.value = nullptr;
	source_.counter = &nullCounter;
}

template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>& GreatVEngine2::WeakPointer<Type_>::operator = (const Null&)
{
	value = nullptr;
	counter = &nullCounter;

	return *this;
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>& GreatVEngine2::WeakPointer<Type_>::operator = (const StrongPointer<Type_>& source_)
{
	value = source_.value;
	counter = source_.counter;

	return *this;
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>& GreatVEngine2::WeakPointer<Type_>::operator = (const WeakPointer& source_)
{
	value = source_.value;
	counter = source_.counter;

	return *this;
}
template<class Type_>
inline GreatVEngine2::WeakPointer<Type_>& GreatVEngine2::WeakPointer<Type_>::operator = (WeakPointer&& source_)
{
	value = source_.value;
	counter = source_.counter;

	source_.value = nullptr;
	source_.counter = &nullCounter;

	return *this;
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
inline typename GreatVEngine2::StrongPointer<Type_> GreatVEngine2::MakeStrong<Type_>(Arguments&&... arguments)
{
	return StrongPointer<Type_>(new Type_(Forward<Arguments>(arguments)...));
}
template<class Type_>
inline typename GreatVEngine2::StrongPointer<Type_> GreatVEngine2::MakeStrong<Type_>()
{
	return StrongPointer<Type_>(new Type_());
}
template<class Type_>
inline typename GreatVEngine2::StrongPointer<Type_> GreatVEngine2::MakeStrong<Type_>(const WeakPointer<Type_>& source_)
{
	return Move(StrongPointer<Type_>(source_));
}

template<class Type_>
inline typename GreatVEngine2::WeakPointer<Type_> GreatVEngine2::MakeWeak<Type_>(const StrongPointer<Type_>& source_)
{
	return Move(WeakPointer<Type_>(source_));
}


template<class DestinationType_, class SourceType_>
typename GreatVEngine2::StrongPointer<DestinationType_> GreatVEngine2::StaticCast<DestinationType_, SourceType_>(const StrongPointer<SourceType_>& source_)
{
	auto castedValue = static_cast<typename StrongPointer<DestinationType_>::Value>(source_.value);
	
	return StrongPointer<DestinationType_>(castedValue, source_.counter);
}
template<class DestinationType_, class SourceType_>
typename GreatVEngine2::StrongPointer<DestinationType_> GreatVEngine2::DynamicCast<DestinationType_, SourceType_>(const StrongPointer<SourceType_>& source_)
{
	auto castedValue = dynamic_cast<typename StrongPointer<DestinationType_>::Value>(source_.value);

	return castedValue
		? StrongPointer<DestinationType_>(castedValue, source_.counter)
		: StrongPointer<DestinationType_>(nullptr);
}

#pragma endregion


// ConstantPointer
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


// UniquePointer
template<class Type_>
inline bool operator == (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_)
{
	return pointer_.GetValue() == value_;
}
template<class Type_>
inline bool operator != (const GreatVEngine2::UniquePointer<Type_>& pointer_, const typename GreatVEngine2::UniquePointer<Type_>::Value& value_)
{
	return pointer_.GetValue() != value_;
}
template<class Type_>
inline bool operator == (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_)
{
	return pointer_ == value_;
}
template<class Type_>
inline bool operator != (const typename GreatVEngine2::UniquePointer<Type_>::Value& value_, const GreatVEngine2::UniquePointer<Type_>& pointer_)
{
	return pointer_ != value_;
}

template<class Type_>
inline bool operator == (const GreatVEngine2::UniquePointer<Type_>& pointer_, const GreatVEngine2::Null&)
{
	return pointer_.GetValue() == nullptr;
}
template<class Type_>
inline bool operator != (const GreatVEngine2::UniquePointer<Type_>& pointer_, const GreatVEngine2::Null&)
{
	return pointer_.GetValue() != nullptr;
}
template<class Type_>
inline bool operator == (const GreatVEngine2::Null&, const GreatVEngine2::UniquePointer<Type_>& pointer_)
{
	return nullptr == pointer_.GetValue();
}
template<class Type_>
inline bool operator != (const GreatVEngine2::Null&, const GreatVEngine2::UniquePointer<Type_>& pointer_)
{
	return nullptr != pointer_.GetValue();
}


#pragma region
#pragma endregion


