#pragma once

#include "lib_graphics/drawable.h"
#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

class DrawableVertexBuffer : public Drawable
{
public:
    DrawableVertexBuffer();

    void setPosition(Vector<float> const &position) override;
    void draw(Canvas &canvas) override;

protected:
    VertexBuffer m_vertexBuffer;
};

}