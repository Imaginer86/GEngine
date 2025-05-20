#pragma once
//#define _USE_MATH_DEFINES
//#include <string>
#include "Math/Vector3f.h"
#include "Math/Vector4f.h"

struct Options
{
	Vector3f cameraPos;
	Vector3f cameraaxis;
	Vector4f lightAmbient;
	Vector4f lightDiffuse;
	Vector4f lightPosition;

	char name[20];

	float fovy;
	float near;
	float far;

	float cameraAngle;

	float moveScale;
	float rotateScale;

	size_t width;
	size_t height;	
	
	bool fullscreen;
	bool light;

	bool graviForce;
	bool collision;
};