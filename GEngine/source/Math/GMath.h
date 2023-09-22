#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>


const float G = 118.57614113176565795195009712934 * 0.001;////667.3848080808080808080f * 0.5f; //Gravi constant //Todo

const float GM_PI = static_cast<float>(M_PI);

inline float degToRad(float degrees)
{
	return (degrees * GM_PI) / 180.0f;
}

inline float radToDeg(float radians)
{
	return (radians * 180.0f) / GM_PI;
}

inline bool isEqual(float f)
{
	return (fabsf(f)) < std::numeric_limits<float>::epsilon();
}

inline bool isNotZero(float f)
{
	return (fabsf(f)) > std::numeric_limits<float>::epsilon();
}

inline bool isEqual(float f1, float f2)
{
	return (fabsf(f1 - f2)) < std::numeric_limits<float>::epsilon();
}

inline void srandG()
{
	srand(static_cast <unsigned> (time(nullptr)));
}

inline float randf()
{
	return  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

inline float randfD1(float X)
{
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / X));
}

inline float randfD(float LO, float HI)
{
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

float inline sqrtG(float f)
{
	return sqrtf(f);
}

float inline absG(float f)
{
	return fabsf(f);
}

	//inline int toInt(float val)
	//{
		//return val > 0.0f ? static_cast<int>(val + 0.5f) : static_cast<int>(val - 0.5f);
	//}
/*
	inline float randf()
	{
		//return float(std::rand()) / (float(std::RAND_MAX) + 1.0f);
	}

	


	inline float atan2f(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float sin(float a)
	{
		return sinf(a);
	}

	inline float cos(float a)
	{
		return cosf(a);
	}

	inline float abs(float a)
	{
		return fabsf(a);
	}
	*/
//}//namespace Math