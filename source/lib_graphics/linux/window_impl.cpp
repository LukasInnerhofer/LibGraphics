#include <cassert>
#include <stdexcept>
#include <X11/Xlib.h>

#include "../window_impl.h"
#include "../opengl.h"
#include "opengl_linux.h"

namespace LibGraphics
{

class WindowImpl::Impl
{
public:
    Display *display;
    std::shared_ptr<OpenGl> openGl{nullptr};
    bool isOpen;
};

WindowImpl::WindowImpl() : m_pImpl{new Impl{}}
{
    
}

WindowImpl::~WindowImpl()
{

}

void WindowImpl::create(String const &title)
{
    if (m_pImpl->isOpen)
    {
        throw std::logic_error("Window has already been created");
    }

    // NULL => Use DISPLAY environment variable
    m_pImpl->display = XOpenDisplay(NULL);
    if (m_pImpl->display == NULL)
    {
	throw std::runtime_error("Failed to connect to X server.");
    }

    const int screen{DefaultScreen(m_pImpl->display)};
    const ::Window window = XCreateSimpleWindow(
        m_pImpl->display,
	RootWindow(m_pImpl->display, screen),
	10, 10,
	100, 100,
	1,
	BlackPixel(m_pImpl->display, screen), WhitePixel(m_pImpl->display, screen));

    XStoreName(m_pImpl->display, window, title.toStdString().c_str());

    XMapWindow(m_pImpl->display, window);
    XFlush(m_pImpl->display);

    m_pImpl->openGl = std::make_shared<OpenGlLinux>();
    m_pImpl->isOpen = true;
}

bool WindowImpl::isOpen() const
{
    return m_pImpl->isOpen;
}

void WindowImpl::pollEvents()
{
}

std::shared_ptr<OpenGl> WindowImpl::getOpenGl() const
{
    return m_pImpl->openGl;
}

void WindowImpl::display() const
{
}

}
