#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


// hack
#include <Windows.h>
#include <chrono>


namespace Desert
{
	enum class CargoRotation
	{
		Front,
		Right,
		Back,
		Left,
	};

	class Exception;
	class Game;
	class GameDependent;
	class Entity;
	class Game;
	class Hold; class HoldDependent;
	class HoldPlace;
	class Cargo; class CargoDependent;
	class CargoPart;
	class Hardpoint; class HardpointUser;
	class Ship; class ShipDependent;
	namespace Ships
	{
		class Test;
	}
	class Equipment;
	namespace Equipments
	{
		class Test;
	}


	inline bool IsConnectPossible(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const CargoRotation& rotation_ = Desert::CargoRotation::Front);
	inline void Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const CargoRotation& rotation_ = Desert::CargoRotation::Front);
	inline void Disconnect(const GVE::StrongPointer<CargoPart>& cargoPart_);

	inline void Mount(const GVE::StrongPointer<HardpointUser>& user_, const GVE::StrongPointer<Hardpoint>& hardpoint_);
	inline void Unmount(const GVE::StrongPointer<HardpointUser>& user_);


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
	public:
		inline void Update(const Delta& delta_);
	};
	class GameDependent
	{
	protected:
		const GVE::WeakPointer<Game> game;
	public:
		inline GameDependent(const GVE::StrongPointer<Game>& game_);
	public:
		inline GVE::StrongPointer<Game> GetGame() const;
	};
	class Entity:
		public GVE::This<Entity>,
		public GameDependent
	{
	public:
		using Delta = Game::Delta;
	public:
		inline Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_);
		inline virtual ~Entity() = default;
	public:
		inline virtual void Update(const Delta& delta_);
	public:
		template<class Derived_> inline GVE::StrongPointer<Derived_> GetThis() const
		{
			auto casted = GVE::DynamicCast<Derived_>(GVE::MakeStrong(self));

			return GVE::Move(casted);
		}
		template<class Derived_> inline GVE::WeakPointer<Derived_> GetWeak() const
		{
			auto casted = GVE::DynamicCast<Derived_>(self);

			return GVE::Move(casted);
		}
	};
	class Ship:
		public virtual Entity
	{
	public:
		using Hardpoints = GVE::Vector<GVE::StrongPointer<Hardpoint>>;
		using Mass = float;
	protected:
		const GVE::StrongPointer<Hold> hold;
		const Hardpoints hardpoints;
	public:
		inline Ship(const GVE::StrongPointer<Ship>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Hold>& hold_ = GVE::StrongPointer<Hold>(nullptr), Hardpoints&& hardpoints_ = Hardpoints());
		inline virtual ~Ship() override = default;
	public:
		virtual void Update(const Delta& delta_) override;
	public:
		// inline Mass GetTotalMass() const;
		// inline Mass GetEquipmentMass() const;
		inline virtual Mass GetMass() const;
		inline GVE::StrongPointer<Hold> GetHold() const;
	};
	class ShipDependent
	{
	protected:
		const GVE::WeakPointer<Ship> ship;
	public:
		inline ShipDependent(const GVE::StrongPointer<Ship>& ship_);
	public:
		inline GVE::StrongPointer<Ship> GetShip() const;
	};
	class Hardpoint:
		public virtual Entity,
		public ShipDependent
	{
		friend void Mount(const GVE::StrongPointer<HardpointUser>& user_, const GVE::StrongPointer<Hardpoint>& hardpoint_);
		friend void Unmount(const GVE::StrongPointer<HardpointUser>& user_);
	protected:
		GVE::StrongPointer<HardpointUser> user = GVE::StrongPointer<HardpointUser>(nullptr);
	public:
		inline Hardpoint(const GVE::StrongPointer<Hardpoint>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Ship>& ship_);
		inline virtual ~Hardpoint() override = default;
	public:
		inline bool IsEmpty() const;
	};
	class HardpointUser
	{
		friend void Mount(const GVE::StrongPointer<HardpointUser>& user_, const GVE::StrongPointer<Hardpoint>& hardpoint_);
		friend void Unmount(const GVE::StrongPointer<HardpointUser>& user_);
	protected:
		GVE::WeakPointer<Hardpoint> hardpoint = GVE::WeakPointer<Hardpoint>(nullptr);
	};
	namespace Ships
	{
		class Test:
			public Ship
		{
		protected:
			static inline Hardpoints GenerateHardpoints(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_);
		public:
			inline Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_);
			inline virtual ~Test() override = default;
		};
	}
	class Hold:
		public virtual Entity
	{
	public:
		using Places = GVE::Vector<GVE::StrongPointer<HoldPlace>>;
		using Cargos = GVE::Set<GVE::StrongPointer<Cargo>>;
	protected:
		static inline Places GeneratePlaces(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_);
	protected:
		const Places places;
		// Cargos cargos;
	public:
		inline Hold(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_);
		inline Hold(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_, Places&& places_);
		inline virtual ~Hold() override = default;
	public:
		virtual void Update(const Delta& delta_) override;
	public:
		inline const Places& GetPlaces() const;
	};
	class HoldDependent
	{
	protected:
		const GVE::WeakPointer<Hold> hold;
	public:
		inline HoldDependent(const GVE::StrongPointer<Hold>& hold_);
	public:
		inline GVE::StrongPointer<Hold> GetHold() const;
	};
	class HoldPlace:
		public virtual Entity,
		public HoldDependent
	{
		friend void Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const CargoRotation& rotation_);
		friend void Disconnect(const GVE::StrongPointer<CargoPart>& cargoPart_);
	public:
		using Fastening = GVE::StrongPointer<HoldPlace>;
	protected:
		Fastening left	= Fastening(nullptr);
		Fastening right	= Fastening(nullptr);
		Fastening back	= Fastening(nullptr);
		Fastening front	= Fastening(nullptr);
		GVE::WeakPointer<CargoPart> part = GVE::WeakPointer<CargoPart>(nullptr);
	public:
		inline HoldPlace(const GVE::StrongPointer<HoldPlace>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Hold>& hold_);
		inline virtual ~HoldPlace() override = default;
	public:
		inline GVE::StrongPointer<CargoPart> GetPart() const;
		inline Fastening GetLeft(const CargoRotation& rotation_) const;
		inline Fastening GetRight(const CargoRotation& rotation_) const;
		inline Fastening GetBack(const CargoRotation& rotation_) const;
		inline Fastening GetFront(const CargoRotation& rotation_) const;
		inline void SetLeft(Fastening& fastening_);
		inline void SetRight(Fastening& fastening_);
		inline void SetBack(Fastening& fastening_);
		inline void SetFront(Fastening& fastening_);
	};
	class Cargo:
		public virtual Entity
	{
	public:
		using Parts = GVE::Vector<GVE::StrongPointer<CargoPart>>;
	public:
		static inline Parts GenerateParts(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_);
	protected:
		const Parts parts;
		GVE::WeakPointer<Hold> hold = GVE::WeakPointer<Hold>(nullptr);
	public:
		inline Cargo(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_);
		inline Cargo(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_, Parts&& patrs_);
	public:
		inline const Parts& GetParts() const;
	};
	class CargoDependent
	{
	protected:
		const GVE::WeakPointer<Cargo> cargo;
	public:
		inline CargoDependent(const GVE::StrongPointer<Cargo>& cargo_);
	public:
		inline GVE::StrongPointer<Cargo> GetCargo() const;
	};
	class CargoPart:
		public virtual Entity,
		public CargoDependent
	{
		friend void Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const CargoRotation& rotation_);
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
		inline CargoPart(const GVE::StrongPointer<CargoPart>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Cargo>& cargo_);
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
		public virtual Entity
	{
	public:
		inline Equipment(const GVE::StrongPointer<Equipment>& this_, const GVE::StrongPointer<Game>& game_);
	};
	namespace Equipments
	{
		class Test:
			public Equipment,
			public Cargo,
			public HardpointUser
		{
		public:
			inline Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_);
		};
		/*class Box:
			public Equipment,
			public Cargo
		{
		public:
			inline Box(const GVE::StrongPointer<Box>& this_, const GVE::StrongPointer<Game>& game_);
		};*/
	}

	
	template<class Type_, class... Arguments_>
	GVE::StrongPointer<Type_> Make(Arguments_&&... arguments_)
	{
		class Holder:
			public Type_
		{
		public:
			Holder(const GVE::StrongPointer<Type_>& this_, const GVE::StrongPointer<Game>& game_, Arguments_&&... arguments_):
				Entity(this_, game_), Type_(this_, GVE::Forward<Arguments_&&>(arguments_)...)
			{
			}
			void operator delete (GVE::Memory<void> rawMemory_)
			{
				auto memory = static_cast<GVE::Memory<Holder>>(rawMemory_);

				GVE::ReleaseMemory(memory);
			}
		};

		auto memory = GVE::AllocateMemory<Holder>();
		auto pointer = GVE::StrongPointer<Holder>(memory);
		auto castedPointer = GVE::StaticCast<Type_>(pointer);

		::new(memory)Type_(castedPointer, GVE::Forward<Arguments_&&>(arguments_)...);

		return GVE::Move(castedPointer);
	}
}


#pragma region Desert

#pragma region Exception

#pragma endregion

#pragma region Exception

#pragma endregion

#pragma region Game

#pragma region Dependent

Desert::GameDependent::GameDependent(const GVE::StrongPointer<Game>& game_):
	game(game_)
{
}

GVE::StrongPointer<Desert::Game> Desert::GameDependent::GetGame() const
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
	auto entity = Desert::Make<Type_>(ownedThis);

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
	GameDependent(game_)
{
}

void Desert::Entity::Update(const Delta& delta_)
{
}

#pragma endregion

#pragma region Hold

Desert::Hold::Places Desert::Hold::GeneratePlaces(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_)
{
	Places places;

	auto p1 = Desert::Make<HoldPlace>(game_, this_);
	auto p2 = Desert::Make<HoldPlace>(game_, this_);
	auto p3 = Desert::Make<HoldPlace>(game_, this_);
	auto p4 = Desert::Make<HoldPlace>(game_, this_);
										   
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
	Hold(this_, game_, Move(GeneratePlaces(this_, game_)))
{
}
Desert::Hold::Hold(const GVE::StrongPointer<Hold>& this_, const GVE::StrongPointer<Game>& game_, Places&& places_) :
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

#pragma region HoldDependent

Desert::HoldDependent::HoldDependent(const GVE::StrongPointer<Hold>& hold_):
	hold(hold_)
{
}

GVE::StrongPointer<Desert::Hold> Desert::HoldDependent::GetHold() const
{
	return GVE::Move(GVE::MakeStrong(hold));
}

#pragma endregion

#pragma region HoldPlace

Desert::HoldPlace::HoldPlace(const GVE::StrongPointer<HoldPlace>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Hold>& hold_):
	Entity(this_, game_),
	HoldDependent(hold_)
{
}

GVE::StrongPointer<Desert::CargoPart> Desert::HoldPlace::GetPart() const
{
	return GVE::MakeStrong(part);
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetLeft(const CargoRotation& rotation_) const
{
	if (rotation_ == CargoRotation::Front)
	{
		return left;
	}
	else if (rotation_ == CargoRotation::Right)
	{
		return front;
	}
	else if (rotation_ == CargoRotation::Back)
	{
		return right;
	}
	else if (rotation_ == CargoRotation::Left)
	{
		return back;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetRight(const CargoRotation& rotation_) const
{
	if (rotation_ == CargoRotation::Front)
	{
		return right;
	}
	else if (rotation_ == CargoRotation::Right)
	{
		return back;
	}
	else if (rotation_ == CargoRotation::Back)
	{
		return left;
	}
	else if (rotation_ == CargoRotation::Left)
	{
		return front;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetFront(const CargoRotation& rotation_) const
{
	if (rotation_ == CargoRotation::Front)
	{
		return front;
	}
	else if (rotation_ == CargoRotation::Right)
	{
		return right;
	}
	else if (rotation_ == CargoRotation::Back)
	{
		return back;
	}
	else if (rotation_ == CargoRotation::Left)
	{
		return left;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Desert::HoldPlace::Fastening Desert::HoldPlace::GetBack(const CargoRotation& rotation_) const
{
	if (rotation_ == CargoRotation::Front)
	{
		return back;
	}
	else if (rotation_ == CargoRotation::Right)
	{
		return left;
	}
	else if (rotation_ == CargoRotation::Back)
	{
		return front;
	}
	else if (rotation_ == CargoRotation::Left)
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

Desert::Cargo::Parts Desert::Cargo::GenerateParts(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_)
{
	Parts parts;

	auto p1 = Desert::Make<CargoPart>(game_, this_);
	auto p2 = Desert::Make<CargoPart>(game_, this_);

	p1->SetFront(p2);

	parts.push_back(p1);
	parts.push_back(p2);

	return Move(parts);
}

Desert::Cargo::Cargo(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_):
	Cargo(this_, game_, Move(GenerateParts(this_, game_)))
{
}
Desert::Cargo::Cargo(const GVE::StrongPointer<Cargo>& this_, const GVE::StrongPointer<Game>& game_, Parts&& parts_):
	Entity(this_, game_),
	parts(parts_)
{
}

const Desert::Cargo::Parts& Desert::Cargo::GetParts() const
{
	return parts;
}

#pragma endregion

#pragma region CargoDependent

Desert::CargoDependent::CargoDependent(const GVE::StrongPointer<Cargo>& cargo_):
	cargo(cargo_)
{
}

GVE::StrongPointer<Desert::Cargo> Desert::CargoDependent::GetCargo() const
{
	return GVE::Move(GVE::MakeStrong(cargo));
}

#pragma endregion

#pragma region CargoPart

Desert::CargoPart::CargoPart(const GVE::StrongPointer<CargoPart>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Cargo>& cargo_):
	Entity(this_, game_),
	CargoDependent(cargo_)
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

#pragma region Hardpoint

Desert::Hardpoint::Hardpoint(const GVE::StrongPointer<Hardpoint>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Ship>& ship_):
	Entity(this_, game_),
	ShipDependent(ship_)
{
}

bool Desert::Hardpoint::IsEmpty() const
{
	return user != nullptr;
}

#pragma endregion

#pragma region Ship

Desert::Ship::Ship(const GVE::StrongPointer<Ship>& this_, const GVE::StrongPointer<Game>& game_, const GVE::StrongPointer<Hold>& hold_, Hardpoints&& hardpoints_):
	Entity(this_, game_),
	hold(hold_),
	hardpoints(hardpoints_)
{
}

void Desert::Ship::Update(const Delta& delta_)
{
	// hold->Update(delta_);
}

// Desert::Ship::Mass Desert::Ship::GetTotalMass() const
// {
// 	auto ownMass = GetMass();
// 	auto equipmentMass = GetEquipmentMass();
// 	auto totalMass = ownMass + equipmentMass;
// 	
// 	return totalMass;
// }
// Desert::Ship::Mass Desert::Ship::GetEquipmentMass() const
// {
// 	Mass mass = 0.0f;
// 
// 	for (auto &hardpoint : hardpoints)
// 	{
// 		// TODO
// 	}
// 
// 	return mass;
// }
Desert::Ship::Mass Desert::Ship::GetMass() const
{
	return 1.0f;
}
GVE::StrongPointer<Desert::Hold> Desert::Ship::GetHold() const
{
	return hold;
}

#pragma endregion

#pragma region ShipDependent

Desert::ShipDependent::ShipDependent(const GVE::StrongPointer<Ship>& ship_):
	ship(ship_)
{
}

GVE::StrongPointer<Desert::Ship> Desert::ShipDependent::GetShip() const
{
	return GVE::Move(GVE::MakeStrong(ship));
}

#pragma endregion

#pragma region Ships

#pragma region Test

Desert::Ship::Hardpoints Desert::Ships::Test::GenerateHardpoints(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_)
{
	Hardpoints hardpoints;

	hardpoints.push_back(Desert::Make<Hardpoint>(game_, this_));

	return GVE::Move(hardpoints);
}

Desert::Ships::Test::Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_), Ship(this_, game_, Desert::Make<Hold>(game_), GenerateHardpoints(this_, game_))
{
}

#pragma endregion

#pragma endregion

#pragma region Equipment

Desert::Equipment::Equipment(const GVE::StrongPointer<Equipment>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_)
{
}

#pragma endregion

#pragma region Equipments

#pragma region Test

Desert::Equipments::Test::Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	Equipment(this_, game_),
	Cargo(this_, game_)
{
}

#pragma endregion

#pragma region Box

/*Desert::Equipments::Box::Box(const GVE::StrongPointer<Box>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_), Equipment(this_, game_, Desert::Make<Cargo>(game_))
{
}*/

#pragma endregion

#pragma endregion


bool Desert::IsConnectPossible(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const CargoRotation& rotation_)
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
void Desert::Connect(const GVE::StrongPointer<CargoPart>& cargoPart_, const GVE::StrongPointer<HoldPlace>& holdPlace_, const CargoRotation& rotation_)
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

void Desert::Mount(const GVE::StrongPointer<HardpointUser>& user_, const GVE::StrongPointer<Hardpoint>& hardpoint_)
{
	if (!hardpoint_->user)
	{
		if (user_->hardpoint != nullptr)
		{
			user_->hardpoint->user = nullptr;
		}

		user_->hardpoint = hardpoint_;
		hardpoint_->user = user_;
	}
	else
	{
		throw Exception();
	}
}
void Desert::Unmount(const GVE::StrongPointer<HardpointUser>& user_)
{

}


#pragma endregion


#pragma region
#pragma endregion


void main()
{
	auto game = GVE::Make<Desert::Game>();
	auto testShip = game->Create<Desert::Ships::Test>();
	auto testEquipment1 = game->Create<Desert::Equipments::Test>();


	auto &place = testShip->GetHold()->GetPlaces()[0];
	auto &part = testEquipment1->GetParts()[0];

	if (Desert::IsConnectPossible(part, place, Desert::CargoRotation::Front))
	{
		Desert::Connect(part, place, Desert::CargoRotation::Front);
	}

	// testEquipment1->

	// Desert::Mo

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		float d = 1.0f / 60.0f;

		game->Update(d);

		Sleep(static_cast<DWORD>(d * 1000.0f));
	}

	std::system("pause");
}