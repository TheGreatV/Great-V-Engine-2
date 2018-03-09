#pragma region Include

#pragma once

#include "Header.hpp"
#include "Errors.hpp"
#include "Types.hpp"

#pragma endregion


#pragma region Macro

#ifdef LoadImage // WinUser.h
#undef LoadImage
#endif

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenIL
	{
		// Global
		inline void				Init();
		inline void				Enable(const State& state_);
		inline void				Disable(const State& state_);
		inline bool				OriginFunc(const Origin& origin_);
		inline Integer			GetInteger(const Parameter& parameter_);
		inline Format			GetFormat();
		inline ComponentType	GetComponentType();
		inline Origin			GetOrigin();
		inline CubemapFace		GetCubemapFace();
		inline Memory<void>		GetData();
		

		// Image
		inline ImageHandle		GenImage();
		inline void				DeleteImage(const ImageHandle& imageHandle_);
		inline void				BindImage(const ImageHandle& imageHandle_);
		inline bool				LoadImage(const Filename& filename_);
		inline bool				ActiveImage(const Size& imageIndex_);
		inline bool				ActiveLayer(const Size& layerIndex_);
		inline bool				ActiveMipmap(const Size& mipmapIndex_);
		inline bool				ActiveFace(const Size& faceIndex_);
	}
}


#pragma region GreatVEngine2

#pragma region OpenIL

// Global
void GreatVEngine2::OpenIL::Init()
{
	ilInit();
	iluInit();
	ilutInit();
}
void GreatVEngine2::OpenIL::Enable(const State& state_)
{
	ilEnable(static_cast<ILenum>(state_));

	ErrorTest();
}
void GreatVEngine2::OpenIL::Disable(const State& state_)
{
	ilDisable(static_cast<ILenum>(state_));

	ErrorTest();
}
bool GreatVEngine2::OpenIL::OriginFunc(const Origin& origin_)
{
	auto result = ilOriginFunc(static_cast<ILenum>(origin_)) == IL_TRUE;

	ErrorTest();

	return result;
}
GreatVEngine2::OpenIL::Integer GreatVEngine2::OpenIL::GetInteger(const Parameter& parameter_)
{
	Integer value = ilGetInteger(static_cast<ILenum>(parameter_));

	ErrorTest();

	return value;
}
GreatVEngine2::OpenIL::Format GreatVEngine2::OpenIL::GetFormat()
{
	auto value = GetInteger(Parameter::ImageFormat);
	auto format = static_cast<Format>(value);

	return format;
}
GreatVEngine2::OpenIL::ComponentType GreatVEngine2::OpenIL::GetComponentType()
{
	auto value = GetInteger(Parameter::ImageType);
	auto componentType = static_cast<ComponentType>(value);

	return componentType;
}
GreatVEngine2::OpenIL::Origin GreatVEngine2::OpenIL::GetOrigin()
{
	auto value = GetInteger(Parameter::ImageOrigin);
	auto origin = static_cast<Origin>(value);

	return origin;
}
GreatVEngine2::OpenIL::CubemapFace GreatVEngine2::OpenIL::GetCubemapFace()
{
	auto value = GetInteger(Parameter::ImageCubeFlags);
	auto cubemapFace = static_cast<CubemapFace>(value);

	return cubemapFace;
}
GreatVEngine2::Memory<void> GreatVEngine2::OpenIL::GetData()
{
	auto data = ilGetData();

	ErrorTest();

	return data;
}

// Image
GreatVEngine2::OpenIL::ImageHandle GreatVEngine2::OpenIL::GenImage()
{
	ImageHandle::Value value = ilGenImage();

	ErrorTest();

	return ImageHandle(value);
}
void GreatVEngine2::OpenIL::DeleteImage(const ImageHandle& imageHandle_)
{
	ilDeleteImage(imageHandle_);

	ErrorTest();
}
void GreatVEngine2::OpenIL::BindImage(const ImageHandle& imageHandle_)
{
	ilBindImage(imageHandle_);

	ErrorTest();
}
bool GreatVEngine2::OpenIL::LoadImage(const Filename& filename_)
{
	auto result = ilLoadImage(filename_.c_str()) == IL_TRUE;

	ErrorTest();

	return result;
}
bool GreatVEngine2::OpenIL::ActiveImage(const Size& imageIndex_)
{
	auto result = ilActiveImage(imageIndex_) != IL_TRUE;

	ErrorTest();

	return result;
}
bool GreatVEngine2::OpenIL::ActiveLayer(const Size& layerIndex_)
{
	auto result = ilActiveLayer(layerIndex_) != IL_TRUE;

	ErrorTest();

	return result;
}
bool GreatVEngine2::OpenIL::ActiveMipmap(const Size& mipmapIndex_)
{
	auto result = ilActiveMipmap(mipmapIndex_) != IL_TRUE;

	ErrorTest();

	return result;
}
bool GreatVEngine2::OpenIL::ActiveFace(const Size& faceIndex_)
{
	auto result = ilActiveFace(faceIndex_) != IL_TRUE;

	ErrorTest();

	return result;
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


