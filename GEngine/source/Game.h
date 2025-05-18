#pragma once
#include  "Math/GMath.h"

#include <vector>
//#include <mutex>

#include "Options.h"
#include "Physics/Entity.h"
#include "Render/Render.h"
#include "Core/Input.h"

class Game
{
public:
	Game()
		:render(nullptr)
		,input(nullptr)
		,numEntites(0)
		,timeScale(1.0f)
		,FPS(0)
		,done(false)
		,pause(false)
		//,lastTickCount(0)
		,GraviForce(false)
		,drawDebugInfo(true)
		,Collision(false)
		//,Enityes(nullptr)
	{
	};
	virtual ~Game() {};
	virtual bool Init(const char* filename);
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
	float timeScale;
	size_t FPS;
	//long long lastTickCount;	
	bool GraviForce;
	bool Collision;
	bool done;
	bool pause;
	bool drawDebugInfo;


	//std::mutex g_lock;

	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};