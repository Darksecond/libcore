#pragma once

#include <cassert>

namespace core
{
    /**
     * stack container with a fixed (compile-time) size.
     */
    template <typename T, size_t N>
    class fixed_stack
    {
        T _array[N];
        T* _current;
    public:
        typedef T* iterator;
        typedef const T* const_iterator;

        inline fixed_stack() : _current(_array)
        {
        }

	//TODO Implement these as memcpy
        fixed_stack(const fixed_stack&) = delete;
        fixed_stack(fixed_stack&&) = delete;

        fixed_stack& operator=(const fixed_stack&) = delete;
        fixed_stack& operator=(fixed_stack&&) = delete;

        /**
         * Number of items on the stack
         */
        inline size_t size() const
        {
            return _current - _array;
        }

        /**
         * Maximum capacity for the stack
         */
        inline size_t capacity() const
        {
            return N;
        }

        /**
         * Push a new item on the stack
         */
        //TODO Add 'T&&' variant
        inline void push(const T& value)
        {
            assert(size() < capacity());
            *_current++ = value;
        }

        /**
         * Pop the top item from the stack
         */
        inline void pop()
        {
            assert(size() > 0);
            --_current;
        }

        /**
         * Get the top most item from the stack
         */
        inline T& top()
        {
            assert(size() > 0);
            return *(_current - 1);
        }

        /**
         * Get the top most item from the stack
         */
        inline const T& top() const
        {
            assert(size() > 0);
            return *(_current - 1);
        }

        /**
         * Clear all items from the stack
         */
        //TODO Rename to 'reset'
        inline void clear()
        {
            _current = _array;
        }

        /**
         * Get an iterator to the beginning of the stack
         */
        inline iterator begin()
        {
            return _array;
        }

        /**
         * Get an iterator to the beginning of the stack
         */
        inline const_iterator begin() const
        {
            return _array;
        }

        /**
         * Get an iterator one item past the last element of the stack.
         */
        inline iterator end()
        {
            return _current;
        }

        /**
         * Get an iterator one item past the last element of the stack.
         */
        inline const_iterator end() const
        {
            return _current;
        }
    };
};
