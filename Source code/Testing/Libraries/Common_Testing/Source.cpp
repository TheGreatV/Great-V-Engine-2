#include <iostream>

#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;

#include <memory>

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

// call tracker
class CallTracker
{
public:
	CallTracker()
	{
		std::cout << "CallTracker()" << std::endl;
	}
	CallTracker(const CallTracker&)
	{
		std::cout << "CallTracker(const CallTracker&)" << std::endl;
	}
	CallTracker(CallTracker&&)
	{
		std::cout << "CallTracker(CallTracker&&)" << std::endl;
	}
	~CallTracker()
	{
		std::cout << "~CallTracker()" << std::endl;
	}
	CallTracker& operator = (const CallTracker&)
	{
		std::cout << "operator = (const CallTracker&)" << std::endl;

		return *this;
	}
	CallTracker& operator = (CallTracker&&)
	{
		std::cout << "operator = (CallTracker&&)" << std::endl;

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
void Reference_ConstantPointer_CreatingAndDestroying()
{
	// empty
	CallChecker::Reset();
	{
		GVE::ConstantPointer<CallChecker> p;

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

	// nullptr
	CallChecker::Reset();
	{
		GVE::ConstantPointer<CallChecker> p(nullptr);

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

	// new
	CallChecker::Reset();
	{
		auto p = new CallChecker();

		auto p1 = GVE::ConstantPointer<CallChecker>(p);

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

	// make unique
	CallChecker::Reset();
	{
		auto p = GVE::MakeConstant<CallChecker>();

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

	// arguments
	auto p = GVE::MakeConstant<ArgumentsChecker>(5, 10.0f);

	Check(p->x == 5 && p->y == 10.0f);
}
void Reference_ConstantPointer_Move()
{
	// move copy
	CallChecker::Reset();

	auto test = []()
	{
		auto p = GVE::MakeConstant<CallChecker>();

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
void Reference_ConstantPointer_Selector()
{
	class Test
	{
	public:
		int x = 0;
	};

	auto p = new Test();
	auto u = GVE::ConstantPointer<Test>(p);

	u->x = 5;

	Check(p->x == 5);

	(*u).x = 10;
	
	Check(p->x == 10);

	auto p2 = new Test();
	const GVE::ConstantPointer<Test> u2(p2);

	p2->x = 15;

	Check((*u2).x == 15);
	Check(u2->x == 15);
}
void Reference_ConstantPointer_Value()
{
	auto p = new int();
	auto c = GVE::ConstantPointer<int>(p);

	Check(c.GetValue() == p);

	// cast to value
	auto r1 = [&](int* x) -> bool
	{
		return x == p;
	}(c);

	Check(r1 == true);

	auto r2 = [&](const int* x) -> bool
	{
		return x == p;
	}(c);

	Check(r2 == true);

	// operators
	Check((c == c) == true);
	Check((c != c) == false);

	Check((c == p) == true);
	Check((c != p) == false);
	Check((p == c) == true);
	Check((p != c) == false);
	
	Check((c == nullptr) == false);
	Check((c != nullptr) == true);
	Check((nullptr == c) == false);
	Check((nullptr != c) == true);

	auto c2 = GVE::MakeConstant<int>();

	Check((c == c2) == false);
	Check((c != c2) == true);

	auto e = GVE::ConstantPointer<int>(nullptr);

	Check(static_cast<bool>(e) == false);
	Check((e == nullptr) == true);
	Check((e != nullptr) == false);
}

void Reference_UniquePointer_CreatingAndDestroying()
{
	// empty
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

	// nullptr
	CallChecker::Reset();
	{
		GVE::UniquePointer<CallChecker> p(nullptr);

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

	// new
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

	// make unique
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

	// arguments
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
void Reference_UniquePointer_Selector()
{
	class Test
	{
	public:
		int x = 0;
	};

	auto p = new Test();
	auto u = GVE::UniquePointer<Test>(p);

	u->x = 5;

	Check(p->x == 5);

	(*u).x = 10;
	
	Check(p->x == 10);

	auto p2 = new Test();
	const GVE::UniquePointer<Test> u2(p2);

	p2->x = 15;

	Check((*u2).x == 15);
	Check(u2->x == 15);
}
void Reference_UniquePointer_Value()
{
	auto p = new int();
	auto u = GVE::UniquePointer<int>(p);

	// get value
	Check(u.GetValue() == p);

	// cast to value
	auto r1 = [&](int* x) -> bool
	{
		return x == p;
	}(u);

	Check(r1 == true);

	auto r2 = [&](const int* x) -> bool
	{
		return x == p;
	}(u);

	Check(r2 == true);

	// operators
	Check(static_cast<bool>(u) == true);
	Check((u == nullptr) == false);
	Check((u != nullptr) == true);

	Check((p == u) == true);
	Check((u == p) == true);
	Check((p != u) == false);
	Check((u != p) == false);

	Check((u == u) == true);
	Check((u != u) == false);

	auto u2 = GVE::MakeUnique<int>();

	Check((u == u2) == false);
	Check((u != u2) == true);

	auto e = GVE::UniquePointer<int>(nullptr);

	Check(static_cast<bool>(e) == false);
	Check((e == nullptr) == true);
	Check((e != nullptr) == false);
}

void Reference_SharedPointer_CreationAndDestroying()
{
	// empty
	CallChecker::Reset();
	{
		auto x = GVE::SharedPointer<CallChecker>();

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

	// nullptr
	CallChecker::Reset();
	{
		auto x = GVE::SharedPointer<CallChecker>(nullptr);

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

	// new
	CallChecker::Reset();
	{
		auto x = GVE::SharedPointer<CallChecker>(new CallChecker());

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

	// make shared
	CallChecker::Reset();
	{
		auto x = GVE::MakeShared<CallChecker>();

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

	// arguments
	auto p = GVE::MakeShared<ArgumentsChecker>(5, 10.0f);

	Check(p->x == 5 && p->y == 10.0f);
}


void main()
{
	Memory_AllocationAndReleasing();
	Memory_Copy();
	Memory_Compare();


	Move_Move();
	Move_Forward();


	Reference_ConstantPointer_CreatingAndDestroying();
	Reference_ConstantPointer_Move();
	Reference_ConstantPointer_Selector();
	Reference_ConstantPointer_Value();

	Reference_UniquePointer_CreatingAndDestroying();
	Reference_UniquePointer_Move();
	Reference_UniquePointer_Selector();
	Reference_UniquePointer_Value();

	Reference_SharedPointer_CreationAndDestroying();


	std::system("pause");
}