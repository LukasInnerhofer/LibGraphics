#include "opengl_drawable.h"

namespace LibGraphics
{

OpenGlDrawable::OpenGlDrawable(std::shared_ptr<OpenGl> openGl, bool hasTexture) :
    m_openGl{openGl}
{
    m_openGl->glGenBuffers()(1, &m_vertexBuffer);
    m_openGl->glGenVertexArrays()(1, &m_vertexArray);
    if (hasTexture)
    {
        m_texture = 0;
        m_openGl->glGenTextures()(1, &*m_texture);
    }
}

OpenGlDrawable::~OpenGlDrawable()
{
    m_openGl->glDeleteBuffers()(1, &m_vertexBuffer);
    m_openGl->glDeleteVertexArrays()(1, &m_vertexArray);
    if (m_texture)
    {
        m_openGl->glDeleteTextures()(1, &*m_texture);
    }
}

void OpenGlDrawable::bind() const
{
    m_openGl->glBindBuffer()(GL_ARRAY_BUFFER, m_vertexBuffer);
    m_openGl->glBindVertexArray()(m_vertexArray);
    if (m_texture)
    {
        m_openGl->glActiveTexture()(GL_TEXTURE0);
        m_openGl->glBindTexture()(GL_TEXTURE_2D, *m_texture);
    }
}

}
