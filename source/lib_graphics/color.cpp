#include "lib_graphics/color.h"

namespace LibGraphics
{

const Color Color::red{0xFF, 0x00, 0x00};
const Color Color::cornflowerBlue{0x89, 0xA6, 0xFB};

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_r{r}, m_g{g}, m_b{b}, m_a{a}
{

}

Color::Float Color::toFloat() const
{
    return {
            static_cast<float>(m_r) / max, 
            static_cast<float>(m_g) / max, 
            static_cast<float>(m_b) / max,
            static_cast<float>(m_a) / max};
}

}

