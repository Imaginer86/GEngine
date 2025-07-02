#pragma once

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <fstream>
#include <vector>
#include <string>

#include "Physics/Entity.h"
#include "Physics/Ball.h"
#include "Physics/Rectangle.h"
#include "Physics/ModelOBJ.h"
#include "Options.h"



namespace Core
{
	class FileReader
	{
		std::ifstream in;
	public:	
		FileReader(const char* filename){ in.open(filename, std::ios::in); }
		~FileReader(){ in.close(); }
		FileReader(const FileReader&) = delete; // Explicitly delete the copy constructor
		FileReader& operator=(const FileReader&) = delete; // Explicitly delete the assignment operator
		bool isOpen() { return in.is_open(); }
		bool isEof() {return in.eof(); }
		std::string getStr()
		{
			std::string str;
			in >> str;
			return str;
		}
		Vector3f getVector3f() { Vector3f v; in >> v; return v; }
		Vector4f getVector4f() { Vector4f v; in >> v; return v; }
		Color4f getColor4f() { Color4f c; in >> c; return c; }
		float getFloat() { float f; in >> f; return f; }
		size_t getNumber() { size_t num; in >> num; return num; }
		bool getBool() { bool b; in >> b; return b; }
	};

	bool LoadRawFile(const char* fileName, char* pHeightMap);

	size_t LoadEntitys(const char* filename, std::vector<Entity*>& Entitys);

	size_t LoadRandomEntitys(size_t numEntititys, const Vector3f& pos, float minR, float maxR, const Vector3f& vel, float minMR, float maxMR, std::vector<Entity*>& Entitys);

	bool LoadOptions(const char* filename, Options& options);


}