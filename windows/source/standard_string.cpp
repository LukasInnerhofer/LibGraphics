#include <memory>

#include "standard_string.h"

namespace LibGraphics
{

StandardStringAnsi::StandardStringAnsi() : m_string{}
{

}

StandardStringAnsi::StandardStringAnsi(char const *str) : m_string{str}
{

}

StandardStringAnsi::StandardStringAnsi(wchar_t const *str)
{
    const size_t len = std::wcstombs(nullptr, str, 0) + 1;
    std::unique_ptr<char[]> dst{new char[len]};
    std::wcstombs(dst.get(), str, len);
    m_string = std::string{dst.get()};
}

char const *StandardStringAnsi::c_str() const
{ 
    return m_string.c_str();
}

StandardStringUnicode::StandardStringUnicode() : m_string{}
{

}

StandardStringUnicode::StandardStringUnicode(char const *str)
{
    const size_t len = std::mbstowcs(nullptr, str, 0) + 1;
    std::unique_ptr<wchar_t[]> dst{new wchar_t[len]};
    std::mbstowcs(dst.get(), str, len);
    m_string = std::wstring{dst.get()};
}

StandardStringUnicode::StandardStringUnicode(wchar_t const *str) : m_string{str}
{
    
}

wchar_t const *StandardStringUnicode::c_str() const
{ 
    return m_string.c_str();
}

}