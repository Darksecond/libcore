#pragma once

#include <core/types.h>
#include <core/logging/log.h>

namespace core
{
    class system_allocator
    {
    public:
        //address+offset should be aligned, NOT address itself
        void* allocate(size_t size, size_t align, size_t offset);
        void free(void* object);
    };
};
