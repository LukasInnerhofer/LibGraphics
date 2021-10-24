#include "libgraphics/texture.h"

namespace LibGraphics
{

std::vector<uint8_t> const &Texture::getData() const
{
    return m_data;
}

Texture::SizeVector Texture::getSize() const
{
    return m_size;
}

Texture::Filtering Texture::getFiltering() const
{
    return m_filtering;
}

bool Texture::isValid() const
{
    return m_valid;
}

bool Texture::setPixel(PositionVector const &position, Color color)
{
    if (position.getX() >=  m_size.getX() ||
        position.getY() >= m_size.getY())
    {
        return false;
    }

    size_t const offset{position.getX() * position.getY() * bytesPerPixel};
    m_data[offset] = color.getR();
    m_data[offset + 1] = color.getG();
    m_data[offset + 2] = color.getB();
    
    m_valid = false;

    return true;
}

void Texture::validate()
{
    m_valid = true;
}

}
