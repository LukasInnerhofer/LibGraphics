#include "libgraphics/drawable.h"

namespace LibGraphics
{

Drawable::Drawable()
{

}

Vector<float> const &Drawable::getPosition() const
{
    return m_position;
}

void Drawable::setPosition(const Vector<float> &position)
{
    m_position = position;
}

}