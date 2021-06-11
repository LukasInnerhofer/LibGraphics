#pragma once

#include <string>

#include "LibGraphics/standard_string.h"

namespace LibGraphics
{

class StandardStringWindows : public StandardString
{
public:
    StandardStringWindows();
    StandardStringWindows(char const *str);
    StandardStringWindows(wchar_t const * str);
    ~StandardStringWindows() override;

    char const *c_str() const noexcept;

protected:
    std::string m_string;
};

class StandardStringWindowsUnicode : public StandardString
{
public:
    StandardStringWindowsUnicode();
    StandardStringWindowsUnicode(char const *str);
    StandardStringWindowsUnicode(wchar_t const *str);
    ~StandardStringWindowsUnicode() override;

    wchar_t const *c_str() const noexcept;

protected:
    std::wstring m_string;
};

#if defined(UNICODE)
using StandardStringImpl = StandardStringWindowsUnicode;
#else
using StandardStringImpl = StandardStringWindows;
#endif // defined(UNICODE)

}