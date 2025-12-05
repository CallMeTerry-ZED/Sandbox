/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Logger/Logger.h"

int main()
{
    FPS::Logger logger; // automatically Init() in constructor

    LOG_INFO("Application started");
    LOG_DEBUG("Debug information: {}", 42);
    LOG_WARN("This is a test warning");

    // Automatically Shutdown() when 'logger' goes out of scope
    return 0;
}
