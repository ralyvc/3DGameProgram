#include "Color.h"
#include <iostream>
#pragma once
class Canvas {
    uint32_t *_pixels;    
    float _width;
    float _height;
    
    void putPixel(int x, int y,  const Color &color);


  public:
    Canvas(uint32_t *pixels, float width, float height) {
        _pixels = pixels;
        _width = width;
        _height = height;

    };
    void BresenhamLine1(int x0,int y0,int x1,int y1,const Color &c);
    void BresenhamLine(int x0,int y0,int x1,int y1,const Color &c);
    virtual ~Canvas() {
    };
    
    void clear();


};
