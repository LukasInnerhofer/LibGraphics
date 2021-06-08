#include <memory>
#include <system_error>
#include <Windows.h>

#include "window.h"

namespace LibGraphics
{

static LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(std::string const& title)
{
    WNDCLASS windowClass { };
    
    const HMODULE moduleHandle { GetModuleHandle(NULL) };
    if(moduleHandle == NULL)
    {
        throw std::system_error { 
            std::error_code { static_cast<int>(GetLastError()), std::system_category() }, 
            "Failed to get module handle" };
    }
    windowClass.hInstance = moduleHandle;
    windowClass.lpszClassName = title.c_str();
    windowClass.lpfnWndProc = WindowProc;

    const ATOM atom = RegisterClass(&windowClass);
    if(atom == 0)
    {
        throw std::system_error { 
            std::error_code { static_cast<int>(GetLastError()), std::system_category() }, 
            "Failed to register window" };
    }

    const HWND windowHandle { CreateWindowEx(
        0,
        windowClass.lpszClassName,
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        moduleHandle,
        NULL
    ) };
    if(windowHandle == NULL)
    {
        throw std::system_error { 
            std::error_code { static_cast<int>(GetLastError()), std::system_category() }, 
            "Failed to create window" };
    }

    ShowWindow(windowHandle, SW_NORMAL);
}

}