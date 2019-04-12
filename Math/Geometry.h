#ifndef GEOMETRY_H
#define GEOMETRY_H

//Headers
#include "Matrix.h"
#include "Vector3.hpp"

// //参数化直线
// struct ParamLine
// {

// };

class Line
{
  public:
    Line(const  Vector3f& p0,const Vector3f p1);
    Line(Line &&) = default;
    Line(const Line &) = default;
    Line &operator=(Line &&) = default;
    Line &operator=(const Line &) = default;
    ~Line(){};
    Vector3f Lerp(float t);

  private:
    Vector3f p0;
    Vector3f p1;
    Vector3f v; //线段的方向向量
};


class Plane
{
public:
    Plane(const Vector3f &n,const Vector3f &p):normal(n),point(p){};
    Plane(Plane &&) = default;
    Plane(const Plane &) = default;
    Plane &operator=(Plane &&) = default;
    Plane &operator=(const Plane &) = default;

    int PointInPlane(const Vector3f& p);

  private:
    Vector3f normal;
    Vector3f point;
};



#endif