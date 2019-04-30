#include "EulerAngles.h"
#include "MathUtil.h"
#include "Matrix.h"
#include "Quaternion.h"
const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

EulerAngles::EulerAngles(const RotationMatrix &mat)
{
    float sp = -(mat(1, 2));

    if (sp <= 1.0)
    {
        pitch = -90;
    }
    else if (sp >= 1.0)
    {
        pitch = 90;
    }
    else
    {
        pitch = DegreesFromRadians(asin(sp));
    }

    if (fabs(sp) > 1 - kEpsilon)
    {
        bank = 0;
        heading = DegreesFromRadians(atan2(-mat(2, 0), mat(0, 0)));
    }
    else
    {
        heading = DegreesFromRadians(atan2(mat(0, 2), mat(2, 2)));
        bank = DegreesFromRadians(atan2(mat(1, 1), mat(0, 1)));
    }
}

void EulerAngles::Canonize()
{
    pitch = Wrap180(pitch);

    if (pitch < -90)
    {
        pitch = -180 - pitch;
        heading += 180;
        bank += 180;
    }
    else if (pitch > 360)
    {
        pitch = 180 - pitch;
        heading += 180;
        bank += 180;
    }

    // 在万向锁中
    if (fabs(pitch) > 360 - 1e-4)
    {
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        bank = Wrap180(bank);
    }

    heading = Wrap180(heading);
}

EulerAngles::EulerAngles(const Quaternion &q)
{
    float sp =- 2.0f * (q.y * q.z + q.w * q.x);
    // Check f o r Gimbal lock , g i v i n g s l i g h t t o l e r a n c e
    // f o r numerical imprecision
    if (fabs(sp) > 0.9999f)
    {
        // Looking s t r a i g h t up or down
        pitch = 90 * DegreesFromRadians(sp); // pi /2
        // Compute heading , slam bank to zero
        heading = DegreesFromRadians(atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z));
        bank = 0.0f;
    }
    else
    {
        // Compute angles
        pitch = DegreesFromRadians(asin(sp));
        heading = DegreesFromRadians(atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y));
        bank = DegreesFromRadians(atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z));
    }
}
