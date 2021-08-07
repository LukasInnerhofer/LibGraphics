#include "lib_graphics/drawable_vertex_buffer.h"

namespace LibGraphics
{

DrawableVertexBuffer::DrawableVertexBuffer() :
    m_vertexBuffer{{}, VertexBuffer::Primitive::Triangle}
{

}

void DrawableVertexBuffer::setPosition(const Vector<float> &position)
{
    m_vertexBuffer.move(position - m_position);
    Drawable::setPosition(position);
}

}
