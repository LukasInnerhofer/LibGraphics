#include <cassert>
#include <stdexcept>

#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

size_t constexpr static floatsPerPositionVector{3};
size_t constexpr static floatsPerColorVector{3};
size_t constexpr static floatsPerTextureCoordinate{2};

static size_t floatsPerVertex(bool hasTexture)
{
    return floatsPerPositionVector +
        floatsPerColorVector +
        (floatsPerTextureCoordinate * hasTexture);
}

VertexBuffer::VertexBuffer(
    std::vector<Vertex> vertices, 
    Primitive primitive, 
    std::optional<std::shared_ptr<Texture>> texture) :
    m_vertexCount{vertices.size()},
    m_primitive{primitive},
    m_texture{texture},
    m_data{
        vertices.size() * floatsPerVertex(static_cast<bool>(m_texture)), 
        0.0f, 
        std::allocator<float>{}}
{
    std::vector<float>::iterator itData{m_data.begin()};
    for (Vertex const &vertex : vertices)
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

void VertexBuffer::move(Vector<float> const &delta)
{
    assert(floatsPerVertex(static_cast<bool>(m_texture)) * m_vertexCount == m_data.size());
    std::vector<float>::iterator itData{m_data.begin()};
    for (size_t itVertices = 0; itVertices < m_vertexCount; ++itVertices)
    {
        *itData++ += delta.getX();
        *itData++ += delta.getY();
        itData += 1 + floatsPerColorVector + static_cast<bool>(m_texture) * floatsPerTextureCoordinate;
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
    return m_vertexCount;
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

}
