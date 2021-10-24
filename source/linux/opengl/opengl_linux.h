#pragma once

#include <X11/Xlib.h>
#include <GL/glx.h>

#include "../../opengl/opengl.h"

namespace LibGraphics
{

class OpenGlLinux : public OpenGl
{
public:
    OpenGlLinux(Display *display, ::Window window, XVisualInfo *visualInfo);
    ~OpenGlLinux();

    #define GL_FUNCTION(returnType, name, ...) \
        bool name ## Supported() const override;
    GL_FUNCTION_LIST
    #undef GL_FUNCTION

    void makeCurrent() const override;
    bool isCurrent() const override;

private:
    Display *m_display;
    ::Window m_window;
    GLXContext m_context;
};

}
