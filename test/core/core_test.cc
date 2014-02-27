#include <cassert>
#include <iostream>

#include <core/hashing/fnv1a.h>
#include <core/memory.h>
#include <core/memory/stack_area.h>

class Test
{
	int t;
public:
	Test()
	{
		static int c;
		t = c++;
		std::cout << "Test: constructor " << t << std::endl;
	}

	~Test()
	{
		std::cout << "Test: destructor " << t << std::endl;
	}
};

template <uint64_t NUM>
struct test_compile_time_const {
	static const uint64_t value = NUM;
};

void test_fnv1a_hash() {
	assert(core::hash_fnv1a("test") == 18007334074686647077ULL);
	//test for real compile time hash
	test_compile_time_const<core::hash_fnv1a("test")> hash;
}

//TODO Make tests for memory stuff
int main() {

	core::heap_area area(64*1024); //64KiB
	core::possessive_arena<core::linear_allocator> arena(area);

	int* b = CORE_NEW(arena, int);
	*b = 4;
	CORE_DELETE(arena, b);

	int* a = CORE_NEW(arena, int, 3);
	*a = 28;
	CORE_DELETE(arena, a);

	Test* t = CORE_NEW(arena, Test);
	CORE_DELETE(arena, t);

	int* c = CORE_NEW_ARRAY(arena, int[3]);
	CORE_DELETE_ARRAY(arena, c);

	Test* u = CORE_NEW_ARRAY(arena, Test[3]);
	CORE_DELETE_ARRAY(arena, u);

	int* d = CORE_NEW_ALIGNED(arena, int, 128);
	*d = 128;
	CORE_DELETE(arena, d);

	test_fnv1a_hash();
	return 0;
}
