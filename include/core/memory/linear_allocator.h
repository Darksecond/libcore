#pragma once

#include <core/types.h>
#include <core/logging/log.h>

namespace core
{
    class linear_allocator
    {
        uint8_t* _start;
        uint8_t* _end;
        uint8_t* _current;
    public:
        linear_allocator(const void* start, const void* end);
        
	/**
	 * \param size amount of data to allocate in bytes
	 * \param align data alignment
	 * \param alignment_offset alignment offset, how many bytes in should the alignment start. can be used for extra preamble data.
	 * \return pointer to allocated memory or nullptr if out of memory
	 * address+offset is aligned, NOT address itself
	 * So if you ask allocate(128, 16, 4) the the return value + 4 will be 16-byte aligned.
	 * The resulting memory block will be 128 bytes big (in total, offset doesn't get added to size)
	 * So the offset only influences where the alignemnt 'starts'.
	 */
        void* allocate(const size_t size, const size_t align, const size_t alignment_offset);
        void free(void* object);
        inline void reset() { _current = _start; }
    };
};
