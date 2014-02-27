#include <core/types.h>
#include <core/memory/linear_allocator.h>
#include <core/util/pointer_align.h>

core::linear_allocator::linear_allocator(const void* start, const void* end) : _start((uint8_t*)start), _end((uint8_t*)end), _current(_start)
{
}

void* core::linear_allocator::allocate(const size_t size, const size_t alignment, const size_t alignment_offset)
{
    _current = (uint8_t*)align_up(_current + alignment_offset, alignment) - alignment_offset;
    void* ptr = _current;
    _current += size;
    if(_current >= _end)
    {
	// Out of memory
        return nullptr;
    }
    
    return ptr;
}

void core::linear_allocator::free(void* object)
{
}
