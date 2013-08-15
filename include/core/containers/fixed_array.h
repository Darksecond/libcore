#pragma once

namespace core
{
    template <typename T, size_t N>
    class fixed_array
    {
        T _array[N];
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        
        inline fixed_array()
        {
            for(size_t i = 0; i < N; ++i)
                _array[i] = T();
        }
        
        inline explicit fixed_array(const T& initial_value)
        {
            for(size_t i = 0; i < N; ++i)
                _array[i] = initial_value;
        }
        
        fixed_array(const fixed_array&) = delete;
        fixed_array(fixed_array&&) = delete;
        
        fixed_array& operator=(const fixed_array&) = delete;
        fixed_array& operator=(fixed_array&&) = delete;
        
        inline T& operator[](size_t i)
        {
            return _array[i];
        }

        inline const T& operator[](size_t i) const
        {
            return _array[i];
        }

        inline size_t capacity() const
        {
            return N;
        }

        inline size_t size() const
        {
            return N;
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
            return _array + N;
        }
        
        inline const_iterator end() const
        {
            return _array + N;
        }
    };
};
