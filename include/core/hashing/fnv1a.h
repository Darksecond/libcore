#pragma once

#include <core/types.h>

namespace core
{
	//code from: http://seanmiddleditch.com/journal/2011/05/compile-time-string-hashing-in-c0x/
	// FNV-1a constants
	static constexpr uint64_t fnv1a_basis = 14695981039346656037ULL;
	static constexpr uint64_t fnv1a_prime = 1099511628211ULL;

	// compile-time hash helper function
	constexpr uint64_t hash_one_fnv1a(char c, const char* remain, uint64_t value)
	{
		return c == 0 ? value : hash_one_fnv1a(remain[0], remain + 1, (value ^ c) * fnv1a_prime);
	}

	// compile-time hash
	constexpr uint64_t hash_fnv1a(const char* str)
	{
		return hash_one_fnv1a(str[0], str + 1, fnv1a_basis);
	}
}
