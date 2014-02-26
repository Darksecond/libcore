#pragma once

#include <core/types.h>

namespace core
{
    template <int Size>
    class stack_area
    {
        uint8_t buffer[Size];

    public:
        stack_area() = default;

        stack_area(const stack_area&) = delete;
        stack_area(stack_area&&) = delete;

        stack_area& operator=(const stack_area&) = delete;
        stack_area& operator=(stack_area&&) = delete;

        inline void* start() const { return (void*)buffer; }
        inline size_t size() const { return Size; }
        inline void* end() const { return (uint8_t*)buffer + Size; }
    };
};
