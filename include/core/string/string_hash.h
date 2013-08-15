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
#ifdef DEBUG
        , original_string(str)
#endif
        {
        }
        
        explicit constexpr string_hash(Type h) : hash(h)
#ifdef DEBUG
        , original_string(nullptr)
#endif
        {
        }
        
        constexpr inline operator Type() const
        {
            return hash;
        }
        
#ifdef DEBUG
        constexpr inline const char* string()
        {
            return original_string;
        }
#endif
        
    private:
        const Type hash;
#if DEBUG
        const char* const original_string;
#endif
    };
};
