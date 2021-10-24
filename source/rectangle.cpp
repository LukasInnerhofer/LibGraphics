#include "libgraphics/rectangle.h"

namespace LibGraphics
{

Rectangle::Rectangle(
    Vector<float> const &position,
    Vector<float> const &size,
    Color const &fillColor,
    std::optional<NonNullSharedPtr<Texture>> texture) :
    m_size{size},
    m_fillColor{fillColor}
{
    m_position = position;
    m_vertexBuffer = VertexBuffer{
        std::vector<Vertex>{
            {
                fillColor,
                position,
                Vertex::TextureCoordinate{0.0f, 0.0f}
            },
            {
                fillColor,
                position + Vector<float>{size.getX(), 0},
                Vertex::TextureCoordinate{1.0f, 0.0f}
            },
            {
                fillColor,
                position + size,
                Vertex::TextureCoordinate{1.0f, 1.0f}
            },
            {
                fillColor,
                position + Vector<float>{0, size.getY()},
                Vertex::TextureCoordinate{0.0f, 1.0f}
            }
        },
        VertexBuffer::Primitive::Quad,
        texture
    };
}

Rectangle::Rectangle(
    Vector<float> const &size,
    Color const &fillColor,
    std::optional<NonNullSharedPtr<Texture>> texture) :
    Rectangle{defaultPosition, size, fillColor, texture}
{

}

}
