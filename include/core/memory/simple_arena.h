#pragma once

#include <core/memory/arena.h>

#include <cassert>

namespace core
{
    template <typename Allocator>
    class simple_arena : public arena
    {
        Allocator* allocator;
    public:
        simple_arena(Allocator* alloc) : allocator(alloc)
        {
            assert(alloc != nullptr);
        }
        
        virtual void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const source_info& info)
        {
            return allocator->allocate(size, align, alignment_offset);
        }
        
        virtual void free(void* object, const source_info& info)
        {
            allocator->free(object);
        }
    };
};
