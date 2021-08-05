#pragma once

#include <vector>

#include "lib_graphics/canvas.h"
#include "lib_graphics/color.h"
#include "lib_graphics/vector.h"
#include "lib_graphics/vertex.h"

namespace LibGraphics
{

class Rectangle : public Drawable
{
public:
    static constexpr Vector<float> defaultPosition{0.0f, 0.0f};

    Rectangle(Vector<float> const &position, Vector<float> const &size, Color const &fillColor);
    Rectangle(Vector<float> const &size, Color const &fillColor);

    void setPosition(Vector<float> const &position) override;
    void draw(Canvas &canvas) override;
    
private:
    Vector<float> m_size;
    Color m_fillColor;
};

}