#pragma once

/**
 * Defines for platform detection.
 * WIN64 needs to be before WIN32 as WIN32 is also on with 64-bit windows (backwards compatibility).
 */

#ifdef __APPLE__
    #define CORE_PLATFORM apple
    #define CORE_PLATFORM_APPLE
#elif __linux__
    #define CORE_PLATFORM linux
    #define CORE_PLATFORM_LINUX
#elif _WIN64
    #define CORE_PLATFORM win
    #define CORE_PLATFORM_SPECIFIC win64
    #define CORE_PLATFORM_WIN
    #define CORE_PLATFORM_WIN64
#elif _WIN32
    #define CORE_PLATFORM win
    #define CORE_PLATFORM_SPECIFIC win32
    #define CORE_PLATFORM_WIN
    #define CORE_PLATFORM_WIN32
#else
    #error Unknown platform
#endif
