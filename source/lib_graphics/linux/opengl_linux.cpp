#include <string>
#include "opengl_linux.h"

namespace LibGraphics
{

OpenGlLinux::OpenGlLinux()
{
    makeCurrent();
}

OpenGlLinux::~OpenGlLinux()
{
    
}

void OpenGlLinux::makeCurrent() const
{
    
}

bool OpenGlLinux::isCurrent() const
{
    return false;
}

#define GL_FUNCTION(returnType, name, ...) \
    OpenGl::name ## Type OpenGlLinux::name() const \
    { \
        return nullptr; \	
    } \
    bool OpenGlLinux::name ## Supported() const \
    { \
	return false; \
    }
GL_FUNCTION_LIST
#undef GL_FUNCTION

}
