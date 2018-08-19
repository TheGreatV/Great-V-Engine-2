#pragma region Include

#pragma once

// #include "Header.hpp"
#include <../Common/Common.hpp>

// #include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace Assimp
	{
		std::vector<std::uint8_t> f(const String& filePath_)
		{
			const aiScene* scene = aiImportFile(
				filePath_.c_str(),
				0
				// | aiProcess_CalcTangentSpace
				// | aiProcess_Triangulate
				// | aiProcess_JoinIdenticalVertices
				// | aiProcess_SortByPType
			);

			if (scene == nullptr)
			{
				const auto errorString = aiGetErrorString();

				throw Exception();
			}

			const auto meshesCount		= scene->mNumMeshes;

			if (meshesCount <= 0)
			{
				throw Exception();
			}

			const auto mesh				= scene->mMeshes[0];

			std::vector<std::uint8_t> data;

			const auto verticesCount	= mesh->mNumVertices;
			const auto vertexSize		= sizeof(float) * 3;

			data.resize(verticesCount * vertexSize);

			for (size_t i = 0; i < verticesCount; ++i)
			{
				const auto &vertex			= mesh->mVertices[i];

				const auto vertexData		= data.data() + (vertexSize * i);
				const auto vertexPosition	= reinterpret_cast<float*>(vertexData);

				vertexPosition[0] = vertex.x;
				vertexPosition[1] = vertex.y;
				vertexPosition[2] = vertex.z;
			}

			return std::move(data);
		}
	}
}


#pragma region
#pragma endregion


