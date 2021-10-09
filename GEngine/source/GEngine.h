#pragma once

//WWWin
#ifdef _WINDOWS
#include "Platform\GWindows.h"
#endif

#include "Math/Vector3f.h"
#include "Math/Quaternion.h"

//TODO
//#include"Render/ModelOBJ.h"

struct InitData {
	const char* title = "GEngine";
	size_t width = 1024;
	size_t height = 768;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;

	Vector3f pos = Vector3f(0.0f, 0.0f, -100.0f);
	float aangle = 0.0f;
	Vector3f axic = Vector3f(0.0f, 1.0f, 0.0f);
};

class Program
{
public:
	long long tick;
	long long lastTickCount = 0;
	bool keys[256];
	size_t FPS = 0;
	bool active = true;
	bool done = false;
	bool pause = false;
	bool drawDebugInfo = true;
	float timeScale = 1.0f;
public:
	bool Init(void *wndProc);
	void Draw();
	void Update(float dt);
	void End();
};

void GInitProgram(Program *& programPtr);

void GUpdateLastTickCount();

void GUpdateKeys();

int GMain();