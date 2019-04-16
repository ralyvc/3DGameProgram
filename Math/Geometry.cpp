#include "Geometry.h"
#include "../SoftRender/Mesh.h"

AABox::AABox(const Mesh& mesh)
{
    Vector3f minVals(std::numeric_limits<float>::min());
    Vector3f maxVals(std::numeric_limits<float>::max());

    for (size_t i = 0; i < mesh.numVertices; i++)
    {
        
        for(size_t ax = 0; ax < 3; ax++)
        {
            maxVals.data[ax] = std::max(mesh.vectices[i].data[ax], maxVals.data[ax]);
            minVals.data[ax] = std::min(mesh.vectices[i].data[ax], minVals.data[ax]);
        }
        
    }
    minPoints = minVals;
    maxPoints = maxVals;
}

void AABox::Update(const Matrix4x4& mat)
{
    Vector3f vertices[8];
    vertices[0] = Vector3f(minPoints);
    vertices[1] = Vector3f(maxPoints.x, minPoints.y, minPoints.z);
    vertices[2] = Vector3f(minPoints.x, maxPoints.y, minPoints.z);
    vertices[3] = Vector3f(maxPoints.x, maxPoints.y, minPoints.z);

    vertices[4] = Vector3f(maxPoints.x, minPoints.y, maxPoints.z);
    vertices[5] = Vector3f(minPoints.x, maxPoints.y, maxPoints.z);
    vertices[6] = Vector3f(minPoints.x, minPoints.y, maxPoints.z);    
    vertices[7] = Vector3f(maxPoints);
}

Line::Line(const Vector3f& p0,const Vector3f p1)
{
    this->p0 = p0;
    this->p1 = p1;
    v = p1 - p0;
}

Vector3f Line::Lerp(float t)
{
    if (t <= 0 )
    {
        return p0;
    }else if (t >= 1)
    {
        return p1;
    }
    return p0 + v * t;
}

int Plane::PointInPlane(const Vector3f& p)
{
    Vector3f v = p - point;
    return normal.dotProduct(v);
}