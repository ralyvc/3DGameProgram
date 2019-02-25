#include "EulerAngles.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "Matrix.h"
const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

EulerAngles::EulerAngles(const RotationMatrix& mat)
{
    float sp = -(mat(2, 1));
    
    if (sp <= 1.0) {
        pitch = -kPiOver2;
    }else if (sp >= 1.0)
    {
        pitch = kPiOver2;
    }else
    {
        pitch = asin(sp);
    }
    
    if (fabs(sp)>1-kEpsilon) {
        bank = 0;
        heading = atan2(-mat(0, 2), mat(0, 0));
    }
    else
    {
        heading = atan2(mat(2, 0), mat(2, 2));
        bank = atan2(mat(0, 1), mat(1, 1));
    }
    
    
}

void EulerAngles::Canonize()
{
    pitch = WrapPi(pitch);

    if (pitch < -kPiOver2)
    {
        pitch = -kPi - pitch;
        heading += kPi;
        bank += kPi;
    }
    else if (pitch > kPiOver2)
    {
        pitch = kPi - pitch;
        heading += kPi;
        bank += kPi;
    }

    // 在万向锁中
    if (fabs(pitch) > kPiOver2 - 1e-4)
    {
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        bank = WrapPi(bank);
    }

    heading = WrapPi(heading);

}

Quaternion EulerAngles::ToQuaternion()
{
    return Quaternion(1, 0, 0, 0);
}
