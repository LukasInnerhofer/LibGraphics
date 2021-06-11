#pragma once

#include <memory>

namespace LibGraphics
{

class Window;

class String
{
public:
    String();
    String(char const *str);
    String(wchar_t const *str);
    ~String();

private:
    friend class Window;
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}