#pragma once
#include "Physics/Entity.h"
#include "Render/Render.h"

//bool keys;

class Game
{
public:
	static bool done;
	static bool pause;
	static bool drawDebugInfo;
	

	
	static size_t FPS;

	static bool *keys;
	long long lastTickCount;
	float timeScale;
	bool GraviForce;
	bool Collision;

	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	

	bool Init(size_t numEntites_, size_t width, size_t height, const Vector3f& cameraPos, float cameraAngle, const Vector3f& cameraAxic, bool fullscreen, bool light, float moveScale, float rotateScale);
	//void Input(int key, bool press);
	
	void Draw();
	void Update(float dt = 0.1f);
	void Input();
	void End();

	static Render* render;
	Entity* Planets;
	size_t numEntites;
};