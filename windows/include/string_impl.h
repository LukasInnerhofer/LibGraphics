#pragma once

#include "LibGraphics/string.h"
#include "standard_string.h"

namespace LibGraphics
{

class String::Impl
{
public:
    Char const *c_str() const;

    StandardString m_string;
};

}