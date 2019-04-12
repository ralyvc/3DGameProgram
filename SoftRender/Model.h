
#if !defined(MODEL_H)
#define MODEL_H
#include <iostream>
#include "../Math/Vector3.hpp"
#include "Mesh.h"
#include "ObjParser.h"
struct TransformParameters;


class Model
{
public:
    Model(const TransformParameters& param,const std::string meshPath )
    {
        BuildMeshFromFile(_mesh, meshPath);
    };
    Model(Model &&) = default;
    Model(const Model &) = default;
    Model &operator=(Model &&) = default;
    Model &operator=(const Model &) = default;
    ~Model(){};

private:
  Mesh _mesh;
};


#endif // MODEL_H
