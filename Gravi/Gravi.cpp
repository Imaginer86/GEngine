#include <iostream>
#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Physics/Entity.h"
#include "Math/gmath.h"
#include "Math/Plane.h"
#include "Math/Line.h"

Program program;
Render *render = nullptr;
const size_t numEntites = 2;// 51;
Entity Planets[numEntites];

bool GraviForce = true;
bool Collision = false;


int main ()
{
	Plane P1(Vector3f(2, 1, -1), -1);
	Plane P2(Vector3f(1, 3, -2), 0);
	Line L = P1 * P2;

	if (!program.Init()) return 1;
	for (;;)
	{
		program.Update(100);
		program.Draw();
	}
	program.End();
	return 0;
}

bool Program::Init(/*void* wndProc*/)
{
	std::cout << "Program::Init" << std::endl;
	render = new RenderGL("Gravi", 1920, 1080, Vector3f(0.0f, 0.0f, -1000.0f), 0.0f, Vector3f(0.0f, 1.0f, 0.0f), false, true, 0.1f, 0.1f);
	if (!render) { std::cout << "Failed to Create render" << std::endl;  return false; }
	if (!render->Init()) { std::cout << "Failed to Init render" << std::endl;  return false; }
	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;

	//Earth-Moon
	
	//Planets = new Entity[numEntites];
	Planets[0].m = 597.370f;
	Planets[0].pos = Vector3f(0, 0, 0);
	Planets[0].vel = Vector3f(0, 0, 0);
	Planets[0].r = 100;
	Planets[0].color = Color4f(0.5f, 1.0f, 0, 1);

	Planets[1].m = 7.3477f;
	Planets[1].pos = Vector3f(0, 384.399f, 0);
	Planets[1].vel = Vector3f(23.605915f, 0, 0);
	Planets[1].r = 10;
	Planets[1].color = Color4f(0.5f, 0.5f, 0.5f, 1);
	
	

	/*
	Planets[0].m = 5000.0;
	Planets[0].pos = Vector3f(-100.0f, 0.0f, 0.0f);
	Planets[0].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].r = 10.0f;
	Planets[0].color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);

	Planets[1].m = 5000.0;
	Planets[1].pos = Vector3f(0.0f, 00.0f, 0.0f);
	Planets[1].vel = Vector3f(-10.0f, 0.0f, 0.0f);
	Planets[1].r = 10.0f;
	Planets[1].color = Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	 */
	//Planets[2].m = 100.0;
	//Planets[2].pos = Vector3f(20.0f, -20.0f, 0.0f);
	//Planets[2].vel = Vector3f(-10.0f, 0.0f, 0.0f);
	//Planets[2].r = 1.0f;
	//Planets[2].color = Color4f(0.0f, 1.0f, 0.0f, 1.0f);


	/*
	Planets[3].m = 750.0;
	Planets[3].pos = Vector3f(5.0f, -5.0f, 0.0f);
	Planets[3].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[3].r = 1.0f;
	Planets[3].color = Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	*/

	/*
	Planets[0].m = 10000.0f;
	Planets[0].pos = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].r = 5.0f;
	Planets[0].color = Color4f(0.2f, 0.2f, 0.2f, 1.0f);

	for (size_t i = 1; i < numEntites; i++)
	{
		Planets[i].m = 10.0f + randf() * 90.0f;
		Planets[i].pos = Vector3f(randf()*200.0f - 100.0f, randf()*200.0f - 100.0f, randf()*200.0f - 100.0f);
		if ((Planets[i].pos - Planets[0].pos).length() < 50.0f)
		{
			--i;
			continue;
		}
		Planets[i].vel = Vector3f(randf()*50.0f - 25.0f, randf()*50.0f - 25.0f, randf()*50.0f - 25.0f);
		Planets[i].r = 10.0f;
		Planets[i].color = Color4f(randf(), randf(), randf(), 1.0f);
	}
	*/
	
	
	/*
	Planets[0].m = 100000.0f;
	Planets[0].pos = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].r = 20.0f;
	Planets[0].color = Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	Planets[1].m = 1000.0f;
	Planets[1].pos = Vector3f(100.0f, 0.0f, -50.0f);
	Planets[1].vel = Vector3f(0.0f, 50.0f, 0.0f);
	Planets[1].r = 10.0f;
	Planets[1].color = Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	Planets[2].m = 1000.0f;
	Planets[2].pos = Vector3f(-100.0f, 0.0f, 50.0f);
	Planets[2].vel = Vector3f(0.0f, -50.0f, 0.0f);
	Planets[2].r = 10.0f;
	Planets[2].color = Color4f(1.0f, 0.0f, -.0f, 1.0f);
	*/

	return true;
}
void Program::Update(float dt)
{
	if (GraviForce)
	{
		for (size_t i = 0; i < numEntites; i++) Planets[i].init();
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = 0; j < numEntites; j++)
				if (i != j)
				{
					float r2 = (Planets[i].pos - Planets[j].pos).lenght2();
					float f = Math::G * Planets[i].m * Planets[j].m / r2;
					Vector3f force = (Planets[j].pos - Planets[i].pos).unit() * f;
					Planets[i].applyForce(force);
					Planets[j].applyForce(-force);
				}
	}
	if (Collision)
	{
		for (size_t i = 0; i < numEntites; i++)
			for (size_t j = i + 1; j < numEntites; j++)
			{
				Vector3f rAxic = Planets[i].pos - Planets[j].pos;
				float dr = rAxic.unitize();
				if (dr <= (Planets[i].r + Planets[j].r))
				{
					Vector3f u1r = rAxic * (rAxic.dotProduct(Planets[i].vel));
					Vector3f u1p = Planets[i].vel - u1r;

					Vector3f u2r = rAxic * (rAxic.dotProduct(Planets[j].vel));
					Vector3f u2p = Planets[j].vel - u2r;

					Vector3f v1r = ((u1r * Planets[i].m) + (u2r * Planets[j].m) - (u1r - u2r) * Planets[j].m) / (Planets[i].m + Planets[j].m);
					Vector3f v2r = ((u1r * Planets[i].m) + (u2r * Planets[j].m) - (u2r - u1r) * Planets[i].m) / (Planets[i].m + Planets[j].m);

					Planets[i].vel = v1r + u1p;
					Planets[j].vel = v2r + u2p;
				}
			}
	}

	for (size_t i = 0; i < numEntites; i++) Planets[i].simulate(dt);
	for (size_t i = 0; i < numEntites; i++) Planets[i].move(dt);
}

void Program::Draw()
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

void Program::End()
{
	delete render;
	//delete[] Planets;
}