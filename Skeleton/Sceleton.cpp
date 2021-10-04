//#include <iostream>

#include "GEngine.h"
#include "Render\RenderGL.h"

Render *render = nullptr;

Program *programPtr = nullptr;

struct {
	char *title = "Roll&Roll";
	float width = 800;
	float height = 600;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;
} InitData;


float angle = 0.0f;


bool Program::Init(void *wndProc)
{
	render = new RenderGL(InitData.width, InitData.height, Vector3f(0.0f, 0.0f, 500.0f), Quaternion(0.0f, Vector3f(0.0f, 1.0f, 0.0f)), InitData.fullscreen, InitData.light);
	// ������� ���� OpenGL ����
	if (!render->Init(InitData.title, wndProc)) return false;

	return true;
}

void Program::Draw()
{
	render->beginDraw();

	render->Rotate(Quaternion(angle, Vector3f(0.0f, 1.0f, 0.0f)));
	render->drawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(100.0f, 100.0f, 100.0f), Color4f(0.0f, 0.7f, 1.0f, 0.7f));

	render->endDraw();
}

void Program::Update(float dt)
{
	angle += dt * 10.0f;
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
		if (render->swithFullscreen())	Draw();
		else done = true;
	}
	if (keys[VK_SPACE])
	{
		//!!!if (pause)	lastTickCount = GetTickCount();
		keys[VK_SPACE] = false;
		pause = !pause;
	}
	if (keys[VK_ESCAPE])
	{
		done = true;
	}
}

int main()
{
	GInitProgram(programPtr);
	GMain();
	delete render;

	return 0;
}