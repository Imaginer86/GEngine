#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Render/ModelOBJ.h"
//#include "Physics/Entity.h"


Render* render = nullptr;
ModelOBJ* Manovar = nullptr;
//ModelOBJ* Tree = nullptr;



//Entity* Planets = nullptr;
//size_t numEntites = 2;// 51;

bool Program::Init(void* wndProc)
{
	render = new RenderGL(1920, 1080, Vector3f(0.0f, 0.0f, 50000.0f), Quaternion(180.0f, Vector3f(0.0f, 0.0f, 1.0f)), false, true, 0.1f, 0.1f);
	if (!render->Init( "Pirates", wndProc)) return false;
	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;

	Manovar = new ModelOBJ;
	//Tree = new ModelOBJ;
	//if (!Tree->Load("data//Tree1//Tree1.obj", true)) return false;
	if (!Manovar->Load("data//Victoria//Victoria.obj")) return false;
	//if (!Manovar->LoadM("data//Manovar//Manovar_mod.obj")) return false;
	//if(!Manovar->Load("data//Manovar//Manovar.obj")) return false;
	//Manovar->Load("data//Cube.obj");

	/*
	Planets = new Entity[numEntites];

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

	*/

	return true;
}

void Program::Update(float dt)
{
	/*
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

	for (size_t i = 0; i < numEntites; i++) Planets[i].simulate(dt);
	for (size_t i = 0; i < numEntites; i++) Planets[i].move(dt);


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
		*/
}

void Program::Draw()
{
	render->beginDraw();
	//render->drawSphere(Vector3f(0.0f, 0.0f, 0.0f), 50.0, Quaternion(0, Vector3f(0.0f, 0.0f, 1.0f)), Color4f(1.0f, 1.0f, 1.0f, 1.0f));

	//render->Rotate(Quaternion(90.0f, Vector3f(0.0f, 1.0f, 0.0f)));
	Manovar->Draw(render);
	//Tree->Draw(render);

	/*

	for (size_t i = 0; i < numEntites; i++)
	{
		render->drawSphere(Planets[i].pos, Planets[i].r, Planets[i].color);
	}
	if (drawDebugInfo)
	{
		render->print(-1.45f, 1.35f, "FPS: %d", FPS);
		render->print(-0.25f, 0.35f, "Time Scale: %f", timeScale);

		//Debug Vel
		render->print(-0.60f, 0.37f, "P0 V: %f %f %f", Planets[0].vel.x, Planets[0].vel.y, Planets[0].vel.z);
		render->print(-0.10f, 0.37f, "P1 V: %f %f %f", Planets[1].vel.x, Planets[1].vel.y, Planets[1].vel.z);

		//Debug Pos
		render->print(-0.60f, 0.39f, "P0 P: %f %f %f", Planets[0].pos.x, Planets[0].pos.y, Planets[0].pos.z);
		render->print(-0.10f, 0.39f, "P1 P: %f %f %f", Planets[1].pos.x, Planets[1].pos.y, Planets[1].pos.z);

	}

	*/
	render->endDraw();
}

void Program::End()
{
	//delete[] Planets;

	delete Manovar;
	//delete Tree;
}

int main()
{
	return GMain();
}
