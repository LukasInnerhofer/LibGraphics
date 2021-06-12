#pragma once

#include <memory>

#include "LibGraphics/string.h"

namespace LibGraphics
{

String::String() : m_string{}
{

}

String::String(char const *str) : m_string{str}
{

}

String::String(wchar_t const *str)
{
    const size_t len = std::wcstombs(nullptr, str, 0) + 1;
    std::unique_ptr<char[]> dst{new char[len]};
    std::wcstombs(dst.get(), str, len);
    m_string = dst.get();
}

String::~String()
{
    
}

std::wstring String::toWideString() const
{
    const size_t len = std::mbstowcs(nullptr, m_string.c_str(), 0) + 1;
    std::unique_ptr<wchar_t[]> dst{new wchar_t[len]};
    std::mbstowcs(dst.get(), m_string.c_str(), len);
    return dst.get();
}

}