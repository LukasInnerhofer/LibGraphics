#pragma once

#include <memory>
#include <queue>

#include "lib_graphics/string.h"
#include "lib_graphics/window.h"
#include "opengl.h"

namespace LibGraphics
{

class WindowImpl
{
public:
    WindowImpl(String const &title, std::shared_ptr<std::queue<Window::Event>> events);
    ~WindowImpl();

    bool isOpen() const;
    void pollEvents();
    void display() const;
    void close();

    std::shared_ptr<OpenGl> getOpenGl() const;

private:
    std::shared_ptr<std::queue<Window::Event>> m_events;

    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

