#include "lib_graphics/drawable.h"

namespace LibGraphics
{

Drawable::Drawable(VertexBuffer const &vertexBuffer): m_vertexBuffer{vertexBuffer}
{

}

VertexBuffer const &Drawable::getVertexBuffer() const
{
    return m_vertexBuffer;
}

}