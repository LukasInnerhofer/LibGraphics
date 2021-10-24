#pragma once

#include <vector>

#include "libgraphics/color.h"
#include "libgraphics/drawable_vertex_buffer.h"
#include "libgraphics/vector.h"
#include "libgraphics/vertex.h"

#include "libutilities/non_null.h"

namespace LibGraphics
{

class Rectangle : public DrawableVertexBuffer
{
public:
    static constexpr Vector<float> defaultPosition{0.0f, 0.0f};

    Rectangle(
        Vector<float> const &position,
        Vector<float> const &size,
        Color const &fillColor,
        std::optional<NonNullSharedPtr<Texture>> texture = {});
    Rectangle(
        Vector<float> const &size,
        Color const &fillColor,
        std::optional<NonNullSharedPtr<Texture>> texture = {});

private:
    Vector<float> m_size;
    Color m_fillColor;
};

}
