#ifndef MATHUTIL_H
#define MATHUTIL_H
#include <cmath>

const float kPi = 3.1415926f;
const float k2Pi = kPi * 2;
const float kPiOver2 = kPi / 2.0;
const float k1OverPi = 1.0 / kPi;
const float kEpsilon = 1e-06f;

//角度限制在-pi到pi之间
static float WrapPi(float theta)
{
    if (fabs(theta) > kPi)
    {
        return theta - floorf((theta + kPi) / k2Pi) * k2Pi - kPi;
    }
    return theta;
}

static inline bool FloatEqual(float a, float b)
{
    return fabsf(a - b) <= kEpsilon;
}

static inline bool EqualZero(float a)
{
    return fabsf(a) <= kEpsilon;
}

static inline float RadiansFromDegrees(float degrees)
{
    return kPi * degrees / 180.0f;
}

static inline float DegreesFromRadians(float radians)
{
    return 180.0f * radians / kPi;
}

#endif // !MATHUTIL_H