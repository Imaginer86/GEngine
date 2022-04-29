#include "Game.h"
#include "Render/RenderGL.h"
#include "Core/Time.h"
#include "Core/Input.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>






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
	render = new RenderGL("Gravi", option);
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
	if (keys[GLFW_KEY_W]) Game::render->MoveCameraUD(-10.0f);
	if (keys[GLFW_KEY_S]) Game::render->MoveCameraUD(10.0f);
	if (keys[GLFW_KEY_A]) Game::render->MoveCameraLR(-10.0f);
	if (keys[GLFW_KEY_D]) Game::render->MoveCameraLR(10.0f);
	if (keys[GLFW_KEY_UP]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_DOWN]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(-1.0f, 0.0f, 0.0f)));
	if (keys[GLFW_KEY_LEFT]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(0.0f, 1.0f, 0.0f)));
	if (keys[GLFW_KEY_RIGHT]) Game::render->RotateCamera(Quaternion(degToRad(1.0f), Vector3f(0.0f, -1.0f, 0.0f)));

}
void Game::Update(float dt)
{
	for (size_t i = 0; i < numEntites; i++) Enityes[i].init();
	if (Collision)
	{
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = i + 1; j < numEntites; j++)
			{
				Vector3f raxis = Enityes[i].pos - Enityes[j].pos;
				float dr = raxis.unitize();
				float r = (Enityes[i].r + Enityes[j].r);
				if (dr < r)
				{
					std::cout << "Collision " << i << " vs " << j << ". Vel Before: " << Enityes[i].vel << " vs " << Enityes[j].vel;
					Vector3f u1r = raxis * (raxis.dotProduct(Enityes[i].vel));
					Vector3f u1p = Enityes[i].vel - u1r;

					Vector3f u2r = raxis * (raxis.dotProduct(Enityes[j].vel));
					Vector3f u2p = Enityes[j].vel - u2r;

					Vector3f v1r = ((u1r * Enityes[i].m) + (u2r * Enityes[j].m) - (u1r - u2r) * Enityes[j].m) / (Enityes[i].m + Enityes[j].m);
					Vector3f v2r = ((u1r * Enityes[i].m) + (u2r * Enityes[j].m) - (u2r - u1r) * Enityes[i].m) / (Enityes[i].m + Enityes[j].m);

					float v = (Enityes[i].vel - Enityes[j].vel).Length();
					float dt0 = (dr - r) / v;
					Enityes[i].move(dt0);
					Enityes[j].move(dt0);
					//float testr = (Enityes[i].pos - Enityes[j].pos).Length();
					//testr -= r;
					Enityes[i].move(dt + dt0);
					Enityes[j].move(dt + dt0);
					Enityes[i].vel = v1r + u1p;
					Enityes[j].vel = v2r + u2p;
					std::cout << ". Vel After: " << Enityes[i].vel << " vs " << Enityes[j].vel;
				}
			}
	}
	if (GraviForce)
	{
		for (size_t i = 0; i < numEntites; i++) Enityes[i].init();
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = 0; j < numEntites; j++)
				if (i != j)
				{
					float r2 = (Enityes[i].pos - Enityes[j].pos).lenght2();
					float f = G * Enityes[i].m * Enityes[j].m / r2;
					Vector3f force = (Enityes[j].pos - Enityes[i].pos).unit() * f;
					Enityes[i].applyForce(force);
					Enityes[j].applyForce(-force);
				}
	}

	for (size_t i = 0; i < numEntites; i++) Enityes[i].simulate(dt);
	for (size_t i = 0; i < numEntites; i++) if (!Enityes[i].moved) Enityes[i].move(dt);
}

void Game::Draw()
{
	render->beginDraw();
	//render->drawSphere(Vector3f(0.0f, 0.0f, 0.0f), 50.0, Quaternion(0, Vector3f(0.0f, 0.0f, 1.0f)), Color4f(1.0f, 1.0f, 1.0f, 1.0f));

	for (size_t i = 0; i < numEntites; i++)
	{
		render->drawSphere(Enityes[i].pos, Enityes[i].r, Enityes[i].color);
	}
	if (drawDebugInfo)
	{
		//render->print(-0.45f, 0.35f, "FPS: %d", FPS);
		//render->print(-0.25f, 0.35f, "Time Scale: %f", timeScale);

		//Debug Vel
		//render->print(-0.60f, 0.37f, "P0 V: %f %f %f", Enityes[0].vel.x, Enityes[0].vel.y, Enityes[0].vel.z);
		//render->print(-0.10f, 0.37f, "P1 V: %f %f %f", Enityes[1].vel.x, Enityes[1].vel.y, Enityes[1].vel.z);

		//Debug Pos
		//render->print(-0.60f, 0.39f, "P0 P: %f %f %f", Enityes[0].pos.x, Enityes[0].pos.y, Enityes[0].pos.z);
		//render->print(-0.10f, 0.39f, "P1 P: %f %f %f", Enityes[1].pos.x, Enityes[1].pos.y, Enityes[1].pos.z);

	}
	render->endDraw();
}

bool Game::Run()
{
	lastTickCount = Core::GetTickCount();
	Draw();
	while (!done)
	{
		InputCheck();
		Draw();//TT
		long long tickCount = Core::GetTickCount();
		tickCount = tickCount - lastTickCount;
		float dt = static_cast<float>(tickCount);
		dt /= 1000.0f;
		FPS = static_cast<size_t>(1.0f / dt);
		dt *= timeScale;
		if (!pause)	Update(dt);		
	}
	return true;
}


void Game::End()
{
	delete render;
	delete input;
	delete[] Enityes;
	delete[] keys;
}