#pragma once

#include <optional>

#include "libgraphics/color.h"
#include "libgraphics/vector.h"

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
