#pragma once

#include <Windows.h>

#include "../opengl.h"

namespace LibGraphics
{

class OpenGlWindows : public OpenGl
{
public:
    OpenGlWindows(HDC deviceContext);

    #define GL_FUNCTION(returnType, name, ...) \
        bool name ## Supported() const override;
    GL_FUNCTION_LIST
    #undef GL_FUNCTION

    void makeCurrent() const override;
    bool isCurrent() const override;

private:
    HGLRC m_context;
    HDC m_deviceContext;
};

}