#include <string>
#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#include "opengl_windows.h"
#include "utilities.h"

namespace LibGraphics
{

static bool wglLoaded{false};

#define WGL_FUNCTION(returnType, name, ...) \
    typedef returnType (* name ## Type)(__VA_ARGS__); \
    static name ## Type name;
#define WGL_FUNCTION_LIST \
    WGL_FUNCTION(HGLRC, wglCreateContext, HDC deviceContext) \
    WGL_FUNCTION(HGLRC, wglGetCurrentContext) \
    WGL_FUNCTION(PROC, wglGetProcAddress, LPCSTR name) \
    WGL_FUNCTION(BOOL, wglMakeCurrent, HDC deviceContext, HGLRC glContext)
WGL_FUNCTION_LIST
#undef WGL_FUNCTION

OpenGlWindows::OpenGlWindows(HDC deviceContext)
{
    const HMODULE module = LoadLibraryW(L"opengl32.dll");

    if (!wglLoaded)
    {
        #define WGL_FUNCTION(returnType, name, ...) \
        name = reinterpret_cast<name ## Type>(GetProcAddress(module, #name)); \
        if (name == nullptr) \
        { \
            throwSystemError("Failed to load" #name " from opengl32.dll"); \
        }
        WGL_FUNCTION_LIST
        #undef WGL_FUNCTION
        wglLoaded = true;
    }
    
    m_deviceContext = deviceContext;
    m_context = wglCreateContext(m_deviceContext);
    if (m_context == NULL)
    {
        throwSystemError("Failed to create OpenGL context");
    }
    makeCurrent();
    
    #define GL_FUNCTION(returnType, name, ...) \
        name ## Ptr = reinterpret_cast<name ## Type>(wglGetProcAddress(#name)); \
        if(name ## Ptr == nullptr) \
        { \
            name ## Ptr = reinterpret_cast<name ## Type>(GetProcAddress(module, #name)); \
        }
    GL_FUNCTION_LIST
    #undef GL_FUNCTION
}

#define GL_FUNCTION(returnType, name, ...) \
bool OpenGlWindows::name ## Supported() const \
{ \
    return name ## Ptr != nullptr; \
}
GL_FUNCTION_LIST
#undef GL_FUNCTION

void OpenGlWindows::makeCurrent() const
{
    if (!wglMakeCurrent(m_deviceContext, m_context))
    {
        throwSystemError("Failed to make OpenGL context curret");
    }
}

bool OpenGlWindows::isCurrent() const
{
    return wglGetCurrentContext() == m_context;
}

}