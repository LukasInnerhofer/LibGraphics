#include <chrono>
#include <clocale>
#include <iomanip>
#include <iostream>
#include <system_error>
#include <thread>

#include "lib_graphics/rectangle.h"
#include "lib_graphics/window.h"

int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");

    std::unique_ptr<LibGraphics::Window> window;
    std::u32string const title{U"z\u00DF\u6C34\U0001F34C"};
    try
    {
        window = std::make_unique<LibGraphics::Window>(title);
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    LibGraphics::Rectangle rectangle{ 
        {0.5f, 0.5f}, 
        {{0.5f, 0.0f, 0.0f}}};
    LibGraphics::Window::Event event;
    std::thread timerThread;
    LibGraphics::Color color{LibGraphics::Color::cornflowerBlue};
    bool colorCountUp = true;
    uint64_t time = 0;
    while(window->isOpen())
    {
        timerThread = std::thread{[]() { std::this_thread::sleep_for(std::chrono::milliseconds(16)); }};
        
        if (window->pollEvent(event))
        {
            switch (event.type)
            { 
            case LibGraphics::Window::EventType::Closed:
                window->close();
                break;
            }
        }
        
        window->clear(color);

        if(color.getG() == LibGraphics::Color::max)
        {
            colorCountUp = false;
        }
        if(color.getG() == 0)
        {
            colorCountUp = true;
        }

        color.setG(color.getG() + colorCountUp - !colorCountUp);
        
        rectangle.setPosition({std::sinf((time / 50.0f)), std::cosf(time / 100.0f)});
        window->draw(rectangle);
        
        window->display();
        timerThread.join();
        ++time;
    }
    
    return 0;
}
