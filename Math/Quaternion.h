#include "Vector3.hpp"

#if !defined(QUATERNION_H)
#define QUATERNION_H

class Quaternion
{
  public:
    float w, x, y, z;

  public:
    Quaternion();
    Quaternion(Quaternion &&) = default;
    Quaternion(const Quaternion &) = default;
    Quaternion &operator=(Quaternion &&) = default;
    Quaternion &operator=(const Quaternion &) = default;
    ~Quaternion();
    void Identity()
    {
        w = 1.0f;
        x = y = z = 0.0f;
    }

    void RotateAboutAxis(const Vector3f &axis, float theta);
    

  private:
};

Quaternion::Quaternion()
{
}

Quaternion::~Quaternion()
{
}

#endif // QUATERNION_H
