#include "FileReader.h"

#include <list>
#include <string>

bool Core::LoadRawFile(const char* fileName, char* pHeightMap)
{
	std::fstream inRaw;
	inRaw.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);

	if (inRaw.is_open())
	{
		std::streampos size = inRaw.tellg();
		inRaw.seekg(0, std::ios::beg);
		inRaw.read(reinterpret_cast<char*>(pHeightMap), size);
	}
	else
	{
		#ifdef _DEBUG
		std::cerr << "Can't Find The Height Map!" << std::endl; //MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
		#endif // _DEBUG
		return false;
	}

	if (inRaw.eof())
	{
		#ifdef _DEBUG
		std::cerr << "Failed To Get Data!" << std::endl;// MessageBox(NULL, "Failed To Get Data!", "Error", MB_OK);
		#endif // _DEBUG
		return false;
	}
	inRaw.close();
	return true;
}

size_t Core::LoadEntitys(const char* filename, std::vector<Entity*>& Entitys)
{
	size_t num_entitys = 0;
	std::fstream inEntitys;
	inEntitys.open(filename, std::ios::in);

	std::list<Entity*> lEntitys;

	if (inEntitys.is_open())
		do
		{
			std::string name;
			inEntitys >> name;
			if (name == "Ball")
			{
				num_entitys++;
				Ball* entity = new Ball;
				inEntitys >> entity->m >> entity->pos >> entity->vel >> entity->r >> entity->color;
				lEntitys.push_back(entity);
			}
			else if (name == "TBall" || name == "TexturedBall") {
				/*!!!Todo*/
				num_entitys++;
				std::string textureName;
				inEntitys >> textureName;
				Ball* entity = new Ball;
				inEntitys >> entity->m >> entity->pos >> entity->vel >> entity->r >> entity->color;
				lEntitys.push_back(entity);
			}
			else if (name == "RBall" || name == "QBall")
			{
				num_entitys++;
				Ball* entity = new Ball;
				Vector3f axic;
				float angle;
				Vector3f axicR;
				float angleR;
				inEntitys >> entity->m >> entity->r >>entity->pos >> entity->vel >> angle >> axic >> angleR >> axicR >> entity->color;
				entity->rot = Quaternion(angle, axic);
				entity->rotvel = Quaternion(angleR, axicR);
				lEntitys.push_back(entity);
			}
			else if (name == "Rectangle" || name == "Rec") //Fus
			{
				num_entitys++;
				Rectangle* entity = new Rectangle;
				Vector3f axic;
				float angle;
				inEntitys >> entity->m >> entity->pos >> entity->vel >> angle >> axic >> entity->w >> entity->h >> entity->color;
				entity->rot = Quaternion(angle, axic);
				lEntitys.push_back(entity);
			}
			else if (name == "Model")
			{
				num_entitys++;
				ModelOBJ* entity = new ModelOBJ;
				inEntitys >> entity->m >> entity->pos >> entity->vel >> entity->color;
				std::string path, fileName;
				bool isQuad;
				bool isNoTextIndex;
				inEntitys >> path >> fileName >> isQuad >> isNoTextIndex;
				if (!entity->Load(path.c_str(), fileName.c_str(), isQuad, isNoTextIndex))
				{
					#ifdef _DEBUG
					std::cerr << "Can't load obj" << std::endl;
					#endif // _DEBUG
					return 0;
				}
				entity->Save((path + '/' + fileName + ".objm").c_str());
				lEntitys.push_back(entity);
			}
			else return 0;
		} while (!inEntitys.eof());
	inEntitys.close();

	Entitys.resize(num_entitys);
	size_t i = 0;
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

size_t Core::LoadRandomEntitys(size_t numEntititys, const Vector3f& pos, float minR, float maxR, const Vector3f& vel, float minMR, float maxMR, std::vector<Entity*>& Entitys)
{
	//Entitys.resize(numEntititys + 1);		
	for (size_t i = 0; i < numEntititys; ++i)
	{
		Ball* entity = new Ball;
		entity->m = randfD(minMR, maxMR);
		entity->r = 10.0f;// sqrtG(entity->m);// entity->m;// entity->m / 10.0f;
		Vector3f Raxix = Vector3f(randfD(-1.0f, 1.0f), randfD(-1.0f, 1.0f), randfD(-1.0f, 1.0f));
		Raxix.unitize();
		float R = randfD(minR, maxR);

		entity->pos = pos + Raxix * R;
		entity->vel = Vector3f(randfD(-vel.x, vel.x), randfD(-vel.y, vel.y), randfD(-vel.z, vel.z));
		entity->color = Color4f(randf(), randf(), randf(), 1.0f);
		Entitys.push_back(entity);
	}
	//return numEntititys;
	//--i;

	/*
	for (; i < (numEntititys + 1); ++i)
	{
	Ball* entity = new Ball;
	entity->m = randfD(static_cast<float>(minMR), static_cast<float>(maxMR));
	entity->r = 10.0f;// entity->m / 10.0f;
	Vector3f s2 = size / 2.0f;
	entity->pos = Vector3f(randfD(pos.x - s2.x / 2.0f, pos.x - s2.x), randfD(pos.y - s2.y / 2.0f, pos.y - s2.y), randfD(pos.z - s2.z / 2.0f, pos.z - s2.z));
	entity->vel = -Vector3f(0.0f, 0.0f, randfD(vel.z / 2.0f, vel.z));
	entity->color = Color4f(randf(), randf(), randf(), 1.0f);
	Entitys[i] = entity;
	}
	*/
	return Entitys.size();
}

bool Core::LoadOptions(const char* filename, Options& options)
{
	FileReader fr(filename);
	if (!fr.isOpen()) return false;

	while (!fr.isEof())
	{		
		std::string pName = fr.getStr(); 
		if (pName == "name") options.name = fr.getStr();
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
		else if (pName == "light_ambient") options.lightAmbient = fr.getVector4f();
		else if (pName == "light_diffuse") options.lightDiffuse = fr.getVector4f();
		else if (pName == "light_position") options.lightPosition = fr.getVector4f();
		else if (pName == "gravi_force") options.graviForce = fr.getBool();
		else if (pName == "collision") options.collision = fr.getBool();
		else
		{
			#ifdef _DEBUG
			std::cerr << "Wrong options data: " << pName << std::endl;
			#endif // _DEBUG
			return false;
		}
	}
	return true;
}
