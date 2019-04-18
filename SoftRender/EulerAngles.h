#include "Vector3.hpp"
#if !defined(ENLER_ANGLES_H)
#define ENLER_ANGLES_H
class Quaternion;
class RotationMatrix;
class EulerAngles
{
public:
  union {
    float heading, y;
  };
  union {
    float pitch, x;
  };
  union {
    float bank, z;
  };

public:
  EulerAngles() {}
  EulerAngles(const RotationMatrix &mat);
  EulerAngles(float h, float p, float b) : heading(h), pitch(p), bank(b) {}
  EulerAngles(const Vector3f &vec) : y(vec.y), x(vec.x), z(vec.z) {}
  EulerAngles(EulerAngles &&) = default;
  EulerAngles(const EulerAngles &) = default;
  EulerAngles &operator=(EulerAngles &&) = default;
  EulerAngles &operator=(const EulerAngles &) = default;

  void Identity()
  {
    pitch = bank = heading = 0.0f;
  }

  void Canonize();
  Quaternion ToQuaternion();

private:
};

extern const EulerAngles kEulerAnglesIdentity;

#endif // ENLER_ANGLES_H
