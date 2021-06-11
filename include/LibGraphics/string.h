#pragma once

#include <memory>

namespace LibGraphics
{

class String
{
public:
    String();
    String(char const *str);
    String(wchar_t const *str);
    ~String();

    char const *c_str() const;
    wchar_t const *c_wstr() const;

protected:
    class Impl;
    friend class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

//LibGraphics::String operator""s(char const *str, std::size_t len);