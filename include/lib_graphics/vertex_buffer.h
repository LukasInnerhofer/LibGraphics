#pragma once

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "lib_graphics/vertex.h"
#include "lib_graphics/texture.h"

namespace LibGraphics
{

class VertexBuffer
{
public:
    enum class Primitive { Triangle, Quad };

    template <typename TVertices>
    VertexBuffer(TVertices &&vertices, Primitive primitive, std::optional<std::shared_ptr<Texture>> texture = {}) :
        m_vertices{std::forward<TVertices>(vertices)},
        m_primitive{primitive},
        m_texture{texture},
        m_data{m_vertices.size() * (3 + 3 + (2 * static_cast<bool>(m_texture))), 0.0f, std::allocator<float>{}}
    {
        updateData();
    }

    void move(Vector<float> const &delta);
    std::vector<float> const &getData() const;
    std::optional<std::reference_wrapper<Texture const>> getTexture() const;
    Primitive getPrimitive() const;
    size_t getCount() const;

private:
    void updateData();

    std::vector<Vertex> m_vertices;
    std::optional<std::shared_ptr<Texture>> m_texture;
    std::vector<float> m_data;
    Primitive m_primitive;
};

}
