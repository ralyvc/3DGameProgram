/*
** EPITECH PROJECT, 2019
** 3DGameProgram
** File description:
** Renderer
*/
#include "Buffer.h"
#include "Color.h"
#include "Matrix.h"
#include "Vector3.hpp"
#include <iostream>
#include <queue>
#include <vector>

#if !defined(RENDERER_H)
#define RENDERER_H

class Model;
class Scene;
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
    void clear();
    Scene *scene;

  public:
    Renderer(int width, int height,Scene* s);
    void BresenhamLine1(int x0, int y0, int x1, int y1, const Color &c);
    void BresenhamLine(int x0, int y0, int x1, int y1, const Color &c);
    Buffer<uint32_t> *GetBuffer() const;
    virtual ~Renderer() { delete pixBuffer; };

    bool ClipLine(int &x0, int &y0, int &x1, int &y1) const;

    void DrawTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c);
    void drawFlatTopTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c);
    void drawFlatBottomTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c);
    void drawLine(int x0, int y0, int x1, int y1, const Color &c);
    void DrawLine(const Vector3f &p0, const Vector3f &p1, const Color &c)
    {
        float alpha = 0.5 * _width - 0.5;
        float beta = 0.5 * _height - 0.5;
        int x0 = alpha + alpha * p0.x;
        int y0 = beta - beta * p0.y;
        int x1 = alpha + alpha * p1.x;
        int y1 = beta - beta * p1.y;

        drawLine(x0, y0, x1, y1, c);
    }

    void DrawModel(Model *model);

    void Update(unsigned int delta);

    Scene *GetScene() { return scene; };

    std::queue<Model *> renderQueue;
};

#endif // RENDERER_H