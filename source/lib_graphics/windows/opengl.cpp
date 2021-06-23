#include <Windows.h>
#include <gl/GL.h>

#include "../opengl.h"

#define GL_FUNCTION(returnType, name, ...) \
    returnType (* name)(__VA_ARGS__);
GL_FUNCTION_LIST
#undef GL_FUNCTION

namespace LibGraphics
{

namespace OpenGl
{
    static bool initialized{false};

    bool isInitialized()
    {
        return initialized;
    }

    void initialize()
    {
        #define GL_FUNCTION(returnType, name, ...) \
            name = reinterpret_cast<returnType (*)(__VA_ARGS__)>(wglGetProcAddress(#name));
        GL_FUNCTION_LIST
        #undef GL_FUNCTION

        initialized = true;
    }
}

}