#pragma once

#include <memory>

#include "lib_graphics/color.h"
#include "lib_graphics/string.h"

namespace LibGraphics
{

class Window
{
public:
    Window(String const &title);
    ~Window();

    bool isOpen() const;
    void pollEvents();
    void clear(Color const &color);
    void display() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}