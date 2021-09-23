#pragma once

#include <map>
#include <stdexcept>
#include <vector>

#include "lib_graphics/vector.h"

namespace LibGraphics
{

class Texture
{
public:
    using SizeVector = Vector<size_t>;

    size_t constexpr static bytesPerPixel { 3 };

    template <typename TData>
    Texture(TData data, SizeVector size) :
        m_data{std::forward<TData>(data)},
        m_size{size}
    {
        if (m_size.getX() * m_size.getY() * bytesPerPixel != m_data.size())
        {
            throw std::invalid_argument{"LibGraphics::Texture Error. Invalid size information."};
        }
    }

    std::vector<uint8_t> const &getData() const;
    SizeVector getSize() const;

private:
    std::vector<uint8_t> m_data;
    SizeVector m_size;
};

};
