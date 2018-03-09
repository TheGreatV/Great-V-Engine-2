#pragma region Include

#pragma once

#include "Header.hpp"

#pragma endregion


#pragma region Macro

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenIL
	{
		using Filename = String;

		using Integer = ILint;

		enum class State: ILenum
		{
			OriginSet		= IL_ORIGIN_SET,
			FileOverwrite	= IL_FILE_OVERWRITE,
			ConvPal			= IL_CONV_PAL,
		};
		enum class Origin: ILenum
		{
			LowerLeft		= IL_ORIGIN_LOWER_LEFT,
			UpperLeft		= IL_ORIGIN_UPPER_LEFT,
		};
		enum class Parameter: ILenum
		{
			NumImages			= IL_NUM_IMAGES,
			NumFaces			= IL_NUM_FACES,
			NumMipmaps			= IL_NUM_MIPMAPS,
			NumLayers			= IL_NUM_LAYERS,

			ImageWidth			= IL_IMAGE_WIDTH,
			ImageHeight			= IL_IMAGE_HEIGHT,
			ImageDepth			= IL_IMAGE_DEPTH,
			ImageSizeOfData		= IL_IMAGE_SIZE_OF_DATA,
			ImageBytesPerPixel	= IL_IMAGE_BYTES_PER_PIXEL,
			ImageBitsPerPixel	= IL_IMAGE_BITS_PER_PIXEL,
			ImageFormat			= IL_IMAGE_FORMAT,			// Use GetFormat() instead of GetInteger()
			ImageType			= IL_IMAGE_TYPE,			// Use GetComponentType() instead of GetInteger()
			ImageCubeFlags		= IL_IMAGE_CUBEFLAGS,
			ImageOrigin			= IL_IMAGE_ORIGIN,			// Use GetOrigin() instead of GetInteger()
			ImageChannels		= IL_IMAGE_CHANNELS,
		};
		enum class Format: ILenum
		{
			RGB					= IL_RGB,
			RGBA				= IL_RGBA,
			BGR					= IL_BGR,
			BGRA				= IL_BGRA,
			Luminance			= IL_LUMINANCE,
			LuminanceAlpha		= IL_LUMINANCE_ALPHA,
			ColourIndex			= IL_COLOUR_INDEX,
		};
		enum class ComponentType: ILenum
		{
			Byte				= IL_BYTE,
			UnsignedByte		= IL_UNSIGNED_BYTE,
			Short				= IL_SHORT,
			UnsignedShort		= IL_UNSIGNED_SHORT,
			Int					= IL_INT,
			UnsignedInt			= IL_UNSIGNED_INT,
			Float				= IL_FLOAT,
			Double				= IL_DOUBLE,

			Int8				= Byte,
			UInt8				= UnsignedByte,
			Int16				= Short,
			UInt16				= UnsignedShort,
			Int32				= Int,
			UInt32				= UnsignedInt,
			Float32				= Float,
			Float64				= Double,
		};
		enum class CubemapFace
		{
			PositiveX			= IL_CUBEMAP_POSITIVEX, // Should be equal to ImageCubeFlags
			NegativeX			= IL_CUBEMAP_NEGATIVEX, // Should be equal to ImageCubeFlags
			PositiveY			= IL_CUBEMAP_POSITIVEY, // Should be equal to ImageCubeFlags
			NegativeY			= IL_CUBEMAP_NEGATIVEY, // Should be equal to ImageCubeFlags
			PositiveZ			= IL_CUBEMAP_POSITIVEZ, // Should be equal to ImageCubeFlags
			NegativeZ			= IL_CUBEMAP_NEGATIVEZ, // Should be equal to ImageCubeFlags

			// TODO: IL_SPHEREMAP
		};

		class ImageHandle
		{
		public:
			using Value = ILuint;
		public:
			inline static ImageHandle None();
		protected:
			Value value;
		public:
			inline ImageHandle() = default;
			inline ImageHandle(const ImageHandle&) = default;
			inline ~ImageHandle() = default;
		public:
			inline explicit ImageHandle(const Value& value_);
		public:
			inline ImageHandle& operator = (const ImageHandle&) = default;
		public:
			inline ImageHandle& operator = (const Value& value_);
		public:
			inline operator Value () const;
			inline operator Value& ();
		};
	}
}


#pragma region GreatVEngine2

#pragma region OpenIL

#pragma region ImageHandle

GreatVEngine2::OpenIL::ImageHandle GreatVEngine2::OpenIL::ImageHandle::None()
{
	Value value = 0; // TODO: move to constants

	return ImageHandle(value);
}

GreatVEngine2::OpenIL::ImageHandle::ImageHandle(const Value& value_):
	value(value_)
{
}
GreatVEngine2::OpenIL::ImageHandle& GreatVEngine2::OpenIL::ImageHandle::operator = (const Value& value_)
{
	value = value_;

	return *this;
}
GreatVEngine2::OpenIL::ImageHandle::operator Value () const
{
	return value;
}
GreatVEngine2::OpenIL::ImageHandle::operator Value& ()
{
	return value;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


