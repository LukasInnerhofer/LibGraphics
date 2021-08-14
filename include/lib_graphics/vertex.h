#pragma once

#include <optional>

#include "lib_graphics/color.h"
#include "lib_graphics/vector.h"

namespace LibGraphics
{

typedef struct VertexTag
{
    Color color;
    Vector<float> position;
    std::optional<Vector<float>> textureCoordinate;
} Vertex;

}