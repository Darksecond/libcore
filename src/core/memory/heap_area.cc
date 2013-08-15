#include <core/memory/heap_area.h>

#include <cstdlib>

core::heap_area::heap_area(size_t s) : _start(nullptr), _size(0)
{
    reserve(s);
}

core::heap_area::~heap_area()
{
    release();
}

core::heap_area::heap_area(core::heap_area&& other) : _start(other.start()), _size(other.size())
{
    other._start = nullptr;
    other._size = 0;
}

core::heap_area& core::heap_area::operator=(core::heap_area&& other)
{
    release();
    
    _start = other.start();
    _size = other.size();
    
    other._start = nullptr;
    other._size = 0;
    
    return *this;
}

void core::heap_area::reserve(size_t new_size)
{
    if(_size == 0)
    {
        _start = ::malloc(new_size);
        _size = new_size;
    }
}

void core::heap_area::release()
{
    if(_size != 0)
    {
        ::free(_start);
        _start = nullptr;
        _size = 0;
    }
}
