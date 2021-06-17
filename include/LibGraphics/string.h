#pragma once

#include <string>

namespace LibGraphics
{

class Window;

class String
{
public:
    String();
    String(char const *string);
    String(char8_t const *string);
    String(std::string const &string);
    String(std::u8string const &string);
    ~String();

    std::wstring toWideString() const;

private:
    std::u8string m_string;
};

}