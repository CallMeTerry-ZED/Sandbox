/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired by TheCherno's Hazel Engine
 * Referenced: https://github.com/TheCherno/Hazel/commit/34df41651fe88041540f20df845a70642359dc17
 */

#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Events/Event.h"
#include <sstream>

namespace FPS
{
    // Base Key Event
    class KeyEvent : public Event
    {
    public:
        int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keycode)
        : m_KeyCode(keycode)
        {
        }

        int m_KeyCode;
    };

    // Key Pressed Event
    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), m_RepeatCount(repeatCount)
        {
        }

        int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_RepeatCount;
    };

    // Key Released Event
    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode)
        : KeyEvent(keycode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    // Key Typed Event (for text input)
    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode)
        : KeyEvent(keycode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif
