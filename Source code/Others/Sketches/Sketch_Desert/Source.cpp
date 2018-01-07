#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


// hack
#include <Windows.h>
#include <chrono>


namespace Desert
{
	class Exception;
	class Entity;
	class Game;
	class Hold;
	class HoldPlace;
	class Cargo;
	class CargoPart;
	class Ship;
	namespace Ships
	{
		class Test;
	}
	class Equipment;
	namespace Equipments
	{
		class Test;
	}


	class Exception
	{
		// TODO
	};
	class Game:
		public GVE::This<Game>
	{
	public:
		using Delta = float;
	public:
		class Dependent;
	protected:
		GVE::List<GVE::StrongPointer<Entity>> entities;
	public:
		inline Game(const GVE::StrongPointer<Game>& this_);
	public:
		inline void Add(const GVE::StrongPointer<Entity>& entity_);
		template<class Type_> GVE::WeakPointer<Type_> Create(); // TODO: replace result with UserPointer
		// template<class Type_, class... Arguments_> GVE::WeakPointer<Type_> Create(Arguments_...&& arguments_); // TODO: replace result with UserPointer
	public:
		inline void Update(const Delta& delta_);
	};
	class Game::Dependent
	{
	protected:
		const GVE::WeakPointer<Game> game;
	public:
		inline Dependent(const GVE::StrongPointer<Game>& game_);
	public:
		inline GVE::StrongPointer<Game> GetGame() const;
	};
	class Entity:
		public GVE::This<Entity>,
		public Game::Dependent
	{
	public:
		using Delta = Game::Delta;
	public:
		inline Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_);
		inline virtual ~Entity() = default;
	public:
		inline virtual void Update(const Delta& delta_);
	};
	class Ship:
		public Entity
	{
	public:
		class Dependent;
	protected:
		const GVE::StrongPointer<Hold> hold;
	public:
		inline Ship(const GVE::StrongPointer<Ship>& this_, const GVE::StrongPointer<Hold>& hold_, const GVE::StrongPointer<Game>& game_);
		inline virtual ~Ship() override = default;
	public:
		virtual void Update(const Delta& delta_) override;
	public:
		inline GVE::StrongPointer<Hold> GetHold() const;
	};
	class Ship::Dependent
	{
	protected:
		const GVE::WeakPointer<Ship> ship;
	public:
		inline Dependent(const GVE::StrongPointer<Ship>& ship_);
	public:
		inline GVE::StrongPointer<Ship> GetShip() const;
	};
	namespace Ships
	{
		class Test:
			public Ship
		{
		public:
			inline Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_);
			inline virtual ~Test() override = default;
		};
	}
	class Hold:
		public Entity
	{
	public:
		using Places = GVE::Vector<GVE::StrongPointer<HoldPlace>>;
	public:
		class Dependent;
	protected:
		static inline Places GeneratePlaces(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_);
	protected:
		const Places places;
	public:
		inline Hold(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_);
		inline Hold(const GVE::StrongPointer<Hold>& this_, Places&& places_, const GVE::StrongPointer<Game>& game_);
		inline virtual ~Hold() override = default;
	public:
		virtual void Update(const Delta& delta_) override;
	public:
		inline const Places& GetPlaces() const;
	};
	class Hold::Dependent
	{
	protected:
		const GVE::WeakPointer<Hold> hold;
	public:
		inline Dependent(const GVE::StrongPointer<Hold>& hold_);
	public:
		inline GVE::StrongPointer<Hold> GetHold() const;
	};
	class Cargo:
		public Entity
	{
	public:
		using Parts = GVE::Vector<GVE::StrongPointer<CargoPart>>;
	public:
		enum class Rotation
		{
			Front,
			Right,
			Back,
			Left,
		};
	public:
		static inline Parts GenerateParts(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_);
	public:
		class Dependent;
	protected:
		const Parts parts;
	public:
		inline Cargo(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_);
		inline Cargo(const GVE::StrongPointer<Cargo>& this_, Parts&& patrs_, const GVE::StrongPointer<Game>& game_);
	public:
		inline const Parts& GetParts() const;
	};


	inline void Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const Cargo::Rotation& rotation_);
	inline void Disconnect(const GVE::StrongPointer<CargoPart>& cargoPart_);


	class Cargo::Dependent
	{
	protected:
		const GVE::WeakPointer<Cargo> cargo;
	public:
		inline Dependent(const GVE::StrongPointer<Cargo>& cargo_);
	public:
		inline GVE::StrongPointer<Cargo> GetCargo() const;
	};
	class HoldPlace:
		public Entity,
		public Hold::Dependent
	{
		friend void Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const Cargo::Rotation& rotation_);
		friend void Disconnect(const GVE::StrongPointer<CargoPart>& cargoPart_);
	public:
		using Rotation = Cargo::Rotation;
		using Fastening = GVE::StrongPointer<HoldPlace>;
	protected:
		Fastening left	= Fastening(nullptr);
		Fastening right	= Fastening(nullptr);
		Fastening back	= Fastening(nullptr);
		Fastening front	= Fastening(nullptr);
		GVE::WeakPointer<CargoPart> part = GVE::WeakPointer<CargoPart>(nullptr);
	public:
		inline HoldPlace(const GVE::StrongPointer<HoldPlace>& this_, const GVE::StrongPointer<Hold>& hold_, const GVE::StrongPointer<Game>& game_);
		inline virtual ~HoldPlace() override = default;
	public:
		inline GVE::StrongPointer<CargoPart> GetPart() const;
		inline Fastening GetLeft(const Rotation& rotation_) const;
		inline Fastening GetRight(const Rotation& rotation_) const;
		inline Fastening GetBack(const Rotation& rotation_) const;
		inline Fastening GetFront(const Rotation& rotation_) const;
		inline void SetLeft(Fastening& fastening_);
		inline void SetRight(Fastening& fastening_);
		inline void SetBack(Fastening& fastening_);
		inline void SetFront(Fastening& fastening_);
	};
	class CargoPart:
		public Entity,
		public Cargo::Dependent
	{
		friend void Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const Cargo::Rotation& rotation_);
		friend void Disconnect(const GVE::StrongPointer<CargoPart>& cargoPart_);
	public:
		using Fastening = GVE::StrongPointer<CargoPart>;
	protected:
		Fastening left	= Fastening(nullptr);
		Fastening right	= Fastening(nullptr);
		Fastening front	= Fastening(nullptr);
		Fastening back	= Fastening(nullptr);
		GVE::WeakPointer<HoldPlace> place = GVE::WeakPointer<HoldPlace>(nullptr);
	public:
		inline CargoPart(const GVE::StrongPointer<CargoPart>& this_, const GVE::StrongPointer<Cargo>& cargo_, const GVE::StrongPointer<Game>& game_);
	public:
		inline GVE::StrongPointer<HoldPlace> GetPlace() const;
		inline Fastening GetLeft() const;
		inline Fastening GetRight() const;
		inline Fastening GetFront() const;
		inline Fastening GetBack() const;
		inline void SetLeft(Fastening& fastening_);
		inline void SetRight(Fastening& fastening_);
		inline void SetFront(Fastening& fastening_);
		inline void SetBack(Fastening& fastening_);
	};
	class Equipment:
		public Entity
	{
	protected:
		const GVE::StrongPointer<Cargo> cargo;
	public:
		inline Equipment(const GVE::StrongPointer<Equipment>& this_, const GVE::StrongPointer<Cargo>& cargo_, const GVE::StrongPointer<Game>& game_);
	public:
		inline GVE::StrongPointer<Cargo> GetCargo() const;
	};
	namespace Equipments
	{
		class Test:
			public Equipment
		{
		public:
			inline Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_);
		};
	}


	inline bool IsConnectPossible(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const Cargo::Rotation& rotation_);
}


#pragma region Desert

#pragma region Exception

#pragma endregion

#pragma region Game

#pragma region Dependent

Desert::Game::Dependent::Dependent(const GVE::StrongPointer<Game>& game_):
	game(game_)
{
}

GVE::StrongPointer<Desert::Game> Desert::Game::Dependent::GetGame() const
{
	return GVE::Move(GVE::MakeStrong(game));
}

#pragma endregion


Desert::Game::Game(const GVE::StrongPointer<Game>& this_):
	This(this_)
{
}

void Desert::Game::Add(const GVE::StrongPointer<Entity>& entity_)
{
	entities.push_back(entity_);
}
template<class Type_> GVE::WeakPointer<Type_> Desert::Game::Create()
{
	auto ownedThis = GetThis<Game>();
	auto entity = GVE::Make<Type_>(ownedThis);

	Add(entity);

	return Move(MakeWeak(entity));
}

void Desert::Game::Update(const Delta& delta_)
{
	for (auto &entity : entities)
	{
		entity->Update(delta_);
	}
}

#pragma endregion

#pragma region Entity

Desert::Entity::Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_):
	This(this_),
	Dependent(game_)
{
}

void Desert::Entity::Update(const Delta& delta_)
{
}

#pragma endregion

#pragma region Hold

#pragma region Dependent

Desert::Hold::Dependent::Dependent(const GVE::StrongPointer<Hold>& hold_):
	hold(hold_)
{
}

GVE::StrongPointer<Desert::Hold> Desert::Hold::Dependent::GetHold() const
{
	return GVE::Move(GVE::MakeStrong(hold));
}

#pragma endregion


Desert::Hold::Places Desert::Hold::GeneratePlaces(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_)
{
	Places places;

	auto p1 = GVE::Make<HoldPlace>(this_, game_);
	auto p2 = GVE::Make<HoldPlace>(this_, game_);
	auto p3 = GVE::Make<HoldPlace>(this_, game_);
	auto p4 = GVE::Make<HoldPlace>(this_, game_);

	// 3 4
	// 1 2
	
	p1->SetRight(p2);
	p1->SetFront(p3);
	p2->SetFront(p4);
	p3->SetRight(p4);

	places.push_back(p1);
	places.push_back(p2);
	places.push_back(p3);
	places.push_back(p4);

	return Move(places);
}

Desert::Hold::Hold(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_):
	Hold(this_, Move(GeneratePlaces(this_, game_)), game_)
{
}
Desert::Hold::Hold(const GVE::StrongPointer<Hold>& this_, Places&& places_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	places(GVE::Move(places_))
{
}

void Desert::Hold::Update(const Delta& delta_)
{
	for (auto &holdPlace : places)
	{
		holdPlace->Update(delta_);
	}
}

const Desert::Hold::Places& Desert::Hold::GetPlaces() const
{
	return places;
}

#pragma endregion

#pragma region HoldPlace

Desert::HoldPlace::HoldPlace(const GVE::StrongPointer<HoldPlace>& this_, const GVE::StrongPointer<Hold>& hold_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	Hold::Dependent(hold_)
{
}

GVE::StrongPointer<Desert::CargoPart> Desert::HoldPlace::GetPart() const
{
	return GVE::MakeStrong(part);
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetLeft(const Rotation& rotation_) const
{
	if (rotation_ == Rotation::Front)
	{
		return left;
	}
	else if (rotation_ == Rotation::Right)
	{
		return front;
	}
	else if (rotation_ == Rotation::Back)
	{
		return right;
	}
	else if (rotation_ == Rotation::Left)
	{
		return back;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetRight(const Rotation& rotation_) const
{
	if (rotation_ == Rotation::Front)
	{
		return right;
	}
	else if (rotation_ == Rotation::Right)
	{
		return back;
	}
	else if (rotation_ == Rotation::Back)
	{
		return left;
	}
	else if (rotation_ == Rotation::Left)
	{
		return front;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetFront(const Rotation& rotation_) const
{
	if (rotation_ == Rotation::Front)
	{
		return front;
	}
	else if (rotation_ == Rotation::Right)
	{
		return right;
	}
	else if (rotation_ == Rotation::Back)
	{
		return back;
	}
	else if (rotation_ == Rotation::Left)
	{
		return left;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetBack(const Rotation& rotation_) const
{
	if (rotation_ == Rotation::Front)
	{
		return back;
	}
	else if (rotation_ == Rotation::Right)
	{
		return left;
	}
	else if (rotation_ == Rotation::Back)
	{
		return front;
	}
	else if (rotation_ == Rotation::Left)
	{
		return right;
	}
	else
	{
		throw Exception(); // TODO
	}
}
void Desert::HoldPlace::SetLeft(Fastening& fastening_)
{
	if (left)
	{
		left->right = nullptr;
	}

	left = fastening_;

	if (left)
	{
		left->right = GetThis<HoldPlace>();
	}
}
void Desert::HoldPlace::SetRight(Fastening& fastening_)
{
	if (right)
	{
		right->left = nullptr;
	}

	right = fastening_;

	if (right)
	{
		right->left = GetThis<HoldPlace>();
	}
}
void Desert::HoldPlace::SetBack(Fastening& fastening_)
{
	if (back)
	{
		back->front = nullptr;
	}

	back = fastening_;

	if (back)
	{
		back->front = GetThis<HoldPlace>();
	}
}
void Desert::HoldPlace::SetFront(Fastening& fastening_)
{
	if (front)
	{
		front->back = nullptr;
	}

	front = fastening_;

	if (front)
	{
		front->back = GetThis<HoldPlace>();
	}
}

#pragma endregion

#pragma region Cargo

#pragma region Dependent

Desert::Cargo::Dependent::Dependent(const GVE::StrongPointer<Cargo>& cargo_):
	cargo(cargo_)
{
}

GVE::StrongPointer<Desert::Cargo> Desert::Cargo::Dependent::GetCargo() const
{
	return GVE::Move(GVE::MakeStrong(cargo));
}

#pragma endregion


Desert::Cargo::Parts Desert::Cargo::GenerateParts(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_)
{
	Parts parts;

	auto p1 = GVE::Make<CargoPart>(this_, game_);
	auto p2 = GVE::Make<CargoPart>(this_, game_);

	p1->SetFront(p2);

	parts.push_back(p1);
	parts.push_back(p2);

	return Move(parts);
}

Desert::Cargo::Cargo(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_):
	Cargo(this_, Move(GenerateParts(this_, game_)), game_)
{
}
Desert::Cargo::Cargo(const GVE::StrongPointer<Cargo>& this_, Parts&& parts_, const GVE::StrongPointer<Game>& game_) :
	Entity(this_, game_),
	parts(parts_)
{
}

const Desert::Cargo::Parts& Desert::Cargo::GetParts() const
{
	return parts;
}

#pragma endregion

#pragma region CargoPart

Desert::CargoPart::CargoPart(const GVE::StrongPointer<CargoPart>& this_, const GVE::StrongPointer<Cargo>& cargo_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	Cargo::Dependent(cargo_)
{
}

GVE::StrongPointer<Desert::HoldPlace> Desert::CargoPart::GetPlace() const
{
	return GVE::MakeStrong(place);
}
Desert::CargoPart::Fastening Desert::CargoPart::GetLeft() const
{
	return left;
}
Desert::CargoPart::Fastening Desert::CargoPart::GetRight() const
{
	return right;
}
Desert::CargoPart::Fastening Desert::CargoPart::GetFront() const
{
	return front;
}
Desert::CargoPart::Fastening Desert::CargoPart::GetBack() const
{
	return back;
}
void Desert::CargoPart::SetLeft(Fastening& fastening_)
{
	if (left)
	{
		left->right = nullptr;
	}

	left = fastening_;
	
	if (left)
	{
		left->right = GetThis<CargoPart>();
	}
}
void Desert::CargoPart::SetRight(Fastening& fastening_)
{
	if (right)
	{
		right->left = nullptr;
	}

	right = fastening_;

	if (right)
	{
		right->left = GetThis<CargoPart>();
	}
}
void Desert::CargoPart::SetFront(Fastening& fastening_)
{
	if (front)
	{
		front->back = nullptr;
	}

	front = fastening_;

	if (front)
	{
		front->back = GetThis<CargoPart>();
	}
}
void Desert::CargoPart::SetBack(Fastening& fastening_)
{
	if (back)
	{
		back->front = nullptr;
	}

	back = fastening_;

	if (back)
	{
		back->front = GetThis<CargoPart>();
	}
}

#pragma endregion

#pragma region Ship

#pragma region Dependent

Desert::Ship::Dependent::Dependent(const GVE::StrongPointer<Ship>& ship_):
	ship(ship_)
{
}

GVE::StrongPointer<Desert::Ship> Desert::Ship::Dependent::GetShip() const
{
	return GVE::Move(GVE::MakeStrong(ship));
}

#pragma endregion


Desert::Ship::Ship(const GVE::StrongPointer<Ship>& this_, const GVE::StrongPointer<Hold>& hold_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	hold(hold_)
{
}

void Desert::Ship::Update(const Delta& delta_)
{
	hold->Update(delta_);
}

GVE::StrongPointer<Desert::Hold> Desert::Ship::GetHold() const
{
	return hold;
}

#pragma endregion

#pragma region Ships

#pragma region Test

Desert::Ships::Test::Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_):
	Ship(this_, GVE::Make<Hold>(game_), game_)
{
}

#pragma endregion

#pragma endregion

#pragma region Equipment

Desert::Equipment::Equipment(const GVE::StrongPointer<Equipment>& this_, const GVE::StrongPointer<Cargo>& cargo_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	cargo(cargo_)
{
}

GVE::StrongPointer<Desert::Cargo> Desert::Equipment::GetCargo() const
{
	return cargo;
}

#pragma endregion

#pragma region Equipments

#pragma region Test

Desert::Equipments::Test::Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_):
	Equipment(this_, GVE::Make<Cargo>(game_), game_)
{
}

#pragma endregion

#pragma endregion


bool Desert::IsConnectPossible(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const Cargo::Rotation& rotation_)
{
	GVE::Set<GVE::Pair<GVE::StrongPointer<CargoPart>, GVE::StrongPointer<HoldPlace>>> pending = {{cargoPart_, holdPlace_}};
	GVE::Set<GVE::StrongPointer<CargoPart>> checked;

	auto check = [&](const GVE::StrongPointer<CargoPart>& part_, const GVE::StrongPointer<HoldPlace>& place_) -> bool
	{
		checked.insert(part_);

		auto empty = place_->GetPart() == nullptr;

		if (!empty)
		{
			return false;
		}

		if (auto leftPart = part_->GetLeft())
		{
			if (checked.find(leftPart) == checked.end())
			{
				if (auto leftPlace = place_->GetLeft(rotation_))
				{
					pending.insert({leftPart, leftPlace});
				}
				else
				{
					return false;
				}
			}
		}
		if (auto rightPart = part_->GetRight())
		{
			if (checked.find(rightPart) == checked.end())
			{
				if (auto rightPlace = place_->GetRight(rotation_))
				{
					pending.insert({rightPart, rightPlace});
				}
				else
				{
					return false;
				}
			}
		}
		if (auto backPart = part_->GetBack())
		{
			if (checked.find(backPart) == checked.end())
			{
				if (auto backPlace = place_->GetBack(rotation_))
				{
					pending.insert({backPart, backPlace});
				}
				else
				{
					return false;
				}
			}
		}
		if (auto frontPart = part_->GetFront())
		{
			if (checked.find(frontPart) == checked.end())
			{
				if (auto frontPlace = place_->GetFront(rotation_))
				{
					pending.insert({frontPart, frontPlace});
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	};

	while (!pending.empty())
	{
		auto toCheck = pending;
		pending.clear();

		for (auto &pair : toCheck)
		{
			if (!check(pair.first, pair.second))
			{
				return false;
			}
		}
	}

	return true;
}
void Desert::Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const Cargo::Rotation& rotation_)
{
	GVE::Set<GVE::Pair<GVE::StrongPointer<CargoPart>, GVE::StrongPointer<HoldPlace>>> pending = {{cargoPart_, holdPlace_}};
	GVE::Set<GVE::StrongPointer<CargoPart>> checked;

	auto connect = [&](const GVE::StrongPointer<CargoPart>& part_, const GVE::StrongPointer<HoldPlace>& place_)
	{
		checked.insert(part_);

		auto empty = place_->GetPart() == nullptr;

		if (empty)
		{
			part_->place = place_;
			place_->part = part_;
		}
		else
		{
			throw Exception(); // TODO
		}

		if (auto leftPart = part_->GetLeft())
		{
			if (checked.find(leftPart) == checked.end())
			{
				if (auto leftPlace = place_->GetLeft(rotation_))
				{
					pending.insert({leftPart, leftPlace});
				}
				else
				{
					throw Exception(); // TODO
				}
			}
		}
		if (auto rightPart = part_->GetRight())
		{
			if (checked.find(rightPart) == checked.end())
			{
				if (auto rightPlace = place_->GetRight(rotation_))
				{
					pending.insert({rightPart, rightPlace});
				}
				else
				{
					throw Exception(); // TODO
				}
			}
		}
		if (auto backPart = part_->GetBack())
		{
			if (checked.find(backPart) == checked.end())
			{
				if (auto backPlace = place_->GetBack(rotation_))
				{
					pending.insert({backPart, backPlace});
				}
				else
				{
					throw Exception(); // TODO
				}
			}
		}
		if (auto frontPart = part_->GetFront())
		{
			if (checked.find(frontPart) == checked.end())
			{
				if (auto frontPlace = place_->GetFront(rotation_))
				{
					pending.insert({frontPart, frontPlace});
				}
				else
				{
					throw Exception(); // TODO
				}
			}
		}
	};

	while (!pending.empty())
	{
		auto toCheck = pending;
		pending.clear();

		for (auto &pair : toCheck)
		{
			connect(pair.first, pair.second);
		}
	}
}
void Desert::Disconnect(const GVE::StrongPointer<CargoPart>& cargoPart_)
{
	GVE::Set<GVE::StrongPointer<CargoPart>> pending = {cargoPart_};
	GVE::Set<GVE::StrongPointer<CargoPart>> checked;

	auto disconnect = [&](const GVE::StrongPointer<CargoPart>& part_)
	{
		checked.insert(part_);

		if (auto place = part_->GetPlace())
		{
			place->part = nullptr;
			part_->place = nullptr;
		}
		else
		{
			throw Exception(); // TODO
		}

		if (auto leftPart = part_->GetLeft())
		{
			if (checked.find(leftPart) == checked.end())
			{
				pending.insert(leftPart);
			}
		}
		if (auto rightPart = part_->GetRight())
		{
			if (checked.find(rightPart) == checked.end())
			{
				pending.insert(rightPart);
			}
		}
		if (auto backPart = part_->GetBack())
		{
			if (checked.find(backPart) == checked.end())
			{
				pending.insert(backPart);
			}
		}
		if (auto frontPart = part_->GetFront())
		{
			if (checked.find(frontPart) == checked.end())
			{
				pending.insert(frontPart);
			}
		}
	};

	while (!pending.empty())
	{
		auto toCheck = pending;
		pending.clear();

		for (auto &part : toCheck)
		{
			disconnect(part);
		}
	}
}

#pragma endregion


#pragma region
#pragma endregion


void main()
{
	using namespace GVE;
	using namespace Desert;

	auto game = Make<Game>();
	auto testShip = game->Create<Ships::Test>();
	auto testEquipment1 = game->Create<Equipments::Test>();

	/* // connections test
	auto check = [&](int i, int j, Cargo::Rotation r, bool s)
	{
		if (IsConnectPossible(testEquipment1->GetCargo()->GetParts()[i], testShip->GetHold()->GetPlaces()[j], r) != s) throw 5;

		if (s)
		{
			Connect(testEquipment1->GetCargo()->GetParts()[i], testShip->GetHold()->GetPlaces()[j], r);
			Disconnect(testEquipment1->GetCargo()->GetParts()[i]);
		}
	};

	check(0, 0, Cargo::Rotation::Front, true);
	check(0, 1, Cargo::Rotation::Front, true);
	check(0, 2, Cargo::Rotation::Front, false);
	check(0, 3, Cargo::Rotation::Front, false);

	check(0, 0, Cargo::Rotation::Right, true);
	check(0, 1, Cargo::Rotation::Right, false);
	check(0, 2, Cargo::Rotation::Right, true);
	check(0, 3, Cargo::Rotation::Right, false);

	check(0, 0, Cargo::Rotation::Back, false);
	check(0, 1, Cargo::Rotation::Back, false);
	check(0, 2, Cargo::Rotation::Back, true);
	check(0, 3, Cargo::Rotation::Back, true);

	check(0, 0, Cargo::Rotation::Left, false);
	check(0, 1, Cargo::Rotation::Left, true);
	check(0, 2, Cargo::Rotation::Left, false);
	check(0, 3, Cargo::Rotation::Left, true);

	check(1, 0, Cargo::Rotation::Front, false);
	check(1, 1, Cargo::Rotation::Front, false);
	check(1, 2, Cargo::Rotation::Front, true);
	check(1, 3, Cargo::Rotation::Front, true);

	check(1, 0, Cargo::Rotation::Right, false);
	check(1, 1, Cargo::Rotation::Right, true);
	check(1, 2, Cargo::Rotation::Right, false);
	check(1, 3, Cargo::Rotation::Right, true);

	check(1, 0, Cargo::Rotation::Back, true);
	check(1, 1, Cargo::Rotation::Back, true);
	check(1, 2, Cargo::Rotation::Back, false);
	check(1, 3, Cargo::Rotation::Back, false);

	check(1, 0, Cargo::Rotation::Left, true);
	check(1, 1, Cargo::Rotation::Left, false);
	check(1, 2, Cargo::Rotation::Left, true);
	check(1, 3, Cargo::Rotation::Left, false);*/

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		float d = 1.0f / 60.0f;

		game->Update(d);

		Sleep(static_cast<DWORD>(d * 1000.0f));
	}

	std::system("pause");
}