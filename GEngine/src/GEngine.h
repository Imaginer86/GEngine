#pragma once

//WWWin
#ifdef _WINDOWS
#include "Platform\GWindows.h"
#endif

#include "Math/Vector3f.h"
#include "Math/Quaternion.h"

struct InitData {
	const char* title = "GEngine";
	size_t width = 1024;
	size_t height = 768;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;

	Vector3f cameraPos = Vector3f(0.0f, 00.0f, -100.0f);
	Quaternion cameraQ = Quaternion(0.0f, Vector3f(0.0f, 1.0f, 0.0f));
};

struct Program
{
	long long lastTickCount = 0;
	bool keys[256];
	size_t FPS = 0;
	bool active = true;
	bool done = false;
	bool pause = true;
	bool drawDebugInfo = true;

	float timeScale = 1.0f;

	//bool	fullscreen = false;
	//bool	lightOn = true;

	//float width;
	//float height;

	
	bool Init(void *wndProc);
	void Draw();
	//void UpdateKeys();
	void Update(float dt);
	void End();
	//char title[11] = "BattleCity";
};

void GInitProgram(Program *& programPtr);

void GUpdateLastTickCount();

void GUpdateKeys();

int GMain();