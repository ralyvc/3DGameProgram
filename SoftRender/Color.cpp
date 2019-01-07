#include "Color.h"

Color::Color(float r,float g,float b,float a):r(r),g(g),b(b),a(a)
{
    data = (uint32_t)(a * 255) << 24 | (uint32_t)(r * 255) << 16 | (uint32_t)(g * 255) << 8 | (uint32_t)(b * 255) ;
}



Color::Color(uint32_t rgba)
{

    float r = ((rgba & 0xff000000) >> 24) / 255.0;
    float g = ((rgba & 0x00ff0000) >> 16) / 255.0;
    float b = ((rgba & 0x0000ff00) >> 8) / 255.0;
    float a = ((rgba & 0x000000ff) ) / 255.0;
    Color(r, b, b, a);
}


Color::Color(int32_t rgba)
{
    uint32_t dd =*(uint32_t*) (&rgba);
    float r = ((dd & 0xff000000) >> 24) / 255.0;
    float g = ((dd & 0x00ff0000) >> 16) / 255.0;
    float b = ((dd & 0x0000ff00) >> 8) / 255.0;
    float a = ((dd & 0x000000ff) ) / 255.0;
    Color(r, b, b, a);
}


uint32_t Color::uint32() const
{
    return data;
}