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

    //TODO Move to it's own file
    /**
     * This arena only works for allocators that have a constructor
     * in the form of allocator(void* start, void* end).
     * That's why it won't work for the system allocator.
     *
     * No access is provided to the allocator itself, for simplicity
     * and to make clear this arena has limited usability.
     */
    template <typename Allocator>
    class possessive_arena : public arena
    {
        Allocator allocator;
    public:
        template <typename Area>
        possessive_arena(const Area& area) : allocator(area.start(), area.end())
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
