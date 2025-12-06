/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */


#ifndef LINUX_WINDOW_H
#define LINUX_WINDOW_H

#include "Core/Window/Window.h"

#include <glad.h>
#include <GLFW/glfw3.h>

namespace FPS
{
    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override
        {
            m_Data.EventCallback = callback;
        }
        inline void SetQueueEventCallback(const QueueEventFn& callback) override
        {
            m_Data.QueueEventCallback = callback;
        }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
            QueueEventFn QueueEventCallback = [](std::unique_ptr<Event>) {};
        };

        WindowData m_Data;
        static bool s_GLFWInitialized;
    };
}

#endif