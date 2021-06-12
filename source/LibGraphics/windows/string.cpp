#pragma once

#include "LibGraphics/string.h"
#include "standard_string.h"
#include "string_impl.h"

namespace LibGraphics
{

Char const *String::Impl::c_str() const
{
    return m_string.c_str();
}

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

}