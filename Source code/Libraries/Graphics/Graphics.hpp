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
		class Exception:
			public GreatVEngine2::Exception
		{
		public:
			inline Exception();
			inline Exception(const Text& text_);
		};

		class Output:
			public This<Output>
		{
		public:
			inline Output() = delete;
			inline Output(const StrongPointer<Output>& this_);
			inline Output(const Output&) = delete;
			inline virtual ~Output() = default;
		public:
			inline Output& operator = (const Output&) = delete;
		public:
			inline virtual void SignalPresented(const StrongPointer<View>& view_) = 0;
		};
		class Engine:
			public This<Engine>
		{
		public:
			inline Engine() = delete;
			inline Engine(const StrongPointer<Engine>& this_);
			inline Engine(const Engine&) = delete;
			inline virtual ~Engine() = default;
		public:
			inline Engine& operator = (const Engine&) = delete;
		public:
			inline virtual StrongPointer<Output> Render(const StrongPointer<Scene>& scene_, const StrongPointer<Camera>& camera_) = 0;
		};
		class Scene:
			public This<Scene>
		{
			friend Object;
			friend Engine;
		protected:
			using Objects = Vector<Memory<Object>>;
			using ObjectIt = Objects::size_type;
			using Version = Size;
		protected:
			static inline ObjectIt EmptyIt()
			{
				return std::numeric_limits<Scene::ObjectIt>::max();
			}
		protected:
			Objects objects;
			Version version;
		public:
			inline Scene() = delete;
			inline Scene(const StrongPointer<Scene>& this_);
			inline Scene(const Scene&) = delete;
			inline ~Scene() = default;
		public:
			inline Scene& operator = (const Scene&) = delete;
		protected:
			inline ObjectIt SignalObjectCreated(const Memory<Object>& objectMemory_);
			inline void SignalObjectDestroyed(const Memory<Object>& objectMemory_);
		protected:
			inline void UpdateVersion();
			inline Version GetVersion() const;
		};
		class Object:
			public This<Object>
		{
			friend Scene;
		protected:
			const StrongPointer<Material> material;
			const StrongPointer<Model> model;
			const Memory<Scene> scene;
		protected: // internal
			Scene::ObjectIt it = Scene::EmptyIt(); // index in array of objects inside scene (for fast remove)
		public:
			inline Object() = delete;
			inline Object(const StrongPointer<Object>& this_, const StrongPointer<Material>& material_, const StrongPointer<Model>& model_, const StrongPointer<Scene>& scene_);
			inline Object(const Object&) = delete;
			inline ~Object();
		public:
			inline Object& operator = (const Object&) = delete;
		public:
			inline StrongPointer<Material> GetMaterial() const;
			inline StrongPointer<Model> GetModel() const;
		};
		class Material:
			public This<Material>
		{
		public:
			inline Material() = delete;
			inline Material(const StrongPointer<Material>& this_);
			inline Material(const Material&) = delete;
			inline ~Material() = default;
		public:
			inline Material& operator = (const Material&) = delete;
		};
		class Model:
			public This<Model>
		{
		public:
			inline Model() = delete;
			inline Model(const StrongPointer<Model>& this_);
			inline Model(const Model&) = delete;
			inline ~Model() = default;
		public:
			inline Model& operator = (const Model&) = delete;
		};
		
		class Camera:
			public This<Camera>
		{
		public:
			inline Camera() = delete;
			inline Camera(const StrongPointer<Camera>& this_);
			inline Camera(const Camera&) = delete;
			inline ~Camera() = default;
		public:
			inline Camera& operator = (const Camera&) = delete;
		};

		class View:
			public This<View>
		{
		public:
			inline View() = delete;
			inline View(const StrongPointer<View>& this_);
			inline View(const View&) = delete;
			inline virtual ~View() = default;
		public:
			inline View& operator = (const View&) = delete;
		public:
			inline virtual void Present(const StrongPointer<Output>& renderResult_) = 0;
		};
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region Exception

GreatVEngine2::Graphics::Exception::Exception():
	Exception("Unknown graphics exception.")
{
}
GreatVEngine2::Graphics::Exception::Exception(const Text& text_):
	GreatVEngine2::Exception(text_)
{
}

#pragma endregion

#pragma region Output

GreatVEngine2::Graphics::Output::Output(const StrongPointer<Output>& this_):
	This(this_)
{
}

#pragma endregion

#pragma region Engine

GreatVEngine2::Graphics::Engine::Engine(const StrongPointer<Engine>& this_):
	This(this_)
{
}

#pragma endregion

#pragma region Scene

GreatVEngine2::Graphics::Scene::Scene(const StrongPointer<Scene>& this_):
	This(this_)
{
}

GreatVEngine2::Graphics::Scene::ObjectIt GreatVEngine2::Graphics::Scene::SignalObjectCreated(const Memory<Object>& objectMemory_)
{
	auto it = objects.size();

	objects.push_back(objectMemory_);

	UpdateVersion();
	
	return it;
}
void GreatVEngine2::Graphics::Scene::SignalObjectDestroyed(const Memory<Object>& objectMemory_)
{
	auto &it = objectMemory_->it;
	
	if (it != EmptyIt())
	{
		objects.back()->it = it;
	
		std::swap(objects.back(), objects[it]);
	
		objects.pop_back();
		
		UpdateVersion();
	}
}

void GreatVEngine2::Graphics::Scene::UpdateVersion()
{
	++version;
}
GreatVEngine2::Graphics::Scene::Version GreatVEngine2::Graphics::Scene::GetVersion() const
{
	return version;
}

#pragma endregion

#pragma region Object

GreatVEngine2::Graphics::Object::Object(const StrongPointer<Object>& this_, const StrongPointer<Material>& material_, const StrongPointer<Model>& model_, const StrongPointer<Scene>& scene_):
	This(this_),
	material(material_),
	model(model_),
	scene(scene_.GetValue())
{
#if __GREAT_V_ENGINE_2__DEBUG__
	if (!material || !model)
	{
		throw Exception(); // TODO: should not be nullptr
	}
#endif

	it = scene->SignalObjectCreated(this);
}
GreatVEngine2::Graphics::Object::~Object()
{
	scene->SignalObjectDestroyed(this);
}

GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::Material> GreatVEngine2::Graphics::Object::GetMaterial() const
{
	return material;
}
GreatVEngine2::StrongPointer<GreatVEngine2::Graphics::Model> GreatVEngine2::Graphics::Object::GetModel() const
{
	return model;
}

#pragma endregion

#pragma region Material

GreatVEngine2::Graphics::Material::Material(const StrongPointer<Material>& this_):
	This(this_)
{
}

#pragma endregion

#pragma region Model

GreatVEngine2::Graphics::Model::Model(const StrongPointer<Model>& this_):
	This(this_)
{
}

#pragma endregion

#pragma region Camera

GreatVEngine2::Graphics::Camera::Camera(const StrongPointer<Camera>& this_):
	This(this_)
{
}

#pragma endregion

#pragma region View

GreatVEngine2::Graphics::View::View(const StrongPointer<View>& this_):
	This(this_)
{
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region Notes

/*	1. Scene::Objects and Object::it optimization
	Scene contains array of objects, which is added to and, and each of this
	objects contains an index, under which it is located inside this array.
*/
/*	2. Scene::Version optimization
*/

#pragma endregion


#pragma region
#pragma endregion


