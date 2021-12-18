#pragma once

namespace Game
{

	static bool keys[512];

	static long long lastTickCount;
	static bool done;
	static bool pause;

	static size_t FPS;
	static bool active;
	static bool drawDebugInfo;
	static float timeScale;

	static bool Init(/*void* wndProc*/);
	static void Draw();
	static void Input();
	static void Update(float dt);
	static void End();
};