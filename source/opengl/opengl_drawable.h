#pragma once

#include <optional>

#include "opengl.h"

namespace LibGraphics
{

class OpenGlDrawable
{
public:
    OpenGlDrawable(std::shared_ptr<OpenGl> openGl, bool hasTexture = false);
    ~OpenGlDrawable();

    GLuint getVertexBuffer() const;
    GLuint getVertexArray() const;
    std::optional<GLuint> getTexture() const;
    void bind() const;

private:
    GLuint m_vertexBuffer;
    GLuint m_vertexArray;
    std::optional<GLuint> m_texture;
    std::shared_ptr<OpenGl> m_openGl;
};

}