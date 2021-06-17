#pragma once

#include <cuchar>
#include <memory>
#include <iomanip>
#include <iostream>

#include "LibGraphics/string.h"

namespace LibGraphics
{

String::String() : m_string{}
{

}

String::String(char const *string) : m_string{reinterpret_cast<char8_t const *>(string)}
{

}

String::String(char8_t const *string) : m_string{string}
{

}

String::String(std::string const &string) : String(string.c_str())
{

}

String::String(std::u8string const &string) : m_string{string}
{

}

String::~String()
{
    
}

std::wstring String::toWideString() const
{
    const size_t length{std::mbstowcs(
        nullptr, 
        reinterpret_cast<char const *>(m_string.c_str()), 
        0) + 1};
    std::unique_ptr<wchar_t[]> destination{new wchar_t[length]};
    std::mbstowcs(
        destination.get(), 
        reinterpret_cast<char const *>(m_string.c_str()), 
        length);
    return destination.get();
}

}