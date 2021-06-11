#pragma once

#include "LibGraphics/string.h"

namespace LibGraphics
{

class Window
{
public:
    Window(String const &title);
    ~Window();

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}