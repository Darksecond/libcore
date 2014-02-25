#pragma once

#include <core/types.h>
#include <core/hashing/fnv1a.h>

namespace core
{
    class string_hash
    {
    public:
        typedef uint64_t Type;
        
        constexpr string_hash(const char* str) : hash(hash_fnv1a(str))
        {
        }
        
        explicit constexpr string_hash(Type h) : hash(h)
        {
        }
        
        constexpr inline operator Type() const
        {
            return hash;
        }
        
    private:
        const Type hash;
    };
};
