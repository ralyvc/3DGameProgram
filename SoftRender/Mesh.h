
#if !defined(MESH_H)
#define MESH_H

#include "Vector3.hpp"
#include <vector>


struct Mesh
{
    int numVertices = 0;
    std::vector<Vector3f> vectices;
    std::vector<Vector3f> normals;
    std::vector<Vector3f> texels;
    std::vector<Vector3f> tangents;
    std::vector<Vector3f> biTangents;

    int numFaces = 0;
    std::vector<Vector3f> fNormals;
    std::vector<Vector3i> vectexIndices;
    std::vector<Vector3i> textureIndices;
    std::vector<Vector3i> normalsIndices;

    void BuildTangetSpace();
    void BuildFaceNormals();
};


#endif // MESH_H
