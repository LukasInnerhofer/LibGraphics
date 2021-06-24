#pragma once

#include <climits>
#include <cuchar>
#include <memory>

#include "lib_graphics/string.h"

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

String::String(char16_t const *string) : m_string{}
{
    mbstate_t mbstate{};
    char multibyteBuffer[MB_LEN_MAX];
    while(*string != 0)
    {
        const size_t length = c16rtomb(multibyteBuffer, *string, &mbstate);
        m_string.append(reinterpret_cast<char8_t const *>(multibyteBuffer), length);
        ++string;
    }
}

String::String(char32_t const *string) : m_string{}
{
    mbstate_t mbstate{};
    char multibyteBuffer[MB_LEN_MAX];
    while(*string != 0)
    {
        const size_t length = c32rtomb(multibyteBuffer, *string, &mbstate);
        m_string.append(reinterpret_cast<char8_t const *>(multibyteBuffer), length);
        ++string;
    }
}

String::String(std::string const &string) : String(string.c_str())
{

}

String::String(std::u8string const &string) : m_string{string}
{

}

String::String(std::u16string const &string) : String(string.c_str())
{

}

String::String(std::u32string const &string) : String(string.c_str())
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
