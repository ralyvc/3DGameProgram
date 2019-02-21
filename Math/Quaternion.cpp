#include "Quaternion.h"
#include "MathUtil.h"

Quaternion AngleAxis(float theta, Vector3f axis)
{
    float thetaOver2 = theta * 0.5f;
    float sinThetaOver2 = sin(thetaOver2);
    return Quaternion(cos(thetaOver2), axis.x * sinThetaOver2, axis.y * sinThetaOver2, axis.z * sinThetaOver2);
}

Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
    //return new Quaternion((float) ((double) lhs.w * (double) rhs.x + (double) lhs.x * (double) rhs.w + (double) lhs.y * (double) rhs.z - (double) lhs.z * (double) rhs.y),
    //(float) ((double) lhs.w * (double) rhs.y + (double) lhs.y * (double) rhs.w + (double) lhs.z * (double) rhs.x - (double) lhs.x * (double) rhs.z),
    //(float) ((double) lhs.w * (double) rhs.z + (double) lhs.z * (double) rhs.w + (double) lhs.x * (double) rhs.y - (double) lhs.y * (double) rhs.x),
    //(float) ((double) lhs.w * (double) rhs.w - (double) lhs.x * (double) rhs.x - (double) lhs.y * (double) rhs.y - (double) lhs.z * (double) rhs.z));
    return Quaternion(w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
                      w * rhs.x + x * rhs.w + z * rhs.y - y * rhs.z,
                      w * rhs.y + y * rhs.w + x * rhs.z - z * rhs.x,
                      w * rhs.z + z * rhs.w + y * rhs.x - x * rhs.y

    );
}

Quaternion &Quaternion::operator*=(const Quaternion &rhs)
{
    *this = *this * rhs;
    return *this;
}

Quaternion Quaternion::Conjugate()
{
    return Quaternion(w, -x, y, z);
}

//四元数求幂  logq =(0,theta/2*n) exp(q) = (cos(theta/2),n*sin(theta/2))
//q^t = exp(t*logq)
Quaternion Quaternion::Pow(float t)
{
    //检查单位四元数，防止除零
    if (fabs(w) > 1 - kEpsilon)
    {
        return Quaternion(*this);
    }

    float alpha = acos(w);
    float newAlpha = alpha * t;
    float mult = sin(newAlpha) / sin(alpha);
    return Quaternion(cos(newAlpha), x * mult, y * mult, z * mult);
}

float Dot(const Quaternion &lhs, const Quaternion &rhs)
{
    return lhs.w * rhs.w + lhs.x + rhs.x + rhs.y + lhs.y + lhs.z * rhs.z;
}