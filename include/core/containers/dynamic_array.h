#pragma once

#include <core/memory/arena.h>
#include <core/memory/new_delete.h>

#include <cassert>
#include <utility>

namespace core
{
    template<typename T>
    class dynamic_array
    {
        arena* _arena;
        T* _start;
        T* _end; //one after end of allocated memory
        T* _used_end; //one after end of used items
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        
        explicit inline dynamic_array(arena* a) : _arena(a), _start(nullptr), _end(nullptr), _used_end(nullptr)
        {
            assert(a != nullptr);
        }
        
        inline dynamic_array(arena* a, const size_t initial_capacity) : _arena(a), _start(nullptr), _end(nullptr), _used_end(nullptr)
        {
            assert(a != nullptr);
            
            reserve(initial_capacity);
        }
        
        //TODO Implement with memcpy
        dynamic_array(dynamic_array&) = delete;
        dynamic_array& operator=(dynamic_array&) = delete;
        
        dynamic_array(dynamic_array&& other) : _start(other._start), _end(other._end), _used_end(other._used_end)
        {
            other._start = nullptr;
            other._end = nullptr;
            other._used_end = nullptr;
        }
        
        dynamic_array& operator=(dynamic_array&& other)
        {
            free();
            
            _start = other._start;
            _end = other._end;
            _used_end = other._used_end;
            
            other._start = nullptr;
            other._end = nullptr;
            other._used_end = nullptr;
        }
        
        ~dynamic_array()
        {
            free();
        }
        
        void reserve(size_t new_capacity)
        {
            assert(_start == nullptr); //dynamic_array has not been free-ed yet.
            
            _start = static_cast<T*>(_arena->allocate(sizeof(T)*new_capacity, alignof(T), 0, CORE_SOURCEINFO));
            _end = _start + new_capacity;
            _used_end = _start;
        }
        
        size_t size()
        {
            return _used_end - _start;
        }
        
        size_t capacity()
        {
            return _end - _start;
        }
        
        void clear()
        {
            for(size_t i = 0; i < size(); ++i)
                memory_internals::destruct(_start + i);
            
            _used_end = _start;
        }
        
        void free()
        {
            clear();
            
            if(_start)
                _arena->free(_start, CORE_SOURCEINFO);
            
            _start = nullptr;
            _end = nullptr;
            _used_end = nullptr;
        }
        
        T& operator[](size_t i)
        {
            assert(_start + i < _used_end); //must be in range
            
            return _start[i];
        }
        
        const T& operator[](size_t i) const
        {
            assert(_start + i < _used_end); //must be in range
            
            return _start[i];
        }
        
        void add(const T& item)
        {
            assert(_start != nullptr); //cannot be free-ed
            assert(_end != _used_end); //cannot be full
            
            memory_internals::construct<T>(_used_end, item);
            ++_used_end;
        }
        
        void add(T&& item)
        {
            assert(_start != nullptr); //cannot be free-ed
            assert(_end != _used_end); //cannot be full

            memory_internals::construct<T>(_used_end, std::move(item));
            ++_used_end;
        }
        
        T* data()
        {
            return _start;
        }
        
        const T* data() const
        {
            return _start;
        }
        
        void pop_back()
        {
            assert(size() > 0);

            --_used_end;
            memory_internals::destruct(_used_end);
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
            return _used_end;
        }
        
        const_iterator end() const
        {
            return _used_end;
        }
        
        bool empty() const
        {
            return _start == _used_end;
        }
        
        /**
         * Erases element i by moving the last element into it's place.
         * This will _not_ keep the array order!
         */
        inline void erase(size_t i)
        {
            assert(_start + i < _used_end); //cannot delete outside of used range
            
            memory_internals::destruct(_start + i);
            
            --_used_end;
            const bool last = (_start +i == _used_end);
            
            if(!empty() && !last)
            {
                memory_internals::construct<T>(_start + i, std::move(*_used_end));
                
                memory_internals::destruct(_used_end);
            }
        }
        
        void erase(iterator it)
        {
            erase(it - _start);
        }
        
        void erase(const_iterator it)
        {
            erase(it - _start);
        }
        
        void erase(const T& element)
        {
            for(size_t i = 0; i < size(); ++i)
            {
                if(_start[i] == element)
                {
                    erase(i);
                    return;
                }
            }
        }
    };
};
