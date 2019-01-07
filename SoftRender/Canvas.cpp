#include "Canvas.h"
#include <cstring>

void Canvas::clear()
{
    memset((uint32_t *)_pixels, 0, sizeof(uint32_t) * _width * _height);
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
    int dx = (x1 - x0);
    int dy = (y1 - y0);
    int delt_x = dx > 0 ? 1 : -1;
    int delt_y = dy > 0 ? 1 : -1;
    float e = 0;
    int dx2 = dx << 1;
    int dy2 = dy << 1;
    if (abs(dx) >= abs(dy))
    {
        for (x = x0; x != x1; x+=delt_x)
        {
            putPixel(x, y, c);

            e = e + dy2;
            if (abs(e) > abs(dx2))
            {
                y+=delt_y;
                e = e - dx2;
            }
        }
    }
    else
    {
        for (y = y0; y != y1; y += delt_y)
        {
            putPixel(x, y, c);
            e = e + dx2;
            if (abs(e) > abs(dy2))
            {
                x += delt_x;
                e = e - dy2;
            }
        }
    }
}