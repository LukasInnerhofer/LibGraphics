#include "opengl.h"

#if LIB_GRAPHICS_PRINT_GL_ERRORS == 1
#include <iostream>
#endif // LIB_GRAPHICS_PRINT_GL_ERRORS == 1

namespace LibGraphics
{

OpenGl::~OpenGl()
{
    
}

#define GL_FUNCTION(returnType, name, ...) \
OpenGl::name ## Type OpenGl::name() \
{ \
    if constexpr (LIB_GRAPHICS_PRINT_GL_ERRORS == 1) \
    { \
        getError(); \
        lastCommand = #name; \
    } \
    return name ## Ptr; \
}
GL_FUNCTION_LIST
#undef GL_FUNCTION

#if LIB_GRAPHICS_PRINT_GL_ERRORS == 1
void OpenGl::getError() const
{
    if (!glGetErrorSupported())
    {
        // Maybe print to stderr
        return;
    }

    switch(glGetErrorPtr())
    {
    case GL_INVALID_ENUM:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] An unacceptable value was specified for an enumerated argument.\n";
        break;
    case GL_INVALID_VALUE:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] A numeric argument was out of range.\n";
        break;
    case GL_INVALID_OPERATION:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] The specified operation is not allowed in the current state.\n";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] The framebuffer object is not complete.\n";
        break;
    case GL_OUT_OF_MEMORY:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] There is not enough memory left to execute the command.\n";
        break;
    case GL_STACK_UNDERFLOW:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] An attempt has been made to perform an operation that would cause an internal stack underflow.\n";
        break;
    case GL_STACK_OVERFLOW:
        std::cerr << "LibGraphics::OpenGl Error. [" << lastCommand << "] An attempt has been made to perform an operation that would cause an internal stack overflow.\n";
        break;
    }
}
#endif // LIB_GRAPHICS_PRINT_GL_ERRORS == 1

}

