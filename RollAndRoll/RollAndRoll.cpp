#include "GEngine.h"

#include "Core\FileReader.h"
#include "Render\RenderGL.h"
#include "Math\Quaternion.h"
#include "Math\Plane.h"
#include "Physics\Tera.h"

Render *render = nullptr;
//Tera tera;
Program *programPtr = nullptr;

struct {
	char *title = "Roll&Roll";	
	unsigned width = 1366;
	unsigned height = 768;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;

	Vector3f cameraPos = Vector3f(500.0f, 0.0f, 1000.0f);
	Quaternion cameraQ = Quaternion(-45.0f, Vector3f(1.0f, 0.0f, 0.0f));

	Quaternion ballStartQ = Quaternion(0.0f, Vector3f(0.0f, 0.0f, 1.0f));
	Vector3f ballStartPos = Vector3f(500.0f, 500.0f, 500.0f);
	Vector3f ballStartVel = Vector3f(0.0f, 0.0f, 0.0f);
	float ballStartR = 25.0f;

	Quaternion ballRotate = Quaternion(1.0f, Vector3f(0.0f, 0.0f, 1.0f));

} InitData;

struct Ball
{
	Quaternion q;
	Vector3f pos;
	Vector3f vel;
	float r;
};

Ball ball;


const unsigned ball_STEP = 32;

Vector3f gravi(0.0f, 0.0f, -10.0f);

#ifndef _DEBUG
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
#else
int main()
{
#endif
	return GMain();
}

bool Program::Init()
{
	//Quaternion q2 = Quaternion(90.0f, Vector3f(1.0f, 0.0f, 0.0f));
	render = new RenderGL(InitData.width, InitData.height, InitData.cameraPos, InitData.cameraQ, InitData.fullscreen, InitData.light);
	// ������� ���� OpenGL ����
	if (!render->createWindow(InitData.title, 32)) return false;

	//if (!render->LoadGLTextures()) return false;

	//if (!LoadRawFile("data/Terrain.raw", Tera::MAP_SIZE*Tera::MAP_SIZE, tera.HeightMap)) return false;

	ball.q = InitData.ballStartQ;
	ball.pos = InitData.ballStartPos;
	ball.vel = InitData.ballStartVel;
	ball.r = InitData.ballStartR;

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
		render->killWindow();
		InitData.fullscreen = !InitData.fullscreen;
		
		render->setFullscreen(InitData.fullscreen);
		if (!render->createWindow(InitData.title, 32))
		{
			done = true;
		}
		else
		{
			Draw();
		}
	}
	if (keys[VK_SPACE])
	{
		if (pause)	lastTickCount = GetTickCount();

		keys[VK_SPACE] = false;
		pause = !pause;
	}
	if (keys[VK_ESCAPE])
	{
		done = true;
	}
}

/*
float Program::interect()
{
	unsigned X = toInt(ball.pos.x);
	unsigned Y = toInt(ball.pos.y);
	if (X < Tera::MAP_SIZE && Y < Tera::MAP_SIZE)
	{
		float dif = fabs(ball.pos.z - static_cast<float>(tera.Height(X, Y)));
		return ball.r - dif;
	}
	else
	{
		return 1000.0f;
	}
}
*/

void Program::Update(float dt)
{
	/*
	float disti = interect();
	if ( disti > 0.0f)
	{
		unsigned X = toInt(ball.pos.x);
		unsigned Y = toInt(ball.pos.y);

		//if (!X) X++; if (!Y) Y++;

		Vector3f p1( static_cast<float>(X - ball_STEP), static_cast<float>(Y), static_cast<float>(tera.Height(X - ball_STEP, Y)));
		Vector3f p2(static_cast<float>(X), static_cast<float>(Y - ball_STEP), static_cast<float>(tera.Height(X , Y - ball_STEP)));
		Vector3f p3(static_cast<float>(X + ball_STEP), static_cast<float>(Y + ball_STEP), static_cast<float>(tera.Height(X + ball_STEP, Y + ball_STEP)));
		
		Plane P(p1, p2, p3);
		Vector3f N = P.unit();

		float dist = P.distance(Vector3f(ball.pos.x, ball.pos.y, ball.pos.z - ball.r));

		float dtd = dist / ball.vel.length();
		ball.pos.z = static_cast<float>(tera.Height(X, Y)) + ball.r;

		Vector3f O(ball.pos.x, ball.pos.y, ball.pos.z - ball.r);

		Quaternion Q(acos((N - O).dotProduct(ball.pos - O) / ( (N - O).length() * (ball.pos - O).length())), N * O);

		Q.rotate(ball.vel);

		ball.vel += gravi * (dt + dtd);
		ball.pos += ball.vel * (dt + dtd);
	}
	else
	{
		ball.q *= InitData.ballRotate;
		ball.vel += gravi * dt;
		ball.pos += ball.vel * dt;
	}
	*/
}

void DrawTera()
{
	render->drawTriangle(Vector3f(0, 0, 0), Vector3f(1024, 0, 0), Vector3f(1024, 1024, 0), Color4f(1.0f, 0.0f, 0.0f, 0.0f));
	render->drawTriangle(Vector3f(1024, 1024, 0), Vector3f(0, 1024, 0), Vector3f(0, 0, 0), Color4f(1.0f, 0.0f, 0.0f, 0.0f));
	//return



	/*
	for (unsigned X = 0; X < Tera::MAP_SIZE; X += Tera::STEP_SIZE)
		for (unsigned Y = 0; Y < Tera::MAP_SIZE; Y += Tera::STEP_SIZE)
		{
			Vector3f a(X, Y, tera.Height(X, Y));
			Vector3f b(X, Y + Tera::STEP_SIZE, tera.Height(X, Y + Tera::STEP_SIZE));
			Vector3f c(X + Tera::STEP_SIZE, Y + Tera::STEP_SIZE, tera.Height(X + Tera::STEP_SIZE, Y + Tera::STEP_SIZE));
			Vector3f d(X + Tera::STEP_SIZE, Y, tera.Height(X + Tera::STEP_SIZE, Y));
			render->drawTriangle(a, b, c, Color4f(0.0f, 0.7f, 0.1f, 1.0f));
			render->drawTriangle(c, d, a, Color4f(0.0f, 0.7f, 0.1f, 1.0f));
			//render->drawQuad(a, b, c, d, Color4f(0.0f, 0.7f, 0.3f, 1.0f));
		}
	*/
}

void Program::Draw()
{
	render->beginDraw();
	DrawTera();
	render->drawSphere(ball.pos, ball.r, ball.q, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	if (drawDebugInfo)
	{
		render->print(-0.45f, 0.35f, "FPS: %d", FPS);
	}
	render->endDraw();	
}
