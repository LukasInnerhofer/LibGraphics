#include <system_error>
#include <Windows.h>

#include "standard_string.h"
#include "string_impl.h"
#include "LibGraphics/window.h"

namespace LibGraphics
{

class Window::Impl
{
public:
    // Non static member functions cannot be registered as message handlers
    // because they take a "this" pointer.
    // This function is used to handle all messages of all Window instances
    // by routing them to each respective instance via the lParam parameter.
    static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Impl* app;
        if (msg == WM_CREATE)
        {
            // Get the implementation pointer from the lParam passed into CreateWindow(Ex)
            app = (Impl*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)app);
        }
        else
        {
            app = (Impl*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        }
        return app->WindowProc(hWnd, msg, wParam, lParam);
    }
    

    LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            m_isOpen = false;
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    HWND m_handle;
    bool m_isOpen;
};

Window::Window(String const& title) : m_pImpl{new Impl()}
{
    WNDCLASS windowClass{};
    
    const HMODULE moduleHandle{GetModuleHandle(NULL)};
    if (moduleHandle == NULL)
    {
        throw std::system_error { 
            std::error_code{static_cast<int>(GetLastError()), std::system_category()}, 
            "Failed to get module handle" };
    }
    windowClass.hInstance = moduleHandle;
    const auto className = title.m_pImpl->c_str();
    windowClass.lpszClassName = className;
    windowClass.lpfnWndProc = Impl::MessageRouter;

    const ATOM atom = RegisterClass(&windowClass);
    if (atom == 0)
    {
        throw std::system_error { 
            std::error_code{static_cast<int>(GetLastError()), std::system_category()}, 
            "Failed to register window" };
    }

    m_pImpl->m_handle = CreateWindowEx(
        0,
        windowClass.lpszClassName,
        className,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        moduleHandle,
        m_pImpl.get()
    );
    if (m_pImpl->m_handle == NULL)
    {
        throw std::system_error { 
            std::error_code{static_cast<int>(GetLastError()), std::system_category()}, 
            "Failed to create window" };
    }

    ShowWindow(m_pImpl->m_handle, SW_NORMAL);
    m_pImpl->m_isOpen = true;
}

Window::~Window()
{

}

void Window::pollEvents()
{
    MSG msg;
    if(PeekMessage(&msg, m_pImpl->m_handle, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Window::isOpen()
{
    return m_pImpl->m_isOpen;
}

}