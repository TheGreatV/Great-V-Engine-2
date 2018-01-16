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
		class Exception
		{
			// TODO
		};
		class Engine:
			public This<Engine>
		{
			friend Scene;
			friend Object;
			friend Material;
			friend Model;
		public:
			inline Engine() = delete;
			inline Engine(const StrongPointer<Engine>& this_);
			inline Engine(const Engine&) = delete;
			inline virtual ~Engine() = default;
		public:
			inline Engine& operator = (const Engine&) = delete;
		protected: // life-cycle
			inline virtual void SignalSceneCreated(const Memory<Scene>& sceneMemory_);
			inline virtual void SignalSceneDestroyed(const Memory<Scene>& sceneMemory_);
			inline virtual void SignalObjectCreated(const Memory<Object>& objectMemory_);
			inline virtual void SignalObjectDestroyed(const Memory<Object>& objectMemory_);
			inline virtual void SignalMaterialCreated(const Memory<Material>& materialMemory_);
			inline virtual void SignalMaterialDestroyed(const Memory<Material>& materialMemory_);
			inline virtual void SignalModelCreated(const Memory<Model>& modelMemory_);
			inline virtual void SignalModelDestroyed(const Memory<Model>& modelMemory_);
		protected: // modifying
			inline virtual void SignalObjectAdded(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_);
			inline virtual void SignalObjectRemoved(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_);
		protected: // render
			inline virtual void SignalSceneRendered(const Memory<Scene>& sceneMemory_, const StrongPointer<View>& view_, const StrongPointer<Camera>& camera_);
		};
		class EngineDependent
		{
		protected:
			const WeakPointer<Engine> engine;
		public:
			inline EngineDependent() = delete;
			inline EngineDependent(const StrongPointer<Engine>& engine_);
			inline EngineDependent(const EngineDependent&) = delete;
			inline ~EngineDependent() = default;
		public:
			inline EngineDependent& operator = (const EngineDependent&) = delete;
		public:
			inline WeakPointer<Engine> GetEngine() const;
		};
		class View:
			public This<View>
		{
		public:
			inline View() = delete;
			inline View(const StrongPointer<View>& this_);
			inline View(const View&) = delete;
			inline ~View() = default;
		public:
			inline View& operator = (const View&) = delete;
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
		class Scene:
			public This<Scene>,
			public EngineDependent
		{
		public:
			using Objects = Vector<StrongPointer<Object>>;
		protected:
			Objects objects;
		public:
			inline Scene() = delete;
			inline Scene(const StrongPointer<Scene>& this_, const StrongPointer<Engine>& engine_);
			inline Scene(const Scene&) = delete;
			inline ~Scene() = default;
		public:
			inline Scene& operator = (const Scene&) = delete;
		public:
			inline void Add(const StrongPointer<Object>& object_);
			inline void Remove(const StrongPointer<Object>& object_);
			inline void Render(const StrongPointer<View>& view_, const StrongPointer<Camera>& camera_);
		};
		class Object:
			public This<Object>,
			public EngineDependent
		{
		protected:
			const StrongPointer<Material> material;
			const StrongPointer<Model> model;
		public:
			inline Object() = delete;
			inline Object(const StrongPointer<Object>& this_, const StrongPointer<Material>& material_, const StrongPointer<Model>& model_, const StrongPointer<Engine>& engine_);
			inline Object(const Object&) = delete;
			inline ~Object();
		public:
			inline Object& operator = (const Object&) = delete;
		public:
			inline StrongPointer<Material> GetMaterial() const;
			inline StrongPointer<Model> GetModel() const;
		};
		class Material:
			public This<Material>,
			public EngineDependent
		{
		public:
			inline Material() = delete;
			inline Material(const StrongPointer<Material>& this_, const StrongPointer<Engine>& engine_);
			inline Material(const Material&) = delete;
			inline ~Material();
		public:
			inline Material& operator = (const Material&) = delete;
		};
		class Model:
			public This<Model>,
			public EngineDependent
		{
		public:
			inline Model() = delete;
			inline Model(const StrongPointer<Model>& this_, const StrongPointer<Engine>& engine_);
			inline Model(const Model&) = delete;
			inline ~Model();
		public:
			inline Model& operator = (const Model&) = delete;
		};

		inline void Test();
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region Engine

GreatVEngine2::Graphics::Engine::Engine(const StrongPointer<Engine>& this_):
	This(this_)
{
}

void GreatVEngine2::Graphics::Engine::SignalSceneCreated(const Memory<Scene>& sceneMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalSceneDestroyed(const Memory<Scene>& sceneMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalObjectCreated(const Memory<Object>& objectMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalObjectDestroyed(const Memory<Object>& objectMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalMaterialCreated(const Memory<Material>& materialMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalMaterialDestroyed(const Memory<Material>& materialMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalModelCreated(const Memory<Model>& modelMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalModelDestroyed(const Memory<Model>& modelMemory_)
{
}

void GreatVEngine2::Graphics::Engine::SignalObjectAdded(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_)
{
}
void GreatVEngine2::Graphics::Engine::SignalObjectRemoved(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_)
{
}

void GreatVEngine2::Graphics::Engine::SignalSceneRendered(const Memory<Scene>& sceneMemory_, const StrongPointer<View>& view_, const StrongPointer<Camera>& camera_)
{
}

#pragma endregion

#pragma region EngineDependent

GreatVEngine2::Graphics::EngineDependent::EngineDependent(const StrongPointer<Engine>& engine_):
	engine(engine_)
{
}

GreatVEngine2::WeakPointer<GreatVEngine2::Graphics::Engine> GreatVEngine2::Graphics::EngineDependent::GetEngine() const
{
	return engine;
}

#pragma endregion

#pragma region View

GreatVEngine2::Graphics::View::View(const StrongPointer<View>& this_):
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

#pragma region Scene

GreatVEngine2::Graphics::Scene::Scene(const StrongPointer<Scene>& this_, const StrongPointer<Engine>& engine_):
	This(this_),
	EngineDependent(engine_)
{
}

void GreatVEngine2::Graphics::Scene::Add(const StrongPointer<Object>& object_)
{
#if __GREAT_V_ENGINE_2__DEBUG__
	if (std::find(objects.begin(), objects.end(), object_) != objects.end())
	{
		throw Exception(); // already exist
	}
#endif

	engine->SignalObjectAdded(this, object_.GetValue());

	objects.push_back(object_);
}
void GreatVEngine2::Graphics::Scene::Remove(const StrongPointer<Object>& object_)
{
	// TODO: optimize erasing

	auto it = std::find(objects.begin(), objects.end(), object_);

#if __GREAT_V_ENGINE_2__DEBUG__
	if (it == objects.end())
	{
		throw Exception(); // already exist
	}
#endif

	engine->SignalObjectRemoved(this, object_.GetValue());

	objects.erase(it);
}
void GreatVEngine2::Graphics::Scene::Render(const StrongPointer<View>& view_, const StrongPointer<Camera>& camera_)
{
	engine->SignalSceneRendered(this, view_, camera_);
}

#pragma endregion

#pragma region Object

GreatVEngine2::Graphics::Object::Object(const StrongPointer<Object>& this_, const StrongPointer<Material>& material_, const StrongPointer<Model>& model_, const StrongPointer<Engine>& engine_):
	This(this_),
	EngineDependent(engine_),
	material(material_),
	model(model_)
{
#if __GREAT_V_ENGINE_2__DEBUG__
	if (!material || !model)
	{
		throw Exception(); // TODO: should not be nullptr
	}
#endif

	engine->SignalObjectCreated(this);
}
GreatVEngine2::Graphics::Object::~Object()
{
	engine->SignalObjectDestroyed(this);
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

GreatVEngine2::Graphics::Material::Material(const StrongPointer<Material>& this_, const StrongPointer<Engine>& engine_):
	This(this_),
	EngineDependent(engine_)
{
	engine->SignalMaterialCreated(this);
}
GreatVEngine2::Graphics::Material::~Material()
{
	engine->SignalMaterialDestroyed(this);
}

#pragma endregion

#pragma region Model

GreatVEngine2::Graphics::Model::Model(const StrongPointer<Model>& this_, const StrongPointer<Engine>& engine_):
	This(this_),
	EngineDependent(engine_)
{
	engine->SignalModelCreated(this);
}
GreatVEngine2::Graphics::Model::~Model()
{
	engine->SignalModelDestroyed(this);
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


