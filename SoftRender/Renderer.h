/*
** EPITECH PROJECT, 2019
** 3DGameProgram
** File description:
** Renderer
*/

#include "Buffer.h"
#include "Color.h"
#include "Vector3.h"
#include <iostream>
#pragma once
class Renderer
{
    enum ClipCode
    {
        ClipCodeC = 0,
        ClipCodeN = 8, //1000
        ClipCodeS = 4, //0100
        ClipCodeE = 2, //0010
        ClipCodeW = 1, //0001
        ClipCodeNW = ClipCodeW | ClipCodeN,
        ClipCodeNE = ClipCodeE | ClipCodeN,
        ClipCodeSW = ClipCodeW | ClipCodeS,
        ClipCodeSE = ClipCodeE | ClipCodeS,

    };

    Buffer<uint32_t> *pixBuffer;
    int _width;
    int _height;

    void putPixel(int x, int y, const Color &color);
    ClipCode getClipCode(int x, int y) const;

  public:
    Renderer(int width, int height)
    {
        _width = width;
        _height = height;
        pixBuffer = new Buffer<uint32_t>(_width, _height);
    };
    void BresenhamLine1(int x0, int y0, int x1, int y1, const Color &c);
    void BresenhamLine(int x0, int y0, int x1, int y1, const Color &c);
    Buffer<uint32_t> *GetBuffer() const;
    virtual ~Renderer() { delete pixBuffer; };

    void clear();

    bool ClipLine(int &x0, int &y0, int &x1, int &y1) const;

    void drawFlatBottomTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c)
    {
        float dxLeft = v2.x - v1.x;
        float dyLeft = v2.y - v1.y;
        float sxLeft = 0;
        if (dyLeft != 0)
        {
            sxLeft = dxLeft / dyLeft;
        }
        float dxRigth = v3.x - v1.x;
        float dyRight = v3.y - v1.y;
        float sxRight = 0;
        if (dyRight != 0)
        {
            sxRight = dxRigth / dyRight;
        }
        float xl = v1.x;
        float xr = v1.x;
        for (size_t i = v1.y; i <= v2.y; i++)
        {
            BresenhamLine(xl, i, xr, i, c);
            xl += sxLeft;
            xr += sxRight;
        }
    }
};
