#include <../Common/Common.hpp>

namespace GVE = GreatVEngine2;
using namespace GVE;


void main()
{
	using Pixel = Pixel<UInt8, UInt8, UInt8>;
	using Mipmap = MipmapCubeX<Pixel>;
	{
		Mipmap a;
		Mipmap b; b = a;
		Mipmap c(Move(b));
		Mipmap d; d = Move(c);

		Mipmap::Faces initializer;
		{
			for (auto &i : initializer)
			{
				i = { Pixel(0, 0, 0) };
			}
		}

		Mipmap mipmap(1, Move(initializer));

		mipmap.GetSize();
		mipmap.GetFacesCount();

		auto &t = mipmap[Mipmap::Face::NegativeX][0][0];
	}

	using Image = ImageCubeX<Pixel>;
	{
		Mipmap::Faces initializer;
		{
			for (auto &i : initializer)
			{
				i = {Pixel(0, 0, 0)};
			}
		}

		Image image({Mipmap(1, Move(initializer))});

		image.GetMipmapsCount();

		auto &t = image[0][Mipmap::Face::NegativeX][0][0];
	}
}
