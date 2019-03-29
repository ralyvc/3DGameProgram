#include "Mesh.h"
using namespace std;
void Mesh::BuildFaceNormals()
{
    for (size_t i = 0; i < numFaces; i++)
    {
        auto indices = vectexIndices[i];
        auto n1 = vectices[indices.y] - vectices[indices.x];
        auto n2 = vectices[indices.z] - vectices[indices.x];
        fNormals.push_back(n1.crossProduct(n2).normalized());
    }
}

// 法线贴图和切线空间 https://blog.csdn.net/sixdaycoder/article/details/79015765
void Mesh::BuildTangetSpace()
{
    vector<vector<Vector3f>> tmpTangents(numVertices);
    vector<vector<Vector3f>> tmpBiTangents(numVertices);
    Vector3f tangent, biTangent;

    for (size_t i = 0; i < numFaces; i++)
    {
        auto vIndices = vectexIndices[i];
        auto tIndices = textureIndices[i];
        auto edge1 = vectices[vIndices.y] - vectices[vIndices.x];
        auto edge2 = vectices[vIndices.z] - vectices[vIndices.x];
        auto deltaUV1 = texels[tIndices.y] - texels[tIndices.x];
        auto deltaUV2 = texels[tIndices.z] - texels[tIndices.x];

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x - deltaUV1.y);
        tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent.normalized();

        biTangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        biTangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        biTangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        biTangent.normalized();

        tmpTangents[vIndices.data[0]].push_back(tangent);
        tmpTangents[vIndices.data[1]].push_back(tangent);
        tmpTangents[vIndices.data[2]].push_back(tangent);

        tmpBiTangents[vIndices.data[0]].push_back(biTangent);
        tmpBiTangents[vIndices.data[1]].push_back(biTangent);
        tmpBiTangents[vIndices.data[2]].push_back(biTangent);
    }

//求平均
    for (int j = 0; j < numVertices; ++j)
    {
        int count1 = 0, count2 = 0;

        Vector3f temp1{0};
        while (!tmpTangents[j].empty())
        {
            ++count1;
            temp1 += tmpTangents[j].back();
            if (temp1.x == 0 && temp1.y == 0 && temp1.z == 0)
            {
                temp1 = tmpTangents[j].back();
            }
            tmpTangents[j].pop_back();
        }

        temp1 = temp1 * (1.0f / count1);
        tangents.push_back(temp1);

        Vector3f temp2{0};
        while (!tmpBiTangents[j].empty())
        {
            ++count2;
            temp2 += tmpBiTangents[j].back();
            if (temp2.x == 0 && temp2.y == 0 && temp2.z == 0)
            {
                temp2 = tmpBiTangents[j].back();
            }
            tmpBiTangents[j].pop_back();
        }
        temp2 = temp2 * (1.0f / count2);
        biTangents.push_back(temp2);
    }

    for(int k = 0; k < numFaces; ++k){
        Vector3i vIndices = vectexIndices[k];
        Vector3i nIndices = normalsIndices[k];

        //Per vertex
        Vector3f tangentV0 = tangents[vIndices.data[0]]; 
        Vector3f tangentV1 = tangents[vIndices.data[1]];
        Vector3f tangentV2 = tangents[vIndices.data[2]];

        Vector3f normalV0 = normals[nIndices.data[0]]; 
        Vector3f normalV1 = normals[nIndices.data[1]];
        Vector3f normalV2 = normals[nIndices.data[2]];

        Vector3f biTangentV0 = biTangents[vIndices.data[0]]; 
        Vector3f biTangentV1 = biTangents[vIndices.data[1]];
        Vector3f biTangentV2 = biTangents[vIndices.data[2]];

        //Renormalizing
        tangentV0  = (tangentV0 - (normalV0*tangentV0.dotProduct(normalV0))).normalized();
        tangentV1  = (tangentV1 - (normalV1*tangentV1.dotProduct(normalV1))).normalized();
        tangentV2  = (tangentV2 - (normalV2*tangentV2.dotProduct(normalV2))).normalized();

        //Correcting handedness
        if (biTangentV0.dotProduct(normalV0.crossProduct(tangentV0)) < 0.0f){
            tangentV0 = tangentV0  * -1.0f;
        }

        if (biTangentV1.dotProduct(normalV1.crossProduct(tangentV1)) < 0.0f){
            tangentV1 = tangentV1  * -1.0f;
        }

        if (biTangentV2.dotProduct(normalV2.crossProduct(tangentV2)) < 0.0f){
            tangentV2 = tangentV2  * -1.0f;
        }

        tangents[vIndices.data[0]]  = tangentV0;
        tangents[vIndices.data[1]]  = tangentV1; 
        tangents[vIndices.data[2]]  = tangentV2; 

    }
}