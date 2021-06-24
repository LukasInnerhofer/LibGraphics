#include <cassert>
#include <stdexcept>

#include "../window_impl.h"
#include "../opengl.h"
#include "opengl_linux.h"

namespace LibGraphics
{

class WindowImpl::Impl
{
public:
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
