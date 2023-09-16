#pragma once
#include  "Math/GMath.h"

#include <vector>
#include <mutex>

#include "Options.h"
#include "Physics/Entity.h"
#include "Render/Render.h"
#include "Core/Input.h"

class Game
{
public:
	Game()
		:done(false)
		,pause(false)
		,drawDebugInfo(true)
		,FPS(0)
		//,lastTickCount(0)
		,timeScale(1.0f)
		,GraviForce(false)
		,Collision(false)
		,numEntites(0)
		//,Enityes(nullptr)
		,render(nullptr)
		,input(nullptr)
		
	{
	};
	virtual bool Init(size_t numEntites_, Options option);
	//void Input(int key, bool press);

	bool Run();

	virtual void Update(float dt);
	virtual void Draw();
	virtual void InputCheck();
	void End();

public:
	Render* render;
	Input* input;
	std::vector<Entity*> Entityes;
	size_t numEntites;
	static bool* keys;


//private:
	bool done;
	bool pause;
	bool drawDebugInfo;	
	size_t FPS;
	//long long lastTickCount;
	float timeScale;
	bool GraviForce;
	bool Collision;

	//std::mutex g_lock;

	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};