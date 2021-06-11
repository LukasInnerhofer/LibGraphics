#pragma once

#include <memory>

#include "LibGraphics/standard_string.h"

namespace LibGraphics
{

class String
{
public:
    String();
    String(char const *str);
    String(wchar_t const *str);

    StandardString const *getString() const;

private:
    std::unique_ptr<StandardString> m_string;
};

}

//LibGraphics::String operator""s(char const *str, std::size_t len);