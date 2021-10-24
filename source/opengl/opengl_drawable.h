#pragma once

#include <optional>

#include "libutilities/non_null.h"

#include "opengl.h"

namespace LibGraphics
{

class OpenGlDrawable
{
public:
    OpenGlDrawable(NonNullSharedPtr<OpenGl> openGl, bool hasTexture = false);
    ~OpenGlDrawable();

    GLuint getVertexBuffer() const;
    GLuint getVertexArray() const;
    std::optional<GLuint> getTexture() const;
    void bind() const;

private:
    GLuint m_vertexBuffer;
    GLuint m_vertexArray;
    std::optional<GLuint> m_texture;
    NonNullSharedPtr<OpenGl> m_openGl;
};

}