#include "GEngine.h"
#include "Render/RenderGL.h"
#include "Render/ModelOBJ.h"
//#include "Physics/Entity.h"


Render* render = nullptr;
//ModelOBJ Manovar;// = nullptr;
ModelOBJ Tree;// = nullptr;

bool Program::Init(void* wndProc)
{
	render = new RenderGL(1920, 1080, Vector3f(0.0f, 0.0f, -50.0f), 0.0f, Vector3f(0.0f, 1.0f, 0.0f), false, true, 0.1f, 10.0f);
	if (!render->Init( "Pirates", wndProc)) return false;
	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;

	if (!Tree.Load("data/Tree.obj", true)) return false;
	return true;
}

static float alpha = 0.0f;//SSStatic

void Program::Update(float dt)
{
	alpha += 0.1;
}

void Program::Draw()
{
	render->beginDraw();

	render->Rotate(alpha, Vector3f(0.0f, 1.0f, 0.0f));
	//Manovar.Draw(render);
	Tree.Draw(render);

	render->LoadIdentity();
	if (drawDebugInfo)
	{
		render->print(-0.75f, 0.3f, "FPS: %d", FPS);
		render->print(-0.5f, 0.3f, "Time Scale: %f", timeScale);
	}
	render->endDraw();
}

void Program::End()
{
	//delete Manovar;
	//delete Tree;
}

int main()
{
	return GMain();
}
