#include <core/types.h>
#include <core/memory/stack_allocator.h>
#include <core/util/pointer_align.h>

#include <cassert>

core::stack_allocator::stack_allocator(const void* start, const void* end) : _start((uint8_t*)start), _end((uint8_t*)end), _current(_start)
{
}

void* core::stack_allocator::allocate(size_t size, const size_t alignment, size_t alignment_offset)
{
    // Add room for ptr to real start
    size += sizeof(uint32_t);
    alignment_offset += sizeof(uint32_t);

    const uint32_t allocation_offset = static_cast<uint32_t>(_current - _start);

    // Align _current
    _current = (uint8_t*)align_up(_current + alignment_offset, alignment) - alignment_offset;
    
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
        uint32_t* as_uint32_t;
    };

    as_char = _current;

    *as_uint32_t = allocation_offset;
    as_char += sizeof(uint32_t);

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
        uint32_t* as_uint32_t;
    };

    as_void = object;

    as_char -= sizeof(uint32_t);
    const uint32_t allocation_offset = *as_uint32_t;

    _current = _start + allocation_offset;
}
