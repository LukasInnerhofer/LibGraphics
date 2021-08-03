#pragma once

#include <vector>

namespace LibGraphics
{

class VertexBuffer
{
public:
    enum class Primitive { Triangle, Quad };

    VertexBuffer(std::vector<float> const &data, Primitive primitive);

    std::vector<float> const &getData() const;
    Primitive getPrimitive() const;
    size_t getCount() const;

private:
    std::vector<float> m_data;
    Primitive m_primitive;
};

}