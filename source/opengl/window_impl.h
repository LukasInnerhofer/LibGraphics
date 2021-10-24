#pragma once

#include <memory>
#include <queue>

#include "libgraphics/string.h"
#include "libgraphics/window.h"

#include "opengl.h"

namespace LibGraphics
{

class WindowImpl
{
public:
    WindowImpl(String const &title, NonNullSharedPtr<std::queue<Window::Event>> events);
    ~WindowImpl();

    void pollEvents();
    void display() const;

    NonNullSharedPtr<OpenGl> getOpenGl() const;

private:
    NonNullSharedPtr<std::queue<Window::Event>> m_events;

    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

