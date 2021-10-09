#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Render/ModelOBJ.h"
//#include "Physics/Entity.h"


Render* render = nullptr;
//ModelOBJ Manovar;// = nullptr;
ModelOBJ Tree;
ModelOBJ Tree_1;// = nullptr;
ModelOBJ Tree_2;
ModelOBJ Tree_3;
ModelOBJ Tree_4;

ModelOBJ Back;

bool Program::Init(void* wndProc)
{
	render = new RenderGL("Pirates", wndProc, 1920, 1080, Vector3f(0.0f, -20.0f, -50.0f), 0.0f, Vector3f(0.0f, 1.0f, 0.0f), false, true, 0.1f, 10.0f);
	if (!render->Init()) return false;
	//if (!Tree.Load("data/Tree.obj", true)) return false;
	//if (!Tree.Load("data/Tree_1.obj", false, false, false)) return false;
	//if (!Tree_1.Load("data/Tree_1.obj", false, false, false)) return false;
	//if (!Tree_2.Load("data/Tree_2.obj", false, false, false)) return false;
	//if (!Tree_3.Load("data/Tree_3.obj", false, false, false)) return false;
	//if (!Tree_4.Load("data/Tree_3.obj", false, false, false)) return false;

	if (!Back.Load("data/Back.obj", true)) return false;
	return true;
}

static float alpha = 0.0f;//SSStatic

void Program::Update(float dt)
{
	alpha += 0.1f;
}

void Program::Draw()
{
	render->beginDraw();

	render->Color(Color4f(1.0f, 0.1f, 1.0f, 1.0f));
	render->Rotate(alpha, Vector3f(0.0f, 1.0f, 0.0f));	
	Back.Draw(render);
	render->LoadIdentity();
	if (drawDebugInfo)
	{
		render->Color(Color4f(1.0f, 0.1f, 0.1f, 1.0f));
		render->print(-1.0f, 0.3f, "FPS: %d", FPS);
		render->print(-0.85f, 0.3f, "Time Scale: %f", timeScale);
	}
	render->endDraw();
}

void Program::End()
{
}

int main()
{
	return GMain();
}
