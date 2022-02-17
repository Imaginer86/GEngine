#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>


const float G = 667.3848080808080808080f * 0.5f; //Gravi constant //Todo

//const float GEPSILON = 0.00001f;
//const float GM_PI = 3.14159265358979323846f;   // pi
const float GM_PI = static_cast<float>(M_PI);

inline float degToRad(float degrees)
{
	return (degrees * GM_PI) / 180.0f;
}

inline float radToDeg(float radians)
{
	return (radians * 180.0f) / GM_PI;
}

inline bool isEqual(float f1, float f2)
{
	//return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < GEPSILON;
	return (fabsf(f1 - f2)) < std::numeric_limits<float>::epsilon();
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

	
	float inline sqrt(float f)
	{
		return sqrtf(f);
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