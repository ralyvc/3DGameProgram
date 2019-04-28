
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
  Model(const std::string meshPath)
  {
    _mesh = BuildMeshFromFile(meshPath);
    Position = Vector3f(0, 0, 0);
    dir = EulerAngles(90, 0, 0);
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
  void Update(unsigned int delta){};

  Mesh *GetMesh() { return _mesh; }
  Matrix4x4 GetModelMatrix()
  {
    return ScaleMatrix(Scale.x, Scale.y, Scale.z) * RotationMatrix(dir) * TranslateMatrix(Position.x, Position.y, Position.z);
  }

  Vector3f Position;
  EulerAngles dir;
  Vector3f Scale;

private:
  Mesh *_mesh;
};

#endif // MODEL_H
