#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Physics/Entity.h"
#include "Math/gmath.h"
#include "Math/Plane.h"
#include "Math/Line.h"

Render *render = nullptr;

struct {
	char *title = "Gravi";
	unsigned width = 1366;
	unsigned height = 768;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;

	Vector3f cameraPos = Vector3f(0.0f, 0.0f, 50.0f);
	Quaternion cameraQ = Quaternion(0.0f, Vector3f(1.0f, 0.0f, 0.0f));

} InitData;


Entity *Planets = nullptr;
unsigned numEntites = 51;

int main ()
{
	Plane P1(Vector3f(2, 1, -1), -1);
	Plane P2(Vector3f(1, 3, -2), 0);
	Line L = P1 * P2;

	return GMain();
}

bool Program::Init(void *wndProc)
{
	render = new RenderGL(InitData.width, InitData.height, InitData.cameraPos, InitData.cameraQ, InitData.fullscreen, InitData.light);
	if (!render->Init(InitData.title, wndProc)) return false;

	//if (!render->LoadGLTextures()) return false;

	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;

	Planets = new Entity[numEntites];
	
	/*
	Planets[0].m = 5000.0;
	Planets[0].pos = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].r = 2.0f;
	Planets[0].color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);

	Planets[1].m = 100.0;
	Planets[1].pos = Vector3f(-20.0f, 20.0f, 0.0f);
	Planets[1].vel = Vector3f(10.0f, 0.0f, 0.0f);
	Planets[1].r = 1.0f;
	Planets[1].color = Color4f(1.0f, 0.0f, 0.0f, 1.0f);

	Planets[2].m = 100.0;
	Planets[2].pos = Vector3f(20.0f, -20.0f, 0.0f);
	Planets[2].vel = Vector3f(-10.0f, 0.0f, 0.0f);
	Planets[2].r = 1.0f;
	Planets[2].color = Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	*/

	/*
	Planets[3].m = 750.0;
	Planets[3].pos = Vector3f(5.0f, -5.0f, 0.0f);
	Planets[3].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[3].r = 1.0f;
	Planets[3].color = Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	*/


	Planets[0].m = 10000.0f;
	Planets[0].pos = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].vel = Vector3f(0.0f, 0.0f, 0.0f);
	Planets[0].r = 5.0f;
	Planets[0].color = Color4f(0.2f, 0.2f, 0.2f, 1.0f);

	for (unsigned i = 1; i < numEntites; i++)
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
		//render->killWindow();
		InitData.fullscreen = !InitData.fullscreen;

		//render->setFullscreen(InitData.fullscreen);
		//if (!render->createWindow(InitData.title, 32))
		{
			done = true;
		}
		//else
		{
			Draw();
		}
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
		timeScale *= 1.1f;
	}
	if (keys[VK_SUBTRACT])
	{
		timeScale /= 1.1f;
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
	for (unsigned i = 0; i < numEntites; i++) Planets[i].init();
	for(unsigned i = 0; i < numEntites; i++)
		for(unsigned j = 0; j < numEntites; j++)
			if (i != j)
			{
				float r2 = (Planets[i].pos - Planets[j].pos).lenght2();
				float f = Planets[i].m * Planets[j].m / r2;
				Vector3f force = (Planets[j].pos - Planets[i].pos).unit() * f;
				Planets[i].applyForce(force);
				Planets[j].applyForce(-force);				
			}
	
	for (unsigned i = 0; i < numEntites; i++) Planets[i].simulate(dt);
	for (unsigned i = 0; i < numEntites; i++) Planets[i].move(dt);

	/*
	for (unsigned i = 0; i < numEntites; i++)
		for (unsigned j = i + 1; j < numEntites; j++)
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

	for (unsigned i = 0; i < numEntites; i++)
	{
		render->drawSphere(Planets[i].pos, Planets[i].r, Planets[i].color);
	}
	if (drawDebugInfo)
	{
		render->print(-0.45f, 0.35f, "FPS: %d", FPS);
	}
	render->endDraw();
}

