#pragma once

#include <core/compiler.h>
#include <core/memory/arena.h>
#include <core/memory/new_delete.h>

#include <cassert>

namespace core
{
    template <typename T>
    class dynamic_stack
    {
        //TODO Implement these
        CORE_NO_COPY(dynamic_stack);
        CORE_NO_MOVE(dynamic_stack);

        arena* _arena;
        T* _start; //Start of array
        T* _end; //One after last element of array
        T* _current; //Next empty element
    public:
        typedef T* iterator;
        typedef const T* const_iterator;

        dynamic_stack(arena* a, const size_t capacity) : _arena(a), _start(nullptr), _end(nullptr), _current(nullptr)
        {
            assert(a != nullptr);
            
            reserve(capacity);
        }

        ~dynamic_stack()
        {
            free();
        }

        void reserve(const size_t capacity)
        {
            assert(_start == nullptr);

            _start = static_cast<T*>(_arena->allocate(sizeof(T)*capacity, CORE_ALIGNOF(T), 0, CORE_SOURCEINFO));
            _current = _start;
            _end = _start + capacity;
        }

        void free()
        {
            clear();

            if(_start)
                _arena->free(_start, CORE_SOURCEINFO);

            _start = nullptr;
            _end = nullptr;
            _current = nullptr;
        }

        size_t size() const
        {
            return _current - _start;
        }

        size_t capacity() const
        {
            return _end - _start;
        }

        void push(const T& value)
        {
            assert(size() < capacity());
            memory_internals::construct<T>(_current, value);
            ++_current;
        }

        void push(T&& value)
        {
            assert(size() < capacity());
            memory_internals::construct<T>(_current, std::move(value));
            ++_current;
        }

        void pop()
        {
            assert(size() > 0);

            --_current;
            memory_internals::destruct(_current);
        }

        T& top()
        {
            assert(size() > 0);
            return *(_current - 1);
        }

        const T& top() const
        {
            assert(size() > 0);
            return *(_current - 1);
        }

        void clear()
        {
            for(size_t i = 0; i < size(); ++i)
                memory_internals::destruct(_start + i);
            _current = _start;
        }

        iterator begin()
        {
            return _start;
        }

        const_iterator begin() const
        {
            return _start;
        }

        iterator end()
        {
            return _current;
        }

        const_iterator end() const
        {
            return _current;
        }
        
        bool empty() const
        {
            return _start == _current;
        }
    };
};
