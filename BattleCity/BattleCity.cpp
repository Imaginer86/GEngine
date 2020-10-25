#include "GEngine.h"

#include "Core\FileReader.h"
#include "Render\RenderGL.h"
#include "Math\Quaternion.h"
#include "Physics\Tank.h"

Render *render = nullptr;
Tank tank;
ModelM modelM;
ModelM levelM;

Program *programPtr = nullptr;

struct {
	char *title = "Roll&Roll";
	unsigned width = 800;
	unsigned height = 600;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;
} InitData;


bool Program::Init()
{
	render = new RenderGL(InitData.width, InitData.height, Vector3f(0.0f, 0.0f, 500.0f), Quaternion(0.0f, Vector3f(0.0f, 0.0f, 1.0f)), InitData.fullscreen, InitData.light);

	//tank.pos = Vector3f();
	//tank.angle = 0.0f;

	if (!render->createWindow(InitData.title, 32)) return false;

	if (!ReadModelOBJM(tank.model, "data/Tank.objm")) return false;

	if (!ReadModelOBJM(levelM, "data/tale1.objm")) return false;

	tank.q.identity();

	tank.q *= Quaternion(180.0f, Vector3f(0.0f, 0.0f, 1.0f));

	return true;
}



void Program::Draw()
{
	render->beginDraw();



	render->Translate(tank.pos);
	render->Rotate(tank.q);
	tank.model.Draw(render);
	render->LoadIdentity();

	{
		float mapW = 13.0f;
		float mapH = 13.0f;


	//Vector3f vPos(-942.5f, -942.5f, 0.0f);
	Vector3f vPos(0.0, 0.0, 0.0f);
	Vector3f vSizeX(300.0f, 0.0f, 0.0f);
	Vector3f vSizeY(0.0f, 300.0f, 0.0f);

	render->Translate(vSizeX*(-0.5f*(mapW)));
	render->Translate(vSizeY*(-0.5f*(mapH)));
	for (size_t i = 0; i < mapW; ++i)
	{
		vPos += vSizeX;
		render->Translate(vSizeX);
		for (size_t j = 0; j < mapH; ++j)
		{
			//if (level.Map[i][j] == 4)
			{
				render->Translate(vPos);
				levelM.Draw(render);
				//DrawModelM(levelM);
				//render->LoadIdentity();
			}
			vPos += vSizeY;
			render->Translate(vSizeY);
		}
		render->Translate(vSizeY*(-(mapH)));
	}

	render->LoadIdentity();
}

	render->endDraw();

	/*
	for (size_t i = 0; i < tank.model.nGroup; ++i)
	{
		for (size_t j = 0; j < tank.model.groups[i].size; ++j)
		{
			Surface surface = tank.model.groups[i].surfaces[j];
			if (surface.n == 3)
			{
				Color4f color(0.2f, 0.75f, 0.2f, 1.0f);
				render->drawTriangle(tank.model.vertexs[surface.Vertexs[0]], tank.model.vertexs[surface.Vertexs[1]], tank.model.vertexs[surface.Vertexs[2]], tank.model.normals[surface.Normals[0]], color);
			}
			else if (surface.n == 4)
			{
				Vector3f quad[4];
				Vector3f n = tank.model.vertexs[surface.Normals[0]];
				quad[0] = tank.model.vertexs[surface.Vertexs[0]];
				quad[1] = tank.model.vertexs[surface.Vertexs[1]];
				quad[2] = tank.model.vertexs[surface.Vertexs[2]];
				quad[3] = tank.model.vertexs[surface.Vertexs[3]];
				Color4f color(0.2f, 0.2f, 0.25f, 1.0f);
				render->drawQuad(quad, n, color);
			}
			else if (surface.n == 5)
			{
				Vector3f vert[5];
				Vector3f norm[5];
				vert[0] = tank.model.vertexs[surface.Vertexs[0]];
				norm[0] = tank.model.normals[surface.Normals[0]];
				vert[1] = tank.model.vertexs[surface.Vertexs[1]];
				norm[1] = tank.model.normals[surface.Normals[1]];
				vert[2] = tank.model.vertexs[surface.Vertexs[2]];
				norm[2] = tank.model.normals[surface.Normals[2]];
				vert[3] = tank.model.vertexs[surface.Vertexs[3]];
				norm[3] = tank.model.normals[surface.Normals[3]];
				vert[4] = tank.model.vertexs[surface.Vertexs[4]];
				norm[4] = tank.model.normals[surface.Normals[4]];
				Color4f color(0.0f, 1.0f, 0.0f, 1.0f);
				//render->drawTriangleStrip(5, vert, norm, color);
			}
			else if (surface.n == 6)
			{
				Vector3f vert[6];
				Vector3f norm[6];
				vert[0] = tank.model.vertexs[surface.Vertexs[0]];
				norm[0] = tank.model.normals[surface.Normals[0]];
				vert[1] = tank.model.vertexs[surface.Vertexs[1]];
				norm[1] = tank.model.normals[surface.Normals[1]];
				vert[2] = tank.model.vertexs[surface.Vertexs[2]];
				norm[2] = tank.model.normals[surface.Normals[2]];
				vert[3] = tank.model.vertexs[surface.Vertexs[3]];
				norm[3] = tank.model.normals[surface.Normals[3]];
				vert[4] = tank.model.vertexs[surface.Vertexs[4]];
				norm[4] = tank.model.normals[surface.Normals[4]];
				vert[5] = tank.model.vertexs[surface.Vertexs[4]];
				norm[5] = tank.model.normals[surface.Normals[4]];


				Color4f color(0.0f, 0.0f, 1.0f, 1.0f);
				//render->drawTriangleStrip(6, vert, norm, color);
			}
			else if (surface.n == 10)
			{
				Vector3f vert[10];
				Vector3f norm[10];
				for (size_t k = 0; k < surface.n; ++k)
				{
					vert[k] = tank.model.vertexs[surface.Vertexs[k]];
					norm[k] = tank.model.normals[surface.Normals[k]];
				}
				Color4f color(0.0f, 0.0f, 1.0f, 1.0f);
				//render->drawTriangleStrip(10, vert, norm, color);
			}
			else
			{
				int t = 0;
			}
		}
	}
	*/

	
}

void Program::Update(float dt)
{

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

		//tank.pos.y += (25.0f * moveScale);
	}
	if (keys['S'])
	{
		//render->MoveCameraQ(-10.0f*moveScale);
		render->MoveCamera(Vector3f(0.0f, -25.0f * InitData.moveScale, 0.0f));
		//tank.pos.y -= (25.0f * moveScale);
	}
	if (keys['A'])
	{
		render->MoveCamera(Vector3f(-25.0f * InitData.moveScale, 0.0f, 0.0f));
		//tank.pos.x -= (25.0f * moveScale);
	}
	if (keys['D'])
	{
		render->MoveCamera(Vector3f(25.0f * InitData.moveScale, 0.0f, 0.0f));
		//tank.pos.x += (25.0f * moveScale);
	}
	if (keys[VK_UP])
	{
		render->RotateCamera(Quaternion(1.0f * InitData.rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
		//tank.q *= Quaternion(1.0f * rotateScale, Vector3f(1.0f, 0.0f, 0.0f));
	}
	if (keys[VK_DOWN])
	{
		render->RotateCamera(Quaternion(-1.0f * InitData.rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
		//tank.q *= Quaternion(-1.0f * rotateScale, Vector3f(1.0f, 0.0f, 0.0f));
	}
	if (keys[VK_LEFT])
	{
		render->RotateCamera(Quaternion(1.0f * InitData.rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
		//tank.q *= Quaternion(1.0f * rotateScale, Vector3f(0.0f, 1.0f, 0.0f));
	}
	if (keys[VK_RIGHT])
	{
		render->RotateCamera(Quaternion(-1.0f * InitData.rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
		//tank.q *= Quaternion(1.0f * rotateScale, Vector3f(0.0f, -1.0f, 0.0f));
	}
	if (keys[VK_TAB])
	{
		keys[VK_TAB] = false;
		drawDebugInfo = !drawDebugInfo;
	}
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	#ifndef _DEBUG
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	#endif
	
	GInitProgram(programPtr);
	GMain();


	delete render;
	return 0;
}