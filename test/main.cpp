#include <iostream>
#include <system_error>

#include "window.h"

int main()
{
    try
    {
        LibGraphics::Window window { "TestWindow" };
    }
    catch(const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}