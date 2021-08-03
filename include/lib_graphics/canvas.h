#pragma once

#include "lib_graphics/drawable.h"
#include "lib_graphics/vertex_buffer.h"

namespace LibGraphics
{

class Drawable;

class Canvas
{
public:
    virtual void draw(Drawable &drawable);
    virtual void draw(VertexBuffer const &vertexBuffer) = 0;
};

}