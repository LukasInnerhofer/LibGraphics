#pragma once

#include <memory>

#include "lib_graphics/string.h"
#include "opengl.h"

namespace LibGraphics
{

class WindowImpl
{
public:
    WindowImpl();
    ~WindowImpl();

    void create(String const &title);
    bool isOpen() const;
    void pollEvents();
    void display() const;

    std::shared_ptr<OpenGl> getOpenGl() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}