#pragma once

#include <string>

#include "opengl.h"

namespace LibGraphics
{

class Shader
{
public:
    Shader(std::shared_ptr<OpenGl> openGl, std::string_view source, GLenum type);
    ~Shader();

    GLuint getId() const;

private:
    std::shared_ptr<OpenGl> m_openGl;
    GLuint m_id;
};

}