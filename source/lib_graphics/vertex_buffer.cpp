#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

VertexBuffer::VertexBuffer(std::vector<Vertex> const &vertices, Primitive primitive) :
    m_vertices{vertices},
    m_primitive{primitive},
    m_data{static_cast<size_t>(vertices.size() * 6), 0.0f, std::allocator<float>()}
{
    std::vector<float>::iterator itData{m_data.begin()};
    for (Vertex const &vertex : m_vertices)
    {
        Color::Float const &floatColor{vertex.color.toFloat()};
        *itData++ = vertex.position.getX();
        *itData++ = vertex.position.getY();
        *itData++ = 1.0f;
        *itData++ = floatColor.r;
        *itData++ = floatColor.g;
        *itData++ = floatColor.b;
    }
}

void VertexBuffer::move(Vector<float> const &delta)
{
    std::vector<float>::iterator itData{m_data.begin()};
    for (Vertex &vertex : m_vertices)
    {
        vertex.position += delta;
        *itData++ = vertex.position.getX();
        *itData++ = vertex.position.getY();
        itData += 4;
    }
}

std::vector<float> const &VertexBuffer::getData() const
{
    return m_data;
}

VertexBuffer::Primitive VertexBuffer::getPrimitive() const
{
    return m_primitive;
}

size_t VertexBuffer::getCount() const
{
    return m_vertices.size();
}

}