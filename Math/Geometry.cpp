#include "Geometry.h"

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