#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Render/ModelOBJ.h"
//#include "Physics/Entity.h"


Render* render = nullptr;
ModelOBJ Cube;

//ModelOBJ Manovar;// = nullptr;
//ModelOBJ Tree;
//ModelOBJ Tree_1;// = nullptr;
//ModelOBJ Tree_2;
//ModelOBJ Tree_3;
//ModelOBJ Tree_4;

//ModelOBJ Back;

Vector3f	CameraPos(-2.5f, -2.5f, -20.0f);
float		CameraAngle(0.0f);
Vector3f	CameraAxic(0.0f, 1.0f, 0.0f);

bool Program::Init(void* wndProc)
{
	render = new RenderGL("Pirates", wndProc, 1920, 1200, CameraPos, CameraAngle, CameraAxic, false, true, 0.1f, 10.0f);
	if (!render->Init()) return false;
	if (!Cube.Load("data", "Cube.obj", true)) return false;
	//if (!Manovar.Load("data", "Manovar.obj")) return false;
	//if (!Tree.Load("data/Tree.obj", true)) return false;
	//if (!Tree.Load("data/Tree_1.obj", false, false, false)) return false;
	//if (!Tree_1.Load("data", "Tree_1.obj")) return false;
	//if (!Tree_2.Load("data/Tree_2.obj", false, false, false)) return false;
	//if (!Tree_3.Load("data/Tree_3.obj", false, false, false)) return false;
	//if (!Tree_4.Load("data/Tree_3.obj", false, false, false)) return false;

	//if (!Back.Load("data/Back.obj", true)) return false;
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
	//render->Rotate(alpha, Vector3f(0.0f, 0.0f, 1.0f));
	Cube.Draw(render);
	if (drawDebugInfo)
	{
		//render->LoadIdentity();
		//render->Color(Color4f(1.0f, 0.1f, 0.1f, 1.0f));
		//render->print(-0.55f, 0.4f, "FPS: %d", FPS);
		//render->print(-0.40f, 0.4f, "Time Scale: %f", timeScale);
	}

	render->endDraw();
}

void Program::End()
{
}

int main()
{
	//return GMain();
}
