#pragma once

#include <cstdint>

namespace LibGraphics
{

class Color
{
    public:
    typedef struct FloatTag
    {
        float r, g, b, a;
        static constexpr float max = 1.f;

        FloatTag(float r, float g, float b, float a = max) : r{r}, g{g}, b{b}, a{a}
        {

        }
    } Float;

    uint8_t m_r, m_g, m_b, m_a;
    static constexpr uint8_t max = 0xFF;

    Color();
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = max);
    Color(Float const &floatColor);

    void setR(uint8_t r);
    void setG(uint8_t g);
    void setB(uint8_t b);
    void setA(uint8_t a);

    uint8_t getR() const;
    uint8_t getG() const;
    uint8_t getB() const;
    uint8_t getA() const;

    Float toFloat() const;

    static const Color red;
    static const Color cornflowerBlue;
};

}

