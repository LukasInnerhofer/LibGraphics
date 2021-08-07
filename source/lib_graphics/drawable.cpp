#include "lib_graphics/drawable.h"

namespace LibGraphics
{

Drawable::Drawable() :
    m_vertexBuffer{{}, VertexBuffer::Primitive::Triangle}
{

}

Vector<float> const &Drawable::getPosition() const
{
    return m_position;
}

void Drawable::setPosition(const Vector<float> &position)
{
    m_position = position;
}

}