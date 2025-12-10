/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired by TheCherno's Hazel Engine
 * Referenced: https://github.com/TheCherno/Hazel/commit/6815f07cd23eb5cd55cfe6fccaec5aefdc8169e8
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "Events/Event.h"
#include <string>
#include <functional>
#include <memory>

namespace Sandbox
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Sandbox Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
        : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        using QueueEventFn = std::function<void(std::unique_ptr<Event>)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetQueueEventCallback(const QueueEventFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProps& props = WindowProps());
    };
}

#endif
