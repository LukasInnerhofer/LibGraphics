#include "lib_graphics/drawable_vertex_buffer.h"

namespace LibGraphics
{

DrawableVertexBuffer::DrawableVertexBuffer() :
    m_vertexBuffer{std::vector<Vertex>{}, VertexBuffer::Primitive::Triangle, std::optional<std::shared_ptr<Texture>>{}}
{

}

void DrawableVertexBuffer::setPosition(const Vector<float> &position)
{
    m_vertexBuffer.move(position - m_position);
    Drawable::setPosition(position);
}

void DrawableVertexBuffer::draw(Canvas &canvas)
{
    canvas.draw(m_vertexBuffer);
}

}
