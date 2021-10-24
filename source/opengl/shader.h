#pragma once

#include <string>

#include "libutilities/in_stream.h"
#include "libutilities/non_null.h"

#include "opengl.h"

namespace LibGraphics
{

class Shader
{
public:
    Shader(NonNullSharedPtr<OpenGl> openGl, LibUtilities::InStream<GLchar> &&source, GLenum type);
    ~Shader();

    GLuint getId() const;

private:
    NonNullSharedPtr<OpenGl> m_openGl;
    GLuint m_id;
};

}