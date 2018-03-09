#pragma region Include

#pragma once

#include "Header.hpp"
#include "Errors.hpp"
#include "Types.hpp"
#include "Functions.hpp"

#pragma endregion


#pragma region Macros

#pragma endregion


namespace GreatVEngine2
{
	namespace OpenIL
	{
		inline StrongPointer<Image> Load(const Filename& filename_);
	}
}


#pragma region GreatVEngine2

#pragma region OpenIL

GreatVEngine2::StrongPointer<GreatVEngine2::Image> GreatVEngine2::OpenIL::Load(const Filename& filename_)
{
	Enable(State::OriginSet);
	OriginFunc(Origin::LowerLeft);

	auto imageHandle = GenImage();

	BindImage(imageHandle);

	if (LoadImage(filename_.c_str()))
	{
		auto ilImagesCount		= GetInteger(Parameter::NumImages);
		auto ilLayersCount		= GetInteger(Parameter::NumLayers);
		auto ilFacesCount		= GetInteger(Parameter::NumFaces);
		auto ilMipmapsCount		= GetInteger(Parameter::NumMipmaps);
		auto ilChannels			= GetInteger(Parameter::ImageChannels);
		auto ilOrigin			= GetOrigin();

		auto ilFormat			= GetFormat();
		auto ilComponentType	= GetComponentType();

		auto ilBytesPerPixel	= GetInteger(Parameter::ImageBytesPerPixel);
		auto ilBitsPerPixel		= GetInteger(Parameter::ImageBitsPerPixel);
		
		auto imagesCount		= static_cast<Size>(ilImagesCount) + 1;
		auto layersCount		= static_cast<Size>(ilLayersCount) + 1;
		auto facesCount			= static_cast<Size>(ilFacesCount) + 1;
		auto mipmapsCount		= static_cast<Size>(ilMipmapsCount) + 1;

		if (imagesCount != 1)
		{
			throw GreatVEngine2::Exception(); // TODO
		}

		if (facesCount == 1)
		{
			if (layersCount == 1)
			{
				if (ilFormat == Format::RGB)
				{
					if (ilComponentType == ComponentType::UInt8)
					{
						using Pixel = Pixel<UInt8, UInt8, UInt8>;
						using Image = Image2DX<Pixel>;

						Image::Mipmaps mipmaps;

						mipmaps.reserve(mipmapsCount);

						for (auto &mipmapIndex : Range(mipmapsCount))
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(0);				//
							ActiveMipmap(mipmapIndex);	//

							auto ilImageCubeFlags	= GetCubemapFace();

							auto ilWidth			= GetInteger(Parameter::ImageWidth);
							auto ilHeight			= GetInteger(Parameter::ImageHeight);
							auto ilDepth			= GetInteger(Parameter::ImageDepth);

							auto ilDataSize			= GetInteger(Parameter::ImageSizeOfData);
							auto ilData				= GetData();

							auto width				= static_cast<Size>(ilWidth);
							auto height				= static_cast<Size>(ilHeight);
							auto depth				= static_cast<Size>(ilDepth);

							if (depth != 1)
							{
								throw Exception(); // TODO
							}

							auto dataSize			= sizeof(Pixel) * width * height;
							auto data				= Memory<Pixel>(ilData);

							if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
							{
								throw Exception(); // TODO
							}

							mipmaps.emplace_back(Size2(width, height), data);
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else if (ilComponentType == ComponentType::UInt16)
					{
						using Pixel = Pixel<UInt16, UInt16, UInt16>;
						using Image = Image2DX<Pixel>;

						Image::Mipmaps mipmaps;

						mipmaps.reserve(mipmapsCount);

						for (auto &mipmapIndex : Range(mipmapsCount))
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(0);				//
							ActiveMipmap(mipmapIndex);	//

							auto ilImageCubeFlags	= GetCubemapFace();

							auto ilWidth			= GetInteger(Parameter::ImageWidth);
							auto ilHeight			= GetInteger(Parameter::ImageHeight);
							auto ilDepth			= GetInteger(Parameter::ImageDepth);

							auto ilDataSize			= GetInteger(Parameter::ImageSizeOfData);
							auto ilData				= GetData();

							auto width				= static_cast<Size>(ilWidth);
							auto height				= static_cast<Size>(ilHeight);
							auto depth				= static_cast<Size>(ilDepth);

							if (depth != 1)
							{
								throw Exception(); // TODO
							}

							auto dataSize			= sizeof(Pixel) * width * height;
							auto data				= Memory<Pixel>(ilData);

							if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
							{
								throw Exception(); // TODO
							}

							mipmaps.emplace_back(Size2(width, height), data);
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else
					{
						BindImage(ImageHandle::None());

						DeleteImage(imageHandle);

						throw GreatVEngine2::NotImplementedException(); // TODO
					}
				}
				if (ilFormat == Format::RGBA)
				{
					if (ilComponentType == ComponentType::UInt8)
					{
						using Pixel = Pixel<UInt8, UInt8, UInt8, UInt8>;
						using Image = Image2DX<Pixel>;

						Image::Mipmaps mipmaps;

						mipmaps.reserve(mipmapsCount);

						for (auto &mipmapIndex : Range(mipmapsCount))
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(0);				//
							ActiveMipmap(mipmapIndex);	//

							auto ilImageCubeFlags = GetCubemapFace();

							auto ilWidth = GetInteger(Parameter::ImageWidth);
							auto ilHeight = GetInteger(Parameter::ImageHeight);
							auto ilDepth = GetInteger(Parameter::ImageDepth);

							auto ilDataSize = GetInteger(Parameter::ImageSizeOfData);
							auto ilData = GetData();

							auto width = static_cast<Size>(ilWidth);
							auto height = static_cast<Size>(ilHeight);
							auto depth = static_cast<Size>(ilDepth);

							if (depth != 1)
							{
								throw Exception(); // TODO
							}

							auto dataSize = sizeof(Pixel)* width * height;
							auto data = Memory<Pixel>(ilData);

							if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
							{
								throw Exception(); // TODO
							}

							mipmaps.emplace_back(Size2(width, height), data);
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else if (ilComponentType == ComponentType::UInt16)
					{
						using Pixel = Pixel<UInt16, UInt16, UInt16, UInt16>;
						using Image = Image2DX<Pixel>;

						Image::Mipmaps mipmaps;

						mipmaps.reserve(mipmapsCount);

						for (auto &mipmapIndex : Range(mipmapsCount))
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(0);				//
							ActiveMipmap(mipmapIndex);	//

							auto ilImageCubeFlags = GetCubemapFace();

							auto ilWidth = GetInteger(Parameter::ImageWidth);
							auto ilHeight = GetInteger(Parameter::ImageHeight);
							auto ilDepth = GetInteger(Parameter::ImageDepth);

							auto ilDataSize = GetInteger(Parameter::ImageSizeOfData);
							auto ilData = GetData();

							auto width = static_cast<Size>(ilWidth);
							auto height = static_cast<Size>(ilHeight);
							auto depth = static_cast<Size>(ilDepth);

							if (depth != 1)
							{
								throw Exception(); // TODO
							}

							auto dataSize = sizeof(Pixel)* width * height;
							auto data = Memory<Pixel>(ilData);

							if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
							{
								throw Exception(); // TODO
							}

							mipmaps.emplace_back(Size2(width, height), data);
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else
					{
						BindImage(ImageHandle::None());

						DeleteImage(imageHandle);

						throw GreatVEngine2::NotImplementedException(); // TODO
					}
				}
				else if (ilFormat == Format::Luminance)
				{
					if (ilComponentType == ComponentType::UInt8)
					{
						using Pixel = Pixel<UInt8>;
						using Image = Image2DX<Pixel>;

						Image::Mipmaps mipmaps;

						mipmaps.reserve(mipmapsCount);

						for (auto &mipmapIndex : Range(mipmapsCount))
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(0);				//
							ActiveMipmap(mipmapIndex);	//

							auto ilImageCubeFlags = GetCubemapFace();

							auto ilWidth = GetInteger(Parameter::ImageWidth);
							auto ilHeight = GetInteger(Parameter::ImageHeight);
							auto ilDepth = GetInteger(Parameter::ImageDepth);

							auto ilDataSize = GetInteger(Parameter::ImageSizeOfData);
							auto ilData = GetData();

							auto width = static_cast<Size>(ilWidth);
							auto height = static_cast<Size>(ilHeight);
							auto depth = static_cast<Size>(ilDepth);

							if (depth != 1)
							{
								throw Exception(); // TODO
							}

							auto dataSize = sizeof(Pixel)* width * height;
							auto data = Memory<Pixel>(ilData);

							if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
							{
								throw Exception(); // TODO
							}

							mipmaps.emplace_back(Size2(width, height), data);
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else if (ilComponentType == ComponentType::UInt16)
					{
						using Pixel = Pixel<UInt16>;
						using Image = Image2DX<Pixel>;

						Image::Mipmaps mipmaps;

						mipmaps.reserve(mipmapsCount);

						for (auto &mipmapIndex : Range(mipmapsCount))
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(0);				//
							ActiveMipmap(mipmapIndex);	//

							auto ilImageCubeFlags	= GetCubemapFace();

							auto ilWidth			= GetInteger(Parameter::ImageWidth);
							auto ilHeight			= GetInteger(Parameter::ImageHeight);
							auto ilDepth			= GetInteger(Parameter::ImageDepth);

							auto ilDataSize			= GetInteger(Parameter::ImageSizeOfData);
							auto ilData				= GetData();

							auto width				= static_cast<Size>(ilWidth);
							auto height				= static_cast<Size>(ilHeight);
							auto depth				= static_cast<Size>(ilDepth);

							if (depth != 1)
							{
								throw Exception(); // TODO
							}

							auto dataSize			= sizeof(Pixel) * width * height;
							auto data				= Memory<Pixel>(ilData);

							if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
							{
								throw Exception(); // TODO
							}

							mipmaps.emplace_back(Size2(width, height), data);
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else
					{
						BindImage(ImageHandle::None());

						DeleteImage(imageHandle);

						throw GreatVEngine2::NotImplementedException(); // TODO
					}
				}
				else
				{
					BindImage(ImageHandle::None());

					DeleteImage(imageHandle);

					throw GreatVEngine2::NotImplementedException(); // TODO
				}
			}
			else
			{
				BindImage(ImageHandle::None());

				DeleteImage(imageHandle);

				throw GreatVEngine2::NotImplementedException(); // TODO
			}
		}
		else if (facesCount == 6)
		{
			if (layersCount == 1)
			{
				if (ilFormat == Format::RGBA)
				{
					if (ilComponentType == ComponentType::UInt8)
					{
						using Pixel = Pixel<UInt8, UInt8, UInt8, UInt8>;
						using Image = ImageCubeX<Pixel>;

						Map<Size, Pair<Size, Image::Mipmap::Faces>> mipmapsFacesData; // size + faces

						for (auto &faceIndex : Range(facesCount)) // order face->mipmap should be kept!
						{
							BindImage(imageHandle);
							ActiveImage(0);				// need to bind all this values each time
							ActiveLayer(0);				//
							ActiveFace(faceIndex);		//

							auto ilImageCubeFlags	= GetCubemapFace();

							auto face =
								ilImageCubeFlags == CubemapFace::NegativeX ? Image::Mipmap::Face::NegativeX :
								ilImageCubeFlags == CubemapFace::PositiveX ? Image::Mipmap::Face::PositiveX :
								ilImageCubeFlags == CubemapFace::NegativeY ? Image::Mipmap::Face::NegativeY :
								ilImageCubeFlags == CubemapFace::PositiveY ? Image::Mipmap::Face::PositiveY :
								ilImageCubeFlags == CubemapFace::NegativeZ ? Image::Mipmap::Face::NegativeZ :
								ilImageCubeFlags == CubemapFace::PositiveZ ? Image::Mipmap::Face::PositiveZ :
								throw Exception();

							for (auto &mipmapIndex : Range(mipmapsCount))
							{
								BindImage(imageHandle);
								ActiveImage(0);				// need to bind all this values each time
								ActiveLayer(0);				//
								ActiveFace(faceIndex);		//
								ActiveMipmap(mipmapIndex);	//

								auto ilOrigin = GetOrigin();

								if (ilOrigin != Origin::UpperLeft)
								{
									iluFlipImage();
								}

								auto ilWidth			= GetInteger(Parameter::ImageWidth);
								auto ilDataSize			= GetInteger(Parameter::ImageSizeOfData);
								auto ilData				= GetData();

								auto width				= static_cast<Size>(ilWidth);
								auto dataAmount			= Size(width * width);
								auto dataSize			= sizeof(Pixel) * dataAmount;
								auto data				= Memory<Pixel>(ilData);

								if (ilDataSize != static_cast<decltype(ilDataSize)>(dataSize))
								{
									throw Exception(); // TODO
								}

								auto &mipmapFacesData = mipmapsFacesData[mipmapIndex];
								auto &facesSize = mipmapFacesData.first;

								facesSize = width;

								auto &facesData = mipmapFacesData.second[static_cast<Size>(face)];

								facesData.resize(dataAmount);
								CopyMemory(facesData.data(), data, dataAmount);
							}
						}

						Image::Mipmaps mipmaps;

						for (auto &i : Range(mipmapsFacesData.size()))
						{
							auto &mipmapFacesData = mipmapsFacesData[i];
							auto &facesSize = mipmapFacesData.first;
							auto &facesData = mipmapFacesData.second;

							mipmaps.emplace_back(facesSize, Move(facesData));
						}

						auto image = MakeStrong<Image>(Move(mipmaps));

						return Move(image);
					}
					else
					{
						BindImage(ImageHandle::None());

						DeleteImage(imageHandle);

						throw GreatVEngine2::NotImplementedException(); // TODO
					}
				}
			}
			else
			{
				BindImage(ImageHandle::None());

				DeleteImage(imageHandle);

				throw GreatVEngine2::NotImplementedException(); // TODO
			}
		}
		else
		{
			BindImage(ImageHandle::None());

			DeleteImage(imageHandle);

			throw GreatVEngine2::Exception(); // TODO
		}
	}

	BindImage(ImageHandle::None());

	DeleteImage(imageHandle);

	throw Exception(); // TODO
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


