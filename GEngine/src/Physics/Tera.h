#pragma once

class Tera
{
public:
	static const unsigned MAP_SIZE = 1024;
	static const unsigned STEP_SIZE = 16;
	unsigned char HeightMap[MAP_SIZE*MAP_SIZE];
	unsigned Height(unsigned x, unsigned y) const;
};


inline unsigned Tera::Height(unsigned X, unsigned Y) const
{
	unsigned x = X % MAP_SIZE;
	unsigned y = Y % MAP_SIZE;

	if (!HeightMap) 
		return 0;

	return static_cast<unsigned>(HeightMap[x + (y * MAP_SIZE)]);
}