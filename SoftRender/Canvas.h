/*
** EPITECH PROJECT, 2019
** 3DGameProgram
** File description:
** Canvas
*/

#include "Color.h"
#include <iostream>
#pragma once
class Canvas
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

    uint32_t *_pixels;
    float _width;
    float _height;

    void putPixel(int x, int y, const Color &color);
    ClipCode getClipCode(int x, int y);

  public:
    Canvas(uint32_t *pixels, float width, float height)
    {
        _pixels = pixels;
        _width = width;
        _height = height;
    };
    void BresenhamLine1(int x0, int y0, int x1, int y1, const Color &c);
    void BresenhamLine(int x0, int y0, int x1, int y1, const Color &c);
    virtual ~Canvas(){};

    void clear();

    bool ClipLine(int &x0, int &y0, int &x1, int &y1);
};
