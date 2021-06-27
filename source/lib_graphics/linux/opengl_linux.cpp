#include <string>

#include <GL/gl.h>
#include <iostream>
#include "opengl_linux.h"

namespace LibGraphics
{

OpenGlLinux::OpenGlLinux(Display *display, ::Window window, XVisualInfo* visualInfo) :
    m_display{display},
    m_window{window}
{
    m_context = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
    makeCurrent();
   
    // TODO: Figure out, which functions are actually supported 
    std::string const supportedFunctions{reinterpret_cast<char const *>(glGetString(GL_EXTENSIONS))};
    #define GL_FUNCTION(returnType, name, ...) \
        name ## Ptr = reinterpret_cast<name ## Type>(glXGetProcAddress(reinterpret_cast<GLubyte const *>(#name)));
    GL_FUNCTION_LIST
    #undef GL_FUNCTION
}

OpenGlLinux::~OpenGlLinux()
{
    
}

void OpenGlLinux::makeCurrent() const
{
    glXMakeCurrent(m_display, m_window, m_context);
}

bool OpenGlLinux::isCurrent() const
{
    return m_context == glXGetCurrentContext();
}

#define GL_FUNCTION(returnType, name, ...) \
    OpenGl::name ## Type OpenGlLinux::name() const \
    { \
        return name ## Ptr; \
    } \
    bool OpenGlLinux::name ## Supported() const \
    { \
	return name ## Ptr != nullptr; \
    }
GL_FUNCTION_LIST
#undef GL_FUNCTION

}

