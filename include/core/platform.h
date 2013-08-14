#pragma once

/**
 * Defines for platform detection.
 * WIN64 needs to be before WIN32 as WIN32 is also on with 64-bit windows (backwards compatibility).
 */

#ifdef __APPLE__
    #define P_PLATFORM apple
    #define P_PLATFORM_APPLE
#elif __linux__
    #define P_PLATFORM linux
    #define P_PLATFORM_LINUX
#elif _WIN64
    #define P_PLATFORM win
    #define P_PLATFORM_SPECIFIC win64
    #define P_PLATFORM_WIN
    #define P_PLATFORM_WIN64
#elif _WIN32
    #define P_PLATFORM win
    #define P_PLATFORM_SPECIFIC win32
    #define P_PLATFORM_WIN
    #define P_PLATFORM_WIN32
#else
    #error Unknown platform
#endif