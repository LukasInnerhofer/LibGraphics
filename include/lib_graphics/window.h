#pragma once

#include "lib_graphics/color.h"
#include "lib_graphics/string.h"

namespace LibGraphics
{

class Window
{
public:
    enum class EventType { Closed };
    typedef struct EventTag
    {
        EventType type;

        EventTag() : type{EventType::Closed}
        {

        }

        EventTag(EventType type) : type{type}
        {

        }
    } Event;

    Window(String const &title);
    ~Window();

    bool isOpen() const;
    bool pollEvent(Event &event);
    void clear(Color const &color);
    void display() const;
    void close();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

