#include <stdexcept>
#include <vector>

#include "shader.h"

namespace LibGraphics
{

Shader::Shader(std::shared_ptr<OpenGl> openGl, std::string_view source, GLuint type) :
    m_openGl{openGl}
{
    m_id = m_openGl->glCreateShader()(type);
    GLchar const * sourceData{source.data()};
    m_openGl->glShaderSource()(m_id, 1, &sourceData, nullptr);
    m_openGl->glCompileShader()(m_id);

    int success;
    m_openGl->glGetShaderiv()(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::vector<char> infoLog;
        GLint infoLogLength;
        m_openGl->glGetShaderiv()(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
        infoLog.resize(infoLogLength + 1);
        m_openGl->glGetShaderInfoLog()(m_id, infoLogLength, nullptr, &*infoLog.begin());
        throw std::runtime_error{
            std::string{"LibGraphics::Window Error. Failed to compile shader.\n"}
            .append(infoLog.data())
        };
    }
}

Shader::~Shader()
{
    m_openGl->glDeleteShader()(m_id);
}

GLuint Shader::getId() const
{
    return m_id;
}

}