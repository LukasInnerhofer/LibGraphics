#pragma once

#include <string>

#include "opengl.h"
#include "libutilities/in_stream.h"

namespace LibGraphics
{

class Shader
{
public:
    Shader(std::shared_ptr<OpenGl> openGl, LibUtilities::InStream<GLchar> &&source, GLenum type);
    ~Shader();

    GLuint getId() const;

private:
    std::shared_ptr<OpenGl> m_openGl;
    GLuint m_id;
};

}