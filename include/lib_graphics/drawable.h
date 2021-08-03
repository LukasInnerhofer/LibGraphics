#pragma once

#include "lib_graphics/canvas.h"
#include "lib_graphics/vector.h"
#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

class Canvas;

class Drawable
{
public:
    Drawable(VertexBuffer const &vertexBuffer);

    VertexBuffer const &getVertexBuffer() const;
    virtual void draw(Canvas &canvas) = 0;

protected:
    VertexBuffer m_vertexBuffer;
    Vector m_position;
};

}
