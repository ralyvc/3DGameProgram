
#if !defined(MODEL_H)
#define MODEL_H
#include "EulerAngles.h"
#include "Matrix.h"
#include "Mesh.h"
#include "ObjParser.h"
#include "Vector3.hpp"
#include <iostream>
struct TransformParameters;

class Model
{
public:
float theta = 0;
  Model(const std::string meshPath)
  {
    
    _mesh = BuildMeshFromFile(meshPath);
    Position = Vector3f(0, 0, 0);
    q = AngleAxis(kPiOver2, Vector3f(1, 0, 0));

    Scale = Vector3f(1, 1, 1);
  };
  Model(Model &&) = default;
  Model(const Model &) = default;
  Model &operator=(Model &&) = default;
  Model &operator=(const Model &) = default;
  ~Model()
  {

    if (_mesh != nullptr)
    {
      delete _mesh;
      _mesh = nullptr;
    }
  };
  void Update(unsigned int delta)
  {

    //q =  q*AngleAxis(kPi / 5.0 * delta / 1000, Vector3f(0, 1, 0)) ;

    //mCam = RotationMatrix(rot).Transpose() * TranslateMatrix(-pos.x, -pos.y, -pos.z);
  };

  Mesh *GetMesh() { return _mesh; }
  Matrix4x4 GetModelMatrix()
  {
    return ScaleMatrix(Scale.x, Scale.y, Scale.z) * RotationMatrix( q) * TranslateMatrix(Position.x, Position.y, Position.z);
  }

  Vector3f Position;
  Quaternion q;
  Vector3f Scale;

private:
  Mesh *_mesh;
};

#endif // MODEL_H
