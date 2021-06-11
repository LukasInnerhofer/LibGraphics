#pragma once

#include "LibGraphics/string.h"
#include "standard_string.h"

namespace LibGraphics
{

class String::Impl
{
public:
    StandardString m_string;
};

String::String() : m_pImpl{new Impl()}
{
    m_pImpl->m_string = StandardString{};
}

String::String(char const *str) : m_pImpl{new Impl()}
{
    m_pImpl->m_string = StandardString{str};
}

String::String(wchar_t const *str) : m_pImpl{new Impl()}
{
    m_pImpl->m_string = StandardString{str};
}

String::~String()
{
    
}

#if !defined(UNICODE)
char const *String::c_str() const
{
    return m_pImpl->m_string.c_str();
}

#else

wchar_t const *String::c_wstr() const
{
    return m_pImpl->m_string.c_str();
}
#endif

}