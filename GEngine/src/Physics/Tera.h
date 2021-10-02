#pragma once
#include "Entity.h"

class Tera : public Entity
{
public:
	static const unsigned MAP_SIZE = 1024;
	static const unsigned STEP_SIZE = 16;
	unsigned char HeightMap[MAP_SIZE*MAP_SIZE];
	float Height(unsigned x, unsigned y) const;
};


inline float Tera::Height(unsigned X, unsigned Y) const
{
	unsigned x = X % MAP_SIZE;
	unsigned y = Y % MAP_SIZE;

	if (!HeightMap) 
		return 0;

	return static_cast<float>(HeightMap[x + (y * MAP_SIZE)]);
}
