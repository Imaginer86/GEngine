#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include "../Physics/Entity.h"
#include "../Physics/Ball.h"
#include "../Options.h"

namespace Core
{
	class FileReader
	{
		std::ifstream in;
	public:	
		FileReader(const char* filename){ in.open(filename, std::ios::in); }
		~FileReader(){ in.close(); }
		bool isOpen() { return in.is_open(); }
		bool isEof() {return in.eof(); }
		std::string	 getStr() { std::string str; in >> str; return str; }
		Vector3f getVector3f() { Vector3f v; in >> v; return v; }
		Vector4f getVector4f() { Vector4f v; in >> v; return v; }
		Color4f getColor4f() { Color4f c; in >> c; return c; }
		float getFloat() { float f; in >> f; return f; }
		size_t getNumber() { size_t num; in >> num; return num; }
		bool getBool() { bool b; in >> b; return b; }
	};

	bool LoadRawFile(const char* fileName, char* pHeightMap)
	{
		std::fstream in;
		in.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);

		if (in.is_open())
		{
			std::streampos size = in.tellg();
			in.seekg(0, std::ios::beg);
			in.read(reinterpret_cast<char*>(pHeightMap), size);
		}
		else
		{
			std::cerr << "Can't Find The Height Map!" << std::endl; //MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
			return false;
		}

		if (in.eof())
		{
			std::cerr << "Failed To Get Data!" << std::endl;// MessageBox(NULL, "Failed To Get Data!", "Error", MB_OK);
			return false;
		}
		in.close();
		return true;
	}

	size_t LoadEntitys(const char* filename, std::vector<Entity*>& Entitys)
	{
		size_t num_entitys = 0;
		std::fstream in;
		in.open(filename, std::ios::in);

		if (in.is_open())
		{
			in >> num_entitys;
			if (num_entitys > 0)
				Entitys.resize(num_entitys);
				//Entitys = new Entity[num_entitys];

			std::string name;			
			for (size_t i = 0; i < num_entitys; ++i)
			{
				Ball* entity = new Ball;				
				in >> name;
				if (name != "Ball")
				{
					//delete[] Entitys;
					return 0;
				}				
				in >> entity->m >> entity->pos >> entity->vel >> entity->r >> entity->color;
				Entitys[i] = entity;
			}
			in.close();
		}
		else return 0;
		return num_entitys;
	}

	bool LoadOptions(const char* filename, Options& options)
	{
		FileReader fr(filename);
		if (!fr.isOpen()) return false;
		
		while (!fr.isEof())
		{
			std::string pName = fr.getStr();
			if (pName == "width") options.width = fr.getNumber();
			else if (pName == "height") options.height = fr.getNumber(); 
			else if (pName == "fovy") options.fovy = fr.getFloat();
			else if (pName == "near") options.near = fr.getFloat();
			else if (pName == "far") options.far = fr.getFloat();
			else if (pName == "camera_pos") options.cameraPos = fr.getVector3f();
			else if (pName == "camera_angle") options.cameraAngle = fr.getFloat();
			else if (pName == "camera_axic") options.cameraaxis = fr.getVector3f();
			else if (pName == "fullscreen") options.fullscreen = fr.getBool();
			else if (pName == "move_scale") options.moveScale = fr.getFloat();
			else if (pName == "rotate_scale") options.rotateScale = fr.getFloat();
			else if (pName == "light") options.light = fr.getBool();
			else if (pName == "light_ambient") options.lightAmbient = fr.getVector4f();
			else if (pName == "light_diffuse") options.lightDiffuse = fr.getVector4f();
			else if (pName == "light_position") options.lightPosition = fr.getVector4f();
			else if (pName == "gravi_force") options.graviForce = fr.getBool();
			else if (pName == "collision") options.collision = fr.getBool();
			else { std::cerr << "Wrong options data: " << pName << std:: endl; return false;} 
		}
		return true;
	}
}