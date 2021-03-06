#include "Color.h"

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
    data = (uint32_t)(a * 255) << 24 | (uint32_t)(r * 255) << 16 | (uint32_t)(g * 255) << 8 | (uint32_t)(b * 255);
}

Color::Color(uint32_t rgba) : Color(((rgba & 0xff000000) >> 24) / 255.0, ((rgba & 0x00ff0000) >> 16) / 255.0, ((rgba & 0x0000ff00) >> 8) / 255.0, ((rgba & 0x000000ff)) / 255.0)
{
}

Color::Color(int32_t rgba) : Color(*(uint32_t *)(&rgba))
{
}

uint32_t Color::uint32() const
{
    return data;
}