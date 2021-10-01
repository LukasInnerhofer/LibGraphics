#pragma once

#include <map>
#include <stdexcept>
#include <vector>

#include "lib_graphics/color.h"
#include "lib_graphics/vector.h"

namespace LibGraphics
{

class Texture
{
public:
    using SizeVector = Vector<size_t>;
    using PositionVector = SizeVector;

    size_t constexpr static bytesPerPixel{3};

    Texture() = delete;

    template <typename TData>
    Texture(TData data, SizeVector const &size) :
        m_data{std::forward<TData>(data)},
        m_size{size},
        m_valid{false}
    {
        if (m_size.getX() * m_size.getY() * bytesPerPixel != m_data.size())
        {
            throw std::invalid_argument{"LibGraphics::Texture Error. Invalid size information."};
        }
    }

    std::vector<uint8_t> const &getData() const;
    SizeVector getSize() const;
    bool isValid() const;

    bool setPixel(PositionVector const &position, Color color);
    void validate();

private:
    std::vector<uint8_t> m_data;
    SizeVector m_size;
    bool m_valid;
};

};
