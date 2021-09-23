#pragma once

#include <vector>

#include "lib_graphics/canvas.h"
#include "lib_graphics/color.h"
#include "lib_graphics/drawable_vertex_buffer.h"
#include "lib_graphics/vector.h"
#include "lib_graphics/vertex.h"

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
        std::optional<std::shared_ptr<Texture>> texture = {});
    Rectangle(
        Vector<float> const &size,
        Color const &fillColor,
        std::optional<std::shared_ptr<Texture>> texture = {});

private:
    Vector<float> m_size;
    Color m_fillColor;
};

}
