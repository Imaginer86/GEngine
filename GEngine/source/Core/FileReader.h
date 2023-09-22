#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>


#include "../Physics/Entity.h"
#include "../Physics/Ball.h"
#include "../Physics/Rectangle.h"
#include "../Physics/ModelOBJ.h"
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
		void getStr(char* strc)
		{
			std::string str;
			in >> str;
			//strc = new char[str.length() + 1]; 
			//strcpy_s(strc, str.length() + 1, str.c_str());
			int i = 0;
			for (; i < str.length(); i++) strc[i] = str[i];
			strc[i] = '\0';
		}
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

		std::list<Entity*> lEntitys;

		if (in.is_open())
		do
		{
			std::string name;
			in >> name;
			if (name == "Ball")
			{
				num_entitys++;
				Ball* entity = new Ball;
				in >> entity->m >> entity->pos >> entity->vel >> entity->r >> entity->color;
				lEntitys.push_back(entity);
			}
			else if (name == "Rectangle" || name == "Rec") //Fus
			{
				num_entitys++;
				Rectangle* entity = new Rectangle;
				Vector3f axic;
				float angle;
				in >> entity->m >> entity->pos >> entity->vel >> angle >> axic >> entity->w >> entity->h >> entity->color;
				entity->q = Quaternion(angle, axic);
				lEntitys.push_back(entity);
			}
			else if (name == "Model")
			{
				num_entitys++;
				ModelOBJ* entity = new ModelOBJ;
				in >> entity->m >> entity->pos >> entity->vel >> entity->color;
				std::string path, fileName;
				bool isQuad;
				bool isNoTextIndex;
				in >> path >> fileName >> isQuad >> isNoTextIndex;				
				if (!entity->Load(path.c_str(), fileName.c_str(), isQuad, isNoTextIndex))
				{
					std::cerr << "Can't load obj" << std::endl;
					return 0;
				}
				entity->Save((path + '/' + fileName + ".objm").c_str());
				lEntitys.push_back(entity);
			}
			else return 0;
		} while (!in.eof());
		in.close();

		Entitys.resize(num_entitys);
		int i = 0;
		for (auto entity : lEntitys) { Entitys[i] = entity; ++i; }

		/*
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
					//return 0;
					num_entitys = 0;
					break;
				}				
				in >> entity->m >> entity->pos >> entity->vel >> entity->r >> entity->color;
				Entitys[i] = entity;
			}
			in.close();
		}
		else return 0;
		*/
		return num_entitys;
	}

	size_t LoadRandomEntitys(size_t numEntititys, const Vector3f& pos, const Vector3f& size, const Vector3f& vel, size_t minMR, size_t maxMR, std::vector<Entity*>& Entitys)
	{
		Entitys.resize(numEntititys + 1);
		size_t i = 1;
		for (; i <= (numEntititys + 1)/ 2; ++i)
		{
			Ball* entity = new Ball;
			entity->m = randfD(minMR, maxMR);
			entity->r = 10.0f;// sqrtG(entity->m);// entity->m;// entity->m / 10.0f;
			Vector3f s2 = size / 2.0f;
			entity->pos = Vector3f(randfD(pos.x + s2.x / 2.0f, pos.x + s2.x), randfD(pos.y + s2.y / 2.0f, pos.y + s2.y), randfD(pos.z + s2.z / 2.0f, pos.z + s2.z));
			entity->vel = Vector3f(0.0f, 0.0f, randfD(vel.z / 2.0f, vel.z));
			entity->color = Color4f(randf(), randf(), randf(), 1.0f);
			Entitys[i] = entity;
		}
		//return numEntititys;
		//--i;

		for (; i < (numEntititys + 1); ++i)
		{
			Ball* entity = new Ball;
			entity->m = randfD(minMR, maxMR);
			entity->r = 10.0f;// entity->m / 10.0f;
			Vector3f s2 = size / 2.0f;
			entity->pos = Vector3f(randfD(pos.x - s2.x / 2.0f, pos.x - s2.x), randfD(pos.y - s2.y / 2.0f, pos.y - s2.y), randfD(pos.z - s2.z / 2.0f, pos.z - s2.z));
			entity->vel = -Vector3f(0.0f, 0.0f, randfD(vel.z / 2.0f, vel.z));
			entity->color = Color4f(randf(), randf(), randf(), 1.0f);
			Entitys[i] = entity;
		}
		return numEntititys + 1;

	}

	bool LoadOptions(const char* filename, Options& options)
	{
		FileReader fr(filename);
		if (!fr.isOpen()) return false;
		
		while (!fr.isEof())
		{
			char pcName[20];// = new char[100];
			fr.getStr(pcName);
			std::string pName(pcName);
			//delete[] pcName;
			
			if (pName == "name") fr.getStr(options.name);
			else if (pName == "width") options.width = fr.getNumber();
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