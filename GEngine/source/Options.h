#pragma once
#include "Math/Vector3f.h"
#include "Math/Vector4f.h"
struct Options
{
	size_t width;
	size_t height;
	Vector3f cameraPos;
	float cameraAngle;
	Vector3f cameraAxic;
	bool fullscreen;
	float moveScale;
	float rotateScale;
	bool light;
	Vector4f lightAmbient;
	Vector4f lightDiffuse;
	Vector4f lightPosition;
};