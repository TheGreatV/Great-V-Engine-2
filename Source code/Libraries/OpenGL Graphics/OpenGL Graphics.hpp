#pragma region Include

#pragma once
#pragma warning (disable : 4503) // names is too long

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
			namespace OpenGL
			{
				class Shader
				{
					// TODO
				};
				class Mesh
				{
					// TODO
				};
				class Engine:
					public Graphics::Engine
				{
				protected:
					using ObjectsTable		= Vector<Memory<Object>>;
					using MeshesTable		= Map<Memory<Mesh>, ObjectsTable>;
					using MeshIt			= MeshesTable::iterator;
					using ShadersTable		= Map<Memory<Shader>, MeshesTable>;
					using ShaderIt			= ShadersTable::iterator;
					using ScenesTable		= Map<Memory<Scene>, ShadersTable>;
					using SceneIt			= ScenesTable::iterator;
					using ShadersLookup		= Map<Memory<Material>, Memory<Shader>>;
					using MeshesLookup		= Map<Memory<Model>, Memory<Mesh>>;
					using ScenesMemory		= Vector<Memory<Scene>>;
					using ObjectsLookup		= Map<Memory<Object>, ScenesMemory>;
				protected:
					ScenesTable scenesTable;
					ShadersLookup shadersLookup;
					MeshesLookup meshesLookup;
					ObjectsLookup objectsLookup;
				public:
					inline Engine() = delete;
					inline Engine(const StrongPointer<Engine>& this_);
					inline Engine(const Engine&) = delete;
					inline virtual ~Engine() = default;
				public:
					inline Engine& operator = (const Engine&) = delete;
				protected:
					inline SceneIt FindOrCreate(const Memory<Scene>& sceneMemory_);
					inline ShaderIt FindOrCreate(const SceneIt& sceneIt_, const Memory<Material>& materialMemory_);
					inline MeshIt FindOrCreate(const ShaderIt& shaderIt_, const Memory<Model>& modelMemory_);
					inline Memory<Shader> FindOrCreate(const Memory<Material>& materialMemory_);
					inline Memory<Mesh> FindOrCreate(const Memory<Model>& modelMemory_);
					
					inline SceneIt Find(const Memory<Scene>& sceneMemory_);
					inline ShaderIt Find(const SceneIt& sceneIt_, const Memory<Shader>& shaderMemory_);
					inline MeshIt Find(const ShaderIt& shaderIt_, const Memory<Mesh>& meshMemory_);
					inline Memory<Shader> Find(const Memory<Material>& materialMemory_);
					inline Memory<Mesh> Find(const Memory<Model>& modelMemory_);

					inline void DeleteIfEmpty(const Memory<Model>& modelMemory_, const Memory<Mesh>& meshMemory_, const MeshIt& meshIt_, const ObjectsTable& objectsTable_, MeshesTable& meshesTable_);
					inline void DeleteIfEmpty(const Memory<Material>& materialMemory_, const Memory<Shader>& shaderMemory_, const ShaderIt& shaderIt_, const MeshesTable& meshesTable_, ShadersTable& shadersTable_);
					inline void DeleteIfEmpty(const SceneIt& sceneIt_, const ShadersTable& shadersTable_);

					inline bool Has(const Memory<Object>& objectMemory_) const;
					inline bool Has(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_) const;
					
					inline void Add(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_);
					inline void Add(const Memory<Object>& objectMemory_, ObjectsTable& objectsTable_, const Memory<Scene>& sceneMemory_);

					inline void Remove(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_);
					inline void Remove(const Memory<Object>& objectMemory_, ObjectsTable& objectsTable_, const Memory<Scene>& sceneMemory_);
				protected:
					inline void AddObjectToScene(const Memory<Object>& objectMemory_, const Memory<Scene>& sceneMemory_);
					inline void RemoveObjectFromScene(const Memory<Object>& objectMemory_, const Memory<Scene>& sceneMemory_);
				public:
					inline virtual void SignalMaterialDestroyed(const Memory<Material>& materialMemory_) override;
					inline virtual void SignalModelDestroyed(const Memory<Model>& modelMemory_) override;

					inline virtual void SignalObjectAdded(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_) override;
					inline virtual void SignalObjectRemoved(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_) override;
					
					inline virtual void SignalSceneRendered(const Memory<Scene>& sceneMemory_, const StrongPointer<View>& view_, const StrongPointer<Camera>& camera_) override;
				};
			}
		}
	}
}


#pragma region GreatVEngine2

#pragma region Graphics

#pragma region APIs

#pragma region OpenGL

#pragma region Engine

GreatVEngine2::Graphics::APIs::OpenGL::Engine::Engine(const StrongPointer<Engine>& this_):
	Graphics::Engine(this_)
{
}

GreatVEngine2::Graphics::APIs::OpenGL::Engine::SceneIt GreatVEngine2::Graphics::APIs::OpenGL::Engine::FindOrCreate(const Memory<Scene>& sceneMemory_)
{
	auto it = scenesTable.find(sceneMemory_);

	if (it == scenesTable.end())
	{
		auto &result = scenesTable.emplace(sceneMemory_, ShadersTable()); // result.second is always true
		auto &nIt = result.first;

		return nIt;
	}
	else
	{
		return it;
	}
}
GreatVEngine2::Graphics::APIs::OpenGL::Engine::ShaderIt GreatVEngine2::Graphics::APIs::OpenGL::Engine::FindOrCreate(const SceneIt& sceneIt_, const Memory<Material>& materialMemory_)
{
	auto shaderMemory = FindOrCreate(materialMemory_);
	auto &shadersTable = (*sceneIt_).second;
	auto it = shadersTable.find(shaderMemory);

	if (it == shadersTable.end())
	{
		auto &result = shadersTable.emplace(shaderMemory, MeshesTable()); // result.second is always true
		auto &nIt = result.first;

		return nIt;
	}
	else
	{
		return it;
	}
}
GreatVEngine2::Graphics::APIs::OpenGL::Engine::MeshIt GreatVEngine2::Graphics::APIs::OpenGL::Engine::FindOrCreate(const ShaderIt& shaderIt_, const Memory<Model>& modelMemory_)
{
	auto meshMemory = FindOrCreate(modelMemory_);
	auto &meshesTable = (*shaderIt_).second;
	auto it = meshesTable.find(meshMemory);

	if (it == meshesTable.end())
	{
		auto &result = meshesTable.emplace(meshMemory, ObjectsTable()); // result.second is always true
		auto &nIt = result.first;

		return nIt;
	}
	else
	{
		return it;
	}
}
GreatVEngine2::Memory<GreatVEngine2::Graphics::APIs::OpenGL::Shader> GreatVEngine2::Graphics::APIs::OpenGL::Engine::FindOrCreate(const Memory<Material>& materialMemory_)
{
	auto shaderMemoryIt = shadersLookup.find(materialMemory_);

	if (shaderMemoryIt == shadersLookup.end())
	{
		auto shaderMemory = new Shader();

		shadersLookup[materialMemory_] = shaderMemory;

		return shaderMemory;
	}
	else
	{
		auto shaderMemory = (*shaderMemoryIt).second;

		return shaderMemory;
	}
}
GreatVEngine2::Memory<GreatVEngine2::Graphics::APIs::OpenGL::Mesh> GreatVEngine2::Graphics::APIs::OpenGL::Engine::FindOrCreate(const Memory<Model>& modelMemory_)
{
	auto meshMemoryIt = meshesLookup.find(modelMemory_);

	if (meshMemoryIt == meshesLookup.end())
	{
		auto meshMemory = new Mesh();

		meshesLookup[modelMemory_] = meshMemory;

		return meshMemory;
	}
	else
	{
		auto meshMemory = (*meshMemoryIt).second;

		return meshMemory;
	}
}

GreatVEngine2::Graphics::APIs::OpenGL::Engine::SceneIt GreatVEngine2::Graphics::APIs::OpenGL::Engine::Find(const Memory<Scene>& sceneMemory_)
{
	auto it = scenesTable.find(sceneMemory_);

	if (it != scenesTable.end())
	{
		return it;
	}
	else
	{
		throw Exception(); // TODO
	}
}
GreatVEngine2::Graphics::APIs::OpenGL::Engine::ShaderIt GreatVEngine2::Graphics::APIs::OpenGL::Engine::Find(const SceneIt& sceneIt_, const Memory<Shader>& shaderMemory_)
{
	auto &shadersTable = (*sceneIt_).second;
	auto it = shadersTable.find(shaderMemory_);

	if (it != shadersTable.end())
	{
		return it;
	}
	else
	{
		throw Exception();
	}
}
GreatVEngine2::Graphics::APIs::OpenGL::Engine::MeshIt GreatVEngine2::Graphics::APIs::OpenGL::Engine::Find(const ShaderIt& shaderIt_, const Memory<Mesh>& meshMemory_)
{
	auto &meshesTable = (*shaderIt_).second;
	auto it = meshesTable.find(meshMemory_);

	if (it != meshesTable.end())
	{
		return it;
	}
	else
	{
		throw Exception(); // TODO
	}
}
GreatVEngine2::Memory<GreatVEngine2::Graphics::APIs::OpenGL::Shader> GreatVEngine2::Graphics::APIs::OpenGL::Engine::Find(const Memory<Material>& materialMemory_)
{
	auto shaderMemoryIt = shadersLookup.find(materialMemory_);

	if (shaderMemoryIt != shadersLookup.end())
	{
		auto shaderMemory = (*shaderMemoryIt).second;

		return shaderMemory;
	}
	else
	{
		throw Exception();
	}
}
GreatVEngine2::Memory<GreatVEngine2::Graphics::APIs::OpenGL::Mesh> GreatVEngine2::Graphics::APIs::OpenGL::Engine::Find(const Memory<Model>& modelMemory_)
{
	auto meshMemoryIt = meshesLookup.find(modelMemory_);

	if (meshMemoryIt != meshesLookup.end())
	{
		auto meshMemory = (*meshMemoryIt).second;

		return meshMemory;
	}
	else
	{
		throw Exception();
	}
}

void GreatVEngine2::Graphics::APIs::OpenGL::Engine::DeleteIfEmpty(const Memory<Model>& modelMemory_, const Memory<Mesh>& meshMemory_, const MeshIt& meshIt_, const ObjectsTable& objectsTable_, MeshesTable& meshesTable_)
{
	if (objectsTable_.empty())
	{
		meshesTable_.erase(meshIt_);
	}
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::DeleteIfEmpty(const Memory<Material>& materialMemory_, const Memory<Shader>& shaderMemory_, const ShaderIt& shaderIt_, const MeshesTable& meshesTable_, ShadersTable& shadersTable_)
{
	if (meshesTable_.empty())
	{
		shadersTable_.erase(shaderIt_);
	}
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::DeleteIfEmpty(const SceneIt& sceneIt_, const ShadersTable& shadersTable_)
{
	if (shadersTable_.empty())
	{
		scenesTable.erase(sceneIt_);
	}
}

bool GreatVEngine2::Graphics::APIs::OpenGL::Engine::Has(const Memory<Object>& objectMemory_) const
{
	auto it = objectsLookup.find(objectMemory_);

	return it != objectsLookup.end();
}
bool GreatVEngine2::Graphics::APIs::OpenGL::Engine::Has(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_) const
{
	auto it = objectsLookup.find(objectMemory_);

	if (it != objectsLookup.end())
	{
		auto &scenes = (*it).second;

		auto it2 = std::find(scenes.begin(), scenes.end(), sceneMemory_);

		return it2 != scenes.end();
	}

	return false;
}

void GreatVEngine2::Graphics::APIs::OpenGL::Engine::Add(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_)
{
	auto &result = objectsLookup.insert({objectMemory_, ScenesMemory()});
	auto &it = result.first;
	auto &scenes = (*it).second;

#if __GREAT_V_ENGINE_2__DEBUG__
	if (std::find(scenes.begin(), scenes.end(), sceneMemory_) != scenes.end())
	{
		throw Exception(); // TODO
	}
#endif

	scenes.push_back(sceneMemory_);
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::Add(const Memory<Object>& objectMemory_, ObjectsTable& objectsTable_, const Memory<Scene>& sceneMemory_)
{
#if __GREAT_V_ENGINE_2__DEBUG__
	if (std::find(objectsTable_.begin(), objectsTable_.end(), objectMemory_) != objectsTable_.end())
	{
		throw Exception(); // TODO
	}
#endif

	objectsTable_.push_back(objectMemory_);
	
	Add(sceneMemory_, objectMemory_);
}

void GreatVEngine2::Graphics::APIs::OpenGL::Engine::Remove(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_)
{
	auto it = objectsLookup.find(objectMemory_);

#if __GREAT_V_ENGINE_2__DEBUG__
	if (it == objectsLookup.end())
	{
		throw Exception(); // TODO
	}
#endif

	auto &scenes = (*it).second;
	auto it2 = std::find(scenes.begin(), scenes.end(), sceneMemory_);

#if __GREAT_V_ENGINE_2__DEBUG__
	if (it2 == scenes.end())
	{
		throw Exception(); // TODO
	}
#endif

	scenes.erase(it2);
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::Remove(const Memory<Object>& objectMemory_, ObjectsTable& objectsTable_, const Memory<Scene>& sceneMemory_)
{
	auto it = std::find(objectsTable_.begin(), objectsTable_.end(), objectMemory_);

#if __GREAT_V_ENGINE_2__DEBUG__
	if (it == objectsTable_.end())
	{
		throw Exception(); // TODO
	}
#endif

	objectsTable_.erase(it);

	Remove(sceneMemory_, objectMemory_);
}


void GreatVEngine2::Graphics::APIs::OpenGL::Engine::AddObjectToScene(const Memory<Object>& objectMemory_, const Memory<Scene>& sceneMemory_)
{
#if __GREAT_V_ENGINE_2__DEBUG__
	if (Has(sceneMemory_, objectMemory_))
	{
		throw Exception(); // TODO: already exist
	}
#endif

	auto material = objectMemory_->GetMaterial();
	auto model = objectMemory_->GetModel();

	auto materialMemory = material.GetValue();
	auto modelMemory = model.GetValue();

	auto sceneIt = FindOrCreate(sceneMemory_);
	auto shaderIt = FindOrCreate(sceneIt, materialMemory);
	auto meshIt = FindOrCreate(shaderIt, modelMemory);
	auto &objectsTable = (*meshIt).second;

	Add(objectMemory_, objectsTable, sceneMemory_);
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::RemoveObjectFromScene(const Memory<Object>& objectMemory_, const Memory<Scene>& sceneMemory_)
{
#if __GREAT_V_ENGINE_2__DEBUG__
	if (!Has(sceneMemory_, objectMemory_))
	{
		throw Exception(); // TODO: does not exist
	}
#endif

	auto material = objectMemory_->GetMaterial();
	auto model = objectMemory_->GetModel();

	auto materialMemory = material.GetValue();
	auto modelMemory = model.GetValue();

	auto sceneIt = Find(sceneMemory_);
	auto shaderMemory = Find(materialMemory);
	auto shaderIt = Find(sceneIt, shaderMemory);
	auto meshMemory = Find(modelMemory);
	auto meshIt = Find(shaderIt, meshMemory);
	auto &objectsTable = (*meshIt).second;

	Remove(objectMemory_, objectsTable, sceneMemory_);

	auto &meshesTable = (*shaderIt).second;

	DeleteIfEmpty(modelMemory, meshMemory, meshIt, objectsTable, meshesTable);

	auto &shadersTable = (*sceneIt).second;

	DeleteIfEmpty(materialMemory, shaderMemory, shaderIt, meshesTable, shadersTable);
	DeleteIfEmpty(sceneIt, shadersTable);
}


void GreatVEngine2::Graphics::APIs::OpenGL::Engine::SignalMaterialDestroyed(const Memory<Material>& materialMemory_)
{
	auto it = shadersLookup.find(materialMemory_);

	if (it != shadersLookup.end())
	{
		auto &shaderMemory = (*it).second;

		delete shaderMemory;

		shadersLookup.erase(it);
	}
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::SignalModelDestroyed(const Memory<Model>& modelMemory_)
{
	auto it = meshesLookup.find(modelMemory_);

	if (it != meshesLookup.end())
	{
		auto &meshMemory = (*it).second;

		delete meshMemory;

		meshesLookup.erase(it);
	}
}

void GreatVEngine2::Graphics::APIs::OpenGL::Engine::SignalObjectAdded(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_)
{
	AddObjectToScene(objectMemory_, sceneMemory_);
}
void GreatVEngine2::Graphics::APIs::OpenGL::Engine::SignalObjectRemoved(const Memory<Scene>& sceneMemory_, const Memory<Object>& objectMemory_)
{
	RemoveObjectFromScene(objectMemory_, sceneMemory_);
}

void GreatVEngine2::Graphics::APIs::OpenGL::Engine::SignalSceneRendered(const Memory<Scene>& sceneMemory_, const StrongPointer<View>& view_, const StrongPointer<Camera>& camera_)
{
	auto it = scenesTable.find(sceneMemory_);

	if (it != scenesTable.end())
	{
		auto &shadersTable = (*it).second;

		for (auto &shaderIt : shadersTable)
		{
			auto &shaderMemory = shaderIt.first;
			auto &meshesTable = shaderIt.second;

			for (auto &meshIt : meshesTable)
			{
				auto &meshMemory = meshIt.first;
				auto &objectsTable = meshIt.second;

				for (auto &objectMemory : objectsTable)
				{
					// TODO: render objectMemory
				}
			}
		}
	}
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


