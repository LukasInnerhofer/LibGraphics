#pragma once

#include "../opengl.h"

namespace LibGraphics
{

class OpenGlLinux : public OpenGl
{
public:
    OpenGlLinux();
    ~OpenGlLinux();

    #define GL_FUNCTION(returnType, name, ...) \
        name ## Type name(void) const override; \
        bool name ## Supported() const override;
    GL_FUNCTION_LIST
    #undef GL_FUNCTION

    void makeCurrent() const override;
    bool isCurrent() const override;
};

}
