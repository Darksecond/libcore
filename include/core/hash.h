#pragma once

#include <core/types.h>

namespace core
{
    //TODO into 'fnv1a.h' file in 'Hashes' folder
    //code from: http://seanmiddleditch.com/journal/2011/05/compile-time-string-hashing-in-c0x/
    namespace hash
    {
        // FNV-1a constants
        static constexpr uint64_t basis = 14695981039346656037ULL;
        static constexpr uint64_t prime = 1099511628211ULL;
        
        // compile-time hash helper function
        constexpr uint64_t hash_one_fnv1a(char c, const char* remain, uint64_t value)
        {
            return c == 0 ? value : hash_one_fnv1a(remain[0], remain + 1, (value ^ c) * prime);
        }
        
        // compile-time hash
        constexpr uint64_t hash_fnv1a(const char* str)
        {
            return hash_one_fnv1a(str[0], str + 1, basis);
        }
    };
};
