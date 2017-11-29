#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


namespace BasicGameClass
{
	template<class Type_> class This
	{
	protected:
		const GVE::WeakPointer<Type_> self;
	public:
		inline This(const GVE::StrongPointer<Type_>& this_):
			self(this_)
		{
		}
		inline This(const This&) = delete;
		inline ~This() = default;
	public:
		inline This& operator = (const This&) = delete;
	public:
		template<class Derived_> inline GVE::StrongPointer<Derived_> GetThis() const
		{
			return GVE::Move(GVE::StaticCast<Derived_>(GVE::MakeStrong(self)));
		}
		template<class Derived_> inline GVE::WeakPointer<Derived_> GetWeak() const
		{
			return self;
		}
	};

	
	class Exception;
	
	class Entity;
	class Game;

	class Building;


	class Exception
	{
	};
	
	class Entity:
		public This<Entity>
	{
	protected:
		const GVE::WeakPointer<Game> game;
	public:
		inline Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_);
		inline Entity(const Entity&) = delete;
		inline virtual ~Entity();
	public:
		inline Entity& operator = (const Entity&) = delete;
	public:
		inline GVE::StrongPointer<Game> GetGame() const;
	};
	class Game:
		public This<Game>
	{
	protected:
		GVE::List<GVE::WeakPointer<Entity>> entities;
	public:
		inline Game(const GVE::StrongPointer<Game>& this_);
		inline Game(const Game&) = delete;
		inline virtual ~Game()
		{
		}
	public:
		inline Game& operator = (const Game&) = delete;
	public:
		inline void Add(const GVE::StrongPointer<Entity>& entity_);
		inline void Remove(const GVE::WeakPointer<Entity>& entity_);
	};
}


#pragma region BasicGameClass

#pragma region Entity

inline BasicGameClass::Entity::Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_):
	This<Entity>(this_),
	game(game_)
{
}
inline BasicGameClass::Entity::~Entity()
{
	game->Remove(GetWeak<Entity>());
}

inline GVE::StrongPointer<BasicGameClass::Game> BasicGameClass::Entity::GetGame() const
{
	return GVE::Move(GVE::MakeStrong(game));
}

#pragma endregion

#pragma region Game

inline BasicGameClass::Game::Game(const GVE::StrongPointer<Game>& this_):
	This<Game>(this_)
{
}

inline void BasicGameClass::Game::Add(const GVE::StrongPointer<Entity>& entity_)
{
	auto weak = GVE::MakeWeak(entity_);

	auto it = std::find(entities.begin(), entities.end(), weak);

	if (it == entities.end())
	{
		entities.push_back(weak);
	}
	else
	{
		throw Exception(); // TODO
	}
}
inline void BasicGameClass::Game::Remove(const GVE::WeakPointer<Entity>& entity_)
{
	auto it = std::find(entities.begin(), entities.end(), entity_);

	if (it != entities.end())
	{
		entities.erase(it);
	}
}

#pragma endregion

#pragma endregion


namespace Brothel
{
	class Exception;
	
	class Entity;
	class Game;

	class City;
	class Building;
	class BuildingDependent;
	namespace Buildings
	{
		class Test;
	}
	class Section;

	class Room;
	class RoomDependent;
	namespace Rooms
	{
		class Bedroom;
		namespace Bedrooms
		{
			class Miserable;
		}
	}
	
	class Frontage;
	class FrontageDependent;
	class Groundwork;
	
	class Inmate;
	class Bed;

	class Character;
	class Personnel;


	// friend functions
	inline void Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_);
	inline void Evict(const GVE::StrongPointer<Bed>& bed_);


	class Exception:
		public BasicGameClass::Exception
	{
	};

	class Entity:
		public BasicGameClass::Entity
	{
	public:
		inline Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_);
		inline Entity(const Entity&) = delete;
		inline virtual ~Entity() override = default;
	public:
		inline Entity& operator = (const Entity&) = delete;
	};
	class Game:
		public BasicGameClass::Game
	{
	protected:
		GVE::List<GVE::StrongPointer<City>>			cities;
		GVE::List<GVE::StrongPointer<Personnel>>	personnels;
	public:
		inline explicit								Game(const GVE::StrongPointer<Game>& this_);
		inline										Game(const Game&) = delete;
		inline virtual								~Game() override
		{
		}
	public:
		inline Game&								operator = (const Game&) = delete;
	public:
		inline GVE::WeakPointer<City>				CreateCity();
		inline GVE::WeakPointer<Personnel>			CreatePersonnel();
	};

	class City:
		public Entity
	{
	protected:
		GVE::List<GVE::StrongPointer<Building>>										buildings;
	public:
		inline																		City(const GVE::StrongPointer<City>& this_, const GVE::StrongPointer<Game>& game_);
		inline																		City(const City&) = delete;
		inline virtual																~City() override = default;
	public:
		inline City&																operator = (const City&) = delete;
	public:
		template<class Building_, class... Arguments_> GVE::WeakPointer<Building_>	CreateBuilding(Arguments_&&... arguments_);
		template<class Building_> GVE::WeakPointer<Building_>						CreateBuilding();
	};
	class CityDependent
	{
	protected:
		const GVE::WeakPointer<City>	city;
	public:
		inline explicit					CityDependent(const GVE::StrongPointer<City>& city_);
		inline							CityDependent(const CityDependent&) = delete;
		inline virtual					~CityDependent() = default;
	public:
		inline CityDependent&			operator = (const CityDependent&) = delete;
	public:
		inline GVE::StrongPointer<City>	GetCity() const;
	};
	class Building:
		public Entity,
		public CityDependent
	{
	public:
		using Sections																= GVE::List<GVE::StrongPointer<Section>>;
		using Rooms																	= GVE::List<GVE::StrongPointer<Room>>;
	protected:
		Sections																	sections;
		Rooms																		rooms;
	public:
		inline																		Building(const GVE::StrongPointer<Building>& this_, const GVE::StrongPointer<City>& city_, const GVE::StrongPointer<Game>& game_);
		inline																		Building(const GVE::StrongPointer<Building>& this_, Sections&& sections_, const GVE::StrongPointer<City>& city_, const GVE::StrongPointer<Game>& game_);
		inline																		Building(const Building&) = delete;
		inline virtual																~Building() override = default;
	public:
		inline Building&															operator = (const Building&) = delete;
	public:
		template<class Room_, class... Arguments_> inline GVE::WeakPointer<Room_>	CreateRoom(Arguments_&&... arguments_);
		// template<class Room_> inline GVE::WeakPointer<Room_>						CreateRoom();
	};
	class BuildingDependent
	{
	protected:
		const GVE::WeakPointer<Building>	building;
	public:
		inline explicit						BuildingDependent(const GVE::StrongPointer<Building>& building_);
		inline								BuildingDependent(const BuildingDependent&) = delete;
		inline virtual						~BuildingDependent() = default;
	public:
		inline BuildingDependent&			operator = (const BuildingDependent&) = delete;
	public:
		inline GVE::StrongPointer<Building>	GetBuilding() const;
	};
	namespace Buildings
	{
		class Test:
			public Building
		{
		protected:
			static inline Sections	CreateSections(const GVE::StrongPointer<Test>& building_, const GVE::StrongPointer<Game>& game_);
		public:
			inline					Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<City>& city_, const GVE::StrongPointer<Game>& game_);
			inline					Test(const Test&) = delete;
			inline virtual			~Test() override = default;
		public:
			inline Test&			operator = (const Test&) = delete;
		};
	}
	class Section:
		public Entity,
		public BuildingDependent
	{
	public:
		enum class Type
		{
			None, // not in use

			Inner,
			Outer,
		};
	protected:
		const Type							type;
		GVE::WeakPointer<Groundwork>		attachedGroundwork = GVE::WeakPointer<Groundwork>(nullptr);
	public: // TODO: make private
		GVE::WeakPointer<Section>			left	= GVE::WeakPointer<Section>(nullptr);
		GVE::WeakPointer<Section>			right	= GVE::WeakPointer<Section>(nullptr);
		GVE::WeakPointer<Section>			front	= GVE::WeakPointer<Section>(nullptr);
		GVE::WeakPointer<Section>			back	= GVE::WeakPointer<Section>(nullptr);
	public:
		inline								Section(const GVE::StrongPointer<Section>& this_, const Type& type_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
		inline								Section(const Section&) = delete;
		inline virtual						~Section() override = default;
	public:
		inline Section&						operator = (const Section&) = delete;
	public:
		inline Type							GetType() const;
		inline bool							IsAttached() const;
		inline void							Attach(const GVE::StrongPointer<Groundwork>& groundwork_);
	};

	class Room:
		public Entity,
		public BuildingDependent
	{
	protected:
		const GVE::StrongPointer<Frontage>	frontage;
	public:
		inline								Room(const GVE::StrongPointer<Room>& this_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
		inline								Room(const Room&) = delete;
		inline virtual						~Room() override = default;
	public:
		inline Room&						operator = (const Room&) = delete;
	};
	class RoomDependent
	{
	protected:
		const GVE::WeakPointer<Room>		room;
	public:
		inline explicit						RoomDependent(const GVE::StrongPointer<Room>& room_);
		inline								RoomDependent(const RoomDependent&) = delete;
		inline virtual						~RoomDependent() = default;
	public:
		inline RoomDependent&				operator = (const RoomDependent&) = delete;
	public:
		inline GVE::StrongPointer<Room>		GetRoom() const;
	};

	class Frontage:
		public Entity,
		public RoomDependent
	{
	public:
		using Groundworks						= GVE::List<GVE::StrongPointer<Groundwork>>;
	protected:
		const Groundworks						groundworks;
		const GVE::StrongPointer<Groundwork>	pivot;
	public:
		inline									Frontage(const GVE::StrongPointer<Frontage>& this_, Groundworks&& groundworks_, const GVE::StrongPointer<Groundwork>& pivot_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_);
		inline									Frontage(const Frontage&) = delete;
		inline virtual							~Frontage() override = default;
	public:
		inline Frontage&						operator = (const Frontage&) = delete;
	protected:
		inline bool								Check(const GVE::StrongPointer<Groundwork>& groundwork_, const GVE::StrongPointer<Section>& section_, GVE::Set<GVE::StrongPointer<Groundwork>>& checked_);
		inline void								Connect(const GVE::StrongPointer<Groundwork>& groundwork_, const GVE::StrongPointer<Section>& section_, GVE::Set<GVE::StrongPointer<Groundwork>>& checked_, GVE::Map<GVE::StrongPointer<Groundwork>, GVE::StrongPointer<Section>>& map_);
		inline void								Disconnect(const GVE::StrongPointer<Groundwork>& groundwork_, GVE::Set<GVE::StrongPointer<Groundwork>>& checked_);
	public:
		inline bool								IsConnectPossible(const GVE::StrongPointer<Section>& section_);
		inline void								Connect(const GVE::StrongPointer<Section>& section_);
		inline void								Disconnect();
	};
	class FrontageDependent
	{
	protected:
		const GVE::WeakPointer<Frontage>	frontage;
	public:
		inline explicit						FrontageDependent(const GVE::StrongPointer<Frontage>& frontage_);
		inline								FrontageDependent(const FrontageDependent&) = delete;
		inline virtual						~FrontageDependent() = default;
	public:
		inline FrontageDependent&			operator = (const FrontageDependent&) = delete;
	public:
		inline GVE::StrongPointer<Frontage>	GetFrontage() const;
	};
	class Groundwork:
		public Entity,
		public FrontageDependent
	{
	protected:
		const Section::Type				requiredType;
		GVE::WeakPointer<Section>		linkedSection = GVE::WeakPointer<Section>(nullptr);
	public:
		GVE::WeakPointer<Groundwork>	left	= GVE::WeakPointer<Groundwork>(nullptr);
		GVE::WeakPointer<Groundwork>	right	= GVE::WeakPointer<Groundwork>(nullptr);
		GVE::WeakPointer<Groundwork>	front	= GVE::WeakPointer<Groundwork>(nullptr);
		GVE::WeakPointer<Groundwork>	back	= GVE::WeakPointer<Groundwork>(nullptr);
	public:
		inline							Groundwork(const GVE::StrongPointer<Groundwork>& this_, const Section::Type& requiredType_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Game>& game_);
		inline							Groundwork(const Groundwork&) = delete;
		inline virtual					~Groundwork() override = default;
	public:
		inline Groundwork&				operator = (const Groundwork&) = delete;
	public:
		inline Section::Type			GetRequiredType() const;
		inline void						Link(const GVE::StrongPointer<Section>& section_);
		inline void						Unlink();
	};
	
	class Inmate:
		public Entity
	{
	public:
		friend inline void			Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_);
		friend inline void			Evict(const GVE::StrongPointer<Bed>& bed_);
	protected:
		GVE::WeakPointer<Bed>		bed = GVE::WeakPointer<Bed>(nullptr);
	public:
		inline						Inmate(const GVE::StrongPointer<Inmate>& this_, const GVE::StrongPointer<Game>& game_);
		inline						Inmate(const Inmate&) = delete;
		inline virtual				~Inmate() override = default;
	public:
		inline Inmate&				operator = (const Inmate&) = delete;
	};
	class Bed:
		public Entity,
		public RoomDependent
	{
	public:
		friend inline void			Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_);
		friend inline void			Evict(const GVE::StrongPointer<Bed>& bed_);
	protected:
		GVE::WeakPointer<Inmate>	inmate = GVE::WeakPointer<Inmate>(nullptr);
	public:
		inline						Bed(const GVE::StrongPointer<Bed>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_);
		inline						Bed(const Bed&) = delete;
		inline virtual				~Bed() override = default;
	public:
		inline Bed&					operator = (const Bed&) = delete;
	public:
		inline bool					IsEmpty() const;
	};

	class Character:
		public Entity
	{
	public:
		inline						Character(const GVE::StrongPointer<Character>& this_, const GVE::StrongPointer<Game>& game_);
		inline						Character(const Character&) = delete;
		inline virtual				~Character() override = default;
	public:
		inline Character&			operator = (const Character&) = delete;
	};
	class Personnel:
		public Character,
		public Inmate
	{
	public:
		inline								Personnel(const GVE::StrongPointer<Personnel>& this_, const GVE::StrongPointer<Game>& game_);
		inline								Personnel(const Personnel&) = delete;
		inline virtual						~Personnel() override = default;
	public:
		inline Personnel&					operator = (const Personnel&) = delete;
	public:
		template<class Derived_> inline		GVE::StrongPointer<Derived_> GetThis() const;
		template<class Derived_> inline		GVE::WeakPointer<Derived_> GetWeak() const;
	};

	namespace Rooms
	{
		class Bedroom:
			public Room
		{
		public:
			using Beds				= GVE::List<GVE::StrongPointer<Bed>>;
		protected:
			const Beds				beds;
		public:
			inline					Bedroom(const GVE::StrongPointer<Bedroom>& this_, Beds&& beds_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
			inline					Bedroom(const Bedroom&) = delete;
			inline virtual			~Bedroom() override = default;
		public:
			inline Bedroom&			operator = (const Bedroom&) = delete;
		public:
			inline bool				IsEmptyBedAvailable() const;
			inline void				Settle(const GVE::StrongPointer<Inmate>& inmate_);
		};
		namespace Bedrooms
		{
			class Miserable:
				public Bedroom
			{
			public:
				class Frontage;
			protected:
				class Bed;
			protected:
				static inline Beds							CreateBeds(const GVE::StrongPointer<Miserable>& this_, const GVE::StrongPointer<Game>& game_);
			public:
				inline										Miserable(const GVE::StrongPointer<Miserable>& this_, const GVE::StrongPointer<Section>& pivot_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
				inline										Miserable(const Miserable&) = delete;
				inline virtual								~Miserable() override = default;
			public:
				inline Miserable&							operator = (const Miserable&) = delete;
			};
		}
	}

#pragma region Rooms::Bedrooms::Miserable::Frontage
	class Rooms::Bedrooms::Miserable::Frontage:
		public Brothel::Frontage
	{
	protected:
		struct GroundworksPack
		{
			Groundworks groundworks;
			GVE::StrongPointer<Groundwork> pivot;
		};
	protected:
		static inline GroundworksPack					CreateGroundworks(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Game>& game_);
	protected:
		inline											Frontage(const GVE::StrongPointer<Frontage>& this_, GroundworksPack&& groundworksPack_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_);
	public:
		inline											Frontage(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_);
		inline											Frontage(const Frontage&) = delete;
		inline virtual									~Frontage() override = default;
	public:
		inline Frontage&								operator = (const Frontage&) = delete;
	};
#pragma endregion
#pragma region Rooms::Bedrooms::Miserable::Bed
		class Rooms::Bedrooms::Miserable::Bed:
			public Brothel::Bed
		{
		public:
			inline						Bed(const GVE::StrongPointer<Bed>& this_, const GVE::StrongPointer<Miserable>& room_, const GVE::StrongPointer<Game>& game_);
			inline						Bed(const Bed&) = delete;
			inline virtual				~Bed() override = default;
		public:
			inline Bed&					operator = (const Bed&) = delete;
		};
#pragma endregion
}


#pragma region Brothel

#pragma region Entity

Brothel::Entity::Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_):
	BasicGameClass::Entity(this_, game_)
{
}

#pragma endregion

#pragma region Game

Brothel::Game::Game(const GVE::StrongPointer<Game>& this_):
	BasicGameClass::Game(this_)
{
}

GVE::WeakPointer<Brothel::City> Brothel::Game::CreateCity()
{
	auto ownedThis = GetThis<Game>();

	auto city = GVE::Make<City>(ownedThis);

	cities.push_back(city);

	Add(city);

	auto weak = GVE::MakeWeak(city);

	return weak;
}
GVE::WeakPointer<Brothel::Personnel> Brothel::Game::CreatePersonnel()
{
	auto ownedThis = GetThis<Game>();

	auto personnel = GVE::Make<Personnel>(ownedThis);

	personnels.push_back(personnel);

	Add(GVE::StaticCast<Character>(personnel));

	auto weak = GVE::MakeWeak(personnel);

	return weak;
}

#pragma endregion

#pragma region City

Brothel::City::City(const GVE::StrongPointer<City>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_)
{
}

template<class Building_, class... Arguments_>
GVE::WeakPointer<Building_> Brothel::City::CreateBuilding(Arguments_&&... arguments_)
{
	auto ownedGame = GetGame();
	auto ownedThis = GetThis<City>();

	auto building = GVE::Make<Building_>(GVE::Forward<Arguments_>(arguments_)..., ownedThis, ownedGame);

	buildings.push_back(building);

	auto weak = GVE::MakeWeak(building);

	return GVE::Move(weak);
}
template<class Building_>
GVE::WeakPointer<Building_> Brothel::City::CreateBuilding()
{
	auto ownedGame = GetGame();
	auto ownedThis = GetThis<City>();

	auto building = GVE::Make<Building_>(ownedThis, ownedGame);

	buildings.push_back(building);

	auto weak = GVE::MakeWeak(building);

	return GVE::Move(weak);
}

#pragma endregion

#pragma region CityDependent

Brothel::CityDependent::CityDependent(const GVE::StrongPointer<City>& city_):
	city(GVE::MakeWeak(city_))
{
}

GVE::StrongPointer<Brothel::City> Brothel::CityDependent::GetCity() const
{
	return GVE::MakeStrong(city);
}

#pragma endregion

#pragma region Building

Brothel::Building::Building(const GVE::StrongPointer<Building>& this_, const GVE::StrongPointer<City>& city_, const GVE::StrongPointer<Game>& game_):
	Building(this_, {}, city_, game_)
{
}
Brothel::Building::Building(const GVE::StrongPointer<Building>& this_, Sections&& sections_, const GVE::StrongPointer<City>& city_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	CityDependent(city_),
	sections(sections_)
{
}

template<class Room_, class... Arguments_>
GVE::WeakPointer<Room_> Brothel::Building::CreateRoom(Arguments_&&... arguments_)
{
	auto ownedGame = GetGame();
	auto ownedThis = GetThis<Building>();

	auto room = GVE::Make<Room_>(GVE::Forward<Arguments_>(arguments_)..., ownedThis, ownedGame);

	rooms.push_back(room);

	auto weak = GVE::MakeWeak(room);

	return GVE::Move(weak);
}
// template<class Room_>
// GVE::WeakPointer<Room_> Brothel::Building::CreateRoom()
// {
// 	// TODO
// }

#pragma endregion

#pragma region BuildingDependent

Brothel::BuildingDependent::BuildingDependent(const GVE::StrongPointer<Building>& building_):
	building(GVE::MakeWeak(building_))
{
}

GVE::StrongPointer<Brothel::Building> Brothel::BuildingDependent::GetBuilding() const
{
	return GVE::MakeStrong(building);
}

#pragma endregion

#pragma region Buildings

#pragma region Test

Brothel::Buildings::Test::Sections Brothel::Buildings::Test::CreateSections(const GVE::StrongPointer<Test>& building_, const GVE::StrongPointer<Game>& game_)
{
	Sections sections;

	sections.push_back(GVE::Make<Section>(Section::Type::Inner, building_, game_));
	sections.push_back(GVE::Make<Section>(Section::Type::Outer, building_, game_));

	return GVE::Move(sections);
}

Brothel::Buildings::Test::Test(const GVE::StrongPointer<Test>& this_, const GVE::StrongPointer<City>& city_, const GVE::StrongPointer<Game>& game_):
	Building(this_, GVE::Move(CreateSections(this_, game_)), city_, game_)
{
}

#pragma endregion

#pragma endregion

#pragma region Section

Brothel::Section::Section(const GVE::StrongPointer<Section>& this_, const Type& type_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	BuildingDependent(building_),
	type(type_)
{
}

Brothel::Section::Type Brothel::Section::GetType() const
{
	return type;
}
bool Brothel::Section::IsAttached() const
{
	return attachedGroundwork != nullptr;
}
void Brothel::Section::Attach(const GVE::StrongPointer<Groundwork>& groundwork_)
{
	attachedGroundwork = GVE::MakeWeak(groundwork_);
}

#pragma endregion

#pragma region Room

Brothel::Room::Room(const GVE::StrongPointer<Room>& this_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	BuildingDependent(building_),
	frontage(frontage_)
{
}

#pragma endregion

#pragma region RoomDependent

Brothel::RoomDependent::RoomDependent(const GVE::StrongPointer<Room>& room_):
	room(GVE::MakeWeak(room_))
{
}

GVE::StrongPointer<Brothel::Room> Brothel::RoomDependent::GetRoom() const
{
	return GVE::MakeStrong(room);
}

#pragma endregion

#pragma region Rooms

#pragma region Bedroom

Brothel::Rooms::Bedroom::Bedroom(const GVE::StrongPointer<Bedroom>& this_, Beds&& beds_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Room(this_, frontage_, building_, game_),
	beds(beds_)
{
}

bool Brothel::Rooms::Bedroom::IsEmptyBedAvailable() const
{
	for (auto &bed : beds)
	{
		if (bed->IsEmpty())
		{
			return true;
		}
	}

	return false;
}
void Brothel::Rooms::Bedroom::Settle(const GVE::StrongPointer<Inmate>& inmate_)
{
	for (auto &bed : beds)
	{
		if (bed->IsEmpty())
		{
			Brothel::Settle(inmate_, bed);

			return; // TODO: return bed?
		}
	}

	throw Exception();
}

#pragma endregion

#pragma region Bedrooms

#pragma region Miserable

#pragma region Frontage

Brothel::Rooms::Bedrooms::Miserable::Frontage::GroundworksPack Brothel::Rooms::Bedrooms::Miserable::Frontage::CreateGroundworks(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Game>& game_)
{
	auto g1 = GVE::Make<Groundwork>(Section::Type::Inner, this_, game_);
	auto g2 = GVE::Make<Groundwork>(Section::Type::Outer, this_, game_);

	g1->front = g2;
	g2->back = g1;

	Frontage::Groundworks groundworks =
	{
		g1,
		g2,
	};

	return GroundworksPack
	{
		groundworks,
		g1,
	};
}

Brothel::Rooms::Bedrooms::Miserable::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, GroundworksPack&& groundworksPack_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_):
	Brothel::Frontage(this_, GVE::Move(groundworksPack_.groundworks), groundworksPack_.pivot, room_, game_)
{
}

Brothel::Rooms::Bedrooms::Miserable::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_):
	Frontage(this_, CreateGroundworks(this_, game_), room_, game_)
{
}

#pragma endregion

#pragma region Bed

Brothel::Rooms::Bedrooms::Miserable::Bed::Bed(const GVE::StrongPointer<Bed>& this_, const GVE::StrongPointer<Miserable>& room_, const GVE::StrongPointer<Game>& game_):
	Brothel::Bed(this_, room_, game_)
{
}

#pragma endregion


Brothel::Rooms::Bedrooms::Miserable::Beds Brothel::Rooms::Bedrooms::Miserable::CreateBeds(const GVE::StrongPointer<Miserable>& this_, const GVE::StrongPointer<Game>& game_)
{
	Beds beds;

	beds.push_back(GVE::Make<Bed>(this_, game_));
	beds.push_back(GVE::Make<Bed>(this_, game_));

	return GVE::Move(beds);
}

Brothel::Rooms::Bedrooms::Miserable::Miserable(const GVE::StrongPointer<Miserable>& this_, const GVE::StrongPointer<Section>& pivot_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Bedroom(this_, CreateBeds(this_, game_), GVE::Make<Frontage>(this_, game_), building_, game_)
{
	// TODO: connect frontage to sections
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Frontage

Brothel::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, Groundworks&& groundworks_, const GVE::StrongPointer<Groundwork>& pivot_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	RoomDependent(room_),
	groundworks(groundworks_),
	pivot(pivot_)
{
}

bool Brothel::Frontage::Check(const GVE::StrongPointer<Groundwork>& groundwork_, const GVE::StrongPointer<Section>& section_, GVE::Set<GVE::StrongPointer<Groundwork>>& checked_)
{
	if (checked_.find(groundwork_) != checked_.end())
	{
		return true;
	}

	checked_.insert(groundwork_);

	if (section_->IsAttached() || section_->GetType() != groundwork_->GetRequiredType())
	{
		return false;
	}
	if (groundwork_->left != nullptr && (section_->left == nullptr || !Check(GVE::MakeStrong(groundwork_->left), GVE::MakeStrong(section_->left), checked_)))
	{
		return false;
	}
	if (groundwork_->right != nullptr && (section_->right == nullptr || !Check(GVE::MakeStrong(groundwork_->right), GVE::MakeStrong(section_->right), checked_)))
	{
		return false;
	}
	if (groundwork_->front != nullptr && (section_->front == nullptr || !Check(GVE::MakeStrong(groundwork_->front), GVE::MakeStrong(section_->front), checked_)))
	{
		return false;
	}
	if (groundwork_->back != nullptr && (section_->back == nullptr || !Check(GVE::MakeStrong(groundwork_->back), GVE::MakeStrong(section_->back), checked_)))
	{
		return false;
	}

	return true;
}
void Brothel::Frontage::Connect(const GVE::StrongPointer<Groundwork>& groundwork_, const GVE::StrongPointer<Section>& section_, GVE::Set<GVE::StrongPointer<Groundwork>>& checked_, GVE::Map<GVE::StrongPointer<Groundwork>, GVE::StrongPointer<Section>>& map_)
{
	if (checked_.find(groundwork_) == checked_.end())
	{
		if (section_->IsAttached() || section_->GetType() != groundwork_->GetRequiredType())
		{
			throw Exception(); // TODO
		}

		map_[groundwork_] = section_; // section_->Attach(groundwork_);
		
		checked_.insert(groundwork_);

		if (groundwork_->left != nullptr)
		{
			Connect(GVE::MakeStrong(groundwork_->left), GVE::MakeStrong(section_->left), checked_, map_);
		}
		if (groundwork_->right != nullptr)
		{
			Connect(GVE::MakeStrong(groundwork_->right), GVE::MakeStrong(section_->right), checked_, map_);
		}
		if (groundwork_->front != nullptr)
		{
			Connect(GVE::MakeStrong(groundwork_->front), GVE::MakeStrong(section_->front), checked_, map_);
		}
		if (groundwork_->back != nullptr)
		{
			Connect(GVE::MakeStrong(groundwork_->back), GVE::MakeStrong(section_->back), checked_, map_);
		}
	}
}
void Brothel::Frontage::Disconnect(const GVE::StrongPointer<Groundwork>& groundwork_, GVE::Set<GVE::StrongPointer<Groundwork>>& checked_)
{
	if (checked_.find(groundwork_) == checked_.end())
	{
		groundwork_->Unlink();

		checked_.insert(groundwork_);

		if (groundwork_->left != nullptr)
		{
			Disconnect(GVE::MakeStrong(groundwork_->left), checked_);
		}
		if (groundwork_->right != nullptr)
		{
			Disconnect(GVE::MakeStrong(groundwork_->right), checked_);
		}
		if (groundwork_->front != nullptr)
		{
			Disconnect(GVE::MakeStrong(groundwork_->front), checked_);
		}
		if (groundwork_->back != nullptr)
		{
			Disconnect(GVE::MakeStrong(groundwork_->back), checked_);
		}
	}
}

bool Brothel::Frontage::IsConnectPossible(const GVE::StrongPointer<Section>& section_)
{
	GVE::Set<GVE::StrongPointer<Groundwork>> checked;

	return Check(pivot, section_, checked);
}
void Brothel::Frontage::Connect(const GVE::StrongPointer<Section>& section_)
{
	GVE::Set<GVE::StrongPointer<Groundwork>> checked;
	GVE::Map<GVE::StrongPointer<Groundwork>, GVE::StrongPointer<Section>> map;

	Connect(pivot, section_, checked, map);

	for (auto &i : map)
	{
		i.second->Attach(i.first);
		i.first->Link(i.second);
	}
}
void Brothel::Frontage::Disconnect()
{
	GVE::Set<GVE::StrongPointer<Groundwork>> checked;

	Disconnect(pivot, checked);
}

#pragma endregion

#pragma region FrontageDependent

Brothel::FrontageDependent::FrontageDependent(const GVE::StrongPointer<Frontage>& frontage_):
	frontage(GVE::MakeWeak(frontage_))
{
}

GVE::StrongPointer<Brothel::Frontage> Brothel::FrontageDependent::GetFrontage() const
{
	return GVE::MakeStrong(frontage);
}

#pragma endregion

#pragma region Groundwork

Brothel::Groundwork::Groundwork(const GVE::StrongPointer<Groundwork>& this_, const Section::Type& requiredType_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	FrontageDependent(frontage_),
	requiredType(requiredType_)
{
}

Brothel::Section::Type Brothel::Groundwork::GetRequiredType() const
{
	return requiredType;
}
void Brothel::Groundwork::Link(const GVE::StrongPointer<Section>& section_)
{
	linkedSection = section_;
}
void Brothel::Groundwork::Unlink()
{
	linkedSection->Attach(GVE::StrongPointer<Groundwork>(nullptr));

	linkedSection = nullptr;
}


#pragma endregion

#pragma region Inmate

inline Brothel::Inmate::Inmate(const GVE::StrongPointer<Inmate>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_)
{
}

#pragma endregion

#pragma region Bed

Brothel::Bed::Bed(const GVE::StrongPointer<Bed>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	RoomDependent(room_)
{
}

bool Brothel::Bed::IsEmpty() const
{
	return inmate == nullptr;
}

#pragma endregion

#pragma region Character

Brothel::Character::Character(const GVE::StrongPointer<Character>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_)
{
}

#pragma endregion

#pragma region Personnel

Brothel::Personnel::Personnel(const GVE::StrongPointer<Personnel>& this_, const GVE::StrongPointer<Game>& game_):
	Character(this_, game_),
	Inmate(this_, game_)
{
}

template<class Derived_>
inline GVE::StrongPointer<Derived_> Brothel::Personnel::GetThis() const
{
	return Character::GetThis<Derived_>();
}
template<class Derived_> inline GVE::WeakPointer<Derived_> Brothel::Personnel::GetWeak() const
{
	return Character::GetWeak<Derived_>();
}

#pragma endregion


void Brothel::Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_)
{
	if (bed_->inmate == nullptr)
	{
		if (inmate_->bed != nullptr)
		{
			inmate_->bed->inmate = nullptr;
			inmate_->bed = nullptr;
		}

		bed_->inmate = inmate_;
	}
	else
	{
		throw Exception(); // TODO
	}
}
void Brothel::Evict(const GVE::StrongPointer<Bed>& bed_)
{
	if (bed_->inmate != nullptr)
	{
		bed_->inmate->bed = nullptr;
		bed_->inmate = nullptr;
	}
}

#pragma endregion


#pragma region
#pragma endregion


void main()
{
	using namespace GVE;
	using namespace Brothel;

	auto game = Make<Game>();
	
	auto city = game->CreateCity();
	
	auto building = city->CreateBuilding<Buildings::Test>();
	
	
	auto s1 = GVE::Make<Section>(Section::Type::Inner, GVE::MakeStrong(building), game);
	auto s2 = GVE::Make<Section>(Section::Type::Outer, GVE::MakeStrong(building), game);
	
	s1->front = s2;
	s2->back = s1;

	auto room = [&]()
	{
		auto f = GVE::Make<Rooms::Bedrooms::Miserable::Frontage>(GVE::StrongPointer<Room>(nullptr), game);

		if (f->IsConnectPossible(s1))
		{
			// auto r = GVE::Make<Rooms::Bedrooms::Miserable>(s1, GVE::MakeStrong(building), game);
			auto r = building->CreateRoom<Rooms::Bedrooms::Miserable>(s1);

			return GVE::Move(r);
		}
		else
		{
			throw Exception();
		}
	}();

	auto personnel = game->CreatePersonnel();

	if (room->IsEmptyBedAvailable())
	{
		room->Settle(GVE::MakeStrong(personnel));
	}
	else
	{
		throw Exception();
	}

	// TODO

	std::system("pause");
}