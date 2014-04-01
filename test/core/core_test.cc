#include <cassert>
#include <iostream>

#include <core/hashing/fnv1a.h>
#include <core/memory.h>
#include <core/memory/stack_area.h>
#include <core/memory/simple_arena.h>
#include <core/memory/stack_allocator.h>

#include <core/containers/fixed_stack.h>
#include <core/containers/dynamic_stack.h>
#include <core/containers/dynamic_array.h>

#include <core/logging/console_logger.h>
#include <core/compiler.h>

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
	//test_compile_time_const<core::hash_fnv1a("test")> hash;
	//TODO disabled for now due to lack of constexpr support on some platforms
}

void test_fixed_stack()
{
	core::fixed_stack<int, 100> stack;

    assert(stack.capacity() == 100);
    assert(stack.size() == 0);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.size() == 3);
    assert(stack.top() == 3);
    stack.pop();
    assert(stack.size() == 2);
    assert(stack.top() == 2);
    stack.clear();
    assert(stack.size() == 0);
    stack.push(1);
    stack.push(2);
    int count = 0;
    for(core::fixed_stack<int, 100>::iterator it = stack.begin(); it != stack.end(); ++it)
        ++count;
    assert(count == 2);
    //test move version of push
}

void test_stack_alloc()
{
    core::heap_area area(64*1024); //64KiB
    std::cout << "area: " << area.start() << " - " << area.end() << std::endl;

    core::stack_allocator alloc(area.start(), area.end());
    core::simple_arena<core::stack_allocator> arena(&alloc);
}

//TODO Make tests for memory stuff
int main() {
    core::console_logger cl;
    core::log::set_logger(&cl, 0);

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

    core::dynamic_stack<int> stack(&arena, 100);

    core::dynamic_array<int> arry(&arena, 10);
    arry.add(std::move(1));

	test_fnv1a_hash();
	test_fixed_stack();
    test_stack_alloc();
	return 0;
}
