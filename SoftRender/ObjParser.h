
#if !defined(OBJ_PARSER_H)
#define OBJ_PARSER_H
#include "Mesh.h"  
#include <fstream>
#include <sstream>

Mesh &BuildMeshFromFile(Mesh &mesh, std::string path);

bool FileExists(std::string path);

void LoadFile(Mesh &mesh, std::ifstream &file);

std::vector<std::string> SplitStr(std::string &str, char delim);

#endif // OBJ_PARSER_H
