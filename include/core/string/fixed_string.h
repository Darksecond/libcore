#pragma once

#include <core/types.h>
#include <cassert>
#include <cstdio>
#include <string.h>

namespace core
{
    //TODO add << operator stuff
    template<size_t N>
    class fixed_string
    {
        char _string[N];
        size_t _length;
    public:
        inline fixed_string() : _length(0)
        {
            _string[0] = 0;
        }
        
        explicit fixed_string(const char* const str) : _length(strlen(str))
        {
            assert(_length < N);
            memcpy(_string, str, _length+1); //copy null byte as well
        }
        
        /**
         * Clear the fixed_string.
         * This resets the length.
         * This also makes the first/last byte a null byte.
         */
        void clear()
        {
            _length = 0;
            _string[0] = 0;
        }
        
        inline char& operator[](size_t i)
        {
            assert(i <= _length);
            return _string[i];
        }
        
        inline const char& operator[](size_t i) const
        {
            assert(i <= _length);
            return _string[i];
        }
        
        /**
         * Returns a c_str compatible string for use with external code.
         */
        inline const char* c_str() const
        {
            return _string;
        }
        
        inline size_t length() const
        {
            return _length;
        }
        
        inline size_t capacity() const
        {
            return N;
        }
        
        /**
         * Append a count bytes of the string str to the fixed_string.
         * The current length + the count cannot be greater than the capacity.
         * An assert _will_ be raised if it does not fit.
         * Append will make sure the fixed_string always ends with a null byte.
         */
        inline void append(const char* str, size_t count)
        {
            assert(_length + count < N);
            
            memcpy(_string + _length, str, count);
            _length += count;
            _string[_length] = 0;
        }
        
        /**
         * Append a string to the fixed string.
         * An assert _will_ be raised if it does not fit, so be careful.
         */
        inline void append(const char* str)
        {
            append(str, strlen(str));
        }
        
        /**
         * This will append a formatted string to the fixed_string.
         * It will take in as many arguments as you supply in a printf style.
         * If the end product formatted string does not fit it is clipped.
         * When clipped, it will always end with a null byte so it is still a valid c_str.
         */
        inline void append_fmt(const char* format, ...)
        {
            va_list formatters;
            va_start(formatters, format);
            append_fmt_v(format, formatters);
            va_end(formatters);
        }
        
        /**
         * This will append a formatted string to the fixed_string.
         * It will take in as many arguments as you supply in a printf style.
         * If the end product formatted string does not fit it is clipped.
         * When clipped, it will always end with a null byte so it is still a valid c_str.
         * This is the va_list version of append_fmt
         */
        inline void append_fmt_v(const char* format, va_list formatters)
        {
            const int chars_written = vsnprintf(_string + _length, N - _length, format, formatters);
            if(chars_written < 0)
            {
                _length = N-1;
                _string[_length] = 0; //clip string, append null byte
            }
            else
            {
                _length += chars_written;
            }
        }
    };
}
