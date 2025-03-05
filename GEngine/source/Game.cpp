#include "Game.h"

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//#include<thread>


#include "Render/RenderGL.h"
#include "Core/Time.h"
#include "Core/Input.h"
#include "Physics/Entity.h"
#include "Physics/Ball.h"
#include "Physics/Rectangle.h"
#include "Physics/Box.h"
#include "Physics/ModelOBJ.h"
#include "Physics/Collision.h"

bool* Game::keys = nullptr;

//const size_t numEntites = 2;// 51;
//void Game::Input(int key, bool press){keys[key] = press;}

bool Game::Init(size_t numEntites_, Options option)
{
	numEntites = numEntites_;
	//Enityes = new Entity[numEntites];
	//lastTickCount = 0;
	pause = true;
	done = false;
	timeScale = 1.0f;
	Collision = option.collision;
	GraviForce = option.graviForce;
	keys = new bool[512];
	for (int i = 0; i < 512; ++i) keys[i] = false;
	std::cout << "Game::Init" << std::endl;
	render = new RenderGL(option);
	if (!render) { std::cerr << "Failed to Create render" << std::endl;  return false; }
	input = new Input();
	void* window = render->Init();
	input->Init(window);
	if (!input) { std::cerr << "Failed to Init Input" << std::endl;  return false; }
	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;
	return true;
}

void Game::InputCheck()
{
	if (keys[GLFW_KEY_ESCAPE]) Game::done = true;
	if (keys[GLFW_KEY_SPACE]) { keys[GLFW_KEY_SPACE] = false; Game::pause = !Game::pause; }
	if (keys[GLFW_KEY_TAB]) { keys[GLFW_KEY_TAB] = false;  Game::drawDebugInfo = !Game::drawDebugInfo; }
	if (keys[GLFW_KEY_W]) Game::render->MoveCameraUD(10.0f);
	if (keys[GLFW_KEY_S]) Game::render->MoveCameraUD(-10.0f);
	if (keys[GLFW_KEY_A]) Game::render->MoveCameraLR(-10.0f);
	if (keys[GLFW_KEY_D]) Game::render->MoveCameraLR(10.0f);
	if (keys[GLFW_KEY_L]) { keys[GLFW_KEY_L] = false;  Game::render->LightSwitch(); }
	if (keys[GLFW_KEY_T]) { keys[GLFW_KEY_T] = false;  Game::render->TextuteSwitch(); }
	if (keys[GLFW_KEY_PAGE_UP]) Game::render->MoveCameraNF(10.0f);
	if (keys[GLFW_KEY_PAGE_DOWN]) Game::render->MoveCameraNF(-10.0f);
	if (keys[GLFW_KEY_UP]) Game::render->RotateCamera(Quaternion(1.0f, Vector3f(1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_DOWN]) Game::render->RotateCamera(Quaternion(1.0f, Vector3f(-1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_LEFT]) Game::render->RotateCamera(Quaternion(1.0f, Vector3f(0.0f, -1.0f, 0.0f)));
	if (keys[GLFW_KEY_RIGHT]) Game::render->RotateCamera(Quaternion(1.0f, Vector3f(0.0f, 1.0f, 0.0f)));
	if (keys[GLFW_KEY_KP_ADD]) timeScale *= 1.1f;
	if (keys[GLFW_KEY_KP_SUBTRACT]) timeScale *= 0.9f;
	if (keys[GLFW_KEY_KP_ENTER]) timeScale = 1.0f;
}

void Game::Update(float dt)
{
	//std::cout << dt << std::endl;
	for (size_t i = 0; i < numEntites; i++) Entityes[i]->init();
	if (Collision)
	{
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = i + 1; j < numEntites; j++)
			{
				if (Entityes[i]->isBall() && Entityes[j]->isBall())
				{
					Vector3f raxis = Entityes[i]->pos - Entityes[j]->pos;
					float dr = raxis.length();
					float r = (static_cast<Ball*>(Entityes[i])->r + static_cast<Ball*>(Entityes[j])->r);
					if (dr <= r) ElasticImpact(Entityes[i], Entityes[j], dt);
					/*
					{
						//std::cout << "Collision " << i << " vs " << j << ". Vel Before: " << Entityes[i]->vel << " vs " << Entityes[j]->vel << "m: " << Entityes[i]->m << " m: " << Entityes[j]->m << std::endl;
						//if (i == 0)	std::cout << "!Black Hole Collision " << std::endl;
						

						//not elatic and inelastic Impact at the same time
						if (InElasticImpact(*Entityes[i], *Entityes[j]))
						{
							numEntites--;
							Entityes[i]->m += Entityes[j]->m;
							std::cout << "m after impact: " << Entityes[i]->m << ". Vel After: " << Entityes[i]->vel << std::endl;
							Entityes.erase(Entityes.begin() + j);
						}
						else std::cerr << "Erorr: collision with not a balls!" << std::endl;
						
						
						if (ElasticImpact(*Entityes[i], *Entityes[j], dt))
						{

						}
						else std::cerr << "Erorr: collision with not a balls!" << std::endl;						
					}
				*/
				}
				else if ((Entityes[i]->isBall() && Entityes[j]->isRectangle()) || (Entityes[i]->isRectangle() && Entityes[j]->isBall()))
				{
					float dr, r;
					if (Entityes[i]->isBall() && Entityes[j]->isRectangle())
					{
						Plane l = static_cast<Rectangle*>(Entityes[j])->getPlane();
						dr = l.distance(Entityes[i]->pos);
						r = static_cast<Ball*>(Entityes[i])->r;
					}
					else
					{
						Plane l = static_cast<Rectangle*>(Entityes[i])->getPlane();
						dr = l.distance(Entityes[j]->pos);
						r = static_cast<Ball*>(Entityes[j])->r;
					}
					if (dr <= r) ElasticImpact(Entityes[i], Entityes[j], dt);
				}
			}
	}

	if (GraviForce)
	{
		for (size_t i = 0; i < numEntites; i++) Entityes[i]->init();
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = 0; j < numEntites; j++)
				if (i != j && isNotZero(Entityes[i]->m) && isNotZero(Entityes[j]->m))
				{
					float r2 = (Entityes[i]->pos - Entityes[j]->pos).lenght2();
					float f = G * Entityes[i]->m * Entityes[j]->m / r2;
					Vector3f force = (Entityes[j]->pos - Entityes[i]->pos).unit() * f;
					Entityes[i]->applyForce(force);
					Entityes[j]->applyForce(-force);
				}
	}

	for (size_t i = 0; i < numEntites; i++) Entityes[i]->simulate(dt);

	for (size_t i = 0; i < numEntites; i++) 
		if (!Entityes[i]->moved) Entityes[i]->move(dt); 
}

void Game::Draw()
{
	render->beginDraw();
	//render->drawSphere(Vector3f(0.0f, 0.0f, 0.0f), 50.0, Quaternion(0, Vector3f(0.0f, 0.0f, 1.0f)), Color4f(1.0f, 1.0f, 1.0f, 1.0f));

	//render->drawLineAB(Vector3f(0, 0, 0), Vector3f(25, 0, 0), Color4f(1, 0, 0, 1));
	for (size_t i = 0; i < numEntites; i++)
	{
		if ((i == numEntites - 1) && Entityes[i]->isBall())
		{ 
			render->drawSphereT(Entityes[i]->pos, static_cast<Ball*>(Entityes[i])->r, Entityes[i]->color);
		}
		else
		{
			if (Entityes[i]->isBall())	render->drawSphere(Entityes[i]->pos, static_cast<Ball*>(Entityes[i])->r, Entityes[i]->color);
			if (Entityes[i]->isRectangle()) render->drawQuad(Entityes[i]->pos, static_cast<Rectangle*>(Entityes[i])->w, static_cast<Rectangle*>(Entityes[i])->h, Entityes[i]->q, Entityes[i]->color);
			if (Entityes[i]->isModel())	dynamic_cast<ModelOBJ*>(Entityes[i])->Draw(render);
		}
	}
	if (drawDebugInfo)
	{
		//render->print(-0.45f, 0.35f, "FPS: %d", FPS);
		//render->print(-0.25f, 0.35f, "Time Scale: %f", timeScale);

		//Debug Vel
		//render->print(-0.60f, 0.37f, "P0 V: %f %f %f", Enityes[0]->vel.x, Enityes[0]->vel.y, Enityes[0]->vel.z);
		//render->print(-0.10f, 0.37f, "P1 V: %f %f %f", Enityes[1]->vel.x, Enityes[1]->vel.y, Enityes[1]->vel.z);

		//Debug Pos
		//render->print(-0.60f, 0.39f, "P0 P: %f %f %f", Enityes[0]->pos.x, Enityes[0]->pos.y, Enityes[0]->pos.z);
		//render->print(-0.10f, 0.39f, "P1 P: %f %f %f", Enityes[1]->pos.x, Enityes[1]->pos.y, Enityes[1]->pos.z);

	}
	//render->endDraw();//!!!
}

bool Game::Run()
{	
	float dt = 0.0f;
	while (!done)
	{
		long long lastTickCount = Core::GetTickCount();
		//FPS = static_cast<size_t>(1.0f / dt);
		dt *= timeScale;
		InputCheck();
		Draw();//TT
		if (!pause)	Update(dt);
		long long tickCount = Core::GetTickCount();
		long long dTickCount = tickCount - lastTickCount;
		dt = static_cast<float>(dTickCount) / 1000.0f;;
		lastTickCount = Core::GetTickCount();
	}
	return true;
}


void Game::End()
{
	delete render;
	delete input;
	for(auto entity : Entityes ) delete entity;
	Entityes.clear();
	delete[] keys;
}