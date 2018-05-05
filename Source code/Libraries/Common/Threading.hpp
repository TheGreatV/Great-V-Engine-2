#pragma region Include

#pragma once

#include "Size.hpp"
#include "Reference.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <functional>

#pragma endregion


#pragma region Macros
#pragma endregion


namespace Threading
{
	class Event
	{
	protected:
		class Holder
		{
		public:
			bool state;
			std::recursive_mutex mutex;
			std::condition_variable_any conditionVariable;
		public:
			inline Holder(const bool& state_ = false):
				state(state_),
				mutex(),
				conditionVariable()
			{
			}
		};
	protected:
		std::shared_ptr<Holder> holder;
	public:
		inline Event(const bool& state_ = false):
			holder(std::make_shared<Holder>(state_))
		{
		}
		inline Event(const Event&) = default;
	public:
		inline Event& operator = (const Event&) = default;
	public:
		inline void Set()
		{
			std::lock_guard<std::recursive_mutex> lock(holder->mutex);

			holder->state = true;

			holder->conditionVariable.notify_all();
		}
		inline void Reset()
		{
			std::lock_guard<std::recursive_mutex> lock(holder->mutex);

			holder->state = false;
		}
		inline void Wait()
		{
			std::unique_lock<std::recursive_mutex> lock(holder->mutex);

			if (!holder->state)
			{
				holder->conditionVariable.wait(lock); // holder->mutex.unlock() will be called
			}
		}
		inline void Wait(std::function<void()> action)
		{
			std::unique_lock<std::recursive_mutex> lock(holder->mutex);

			if (!holder->state)
			{
				holder->conditionVariable.wait(lock); // holder->mutex.unlock() will be called
			}

			if (action)
			{
				action();
			}
		}
	};
}


#pragma region Threading
#pragma endregion


#pragma region
#pragma endregion


