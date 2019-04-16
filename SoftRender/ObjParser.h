
#if !defined(OBJ_PARSER_H)
#define OBJ_PARSER_H
#include "Mesh.h"  
#include <fstream>
#include <sstream>

extern Mesh *BuildMeshFromFile( std::string path);

extern bool FileExists(std::string path);

extern Mesh *LoadFile( std::ifstream &file);

extern std::vector<std::string> SplitStr(std::string &str, char delim);

#endif // OBJ_PARSER_H
