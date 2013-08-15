#include <cassert>
#include <iostream>

#include <core/hashing/fnv1a.h>

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
	test_fnv1a_hash();
	return 0;
}
