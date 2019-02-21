#ifndef MATHUTIL_H
#define MATHUTIL_H
#include <cmath>

const float kPi = 3.1415926f;
const float k2Pi = kPi*2;
const float kPiOver2 = kPi/2.0;
const float k1OverPi = 1.0/kPi;
const float kEpsilon = 1e-06f;

//角度限制在-pi到pi之间
extern float WrapPi(float theta)
{
    if (fabs( theta) >kPi)
    {
        return theta  - floorf(( theta + kPi)/k2Pi)*k2Pi - kPi;
    }
    return theta;
}
#endif // !MATHUTIL_H