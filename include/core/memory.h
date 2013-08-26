#pragma once

#include <core/memory/new_delete.h>
#include <core/memory/arena.h>
#include <core/memory/heap_area.h>

//EXAMPLES:
//STL::FalbackAllocator& someArena = fallbackAllocator();
//int* a = CORE_NEW(someArena, int, 3);
//CORE_DELETE(someArena, a);
//int* b = CORE_NEW_ARRAY(someArena, int[3]);
//CORE_DELETE_ARRAY(someArena, b);
/*
 struct alignas(128) bigalign
 {
 uint64_t i[2];
 };
 */
