#include "Renderer.h"
#include "Camera.h"
#include "Model.h"
#include "Scene.h"
#include "Shader.h"
#include "Vector3.hpp"
#include <cstring>

Renderer::Renderer(int width, int height, Scene *s)
{
    _width = width;
    _height = height;
    pixBuffer = new Buffer<uint32_t>(_width, _height);
    this->scene = s;
    camera = s->GetCamera();
};
void Renderer::clear()
{
    pixBuffer->clear();
}

void Renderer::putPixel(int x, int y, const Color &color)
{

    if (x >= 0 && x < _width && y >= 0 && y < _height)
    {
        /* code */
        (*pixBuffer)(x, y) = color.uint32();
    }
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
        x0 = x1 + (_height - 1 - y1) * k1;
        y0 = _height - 1;
        break;
    case Renderer::ClipCodeW:
        y0 = y1 + (0 - x1) * k;
        x0 = 0;
        break;
    case Renderer::ClipCodeE:
        y0 = y1 + (_width - 1 - x1) * k;
        x0 = _width - 1;
        break;
    case Renderer::ClipCodeNE:
        x0 = x1 + (0 - y1) * k1;
        y0 = 0;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (_width - 1 - x1) * k;
            x0 = _width - 1;
        }
        break;
    case Renderer::ClipCodeSE:
        x0 = x1 + (_height - 1 - y1) * k1;
        y0 = _height;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (_width - 1 - x1) * k;
            x0 = _width - 1;
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
        x0 = x1 + (_height - 1 - y1) * k1;
        y0 = _height - 1;
        if (x0 < 0 || x0 >= _width)
        {
            y0 = y1 + (0 - x1) * k;
            x0 = 0;
        }
        break;
    default:
        break;
    }

    if (x0 < 0 || x0 >= _width || y0 < 0 || y0 >= _height)
    {
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
        x1 = x0 + (_height - 1 - y0) * k1;
        y1 = _height - 1;
        break;
    case Renderer::ClipCodeW:
        y1 = y0 + (0 - x0) * k;
        x1 = 0;
        break;
    case Renderer::ClipCodeE:
        y1 = y0 + (_width - 1 - x0) * k;
        x1 = _width - 1;
        break;
    case Renderer::ClipCodeNE:
        x1 = x0 + (0 - y0) * k1;
        y1 = 0;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (_width - 1 - x0) * k;
            x1 = _width - 1;
        }
        break;
    case Renderer::ClipCodeSE:
        x1 = x0 + (_height - 1 - y0) * k1;
        y1 = _height - 1;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (_width - 1 - x0) * k;
            x1 = _width - 1;
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
        x1 = x0 + (_height - 1 - y0) * k1;
        y1 = _height - 1;
        if (x1 < 0 || x1 >= _width)
        {
            y1 = y0 + (0 - x0) * k;
            x1 = 0;
        }
        break;
    default:
        break;
    }
    if (x1 < 0 || x1 >= _width || y1 < 0 || y1 >= _height)
    {
        return false;
    }
    return true;
}

Buffer<uint32_t> *Renderer::GetBuffer() const
{
    return pixBuffer;
}

void Renderer::drawFlatTopTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c)
{
    float dxLeft = v3.x - v1.x;
    float dyLeft = v3.y - v1.y;
    float sxLeft = 0;
    if (dyLeft != 0)
    {
        sxLeft = float(dxLeft) / dyLeft;
    }
    float dxRigth = v3.x - v2.x;
    float dyRight = v3.y - v2.y;
    float sxRight = 0;
    if (dyRight != 0)
    {
        sxRight = float(dxRigth) / dyRight;
    }
    float xl = v1.x;
    float xr = v2.x;
    int endY = v3.y;

    if (v1.y < 0)
    {
        xl = v1.x - dxLeft * v1.y;
        xr = v2.x - dxRigth * v1.y;
    }
    if (v3.y >= _height)
    {
        endY = _height;
    }
    if (xl > xr)
    {
        std::swap(xl, xr);
        std::swap(sxLeft, sxRight);
    }

    if (v1.x >= 0 && v1.x < _width && v2.x >= 0 && v2.x < _width && v3.x >= 0 && v3.x < _width)
    {
        for (size_t i = v1.y; i <= endY; i++)
        {
            pixBuffer->SetBuffer(xl, i, xr, i, c.data);
            xl += sxLeft;
            xr += sxRight;
        }
    }
    else
    {
        float left, right;
        for (size_t i = v1.y; i <= endY; i++)
        {
            left = xl;
            right = xr;
            xl += sxLeft;
            xr += sxRight;
            if (left < 0)
            {
                left = 0;
                if (right < 0)
                {
                    continue;
                }
            }
            if (right >= _width)
            {
                right = _width;
                if (left >= _width)
                {
                    continue;
                }
            }
            pixBuffer->SetBuffer(left, i, right, i, c.data);
        }
    }
}

void Renderer::drawFlatBottomTriangle(const Vector3i &v1, const Vector3i &v2, const Vector3i &v3, const Color &c)
{
    float dxLeft = v2.x - v1.x;
    float dyLeft = v2.y - v1.y;
    float sxLeft = 0;
    if (dyLeft != 0)
    {
        sxLeft = float(dxLeft) / dyLeft;
    }
    float dxRigth = v3.x - v1.x;
    float dyRight = v3.y - v1.y;
    float sxRight = 0;
    if (dyRight != 0)
    {
        sxRight = float(dxRigth) / dyRight;
    }
    float xl = v1.x;
    float xr = v1.x;
    int endY = v3.y;

    if (v1.y < 0)
    {
        xl = v1.x - dxLeft * v1.y;
        xr = v1.x - dxRigth * v1.y;
    }
    if (v3.y >= _height)
    {
        endY = _height;
    }
    if (xl > xr)
    {
        std::swap(xl, xr);
        std::swap(sxLeft, sxRight);
    }

    if (v1.x >= 0 && v1.x < _width && v2.x >= 0 && v2.x < _width && v3.x >= 0 && v3.x < _width)
    {
        for (size_t i = v1.y; i <= endY; i++)
        {
            pixBuffer->SetBuffer(xl, i, xr, i, c.data);
            xl += sxLeft;
            xr += sxRight;
        }
    }
    else
    {
        float left, right;
        for (size_t i = v1.y; i <= endY; i++)
        {
            left = xl;
            right = xr;
            xl += sxLeft;
            xr += sxRight;
            if (left < 0)
            {
                left = 0;
                if (right < 0)
                {
                    continue;
                }
            }
            if (right >= _width)
            {
                right = _width;
                if (left >= _width)
                {
                    continue;
                }
            }
            pixBuffer->SetBuffer(left, i, right, i, c.data);
        }
    }
}

void Renderer::PackData(Vector3i &index, Vector3f *primitive, std::vector<Vector3f> &vals)
{

    for (size_t i = 0; i < 3; i++)
    {
        primitive[i] = vals[index.data[i]];
    }
}

void Renderer::DrawModel(Model *model)
{
    auto mesh = model->GetMesh();
    auto vIndices = &mesh->vectexIndices;
    auto tIndices = &mesh->textureIndices;
    auto nIndices = &mesh->normalsIndices;
    auto fNormals = &mesh->fNormals;

    auto vertices = &mesh->vectices;
    auto texels = &mesh->texels;
    auto normals = &mesh->normals;
    auto tangents = &mesh->tangents;

    int numFaces = mesh->numFaces;
    FlatShader shader;
    shader.M = model->GetModelMatrix();
    shader.MV = shader.M * camera->mCam;
    shader.V = camera->mCam;
    shader.MVP = shader.MV * camera->mPer;

    for (size_t i = 0; i < numFaces; i++)
    {
        Vector3f trianglePrimitive[3], normalPrimitive[3], uvPrimitive[3], tangentPrimitive[3];
        PackData((*vIndices)[i], trianglePrimitive, *vertices);

        for (size_t i = 0; i < 3; i++)
        {
            trianglePrimitive[i] = shader.vertex(trianglePrimitive[i], Vector3f(0, 0, 1), Vector3f(0, 0, 1), Vector3f(0, 0, 0), i);
            trianglePrimitive[i].perspectiveDivide();
        }
        DrawLine(trianglePrimitive[0], trianglePrimitive[1], Color::Red());
        DrawLine(trianglePrimitive[1], trianglePrimitive[2], Color::Red());
        DrawLine(trianglePrimitive[0], trianglePrimitive[2], Color::Red());
    }
}

void Renderer::Update(unsigned int delta)
{
    clear();
    auto models = scene->GetVisibleModels();
    while (!models->empty())
    {
        DrawModel(models->front());
        models->pop();
    }
}