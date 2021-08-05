#pragma once

#include "lib_graphics/color.h"
#include "lib_graphics/vector.h"

namespace LibGraphics
{

typedef struct VertexTag
{
    Color color;
    Vector<float> position;
} Vertex;

}