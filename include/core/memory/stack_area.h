#pragma once

#include <core/compiler.h>
#include <core/types.h>

namespace core
{
    template <int Size>
    class stack_area
    {
        CORE_NO_COPY(stack_area);
        CORE_NO_MOVE(stack_area);

        uint8_t buffer[Size];

    public:
        inline void* start() const { return (void*)buffer; }
        inline size_t size() const { return Size; }
        inline void* end() const { return (uint8_t*)buffer + Size; }
    };
};
