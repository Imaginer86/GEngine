#pragma once

const float GEPSILON = 0.0001f;
const float GM_PI = 3.14159265358979323846f;   // pi

float randf();

bool closeEnough(float f1, float f2);

float gsqrt(float f);

float gatan2f(float y, float x);

float gsin(float a);
float gcos(float a);
float gabs(float a);

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
