/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired by TheCherno's Hazel Engine
 * Referenced: https://github.com/TheCherno/Hazel/commit/34df41651fe88041540f20df845a70642359dc17
 */

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <functional>
#include <sstream>
#include <iostream>

namespace Sandbox
{
    // Helper macro for bit shifting
    #define BIT(x) (1 << x)

    // Event type Enums
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // Event category flags (bitwise)
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

    // Base Event class
    class Event
    {
        friend class EventDispatcher;

    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        bool IsHandled() const { return m_Handled; }
        void SetHandled(bool handled) { m_Handled = handled; }

    protected:
        bool m_Handled = false;
    };

    // EventDispatcher for type-safe event handling
    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event)
        : m_Event(event)
        {
        }

        // Dispatch event to a function if types match
        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    // Stream operator for easy logging
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

    // Event class macros
    #define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }
}

#endif
