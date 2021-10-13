#include "GEngine.h"

#include "Core\FileReader.h"
#include "Render\RenderGL.h"
#include "Math\Quaternion.h"
#include "Physics\Tank.h"

Render *render = nullptr;
Tank* tank = nullptr;;
//ModelOBJ ModelOBJ;
//ModelOBJ levelM;

Program *programPtr = nullptr;


bool Program::Init(void *wndProc)
{
	render = new RenderGL("BattleCity", wndProc, 1024, 768, Vector3f(0.0f, 0.0f, 500.0f), 180.0f, Vector3f(0.0f, 0.0f, 1.0f), false, true, 0.1f, 0.1f);
	tank = new Tank;
	if (!render->Init()) return false;
	if (!tank->model.Load("data", "Tank.objm")) return false;
	size_t indexN = 0;
	for (size_t i = 0; i < tank->model.trianglesN; i++)
	{
		//TTT indexN += tank->model.Quads[i];
	}

	
	size_t *index = new size_t[indexN * 3];
	size_t in = 0;
	for (size_t i = 0; i < tank->model.trianglesN; i++)
	{
		//TTT for (size_t j = 0; j < tank->model.Quads[i]; j++)
		{
			index[in] = tank->model.Triangles[i].VertexT[0];
			in++;
			index[in] = tank->model.Triangles[i].VertexT[1];
			in++;
			index[in] = tank->model.Triangles[i].VertexT[2];
			in++;
		}
	}


	float *vertex = new float[tank->model.vertexN * 3];
	size_t vn = 0;
	for (size_t i = 0; i < tank->model.vertexN; i++)
	{
		vertex[vn] = tank->model.Vertexs[i].x;
		vn++;
		vertex[vn] = tank->model.Vertexs[i].y;
		vn++;
		vertex[vn] = tank->model.Vertexs[i].z;
		vn++;
	}

	//float *normal = new float[tank.model.normalN];
	//render->CreateVBO(vertex, vn, index, in);

	tank->q.identity();
	tank->q *= Quaternion(180.0f, Vector3f(0.0f, 0.0f, 1.0f));
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
	if (drawDebugInfo)
	{
		render->print(-0.45f, 0.35f, "FPS: %d", FPS);
	}
	render->endDraw();
}

void Program::Update(float dt)
{
	dt += dt;//TTT;
}
void Program::End()
{
	delete render;
	delete tank;
}

int main()
{
	GMain();
	return 0;
}