
#include "../Math/Vector3.hpp"

struct IShader
{
    Matrix4x4 MVP, MV, V, N;
    virtual ~IShader(){}
    virtual Vector3f vertex(
        const Vector3f &vertex, const Vector3f &normal,
        const Vector3f &textureVals, const Vector3f &tangent,
        int index, const Vector3f &light = Vector3f{1, 1, 1}) = 0;

    
    virtual Vector3f fragment(float u, float v) = 0;
};  