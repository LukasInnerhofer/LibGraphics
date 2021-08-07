#pragma once

#include "lib_graphics/canvas.h"
#include "lib_graphics/vector.h"

namespace LibGraphics
{

class Canvas;

class Drawable
{
public:
    Drawable();

    Vector<float> const &getPosition() const;
    virtual void setPosition(Vector<float> const &position);
    virtual void draw(Canvas &canvas) = 0;

protected:
    Vector<float> m_position;
};

}
