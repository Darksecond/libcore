#include <cassert>
#include <iostream>

#include <core/hashing/fnv1a.h>
#include <core/memory.h>
#include <core/memory/stack_area.h>

template <uint64_t NUM>
struct test_compile_time_const {
	static const uint64_t value = NUM;
};

void test_fnv1a_hash() {
	assert(core::hash_fnv1a("test") == 18007334074686647077ULL);
	//test for real compile time hash
	test_compile_time_const<core::hash_fnv1a("test")> hash;
}

int main() {
	core::heap_area area(64*1024); //64KiB
	int x;
	core::stack_area<64*1024> sa;
	int y;
	core::some_arena<core::linear_allocator> arena(sa);
	int* a = CORE_NEW(arena, int, 3);
	std::cout << &x << std::endl;
	std::cout << sa.start() << std::endl;
	std::cout << &y << std::endl;
	CORE_DELETE(arena, a);
	test_fnv1a_hash();
	return 0;
}
