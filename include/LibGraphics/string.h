#pragma once

#include <string>

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

    std::wstring toWideString() const;

private:
    std::string m_string;
};

}