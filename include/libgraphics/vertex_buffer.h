#pragma once

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "libgraphics/vertex.h"
#include "libgraphics/texture.h"
#include "libgraphics/window.h"

#include "libutilities/badge.h"
#include "libutilities/non_null.h"

namespace LibGraphics
{

class Window;

class VertexBuffer
{
public:
    enum class Primitive { Triangle, Quad };

    VertexBuffer(
        std::vector<Vertex> vertices,
        Primitive primitive, 
        std::optional<NonNullSharedPtr<Texture>> texture = {});

    void move(Vector<float> const &delta);
    std::vector<float> const &getData() const;
    std::optional<std::reference_wrapper<Texture>> getTexture(Badge<Window>) const;
    Primitive getPrimitive() const;
    size_t getCount() const;

private:
    void updateData();

    size_t m_vertexCount;
    std::optional<NonNullSharedPtr<Texture>> m_texture;
    std::vector<float> m_data;
    Primitive m_primitive;
};

}
