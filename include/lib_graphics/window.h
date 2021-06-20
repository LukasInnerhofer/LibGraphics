#pragma once

#include <memory>

#include "lib_graphics/string.h"

namespace LibGraphics
{

class Window
{
public:
    Window(String const &title);
    ~Window();

    bool isOpen();
    void pollEvents();
    void clear();
    void display();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}