#pragma once

#include "LibGraphics/string.h"
#include "standard_string_windows.h"

namespace LibGraphics
{

#if defined(UNICODE)
using StandardStringImpl = StandardStringWindowsUnicode;
#else
using StandardStringImpl = StandardStringWindows;
#endif

String::String() : m_string { std::make_unique<StandardStringImpl>() }
{

}

String::String(char const *str) : m_string { std::make_unique<StandardStringImpl>(str) }
{

}

String::String(wchar_t const *str) : m_string { std::make_unique<StandardStringImpl>(str) }
{

}

StandardString const *String::getString() const
{
    return m_string.get();
}

}