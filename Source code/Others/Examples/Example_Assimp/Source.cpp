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
		| aiProcess_CalcTangentSpace
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
	const auto mesh						= scene->mMeshes[0];

	const auto verticesCount			= mesh->mNumVertices;

	const auto positionSize				= sizeof(float) * 3;
	const auto tangentSize				= (mesh->mTangents != nullptr)
		? sizeof(float) * 3
		: 0;
	const auto bitangentSize			= (mesh->mBitangents != nullptr)
		? sizeof(float) * 3
		: 0;
	const auto normalSize				= (mesh->mNormals != nullptr)
		? sizeof(float) * 3
		: 0;
	const auto textureCoordinatesSize	= (mesh->mNumUVComponents != nullptr && mesh->mNumUVComponents[0] == 2)
		? sizeof(float) * 2
		: 0;

	const auto positionOffset			= 0u;
	const auto tangentOffset			= positionOffset + positionSize;
	const auto bitangentOffset			= tangentOffset + tangentSize;
	const auto normalOffset				= bitangentOffset + bitangentSize;
	const auto textureCoordinatesOffset	= normalOffset + normalSize;

	const auto vertexSize				= 0
		+ positionSize
		+ tangentSize
		+ bitangentSize
		+ normalSize
		+ textureCoordinatesSize
		;
	auto verticesData					= std::vector<std::uint8_t>(verticesCount * vertexSize);

	// vertices
	for (size_t i = 0; i < verticesCount; ++i)
	{
		const auto &vertex			= mesh->mVertices[i];

		const auto vertexData		= verticesData.data() + (vertexSize * i);
		const auto vertexPosition	= reinterpret_cast<float*>(vertexData + positionOffset);

		vertexPosition[0] = vertex.x;
		vertexPosition[1] = vertex.y;
		vertexPosition[2] = vertex.z;

		if (tangentSize != 0)
		{
			const auto tangent			= mesh->mTangents[i];
			const auto vertexTangent	= reinterpret_cast<float*>(vertexData + tangentOffset);

			vertexTangent[0] = tangent.x;
			vertexTangent[1] = tangent.y;
			vertexTangent[2] = tangent.z;
		}
		if (bitangentSize != 0)
		{
			const auto bitangent		= mesh->mBitangents[i];
			const auto vertexBitangent	= reinterpret_cast<float*>(vertexData + bitangentOffset);

			vertexBitangent[0] = bitangent.x;
			vertexBitangent[1] = bitangent.y;
			vertexBitangent[2] = bitangent.z;
		}
		if (normalSize != 0)
		{
			const auto normal			= mesh->mNormals[i];
			const auto vertexNormal		= reinterpret_cast<float*>(vertexData + normalOffset);

			vertexNormal[0] = normal.x;
			vertexNormal[1] = normal.y;
			vertexNormal[2] = normal.z;
		}
		if (textureCoordinatesSize != 0)
		{
			const auto textureCoordinates			= mesh->mTextureCoords[0][i];
			const auto vertexTextureCoordinates		= reinterpret_cast<float*>(vertexData + textureCoordinatesOffset);

			vertexTextureCoordinates[0] = textureCoordinates.x;
			vertexTextureCoordinates[1] = textureCoordinates.y;
		}
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

	auto output = Tau::Map({
		Tau::Pair("Version", "0.1.0"),
		Tau::Pair("Vertices", Tau::Map({
			Tau::Pair("Attributes", Tau::Map({
				Tau::Pair("Position", Tau::Map({
					Tau::Pair("Class", "Regular Attribute"),
					Tau::Pair("Type", Tau::Map({
						Tau::Pair("Class", "Vector Attribute Type"),
						Tau::Pair("Component", "Signed 32-bit Float"),
						Tau::Pair("Size", 3),
					})),
					Tau::Pair("Offset", 0),
					Tau::Pair("Stride", static_cast<int>(vertexSize)),
				})),
			})),
			Tau::Pair("Count", static_cast<int>(verticesCount)),
			Tau::Pair("Data", Tau::Binary::Hex(verticesData)),
		})),
		Tau::Pair("Indices", Tau::Map({
			Tau::Pair("Type", "Unsigned 32-bit Integer"),
			Tau::Pair("Count", static_cast<int>(indicesCount)),
			Tau::Pair("Data", Tau::Binary::Hex(indicesData)),
		})),
	});

	if (tangentSize != 0 && bitangentSize != 0 && normalSize != 0)
	{
		output["Vertices"]["Attributes"]["Tangent Space"] = Tau::Map({
			Tau::Pair("Class", "Regular Attribute"),
			Tau::Pair("Type", Tau::Map({
				Tau::Pair("Class", "Matrix Attribute Type"),
				Tau::Pair("Component", "Signed 32-bit Float"),
				Tau::Pair("Order", "Row-major"),
				Tau::Pair("Rows", 3),
				Tau::Pair("Columns", 3),
			})),
			Tau::Pair("Offset", static_cast<int>(tangentOffset)),
			Tau::Pair("Stride", static_cast<int>(vertexSize)),
		});
	}
	else
	{
		if (tangentSize != 0)
		{
			output["Vertices"]["Attributes"]["Tangent"] = Tau::Map({
				Tau::Pair("Class", "Regular Attribute"),
				Tau::Pair("Type", Tau::Map({
					Tau::Pair("Class", "Vector Attribute Type"),
					Tau::Pair("Component", "Signed 32-bit Float"),
					Tau::Pair("Size", 3),
				})),
				Tau::Pair("Offset", static_cast<int>(tangentOffset)),
				Tau::Pair("Stride", static_cast<int>(vertexSize)),
			});
		}
		if (bitangentSize != 0)
		{
			output["Vertices"]["Attributes"]["Bitangent"] = Tau::Map({
				Tau::Pair("Class", "Regular Attribute"),
				Tau::Pair("Type", Tau::Map({
					Tau::Pair("Class", "Vector Attribute Type"),
					Tau::Pair("Component", "Signed 32-bit Float"),
					Tau::Pair("Size", 3),
				})),
				Tau::Pair("Offset", static_cast<int>(bitangentOffset)),
				Tau::Pair("Stride", static_cast<int>(vertexSize)),
			});
		}
		if (normalSize != 0)
		{
			output["Vertices"]["Attributes"]["Normal"] = Tau::Map({
				Tau::Pair("Class", "Regular Attribute"),
				Tau::Pair("Type", Tau::Map({
					Tau::Pair("Class", "Vector Attribute Type"),
					Tau::Pair("Component", "Signed 32-bit Float"),
					Tau::Pair("Size", 3),
				})),
				Tau::Pair("Offset", static_cast<int>(normalOffset)),
				Tau::Pair("Stride", static_cast<int>(vertexSize)),
			});
		}
	}
	if (textureCoordinatesSize != 0)
	{
		output["Vertices"]["Attributes"]["Texture Coordinates"] = Tau::Map({
			Tau::Pair("Class", "Regular Attribute"),
			Tau::Pair("Type", Tau::Map({
				Tau::Pair("Class", "Vector Attribute Type"),
				Tau::Pair("Component", "Signed 32-bit Float"),
				Tau::Pair("Size", 2),
			})),
			Tau::Pair("Offset", static_cast<int>(textureCoordinatesOffset)),
			Tau::Pair("Stride", static_cast<int>(vertexSize)),
		});
	}

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


