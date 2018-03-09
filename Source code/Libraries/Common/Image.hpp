#pragma region Include

#pragma once

#include "Header.hpp"
#include "Size.hpp"
#include "Memory.hpp"
#include "Mathematics.hpp"
#include "Collection.hpp"

#pragma endregion


namespace GreatVEngine2
{
	template<class Red, class Green = void, class Blue = void, class Alpha = void> class Pixel
	{
	protected:
		Red red;
		Green green;
		Blue blue;
		Alpha alpha;
	public:
		inline Red GetRed() const;
		inline Green GetGreen() const;
		inline Blue GetBlue() const;
		inline Alpha GetAlpha() const;
	};
	template<class Red, class Green, class Blue> class Pixel<Red, Green, Blue, void>
	{
	protected:
		Red red;
		Green green;
		Blue blue;
	public:
		inline Pixel() = default;
		inline Pixel(const Pixel&) = default;
		inline Pixel(const Red& red_, const Green& green_, const Blue& blue_):
			red(red_), green(green_), blue(blue_)
		{
		}
		inline ~Pixel() = default;
	public:
		inline Red GetRed() const;
		inline Green GetGreen() const;
		inline Blue GetBlue() const;
	};
	template<class Red, class Green> class Pixel<Red, Green, void, void>
	{
	protected:
		Red red;
		Green green;
	public:
		inline Red GetRed() const;
		inline Green GetGreen() const;
	};
	template<class Red> class Pixel<Red, void, void, void>
	{
	protected:
		Red red;
	public:
		inline Red GetRed() const;
	};

	class Mipmap
	{
	public:
		using Data = Memory<const void>;
	public:
		virtual ~Mipmap() = default;
	};
	class Mipmap2D:
		public Mipmap
	{
	public:
		virtual ~Mipmap2D() override = default;
	public:
		virtual Size2 GetSize() const = 0;
		virtual Data GetData() const = 0;
	};
	class MipmapCube:
		public Mipmap
	{
	public:
		enum class Face
		{
			PositiveX	= 0,
			NegativeX	= 1,
			PositiveY	= 2,
			NegativeY	= 3,
			PositiveZ	= 4,
			NegativeZ	= 5,
			Count		= 6,
		};
	public:
		using FacesData = Array<Data, static_cast<Size>(Face::Count)>;
	public:
		class AccessorFace
		{
		public:
			virtual Data GetData() const = 0;
		};
	public:
		virtual ~MipmapCube() override = default;
	public:
		virtual Size GetSize() const = 0;
		virtual FacesData GetData() const = 0;
		inline Size GetFacesCount() const
		{
			return static_cast<Size>(Face::Count);
		}
	};

	template<class Pixel> class Mipmap2DX:
		public Mipmap2D
	{
	public:
		using Buffer = Vector<Pixel>; // Buffer<Pixel>;
	protected:
		class AccessorX
		{
		protected:
			const Memory<const Mipmap2DX> mipmap; // TODO: replace with "&" ?
			const Size& x;
		public:
			inline AccessorX() = delete;
			inline AccessorX(const Mipmap2DX& mipmap_, const Size& x_):
				mipmap(&mipmap_),
				x(x_)
			{
			}
			inline AccessorX(const AccessorX&) = default;
			inline ~AccessorX() = default;
		public:
			inline const Pixel& operator [] (const Size& y_) const
			{
				return mipmap->pixels[y_ * mipmap->width + x];
			}
		};
		friend AccessorX;
	protected:
		Size2 size = 0;
		Buffer pixels;
	public:
		inline Mipmap2DX() = default;
		inline Mipmap2DX(const Mipmap2DX& source_) = default;
		inline Mipmap2DX(Mipmap2DX&& source_):
			size(source_.size),
			pixels(Move(source_.pixels))
		{
		}
		inline virtual ~Mipmap2DX() override = default;
	public:
		inline Mipmap2DX(const Size2& size_, Vector<Pixel>&& pixels_):
			size(size_),
			pixels(Move(pixels_)) // TODO: size check // pixels(width_, pixels_.data())
		{
		}
		inline Mipmap2DX(const Size2& size_, const Memory<const Pixel>& pixels_):
			size(size_),
			pixels(size.x * size.y)
		{
			CopyMemory<Pixel>(pixels.data(), pixels_, pixels.size());
		}
	public:
		inline Mipmap2DX& operator = (const Mipmap2DX& source_) = default;
		inline Mipmap2DX& operator = (Mipmap2DX&& source_)
		{
			size = source_.size;
			pixels = Move(source_.pixels);

			return *this;
		}
	public:
		inline const AccessorX operator [] (const Size& x_) const
		{
			return AccessorX(*this, x_);
		}
	public:
		virtual Size2 GetSize() const override
		{
			return size;
		}
		virtual Data GetData() const override
		{
			return pixels.data();
		}
	};
	template<class Pixel> class MipmapCubeX:
		public MipmapCube
	{
	public:
		using Faces = Array<Vector<Pixel>, static_cast<Size>(Face::Count)>;
	public:
		class AccessorX
		{
		protected:
			const Memory<const MipmapCubeX> mipmap; // TODO: replace with "&" ?
			const Face& face;
			const Size& x;
		public:
			inline AccessorX() = delete;
			inline AccessorX(const MipmapCubeX& mipmap_, const Face& face_, const Size& x_):
				mipmap(&mipmap_),
				face(face_),
				x(x_)
			{
			}
			inline AccessorX(const AccessorX&) = default;
			inline ~AccessorX() = default;
		public:
			inline const Pixel& operator [] (const Size& y_) const
			{
				return mipmap->faces[static_cast<Size>(face)][y_ * mipmap->size + x];
			}
		};
		class AccessorFace
		{
		protected:
			const Memory<const MipmapCubeX> mipmap; // TODO: replace with "&" ?
			const Face& face;
		public:
			inline AccessorFace() = delete;
			inline AccessorFace(const MipmapCubeX& mipmap_, const Face& face_):
				mipmap(&mipmap_),
				face(face_)
			{
			}
			inline AccessorFace(const AccessorFace&) = default;
			inline ~AccessorFace() = default;
		public:
			inline const AccessorX operator [] (const Size& x_) const
			{
				return AccessorX(*mipmap, face, x_);
			}
		};
		friend AccessorX;
		friend AccessorFace;
	protected:
		Size size = 0;
		Faces faces;
	public:
		inline MipmapCubeX() = default;
		inline MipmapCubeX(const MipmapCubeX& source_) = default;
		inline MipmapCubeX(MipmapCubeX&& source_):
			size(source_.size),
			faces(Move(source_.faces))
		{
		}
		inline virtual ~MipmapCubeX() override = default;
	public:
		inline MipmapCubeX(const Size& size_, Faces&& faces_):
			size(size_),
			faces(faces_)
		{
			for (auto &face : faces_)
			{
				if (face.size() != size * size)
				{
					throw Exception();
				}
			}
		}
	public:
		inline MipmapCubeX& operator = (const MipmapCubeX& source_) = default;
		inline MipmapCubeX& operator = (MipmapCubeX&& source_)
		{
			size = source_.size;
			faces = Move(source_.faces);
		
			return *this;
		}
	public:
		inline const AccessorFace operator [] (const Face& face_) const
		{
			return AccessorFace(*this, face_);
		}
	public:
		inline virtual Size GetSize() const override
		{
			return size;
		}
		inline virtual FacesData GetData() const override
		{
			FacesData facesData;

			for (auto &i : Range(GetFacesCount()))
			{
				facesData[i] = faces[i].data();
			}

			return facesData;
		}
	};

	class Image
	{
	public:
		virtual ~Image() = default;
	};
	class Image2D:
		public Image
	{
	public:
		virtual ~Image2D() override = default;
	public:
		virtual const Mipmap2D& operator [] (const Size& index_) const = 0;
	public:
		virtual Size GetMipmapsCount() const = 0;
	};
	class ImageCube:
		public Image
	{
	public:
		virtual ~ImageCube() override = default;
	public:
		virtual const MipmapCube& operator [] (const Size& index_) const = 0;
	public:
		virtual Size GetMipmapsCount() const = 0;
	};
	
	template<class Pixel> class Image2DX:
		public Image2D
	{
	public:
		using Mipmap = Mipmap2DX<Pixel>;
		using Mipmaps = Vector<Mipmap>;
	protected:
		Mipmaps mipmaps;
	public:
		inline Image2DX() = default;
		inline Image2DX(Mipmaps&& mipmaps_):
			mipmaps(Move(mipmaps_))
		{
		}
		inline Image2DX(const Image2DX&) = default;
		inline Image2DX(Image2DX&& source_):
			mipmaps(Move(source_.mipmaps))
		{
		}
		inline virtual ~Image2DX() override = default;
	public:
		inline Image2DX& operator = (const Image2DX&) = default;
		inline Image2DX& operator = (Image2DX&& source_)
		{
			mipmaps = Move(source_.mipmaps);

			return *this;
		}
	public:
		inline const Mipmap& operator [] (const Size& index_) const override
		{
			return mipmaps[index_];
		}
	public:
		virtual Size GetMipmapsCount() const override
		{
			return mipmaps.size();
		}
	};
	template<class Pixel> class ImageCubeX:
		public ImageCube
	{
	public:
		using Mipmap = MipmapCubeX<Pixel>;
		using Mipmaps = Vector<Mipmap>;
	protected:
		Mipmaps mipmaps;
	public:
		inline ImageCubeX() = default;
		inline ImageCubeX(Mipmaps&& mipmaps_):
			mipmaps(Move(mipmaps_))
		{
		}
		inline ImageCubeX(const ImageCubeX&) = default;
		inline ImageCubeX(ImageCubeX&& source_):
			mipmaps(Move(source_.mipmaps))
		{
		}
		inline virtual ~ImageCubeX() override = default;
	public:
		inline ImageCubeX& operator = (const ImageCubeX&) = default;
		inline ImageCubeX& operator = (ImageCubeX&& source_)
		{
			mipmaps = Move(source_.mipmaps);

			return *this;
		}
	public:
		inline const Mipmap& operator [] (const Size& index_) const override
		{
			return mipmaps[index_];
		}
	public:
		virtual Size GetMipmapsCount() const override
		{
			return mipmaps.size();
		}
	};
}


#pragma region GreatVEngine2
#pragma endregion


#pragma region
#pragma endregion


