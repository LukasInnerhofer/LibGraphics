#include "lib_graphics/canvas.h"

namespace LibGraphics
{

void Canvas::draw(Drawable &drawable)
{
    drawable.draw(*this);
}

}