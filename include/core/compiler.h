#pragma once

#include <core/platform.h>

#ifdef CORE_PLATFORM_WIN

#define CORE_ALIGNOF(type) __alignof(type)

#define CORE_NO_MOVE_CONSTRUCTOR(Class) Class(Class&&)
#define CORE_NO_MOVE_ASSIGNMENT(Class) Class& operator=(Class&&)
#define CORE_NO_COPY_CONSTRUCTOR(Class) Class(const Class&)
#define CORE_NO_COPY_ASSIGNMENT(Class) Class& operator=(const Class&)

#else //All other platforms (fallback)

#define CORE_ALIGNOF(type) alignof(type)

#define CORE_NO_MOVE_CONSTRUCTOR(Class) Class(Class&&) = delete;
#define CORE_NO_MOVE_ASSIGNMENT(Class) Class& operator=(Class&&) = delete;
#define CORE_NO_COPY_CONSTRUCTOR(Class) Class(const Class&) = delete;
#define CORE_NO_COPY_ASSIGNMENT(Class) Class& operator=(const Class&) = delete;

#endif

#define CORE_NO_MOVE(Class) \
    CORE_NO_MOVE_CONSTRUCTOR(Class); \
    CORE_NO_MOVE_ASSIGNMENT(Class)

#define CORE_NO_COPY(Class) \
    CORE_NO_COPY_CONSTRUCTOR(Class); \
    CORE_NO_COPY_ASSIGNMENT(Class)
