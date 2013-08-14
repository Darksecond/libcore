#pragma once

#include <core/types.h>

namespace core
{
    class heap_area
    {
        void* _start;
        size_t _size;
    public:
        explicit heap_area(size_t s);
        ~heap_area();
        
        heap_area(heap_area& other) = delete;
        heap_area& operator=(heap_area& other) = delete;
        
        heap_area(heap_area&& other);
        heap_area& operator=(heap_area&& other);
        
        void reserve(size_t new_size);
        void release();
        
        inline void* start() { return _start; }
        inline void* end() { return (uint8_t*)_start + _size - 1; }
        inline size_t size() { return _size; }
    };
};
