#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


// hack
#include <Windows.h>


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
			return GVE::Move(GVE::StaticCast<Derived_>(self));
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
	public:
		using Delta = float;
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
	public:
		inline virtual void Update(const Delta& delta_);
	};
	class Game:
		public This<Game>
	{
	public:
		using Delta = float;
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
	public:
		inline virtual void Update(const Delta& delta_);
	};
}


#pragma region BasicGameClass

#pragma region Entity

BasicGameClass::Entity::Entity(const GVE::StrongPointer<Entity>& this_, const GVE::StrongPointer<Game>& game_):
	This<Entity>(this_),
	game(game_)
{
}
BasicGameClass::Entity::~Entity()
{
	game->Remove(GetWeak<Entity>());
}

GVE::StrongPointer<BasicGameClass::Game> BasicGameClass::Entity::GetGame() const
{
	return GVE::Move(GVE::MakeStrong(game));
}
void BasicGameClass::Entity::Update(const Delta& delta_)
{
}

#pragma endregion

#pragma region Game

BasicGameClass::Game::Game(const GVE::StrongPointer<Game>& this_):
	This<Game>(this_)
{
}

void BasicGameClass::Game::Add(const GVE::StrongPointer<Entity>& entity_)
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
void BasicGameClass::Game::Remove(const GVE::WeakPointer<Entity>& entity_)
{
	auto it = std::find(entities.begin(), entities.end(), entity_);

	if (it != entities.end())
	{
		entities.erase(it);
	}
}
void BasicGameClass::Game::Update(const Delta& delta_)
{
	// entities can be deleted white updating, so foreach can't be used
	auto it = entities.begin();
	
	while (it != entities.end())
	{
		auto entity = GVE::MakeStrong(*it);

		++it;

		entity->Update(delta_);
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
	class CityDependent;

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

		class Workroom;
		class WhiteRoom;
		namespace WhiteRooms
		{
			class SnackBar;
		}
	}
	
	class Frontage;
	class FrontageDependent;
	class Groundwork;
	
	class Inmate;
	class Bed;

	class Workplace;
	class Employee;

	class Character;
	class Personnel;
	class PersonnelState;
	namespace PersonnelStates
	{
		class Idle;
	}

	class Guest;
	class GuestState;
	namespace GuestStates
	{
		class Idle;
	}
	class Seat;

	// friend functions
	inline void Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_);
	inline void Evict(const GVE::WeakPointer<Inmate>& inmate_); // calls only from the ~Inmate()

	inline void Hire(const GVE::StrongPointer<Employee>& employee_, const GVE::StrongPointer<Workplace>& workplace_);
	inline void Dismiss(const GVE::WeakPointer<Employee>& employee_);

	inline void Place(const GVE::StrongPointer<Guest>& guest_, const GVE::StrongPointer<Seat>& seat_);
	inline void Displace(const GVE::WeakPointer<Guest>& guest_);

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
	public:
		inline virtual void															Update(const Delta& delta_) override;
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
		using Guests																= GVE::List<GVE::StrongPointer<Guest>>;
	protected:
		Sections																	sections;
		Rooms																		rooms;
		Guests																		guestsQueue;
		Guests																		guestsInProgress;
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
		inline GVE::WeakPointer<Guest>												CreateGuest();
	protected:
		inline GVE::StrongPointer<Seat>												FindEmptySeat(); // TODO: add requirements
		inline void																	PerformWhiteroomGuests();
	public:
		inline virtual void															Update(const Delta& delta_) override;
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
	public:
		inline virtual void					Update(const Delta& delta_) override;
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
		struct GroundworksPack
		{
			Groundworks							groundworks;
			GVE::StrongPointer<Groundwork>		pivot;
		};
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
		friend void					Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_);
		friend void					Evict(const GVE::WeakPointer<Inmate>& inmate_);
	protected:
		GVE::WeakPointer<Bed>		bed = GVE::WeakPointer<Bed>(nullptr);
	public:
		inline						Inmate(const GVE::StrongPointer<Inmate>& this_, const GVE::StrongPointer<Game>& game_);
		inline						Inmate(const Inmate&) = delete;
		inline virtual				~Inmate() override;
	public:
		inline Inmate&				operator = (const Inmate&) = delete;
	};
	class Bed:
		public Entity,
		public RoomDependent
	{
	public:
		friend void					Settle(const GVE::StrongPointer<Inmate>& inmate_, const GVE::StrongPointer<Bed>& bed_);
		friend void					Evict(const GVE::WeakPointer<Inmate>& inmate_);
	protected:
		GVE::WeakPointer<Inmate>	inmate = GVE::WeakPointer<Inmate>(nullptr);
	public:
		inline						Bed(const GVE::StrongPointer<Bed>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_);
		inline						Bed(const Bed&) = delete;
		inline virtual				~Bed() override;
	public:
		inline Bed&					operator = (const Bed&) = delete;
	public:
		inline bool					IsEmpty() const;
	};

	class Workplace:
		public Entity,
		public RoomDependent
	{
		friend						void Hire(const GVE::StrongPointer<Employee>& employee_, const GVE::StrongPointer<Workplace>& workplace_);
		friend						void Dismiss(const GVE::WeakPointer<Employee>& employee_);
	protected:
		GVE::WeakPointer<Employee>	employee = GVE::WeakPointer<Employee>(nullptr);
	public:
		inline						Workplace(const GVE::StrongPointer<Workplace>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_);
		inline						Workplace(const Workplace&) = delete;
		inline virtual				~Workplace() override;
	public:
		inline Workplace&			operator = (const Workplace&) = delete;
	public:
		inline bool					IsEmpty() const;
	};
	class Employee:
		public Entity
	{
		friend							void Hire(const GVE::StrongPointer<Employee>& employee_, const GVE::StrongPointer<Workplace>& workplace_);
		friend							void Dismiss(const GVE::WeakPointer<Employee>& employee_);
	protected:
		GVE::WeakPointer<Workplace>		workplace = GVE::WeakPointer<Workplace>(nullptr);
	public:
		inline							Employee(const GVE::StrongPointer<Employee>& this_, const GVE::StrongPointer<Game>& game_);
		inline							Employee(const Employee&) = delete;
		inline virtual					~Employee() override;
	public:
		inline Employee&				operator = (const Employee&) = delete;
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
		public Inmate,
		public Employee
	{
	protected:
		GVE::StrongPointer<PersonnelState>	state;
	public:
		inline								Personnel(const GVE::StrongPointer<Personnel>& this_, const GVE::StrongPointer<Game>& game_);
		inline								Personnel(const Personnel&) = delete;
		inline virtual						~Personnel() override = default;
	public:
		inline Personnel&					operator = (const Personnel&) = delete;
	public:
		template<class Derived_> inline		GVE::StrongPointer<Derived_> GetThis() const;
		template<class Derived_> inline		GVE::WeakPointer<Derived_> GetWeak() const;
	public:
		inline virtual void					Update(const Delta& delta_) override;
	};
	class PersonnelState:
		public BasicGameClass::This<PersonnelState>
	{
	public:
		using Delta											= float;
	protected:
		const GVE::WeakPointer<Personnel>					personnel;
	public:
		inline												PersonnelState(const GVE::StrongPointer<PersonnelState>& this_, const GVE::StrongPointer<Personnel>& personnel_);
		inline												PersonnelState(const PersonnelState&) = delete;
		inline virtual										~PersonnelState() = default;
	public:
		inline PersonnelState&								operator = (const PersonnelState&) = delete;
	public:
		inline GVE::StrongPointer<Personnel>				GetPersonnel() const;
		inline virtual GVE::StrongPointer<PersonnelState>	Update(const Delta& delta_);
	};
	namespace PersonnelStates
	{
		class Idle:
			public PersonnelState
		{
		public:
			inline							Idle(const GVE::StrongPointer<Idle>& this_, const GVE::StrongPointer<Personnel>& personnel_);
			inline							Idle(const Idle&) = delete;
			inline virtual					~Idle() override = default;
		public:
			inline Idle&					operator = (const Idle&) = delete;
		};
	}

	class Guest:
		public Character,
		public BuildingDependent
	{
		friend void							Place(const GVE::StrongPointer<Guest>& guest_, const GVE::StrongPointer<Seat>& seat_);
		friend void							Displace(const GVE::WeakPointer<Guest>& guest_);
	protected:
		GVE::WeakPointer<Seat>				seat = GVE::WeakPointer<Seat>(nullptr);
		GVE::StrongPointer<GuestState>		state;
	public:
		inline								Guest(const GVE::StrongPointer<Guest>& this_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
		inline								Guest(const Guest&) = delete;
		inline virtual						~Guest() override = default;
	public:
		inline Guest&						operator = (const Guest&) = delete;
	public:
		inline virtual void					Update(const Delta& delta_) override;
	};
	class GuestState:
		public BasicGameClass::This<GuestState>
	{
	public:
		using Delta										= float;
	protected:
		const GVE::WeakPointer<Guest>					guest;
	public:
		inline											GuestState(const GVE::StrongPointer<GuestState>& this_, const GVE::StrongPointer<Guest>& guest_);
		inline											GuestState(const GuestState&) = delete;
		inline virtual									~GuestState() = default;
	public:
		inline GuestState&								operator = (const GuestState&) = delete;
	public:
		inline GVE::StrongPointer<Guest>				GetGuest() const;
		inline virtual GVE::StrongPointer<GuestState>	Update(const Delta& delta_);
	};
	namespace GuestStates
	{
		class Idle:
			public GuestState
		{
		public:
			inline							Idle(const GVE::StrongPointer<Idle>& this_, const GVE::StrongPointer<Guest>& guest_);
			inline							Idle(const Idle&) = delete;
			inline virtual					~Idle() override = default;
		public:
			inline Idle&					operator = (const Idle&) = delete;
		};
	}
	class Seat:
		public Entity,
		public RoomDependent
	{
		friend void					Place(const GVE::StrongPointer<Guest>& guest_, const GVE::StrongPointer<Seat>& seat_);
		friend void					Displace(const GVE::WeakPointer<Guest>& guest_);
	protected:
		GVE::WeakPointer<Guest>		guest = GVE::WeakPointer<Guest>(nullptr);
	public:
		inline						Seat(const GVE::StrongPointer<Seat>& this_, const GVE::StrongPointer<Rooms::WhiteRoom>& room_, const GVE::StrongPointer<Game>& game_);
		inline						Seat(const Seat&) = delete;
		inline virtual				~Seat() override;
	public:
		inline Seat&				operator = (const Seat&) = delete;
	public:
		inline bool					IsEmpty() const;
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
		public:
			inline virtual void		Update(const Delta& delta_) override;
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

		class Workroom:
			public Room
		{
		public:
			using Workplaces		= GVE::List<GVE::StrongPointer<Workplace>>;
		protected:
			const Workplaces		workplaces;
		public:
			inline					Workroom(const GVE::StrongPointer<Workroom>& this_, Workplaces&& workplaces_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
			inline					Workroom(const Workroom&) = delete;
			inline virtual			~Workroom() override = default;
		public:
			inline Workroom&		operator = (const Workroom&) = delete;
		public:
			inline bool				IsEmptyWorkplaceAvailable() const;
			inline void				Hire(const GVE::StrongPointer<Employee>& employee_);
			inline virtual void		Update(const Delta& delta_) override;
		};
		class WhiteRoom:
			public Workroom
		{
		public:
			using Seats						= GVE::List<GVE::StrongPointer<Seat>>;
		protected:
			const Seats						seats;
		public:
			inline							WhiteRoom(const GVE::StrongPointer<WhiteRoom>& this_, Seats&& seats_, Workplaces&& workplaces_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
			inline							WhiteRoom(const WhiteRoom&) = delete;
			inline virtual					~WhiteRoom() override = default;
		public:
			inline WhiteRoom&				operator = (const WhiteRoom&) = delete;
		public:
			inline GVE::StrongPointer<Seat>	FindEmptySeat() const;
		public:
			inline virtual void				Update(const Delta& delta_) override;
		};
		namespace WhiteRooms
		{
			class SnackBar:
				public WhiteRoom
			{
			public:
				class Frontage;
			protected:
				class Workplace;
				class Seat;
			public:
				static inline Workplaces	CreateWorkplaces(const GVE::StrongPointer<SnackBar>& this_, const GVE::StrongPointer<Game>& game_);
				static inline Seats	CreateSeats(const GVE::StrongPointer<SnackBar>& this_, const GVE::StrongPointer<Game>& game_);
			public:
				inline						SnackBar(const GVE::StrongPointer<SnackBar>& this_, const GVE::StrongPointer<Section>& pivot_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_);
				inline						SnackBar(const SnackBar&) = delete;
				inline virtual				~SnackBar() override = default;
			public:
				inline SnackBar&			operator = (const SnackBar&) = delete;
			};
		}
	}

#pragma region Rooms::Bedrooms::Miserable::Frontage
	class Rooms::Bedrooms::Miserable::Frontage:
		public Brothel::Frontage
	{
	protected:
		static inline GroundworksPack					CreateGroundworks(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Game>& game_);
	protected:
		inline											Frontage(const GVE::StrongPointer<Frontage>& this_, GroundworksPack&& groundworksPack_, const GVE::StrongPointer<Miserable>& room_, const GVE::StrongPointer<Game>& game_);
	public:
		inline											Frontage(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Miserable>& room_, const GVE::StrongPointer<Game>& game_);
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

#pragma region Rooms::WhiteRooms::SnackBar::Frontage
	class Rooms::WhiteRooms::SnackBar::Frontage:
		public Brothel::Frontage
	{
	protected:
		static inline GroundworksPack					CreateGroundworks(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Game>& game_);
	protected:
		inline											Frontage(const GVE::StrongPointer<Frontage>& this_, GroundworksPack&& groundworksPack_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_);
	public:
		inline											Frontage(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_);
		inline											Frontage(const Frontage&) = delete;
		inline virtual									~Frontage() override = default;
	public:
		inline Frontage&								operator = (const Frontage&) = delete;
	};
#pragma endregion
#pragma region Rooms::WhiteRooms::SnackBar::Workplace
		class Rooms::WhiteRooms::SnackBar::Workplace:
			public Brothel::Workplace
		{
		public:
			inline						Workplace(const GVE::StrongPointer<Workplace>& this_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_);
			inline						Workplace(const Workplace&) = delete;
			inline virtual				~Workplace() override = default;
		public:
			inline Workplace&			operator = (const Workplace&) = delete;
		};
#pragma endregion
#pragma region Rooms::WhiteRooms::SnackBar::Seat
		class Rooms::WhiteRooms::SnackBar::Seat:
			public Brothel::Seat
		{
		public:
			inline				Seat(const GVE::StrongPointer<Seat>& this_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_);
			inline				Seat(const Seat&) = delete;
			inline virtual		~Seat() override = default;
		public:
			inline Seat&		operator = (const Seat&) = delete;
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

void Brothel::City::Update(const Delta& delta_)
{
	auto &it = buildings.begin();

	while (it != buildings.end())
	{
		auto &building = *it;

		++it;

		building->Update(delta_);
	}
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
GVE::WeakPointer<Brothel::Guest> Brothel::Building::CreateGuest()
{
	auto ownedGame = GetGame();
	auto ownedThis = GetThis<Building>();

	auto guest = GVE::Make<Guest>(ownedThis, ownedGame);

	guestsQueue.push_back(guest);

	auto weak = GVE::MakeWeak(guest);

	return GVE::Move(weak);
}

GVE::StrongPointer<Brothel::Seat> Brothel::Building::FindEmptySeat()
{
	for (auto &room : rooms)
	{
		if (auto whiteRoom = GVE::DynamicCast<Brothel::Rooms::WhiteRoom>(room))
		{
			if (auto seat = whiteRoom->FindEmptySeat())
			{
				return seat;
			}
		}
	}

	return GVE::StrongPointer<Seat>(nullptr);
}
void Brothel::Building::PerformWhiteroomGuests()
{
	if (!guestsQueue.empty())
	{
		auto guest = guestsQueue.front();
		auto seat = FindEmptySeat();

		Place(guest, seat);

		guestsQueue.pop_front();
		guestsInProgress.push_back(guest);
	}
}

void Brothel::Building::Update(const Delta& delta_)
{
	PerformWhiteroomGuests();

	sections;
	{
		auto &it = sections.begin();

		while (it != sections.end())
		{
			auto &section = *it;

			++it;

			section->Update(delta_);
		}
	}

	rooms;
	{
		auto &it = rooms.begin();

		while (it != rooms.end())
		{
			auto &room = *it;

			++it;

			room->Update(delta_);
		}
	}

	/*guests;
	{
		auto &it = guests.begin();

		while (it != guests.end())
		{
			auto &guest = *it;

			++it;

			guest->Update(delta_);
		}
	}*/
}

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

void Brothel::Section::Update(const Delta& delta_)
{
	// TODO
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

void Brothel::Rooms::Bedroom::Update(const Delta& delta_)
{
	auto &it = beds.begin();

	while (it != beds.end())
	{
		auto &bed = *it;

		++it;

		bed->Update(delta_);
	}
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

Brothel::Rooms::Bedrooms::Miserable::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, GroundworksPack&& groundworksPack_, const GVE::StrongPointer<Miserable>& room_, const GVE::StrongPointer<Game>& game_):
	Brothel::Frontage(this_, GVE::Move(groundworksPack_.groundworks), groundworksPack_.pivot, room_, game_)
{
}

Brothel::Rooms::Bedrooms::Miserable::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Miserable>& room_, const GVE::StrongPointer<Game>& game_) :
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
	frontage->Connect(pivot_); // TODO: connect frontage to sections
}

#pragma endregion

#pragma endregion

#pragma region Workroom

Brothel::Rooms::Workroom::Workroom(const GVE::StrongPointer<Workroom>& this_, Workplaces&& workplaces_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Room(this_, frontage_, building_, game_),
	workplaces(workplaces_)
{
}

bool Brothel::Rooms::Workroom::IsEmptyWorkplaceAvailable() const
{
	for (auto &workplace : workplaces)
	{
		if (workplace->IsEmpty())
		{
			return true;
		}
	}

	return false;
}
void Brothel::Rooms::Workroom::Hire(const GVE::StrongPointer<Employee>& employee_)
{
	for (auto &workplace : workplaces)
	{
		if (workplace->IsEmpty())
		{
			Brothel::Hire(employee_, workplace);

			return;
		}
	}

	throw Exception(); // TODO
}
void Brothel::Rooms::Workroom::Update(const Delta& delta_)
{
	auto &it = workplaces.begin();

	while (it != workplaces.end())
	{
		auto &workplace = *it;

		++it;

		workplace->Update(delta_);
	}
}

#pragma endregion

#pragma region WhiteRoom

Brothel::Rooms::WhiteRoom::WhiteRoom(const GVE::StrongPointer<WhiteRoom>& this_, Seats&& seats_, Workplaces&& workplaces_, const GVE::StrongPointer<Frontage>& frontage_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Workroom(this_, GVE::Move(workplaces_), frontage_, building_, game_),
	seats(seats_)
{
}

inline GVE::StrongPointer<Brothel::Seat> Brothel::Rooms::WhiteRoom::FindEmptySeat() const
{
	for (auto &seat : seats)
	{
		if (seat->IsEmpty())
		{
			return seat;
		}
	}

	return GVE::StrongPointer<Seat>(nullptr);
}

void Brothel::Rooms::WhiteRoom::Update(const Delta& delta_)
{
	Workroom::Update(delta_);

	auto &it = seats.begin();

	while (it != seats.end())
	{
		auto &seat = *it;

		++it;

		seat->Update(delta_);
	}
}

#pragma endregion

#pragma region WhiteRooms

#pragma region SnackBar

#pragma region Frontage

Brothel::Rooms::WhiteRooms::SnackBar::Frontage::GroundworksPack Brothel::Rooms::WhiteRooms::SnackBar::Frontage::CreateGroundworks(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<Game>& game_)
{
	auto g1 = GVE::Make<Groundwork>(Section::Type::Inner, this_, game_);
	auto g2 = GVE::Make<Groundwork>(Section::Type::Outer, this_, game_);

	auto g3 = GVE::Make<Groundwork>(Section::Type::Inner, this_, game_);
	auto g4 = GVE::Make<Groundwork>(Section::Type::Outer, this_, game_);

	g1->front = g2;
	g2->back = g1;

	g3->front = g4;
	g4->back = g3;

	g1->right = g3;
	g3->left = g1;

	g2->right = g4;
	g4->left = g2;

	Frontage::Groundworks groundworks =
	{
		g1,
		g2,
		g3,
		g4,
	};

	return GroundworksPack
	{
		groundworks,
		g1,
	};
}

Brothel::Rooms::WhiteRooms::SnackBar::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, GroundworksPack&& groundworksPack_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_):
	Brothel::Frontage(this_, GVE::Move(groundworksPack_.groundworks), groundworksPack_.pivot, room_, game_)
{
}

Brothel::Rooms::WhiteRooms::SnackBar::Frontage::Frontage(const GVE::StrongPointer<Frontage>& this_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_) :
	Frontage(this_, CreateGroundworks(this_, game_), room_, game_)
{
}

#pragma endregion

#pragma region Workplace

Brothel::Rooms::WhiteRooms::SnackBar::Workplace::Workplace(const GVE::StrongPointer<Workplace>& this_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_):
	Brothel::Workplace(this_, room_, game_)
{
}

#pragma endregion

#pragma region Seat

Brothel::Rooms::WhiteRooms::SnackBar::Seat::Seat(const GVE::StrongPointer<Seat>& this_, const GVE::StrongPointer<SnackBar>& room_, const GVE::StrongPointer<Game>& game_):
	Brothel::Seat(this_, room_, game_)
{
}

#pragma endregion

Brothel::Rooms::WhiteRooms::SnackBar::Workplaces Brothel::Rooms::WhiteRooms::SnackBar::CreateWorkplaces(const GVE::StrongPointer<SnackBar>& this_, const GVE::StrongPointer<Game>& game_)
{
	Workplaces workplaces;

	workplaces.push_back(GVE::Make<Workplace>(this_, game_));
	workplaces.push_back(GVE::Make<Workplace>(this_, game_));
	workplaces.push_back(GVE::Make<Workplace>(this_, game_));

	return GVE::Move(workplaces);
}
Brothel::Rooms::WhiteRooms::SnackBar::Seats	Brothel::Rooms::WhiteRooms::SnackBar::CreateSeats(const GVE::StrongPointer<SnackBar>& this_, const GVE::StrongPointer<Game>& game_)
{
	Seats seats;

	seats.push_back(GVE::Make<Seat>(this_, game_));
	seats.push_back(GVE::Make<Seat>(this_, game_));
	seats.push_back(GVE::Make<Seat>(this_, game_));
	seats.push_back(GVE::Make<Seat>(this_, game_));
	seats.push_back(GVE::Make<Seat>(this_, game_));

	return Move(seats);
}

Brothel::Rooms::WhiteRooms::SnackBar::SnackBar(const GVE::StrongPointer<SnackBar>& this_, const GVE::StrongPointer<Section>& pivot_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	WhiteRoom(this_, CreateSeats(this_, game_), CreateWorkplaces(this_, game_), GVE::Make<Frontage>(this_, game_), building_, game_)
{
	frontage->Connect(pivot_);
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
inline Brothel::Inmate::~Inmate()
{
	Evict(GetWeak<Inmate>());
}

#pragma endregion

#pragma region Bed

Brothel::Bed::Bed(const GVE::StrongPointer<Bed>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	RoomDependent(room_)
{
}
Brothel::Bed::~Bed()
{
	if (inmate != nullptr)
	{
		Evict(inmate);
	}
}

bool Brothel::Bed::IsEmpty() const
{
	return inmate == nullptr;
}

#pragma endregion

#pragma region Workplace

Brothel::Workplace::Workplace(const GVE::StrongPointer<Workplace>& this_, const GVE::StrongPointer<Room>& room_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	RoomDependent(room_)
{
}
Brothel::Workplace::~Workplace()
{
	if (employee != nullptr)
	{
		Dismiss(employee);
	}
}

bool Brothel::Workplace::IsEmpty() const
{
	return employee == nullptr;
}

#pragma endregion

#pragma region Employee

Brothel::Employee::Employee(const GVE::StrongPointer<Employee>& this_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_)
{
}
Brothel::Employee::~Employee()
{
	Dismiss(GetWeak<Employee>());
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
	Inmate(this_, game_),
	Employee(this_, game_),
	state(GVE::Make<PersonnelStates::Idle>(this_))
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

void Brothel::Personnel::Update(const Delta& delta_)
{
	state = state->Update(delta_);
}

#pragma endregion

#pragma region PersonnelState

Brothel::PersonnelState::PersonnelState(const GVE::StrongPointer<PersonnelState>& this_, const GVE::StrongPointer<Personnel>& personnel_):
	This(this_),
	personnel(personnel_)
{
}

GVE::StrongPointer<Brothel::Personnel> Brothel::PersonnelState::GetPersonnel() const
{
	return GVE::MakeStrong(personnel);
}
GVE::StrongPointer<Brothel::PersonnelState>	Brothel::PersonnelState::Update(const Delta& delta_)
{
	return GetThis<PersonnelState>();
}

#pragma endregion

#pragma region PersonnelStates

#pragma region Idle

Brothel::PersonnelStates::Idle::Idle(const GVE::StrongPointer<Idle>& this_, const GVE::StrongPointer<Personnel>& personnel_):
	PersonnelState(this_, personnel_)
{
}

#pragma endregion

#pragma endregion

#pragma region Guest

Brothel::Guest::Guest(const GVE::StrongPointer<Guest>& this_, const GVE::StrongPointer<Building>& building_, const GVE::StrongPointer<Game>& game_):
	Character(this_, game_),
	BuildingDependent(building_),
	state(GVE::Make<GuestStates::Idle>(this_))
{
}

void Brothel::Guest::Update(const Delta& delta_)
{
	state = state->Update(delta_);
}

#pragma endregion

#pragma region GuestState

Brothel::GuestState::GuestState(const GVE::StrongPointer<GuestState>& this_, const GVE::StrongPointer<Guest>& guest_):
	This(this_),
	guest(guest_)
{
}

GVE::StrongPointer<Brothel::Guest> Brothel::GuestState::GetGuest() const
{
	return GVE::MakeStrong(guest);
}
GVE::StrongPointer<Brothel::GuestState>	Brothel::GuestState::Update(const Delta& delta_)
{
	return GetThis<GuestState>();
}

#pragma endregion

#pragma region GuestStates

#pragma region Idle

Brothel::GuestStates::Idle::Idle(const GVE::StrongPointer<Idle>& this_, const GVE::StrongPointer<Guest>& guest_):
	GuestState(this_, guest_)
{
}

#pragma endregion

#pragma endregion

#pragma region Seat

Brothel::Seat::Seat(const GVE::StrongPointer<Seat>& this_, const GVE::StrongPointer<Rooms::WhiteRoom>& room_, const GVE::StrongPointer<Game>& game_):
	Entity(this_, game_),
	RoomDependent(room_)
{
}
Brothel::Seat::~Seat()
{
	if (guest != nullptr)
	{
		Displace(guest);
	}
}

bool Brothel::Seat::IsEmpty() const
{
	return guest == nullptr;
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

		inmate_->bed = bed_;
		bed_->inmate = inmate_;
	}
	else
	{
		throw Exception(); // TODO
	}
}
void Brothel::Evict(const GVE::WeakPointer<Inmate>& inmate_)
{
	if (inmate_->bed.IsExpired()) // bed may be destroyed before inmate
	{
		inmate_->bed = nullptr; // TODO: remove?
	}
	else
	{
		inmate_->bed->inmate = nullptr; // inamete_->bed whould always != nullptr
		inmate_->bed = nullptr; // TODO: remove?
	}
}

void Brothel::Hire(const GVE::StrongPointer<Employee>& employee_, const GVE::StrongPointer<Workplace>& workplace_)
{
	if (employee_->workplace != nullptr)
	{
		employee_->workplace->employee = nullptr;
	}

	if (workplace_->employee != nullptr)
	{
		workplace_->employee->workplace = nullptr;
	}

	workplace_->employee = employee_;
	employee_->workplace = workplace_;
}
void Brothel::Dismiss(const GVE::WeakPointer<Employee>& employee_)
{
	if (employee_->workplace != nullptr)
	{
		employee_->workplace->employee = nullptr;
		employee_->workplace = nullptr;
	}
}

void Brothel::Place(const GVE::StrongPointer<Guest>& guest_, const GVE::StrongPointer<Seat>& seat_)
{
	if (guest_->seat != nullptr)
	{
		guest_->seat->guest = nullptr;
		guest_->seat = nullptr;
	}

	if (seat_->guest == nullptr)
	{
		seat_->guest = guest_;
		guest_->seat = seat_;
	}
	else
	{
		throw Exception(); // TODO: where this poor man should go?
	}
}
void Brothel::Displace(const GVE::WeakPointer<Guest>& guest_)
{
	if (!guest_->seat.IsExpired())
	{
		guest_->seat->guest = nullptr;
	}

	guest_->seat = nullptr;
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

	s1->front = s2; s2->back = s1;

	auto s3 = GVE::Make<Section>(Section::Type::Inner, GVE::MakeStrong(building), game);
	auto s4 = GVE::Make<Section>(Section::Type::Outer, GVE::MakeStrong(building), game);

	s3->front = s4; s4->back = s3;

	auto s5 = GVE::Make<Section>(Section::Type::Inner, GVE::MakeStrong(building), game);
	auto s6 = GVE::Make<Section>(Section::Type::Outer, GVE::MakeStrong(building), game);

	s5->front = s6; s6->back = s5;

	s1->right = s3; s3->left = s1;
	s2->right = s4; s4->left = s2;

	s3->right = s5; s5->left = s3;
	s4->right = s6; s6->left = s4;


	auto bedroom = [&]()
	{
		auto f = GVE::Make<Rooms::Bedrooms::Miserable::Frontage>(GVE::StrongPointer<Room>(nullptr), game);

		if (f->IsConnectPossible(s1))
		{
			auto r = building->CreateRoom<Rooms::Bedrooms::Miserable>(s1);

			return GVE::Move(r);
		}
		else
		{
			throw GVE::Exception();
		}
	}();

	auto personnel = game->CreatePersonnel();

	if (bedroom->IsEmptyBedAvailable())
	{
		bedroom->Settle(GVE::MakeStrong(personnel));
	}
	else
	{
		throw GVE::Exception();
	}

	auto snackBar = [&]()
	{
		auto f = GVE::Make<Rooms::WhiteRooms::SnackBar::Frontage>(GVE::StrongPointer<Room>(nullptr), game);

		if (f->IsConnectPossible(s3))
		{
			auto r = building->CreateRoom<Rooms::WhiteRooms::SnackBar>(s3);

			return GVE::Move(r);
		}
		else
		{
			throw GVE::Exception();
		}
	}();

	if (snackBar->IsEmptyWorkplaceAvailable())
	{
		snackBar->Hire(GVE::MakeStrong(personnel));
	}
	else
	{
		throw GVE::Exception(); // TODO
	}

	auto guest = building->CreateGuest();

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		float d = 1.0f / 60.0f;

		game->Update(d);

		Sleep(static_cast<DWORD>(d * 1000.0f));
	}

	// TODO

	std::system("pause");
}