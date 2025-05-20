#pragma once
#include <string>

#include "../Math/Vector3f.h"

class MaterialMTL
{
public:
	struct MTL
	{
		std::string name;
		float Ns;
		float Ni;
		float d;
		float Tr;
		Vector3f Tf;
		size_t illum;
		Vector3f Ka;
		Vector3f Kd;
		Vector3f Ks;
		Vector3f Ke;
	};
public:
	MTL* Load(const char* fileName, size_t& matN);
};