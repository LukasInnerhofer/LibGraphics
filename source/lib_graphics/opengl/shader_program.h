#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include "opengl.h"
#include "shader.h"

namespace LibGraphics
{

class ShaderProgram
{
public:
    template <typename T>
    ShaderProgram(std::shared_ptr<OpenGl> openGl, T const &shaders) :
        m_openGl{openGl}
    {
        m_id = m_openGl->glCreateProgram()();
        for (std::shared_ptr<Shader> const &shader : shaders)
        {
            m_openGl->glAttachShader()(m_id, shader->getId());
        }
        m_openGl->glLinkProgram()(m_id);
        int success;
        m_openGl->glGetProgramiv()(m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::vector<char> infoLog;
            GLint infoLogLength;
            m_openGl->glGetProgramiv()(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
            infoLog.resize(infoLogLength + 1);
            m_openGl->glGetProgramInfoLog()(m_id, infoLogLength, nullptr, &*infoLog.begin());
            throw std::runtime_error{
                std::string{"LibGraphics::Window Error. Failed to link shader program.\n"}
                .append(infoLog.data())
            };
        }
    }

    ~ShaderProgram()
    {
        m_openGl->glDeleteProgram()(m_id);
    }

    GLuint getId() const
    {
        return m_id;
    }

private:
    std::shared_ptr<OpenGl> m_openGl;
    GLuint m_id;
};

}