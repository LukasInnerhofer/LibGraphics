#pragma once

#include "libgraphics/window.h"
#include "libgraphics/vector.h"

namespace LibGraphics
{

class Window;

class Drawable
{
public:
    Drawable();
    virtual ~Drawable() = default;

    Vector<float> const &getPosition() const;
    virtual void setPosition(Vector<float> const &position);
    virtual void draw(Window &canvas) = 0;

protected:
    Vector<float> m_position;
};

}
