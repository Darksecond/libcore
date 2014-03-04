#include <core/types.h>
#include <core/memory/stack_allocator.h>
#include <core/util/pointer_align.h>

#include <cassert>

core::stack_allocator::stack_allocator(const void* start, const void* end) : _start((uint8_t*)start), _end((uint8_t*)end), _current(_start)
{
}

void* core::stack_allocator::allocate(size_t size, const size_t alignment, size_t alignment_offset)
{
    assert(alignment > 0 && alignment < 65536);

    // Add room for ptr to real start
    size += sizeof(uint16_t);
    alignment_offset += sizeof(uint16_t);

    const uint8_t* prev = _current;

    // Align _current
    _current = (uint8_t*)align_up(_current + alignment_offset, alignment) - alignment_offset;

    //this is the amount of bytes used for alignment.
    const uint16_t allocation_offset = static_cast<uint16_t>(_current - prev);

    // Check for OOM conditions
    if(_current + size > _end)
    {
        // Out of memory
        return nullptr;
    }

    union
    {
        void* as_void;
        uint8_t* as_char;
        uint16_t* as_uint16_t;
    };

    as_char = _current;

    *as_uint16_t = allocation_offset;
    as_char += sizeof(uint16_t);

    void* ptr = as_void;
    _current += size;
    return ptr;
}

void core::stack_allocator::free(void* object)
{
    assert(object);

    union
    {
        void* as_void;
        uint8_t* as_char;
        uint16_t* as_uint16_t;
    };

    as_void = object;

    as_char -= sizeof(uint16_t);
    const uint16_t allocation_offset = *as_uint16_t;

    _current = as_char - allocation_offset;
}
