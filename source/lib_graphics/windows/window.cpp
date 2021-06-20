#include <system_error>
#include <Windows.h>
#include <gl/GL.h>

#include "lib_graphics/window.h"
#include "lib_graphics/string.h"

namespace LibGraphics
{

static void throwSystemError(const std::string &message)
{
    throw std::system_error{ 
        std::error_code{static_cast<int>(GetLastError()), std::system_category()}, 
        message};
}

class Window::Impl
{
public:
    // Non static member functions cannot be registered as message handlers
    // because they take a "this" pointer.
    // This function is used to handle all messages of all Window instances
    // by routing them to each respective instance via the lParam parameter.
    static LRESULT CALLBACK messageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Impl* app;
        if (msg == WM_CREATE)
        {
            // Get the implementation pointer from the lParam passed into CreateWindow(Ex)
            app = (Impl*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)app);
        }
        else
        {
            app = (Impl*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
        }
        return app->windowProc(hWnd, msg, wParam, lParam);
    }
    

    LRESULT CALLBACK windowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            m_isOpen = false;
            break;

        default:
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    HWND m_handle;
    bool m_isOpen;
};

Window::Window(String const& title) : m_pImpl{new Impl()}
{
    const HMODULE moduleHandle{GetModuleHandleW(NULL)};
    if (moduleHandle == NULL) 
    {
        throwSystemError("Failed to get module handle");
    }
    
    const std::wstring className = title.toWideString();

    const WNDCLASSW windowClass 
    {  
        CS_OWNDC, // style
        Impl::messageRouter, // wndProc
        NULL, // cbClsExtra
        NULL, // cbWndExtra
        moduleHandle, // associated module handle
        NULL, // icon
        NULL, // cursor
        NULL, // background brush
        NULL, // menu name
        className.c_str()
    };

    const ATOM atom = RegisterClassW(&windowClass);
    if (atom == 0) 
    {
        throwSystemError("Failed to register window class");
    }

    m_pImpl->m_handle = CreateWindowExW(
        0, // extended style
        windowClass.lpszClassName, // class name
        className.c_str(), // window name
        WS_OVERLAPPEDWINDOW, // style
        CW_USEDEFAULT, // x
        CW_USEDEFAULT, // y
        CW_USEDEFAULT, // width
        CW_USEDEFAULT, // height
        NULL, // parent window
        NULL, // menu
        moduleHandle, // associated module handle
        m_pImpl.get() // passed to messageRouter via lParam
    );
    if (m_pImpl->m_handle == NULL) 
    {
        throwSystemError("Failed to create window");
    }

    const PIXELFORMATDESCRIPTOR pixelFormat 
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1, // version
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // flags
        32, // color depth in bits of the frame buffer
        0, 0, 0, 0, 0, 0, 0, 0, // rgba bitplanes
        0, // total number of bitplanes in the acc buffer
        0, 0, 0, 0, // number of rgba bitplanes in the acc buffer 
        24, // number of bits for the depth buffer
        8, // number of bits for the stencil buffer
        0, // number of aux buffers in the frame buffer
        PFD_MAIN_PLANE, // ignored
        0, // number of overlay and underlay planes
        0, // ignored 
        0, // visible mask
        0 // ignored
    };
    
    const HDC deviceContext = GetDC(m_pImpl->m_handle);
    if (deviceContext == NULL) 
    {
        throwSystemError("Failed to get device context");
    }

    const int pixelFormatIndex = ChoosePixelFormat(deviceContext, &pixelFormat);
    if (pixelFormatIndex == 0) 
    {
        throwSystemError("Failed to choose pixel format");
    }

    if (SetPixelFormat(deviceContext, pixelFormatIndex, &pixelFormat) == FALSE)
    {
        throwSystemError("Failed to set pixel format");
    }

    const HGLRC glContext = wglCreateContext(deviceContext);
    if (glContext == NULL)
    {
        throwSystemError("Failed to create OpenGL context");
    }

    if (wglMakeCurrent(deviceContext, glContext) == FALSE)
    {
        throwSystemError("Failed to make OpenGL context current");
    }

    glClearColor(1.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(deviceContext);


    ShowWindow(m_pImpl->m_handle, SW_NORMAL);
    m_pImpl->m_isOpen = true;
}

Window::~Window()
{

}

void Window::pollEvents()
{
    MSG msg;
    if(PeekMessageW(&msg, m_pImpl->m_handle, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

bool Window::isOpen()
{
    return m_pImpl->m_isOpen;
}

}