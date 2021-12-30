#pragma once

namespace Game
{
	//static bool *keys;
	extern long long lastTickCount;
	extern bool done;
	extern bool pause;
	extern float timeScale;
	extern bool GraviForce;
	extern bool Collision;

	static size_t FPS;
	static bool active;
	static bool drawDebugInfo;
	

	bool Init(/*void* wndProc*/);
	void Draw();
	//void Input(int key, bool press);
	void Update(float dt);
	void End();
};