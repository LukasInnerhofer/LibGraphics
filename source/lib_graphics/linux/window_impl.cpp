#include <cassert>
#include <stdexcept>
#include <thread>
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
    Atom wmDeleteMessage;
    std::shared_ptr<OpenGl> openGl{nullptr};
    bool isOpen;
};

WindowImpl::WindowImpl() : 
    m_pImpl{new Impl{}} 
{

}

WindowImpl::~WindowImpl()
{

}

void WindowImpl::create(String const &title, std::shared_ptr<std::queue<Window::Event>> events)
{
    m_events = events;

    if (m_pImpl->isOpen)
    {
        throw std::logic_error{"Window has already been created"};
    }

    // NULL => Use DISPLAY environment variable
    m_pImpl->display = XOpenDisplay(NULL);
    if (m_pImpl->display == NULL)
    {
	throw std::runtime_error{"Failed to connect to X server."};
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

    m_pImpl->wmDeleteMessage = XInternAtom(m_pImpl->display, "WM_DELETE_WINDOW", true);
    XSetWMProtocols(m_pImpl->display, window, &m_pImpl->wmDeleteMessage, 1);

    XMapWindow(m_pImpl->display, window);
    XFlush(m_pImpl->display);

    m_pImpl->openGl = std::make_shared<OpenGlLinux>();
    m_pImpl->isOpen = true;
}

bool WindowImpl::isOpen() const
{
    if (m_pImpl == nullptr)
    {
	throw std::logic_error{"Window has not been created"};
    }

    return m_pImpl->isOpen;
}

void WindowImpl::pollEvents()
{
    if (m_pImpl == nullptr)
    {
	throw std::logic_error{"Window has not been created"};
    }

    XEvent event;
    while (XPending(m_pImpl->display))
    {
        XNextEvent(m_pImpl->display, &event);
	if (event.type == ClientMessage &&
	    event.xclient.data.l[0] == m_pImpl->wmDeleteMessage)
	{
            m_events->push(Window::Event{Window::EventType::Closed});
	}
    }
}

std::shared_ptr<OpenGl> WindowImpl::getOpenGl() const
{
    if (m_pImpl == nullptr)
    {
	throw std::logic_error{"Window has not been created"};
    }

    return m_pImpl->openGl;
}

void WindowImpl::display() const
{
    
}

void WindowImpl::close()
{
    XCloseDisplay(m_pImpl->display);
    m_pImpl->isOpen = false;
}

}

