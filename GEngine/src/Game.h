#pragma once

class Game
{
public:
	static bool done;
	static 	bool pause;
	static bool drawDebugInfo;

	virtual ~Game();
	//static bool *keys;
	long long lastTickCount;
	float timeScale;
	bool GraviForce;
	bool Collision;

	static size_t FPS;
	

	virtual bool Init(/*void* wndProc*/);
	virtual void Draw();
	//void Input(int key, bool press);
	virtual void Update(float dt);
	virtual void End();
};