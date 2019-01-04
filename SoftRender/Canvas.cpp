#include "Canvas.h"
#include <cstring>

void Canvas::clear() 
{
    memset((uint32_t*)_pixels, 0, sizeof(uint32_t) * _width * _height);
}

void Canvas::putPixel(int x, int y, const Color &color)
{
    int index = (int)(_width * y + x);
    _pixels[index] = color.uint32();
}

void Canvas::BresenhamLine1(int x0, int y0, int x1, int y1, const Color &c)
{
    int x = x0;
    int y = y0;
    int dx = x1 - x0;
    int dy = y1 - y0;
    float k = dy / dx;
    float e = 0;

    for (size_t i = x0; i <= x1; i++)
    {
        putPixel(x, y, c);
        e = e + k;
        x++;
        if (e > 0.5)
        {
            y++;
            e--;
        }
    }
}
//等式两边同时乘以2*dx
void Canvas::BresenhamLine(int x0, int y0, int x1, int y1, const Color &c)
{
    int x = x0;
    int y = y0;
    int dx = (x1 - x0) << 1;
    int dy = (y1 - y0) << 1;

    float e = 0;

    for (size_t i = x0; i <= x1; i++)
    {
        putPixel(x, y, c);
        x++;
        e = e + dy;
        if (e > dx)
        {
            y++;
            e=e-dx;
        }
    }
}