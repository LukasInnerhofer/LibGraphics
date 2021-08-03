#include "lib_graphics/rectangle.h"

namespace LibGraphics
{

Rectangle::Rectangle(const Vector &position, const Vector &size) :
    m_size{size}, Drawable{{
        { 
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        },
        VertexBuffer::Primitive::Quad
    }}
{
    m_position = position;
}

void Rectangle::draw(Canvas &canvas)
{
    canvas.draw(m_vertexBuffer);
}

}