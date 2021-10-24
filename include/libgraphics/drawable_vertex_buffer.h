#pragma once

#include "libgraphics/window.h"
#include "libgraphics/vertex_buffer.h"

namespace LibGraphics
{

class DrawableVertexBuffer : public Drawable
{
public:
    DrawableVertexBuffer();

    void setPosition(Vector<float> const &position) override;
    void draw(Window &canvas) override;

protected:
    VertexBuffer m_vertexBuffer;
};

}