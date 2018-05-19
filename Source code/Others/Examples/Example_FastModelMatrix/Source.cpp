#include <iostream>

#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;


class Scalar
{
public:
	String v;
	Scalar() = default;
	Scalar(const int& s):
		v(ToString(s))
	{
	}
	Scalar(const String& s):
		v(s)
	{
	}
	inline Scalar operator + (const Scalar& s) const
	{
		return
			v == "0"	? s :
			s.v == "0"	? v :
			v + " + " + s.v;
	}
	inline Scalar operator * (const Scalar& s) const
	{
		return
			v == "0" || s.v == "0"	? String("0") :
			v == "1"				? s :
			s.v == "1"				? v :
			v + " * " + s.v;
	}
	inline Scalar operator - () const
	{
		return "-" + v;
	}
};
template<class T>
class Mat
{
public:
	/*
		v[x][y]
		v[0][0]	v[1][0]	v[2][0]	v[3][0]
		v[0][1]	v[1][1]	v[2][1]	v[3][1]
		v[0][2]	v[1][2]	v[2][2]	v[3][2]
		v[0][3]	v[1][3]	v[2][3]	v[3][3]
	*/
	Array<Array<T, 4>, 4> v; // v[][]
	Mat(
		const T& v00_, const T& v01_, const T& v02_, const T& v03_,
		const T& v10_, const T& v11_, const T& v12_, const T& v13_,
		const T& v20_, const T& v21_, const T& v22_, const T& v23_,
		const T& v30_, const T& v31_, const T& v32_, const T& v33_
	)
	{
		v[0][0]	= v00_;
		v[0][1]	= v01_;
		v[0][2]	= v02_;
		v[0][3]	= v03_;

		v[1][0]	= v10_;
		v[1][1]	= v11_;
		v[1][2]	= v12_;
		v[1][3]	= v13_;

		v[2][0]	= v20_;
		v[2][1]	= v21_;
		v[2][2]	= v22_;
		v[2][3]	= v23_;

		v[3][0]	= v30_;
		v[3][1]	= v31_;
		v[3][2]	= v32_;
		v[3][3]	= v33_;
	}
	Mat operator * (const Mat& s) const
	{
		auto f = [&](int x, int y)
		{
			return
				v[0][x] * s.v[y][0] +
				v[1][x] * s.v[y][1] +
				v[2][x] * s.v[y][2] +
				v[3][x] * s.v[y][3];
		};

		return Mat(
			f(0, 0), f(1, 0), f(2, 0), f(3, 0),
			f(0, 1), f(1, 1), f(2, 1), f(3, 1),
			f(0, 2), f(1, 2), f(2, 2), f(3, 2),
			f(0, 3), f(1, 3), f(2, 3), f(3, 3)
		);
	}
	static Mat Transpose(const Mat& s)
	{
		return Mat(
			s.v[0][0], s.v[1][0], s.v[2][0], s.v[3][0],
			s.v[0][1], s.v[1][1], s.v[2][1], s.v[3][1],
			s.v[0][2], s.v[1][2], s.v[2][2], s.v[3][2],
			s.v[0][3], s.v[1][3], s.v[2][3], s.v[3][3]
		);
	}
	static Mat Move4(const T& x, const T& y, const T& z)
	{
		return Transpose(Mat(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		));
	}
	static Mat Scale4(const T& x, const T& y, const T& z)
	{
		return Transpose(Mat(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
			));
	}
	static Mat RotateX4(const T& x)
	{
		auto s = Scalar("s" + x.v);
		auto c = Scalar("c" + x.v);

		return Transpose(Mat(
			Scalar(1),	Scalar(0),	Scalar(0),	Scalar(0),
			Scalar(0),	c,			-s,			Scalar(0),
			Scalar(0),	s,			c,			Scalar(0),
			Scalar(0),	Scalar(0),	Scalar(0),	Scalar(1)
		));
	}
	static Mat RotateY4(const T& x)
	{
		auto s = Scalar(String("s" + x.v));
		auto c = Scalar(String("c" + x.v));

		return Transpose(Mat(
			c,			Scalar(0),	s,			Scalar(0),
			Scalar(0),	Scalar(1),	Scalar(0),	Scalar(0),
			-s,			Scalar(0),	c,			Scalar(0),
			Scalar(0),	Scalar(0),	Scalar(0),	Scalar(1)
		));
	}
	static Mat RotateZ4(const T& x)
	{
		auto s = Scalar(String("s" + x.v));
		auto c = Scalar(String("c" + x.v));

		return Transpose(Mat(
			c,			s,			Scalar(0),	Scalar(0),
			-s,			c,			Scalar(0),	Scalar(0),
			Scalar(0),	Scalar(0),	Scalar(1),	Scalar(0),
			Scalar(0),	Scalar(0),	Scalar(0),	Scalar(1)
		));
	}
};


void Print(const Mat<Scalar>& m)
{
	std::cout <<
		m.v[0][0].v << " | " << m.v[1][0].v << " | " << m.v[2][0].v << " | " << m.v[3][0].v << std::endl <<
		m.v[0][1].v << " | " << m.v[1][1].v << " | " << m.v[2][1].v << " | " << m.v[3][1].v << std::endl <<
		m.v[0][2].v << " | " << m.v[1][2].v << " | " << m.v[2][2].v << " | " << m.v[3][2].v << std::endl <<
		m.v[0][3].v << " | " << m.v[1][3].v << " | " << m.v[2][3].v << " | " << m.v[3][3].v << std::endl;
}
void Print2(const Mat<Scalar>& m)
{
	std::cout <<
		"[0][0] = " << m.v[0][0].v << std::endl <<
		"[1][0] = " << m.v[1][0].v << std::endl <<
		"[2][0] = " << m.v[2][0].v << std::endl <<
		"[3][0] = " << m.v[3][0].v << std::endl << std::endl <<

		"[0][1] = " << m.v[0][1].v << std::endl <<
		"[1][1] = " << m.v[1][1].v << std::endl <<
		"[2][1] = " << m.v[2][1].v << std::endl <<
		"[3][1] = " << m.v[3][1].v << std::endl << std::endl <<

		"[0][2] = " << m.v[0][2].v << std::endl <<
		"[1][2] = " << m.v[1][2].v << std::endl <<
		"[2][2] = " << m.v[2][2].v << std::endl <<
		"[3][2] = " << m.v[3][2].v << std::endl << std::endl <<

		"[0][3] = " << m.v[0][3].v << std::endl <<
		"[1][3] = " << m.v[1][3].v << std::endl <<
		"[2][3] = " << m.v[2][3].v << std::endl <<
		"[3][3] = " << m.v[3][3].v << std::endl <<
		std::endl;
}
void Print(const Mat4& m)
{
	std::cout <<
		m[0][0] << " | " << m[1][0] << " | " << m[2][0] << " | " << m[3][0] << std::endl <<
		m[0][1] << " | " << m[1][1] << " | " << m[2][1] << " | " << m[3][1] << std::endl <<
		m[0][2] << " | " << m[1][2] << " | " << m[2][2] << " | " << m[3][2] << std::endl <<
		m[0][3] << " | " << m[1][3] << " | " << m[2][3] << " | " << m[3][3] << std::endl;
}


void main()
{
	using M = Mat<Scalar>;

	/*auto a0 = M(
		String("1"), String("2"), String("3"), String("4"),
		String("0"), String("0"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0")
	);
	auto b0 = Mat4(
		1.0f, 2.0f, 3.0f, 4.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	Print(a0);
	Print(b0);
	std::cout << std::endl;

	auto a2 = M::Transpose(M(
		1, 0, 0, 10,
		0, 1, 0, 20,
		0, 0, 1, 30,
		0, 0, 0, 1
	));
	auto b2 = Transpose(Mat4(
		1.0f, 0.0f, 0.0f, 10.0f,
		0.0f, 1.0f, 0.0f, 20.0f,
		0.0f, 0.0f, 1.0f, 30.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	));
	Print(a2);
	Print(b2);
	std::cout << std::endl;

	auto a3 = M::Move4(10, 20, 30);
	auto b3 = Move4(Vec3(10.0f, 20.0f, 30.0f));
	Print(a3);
	Print(b3);
	std::cout << std::endl;

	auto a4 =
	M(
		String("0"), String("1"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0")
	)
	*
	M(
		String("0"), String("0"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0"),
		String("1"), String("0"), String("0"), String("0"),
		String("0"), String("0"), String("0"), String("0")
	);
	auto b4 =
	Mat4(
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	)
	*
	Mat4(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	Print(a4);
	Print(b4);
	std::cout << std::endl;*/

	auto m =
		M::Move4(String("px"), String("py"), String("pz")) *
		M::RotateY4(String("ay")) *
		M::RotateX4(String("ax")) *
		M::RotateZ4(String("az")) *
		M::Scale4(String("sx"), String("sy"), String("sz"));

	Print2(m);

	std::system("pause");
}