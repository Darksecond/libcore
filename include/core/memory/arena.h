#pragma once

#include <core/types.h>
#include <core/logging/log.h> // For source_info

namespace core
{
    class arena
    {
    public:
        virtual ~arena() {}
        virtual void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const source_info& info) = 0;
        virtual void free(void* object, const source_info& info) = 0;
    };

    //TODO Rename
    //TODO Move to it's own file
    template <typename Allocator>
    class some_arena
    {
        Allocator allocator;
    public:
        template <typename Area>
        some_arena(const Area& area) : allocator(area.start(), area.end())
        {
        }

        virtual void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const source_info& info)
        {
            return allocator.allocate(size, align, alignment_offset);
        }

        virtual void free(void* object, const source_info& info)
        {
            allocator.free(object);
        }
    };
};
