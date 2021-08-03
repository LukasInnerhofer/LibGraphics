#pragma once

#include <cstdint>
#include <memory>
#include <string>

#define GL_FALSE    0
#define GL_TRUE     1

#define GL_BYTE             0x1400
#define GL_UNSIGNED_BYTE    0x1401
#define GL_SHORT            0x1402
#define GL_UNSIGNED_SHORT   0x1403
#define GL_FLOAT            0x1406
#define GL_FIXED            0x140C

#define GL_INVALID_ENUM                     0x0500
#define GL_INVALID_VALUE                    0x0501
#define GL_INVALID_OPERATION                0x0502
#define GL_STACK_OVERFLOW                   0x0503
#define GL_STACK_UNDERFLOW                  0x0504
#define GL_OUT_OF_MEMORY                    0x0505
#define GL_INVALID_FRAMEBUFFER_OPERATION    0x0506

#define GL_TRIANGLES    0x0004
#define GL_QUADS        0x0007

#define GL_ARRAY_BUFFER 0x8892

#define GL_STATIC_DRAW 0x88E4

#define GL_FRAGMENT_SHADER  0x8B30
#define GL_VERTEX_SHADER    0x8B31

#define GL_COMPILE_STATUS   0x8B81
#define GL_LINK_STATUS      0x8B82
#define GL_INFO_LOG_LENGTH  0x8B84

#if !defined(GL_COLOR_BUFFER_BIT)
#define GL_COLOR_BUFFER_BIT 0x4000
#endif

using GLenum = unsigned int;
using GLbitfield = unsigned int;
using GLuint = unsigned int;
using GLint = int;
using GLsizei = int;
using GLboolean = unsigned char;
using GLbyte = signed char;
using GLchar = char;
using GLshort = short;
using GLubyte = unsigned char;
using GLushort = unsigned short;
using GLulong = unsigned long;
using GLfloat = float;
using GLclampf = float;
using GLdouble = double;
using GLclampd= double;
using GLsizeiptr = std::ptrdiff_t;

namespace LibGraphics
{

class OpenGl
{
public:
    virtual ~OpenGl();

    #define GL_FUNCTION_LIST \
        GL_FUNCTION(void, glClear, GLbitfield mask) \
        GL_FUNCTION(void, glClearColor, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) \
        GL_FUNCTION(void, glGenBuffers, GLsizei n, GLuint *buffers) \
        GL_FUNCTION(void, glDeleteBuffers, GLsizei n, GLuint const *buffers) \
        GL_FUNCTION(void, glBindBuffer, GLenum target, GLuint buffer) \
        GL_FUNCTION(void, glBufferData, GLenum target, GLsizeiptr size, void const *data, GLenum usage) \
        GL_FUNCTION(void, glGenVertexArrays, GLsizei n, GLuint *arrays) \
        GL_FUNCTION(void, glDeleteVertexArrays, GLsizei n, GLuint const *arrays) \
        GL_FUNCTION(void, glDrawArrays, GLenum mode, GLint first, GLsizei count) \
        GL_FUNCTION(void, glBindVertexArray, GLuint array) \
        GL_FUNCTION(GLuint, glCreateShader, GLenum shaderType) \
        GL_FUNCTION(void, glDeleteShader, GLuint shader) \
        GL_FUNCTION(void, glShaderSource, GLuint shader, GLsizei count, GLchar const **string, GLint const *length) \
        GL_FUNCTION(void, glCompileShader, GLuint shader) \
        GL_FUNCTION(void, glGetShaderiv, GLuint shader, GLenum pname, GLint *params) \
        GL_FUNCTION(void, glGetShaderInfoLog, GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog) \
        GL_FUNCTION(GLuint, glCreateProgram) \
        GL_FUNCTION(void, glDeleteProgram, GLuint program) \
        GL_FUNCTION(void, glGetProgramiv, GLuint program, GLenum pname, GLint *params) \
        GL_FUNCTION(void, glGetProgramInfoLog, GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) \
        GL_FUNCTION(void, glAttachShader, GLuint program, GLuint shader) \
        GL_FUNCTION(void, glLinkProgram, GLuint program) \
        GL_FUNCTION(void, glUseProgram, GLuint program) \
        GL_FUNCTION(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void const *pointer) \
        GL_FUNCTION(void, glEnableVertexAttribArray, GLuint index) \
        GL_FUNCTION(GLenum, glGetError, void)

    #define GL_FUNCTION(returnType, name, ...) \
        typedef returnType (* const name ## Type)(__VA_ARGS__); \
        name ## Type name(void); \
        virtual bool name ## Supported() const = 0;
    GL_FUNCTION_LIST
    #undef GL_FUNCTION

    virtual void makeCurrent() const = 0;
    virtual bool isCurrent() const = 0;

protected:
    #define GL_FUNCTION(returnType, name, ...) \
    returnType (* name ## Ptr)(__VA_ARGS__);
    GL_FUNCTION_LIST
    #undef GL_FUNCTION

private:
    void getError() const;

    std::string lastCommand;
};

}

