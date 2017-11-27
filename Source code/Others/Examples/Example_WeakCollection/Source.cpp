#include <iostream>
#include <functional>

#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


class Entity
{
protected:
	GVE::WeakPointer<Entity> self;
public:
	GVE::List<std::function<void()>> onDestruction;
	inline void OnDestruction(const std::function<void()>& handler_)
	{
		onDestruction.push_back(handler_);
	}
public:
	inline Entity(const GVE::StrongPointer<Entity>& this_):
		self(this_)
	{
	}
	inline Entity(const Entity&) = delete;
	inline ~Entity()
	{
		for (auto &i : onDestruction)
		{
			i();
		}
	}
public:
	inline Entity& operator = (const Entity&) = delete;
public:
	template<class T>
	inline GVE::StrongPointer<T> GetThis()
	{
		auto strong = GVE::MakeStrong(self);
		auto casted = GVE::StaticCast<T>(strong);

		return casted;
	}
};

class WeakCollection
{
protected:
	GVE::List<GVE::WeakPointer<Entity>> elements;
public:
	inline void Remove(const GVE::WeakPointer<Entity>& entity_)
	{
		elements.remove(entity_);
	}
	inline void Add(const GVE::StrongPointer<Entity>& entity_)
	{
		class Remover
		{
		public:
			const GVE::Memory<WeakCollection> collection;
			const GVE::WeakPointer<Entity> entity;
			inline Remover(const GVE::Memory<WeakCollection>& collection_, const GVE::WeakPointer<Entity>& entity_):
				collection(collection_),
				entity(entity_)
			{
			}
			inline void operator()() const
			{
				collection->Remove(entity);
			}
		};

		auto weak = GVE::MakeWeak(entity_);
		auto remover = Remover(this, weak);

		entity_->OnDestruction(remover);

		elements.push_back(weak);
	}
};


void main()
{
	auto weakCollection = WeakCollection();

	auto e = GVE::Make<Entity>();

	weakCollection.Add(e);

	e = nullptr;

	std::system("pause");
}



