/*
** EPITECH PROJECT, 2019
** 3DGameProgram
** File description:
** Renderer
*/

#include "Color.h"
#include "Buffer.h"
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
    ClipCode getClipCode(int x, int y);

  public:
    Renderer(int width, int height)
    {
        _width = width;
        _height = height;
        pixBuffer = new Buffer<uint32_t>(_width, _height);
    };
    void BresenhamLine1(int x0, int y0, int x1, int y1, const Color &c);
    void BresenhamLine(int x0, int y0, int x1, int y1, const Color &c);
    Buffer<uint32_t> *GetBuffer();
    virtual ~Renderer() { delete pixBuffer; };

    void clear();

    bool ClipLine(int &x0, int &y0, int &x1, int &y1);
};
