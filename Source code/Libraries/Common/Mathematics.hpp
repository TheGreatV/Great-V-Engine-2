#pragma region Include

#pragma once


#include <cstdint>

#include <half.hpp>
#include <glm/glm.hpp>

#include "Header.hpp"
#include "Size.hpp"

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	using UInt8			= std::uint8_t;
	using UInt16		= std::uint16_t;
	using UInt32		= std::uint32_t;
	using UInt64		= std::uint64_t;
	using SInt8			= std::int8_t;
	using SInt16		= std::int16_t;
	using SInt32		= std::int32_t;
	using SInt64		= std::int64_t;
	
	using Float16		= half_float::half;
	using Float32		= float;
	using Float64		= double;

	using Size2			= glm::tvec2<Size, glm::highp>;
	using Size3			= glm::tvec3<Size, glm::highp>;
	using Size4			= glm::tvec4<Size, glm::highp>;
	using Vec2			= glm::vec2;
	using Vec3			= glm::vec3;
	using Vec4			= glm::vec4;
	using HVec2			= glm::tvec2<Float16, glm::highp>;
	using HVec3			= glm::tvec3<Float16, glm::highp>;
	using HVec4			= glm::tvec4<Float16, glm::highp>;
	using DVec2			= glm::tvec2<Float64, glm::highp>;
	using DVec3			= glm::tvec3<Float64, glm::highp>;
	using DVec4			= glm::tvec4<Float64, glm::highp>;
	using BVec2			= glm::bvec2;
	using BVec3			= glm::bvec3;
	using BVec4			= glm::bvec4;
	using IVec2			= glm::ivec2;
	using IVec3			= glm::ivec3;
	using IVec4			= glm::ivec4;
	using LVec2			= glm::tvec2<SInt64, glm::highp>;
	using LVec3			= glm::tvec3<SInt64, glm::highp>;
	using LVec4			= glm::tvec4<SInt64, glm::highp>;
	using UVec2			= glm::uvec2;
	using UVec3			= glm::uvec3;
	using UVec4			= glm::uvec4;

	using Mat2			= glm::mat2;
	using Mat3			= glm::mat3;
	using Mat4			= glm::mat4;
}


#pragma region GreatVEngine2

#pragma endregion


#pragma region
#pragma endregion


