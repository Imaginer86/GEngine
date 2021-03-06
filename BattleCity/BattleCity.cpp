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
	char *title = "BattleCity";
	unsigned width = 1600;
	unsigned height = 900;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;
} InitData;


bool Program::Init(void *wndProc)
{
	render = new RenderGL(InitData.width, InitData.height, Vector3f(0.0f, 0.0f, 500.0f), Quaternion(180.0f, Vector3f(0.0f, 0.0f, 1.0f)), InitData.fullscreen, InitData.light);

	//tank.pos = Vector3f();
	//tank.angle = 0.0f;

	if (!render->Init(InitData.title, wndProc)) return false;

	//if (!ReadModelOBJM(levelM, "data/tale1.objm")) return false;
	if (!ReadModelOBJM(tank.model, "data/Tank.objm")) return false;

	unsigned indexN = 0;
	for (unsigned i = 0; i < tank.model.groupN; i++)
	{
		indexN += tank.model.Groups[i].surfacesN;
	}

	
	unsigned *index = new unsigned[indexN * 3];
	unsigned in = 0;
	for (unsigned i = 0; i < tank.model.groupN; i++)
	{
		for (unsigned j = 0; j < tank.model.Groups[i].surfacesN; j++)
		{
			index[in] = tank.model.Groups[i].Surfaces[j].VertexT[0];
			in++;
			index[in] = tank.model.Groups[i].Surfaces[j].VertexT[1];
			in++;
			index[in] = tank.model.Groups[i].Surfaces[j].VertexT[2];
			in++;
		}
	}


	float *vertex = new float[tank.model.vertexN * 3];
	unsigned vn = 0;
	for (unsigned i = 0; i < tank.model.vertexN; i++)
	{
		vertex[vn] = tank.model.Vertexs[i].x;
		vn++;
		vertex[vn] = tank.model.Vertexs[i].y;
		vn++;
		vertex[vn] = tank.model.Vertexs[i].z;
		vn++;
	}

	float *normal = new float[tank.model.normalN];
	render->CreateVBO(vertex, vn, index, in);

	tank.q.identity();

	tank.q *= Quaternion(180.0f, Vector3f(0.0f, 0.0f, 1.0f));

	return true;
}



void Program::Draw()
{
	render->beginDraw();



	//render->Translate(tank.pos);
	//render->Rotate(tank.q);
	Vector3f a(-100.0f, -100.0f, 0.0f);
	Vector3f b(-100.0f, 100.0f, 0.0f);
	Vector3f c(100.0f, 100.0f, 0.0f);
	Vector3f d(100.0f, -100.0f, 0.0f);
	render->drawQuad(a, b, c, d, Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	//tank.model.Draw(render);
	render->drawVBO();


	//for (size_t i = 0; i < tank.model.vertexN; i++)
		//render->drawTriangleStrip(tank.model.vertexN, tank.model.Vertexs, tank.model.Normals, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	
	//render->LoadIdentity();

	if (drawDebugInfo)
	{
		render->print(-0.45f, 0.35f, "FPS: %d", FPS);
	}

	render->endDraw();

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
	if (keys[VK_SPACE])
	{
		//!!!if (pause)	lastTickCount = GetTickCount();

		keys[VK_SPACE] = false;
		pause = !pause;
	}
}


//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
//{
	//#ifndef _DEBUG
	//UNREFERENCED_PARAMETER(hInstance);
	//UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);
	//UNREFERENCED_PARAMETER(nCmdShow);
	//#endif
int main()
{
	
	GInitProgram(programPtr);
	programPtr->fullscreen = InitData.fullscreen;
	programPtr->width = InitData.width;
	programPtr->height =  InitData.height;
	GMain();


	delete render;
	return 0;
}