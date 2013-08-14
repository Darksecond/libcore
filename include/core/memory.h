#pragma once

#include <core/memory/new_delete.h>
#include <core/memory/arena.h>
#include <core/memory/heap_area.h>

//EXAMPLES:
//STL::FalbackAllocator& someArena = fallbackAllocator();
//int* a = P_NEW(someArena, int, 3);
//P_DELETE(someArena, a);
//int* b = P_NEW_ARRAY(someArena, int[3]);
//P_DELETE_ARRAY(someArena, b);
/*
 struct alignas(128) bigalign
 {
 uint64_t i[2];
 };
 */

namespace core
{
    //TODO add 'arena' class-range after all
    //TODO write more allocators (pool, linear, stack)
    //TODO write a macro to re-size a size to include the P_NEW_ARRAY overhead
};
