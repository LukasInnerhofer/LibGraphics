#pragma once

#include <memory>

#include "LibGraphics/string.h"

namespace LibGraphics
{

class Window
{
public:
    Window(String const &title);
    ~Window();

    void pollEvents();
    bool isOpen();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}