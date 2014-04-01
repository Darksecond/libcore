#pragma once

#include <core/compiler.h>

#include <cassert>

namespace core
{
    /**
     * stack container (FILO) with a fixed (compile-time) size.
     */
    template <typename T, size_t N>
    class fixed_stack
    {
        //TODO Implement these as memcpy
        CORE_NO_COPY(fixed_stack);
        CORE_NO_MOVE(fixed_stack);
        T _array[N];
        T* _current;
    public:
        typedef T* iterator;
        typedef const T* const_iterator;

        inline fixed_stack() : _current(_array)
        {
        }

        inline size_t size() const
        {
            return _current - _array;
        }

        inline size_t capacity() const
        {
            return N;
        }

        //TODO Add 'T&&' variant
        inline void push(const T& value)
        {
            assert(size() < capacity());
            *_current++ = value;
        }

        inline void pop()
        {
            assert(size() > 0);
            --_current;
        }

        inline T& top()
        {
            assert(size() > 0);
            return *(_current - 1);
        }

        inline const T& top() const
        {
            assert(size() > 0);
            return *(_current - 1);
        }

        //TODO Rename to 'reset'
        inline void clear()
        {
            _current = _array;
        }

        inline iterator begin()
        {
            return _array;
        }

        inline const_iterator begin() const
        {
            return _array;
        }

        inline iterator end()
        {
            return _current;
        }

        inline const_iterator end() const
        {
            return _current;
        }
    };
};
