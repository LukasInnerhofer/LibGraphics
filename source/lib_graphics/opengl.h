#pragma once

#include <cstdint>

namespace LibGraphics
{

namespace OpenGl
{
    bool isInitialized();
    void initialize();
}

}

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31

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
using GLsizeiptr = ptrdiff_t;

#define GL_FUNCTION(returnType, name, ...) \
    extern returnType (* name)(__VA_ARGS__);
#define GL_FUNCTION_LIST \
    GL_FUNCTION(void, glGenBuffers, GLsizei n, GLuint *buffers) \
    GL_FUNCTION(void, glGenVertexArrays, GLsizei n, GLuint *arrays) \
    GL_FUNCTION(void, glBindBuffer, GLenum target, GLuint buffer) \
    GL_FUNCTION(void, glBindVertexArray, GLuint array) \
    GL_FUNCTION(void, glBufferData, GLenum target, GLsizeiptr size, void const *data, GLenum usage) \
    GL_FUNCTION(GLuint, glCreateShader, GLenum shaderType) \
    GL_FUNCTION(void, glDeleteShader, GLuint shader) \
    GL_FUNCTION(void, glShaderSource, GLuint shader, GLsizei count, GLchar const **string, GLint const *length) \
    GL_FUNCTION(void, glCompileShader, GLuint shader) \
    GL_FUNCTION(GLuint, glCreateProgram) \
    GL_FUNCTION(void, glAttachShader, GLuint program, GLuint shader) \
    GL_FUNCTION(void, glLinkProgram, GLuint program) \
    GL_FUNCTION(void, glUseProgram, GLuint program) \
    GL_FUNCTION(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void const *pointer) \
    GL_FUNCTION(void, glEnableVertexAttribArray, GLuint index)

GL_FUNCTION_LIST
#undef GL_FUNCTION