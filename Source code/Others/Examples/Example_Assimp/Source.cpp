#include <../Assimp/Assimp.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;


#include <Tau/Tau.hpp>

#include <fstream>


void main()
{
	// const auto data = GVE::Assimp::f("Media/Models/Common/Box.DAE");
	// 
	// std::cout << data.size() << std::endl;


	const auto filePath = String("Media/Models/Common/Box.DAE");

	const aiScene* scene = aiImportFile(
		filePath.c_str(),
		0
		// | aiProcess_CalcTangentSpace
		| aiProcess_Triangulate
		// | aiProcess_JoinIdenticalVertices
		// | aiProcess_SortByPType
		);

	// scene
	if (scene == nullptr)
	{
		const auto errorString = aiGetErrorString();

		throw Exception();
	}

	// meshes
	const auto meshesCount		= scene->mNumMeshes;

	if (meshesCount <= 0)
	{
		throw Exception();
	}

	// mesh
	const auto mesh				= scene->mMeshes[0];

	const auto verticesCount	= mesh->mNumVertices;
	const auto vertexSize		= sizeof(float) * 3;
	auto verticesData			= std::vector<std::uint8_t>(verticesCount * vertexSize);

	// vertices
	for (size_t i = 0; i < verticesCount; ++i)
	{
		const auto &vertex			= mesh->mVertices[i];

		const auto vertexData		= verticesData.data() + (vertexSize * i);
		const auto vertexPosition	= reinterpret_cast<float*>(vertexData);

		vertexPosition[0] = vertex.x;
		vertexPosition[1] = vertex.y;
		vertexPosition[2] = vertex.z;
	}

	// indices
	const auto indicesCount		= mesh->mNumFaces * 3;
	const auto indexSize		= sizeof(std::uint32_t);
	auto indicesData			= std::vector<std::uint8_t>(indicesCount * indexSize);

	for (size_t i = 0; i < mesh->mNumFaces; ++i)
	{
		const auto face				= mesh->mFaces[i];

		if (face.mNumIndices != 3)
		{
			throw Exception();
		}

		for (size_t j = 0; j < face.mNumIndices; ++j)
		{
			const auto index		= face.mIndices[j];

			const auto indexData	= indicesData.data() + (indexSize * ((i * 3) + j));
			const auto indexValue	= reinterpret_cast<std::uint32_t*>(indexData);

			*indexValue = index;
		}
	}

	const auto output = Tau::Map({
		Tau::Pair("Version", "0.1.0"),
		Tau::Pair("Vertices", Tau::Map({
			Tau::Pair("Attributes", Tau::Map({
				Tau::Pair("Position", Tau::Map({
					Tau::Pair("Type", "Signed 32-bit Float"),
					Tau::Pair("Components", 3),
					Tau::Pair("Offset", 0),
					Tau::Pair("Stride", 12),
				})),
			})),
			Tau::Pair("Count", static_cast<int>(verticesCount)),
			Tau::Pair("Data", Tau::Binary::Hex(verticesData)),
		})),
		Tau::Pair("Indices", Tau::Map({
			Tau::Pair("Type", "Unsigned 32-bit Integer"),
			Tau::Pair("Count", static_cast<int>(verticesCount)),
			Tau::Pair("Data", Tau::Binary::Hex(indicesData)),
		})),
	});

	// std::cout << Tau::Stringifier().Stringify(output) << std::endl;

	std::ofstream file("output.tau");

	file << Tau::Stringifier().Stringify(output);

	file.close();

	std::system("pause");
}
void main1()
{
	std::ifstream file("output.tau");

	auto content = std::string{};

	std::getline(file, content, '\0');

	file.close();

	const auto object = Tau::Parser().Parse(content);

	std::ofstream file2("output2.tau");

	file2 << Tau::Stringifier().Stringify(object);

	file2.close();

	std::system("pause");
}


