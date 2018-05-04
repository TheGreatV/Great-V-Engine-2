#pragma region Include

#pragma once


#include <cstdint>

#include <half.hpp>

#include <glm/detail/setup.hpp>
#define GLM_SWIZZLE GLM_SWIZZLE_XYZW
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


	const Float32 PI	= 3.1415926535897932384626433832795f;


	inline Float32 Rnd()
	{
		return static_cast <Float32> (rand()) / static_cast <Float32> (RAND_MAX);
	}
	inline Float32 Rnd(const Float32& max_)
	{
		return static_cast <Float32> (rand()) / (static_cast <Float32> (RAND_MAX / max_));
	}
	inline Float32 Rnd(const Float32& min_, const Float32& max_)
	{
		return min_ + static_cast <Float32> (rand()) / (static_cast <Float32> (RAND_MAX / (max_ - min_)));
	}
	inline Vec2 Rnd2()
	{
		return Vec2(Rnd(), Rnd());
	}
	inline Vec2 Rnd2(const Float32& max_)
	{
		return Vec2(Rnd(max_), Rnd(max_));
	}
	inline Vec2 Rnd2(const Float32& min_, const Float32& max_)
	{
		return Vec2(Rnd(min_, max_), Rnd(min_, max_));
	}
	inline Vec3 Rnd3()
	{
		return Vec3(Rnd(), Rnd(), Rnd());
	}
	inline Vec3 Rnd3(const Float32& max_)
	{
		return Vec3(Rnd(max_), Rnd(max_), Rnd(max_));
	}
	inline Vec3 Rnd3(const Float32& min_, const Float32& max_)
	{
		return Vec3(Rnd(min_, max_), Rnd(min_, max_), Rnd(min_, max_));
	}
	inline Vec4 Rnd4()
	{
		return Vec4(Rnd(), Rnd(), Rnd(), Rnd());
	}
	inline Vec4 Rnd4(const Float32& max_)
	{
		return Vec4(Rnd(max_), Rnd(max_), Rnd(max_), Rnd(max_));
	}
	inline Vec4 Rnd4(const Float32& min_, const Float32& max_)
	{
		return Vec4(Rnd(min_, max_), Rnd(min_, max_), Rnd(min_, max_), Rnd(min_, max_));
	}


	template<class Type> inline Type Radians(const Type& degrees_);
	template<class Type> inline Type Degrees(const Type& radians_);
	template<class Type> inline Type Sin(const Type& radians_);
	template<class Type> inline Type Cos(const Type& radians_);
	template<class Type> inline Type SinDg(const Type& degrees_);
	template<class Type> inline Type CosDg(const Type& degrees_);

	template <typename Type> inline Type Clamp(Type value_, Type minValue_, Type maxValue_)
	{
		return glm::clamp(value_, minValue_, maxValue_);
	}
	template <typename genTypeT, typename genTypeU>
	inline genTypeT Mix(const genTypeT& a, const genTypeT& b, const genTypeU& t)
	{
		return glm::mix(a, b, t);
	}
	template <typename T> inline Float32 Length(const T& t)
	{
		return glm::length(t);
	}
	template<class Type> inline Type Normalize(const Type& source_);
	template<class Type> inline typename Type::transpose_type Transpose(const Type& source_)
	{
		return glm::transpose(source_);
	}
	template<class Type> inline Type Inverse(const Type& source_);


	inline Mat3 RotateX3(const Float32& angle_);
	inline Mat3 RotateY3(const Float32& angle_);
	inline Mat3 RotateZ3(const Float32& angle_);
	inline Mat3 RotateZXY3(const Vec3& angle_);
	inline Mat3 RotateYXZ3(const Vec3& angle_);

	inline Mat4 One4();
	inline Mat4 Move4(const Vec3& position_);
	inline Mat4 Scale4(const Vec3& scale_);
	inline Mat4 Scale4(const Vec4& scale_);
	inline Mat4 RotateX4(const Float32& angle_);
	inline Mat4 RotateY4(const Float32& angle_);
	inline Mat4 RotateZ4(const Float32& angle_);
	inline Mat4 RotateZXY4(const Vec3& angle_);
	inline Mat4 RotateYXZ4(const Vec3& angle_);
	inline Mat4 Perspective(const Float32& fov_, const Float32& aspect_, const Float32& near_, const Float32& far_);
	inline Mat4 PerspectiveInverse(const Float32& fov_, const Float32& aspect_, const Float32& near_, const Float32& far_);
	inline Mat4 Orthogonal(const Float32& left_, const Float32& right_, const Float32& bottom_, const Float32& top_, const Float32& back_, const Float32& front_);
	inline Mat4 OrthogonalInverse(const Float32& left_, const Float32& right_, const Float32& bottom_, const Float32& top_, const Float32& back_, const Float32& front_);
	inline Mat4 To4(const Mat3& mat_);

	inline Float32 GetAngle(const Vec2& value_);
	inline Vec2 GetAngle(const Vec3& value_);
	inline Vec3 GetAngle(const Mat3& value_);
	inline Vec3 GetAngle(const Mat4& value_);
}


#pragma region GreatVEngine2


template<class Type> typename Type GreatVEngine2::Radians(const Type& degrees_)
{
	return glm::radians(degrees_);
}
template<class Type> typename Type GreatVEngine2::Degrees(const Type& radians_)
{
	return glm::degrees(radians_);
}
template<class Type> typename Type GreatVEngine2::Sin(const Type& radians_)
{
	return glm::sin(radians_);
}
template<class Type> typename Type GreatVEngine2::Cos(const Type& radians_)
{
	return glm::cos(radians_);
}
template<class Type> typename Type GreatVEngine2::SinDg(const Type& degrees_)
{
	return Sin<Type>(Radians<Type>(degrees_));
}
template<class Type> typename Type GreatVEngine2::CosDg(const Type& degrees_)
{
	return Cos<Type>(Radians<Type>(degrees_));
}

template<class Type> typename Type GreatVEngine2::Normalize(const Type& source_)
{
	return glm::normalize(source_);
}
template<class Type> typename Type GreatVEngine2::Inverse(const Type& source_)
{
	return glm::inverse(source_);
}


GreatVEngine2::Mat3 GreatVEngine2::RotateX3(const Float32& angle_)
{
	auto a = Radians(angle_);
	auto s = Sin(a);
	auto c = Cos(a);

	return Transpose(Mat3(
		1.0f,	0.0f,	0.0f,
		0.0f,	c,		-s,
		0.0f,	s,		c));
}
GreatVEngine2::Mat3 GreatVEngine2::RotateY3(const Float32& angle_)
{
	auto a = Radians(angle_);
	auto s = Sin(a);
	auto c = Cos(a);

	return Transpose(Mat3(
		c, 0.0f, s,
		0.0f, 1.0f, 0.0f,
		-s, 0.0f, c));
}
GreatVEngine2::Mat3 GreatVEngine2::RotateZ3(const Float32& angle_)
{
	auto a = Radians(angle_);
	auto s = Sin(a);
	auto c = Cos(a);

	return Transpose(Mat3(
		c, s, 0.0f,
		-s, c, 0.0f,
		0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat3 GreatVEngine2::RotateZXY3(const Vec3& angle_)
{
	return RotateY3(angle_.y) * RotateX3(angle_.x) * RotateZ3(angle_.z);
}
GreatVEngine2::Mat3 GreatVEngine2::RotateYXZ3(const Vec3& angle_)
{
	return RotateZ3(angle_.z) * RotateX3(angle_.x) * RotateY3(angle_.y);
}

GreatVEngine2::Mat4 GreatVEngine2::One4()
{
	return Transpose(Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::Move4(const Vec3& position_)
{
	return Transpose(Mat4(
		1.0f, 0.0f, 0.0f, position_.x,
		0.0f, 1.0f, 0.0f, position_.y,
		0.0f, 0.0f, 1.0f, position_.z,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::Scale4(const Vec3& scale_)
{
	return Transpose(Mat4(
		scale_.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale_.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale_.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::Scale4(const Vec4& scale_)
{
	return Transpose(Mat4(
		scale_.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale_.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale_.z, 0.0f,
		0.0f, 0.0f, 0.0f, scale_.w));
}
GreatVEngine2::Mat4 GreatVEngine2::RotateX4(const Float32& angle_)
{
	auto a = Radians(angle_);
	auto s = Sin(a);
	auto c = Cos(a);

	return Transpose(Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c, -s, 0.0f,
		0.0f, s, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::RotateY4(const Float32& angle_)
{
	auto a = Radians(angle_);
	auto s = Sin(a);
	auto c = Cos(a);

	return Transpose(Mat4(
		c, 0.0f, s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::RotateZ4(const Float32& angle_)
{
	auto a = Radians(angle_);
	auto s = Sin(a);
	auto c = Cos(a);

	return Transpose(Mat4(
		c, s, 0.0f, 0.0f,
		-s, c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::RotateZXY4(const Vec3& angle_)
{
	return  RotateY4(angle_.y) * RotateX4(angle_.x) * RotateZ4(angle_.z);
}
GreatVEngine2::Mat4 GreatVEngine2::RotateYXZ4(const Vec3& angle_)
{
	return  RotateZ4(angle_.z) * RotateX4(angle_.x) * RotateY4(angle_.y);
}
GreatVEngine2::Mat4 GreatVEngine2::Perspective(const Float32& fov_, const Float32& aspect_, const Float32& near_, const Float32& far_)
{
	auto g = Radians(fov_);
	Float32 f = 1.0f / tanf(g / 2.0f);
	Float32 a = (far_ + near_) / (near_ - far_);
	Float32 b = (2.0f * far_ * near_) / (near_ - far_);

	return Transpose(Mat4( // corrected by *(1,1,-1)
		f / aspect_, 0.0f, 0.0f, 0.0f,
		0.0f, f, 0.0f, 0.0f,
		0.0f, 0.0f, -a, b,
		0.0f, 0.0f, 1.0f, 0.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::PerspectiveInverse(const Float32& fov_, const Float32& aspect_, const Float32& near_, const Float32& far_)
{
	auto g = Radians(fov_);
	Float32 f = 1.0f / tanf(g / 2.0f);
	Float32 a = (far_ + near_) / (near_ - far_);
	Float32 b = (2.0f * far_ * near_) / (near_ - far_);

	// return glm::transpose(Mat4( // original
	// 	aspect_ / f,	0.0f,		0.0f,		0.0f,
	// 	0.0f,			1.0f / f,	0.0f,		0.0f,
	// 	0.0f,			0.0f,		0.0f,		-1.0f,
	// 	0.0f,			0.0f,		1.0f / b,	a / b));
	return Transpose(Mat4( // corrected by *(1,1,-1)
		aspect_ / f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f / b, a / b));
}
GreatVEngine2::Mat4 GreatVEngine2::Orthogonal(const Float32& left_, const Float32& right_, const Float32& bottom_, const Float32& top_, const Float32& back_, const Float32& front_)
{
	Float32
		dx = 1.0f / (right_ - left_),
		dy = 1.0f / (top_ - bottom_),
		dz = 1.0f / (front_ - back_);

	return Transpose(Mat4(
		2 * dx, 0.0f, 0.0f, -(right_ + left_) * dx,
		0.0f, 2 * dy, 0.0f, -(top_ + bottom_)*dy,
		0.0f, 0.0f, -2 * dz, -(front_ + back_)*dz,
		0.0f, 0.0f, 0.0f, 1.0f));
}
GreatVEngine2::Mat4 GreatVEngine2::OrthogonalInverse(const Float32& left_, const Float32& right_, const Float32& bottom_, const Float32& top_, const Float32& back_, const Float32& front_)
{
	return Inverse(Orthogonal(left_, right_, bottom_, top_, back_, front_));
}
GreatVEngine2::Mat4 GreatVEngine2::To4(const Mat3& mat_)
{
	return Mat4(
		mat_[0].x,	mat_[0].y,	mat_[0].z,	0.0f,
		mat_[1].x,	mat_[1].y,	mat_[1].z,	0.0f,
		mat_[2].x,	mat_[2].y,	mat_[2].z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);
}

GreatVEngine2::Float32 GreatVEngine2::GetAngle(const Vec2& value_)
{
	return Degrees(atan2(value_.x, value_.y));
}
GreatVEngine2::Vec2 GreatVEngine2::GetAngle(const Vec3& value_)
{
	Vec2 out(
		GetAngle(Vec2(-value_.y, sqrt(value_.x*value_.x + value_.z*value_.z))),
		GetAngle(Vec2(value_.x, value_.z))
	);
	
	return out;
}
GreatVEngine2::Vec3 GreatVEngine2::GetAngle(const Mat3& value_)
{
	Vec3	result(0.0f), v_xz(0.0f), v_y(0.0f);

	v_xz = value_ * Vec3(0.0f, 0.0f, 1.0f);

	auto t = GetAngle(v_xz);

	result.x = t.x;
	result.y = t.y;

	v_y = (RotateYXZ3(Vec3(-result.x, -result.y, 0.0f)) * value_) * Vec3(0.0f, 1.0f, 0.0f);

	result.z = Degrees(atan2(v_y.x, v_y.y));

	return result;
}
GreatVEngine2::Vec3 GreatVEngine2::GetAngle(const Mat4& value_)
{
	return GetAngle(Mat3(
		value_[0][0], value_[1][0], value_[2][0],
		value_[0][1], value_[1][1], value_[2][1],
		value_[0][2], value_[1][2], value_[2][2]));
}

#pragma endregion


#pragma region
#pragma endregion


