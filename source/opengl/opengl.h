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

#define GL_TEXTURE 0x1702

#define GL_RGB  0x1907
#define GL_RGBA 0x1908

#define GL_INVALID_ENUM                     0x0500
#define GL_INVALID_VALUE                    0x0501
#define GL_INVALID_OPERATION                0x0502
#define GL_STACK_OVERFLOW                   0x0503
#define GL_STACK_UNDERFLOW                  0x0504
#define GL_OUT_OF_MEMORY                    0x0505
#define GL_INVALID_FRAMEBUFFER_OPERATION    0x0506

#define GL_TEXTURE_2D 0x0DE1

#define GL_NEAREST  0x2600
#define GL_LINEAR   0x2601
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_LINEAR_MIPMAP_NEAREST  0x2701
#define GL_NEAREST_MIPMAP_LINEAR  0x2702
#define GL_LINEAR_MIPMAP_LINEAR   0x2703
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP  0x2900
#define GL_REPEAT 0x2901

#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF

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
        GL_FUNCTION(void, glEnable, GLenum cap) \
        GL_FUNCTION(void, glClear, GLbitfield mask) \
        GL_FUNCTION(void, glClearColor, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) \
        GL_FUNCTION(void, glGenBuffers, GLsizei n, GLuint *buffers) \
        GL_FUNCTION(void, glDeleteBuffers, GLsizei n, GLuint const *buffers) \
        GL_FUNCTION(void, glBindBuffer, GLenum target, GLuint buffer) \
        GL_FUNCTION(void, glBufferData, GLenum target, GLsizeiptr size, void const *data, GLenum usage) \
        GL_FUNCTION(void, glGenVertexArrays, GLsizei n, GLuint *arrays) \
        GL_FUNCTION(void, glDeleteVertexArrays, GLsizei n, GLuint const *arrays) \
        GL_FUNCTION(void, glDrawArrays, GLenum mode, GLint first, GLsizei count) \
        GL_FUNCTION(void, glDrawElements, GLenum mode, GLsizei count, GLenum type, void const *indices) \
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
        GL_FUNCTION(void, glGenTextures, GLsizei n, GLuint *textures) \
        GL_FUNCTION(void, glDeleteTextures, GLsizei n, const GLuint *textures) \
        GL_FUNCTION(void, glActiveTexture, GLenum texture) \
        GL_FUNCTION(void, glBindTexture, GLenum target, GLuint texture) \
        GL_FUNCTION(void, glTexParameteri, GLenum target, GLenum pname, GLint param) \
        GL_FUNCTION(void, glTexImage2D, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, void const *data) \
        GL_FUNCTION(void, glGenerateMipmap, GLenum target) \
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
