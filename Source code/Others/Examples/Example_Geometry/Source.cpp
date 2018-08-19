#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;


void main()
{
	const auto geometry = Geometry2::Load("output.tau");

	/*using Component = Geometry2::Vertexed::Vertices::Attribute::Type::Component::Regular;
	using Attribute = Geometry2::Vertexed::Vertices::Attribute;

	const auto sfloat32						= MakeStrong<Component>(32, Component::Sign::Signed, Component::Normalization::Unnormalized, Component::Conversion::Floating);
	const auto vec3Attribute				= MakeStrong<Attribute::Type::Vector>(sfloat32, 3);

	const auto stride						= sizeof(Vec3) + sizeof(Mat3) + sizeof(Vec2);
	const auto attributePosition			= MakeStrong<Attribute::Regular>("Position",			0, stride, vec3Attribute);
	const auto attributeTangentSpace		= MakeStrong<Attribute::Regular>("TangentSpace",		0, stride, vec3Attribute);
	const auto attributeTextureCoordinates	= MakeStrong<Attribute::Regular>("TextureCoordinates",	0, stride, vec3Attribute);

	const auto vertices						= MakeStrong<Geometry2::Vertices::Unformatted>(Geometry2::Vertices::Attributes({
		attributePosition,
		attributeTangentSpace,
		attributeTextureCoordinates,
	}), 1, Geometry2::Vertices::Data({}));*/

	// using Vertex = int;

	// const auto vertices = new Geometry2::Vertices::Regular<Vertex>();

	/*const auto attributePosition			= MakeStrong<Geometry2::Vertexed::Vertices::Attribute::Common>("Position",				0, sizeof(Vec3));
	const auto attributeTangentSpace		= MakeStrong<Geometry2::Vertexed::Vertices::Attribute::Common>("TangentSpace",			sizeof(Vec3), sizeof(Mat3));
	const auto attributeTextureCoordinates	= MakeStrong<Geometry2::Vertexed::Vertices::Attribute::Common>("TextureCoordinates",	sizeof(Vec3) + sizeof(Mat3), sizeof(Vec2));

	const auto verticesAttributes			= MakeStrong<Geometry2::Vertexed::Vertices::Attributes::Listed>({
		attributePosition,
		attributeTangentSpace,
		attributeTextureCoordinates,
	});

	const auto geometry				= MakeStrong<Geometry2::Vertexed>(StrongPointer<Geometry2::Vertexed::Vertices::Attributes>(nullptr));
	const auto vertices				= geometry->GetVertices();

	const auto verticesCount		= vertices->GetData();
	const auto verticesData			= vertices->GetData();*/

	std::system("pause");
}
