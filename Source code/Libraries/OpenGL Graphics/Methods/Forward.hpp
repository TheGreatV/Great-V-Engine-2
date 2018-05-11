#pragma region Include

#pragma once
#pragma warning (disable : 4503) // names is too long

#include "../Header.hpp"

#include <string>
#include <fstream>
#include <streambuf>

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace Graphics
	{
		namespace APIs
		{
			namespace OpenGL
			{
				namespace Methods
				{
					class Forward:
						public Method
					{
					protected:
						class Output; friend Output;
					public:
						inline Forward() = delete;
						inline Forward(const StrongPointer<Forward>& this_);
						inline Forward(const Forward&) = delete;
						inline virtual ~Forward() = default;
					public:
						inline Forward& operator = (const Forward&) = delete;
					public:
						inline virtual StrongPointer<OpenGL::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
					};
#pragma region Forward
					GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Forward(const StrongPointer<Forward>& this_):
						Method(this_)
					{
					}

					GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::APIs::OpenGL::Output> GreatVEngine2::Graphics::APIs::OpenGL::Methods::Forward::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
					{
						throw NotImplementedException();
					}
#pragma endregion
#pragma region Forward::Output
					class Forward::Output:
						public OpenGL::Output
					{
					protected:
						const StrongPointer<Camera> camera;
					public:
						inline Output() = delete;
						inline Output(const StrongPointer<Output>& this_, const StrongPointer<Camera>& camera_);
						inline Output(const Output&) = delete;
						inline virtual ~Output() = default;
					public:
						inline Output& operator = (const Output&) = delete;
					protected:
						inline virtual void Present(const Memory<APIs::Windows::View>& view_) override;
					};
					Forward::Output::Output(const StrongPointer<Output>& this_, const StrongPointer<Camera>& camera_):
						OpenGL::Output(this_),
						camera(camera_)
					{
					}

					void Forward::Output::Present(const Memory<APIs::Windows::View>& view_)
					{
						// renderer->PresentOn(view_, camera);
					}
#pragma endregion
				}
			}
		}
	}
}


#pragma region
#pragma endregion


