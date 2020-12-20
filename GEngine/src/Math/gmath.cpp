#include "gmath.h"
//#define _USE_MATH_DEFINES

#include <cmath>

float randf()
{
	return float(rand()) / (float(RAND_MAX) + 1.0f);
}

bool closeEnough(float f1, float f2)
{
	return fabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < GEPSILON;
}

float gsqrt(float f)
{
	return sqrtf(f);
}

float gatan2f(float y , float x)
{
	return atan2f(y, x);
}

float gsin(float a)
{
	return sinf(a);
}

float gcos(float a)
{
	return cosf(a);
}

float gabs(float a)
{
	return fabsf(a);
}
