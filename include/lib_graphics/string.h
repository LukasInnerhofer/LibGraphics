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
    String(char16_t const *string);
    String(char32_t const *string);
    String(std::string const &string);
    String(std::u8string const &string);
    String(std::u16string const &string);
    String(std::u32string const &string);
    ~String();
  
    std::string toStdString() const;
    std::wstring toStdWideString() const;

private:
    std::u8string m_string;
};

}

