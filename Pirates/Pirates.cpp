#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Render/ModelM.h"
#include "Physics/Entity.h"


Render* render = nullptr;
ModelM* Manovar = nullptr;

struct {
	const char* title = "Pirates";
	size_t width = 1920;
	size_t height = 1080;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;

	Vector3f cameraPos = Vector3f(0.0f, 0.0f, 1750.0f);
	Quaternion cameraQ = Quaternion(0.0f, Vector3f(1.0f, 0.0f, 0.0f));

} InitData;

const float G = 667.3848080808080808080f * 0.5f;

Entity* Planets = nullptr;
size_t numEntites = 2;// 51;

int main()
{
	//InitData.title = "Pirates";
	//Plane P1(Vector3f(2, 1, -1), -1);
	//Plane P2(Vector3f(1, 3, -2), 0);
	//Line L = P1 * P2;

	return GMain();
}

bool Program::Init(void* wndProc)
{
	render = new RenderGL(InitData.width, InitData.height, InitData.cameraPos, InitData.cameraQ, InitData.fullscreen, InitData.light);
	if (!render->Init( InitData.title, wndProc)) return false;
	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;


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

	return true;
}

void Program::UpdateKeys()
{
	if (keys[VK_PRIOR])
	{
		render->MoveCameraQ(100.0f * InitData.moveScale);
	}
	if (keys[VK_NEXT])
	{
		render->MoveCameraQ(-100.0f * InitData.moveScale);
	}
	if (keys['W'])
	{
		//render->MoveCameraQ(10.0f * moveScale);
		render->MoveCamera(Vector3f(0.0f, 25.0f * InitData.moveScale, 0.0f));
	}
	if (keys['S'])
	{
		//render->MoveCameraQ(-10.0f*moveScale);
		render->MoveCamera(Vector3f(0.0f, -25.0f * InitData.moveScale, 0.0f));
	}
	if (keys['A'])
	{
		render->MoveCamera(Vector3f(-25.0f * InitData.moveScale, 0.0f, 0.0f));
	}
	if (keys['D'])
	{
		render->MoveCamera(Vector3f(25.0f * InitData.moveScale, 0.0f, 0.0f));
	}
	if (keys[VK_UP])
	{
		render->RotateCamera(Quaternion(1.0f * InitData.rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
	}
	if (keys[VK_DOWN])
	{
		render->RotateCamera(Quaternion(-1.0f * InitData.rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
	}
	if (keys[VK_LEFT])
	{
		render->RotateCamera(Quaternion(-1.0f * InitData.rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
	}
	if (keys[VK_RIGHT])
	{
		render->RotateCamera(Quaternion(1.0f * InitData.rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
	}
	if (keys[VK_TAB])
	{
		keys[VK_TAB] = false;
		drawDebugInfo = !drawDebugInfo;
	}

	if (keys[VK_F1])
	{
		keys[VK_F1] = false;
		//TODO render->killWindow();
		if (render->swithFullscreen()) Draw();
		else done = true;
	}
	if (keys[VK_SPACE])
	{
		if (pause) UpdateLastTickCount();

		keys[VK_SPACE] = false;
		pause = !pause;
	}
	if (keys[VK_ESCAPE])
	{
		done = true;
	}
	if (keys[VK_ADD])
	{
		timeScale += 0.1f;
	}
	if (keys[VK_SUBTRACT])
	{
		timeScale -= 0.1f;
	}

	if (keys['L'])
	{
		render->SetLight(!render->GetLight());
		render->UpdateLight();
		keys['L'] = false;
	}
}

void Program::Update(float dt)
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
		render->print(-1.45f, 1.35f, "FPS: %d", FPS);
		render->print(-0.25f, 0.35f, "Time Scale: %f", timeScale);

		//Debug Vel
		render->print(-0.60f, 0.37f, "P0 V: %f %f %f", Planets[0].vel.x, Planets[0].vel.y, Planets[0].vel.z);
		render->print(-0.10f, 0.37f, "P1 V: %f %f %f", Planets[1].vel.x, Planets[1].vel.y, Planets[1].vel.z);

		//Debug Pos
		render->print(-0.60f, 0.39f, "P0 P: %f %f %f", Planets[0].pos.x, Planets[0].pos.y, Planets[0].pos.z);
		render->print(-0.10f, 0.39f, "P1 P: %f %f %f", Planets[1].pos.x, Planets[1].pos.y, Planets[1].pos.z);

	}
	render->endDraw();
}

void Program::End()
{
	delete[] Planets;
}