#include "Vector3.hpp"
#include "MathUtil.h"
#if !defined(QUATERNION_H)
#define QUATERNION_H
class RotationMatrix;
class Quaternion
{
public:
  float w, x, y, z;

public:
  Quaternion() { Identity(); }
  Quaternion(float ww, float xx, float yy, float zz) : w(ww), x(xx), y(yy), z(zz) {}
  Quaternion(Quaternion &&) = default;
  Quaternion(const Quaternion &) = default;
  Quaternion &operator=(Quaternion &&) = default;
  Quaternion &operator=(const Quaternion &) = default;
  bool operator==(const Quaternion &other) const
  {
    return fabs(w - other.w) < kEpsilon && fabs(x - other.x) < kEpsilon && fabs(y - other.y) < kEpsilon && fabs(z - other.z) < kEpsilon;
  }
  bool operator!=(const Quaternion &other) const
  {
    return  !(*this == other);
  }
  Quaternion(const RotationMatrix &mat);
  
  void Identity()
  {
    w = 1.0f;
    x = y = z = 0.0f;
  }

  //四元数叉乘运算
  Quaternion operator*(const Quaternion &a) const;

  Quaternion &operator*=(const Quaternion &a);

  //四元数共轭，即与原四元数旋转相反的四元数
  Quaternion Conjugate();

  //四元数求幂，即变为原来角度的t倍 logq =(0,theta/2*n) exp(q) = (cos(theta/2),n*sin(theta/2))
  //q^t = exp(t*logq)
  Quaternion Pow(float t) const;
  //点乘
  float Dot( const Quaternion &rhs) const;

  float GetRotationAngle();

  Vector3f GetRotationAxis();

  void Normalize();

private:
};

extern Quaternion AngleAxis(float angle, Vector3f axis);

extern Quaternion Slerp(const Quaternion &q0, const Quaternion &q1,float t);
#endif // QUATERNION_H
