#include <system_error>
#include <Windows.h>

#include "standard_string_windows.h"
#include "LibGraphics/window.h"

namespace LibGraphics
{

class Window::Impl
{
public:
    HWND m_handle;
};

static LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

Window::Window(String const& title) : m_pImpl { new Impl() }
{
    WNDCLASS windowClass { };
    
    const HMODULE moduleHandle { GetModuleHandle(NULL) };
    if (moduleHandle == NULL)
    {
        throw std::system_error { 
            std::error_code { static_cast<int>(GetLastError()), std::system_category() }, 
            "Failed to get module handle" };
    }
    windowClass.hInstance = moduleHandle;
    windowClass.lpszClassName = static_cast<StandardStringImpl const*>(title.getString())->c_str();
    windowClass.lpfnWndProc = WindowProc;

    const ATOM atom = RegisterClass(&windowClass);
    if (atom == 0)
    {
        throw std::system_error { 
            std::error_code { static_cast<int>(GetLastError()), std::system_category() }, 
            "Failed to register window" };
    }

    m_pImpl->m_handle = CreateWindowEx(
        0,
        windowClass.lpszClassName,
        static_cast<StandardStringImpl const*>(title.getString())->c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        moduleHandle,
        NULL
    );
    if (m_pImpl->m_handle == NULL)
    {
        throw std::system_error { 
            std::error_code { static_cast<int>(GetLastError()), std::system_category() }, 
            "Failed to create window" };
    }

    ShowWindow(m_pImpl->m_handle, SW_NORMAL);
}

Window::~Window()
{
    
}

}