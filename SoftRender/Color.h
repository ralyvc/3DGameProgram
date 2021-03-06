
#include <cstdint>
#include <cstdlib>

#pragma once
class Color
{

  public:
    float r;
    float g;
    float b;
    float a;
    uint32_t data;
    Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    Color(uint32_t rgba);
    Color(int32_t rgba);

    static Color randomColor()
    {
        float r = (rand() % 255) / 255.0;
        float g = (rand() % 255) / 255.0;
        float b = (rand() % 255) / 255.0;
        Color c = Color(r, g, b, 1);
        return c;
    };

    static Color Red()
    {
        return Color(1, 0, 0, 1);
    }
    static Color Green()
    {
        return Color(0, 1, 0, 1);
    }
    static Color Blue()
    {
        return Color(0, 0, 1, 1);
    }
    uint32_t uint32() const;

    Color operator+(const Color &color) const
    {
        return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    };

    Color operator-(const Color &color) const
    {
        return Color(r - color.r, g - color.g, b - color.b, a - color.a);
    };

    Color operator*(float factor) const
    {
        return Color(r * factor, g * factor, b * factor, a * factor);
    };

    Color interpolate(const Color &c, float factor) const
    {
        return *this + (c - *this) * factor;
    };
};
