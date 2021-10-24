#include "libgraphics/color.h"

namespace LibGraphics
{

const Color Color::red{0xFF, 0x00, 0x00};
const Color Color::cornflowerBlue{0x89, 0xA6, 0xFB};

Color::Color() : Color{0xFF, 0xFF, 0xFF}
{
    
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_r{r}, m_g{g}, m_b{b}, m_a{a}
{

}

void Color::setR(uint8_t r)
{
    m_r = r;
}

void Color::setG(uint8_t g)
{
    m_g = g;
}

void Color::setB(uint8_t b)
{
    m_b = b;
}

void Color::setA(uint8_t a)
{
    m_a = a;
}

uint8_t Color::getR() const
{
    return m_r;
}

uint8_t Color::getG() const
{
    return m_g;
}

uint8_t Color::getB() const
{
    return m_b;
}

uint8_t Color::getA() const
{
    return m_a;
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

