#include "lib_graphics/texture.h"

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

}
