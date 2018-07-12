#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


namespace Spaceship
{
	class Entity;
	class Game;


	namespace Power
	{
		class Circuit;
		class CircuitComponent;

		class Generator;
		class Fuse;
		class Battery;
		class Accumulator;
	}
}
namespace Spaceship
{
	class Entity:
		public GVE::This<Entity>
	{
	protected:
		const GVE::Memory<Game> game;
	public:
		inline Entity(const GVE::StrongPointer<Entity>& this_, const GVE::Memory<Game>& game_);
		inline virtual ~Entity() = default;
	};
	class Game:
		public GVE::This<Game>
	{
	public:
		inline Game(const GVE::StrongPointer<Game>& this_);
	public:
		inline void SignalCreated(const GVE::Memory<Power::CircuitComponent>& circuitComponentMemory_);
		inline void SignalDeleted(const GVE::Memory<Power::CircuitComponent>& circuitComponentMemory_);
	};


	namespace Time
	{
		class Delta
		{
		};
	}

	namespace Resources
	{
		// Power
		class Energy
		{
		};

		// Ventilation
		class RespiratoryMixture
		{
		};
		class Oxygen
		{
		};
		class CarbonDioxide
		{
		};

		// Thermoregulation
		class Heat
		{
		};
		class Coolant
		{
		};
	}

	namespace Communication
	{
		class Controller
		{
		};
	}

	namespace Power
	{
		class Circuit
		{
		protected:
			GVE::Set<GVE::Memory<CircuitComponent>> components;
		};
		class CircuitComponent:
			public virtual Entity
		{
		protected:
			GVE::Memory<const Circuit> circuit = nullptr;
		public:
			inline CircuitComponent(const GVE::StrongPointer<CircuitComponent>& this_, const GVE::Memory<Game>& game_);
			inline ~CircuitComponent();
		};

		class Generator
		{
		};
		class Fuse
		{
		};
		class Battery // not rechargable
		{
		};
		class Accumulator // rechargable
		{
		};
	}

	namespace Light
	{
		class Cartrige
		{
		};
		class Lamp
		{
		};
	}

	namespace Ventilation
	{
		class RespiratoryMixtureReservoir // TODO: move to RespiratoryMixture?
		{
		};
		class OxygenReservoir // TODO: move to Oxygen?
		{
		};
		class CarbonDioxideReservoir // TODO: move to CarbonDioxide?
		{
		};

		class Node
		{
		};
		class System
		{
		};
	}

	namespace Thermoregulation
	{
		class CoolantReservoir
		{
		};

		class Fan
		{
		};
		class Radiator
		{
		};

		class Node
		{
		};
		class System
		{
		};
	}
}
namespace Spaceship
{
#pragma region Entity
	Entity::Entity(const GVE::StrongPointer<Entity>& this_, const GVE::Memory<Game>& game_):
		This(this_),
		game(game_)
	{
	}
#pragma endregion
#pragma region Game
	Game::Game(const GVE::StrongPointer<Game>& this_):
		This(this_)
	{
	}

	void Game::SignalCreated(const GVE::Memory<Power::CircuitComponent>& circuitComponentMemory_)
	{
	}
	void Game::SignalDeleted(const GVE::Memory<Power::CircuitComponent>& circuitComponentMemory_)
	{
	}
#pragma endregion

	namespace Power
	{
		CircuitComponent::CircuitComponent(const GVE::StrongPointer<CircuitComponent>& this_, const GVE::Memory<Game>& game_):
			Entity(this_, game_)
		{
			game->SignalCreated(this);
		}
		CircuitComponent::~CircuitComponent()
		{
			game->SignalDeleted(this);
		}
	}
}


#pragma region
#pragma endregion


void main()
{
	auto game = GVE::Make<Spaceship::Game>();
}