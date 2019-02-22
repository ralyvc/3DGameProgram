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
Quaternion Quaternion::Pow(float t) const
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

float Quaternion::Dot( const Quaternion &rhs) const
{
    return w * rhs.w + x * rhs.x + rhs.y * y + z * rhs.z;
}

float Quaternion::GetRotationAngle()
{
    float alpha = acos(w);
    return alpha * 2;
}

Vector3f Quaternion::GetRotationAxis()
{
    if (fabs(w) > 1 - kEpsilon)
    {
        return Vector3f(0,0,0);
    }
    float mult = 1.0f/(sqrt(1-w*w));
    return Vector3f(x * mult, y * mult, z * mult);
}

void Quaternion::Normalize()
{
    float mag = sqrt(w * w + x * x + y * y + z * z);
    
    if (mag > 0) {
        float oneOverMag = 1.0f / mag;
        w *= oneOverMag;
        x *= oneOverMag;
        y *= oneOverMag;
        z *= oneOverMag;
    }else
    {
        Identity();
    }
    
}

// slerp(q0,q1,t) = q0(q0^-1 * q1)^t = sin((1-t)*w)/sin(w)*q0 + sin(t*w)/sin(w) *q1 (w是两个四元数之间的“夹角”)
Quaternion Slerp(const Quaternion& q0,const Quaternion& q1,float t)
{
    if (t <=0 )
    {
        return q0;
    }
    if (t >= 1)
    {
        return q1;
    }
    float k0, k1;
    float cosOmega = q0.Dot(q1);
    int mult = 1;
    if (cosOmega < 0) {
        mult = -1;
        cosOmega = -cosOmega;
    }
    if (cosOmega > 1- kEpsilon) {
        k0 = 1 - t;
        k1 = t;
    }else
    {
        float sinOmega = sqrt(1 - cosOmega * cosOmega);
        float omega = atan2(sinOmega, cosOmega);
        float oneOverSinOmega = 1.0f / sinOmega;
        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    return Quaternion(q0.w * k0 + q1.w * k1 * mult, q0.x * k0 + q1.x * k1 * mult, q0.y * k0 + q1.y * k1 * mult, q0.z * k0 + q1.z * k1 * mult);
}