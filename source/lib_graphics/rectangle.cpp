#include "lib_graphics/rectangle.h"

namespace LibGraphics
{

Rectangle::Rectangle(Vector<float> const &position, Vector<float> const &size, Color const &fillColor) :
    m_size{size},
    m_fillColor{fillColor}
{
    m_position = position;
    m_vertexBuffer = VertexBuffer{
        {
            {fillColor, position}, 
            {fillColor, position + Vector<float>{size.getX(), 0}},
            {fillColor, position + size},
            {fillColor, position + Vector<float>{0, size.getY()}}
        },
        VertexBuffer::Primitive::Quad
    };
}

Rectangle::Rectangle(Vector<float> const &size, Color const &fillColor) :
    Rectangle{defaultPosition, size, fillColor}
{
    
}

}