#include <cassert>
#include <iostream>

#include <core/hashing/fnv1a.h>
#include <core/memory.h>

//TODO Move to it's own file
template <int Size>
class stack_area
{
	uint8_t buffer[Size];
public:
        inline void* start() const { return (void*)buffer; }
        inline size_t size() const { return Size; }
        inline void* end() const { return (uint8_t*)buffer + Size; }
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

int main() {
	core::heap_area area(64*1024); //64KiB
	stack_area<64*1024> sa;
	core::some_arena<core::linear_allocator> arena(sa);
	int* a = CORE_NEW(arena, int, 3);
	CORE_DELETE(arena, a);
	test_fnv1a_hash();
	return 0;
}
