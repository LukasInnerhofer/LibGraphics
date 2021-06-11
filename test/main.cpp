#include <clocale>
#include <iostream>
#include <system_error>

#include "LibGraphics/window.h"

int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");

    try
    {
        LibGraphics::Window window { "zß水🍌" };
    }
    catch(const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    for(;;);
    
    return 0;
}