#include <iostream>

#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;


void Check(bool x)
{
	if (!x)
	{
		throw std::exception();
	}
}


// call checker
int constructorCallsCounter = 0;
int copyCallsCounter = 0;
int moveCopyCallsCounter = 0;
int destructorCallsCounter = 0;
int assignmentCallsCounter = 0;
int moveAssignmentCallsCounter = 0;

class CallChecker
{
public:
	static void Reset()
	{
		constructorCallsCounter = 0;
		copyCallsCounter = 0;
		moveCopyCallsCounter = 0;
		destructorCallsCounter = 0;
		assignmentCallsCounter = 0;
		moveAssignmentCallsCounter = 0;
	}
public:
	CallChecker()
	{
		++constructorCallsCounter;
	}
	CallChecker(const CallChecker&)
	{
		++copyCallsCounter;
	}
	CallChecker(CallChecker&&)
	{
		++moveCopyCallsCounter;
	}
	~CallChecker()
	{
		++destructorCallsCounter;
	}
	CallChecker& operator = (const CallChecker&)
	{
		++assignmentCallsCounter;

		return *this;
	}
	CallChecker& operator = (CallChecker&&)
	{
		++moveAssignmentCallsCounter;

		return *this;
	}
};

// arguments checker
class ArgumentsChecker
{
public:
	int x;
	float y;
	ArgumentsChecker(const int& x_, const float& y_):
		x(x_), y(y_)
	{
	}
};


// Memory
void Memory_AllocationAndReleasing()
{
	// single
	auto memory1 = GVE::AllocateMemory<int>(1);

	memory1[0] = 5;

	Check(memory1[0] == 5);

	GVE::ReleaseMemory(memory1);

	// multiple
	auto memory2 = GVE::AllocateMemory<int>(10);

	for (int i = 0; i < 10; ++i)
	{
		memory2[i] = i;
	}

	for (int i = 0; i < 10; ++i)
	{
		Check(memory2[i] == i);
	}

	GVE::ReleaseMemory(memory2);
}
void Memory_Copy()
{
	// single
	auto memory1 = GVE::AllocateMemory<int>(1);

	memory1[0] = 5;

	auto memory2 = GVE::AllocateMemory<int>(1);

	GVE::CopyMemory(memory2, memory1, 1);

	GVE::ReleaseMemory(memory1);

	Check(memory2[0] == 5);

	GVE::ReleaseMemory(memory2);

	// multiple
	auto memory3 = GVE::AllocateMemory<int>(10);

	for (int i = 0; i < 10; ++i)
	{
		memory3[i] = i;
	}

	auto memory4 = GVE::AllocateMemory<int>(10);

	GVE::CopyMemory(memory4, memory3, 10);

	GVE::ReleaseMemory(memory3);

	for (int i = 0; i < 10; ++i)
	{
		memory4[i] = i;
	}

	GVE::ReleaseMemory(memory4);
}
void Memory_Compare()
{
	// single positive
	auto memory1 = GVE::AllocateMemory<int>(1);

	memory1[0] = 5;

	auto memory2 = GVE::AllocateMemory<int>(1);

	memory2[0] = 5;

	Check(GVE::CompareMemory(memory1, memory2, 1) == true);

	GVE::ReleaseMemory(memory1);
	GVE::ReleaseMemory(memory2);

	// single negative
	auto memory1n = GVE::AllocateMemory<int>(1);

	memory1n[0] = 5;

	auto memory2n = GVE::AllocateMemory<int>(1);

	memory2n[0] = 6;

	Check(GVE::CompareMemory(memory1n, memory2n, 1) == false);

	GVE::ReleaseMemory(memory1n);
	GVE::ReleaseMemory(memory2n);

	// multiple positive
	auto memory3 = GVE::AllocateMemory<int>(10);

	for (int i = 0; i < 10; ++i)
	{
		memory3[i] = i;
	}

	auto memory4 = GVE::AllocateMemory<int>(10);

	for (int i = 0; i < 10; ++i)
	{
		memory4[i] = i;
	}

	Check(GVE::CompareMemory(memory3, memory4, 10) == true);

	GVE::ReleaseMemory(memory3);
	GVE::ReleaseMemory(memory4);

	// multiple negative
	auto memory3n = GVE::AllocateMemory<int>(10);

	for (int i = 0; i < 10; ++i)
	{
		memory3n[i] = i;
	}

	auto memory4n = GVE::AllocateMemory<int>(10);

	for (int i = 0; i < 10; ++i)
	{
		memory4n[i] = i * 2;
	}

	Check(GVE::CompareMemory(memory3n, memory4n, 10) == false);

	GVE::ReleaseMemory(memory3n);
	GVE::ReleaseMemory(memory4n);
}


// Move
void Move_ForwardFunction(int& x)
{
	x = 5;
}
template<class... T>
void Move_ForwardFunction1(T... t)
{
	Move_ForwardFunction(t...);
}
template<class... T>
void Move_ForwardFunction2(T&&... t)
{
	Move_ForwardFunction(GVE::Forward<T>(t)...);
}

void Move_Move()
{
	/*class Test
	{
	public:
		Test()
		{
			std::cout << "Test()" << std::endl;
		}
		Test(const Test&)
		{
			std::cout << "Test(const Test&)" << std::endl;
		}
		Test(Test&&)
		{
			std::cout << "Test(Test&&)" << std::endl;
		}
		~Test()
		{
			std::cout << "~Test()" << std::endl;
		}
		Test& operator = (const Test&)
		{
			std::cout << "operator = (const Test&)" << std::endl;

			return *this;
		}
		Test& operator = (Test&&)
		{
			std::cout << "operator = (Test&&)" << std::endl;

			return *this;
		}
		static Test Function()
		{
			Test x;

			return std::move(x);
		}
	};*/

	/*
	Test t1;
	Test t2 = t1;
	Test t3 = Test::Function();

	t1 = t2;
	t1 = std::move(t2);
	t1 = Test::Function();
	*/

	CallChecker x;

	constructorCallsCounter = 0;
	copyCallsCounter = 0;
	moveCopyCallsCounter = 0;
	destructorCallsCounter = 0;
	assignmentCallsCounter = 0;
	moveAssignmentCallsCounter = 0;

	CallChecker y(GVE::Move(x));

	Check(
		constructorCallsCounter == 0 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 1 &&
		destructorCallsCounter == 0 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	constructorCallsCounter = 0;
	copyCallsCounter = 0;
	moveCopyCallsCounter = 0;
	destructorCallsCounter = 0;
	assignmentCallsCounter = 0;
	moveAssignmentCallsCounter = 0;

	x = GVE::Move(y);

	Check(
		constructorCallsCounter == 0 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 0 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 1
	);
}
void Move_Forward()
{
	int x = 0;

	Move_ForwardFunction1(x);

	Check(x == 0);

	Move_ForwardFunction2(x);

	Check(x == 5);
}


// Reference
void Reference_UniquePointer_CreatingAndDestroying()
{
	CallChecker::Reset();
	{
		GVE::UniquePointer<CallChecker> p;

		Check(
			constructorCallsCounter == 0 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 0 &&
			assignmentCallsCounter == 0 &&
			moveAssignmentCallsCounter == 0
		);
	}

	Check(
		constructorCallsCounter == 0 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 0 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	CallChecker::Reset();
	{
		auto p = new CallChecker();

		auto p1 = GVE::UniquePointer<CallChecker>(p);

		Check(
			constructorCallsCounter == 1 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 0 &&
			assignmentCallsCounter == 0 &&
			moveAssignmentCallsCounter == 0
		);
	}

	Check(
		constructorCallsCounter == 1 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 1 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	CallChecker::Reset();
	{
		auto p = GVE::MakeUnique<CallChecker>();

		Check(
			constructorCallsCounter == 1 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 0 &&
			assignmentCallsCounter == 0 &&
			moveAssignmentCallsCounter == 0
		);
	}

	Check(
		constructorCallsCounter == 1 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 1 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	auto p = GVE::MakeUnique<ArgumentsChecker>(5, 10.0f);

	Check(p->x == 5 && p->y == 10.0f);
}
void Reference_UniquePointer_Move()
{
	// move assignment
	CallChecker::Reset();
	{
		GVE::UniquePointer<CallChecker> p1;
		{
			auto p2 = GVE::MakeUnique<CallChecker>();
			
			CallChecker::Reset();

			p1 = GVE::Move(p2);

			Check(
				constructorCallsCounter == 0 &&
				copyCallsCounter == 0 &&
				moveCopyCallsCounter == 0 &&
				destructorCallsCounter == 0 &&
				assignmentCallsCounter == 0 &&
				moveAssignmentCallsCounter == 0
			);
		}

		Check(
			constructorCallsCounter == 0 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 0 &&
			assignmentCallsCounter == 0 &&
			moveAssignmentCallsCounter == 0
		);
	}

	Check(
		constructorCallsCounter == 0 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 1 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	// move copy
	CallChecker::Reset();

	auto test = []()
	{
		auto p = GVE::MakeUnique<CallChecker>();

		return p;
	};

	{
		auto p = test();

		Check(
			constructorCallsCounter == 1 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 0 &&
			assignmentCallsCounter == 0 &&
			moveAssignmentCallsCounter == 0
		);
	}

	Check(
		constructorCallsCounter == 1 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 1 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);
}

void main()
{
	Memory_AllocationAndReleasing();
	Memory_Copy();
	Memory_Compare();

	Move_Move();
	Move_Forward();

	Reference_UniquePointer_CreatingAndDestroying();
	Reference_UniquePointer_Move();

	std::system("pause");
}