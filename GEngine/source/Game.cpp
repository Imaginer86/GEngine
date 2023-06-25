#include "Game.h"

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include<thread>


#include "Render/RenderGL.h"
#include "Core/Time.h"
#include "Core/Input.h"
#include "Physics/Entity.h"
#include "Physics/Ball.h"
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
	lastTickCount = 0;
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
	if (keys[GLFW_KEY_SPACE]) { keys[GLFW_KEY_SPACE] = false;  Game::pause = !Game::pause; }
	if (keys[GLFW_KEY_TAB]) { keys[GLFW_KEY_TAB] = false;  Game::drawDebugInfo = !Game::drawDebugInfo; }
	if (keys[GLFW_KEY_W]) Game::render->MoveCameraUD(10.0f);
	if (keys[GLFW_KEY_S]) Game::render->MoveCameraUD(-10.0f);
	if (keys[GLFW_KEY_A]) Game::render->MoveCameraLR(-10.0f);
	if (keys[GLFW_KEY_D]) Game::render->MoveCameraLR(10.0f);
	if (keys[GLFW_KEY_PAGE_UP]) Game::render->MoveCameraNF(10.0f);
	if (keys[GLFW_KEY_PAGE_DOWN]) Game::render->MoveCameraNF(-10.0f);
	if (keys[GLFW_KEY_UP]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_DOWN]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(-1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_LEFT]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(0.0f, -1.0f, 0.0f)));
	if (keys[GLFW_KEY_RIGHT]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(0.0f, 1.0f, 0.0f)));

}
void Update(Game& game)
{

	game.lastTickCount = Core::GetTickCount();
	while (!game.done)
	{		
		long long tickCount = Core::GetTickCount();
		tickCount = tickCount - game.lastTickCount;
		game.dt = static_cast<float>(tickCount);
		game.dt /= 1000.0f;
		game.FPS = static_cast<size_t>(1.0f / game.dt);
		game.dt *= game.timeScale;
		if (!game.pause)
		{
			for (size_t i = 0; i < game.numEntites; i++) game.Entityes[i]->init();
			if (game.Collision)
			{
				for (size_t i = 0; i < game.numEntites; i++)
					//size_t i = 0;
					for (size_t j = i + 1; j < game.numEntites; j++)
					{
						if (game.Entityes[i]->isBall() && game.Entityes[j]->isBall())
						{
							Vector3f raxis = game.Entityes[i]->pos - game.Entityes[j]->pos;
							float dr = raxis.Length();
							float r = (dynamic_cast<Ball*>(game.Entityes[i])->r + dynamic_cast<Ball*>(game.Entityes[j])->r);
							if (dr <= r)
							{
								std::cout << "Collision " << i << " vs " << j << ". Vel Before: " << game.Entityes[i]->vel << " vs " << game.Entityes[j]->vel << "m: " << game.Entityes[i]->m << " m: " << game.Entityes[j]->m << std::endl;

								if (i == 0)
								{
									std::cout << "!Black Hole Collision " << std::endl;
								}

								
								if (InElasticImpact(*game.Entityes[i], *game.Entityes[j]))
								{
									game.g_lock.lock();
									game.numEntites--;
									game.Entityes[i]->m += game.Entityes[j]->m;
									std::cout << "m after impact: " << game.Entityes[i]->m << ". Vel After: " << game.Entityes[i]->vel << std::endl;
									game.Entityes.erase(game.Entityes.begin() + j);
									//game.g_lock.unlock();
								}
								else
								{
									std::cerr << "Erorr: collision with not a balls!" << std::endl;
								}

								//ElasticImpact(*Entityes[i], *Entityes[j], dt);
							}
						}
					}
			}

			if (game.GraviForce)
			{
				for (size_t i = 0; i < game.numEntites; i++) game.Entityes[i]->init();
				for (size_t i = 0; i < game.numEntites; i++)
					for (size_t j = 0; j < game.numEntites; j++)
						if (i != j)
						{
							float r2 = (game.Entityes[i]->pos - game.Entityes[j]->pos).lenght2();
							float f = G * game.Entityes[i]->m * game.Entityes[j]->m / r2;
							Vector3f force = (game.Entityes[j]->pos - game.Entityes[i]->pos).unit() * f;
							game.g_lock.lock();
							game.Entityes[i]->applyForce(force);
							game.Entityes[j]->applyForce(-force);
							game.g_lock.unlock();
						}
			}

			for (size_t i = 0; i < game.numEntites; i++)
			{
				game.g_lock.lock();
				game.Entityes[i]->simulate(game.dt);
				game.g_lock.unlock();
			}
			for (size_t i = 0; i < game.numEntites; i++) 
				if (!game.Entityes[i]->moved)
				{
					game.g_lock.lock();
					game.Entityes[i]->move(game.dt);
					game.g_lock.unlock();
				}
		}
	}
}

void Game::Draw()
{
	render->beginDraw();
	//render->drawSphere(Vector3f(0.0f, 0.0f, 0.0f), 50.0, Quaternion(0, Vector3f(0.0f, 0.0f, 1.0f)), Color4f(1.0f, 1.0f, 1.0f, 1.0f));

	for (size_t i = 0; i < numEntites; i++)
	{
		if (Entityes[i]->isBall())	render->drawSphere(Entityes[i]->pos, dynamic_cast<Ball*>(Entityes[i])->r, Entityes[i]->color);
		else if (Entityes[i]->isModel())	dynamic_cast<ModelOBJ*>(Entityes[i])->Draw(render);
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
	render->endDraw();
}

bool Game::Run()
{
	
	Draw();
	std::thread thr(Update, std::ref(*this));
	thr.detach();
	while (!done)
	{
		InputCheck();
		Draw();//TT
		//long long tickCount = Core::GetTickCount();
		//tickCount = tickCount - lastTickCount;
		//dt = static_cast<float>(tickCount);
		//dt /= 1000.0f;
		//FPS = static_cast<size_t>(1.0f / dt);
		//dt *= timeScale;
		//if (!pause)	Update(d);		
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