#pragma once

#include <core/types.h>
#include <core/logging/log.h>

namespace core
{
    class stack_allocator
    {
        uint8_t* _start;
        uint8_t* _end;
        uint8_t* _current;
    public:
        stack_allocator(const void* start, const void* end);

        void* allocate(const size_t size, const size_t align, const size_t alignment_offset);
        void free(void* object);
    };
}
