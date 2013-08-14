#include <core/types.h>
#include <core/memory/linear_allocator.h>
#include <core/memory/new_delete.h>

core::linear_allocator::linear_allocator(const void* start, const void* end) : _start((uint8_t*)start), _end((uint8_t*)end), _current(_start)
{
}

void* core::linear_allocator::allocate(const size_t size, const size_t alignment, const size_t alignment_offset)
{
    _current = (uint8_t*)memory_internals::align_forward(_current + alignment_offset, alignment) - alignment_offset;
    void* ptr = _current;
    _current += size;
    if(_current > _end)
    {
        return nullptr;
    }
    
    return ptr;
}

void core::linear_allocator::free(void* object)
{
}
