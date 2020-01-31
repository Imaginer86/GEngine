#ifndef _MATH
#define _MATH
//#define _USE_MATH_DEFINES
#include <cmath>

const float GEPSILON = 0.001f;
const float GM_PI = 3.14159265358979323846f;   // pi

inline bool closeEnough(float f1, float f2)
{
	return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < GEPSILON;
}

inline float degreesToRadians(float degrees)
{
	return (degrees * GM_PI) / 180.0f;
}

inline float radiansToDegrees(float radians)
{
	return (radians * 180.0f) / GM_PI;
}

inline float randf()
{
	return float(rand()) / (float(RAND_MAX) + 1.0f);
}

inline int toInt(float val)
{
	return val > 0.0f ? static_cast<int>(val + 0.5f) : static_cast<int>(val - 0.5f);
}
#endif //_MATH