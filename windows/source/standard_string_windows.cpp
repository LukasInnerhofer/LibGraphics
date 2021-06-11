#include <memory>
#include <cstdlib>

#include "standard_string_windows.h"

namespace LibGraphics
{

StandardStringWindows::StandardStringWindows() : m_string {  }
{

}

StandardStringWindows::StandardStringWindows(char const * str) : m_string { str }
{

}

StandardStringWindows::StandardStringWindows(wchar_t const * str)
{
    const size_t len = std::wcstombs(nullptr, str, 0) + 1;
    std::unique_ptr<char[]> dst { new char[len] };
    std::wcstombs(dst.get(), str, len);
    m_string = std::string { dst.get() };
}

StandardStringWindows::~StandardStringWindows()
{
    
}

char const *StandardStringWindows::c_str() const noexcept
{
    return m_string.c_str();
}

StandardStringWindowsUnicode::StandardStringWindowsUnicode() : m_string {  }
{

}

StandardStringWindowsUnicode::StandardStringWindowsUnicode(char const *str)
{
    const size_t len = std::mbstowcs(nullptr, str, 0) + 1;
    std::unique_ptr<wchar_t[]> dst { new wchar_t[len] };
    std::mbstowcs(dst.get(), str, len);
    m_string = std::wstring { dst.get() };
}

StandardStringWindowsUnicode::StandardStringWindowsUnicode(wchar_t const *str) : m_string { str }
{

}

StandardStringWindowsUnicode::~StandardStringWindowsUnicode()
{
    
}

wchar_t const *StandardStringWindowsUnicode::c_str() const noexcept
{
    return m_string.c_str();
}

}