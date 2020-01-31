#pragma once

#ifdef _WINDOWS
#include "Platform\GWindows.h"
#endif

struct Program
{
	DWORD lastTickCount = 0;
	bool keys[256];
	unsigned FPS = 0;
	bool active = true;
	bool done = false;
	bool pause = true;
	bool drawDebugInfo = true;

	float timeScale = 1.0f;

	bool Init();
	void Draw();
	void UpdateKeys();
	void Update(float dt);
};

void GInitProgram(Program* programPtr);

int GMain();