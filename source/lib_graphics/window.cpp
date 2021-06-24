#include <stdexcept>

#include "lib_graphics/window.h"
#include "lib_graphics/string.h"
#include "window_impl.h"

namespace LibGraphics
{

class Window::Impl
{
public:
    WindowImpl osImpl;
    std::shared_ptr<OpenGl> openGl;
};

Window::Window(String const& title) : m_pImpl{new Impl{}}
{
    m_pImpl->osImpl.create(title);
    m_pImpl->openGl = m_pImpl->osImpl.getOpenGl();
}

Window::~Window()
{

}

bool Window::isOpen() const
{
    return m_pImpl->osImpl.isOpen();
}

void Window::pollEvents()
{
    m_pImpl->osImpl.pollEvents();
}

void Window::clear(Color const &color)
{
    if (!m_pImpl->openGl->glClearColorSupported() ||
        !m_pImpl->openGl->glClearSupported())
    {
        throw std::runtime_error{"LibGraphics::Window::clear: Your system is missing support for required OpenGL functions."};
    }

    const Color::Float floatColor{color.toFloat()};
    if (!m_pImpl->openGl->isCurrent())
    {
        m_pImpl->openGl->makeCurrent();
    }
    m_pImpl->openGl->glClearColor()(floatColor.r, floatColor.g, floatColor.b, floatColor.a);
    m_pImpl->openGl->glClear()(GL_COLOR_BUFFER_BIT);
}

void Window::display() const
{
    m_pImpl->osImpl.display();
}

}