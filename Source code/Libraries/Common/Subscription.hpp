#pragma region Include

#pragma once

#include "Header.hpp"
#include "Collection.hpp"
#include "Reference.hpp"

#include <functional>

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	template<class Signature_> class Subscription
	{
	public:
		using Subscriber	= typename std::function<typename Signature_>;
		using Subscribers	= typename List<Subscriber>;
		using Iterator		= typename Subscribers::iterator;
	protected:
		class Holder
		{
		protected:
			Subscribers subscribers;
		public:
			inline Holder() = default;
			inline Holder(const Holder&) = delete;
			inline ~Holder() = default;
		public:
			inline Holder& operator = (const Holder&) = delete;
		public:
			inline Iterator Subscribe(const Subscriber& subscriber_)
			{
				const auto &it = subscribers.insert(subscribers.begin(), subscriber_);

				return it;
			}
			inline void Unsubscribe(const Iterator& iterator_)
			{
				subscribers.erase(iterator_);
			}
			template<class... Arguments_> inline void Invoke(Arguments_&&... arguments_)
			{
				auto toInvoke = subscribers;

				for (auto &subscriber : toInvoke)
				{
					subscriber(Forward<Arguments_&&>(arguments_)...);
				}
			}
		};
	public:
		class Unsubscriber
		{
		protected:
			StrongPointer<Holder> holder = StrongPointer<Holder>(nullptr);
			Iterator iterator;
		public:
			inline Unsubscriber() = default;
			inline Unsubscriber(const StrongPointer<Holder>& holder_, const Iterator& iterator_):
				holder(holder_),
				iterator(iterator_)
			{
			}
			inline Unsubscriber(const Unsubscriber&) = delete;
			inline Unsubscriber(Unsubscriber&& source_):
				holder(source_.holder),
				iterator(source_.iterator)
			{
				source_.holder = nullptr;
			}
			inline ~Unsubscriber()
			{
				if (holder)
				{
					holder->Unsubscribe(iterator);
				}
			}
		public:
			inline Unsubscriber& operator = (const Unsubscriber&) = delete;
			inline Unsubscriber& operator = (Unsubscriber&& source_)
			{
				if (holder)
				{
					holder->Unsubscribe(iterator);
				}

				holder		= source_.holder;
				iterator	= source_.iterator;
				
				source_.holder = nullptr;

				return *this;
			}
			inline Unsubscriber& operator = (const Null&)
			{
				if (holder)
				{
					holder->Unsubscribe(iterator);
				}

				holder = nullptr;

				return *this;
			}
		};
	protected:
		const StrongPointer<Holder> holder;
	public:
		inline Subscription():
			holder(MakeStrong<Holder>())
		{
		}
		inline Subscription(const Subscription&) = delete;
		inline ~Subscription() = default;
	public:
		inline Subscription& operator = (const Subscription&) = delete;
	public:
		template<class... Arguments_> inline void operator () (Arguments_&&... arguments_)
		{
			holder->Invoke(Forward<Arguments_&&>(arguments_)...);
		}
	public:
		inline Unsubscriber operator += (const Subscriber& subscriber_)
		{
			const auto &iterator = holder->Subscribe(subscriber_);

			return Move(Unsubscriber(holder, iterator));
		}
	};
}


#pragma region GreatVEngine2
#pragma endregion


#pragma region
#pragma endregion


