#include "MaterialMTL.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <fstream>
#include <sstream>
#include <list>

MaterialMTL::MTL* MaterialMTL::Load(const char* fileName, size_t& matN)
{
	std::ifstream inFile;
	inFile.open(fileName, std::ios::in);
	if (!inFile.is_open())	return nullptr;
	std::string str;
	bool isContinue = false;
	//std::string mtlName;
	std::list<MTL> MTLL;
	MTL mtl;
	while (getline(inFile, str))
	{
		if (str.empty()) continue;
		std::stringstream sstr(str);
		char c;
		sstr >> c;
		if (c == '#') continue;
		else if (c == 'n' || isContinue )
		{
			/*
			char c1, c2, c3, c4, c5;
			if (!isContinue)	sstr >> c1 >> c2 >> c3 >> c4 >> c5;
			if (isContinue || (c1 == 'e' && c2 == 'w' && c3 == 'm' && c4 == 't' && c5 == 'l'))
			{
				if (!isContinue)	sstr >> mtlName;
				std::cout << mtlName << std::endl;
			}
			#ifdef _DEBUG
			else std::cerr << "Error Load MTL n" << std::endl;
			#endif // _DEBUG
			*/
			std::string strstr;
			do
			{
				std::stringstream sstrstr(strstr);
				char cc;
				sstrstr >> cc;
				if (cc == 'n')
				{
					char cc1, cc2, cc3, cc4, cc5;
					sstrstr >> cc1 >> cc2 >> cc3 >> cc4 >> cc5;
					if (cc1 == 'e' && cc2 == 'w' && cc3 == 'm' && cc4 == 't' && cc5 == 'l')
					{
						sstrstr >> mtl.name;
						//std::cout << mtl.name << std::endl;
						isContinue = true;
					}
					#ifdef _DEBUG
					else std::cerr << "Error load MTL n";
					#endif // _DEBUG
				}
				else if (cc == 'N')
				{
					char ccc;
					sstrstr >> ccc;
					if (ccc == 's')	sstrstr >> mtl.Ns;
					else if (ccc == 'i')	sstrstr >> mtl.Ni;
					#ifdef _DEBUG
					else std::cerr << "Eror Load MTL N" << std::endl;
					#endif // _DEBUG
				}
				else if (cc == 'd') sstrstr >> mtl.d;
				else if (cc == 'T')
				{
					char ccc;
					sstrstr >> ccc;
					if (ccc == 'r')	sstrstr >> mtl.Tr;
					else if (ccc == 'f') sstrstr >> mtl.Tf.x >> mtl.Tf.y >> mtl.Tf.z;
					#ifdef _DEBUG
					else std::cerr << "Eror Load MTL T" << std::endl;
					#endif // _DEBUG
				}
				else if (cc == 'i')
				{
					char cc1, cc2, cc3, cc4;
					sstrstr >> cc1 >> cc2 >> cc3 >> cc4;
					if (cc1 == 'l' && cc2 == 'l' && cc3 == 'u' && cc4 == 'm')	sstrstr >> mtl.illum;
					#ifdef _DEBUG
					else std::cerr << "Eror Load MTL illum" << std::endl;
					#endif // _DEBUG
				}
				else if (cc == 'K')
				{
					char ccc;
					sstrstr >> ccc;
					if (ccc == 'a') sstrstr >> mtl.Ka.x >> mtl.Ka.y >> mtl.Ka.z;
					else if (ccc == 'd') sstrstr >> mtl.Kd.x >> mtl.Kd.y >> mtl.Kd.z;
					else if (ccc == 's') sstrstr >> mtl.Ks.x >> mtl.Ks.y >> mtl.Ks.z;
					else if (ccc == 'e') sstrstr >> mtl.Ke.x >> mtl.Ke.y >> mtl.Ke.z;
					#ifdef _DEBUG
					else std::cerr << "Eror Load MTL K" << std::endl;
					#endif // _DEBUG
				}

			} while (getline(inFile, strstr));

			MTLL.push_back(mtl);
		}
	}
	inFile.close();
	
	if (MTLL.empty()) return nullptr;

	matN = MTLL.size();
	MTL* MTLs = new MTL[matN];
	for (size_t i = 0; i < matN; ++i)
	{
		MTLs[i] = MTLL.front();
		MTLL.pop_front();
	}

	return MTLs;
}
