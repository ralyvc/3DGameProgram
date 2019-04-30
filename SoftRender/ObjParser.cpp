#include "ObjParser.h"
using namespace std;
//https://www.jianshu.com/p/f7f3e7b6ebf5

Mesh *BuildMeshFromFile( string path)
{
    ifstream file;
    file.open(path.c_str());
    auto mesh = LoadFile( file);
    file.close();
    return mesh;
}

vector<string> SplitStr(string &str, char delim)
{
    stringstream ss(str);
    string token;
    vector<string> splitString;

    while (getline(ss, token, delim))
    {
        if (token == "")
        {
            splitString.push_back("0");
        }
        else
        {
            splitString.push_back(token);
        }
    }
    return splitString;
}

Mesh * LoadFile( std::ifstream &file)
{
    string line, key, x, y, z;
    Vector3i indices[3];
    char delimeter = '/';
    Mesh *mesh = new Mesh();
    while (!file.eof())
    {
        getline(file, line);
        istringstream iss(line);
        iss >> key;
        if (key == "v")
        {
            iss >> x >> y >> z;
            Vector3f vec(stof(x), stof(y), stof(z));
            mesh->vectices.push_back(vec);
        }
        else if (key == "vn")
        {
            iss >> x >> y >> z;
            Vector3f vec(stof(x), stof(y), stof(z));
            mesh->normals.push_back(vec);
        }
        else if (key == "vt")
        {
            iss >> x >> y ;
            Vector3f vec(stof(x), stof(y),0);
            mesh->texels.push_back(vec);
        }
        else if (key == "f")  //index data
        {
            iss >> x >> y >> z;
            auto splitx = SplitStr(x, delimeter);
            auto splity = SplitStr(y, delimeter);
            auto splitz = SplitStr(z, delimeter);
            for (size_t i = 0; i < splitx.size(); i++)
            {
                indices[i] = Vector3i(stoi(splitx[i]) - 1, stoi(splity[i]) - 1, stoi(splitz[i]) - 1);
            }
            mesh->vectexIndices.push_back(indices[0]);
            mesh->textureIndices.push_back(indices[1]);
            mesh->normalsIndices.push_back(indices[2]);
        }
    }
    mesh->numVertices = mesh->vectices.size();
    mesh->numFaces = mesh->vectexIndices.size();
    mesh->BuildFaceNormals();
    mesh->BuildTangetSpace();
    return mesh;
}