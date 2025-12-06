/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

 #ifndef CORE_H
 #define CORE_H

// Platform detection
#ifdef _WIN32
    #define FPS_PLATFORM_WINDOWS
#elif defined(__linux__)
    #define FPS_PLATFORM_LINUX
#elif defined(__APPLE__)
    #define FPS_PLATFORM_MACOS
#endif

// Debug break - cross-platform
#ifdef FPS_PLATFORM_WINDOWS
    #define FPS_DEBUGBREAK() __debugbreak()
#elif defined(FPS_PLATFORM_LINUX) || defined(FPS_PLATFORM_MACOS)
    #include <signal.h>
    #define FPS_DEBUGBREAK() raise(SIGTRAP)
#else
    #define FPS_DEBUGBREAK() // No-op for other platforms
#endif

// Assertions
#ifdef FPS_DEBUG
    #define FPS_ENABLE_ASSERTS
#endif

#ifdef FPS_ENABLE_ASSERTS
    #include "Core/Logger/Logger.h"
    #define FPS_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {}", __VA_ARGS__); FPS_DEBUGBREAK(); } }
    #define FPS_CORE_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {}", __VA_ARGS__); FPS_DEBUGBREAK(); } }
#else
    #define FPS_ASSERT(x, ...)
    #define FPS_CORE_ASSERT(x, ...)
#endif

 #endif