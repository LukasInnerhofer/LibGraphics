#pragma once

#include "lib_graphics/canvas.h"
#include "lib_graphics/vector.h"

namespace LibGraphics
{

class Rectangle : public Drawable
{
public:
    Rectangle(const Vector &position, const Vector& size);

    void draw(Canvas &canvas) override;
    
private:
    Vector m_size;
};

}