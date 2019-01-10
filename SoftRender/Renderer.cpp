#include "Renderer.h"
#include <cstring>

void Renderer::clear()
{
    pixBuffer->clear();
}

void Renderer::putPixel(int x, int y, const Color &color)
{
    (*pixBuffer)(x, y) = color.uint32();
}

void Renderer::BresenhamLine1(int x0, int y0, int x1, int y1, const Color &c)
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
void Renderer::BresenhamLine(int x0, int y0, int x1, int y1, const Color &c)
{

    if (ClipLine(x0, y0, x1, y1))
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
            for (x = x0; x != x1; x += delt_x)
            {
                putPixel(x, y, c);

                e = e + dy2;
                if (abs(e) > abs(dx2))
                {
                    y += delt_y;
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
}

Renderer::ClipCode Renderer::getClipCode(int x, int y) const
{

    Renderer::ClipCode clipCode = Renderer::ClipCodeC;

    if (x < 0)
    {
        clipCode = Renderer::ClipCode(clipCode | Renderer::ClipCodeW);
    }
    else if (x >= _width)
    {
        clipCode = Renderer::ClipCode(clipCode | Renderer::ClipCodeE);
    }
    if (y < 0)
    {
        clipCode = Renderer::ClipCode(clipCode | Renderer::ClipCodeN);
    }
    else if (y >= _height)
    {
        clipCode = Renderer::ClipCode(clipCode | Renderer::ClipCodeS);
    }
    return clipCode;
}

//https://blog.csdn.net/soulmeetliang/article/details/79179350
//Cohen－Sutherland 算法
bool Renderer::ClipLine(int &x0, int &y0, int &x1, int &y1) const
{

    Renderer::ClipCode p1Code = getClipCode(x0, y0);
    Renderer::ClipCode p2Code = getClipCode(x1, y1);

    if (p1Code & p2Code)
    {
        return false;
    }

    if (p1Code == Renderer::ClipCodeC && p2Code == Renderer::ClipCodeC)
    {
        return true;
    }
    float k = 0;
    float k1 = 0;
    if (x1 != x0)
    {
        k = (float)(y1 - y0) / (x1 - x0);
    }
    if (y1 != y0)
    {
        k1 = (float)(x1 - x0) / (y1 - y0);
    }

    switch (p1Code)
    {
    case Renderer::ClipCodeC:
        break;

    case Renderer::ClipCodeN:
        x0 = x1 + (0 - y1) * k1;
        y0 = 0;
        break;
    case Renderer::ClipCodeS:
        x0 = x1 + (_height-1 - y1) * k1;
        y0 = _height-1;
        break;
    case Renderer::ClipCodeW:
        y0 = y1 + (0 - x1) * k;
        x0 = 0;
        break;
    case Renderer::ClipCodeE:
        y0 = y1 + (_width-1 - x1) * k;
        x0 = _width-1;
        break;
    case Renderer::ClipCodeNE:
        x0 = x1 + (0 - y1) * k1;
        y0 = 0;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (_width-1 - x1) * k;
            x0 = _width-1;
        }
        break;
    case Renderer::ClipCodeSE:
        x0 = x1 + (_height-1 - y1) * k1;
        y0 = _height;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (_width-1 - x1) * k;
            x0 = _width-1;
        }
        break;
    case Renderer::ClipCodeNW:
        x0 = x1 + (0 - y1) * k1;
        y0 = 0;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (0 - x1) * k;
            x0 = 0;
        }
        break;
    case Renderer::ClipCodeSW:
        x0 = x1 + (_height-1 - y1) * k1;
        y0 = _height-1;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (0 - x1) * k;
            x0 = 0;
        }
        break;
    default:
        break;
    }
    
    if (x0<0||x0>=_width||y0<0||y0>=_height ) {
        return false;
    }
    switch (p2Code)
    {
    case Renderer::ClipCodeC:
        break;

    case Renderer::ClipCodeN:
        x1 = x0 + (0 - y0) * k1;
        y1 = 0;
        break;
    case Renderer::ClipCodeS:
        x1 = x0 + (_height-1 - y0) * k1;
        y1 = _height-1;
        break;
    case Renderer::ClipCodeW:
        y1 = y0 + (0 - x0) * k;
        x1 = 0;
        break;
    case Renderer::ClipCodeE:
        y1 = y0 + (_width-1 - x0) * k;
        x1 = _width-1;
        break;
    case Renderer::ClipCodeNE:
        x1 = x0 + (0 - y0) * k1;
        y1 = 0;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (_width-1 - x0) * k;
            x1 = _width-1;
        }
        break;
    case Renderer::ClipCodeSE:
        x1 = x0 + (_height-1 - y0) * k1;
        y1 = _height-1;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (_width-1 - x0) * k;
            x1 = _width-1;
        }
        break;
    case Renderer::ClipCodeNW:
        x1 = x0 + (0 - y0) * k1;
        y1 = 0;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (0 - x0) * k;
            x1 = 0;
        }
        break;
    case Renderer::ClipCodeSW:
        x1 = x0 + (_height-1 - y0) * k1;
        y1 = _height-1;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (0 - x0) * k;
            x1 = 0;
        }
        break;
    default:
        break;
    }
       if (x1<0||x1>=_width||y1<0||y1>=_height ) {
        return false;
    }
    return true;
}

Buffer<uint32_t> *Renderer::GetBuffer() const
{
    return pixBuffer;
}
