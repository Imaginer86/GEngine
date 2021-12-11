//#include <iostream>

#include "GEngine.h"
#include "Render\RenderGL.h"

Render *render = nullptr;

Program *programPtr = nullptr;

float angle = 0.0f;


bool Program::Init(void *wndProc)
{
	render = new RenderGL("Skeleton", wndProc, 1024, 768, Vector3f(0.0f, 0.0f, 500.0f), 0.0f, Vector3f(0.0f, 1.0f, 0.0f), false, true, 0.1f, 0.1f);
	// ������� ���� OpenGL ����
	if (!render->Init()) return false;

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

void Program::End()
{
	delete render;
}

int main()
{
	//GInitProgram(programPtr);
	//GMain();
	return 0;
}