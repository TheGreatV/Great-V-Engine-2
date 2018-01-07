#include <iostream>

#include <../Common/Common.hpp>

namespace GVE = GreatVEngine2;
using namespace GVE;


void main()
{
	auto x = AllocateMemory<int>(1);

	x[0] = 5;

	auto y = AllocateMemory<int>(1);

	CopyMemory(y, x, 1);

	ReleaseMemory(x);

	if (y[0] != 5)
	{
		throw std::exception();
	}


	std::system("pause");
}