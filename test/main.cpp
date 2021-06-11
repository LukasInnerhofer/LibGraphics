#include <clocale>
#include <iostream>
#include <system_error>

#include "LibGraphics/window.h"

int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");

    std::unique_ptr<LibGraphics::Window> window;
    try
    {
        window = std::make_unique<LibGraphics::Window>("zß水🍌");
    }
    catch(const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    while(window->isOpen())
    {
        window->pollEvents();
    }
    
    return 0;
}