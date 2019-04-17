/*
** EPITECH PROJECT, 2019
** 3DGameProgram
** File description:
** Renderer
*/

#include "Buffer.h"
#include "Color.h"
#include "Vector3.hpp"
#include "Matrix.h"
#include <iostream>
#include <vector>

#if !defined(RENDERER_H)
#define RENDERER_H

class Model;

class Camera;

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

    void PackData(Vector3i &index, Vector3f *primitive, std::vector<Vector3f> &vals);

    Camera *camera;

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

    void DrawTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c);
    void drawFlatTopTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c);
    void drawFlatBottomTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c);

    void DrawModel(Model *model);
};

#endif // RENDERER_H