#include "EulerAngles.h"
#include "MathUtil.h"
#include "Quaternion.h"

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

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
    
}