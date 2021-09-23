#pragma once

#include <optional>

#include "lib_graphics/color.h"
#include "lib_graphics/vector.h"

namespace LibGraphics
{

typedef struct VertexTag
{
    using TextureCoordinate = Vector<float>;
    using PositionVector = Vector<float>;

    Color color;
    PositionVector position;
    std::optional<TextureCoordinate> textureCoordinate;
} Vertex;

}
