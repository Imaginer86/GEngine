#pragma once

namespace Game
{
	//static bool *keys;
	static long long lastTickCount;
	static bool done;
	static bool pause;

	static size_t FPS;
	static bool active;
	static bool drawDebugInfo;
	static float timeScale;

	bool Init(/*void* wndProc*/);
	void Draw();
	void Input(int key, bool press);
	void Update(float dt);
	void End();
};