#pragma once

#include <core/types.h>

namespace core
{

	inline void* align_up(void* p, size_t align)
	{
		uintptr_t pi = uintptr_t(p);
		const size_t mod = pi % align;
		if (mod)
			pi += (align - mod);
		return (void*)pi;
	}

	inline void* align_down(void* p, size_t align)
	{
		uintptr_t pi = uintptr_t(p);
		const size_t mod = pi % align;
		if (mod)
			pi -= mod;
		return (void*)pi;
	}

}
