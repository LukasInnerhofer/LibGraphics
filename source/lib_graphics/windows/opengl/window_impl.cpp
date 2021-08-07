#include <cassert>
#include <Windows.h>

#include "../../opengl/window_impl.h"
#include "../../opengl/opengl.h"
#include "opengl_windows.h"
#include "../utilities.h"

namespace LibGraphics
{

class WindowImpl::Impl
{
public:
    /* Non static member functions cannot be registered as message handlers
     * because they take a "this" pointer.
     * This function is used to handle all messages of all Window instances
     * by routing them to each respective instance via the lParam parameter.
     */
    static LRESULT CALLBACK messageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Impl *app;
        if (msg == WM_CREATE)
        {
            // Get the implementation pointer from the lParam passed into CreateWindow(Ex)
            app = (Impl *)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            assert(app != nullptr);
            SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)app);
        }
        else
        {
            app = (Impl *)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
        }

        return app->windowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK windowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CLOSE:
            assert(hWnd == handle);
            events->push(Window::Event{Window::EventType::Closed});
            break;

        default:
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    std::shared_ptr<OpenGl> openGl{nullptr};
    std::shared_ptr<std::queue<Window::Event>> events{nullptr};
    HWND handle{nullptr};
    HDC deviceContext{nullptr};
    bool isOpen;
};

WindowImpl::WindowImpl(String const &title, std::shared_ptr<std::queue<Window::Event>> events) : 
    m_pImpl{new Impl{}}
{
    m_events = events;
    m_pImpl->events = m_events;

    if (m_pImpl->isOpen)
    {
        throw std::logic_error("Window has already been created");
    }

    const HMODULE moduleHandle{GetModuleHandleW(NULL)};
    if (moduleHandle == NULL) 
    {
        throwSystemError("Failed to get module handle");
    }
    
    const std::wstring className = title.toStdWideString();

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

    m_pImpl->handle = CreateWindowExW(
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
    if (m_pImpl->handle == NULL) 
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
    
    m_pImpl->deviceContext = GetDC(m_pImpl->handle);
    if (m_pImpl->deviceContext == NULL) 
    {
        throwSystemError("Failed to get device context");
    }

    const int pixelFormatIndex = ChoosePixelFormat(m_pImpl->deviceContext, &pixelFormat);
    if (pixelFormatIndex == 0) 
    {
        throwSystemError("Failed to choose pixel format");
    }

    if (SetPixelFormat(m_pImpl->deviceContext, pixelFormatIndex, &pixelFormat) == FALSE)
    {
        throwSystemError("Failed to set pixel format");
    }

    m_pImpl->openGl = std::make_shared<OpenGlWindows>(m_pImpl->deviceContext);

    ShowWindow(m_pImpl->handle, SW_NORMAL);
    m_pImpl->isOpen = true;
}

WindowImpl::~WindowImpl()
{

}

bool WindowImpl::isOpen() const
{
    return m_pImpl->isOpen;
}

void WindowImpl::pollEvents()
{
    MSG msg;
    if(PeekMessageW(&msg, m_pImpl->handle, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

std::shared_ptr<OpenGl> WindowImpl::getOpenGl() const
{
    return m_pImpl->openGl;
}

void WindowImpl::display() const
{
    SwapBuffers(m_pImpl->deviceContext);
}

void WindowImpl::close()
{
    DestroyWindow(m_pImpl->handle);
    ReleaseDC(m_pImpl->handle, m_pImpl->deviceContext);
    m_pImpl->isOpen = false;
}

}
