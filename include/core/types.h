#pragma once

#include <cstddef>
#include <stdint.h>

namespace core
{
    template<class T>
    struct type_and_count
    {
        typedef T Type;
    };
    
    template<class T, size_t N>
    struct type_and_count<T[N]>
    {
        typedef T Type;
        static const size_t Count = N;
    };
    
    template<bool I>
    struct bool_to_type
    {
    };
};
