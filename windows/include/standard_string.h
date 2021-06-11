#pragma once

#include <string>

namespace LibGraphics
{

class StandardStringAnsi
{
public:
    StandardStringAnsi();
    StandardStringAnsi(char const *str);
    StandardStringAnsi(wchar_t const *str);

    char const *c_str() const;

private:
    std::string m_string;
};

class StandardStringUnicode
{
public:
    StandardStringUnicode();
    StandardStringUnicode(char const *str);
    StandardStringUnicode(wchar_t const *str);

    wchar_t const *c_str() const;

private:
    std::wstring m_string;
};

#if defined(UNICODE)
using StandardString = StandardStringUnicode;
using Char = wchar_t;
#else
using StandardString = StandardStringAnsi;
using Char = char;
#endif // defined(UNICODE)

}