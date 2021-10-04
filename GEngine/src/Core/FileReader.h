#pragma once
//#include "../Render/Model.h"
#include "../Render/ModelM.h"

bool LoadRawFile(const char* fileName, unsigned char* pHeightMap);
//void ReadModelOBJ(Model &model, const char *fileName);
bool ReadModelOBJM(ModelM &model, const char *fileName);
//int GetSceneNum(const char* fileName);
//char* filetobuf(char *file);