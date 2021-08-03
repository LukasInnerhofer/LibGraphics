#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

VertexBuffer::VertexBuffer(std::vector<float> const &data, Primitive primitive) :
    m_data{data}, m_primitive{primitive}
{
    
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
    return m_data.size() / 6;
}

}