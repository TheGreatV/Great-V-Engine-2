namespace Spaceship
{
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
		class Reactor
		{
		public:
			// inline Resources::Energy Obtain();
		};

		class Fuse
		{
		public:
			inline Resources::Energy Conduct(const Resources::Energy& energy_, const Time::Delta& delta_);
		};
		class Battery
		{
		public:
			inline Resources::Energy Discharge(const Time::Delta& delta_);
		};
		class Accumulator
		{
		public:
			inline void Charge();
			inline Resources::Energy Discharge(const Time::Delta& delta_);
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


void main()
{
}