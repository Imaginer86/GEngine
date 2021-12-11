#pragma once
#include <cmath>

namespace Math {
	const float G = 667.3848080808080808080f * 0.5f; //Gravi constant //Todo

	const float GEPSILON = 0.0001f;
	const float GM_PI = 3.14159265358979323846f;   // pi

	inline float degreesToRadians(float degrees)
	{
		return (degrees * GM_PI) / 180.0f;
	}

	inline float radiansToDegrees(float radians)
	{
		return (radians * 180.0f) / GM_PI;
	}

	inline int toInt(float val)
	{
		return val > 0.0f ? static_cast<int>(val + 0.5f) : static_cast<int>(val - 0.5f);
	}

	inline float randf()
	{
		return float(std::rand()) / (float(RAND_MAX) + 1.0f);
	}

	inline bool closeEnough(float f1, float f2)
	{
		return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < GEPSILON;
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
}