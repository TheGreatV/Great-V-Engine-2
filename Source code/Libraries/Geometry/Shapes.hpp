#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	class Geometry // TODO: move to other file
	{
	public:
		enum class VertexPackMode
		{
			Pos32F,
			Pos32F_TBN32F_Tex32F,				// 4*3	+ 4*3*3	+ 4*2	= 56 bytes
			Pos32F_TN16F_Tex32F,				// 4*3	+ 2*3*2	+ 2*2	= 32 bytes
			Pos16F_TBNa16F_Tex16F,				// 2*3	+ 2*3	+ 2*2	= 16 bytes (TBN is saved as angles)
			Default = Pos32F_TBN32F_Tex32F,
		};
		enum class IndexPackMode
		{
			UInt32,
			UInt16,
			UInt8,
			Default = UInt32
		};
		enum class Topology
		{
			Points,
			Lines,
			LineStrip,
			LineLoop,
			Triangles,
			TriangleStrip,
			TriangleFan,
			Patches2,
			Patches3,
			Patches4,
		};
	public:
		using Index = UInt32;
		using Bytes = Vector<UInt8>;
	public:
		struct Vertex
		{
			Vec3 pos;
			Vec3 tan;
			Vec3 bin;
			Vec3 nor;
			Vec2 tex;
		};
	public:
		static inline StrongPointer<Geometry> CreateBox(const Vec3& size_, const Vec3& tex_, const UVec3& seg_);
		static inline StrongPointer<Geometry> CreateSphere(const Float32& radius_, const Vec2& tex_, const UVec2& seg_);
		static inline StrongPointer<Geometry> CreateTorus(const Float32& radius_, const Float32& width_, const Vec2& tex_, const UVec2& seg_);
		static inline StrongPointer<Geometry> CreateCapsule(const Float32& radius_, const Float32& height_, const Vec2& tex_, const UVec2& seg_);
	public:
		Topology topology = Topology::Triangles;
		Vector<Vertex> vertices;
		Vector<Index> indices;
	public:
		inline Geometry() = default;
		inline Geometry(const Topology& topology_, const Size& verticesCount, const Size& indicesCount):
			topology(topology_),
			vertices(verticesCount),
			indices(indicesCount)
		{
		}
		inline Geometry(const Geometry&) = default;
		inline Geometry(Geometry&& source):
			vertices(std::move(source.vertices)),
			indices(std::move(source.indices))
		{
		}
		inline ~Geometry() = default;
	public:
		inline Geometry& operator = (const Geometry&) = default;
		inline Geometry& operator = (Geometry&& source)
		{
			vertices = std::move(source.vertices);
			indices = std::move(source.indices);

			return *this;
		}
	public:
		inline Topology GetTopology() const
		{
			return topology;
		}
		inline void SetTopology(const Topology& topology_)
		{
			topology = topology_;
		}
		inline static Size GetVertexSize(const VertexPackMode& vertexPackMode_ = VertexPackMode::Default)
		{
			switch(vertexPackMode_)
			{
				case VertexPackMode::Pos32F:
					return sizeof(Float32)*3;
				case VertexPackMode::Pos32F_TBN32F_Tex32F:
					return sizeof(Float32) * (4 + 3*3 + 2);
				case VertexPackMode::Pos32F_TN16F_Tex32F:
					return  sizeof(Float32)* (3 + 2) + sizeof(Float16)* (3 * 2);
				default:
					throw Exception("Unknown vertex packing mode");
			}
		}
		inline Size GetVerticesCount() const
		{
			return vertices.size();
		}
		inline Bytes GetVertices(const VertexPackMode& vertexPackMode_ = VertexPackMode::Default) const
		{
			Size vertexSize = GetVertexSize(vertexPackMode_);
			auto bytes = Bytes(vertices.size() * vertexSize, 0x00);

			switch(vertexPackMode_)
			{
				case VertexPackMode::Pos32F:
				{
					Size i = 0;
					for(auto &vertex : vertices)
					{
						auto byte = bytes.data() + i;
					
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 0)) = vertex.pos;
					
						i += vertexSize;
					}

					return bytes;
				} break;
				case VertexPackMode::Pos32F_TBN32F_Tex32F:
				{
					Size i = 0;
					for(auto &vertex : vertices)
					{
						auto byte = bytes.data() + i;
					
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 0)) = vertex.pos;
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 1)) = vertex.tan;
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 2)) = vertex.bin;
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 3)) = vertex.nor;
						*(Vec2*)(byte +(sizeof(Float32)* 3 * 4)) = vertex.tex;
					
						i += vertexSize;
					}

					return bytes;
				} break;
				default:
				{
					throw NotImplementedException();
				} break;
			}
		}
		inline Bytes GetVertices(const Mat4& transform_, const VertexPackMode& vertexPackMode_ = VertexPackMode::Default) const
		{
			Size vertexSize = GetVertexSize(vertexPackMode_);
			auto bytes = Bytes(vertices.size() * vertexSize, 0x00);

			auto rotate = Mat3(transform_);

			switch(vertexPackMode_)
			{
				case VertexPackMode::Pos32F:
				{
					Size i = 0;
					for(auto &vertex : vertices)
					{
						auto byte = bytes.data() + i;
					
						auto pos = (transform_ * Vec4(vertex.pos, 1.0f)).xyz;

						*(Vec3*)(byte +(sizeof(Float32)* 3 * 0)) = pos;
					
						i += vertexSize;
					}

					return bytes;
				} break;
				case VertexPackMode::Pos32F_TBN32F_Tex32F:
				{
					Size i = 0;
					for(auto &vertex : vertices)
					{
						auto byte = bytes.data() + i;
					
						auto &pos = (transform_ * Vec4(vertex.pos, 1.0f)).xyz;
						auto &tan = rotate * vertex.tan;
						auto &bin = rotate * vertex.bin;
						auto &nor = rotate * vertex.nor;
						auto &tex = vertex.tex;

						*(Vec3*)(byte + (sizeof(Float32)* 3 * 0)) = pos;
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 1)) = tan;
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 2)) = bin;
						*(Vec3*)(byte +(sizeof(Float32)* 3 * 3)) = nor;
						*(Vec2*)(byte +(sizeof(Float32)* 3 * 4)) = tex;
					
						i += vertexSize;
					}

					return bytes;
				} break;
				default:
				{
					throw NotImplementedException();
				} break;
			}
		}
		inline static Size GetIndexSize(const IndexPackMode& indexPackMode_ = IndexPackMode::Default)
		{
			switch(indexPackMode_)
			{
				case IndexPackMode::UInt32: return 4;
				case IndexPackMode::UInt16: return 2;
				case IndexPackMode::UInt8: return 1;
				default: throw Exception("Unknown index packing mode");
			}
		}
		inline Size GetIndicesCount() const
		{
			return indices.size();
		}
		inline Bytes GetIndices(const IndexPackMode& indexPackMode_ = IndexPackMode::Default) const
		{
			switch(indexPackMode_)
			{
				case IndexPackMode::UInt32:
				{
					Size indexSize = sizeof(UInt32);
					auto bytes = Bytes(indices.size() * indexSize);

					Size i = 0;
					for(auto &index : indices)
					{
						auto byte = bytes.data() + i;
					
						*(UInt32*)(byte + 0) = index;
					
						i += indexSize;
					}

					return bytes;
				} break;
				default:
				{
					throw NotImplementedException();
				} break;
			}
		}
	};
}


#pragma region GreatVEngine2

#pragma region Geometry

GreatVEngine2::StrongPointer<GreatVEngine2::Geometry> GreatVEngine2::Geometry::CreateBox(const Vec3& size_, const Vec3& tex_, const UVec3& seg_)
{
	if(seg_.x == 0 || seg_.y == 0 || seg_.z == 0)
	{
		throw Exception("Invalid segments count");
	}

	auto geometry = new Geometry(
		Topology::Triangles,
		2*((seg_.x+1)*(seg_.y+1) + (seg_.y+1)*(seg_.z+1) + (seg_.z+1)*(seg_.x+1)),
		2*6*(seg_.x*seg_.y + seg_.y*seg_.z + seg_.z*seg_.x)
	);

	Size id;
	Vec3 maxPos = size_ * 0.5f;
	Vec3 minPos = size_ * -0.5f;

	const Size offsetVertexBack = 0;
	const Size offsetVertexFront = offsetVertexBack + (seg_.x+1)*(seg_.y+1);
	const Size offsetVertexLeft = offsetVertexFront + (seg_.x+1)*(seg_.y+1);
	const Size offsetVertexRight = offsetVertexLeft + (seg_.y+1)*(seg_.z+1);
	const Size offsetVertexBottom = offsetVertexRight + (seg_.y+1)*(seg_.z+1);
	const Size offsetVertexTop = offsetVertexBottom + (seg_.z+1)*(seg_.x+1);
	const Size offsetIndexBack = 0;
	const Size offsetIndexFront = offsetIndexBack + 6*(seg_.x*seg_.y);
	const Size offsetIndexLeft = offsetIndexFront + 6*(seg_.x*seg_.y);
	const Size offsetIndexRight = offsetIndexLeft + 6*(seg_.y*seg_.z);
	const Size offsetIndexBottom = offsetIndexRight + 6*(seg_.y*seg_.z);
	const Size offsetIndexTop = offsetIndexBottom + 6*(seg_.z*seg_.y);

	for(Size x = 0; x <= seg_.x; ++x)
	for(Size y = 0; y <= seg_.y; ++y)
	{
		Vec2 t(Float32(x)/Float32(seg_.x),Float32(y)/Float32(seg_.y));

		id = offsetVertexBack + y*(seg_.x+1) + x;
		geometry->vertices[id].pos = Vec3(minPos.x + size_.x*t.x, minPos.y + size_.y*t.y, minPos.z);
		geometry->vertices[id].tex = t * Vec2(tex_.x, tex_.y);
		geometry->vertices[id].tan = Vec3(1.0f,0.0f,0.0f);
		geometry->vertices[id].bin = Vec3(0.0f,1.0f,0.0f);
		geometry->vertices[id].nor = Vec3(0.0f,0.0f,-1.0f);

		id = offsetVertexFront + y*(seg_.x+1) + x;
		geometry->vertices[id].pos = Vec3(minPos.x + size_.x*t.x,minPos.y + size_.y*t.y,maxPos.z);
		geometry->vertices[id].tex = Vec2(1.0f - t.x,t.y) * Vec2(tex_.x, tex_.y);
		geometry->vertices[id].tan = Vec3(-1.0f,0.0f,0.0f);
		geometry->vertices[id].bin = Vec3(0.0f,1.0f,0.0f);
		geometry->vertices[id].nor = Vec3(0.0f,0.0f,1.0f);
	}
	for(Size y = 0; y <= seg_.y; ++y)
	for(Size z = 0; z <= seg_.z; ++z)
	{
		Vec2 t(Float32(z)/Float32(seg_.z),Float32(y)/Float32(seg_.y));

		id = offsetVertexLeft + z*(seg_.y+1) + y;
		geometry->vertices[id].pos = Vec3(minPos.x,minPos.y + size_.y*t.y,minPos.z + size_.z*t.x);
		geometry->vertices[id].tex = Vec2(1.0f - t.x,t.y) * Vec2(tex_.z, tex_.y);
		geometry->vertices[id].tan = Vec3(0.0f,0.0f,-1.0f);
		geometry->vertices[id].bin = Vec3(0.0f,1.0f,0.0f);
		geometry->vertices[id].nor = Vec3(-1.0f,0.0f,0.0f);

		id = offsetVertexRight + z*(seg_.y+1) + y;
		geometry->vertices[id].pos = Vec3(maxPos.x,minPos.y + size_.y*t.y,minPos.z + size_.z*t.x);
		geometry->vertices[id].tex = t * Vec2(tex_.z, tex_.y);
		geometry->vertices[id].tan = Vec3(0.0f,0.0f,1.0f);
		geometry->vertices[id].bin = Vec3(0.0f,1.0f,0.0f);
		geometry->vertices[id].nor = Vec3(1.0f,0.0f,0.0f);
	}
	for(Size z = 0; z <= seg_.z; ++z)
	for(Size x = 0; x <= seg_.x; ++x)
	{
		Vec2 t(Float32(x)/Float32(seg_.x),Float32(z)/Float32(seg_.z));

		id = offsetVertexBottom + x*(seg_.z+1) + z;
		geometry->vertices[id].pos = Vec3(minPos.x + size_.x*t.x,minPos.y,minPos.z + size_.z*t.y);
		geometry->vertices[id].tex = Vec2(t.x,1.0f - t.y) * Vec2(tex_.x,tex_.z);
		geometry->vertices[id].tan = Vec3(1.0f,0.0f,0.0f);
		geometry->vertices[id].bin = Vec3(0.0f,0.0f,-1.0f);
		geometry->vertices[id].nor = Vec3(0.0f,-1.0f,0.0f);

		id = offsetVertexTop + x*(seg_.z+1) + z;
		geometry->vertices[id].pos = Vec3(minPos.x + size_.x*t.x,maxPos.y,minPos.z + size_.z*t.y);
		geometry->vertices[id].tex = t * Vec2(tex_.x, tex_.z);
		geometry->vertices[id].tan = Vec3(1.0f,0.0f,0.0f);
		geometry->vertices[id].bin = Vec3(0.0f,0.0f,1.0f);
		geometry->vertices[id].nor = Vec3(0.0f,1.0f,0.0f);
	}

	for(Size x = 0; x < seg_.x; ++x)
	for(Size y = 0; y < seg_.y; ++y)
	{
		id = offsetIndexBack + 6*(y*seg_.x + x);
		geometry->indices[id + 0] = offsetVertexBack + (y + 0)*(seg_.x + 1) + (x + 0);
		geometry->indices[id+1] = offsetVertexBack + (y+0)*(seg_.x+1) + (x+1);
		geometry->indices[id+2] = offsetVertexBack + (y+1)*(seg_.x+1) + (x+0);
		geometry->indices[id+3] = geometry->indices[id+2];
		geometry->indices[id+4] = geometry->indices[id+1];
		geometry->indices[id+5] = offsetVertexBack + (y+1)*(seg_.x+1) + (x+1);

		id = offsetIndexFront + 6*(y*seg_.x + x);
		geometry->indices[id+0] = offsetVertexFront + (y+0)*(seg_.x+1) + (x+0);
		geometry->indices[id+2] = offsetVertexFront + (y+0)*(seg_.x+1) + (x+1);
		geometry->indices[id+1] = offsetVertexFront + (y+1)*(seg_.x+1) + (x+0);
		geometry->indices[id+3] = geometry->indices[id+2];
		geometry->indices[id+4] = geometry->indices[id+1];
		geometry->indices[id+5] = offsetVertexFront + (y+1)*(seg_.x+1) + (x+1);
	}
	for(Size y = 0; y < seg_.y; ++y)
	for(Size z = 0; z < seg_.z; ++z)
	{
		id = offsetIndexLeft + 6*(z*seg_.y + y);
		geometry->indices[id+0] = offsetVertexLeft + (z+0)*(seg_.y+1) + (y+0);
		geometry->indices[id+1] = offsetVertexLeft + (z+0)*(seg_.y+1) + (y+1);
		geometry->indices[id+2] = offsetVertexLeft + (z+1)*(seg_.y+1) + (y+0);
		geometry->indices[id+3] = geometry->indices[id+2];
		geometry->indices[id+4] = geometry->indices[id+1];
		geometry->indices[id+5] = offsetVertexLeft + (z+1)*(seg_.y+1) + (y+1);

		id = offsetIndexRight + 6*(z*seg_.y + y);
		geometry->indices[id+0] = offsetVertexRight + (z+0)*(seg_.y+1) + (y+0);
		geometry->indices[id+2] = offsetVertexRight + (z+0)*(seg_.y+1) + (y+1);
		geometry->indices[id+1] = offsetVertexRight + (z+1)*(seg_.y+1) + (y+0);
		geometry->indices[id+3] = geometry->indices[id+2];
		geometry->indices[id+4] = geometry->indices[id+1];
		geometry->indices[id+5] = offsetVertexRight + (z+1)*(seg_.y+1) + (y+1);
	}
	for(Size z = 0; z < seg_.z; ++z)
	for(Size x = 0; x < seg_.x; ++x)
	{
		id = offsetIndexBottom + 6*(x*seg_.z + z);
		geometry->indices[id+0] = offsetVertexBottom + (x+0)*(seg_.z+1) + (z+0);
		geometry->indices[id+1] = offsetVertexBottom + (x+0)*(seg_.z+1) + (z+1);
		geometry->indices[id+2] = offsetVertexBottom + (x+1)*(seg_.z+1) + (z+0);
		geometry->indices[id+3] = geometry->indices[id+2];
		geometry->indices[id+4] = geometry->indices[id+1];
		geometry->indices[id+5] = offsetVertexBottom + (x+1)*(seg_.z+1) + (z+1);

		id = offsetIndexTop + 6*(x*seg_.z + z);
		geometry->indices[id+0] = offsetVertexTop + (x+0)*(seg_.z+1) + (z+0);
		geometry->indices[id+2] = offsetVertexTop + (x+0)*(seg_.z+1) + (z+1);
		geometry->indices[id+1] = offsetVertexTop + (x+1)*(seg_.z+1) + (z+0);
		geometry->indices[id+3] = geometry->indices[id+2];
		geometry->indices[id+4] = geometry->indices[id+1];
		geometry->indices[id+5] = offsetVertexTop + (x+1)*(seg_.z+1) + (z+1);
	}

	return MakeStrong(geometry);
}
GreatVEngine2::StrongPointer<GreatVEngine2::Geometry> GreatVEngine2::Geometry::CreateSphere(const Float32& radius_, const Vec2& tex_, const UVec2& seg_)
{
	if (seg_.x < 3 || seg_.y < 3)
	{
		throw Exception("Invalid segments count");
	}

	auto geometry = new Geometry(
		Topology::Triangles,
		(seg_.x + 1)*(seg_.y + 1),
		6 * seg_.x*seg_.y);

	for (Size x = 0; x <= seg_.x; ++x)
	for (Size y = 0; y <= seg_.y; ++y)
	{
		Float32 dx = Float32(x) / Float32(seg_.x);
		Float32 dy = Float32(y) / Float32(seg_.y);
		Size id = y*(seg_.x + 1) + x;
		Mat3 rMat = RotateZXY3(Vec3(90.0f - dy*180.0f, 180.0f - dx*360.0f, 0.0f));
		geometry->vertices[id].pos = rMat * Vec3(0.0f, 0.0f, radius_);
		geometry->vertices[id].tex = Vec2(dx, dy)*tex_;
		geometry->vertices[id].tan = rMat * Vec3(-1.0f, 0.0f, 0.0f);
		geometry->vertices[id].bin = rMat * Vec3(0.0f, 1.0f, 0.0f);
		geometry->vertices[id].nor = rMat * Vec3(0.0f, 0.0f, 1.0f);
	}

	for (Size x = 0; x < seg_.x; ++x)
	for (Size y = 0; y < seg_.y; ++y)
	{
		Size id = 6 * (y*seg_.x + x);
		geometry->indices[id + 0] = (y + 0)*(seg_.x + 1) + (x + 0);
		geometry->indices[id + 1] = (y + 0)*(seg_.x + 1) + (x + 1);
		geometry->indices[id + 2] = (y + 1)*(seg_.x + 1) + (x + 0);
		geometry->indices[id + 3] = geometry->indices[id + 1];
		geometry->indices[id + 4] = (y + 1)*(seg_.x + 1) + (x + 1);
		geometry->indices[id + 5] = geometry->indices[id + 2];
	}

	return MakeStrong(geometry);
}
GreatVEngine2::StrongPointer<GreatVEngine2::Geometry> GreatVEngine2::Geometry::CreateTorus(const Float32& radius_, const Float32& width_, const Vec2& tex_, const UVec2& seg_)
{
	if (seg_.x < 3 || seg_.y < 3)
	{
		throw Exception("Invalid segments count");
	}

	auto geometry = new Geometry(
		Topology::Triangles,
		(seg_.x + 1)*(seg_.y + 1),
		seg_.x*seg_.y * 6
	);

	SInt32 segX = seg_.x + 1;
	SInt32 segY = seg_.y + 1;
	Float32 step_tx = tex_.x / Float32(seg_.x);
	Float32 step_ty = tex_.y / Float32(seg_.y);
	Float32 step_ay = 360.0f / Float32(seg_.y);
	Float32 step_ax = 360.0f / Float32(seg_.x);

	Vec3 tpos;
	Mat3 tmat;
	SInt32 id;

	for (SInt32 x = 0; x < SInt32(seg_.x) + 1; ++x)
	{
		for (SInt32 y = 0; y < SInt32(seg_.y) + 1; ++y)
		{
			id = (seg_.y + 1)*x + y;
			tpos = ((
				RotateZXY4(Vec3(0, step_ax*x, 0))
				*Move4(Vec3(0, 0, radius_))
				*RotateZXY4(Vec3(step_ay*y, 0, 0))
			) * Vec4(Vec3(0, 0, width_), 1.0f)).xyz;
			
			geometry->vertices[id].pos = tpos;
			geometry->vertices[id].tex = Vec2(step_tx*x, step_ty*y);
			tmat = RotateZXY3(Vec3(step_ay*y, step_ax*x, 0));
			geometry->vertices[id].tan = tmat * Vec3(1, 0, 0);
			geometry->vertices[id].bin = tmat * Vec3(0, -1, 0);
			geometry->vertices[id].nor = tmat * Vec3(0, 0, 1);
		}
	}

	for (SInt32 x = 0; x < SInt32(seg_.x); ++x)
	{
		for (SInt32 y = 0; y < SInt32(seg_.y); ++y)
		{
			id = 6 * (seg_.y*x + y);
			geometry->indices[id + 0] = (seg_.y + 1)*(x + 0) + (y + 0);
			geometry->indices[id + 1] = (seg_.y + 1)*(x + 1) + (y + 0);
			geometry->indices[id + 2] = (seg_.y + 1)*(x + 0) + (y + 1);
			geometry->indices[id + 3] = geometry->indices[id + 1];
			geometry->indices[id + 4] = (seg_.y + 1)*(x + 1) + (y + 1);
			geometry->indices[id + 5] = geometry->indices[id + 2];
		}
	}

	return MakeStrong(geometry);
}
GreatVEngine2::StrongPointer<GreatVEngine2::Geometry> GreatVEngine2::Geometry::CreateCapsule(const Float32& radius_, const Float32& height_, const Vec2& tex_, const UVec2& seg_)
{
	auto geometry = new Geometry(
		Topology::Triangles,
		(seg_.x + 1)*(seg_.y + 1) * 2,
		(6 * ((seg_.y - 1) * 2 + 1) + 3 * 2) * seg_.x
	);

	Float32	st = (radius_*PI*0.5f) / (2.0f*(radius_*PI*0.5f) + height_);
	Mat3	tMat;

	for (Size x = 0; x <= seg_.x; ++x)
	{
		Float32 dx = Float32(x) / Float32(seg_.x);

		for (Size y = 0; y <= seg_.y; ++y)
		{
			Float32 dy = Float32(y) / Float32(seg_.y);
			{
				Size id = (seg_.y + 1) * 2 * x + y;
				tMat = RotateZXY3(Vec3(-90.0f + 90.0f*dy, 360.0f*dx - 180.0f, 0.0f));
				geometry->vertices[id].pos = (tMat * Vec3(0.0f, 0.0f, radius_)) + Vec3(0.0f, height_*0.5f, 0.0f);
				geometry->vertices[id].tan = tMat*Vec3(-1.0f, 0.0f, 0.0f);
				geometry->vertices[id].bin = tMat*Vec3(0.0f, 1.0f, 0.0f);
				geometry->vertices[id].nor = tMat*Vec3(0.0f, 0.0f, 1.0f);
				geometry->vertices[id].tex = Vec2(1.0f - dx, 1.0f - dy*st) * tex_;
			}
			{
				Size id = (seg_.y + 1) * 2 * x + (seg_.y + 1) + y;
				tMat = RotateZXY3(Vec3(90.0f*dy, 360.0f*dx - 180.0f, 0.0f));
				geometry->vertices[id].pos = (tMat * Vec3(0.0f, 0.0f, radius_)) + Vec3(0.0f, -height_*0.5f, 0.0f);
				geometry->vertices[id].tan = tMat*Vec3(-1.0f, 0.0f, 0.0f);
				geometry->vertices[id].bin = tMat*Vec3(0.0f, 1.0f, 0.0f);
				geometry->vertices[id].nor = tMat*Vec3(0.0f, 0.0f, 1.0f);
				geometry->vertices[id].tex = Vec2(1.0f - dx, (1.0f - dy)*st) * tex_;
			}
		}
	}

	Size iR = 6 * (1 + 2 * (seg_.y - 1)) + 3 * 2;
	for (Size x = 0; x < seg_.x; ++x)
	{
		{
			Size id = iR*x + 0;
			geometry->indices[id + 0] = (seg_.y + 1) * 2 * (x + 0) + 0;
			geometry->indices[id + 1] = (seg_.y + 1) * 2 * (x + 1) + 1;
			geometry->indices[id + 2] = (seg_.y + 1) * 2 * (x + 0) + 1;
		}
		{
			Size id = iR*x + (3 + 6 * (2 * (seg_.y - 1) + 1)) + 0;
			geometry->indices[id + 0] = (seg_.y + 1) * 2 * (x + 0) + (2 * seg_.y);
			geometry->indices[id + 1] = (seg_.y + 1) * 2 * (x + 1) + (2 * seg_.y);
			geometry->indices[id + 2] = (seg_.y + 1) * 2 * (x + 0) + (2 * seg_.y + 1);
		}
		{
			Size id = iR*x + 3 + 6 * (seg_.y - 1);
			geometry->indices[id + 0] = (seg_.y + 1) * 2 * (x + 0) + seg_.y + 0;
			geometry->indices[id + 1] = (seg_.y + 1) * 2 * (x + 1) + seg_.y + 0;
			geometry->indices[id + 2] = (seg_.y + 1) * 2 * (x + 0) + seg_.y + 1;
			geometry->indices[id + 3] = geometry->indices[id + 2];
			geometry->indices[id + 4] = geometry->indices[id + 1];
			geometry->indices[id + 5] = (seg_.y + 1) * 2 * (x + 1) + seg_.y + 1;
		}
		for (Size y = 0; y < seg_.y - 1; ++y)
		{
			{
				Size id = iR*x + 3 + 6 * y;
				geometry->indices[id + 0] = (seg_.y + 1) * 2 * (x + 0) + 1 + (y + 0);
				geometry->indices[id + 1] = (seg_.y + 1) * 2 * (x + 1) + 1 + (y + 0);
				geometry->indices[id + 2] = (seg_.y + 1) * 2 * (x + 0) + 1 + (y + 1);
				geometry->indices[id + 3] = geometry->indices[id + 2];
				geometry->indices[id + 4] = geometry->indices[id + 1];
				geometry->indices[id + 5] = (seg_.y + 1) * 2 * (x + 1) + 1 + (y + 1);
			}
			{
				Size id = iR*x + 3 + 6 * (seg_.y - 1) + 6 + 6 * y;
				geometry->indices[id + 0] = (seg_.y + 1) * 2 * (x + 0) + (seg_.y + 1) + (y + 0);
				geometry->indices[id + 1] = (seg_.y + 1) * 2 * (x + 1) + (seg_.y + 1) + (y + 0);
				geometry->indices[id + 2] = (seg_.y + 1) * 2 * (x + 0) + (seg_.y + 1) + (y + 1);
				geometry->indices[id + 3] = geometry->indices[id + 2];
				geometry->indices[id + 4] = geometry->indices[id + 1];
				geometry->indices[id + 5] = (seg_.y + 1) * 2 * (x + 1) + (seg_.y + 1) + (y + 1);
			}
		}
	}

	return MakeStrong(geometry);
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


