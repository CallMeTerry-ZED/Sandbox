/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Logger/Logger.h"

namespace FPS
{
    std::shared_ptr<spdlog::logger> Logger::s_logger = nullptr;

    Logger::Logger()
    {
        Init();
    }

    Logger::~Logger()
    {
        Shutdown();
        s_logger = nullptr;
    }

    void Logger::Init()
    {
        if (!s_logger)
        {
            s_logger = spdlog::stdout_color_mt("FPS");
            s_logger->set_level(spdlog::level::trace);
            s_logger->set_pattern("[%H:%M:%S] [%^%l%$] %v");
        }
    }

    void Logger::Shutdown()
    {
        if (s_logger)
        {
            s_logger->flush();
            spdlog::drop("FPS"); // Remove logger from spdlog registry
            s_logger = nullptr;
        }
    }
}
