#pragma once

namespace LibGraphics
{

template <typename T>
class Vector
{
public:
    constexpr Vector() : Vector{0, 0}
    {

    }
    constexpr Vector(T x, T y) : m_x{x}, m_y{y}
    {

    }

    T getX() const
    {
        return m_x;
    }
    T getY() const
    {
        return m_y;
    }

    Vector operator+(Vector const &rhs) const
    {
        return {m_x + rhs.m_x, m_y + rhs.m_y};
    }

    Vector& operator+=(Vector const &rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        return *this;
    }

    Vector operator-(Vector const &rhs) const
    {
        return {m_x - rhs.m_x, m_y - rhs.m_y};
    }

private:
    T m_x, m_y;
};

}