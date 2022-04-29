#pragma once
#include "Options.h"
#include "Physics/Entity.h"
#include "Render/Render.h"
#include "Core/Input.h"

//bool keys;

class Game
{
public:
	Game()
		:done(false)
		,pause(true)
		,drawDebugInfo(true)
		,FPS(0)
		,lastTickCount(0)
		,timeScale(0.1f)
		,GraviForce(false)
		,Collision(false)
		,numEntites(0)
		,Enityes(nullptr)
		,render(nullptr)
		,input(nullptr)
		
	{
	};
	bool Init(size_t numEntites_, Options option);
	//void Input(int key, bool press);

	bool Run();

	void Draw();
	void Update(float dt = 0.1f);
	void InputCheck();
	void End();

public:
	Render* render;
	Input* input;
	Entity* Enityes;
	size_t numEntites;
	static bool* keys;


private:
	bool done;
	bool pause;
	bool drawDebugInfo;	
	size_t FPS;
	long long lastTickCount;
	float timeScale;
	bool GraviForce;
	bool Collision;

	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};