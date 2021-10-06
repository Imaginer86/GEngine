#pragma once
#include "Entity.h"

class Tera : public Entity
{
public:
	static const size_t MAP_SIZE = 1024;
	static const size_t STEP_SIZE = 16;
	char HeightMap[MAP_SIZE*MAP_SIZE];
	float Height(size_t x, size_t y) const;
};


inline float Tera::Height(size_t X, size_t Y) const
{
	size_t x = X % MAP_SIZE;
	size_t y = Y % MAP_SIZE;

	if (!HeightMap) 
		return 0;

	return static_cast<float>(HeightMap[x + (y * MAP_SIZE)]);
}
