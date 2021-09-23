#include <cassert>
#include <stdexcept>

#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

void VertexBuffer::move(Vector<float> const &delta)
{
    assert(m_data.size() == m_vertices.size() * (3 + 3 + (static_cast<bool>(m_texture) * 2)));
    std::vector<float>::iterator itData{m_data.begin()};
    for (Vertex &vertex : m_vertices)
    {
        vertex.position += delta;
        *itData++ = vertex.position.getX();
        *itData++ = vertex.position.getY();
        itData += 4 + static_cast<bool>(m_texture) * 2;
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

std::optional<std::reference_wrapper<Texture const>> VertexBuffer::getTexture() const
{
    if (m_texture)
    {
        return {std::reference_wrapper<Texture const>{**m_texture}};
    }
    else
    {
        return {};
    }
}

void VertexBuffer::updateData()
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

        if (m_texture)
        {
            if (!vertex.textureCoordinate)
            {
                throw std::invalid_argument{"LibGraphics::VertexBuffer Error."
                    "A VertexBuffer with texture support must be constructed from "
                    "vertices containing texture coordinates."};
            }

            *itData++ = vertex.textureCoordinate->getX();
            *itData++ = vertex.textureCoordinate->getY();
        }
    }
}

}
