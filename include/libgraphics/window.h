#pragma once

#include "libgraphics/color.h"
#include "libgraphics/drawable.h"
#include "libgraphics/string.h"
#include "libgraphics/vertex_buffer.h"

namespace LibGraphics
{

class Drawable;
class VertexBuffer;

class Window
{
public:
    enum class EventType { Closed };
    typedef struct EventTag
    {
        EventType type;

        EventTag(EventType type = EventType::Closed) : type{type}
        {

        }
    } Event;

    Window(String const &title);
    ~Window();
    
    bool pollEvent(Event &event);
    void clear(Color const &color);
    void draw(Drawable &drawable);
    void draw(VertexBuffer const &vertexBuffer);
    void display() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

