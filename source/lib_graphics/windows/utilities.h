#pragma once

#include <Windows.h>
#include <system_error>

namespace LibGraphics
{

static void throwSystemError(const std::string &message)
{
    throw std::system_error{ 
        std::error_code{static_cast<int>(GetLastError()), std::system_category()}, 
        message};
}

}