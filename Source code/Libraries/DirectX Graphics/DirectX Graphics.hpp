#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace Graphics
	{
		namespace APIs
		{
			namespace DirectX
			{
				class Output:
					public Graphics::Output
				{
				public:
					inline Output() = delete;
					inline Output(const StrongPointer<Output>& this_);
					inline Output(const Output&) = delete;
					inline virtual ~Output() = default;
				public:
					inline Output& operator = (const Output&) = delete;
				public:
					inline virtual void SignalPresented(const StrongPointer<View>& view_) override;
				};
				class Engine:
					public Graphics::Engine
				{
				public:
					inline Engine() = delete;
					inline Engine(const StrongPointer<Engine>& this_);
					inline Engine(const Engine&) = delete;
					inline virtual ~Engine() = default;
				public:
					inline Engine& operator = (const Engine&) = delete;
				public:
					inline virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
				};
			}
		}
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region APIs

#pragma region DirectX

#pragma region Output

GreatVEngine2::Graphics::APIs::DirectX::Output::Output(const StrongPointer<Output>& this_):
	Graphics::Output(this_)
{
}

void GreatVEngine2::Graphics::APIs::DirectX::Output::SignalPresented(const StrongPointer<View>& view_)
{
	if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
	{
		// TODO
	}
}

#pragma endregion

#pragma region Engine

GreatVEngine2::Graphics::APIs::DirectX::Engine::Engine(const StrongPointer<Engine>& this_):
	Graphics::Engine(this_)
{
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::Output> GreatVEngine2::Graphics::APIs::DirectX::Engine::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
{
	auto output = Make<Output>();

	return Move(output);
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


