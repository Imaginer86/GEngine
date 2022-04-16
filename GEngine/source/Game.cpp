#include "Game.h"
#include "Render/RenderGL.h"
#include "Core/Time.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>



bool  Game::done = false;
bool Game::pause = true;
bool Game::drawDebugInfo = true;
size_t Game::FPS = 0;
Render* Game::render = nullptr;
bool* Game::keys = nullptr;


//Input* input = nullptr;

//const size_t numEntites = 2;// 51;
//void Game::Input(int key, bool press){keys[key] = press;}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 512)
		if (action == GLFW_PRESS) Game::keys[key] = true;
		else if(action == GLFW_RELEASE) Game::keys[key] = false;
}

bool Game::Init(size_t numEntites_, Options option)
{
	numEntites = numEntites_;
	//Planets = new Entity[numEntites];
	lastTickCount = 0;
	pause = true;
	done = false;
	timeScale = 1.0f;


	keys = new bool[512];
	for (int i = 0; i < 512; ++i) keys[i] = false;
	std::cout << "Game::Init" << std::endl;
	render = new RenderGL("Gravi", option.width, option.height, option.cameraPos, option.cameraAngle, option.cameraAxic, option.fullscreen, option.light, option.lightAmbient, option.lightDiffuse, option.lightPosition, option.moveScale, option.rotateScale);
	if (!render) { std::cerr << "Failed to Create render" << std::endl;  return false; }
	GLFWwindow* window = (GLFWwindow*) render->Init();
	if (!window) { std::cerr << "Failed to Init Render" << std::endl;  return false; }
	glfwSetKeyCallback(window, key_callback);

	//if (!input->Init(window)) { std::cerr << "Failed to Init Input" << std::endl;  return false; }
	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;

	return true;
}

void Game::Input()
{
	if (keys[GLFW_KEY_ESCAPE]) Game::done = true;
	if (keys[GLFW_KEY_SPACE]) { keys[GLFW_KEY_SPACE] = false;  Game::pause = !Game::pause; }
	if (keys[GLFW_KEY_TAB]) { keys[GLFW_KEY_TAB] = false;  Game::drawDebugInfo = !Game::drawDebugInfo; }
	if (keys[GLFW_KEY_W]) Game::render->MoveCameraQ(10.0f);
	if (keys[GLFW_KEY_S]) Game::render->MoveCameraQ(-10.0f);
	if (keys[GLFW_KEY_UP]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_DOWN]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(-1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_LEFT]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(0.0f, 1.0f, 0.0f)));
	if (keys[GLFW_KEY_RIGHT]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(0.0f, -1.0f, 0.0f)));

}
void Game::Update(float dt)
{
	for (size_t i = 0; i < numEntites; i++) Planets[i].init();
	if (Collision)
	{
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = i + 1; j < numEntites; j++)
			{
				Vector3f rAxic = Planets[i].pos - Planets[j].pos;
				float dr = rAxic.unitize();
				float r = (Planets[i].r + Planets[j].r);
				if (dr < r)
				{
					std::cout << "Collision " << i << " vs " << j << ". Vel Before: " << Planets[i].vel << " vs " << Planets[j].vel;
					Vector3f u1r = rAxic * (rAxic.dotProduct(Planets[i].vel));
					Vector3f u1p = Planets[i].vel - u1r;

					Vector3f u2r = rAxic * (rAxic.dotProduct(Planets[j].vel));
					Vector3f u2p = Planets[j].vel - u2r;

					Vector3f v1r = ((u1r * Planets[i].m) + (u2r * Planets[j].m) - (u1r - u2r) * Planets[j].m) / (Planets[i].m + Planets[j].m);
					Vector3f v2r = ((u1r * Planets[i].m) + (u2r * Planets[j].m) - (u2r - u1r) * Planets[i].m) / (Planets[i].m + Planets[j].m);

					float v = (Planets[i].vel - Planets[j].vel).Length();
					float dt0 = (dr - r) / v;
					Planets[i].move(dt0);
					Planets[j].move(dt0);
					//float testr = (Planets[i].pos - Planets[j].pos).Length();
					//testr -= r;
					Planets[i].move(dt + dt0);
					Planets[j].move(dt + dt0);
					Planets[i].vel = v1r + u1p;
					Planets[j].vel = v2r + u2p;
					std::cout << ". Vel After: " << Planets[i].vel << " vs " << Planets[j].vel;
				}
			}
	}
	if (GraviForce)
	{
		for (size_t i = 0; i < numEntites; i++) Planets[i].init();
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = 0; j < numEntites; j++)
				if (i != j)
				{
					float r2 = (Planets[i].pos - Planets[j].pos).lenght2();
					float f = G * Planets[i].m * Planets[j].m / r2;
					Vector3f force = (Planets[j].pos - Planets[i].pos).unit() * f;
					Planets[i].applyForce(force);
					Planets[j].applyForce(-force);
				}
	}

	for (size_t i = 0; i < numEntites; i++) Planets[i].simulate(dt);
	for (size_t i = 0; i < numEntites; i++) if (!Planets[i].moved) Planets[i].move(dt);
}

void Game::Draw()
{
	render->beginDraw();
	//render->drawSphere(Vector3f(0.0f, 0.0f, 0.0f), 50.0, Quaternion(0, Vector3f(0.0f, 0.0f, 1.0f)), Color4f(1.0f, 1.0f, 1.0f, 1.0f));

	for (size_t i = 0; i < numEntites; i++)
	{
		render->drawSphere(Planets[i].pos, Planets[i].r, Planets[i].color);
	}
	if (drawDebugInfo)
	{
		//render->print(-0.45f, 0.35f, "FPS: %d", FPS);
		//render->print(-0.25f, 0.35f, "Time Scale: %f", timeScale);

		//Debug Vel
		//render->print(-0.60f, 0.37f, "P0 V: %f %f %f", Planets[0].vel.x, Planets[0].vel.y, Planets[0].vel.z);
		//render->print(-0.10f, 0.37f, "P1 V: %f %f %f", Planets[1].vel.x, Planets[1].vel.y, Planets[1].vel.z);

		//Debug Pos
		//render->print(-0.60f, 0.39f, "P0 P: %f %f %f", Planets[0].pos.x, Planets[0].pos.y, Planets[0].pos.z);
		//render->print(-0.10f, 0.39f, "P1 P: %f %f %f", Planets[1].pos.x, Planets[1].pos.y, Planets[1].pos.z);

	}
	render->endDraw();
}


void Game::End()
{
	delete render;	
	delete[] Planets;
	delete[] keys;
}