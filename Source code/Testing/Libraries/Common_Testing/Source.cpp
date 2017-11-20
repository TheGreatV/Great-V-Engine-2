#include <iostream>

#include <../Common/Common.hpp>
namespace GVE = GreatVEngine2;

#include <memory>
#include <ctime>

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

// Inheritance checker
class StaticInheritanceCheckerBase
{
public:
	int x;
	StaticInheritanceCheckerBase() = default;
	StaticInheritanceCheckerBase(int x_):
		x(x_)
	{
	}
};
class StaticInheritanceCheckerDerived:
	public StaticInheritanceCheckerBase
{
public:
	int y;
	StaticInheritanceCheckerDerived() = default;
	StaticInheritanceCheckerDerived(int y_, int x_):
		StaticInheritanceCheckerBase(x_),
		y(y_)
	{
	}
};

class DynamicInheritanceCheckerBase
{
public:
	int x;
	DynamicInheritanceCheckerBase() = default;
	DynamicInheritanceCheckerBase(int x_):
		x(x_)
	{
	}
	virtual ~DynamicInheritanceCheckerBase() = default;
};
class DynamicInheritanceCheckerDerived:
	public DynamicInheritanceCheckerBase
{
public:
	int y;
	DynamicInheritanceCheckerDerived() = default;
	DynamicInheritanceCheckerDerived(int y_, int x_):
		DynamicInheritanceCheckerBase(x_),
		y(y_)
	{
	}
	virtual ~DynamicInheritanceCheckerDerived() override = default;
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
	}(static_cast<int*>(c));

	Check(r1 == true);

	auto r2 = [&](const int* x) -> bool
	{
		return x == p;
	}(static_cast<const int*>(c));

	Check(r2 == true);

	// operators
	Check(static_cast<bool>(c) == true);
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
	}(static_cast<int*>(u));

	Check(r1 == true);

	auto r2 = [&](const int* x) -> bool
	{
		return x == p;
	}(static_cast<const int*>(u));

	Check(r2 == true);

	// operators
	Check(static_cast<bool>(u) == true);
	Check((u == u) == true);
	Check((u != u) == false);

	Check((u == p) == true);
	Check((u != p) == false);
	Check((p == u) == true);
	Check((p != u) == false);

	Check((u == nullptr) == false);
	Check((u != nullptr) == true);
	Check((nullptr == u) == false);
	Check((nullptr != u) == true);

	auto u2 = GVE::MakeUnique<int>();

	Check((u == u2) == false);
	Check((u != u2) == true);

	auto e = GVE::UniquePointer<int>(nullptr);

	Check(static_cast<bool>(e) == false);
	Check((e == nullptr) == true);
	Check((e != nullptr) == false);
}
void Reference_UniquePointer_Release()
{
	auto p = new CallChecker();
	auto u = GVE::UniquePointer<CallChecker>(p);

	CallChecker::Reset();

	u.Release();

	Check(
		constructorCallsCounter == 0 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 0 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	delete p;
}

void Reference_StrongPointer_CreationAndDestroying()
{
	// empty
	CallChecker::Reset();
	{
		auto x = GVE::StrongPointer<CallChecker>();

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
		auto x = GVE::StrongPointer<CallChecker>(nullptr);

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
		auto x = GVE::StrongPointer<CallChecker>(new CallChecker());

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
		auto x = GVE::MakeStrong<CallChecker>();

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
	auto p = GVE::MakeStrong<ArgumentsChecker>(5, 10.0f);

	Check(p->x == 5 && p->y == 10.0f);
}
void Reference_StrongPointer_Usage()
{
	// assignment
	CallChecker::Reset();
	{
		GVE::StrongPointer<CallChecker> p1;
		{
			auto p2 = GVE::MakeStrong<CallChecker>();

			p1 = p2;

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

	// nulling
	CallChecker::Reset();
	{
		auto p = GVE::MakeStrong<CallChecker>();

		p = nullptr;

		Check(
			constructorCallsCounter == 1 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 1 &&
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
void Reference_StrongPointer_Move()
{
	// move assignment
	CallChecker::Reset();
	{
		GVE::StrongPointer<CallChecker> p1;
		{
			auto p2 = GVE::MakeStrong<CallChecker>();
			
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

	{
		auto p1 = GVE::MakeStrong<CallChecker>();
		auto p2 = GVE::StrongPointer<CallChecker>(GVE::Move(p1));

		Check(p1.GetValue() == nullptr);

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
void Reference_StrongPointer_Weak()
{
	auto s = GVE::MakeStrong<int>();
	auto w = GVE::WeakPointer<int>(s);
	auto s2 = GVE::MakeStrong(w);

	Check(s.GetValue() == s2.GetValue());
}
void Reference_StrongPointer_Cast()
{
	// static
	auto sd = GVE::MakeStrong<StaticInheritanceCheckerDerived>();

	sd->x = 5;

	auto sb = GVE::StaticCast<StaticInheritanceCheckerBase>(sd);

	Check(sb->x == 5);

	// dynamic
	auto db = GVE::StaticCast<DynamicInheritanceCheckerBase>(GVE::MakeStrong<DynamicInheritanceCheckerDerived>(5, 10));
	auto dd = GVE::DynamicCast<DynamicInheritanceCheckerDerived>(db);

	Check(dd->y == 5);

	db = nullptr;

	// failed dynamic
	auto fdb = GVE::MakeStrong<DynamicInheritanceCheckerBase>();
	auto fdd = GVE::DynamicCast<DynamicInheritanceCheckerDerived>(fdb);

	Check(fdd.GetValue() == nullptr);
}

void Reference_WeakPointer_CreationAndDestroying()
{
	// empty
	CallChecker::Reset();
	{
		auto x = GVE::WeakPointer<CallChecker>();

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
		auto x = GVE::WeakPointer<CallChecker>(nullptr);

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
void Reference_WeakPointer_Usage()
{
	// separate usage
	CallChecker::Reset();
	{
		auto s = GVE::MakeStrong<CallChecker>();
		auto w = GVE::WeakPointer<CallChecker>(s);

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

	// shared nulling (copy)
	CallChecker::Reset();
	{
		auto s = GVE::MakeStrong<CallChecker>();
		auto w = GVE::WeakPointer<CallChecker>(s);

		s = nullptr;

		Check(
			constructorCallsCounter == 1 &&
			copyCallsCounter == 0 &&
			moveCopyCallsCounter == 0 &&
			destructorCallsCounter == 1 &&
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

	// shared nulling (assign)
	CallChecker::Reset();
	{
		GVE::WeakPointer<CallChecker> w;
		{
			auto s = GVE::MakeStrong<CallChecker>();

			w = s;

			Check(
				constructorCallsCounter == 1 &&
				copyCallsCounter == 0 &&
				moveCopyCallsCounter == 0 &&
				destructorCallsCounter == 0 &&
				assignmentCallsCounter == 0 &&
				moveAssignmentCallsCounter == 0
			);

			s = nullptr;

			Check(
				constructorCallsCounter == 1 &&
				copyCallsCounter == 0 &&
				moveCopyCallsCounter == 0 &&
				destructorCallsCounter == 1 &&
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

	Check(
		constructorCallsCounter == 1 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 1 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	// shared destroying (assign)
	CallChecker::Reset();
	{
		GVE::WeakPointer<CallChecker> w;
		{
			auto s = GVE::MakeStrong<CallChecker>();
			
			w = s;

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

	Check(
		constructorCallsCounter == 1 &&
		copyCallsCounter == 0 &&
		moveCopyCallsCounter == 0 &&
		destructorCallsCounter == 1 &&
		assignmentCallsCounter == 0 &&
		moveAssignmentCallsCounter == 0
	);

	// saving and restoring
	CallChecker::Reset();
	{
		auto s = GVE::MakeStrong<CallChecker>();
		auto w = GVE::WeakPointer<CallChecker>(s);
		auto s2 = GVE::StrongPointer<CallChecker>(w);

		Check(s.GetValue() == s2.GetValue());
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


template<class T>
double Stopwatch(T t)
{
	auto t1 = std::clock();

	t();

	auto t2 = std::clock();
	auto d = std::difftime(t2, t1);

	// std::cout << "Time: " << d << std::endl;

	return d;
}


void main2()
{
	std::cout << "sizeof(std::size_t): " << sizeof(std::size_t) << std::endl;
	std::cout << "sizeof(int): " << sizeof(int) << std::endl;
	std::cout << "sizeof(std::shared_ptr<int>): " << sizeof(std::shared_ptr<int>) << std::endl;

	std::system("pause");
}
void main()
{
	// Memory
	Memory_AllocationAndReleasing();
	Memory_Copy();
	Memory_Compare();

	// Move
	Move_Move();
	Move_Forward();

	// Reference
	Reference_ConstantPointer_CreatingAndDestroying();
	Reference_ConstantPointer_Move();
	Reference_ConstantPointer_Selector();
	Reference_ConstantPointer_Value();

	Reference_UniquePointer_CreatingAndDestroying();
	Reference_UniquePointer_Move();
	Reference_UniquePointer_Selector();
	Reference_UniquePointer_Value();
	Reference_UniquePointer_Release();

	Reference_StrongPointer_CreationAndDestroying();
	Reference_StrongPointer_Usage();
	Reference_StrongPointer_Move();
	Reference_StrongPointer_Weak();
	Reference_StrongPointer_Cast();

	Reference_WeakPointer_CreationAndDestroying();
	Reference_WeakPointer_Usage();


	std::system("pause");
}