#include <clocale>
#include <iostream>
#include <iomanip>
#include <system_error>

#include "lib_graphics/window.h"

int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");

    std::unique_ptr<LibGraphics::Window> window;
    const std::u32string title{U"z\u00DF\u6C34\U0001F34C"};
    try
    {
        window = std::make_unique<LibGraphics::Window>(title);
    }
    catch(const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    while(window->isOpen())
    {
        window->pollEvents();
        window->clear();
        window->display();
    }
    
    return 0;
}