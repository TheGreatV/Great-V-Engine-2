#pragma region Include

#pragma once

#include <../OpenGL/OpenGL.hpp>
#include <../Graphics/Graphics.hpp>
#include <../Windows Graphics/Windows Graphics.hpp>

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
				namespace GL = GreatVEngine2::OpenGL;
				namespace WGL = GreatVEngine2::OpenGL::OSs::Windows;

				class Output;
				class Engine;

				class Method;
				namespace Methods
				{
					class Forward;
				}


				class Module:
					public Material::Module
				{
				public:
					const String vertexShaderFilename;
					const String fragmentShaderFilename;
					const StrongPointer<Image> albedoImage;
					const StrongPointer<Image> normalsImage;
					const StrongPointer<Image> roughnessImage;
					const StrongPointer<Image> metalnessImage;
					const StrongPointer<Image> occlusionImage;
				public:
					inline Module(const StrongPointer<Module>& this_,
						const String& vertexShaderFilename_,
						const String& fragmentShaderFilename_,
						const StrongPointer<Image>& albedoImage_,
						const StrongPointer<Image>& normalsImage_,
						const StrongPointer<Image>& roughnessImage_,
						const StrongPointer<Image>& metalnessImage_,
						const StrongPointer<Image>& occlusionImage_
					): Material::Module(this_),
						vertexShaderFilename(vertexShaderFilename_),
						fragmentShaderFilename(fragmentShaderFilename_),
						albedoImage(albedoImage_),
						normalsImage(normalsImage_),
						roughnessImage(roughnessImage_),
						metalnessImage(metalnessImage_),
						occlusionImage(occlusionImage_)
					{
					}
					virtual ~Module() override = default;
				};

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
				protected:
					inline virtual void Present(const Memory<APIs::Windows::View>& view_) = 0;
				public:
					inline virtual void SignalPresented(const StrongPointer<View>& view_) override;
				};
				class Engine:
					public Graphics::Engine
				{
				protected:
					StrongPointer<Method> method;
				public:
					inline Engine() = delete;
					inline Engine(const StrongPointer<Engine>& this_, const StrongPointer<Method>& method_);
					inline Engine(const Engine&) = delete;
					inline virtual ~Engine() = default;
				public:
					inline Engine& operator = (const Engine&) = delete;
				public:
					inline virtual StrongPointer<Graphics::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) override;
				};
				class Method:
					public This<Method>
				{
				public:
					inline Method() = delete;
					inline Method(const StrongPointer<Method>& this_);
					inline Method(const Method&) = delete;
					inline virtual ~Method() = default;
				public:
					inline Method& operator = (const Method&) = delete;
				public:
					inline virtual StrongPointer<OpenGL::Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) = 0;
				};

#pragma region Output
				Output::Output(const StrongPointer<Output>& this_):
					Graphics::Output(this_)
				{
				}

				void Output::SignalPresented(const StrongPointer<View>& view_)
				{
					if (auto windowsView = DynamicCast<APIs::Windows::View>(view_))
					{
						Present(windowsView.GetValue());
					}
				}
#pragma endregion
#pragma region Engine
				Engine::Engine(const StrongPointer<Engine>& this_, const StrongPointer<Method>& method_):
					Graphics::Engine(this_),
					method(method_)
				{
				}

				StrongPointer<Graphics::Output> Engine::Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_)
				{
					return method->Render(scene_, camera_);
				}
#pragma endregion
#pragma region Method
				Method::Method(const StrongPointer<Method>& this_):
					This(this_)
				{
				}
#pragma endregion
			}
		}
	}
}


#pragma region
#pragma endregion


