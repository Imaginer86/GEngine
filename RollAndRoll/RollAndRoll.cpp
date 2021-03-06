﻿#include "GEngine.h"

#include "Core\FileReader.h"
#include "Render\RenderGL.h"
#include "Math\gmath.h"
#include "Math\Quaternion.h"
#include "Math\Plane.h"
#include "Physics\Tera.h"

Render *render = nullptr;
Tera tera;
Program *programPtr = nullptr;

Plane plane(Vector3f(0.0f, 0.0f, 1.0f), -100.0f);

struct {
	char *title = "Roll&Roll";	
	unsigned width = 1366;
	unsigned height = 768;
	bool fullscreen = false;
	bool light = true;
	float moveScale = 0.1f;
	float rotateScale = 0.1f;

	Vector3f cameraPos = Vector3f(0.0f, -1500.0f, 50.0f);
	Quaternion cameraQ = Quaternion(-90.0f, Vector3f(1.0f, 0.0f, 0.0f));
	
	Quaternion ballStartQ = Quaternion(0.0f, Vector3f(0.0f, 0.0f, 1.0f));
	Vector3f ballStartPos = Vector3f(0.0f, 0.0f, 500.0f);
	Vector3f ballStartVel = Vector3f(0.0f, 0.0f, 0.0f);
	float ballStartR = 50.0f;

	Quaternion ballRotate = Quaternion(0.0f, Vector3f(0.0f, 1.0f, 0.0f));

} InitData;

struct Ball
{
	Quaternion q;
	Quaternion qa;
	Vector3f pos;
	Vector3f vel;
	float r;
};

Ball ball;


const unsigned ball_STEP = 32;

Vector3f gravi(0.0f, 0.0f, -50.0f);
float dvel = 0.9f;

Quaternion qUp(1.0f, Vector3f(1.0f, 0.0f, 0.0f));
Quaternion qDown(-1.0f, Vector3f(1.0f, 0.0f, 0.0f));
Quaternion qLeft(1.0f, Vector3f(0.0f, 1.0f, 0.0f));
Quaternion qRight(-1.0f, Vector3f(0.0f, 1.0f, 0.0f));


bool contact = false;
Vector3f aContact;

float minVN = 0.1f;

int main()
{

	return GMain();
}

bool Program::Init(void *wndProc)
{
	//Quaternion q2 = Quaternion(90.0f, Vector3f(1.0f, 0.0f, 0.0f));
	render = new RenderGL(InitData.width, InitData.height, InitData.cameraPos, InitData.cameraQ, InitData.fullscreen, InitData.light);
	// ������� ���� OpenGL ����
	if (!render->Init(InitData.title, wndProc)) return false;

	if (!LoadRawFile("data/Terrain.raw", tera.HeightMap)) return false;

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
		if(keys[VK_SHIFT])
			render->RotateCamera(Quaternion(1.0f * InitData.rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
		else
		{
			Vector3f N = plane.unit();
			qUp.rotate(N);
			float d = plane.D;
			plane = Plane(N, d);
		}
	}
	if (keys[VK_DOWN])
	{
		if (keys[VK_SHIFT])
			render->RotateCamera(Quaternion(-1.0f * InitData.rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
		else
		{
			Vector3f N = plane.unit();
			qDown.rotate(N);
			float d = plane.D;
			plane = Plane(N, d);
		}
	}
	if (keys[VK_LEFT])
	{
		if (keys[VK_SHIFT])
			render->RotateCamera(Quaternion(-1.0f * InitData.rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
		else
		{
			Vector3f N = plane.unit();
			qLeft.rotate(N);
			float d = plane.D;
			plane = Plane(N, d);
		}
	}
	if (keys[VK_RIGHT])
	{
		if (keys[VK_SHIFT])
			render->RotateCamera(Quaternion(1.0f * InitData.rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
		else
		{
			Vector3f N = plane.unit();
			qRight.rotate(N);
			float d = plane.D;
			plane = Plane(N, d);
		}

	}
	if (keys[VK_TAB])
	{
		keys[VK_TAB] = false;
		drawDebugInfo = !drawDebugInfo;
	}

	if (keys[VK_F1])
	{
		keys[VK_F1] = false;
		//!!!render->killWindow();
		InitData.fullscreen = !InitData.fullscreen;
		
		render->setFullscreen(InitData.fullscreen);
		//!!!if (!render->createWindow(InitData.title, 32))
		{
			done = true;
		}
		//!!!else
		{
			Draw();
		}
	}
	if (keys[VK_SPACE])
	{
		//111if (pause)	lastTickCount = GetTickCount();

		keys[VK_SPACE] = false;
		pause = !pause;
	}
	if (keys[VK_ESCAPE])
	{
		done = true;
	}
}

void Program::Update(float dt)
{

	dt = 1.0f / 60.0f;




	float dist = gabs(plane.distance(ball.pos)); 
	if (!contact && dist <= ball.r)
	{
		
		Vector3f N = plane.unit();
		N.unitize();
		//Vector3f I = ball.vel;
		//I.unitize();
		//Vector3f R = N * (-I.dotProduct(N)) * 2 + I;
		Vector3f VN = N * (ball.vel.dotProduct(N));
		Vector3f U = ball.vel - VN;


		float Z = plane.A * ball.pos.x + plane.B * ball.pos.y + plane.C * ball.pos.z - ball.r + plane.D;
		//if (fabsf(Z) < GEPSILON) Z = 0.0f;
		float D = plane.A * ball.vel.x + plane.B * ball.vel.y + plane.C * ball.vel.z;

		float dte = Z / D;

		if (dte >= 0.0f && dte <= dt)
		{
			ball.pos -= ball.vel * dte;
			float dtest = plane.distance(ball.pos);

			VN *= dvel;

			if ( VN.length() < minVN )
			{
				contact = true;
				VN = Vector3f(0.0f, 0.0f, 0.0f);
				Vector3f N = plane.unit();
				Vector3f G = gravi.unit();
				float cosA = N.dotProduct(G);
				float sinA = gsqrt(1 - cosA * cosA);
				float aCon = 5.0f * gravi.length() * sinA / 7.0f;
				aContact = (N*G*N)*aCon;

				Vector3f Q = aContact.unit() * N;

				ball.q = Quaternion(0.0f, Q);
				ball.qa = Quaternion(aCon / ball.r, Q);
			}



			ball.vel = U - VN;
			ball.pos += ball.vel * (dt - dte);
			dtest = plane.distance(ball.pos);
		}
		else
		{
			//VN *= dvel;
			ball.vel = U - VN;
			ball.pos += ball.vel * dt ;
			float dtest = plane.distance(ball.pos);
			if (dte >= dt)
				int ttttt = 0;
			if (dte < 0.0f)
				int ttttt = 0;
		}
	}
	else if (!contact)
	{
		ball.q *= InitData.ballRotate;
		ball.vel += gravi * dt;
		ball.pos += ball.vel * dt;
	}
	else
	{
		ball.q *= ball.qa;
		ball.vel += aContact * dt;
		ball.pos += ball.vel * dt;
	}
	
}

void DrawTera()
{
	//render->drawTriangle(Vector3f(0, 0, 0), Vector3f(1024, 0, 0), Vector3f(1024, 1024, 0), Color4f(1.0f, 0.0f, 0.0f, 0.0f));
	//render->drawTriangle(Vector3f(1024, 1024, 0), Vector3f(0, 1024, 0), Vector3f(0, 0, 0), Color4f(1.0f, 0.0f, 0.0f, 0.0f));
	//return


	float step_size = static_cast<float>(Tera::STEP_SIZE);
	for (unsigned X = 0; X < Tera::MAP_SIZE; X += Tera::STEP_SIZE)
		for (unsigned Y = 0; Y < Tera::MAP_SIZE; Y += Tera::STEP_SIZE)
		{
			float x = static_cast<float>(X) - 512.0f;
			float y = static_cast<float>(Y) - 512.0f;
			float z = tera.Height(X, Y);
			Vector3f a(x, y, z);
			z = tera.Height(X, Y + Tera::STEP_SIZE);
			Vector3f b(x, y + step_size, z);
			z = tera.Height(X + Tera::STEP_SIZE, Y + Tera::STEP_SIZE);
			Vector3f c(x + step_size, y + step_size, z);
			z = tera.Height(X + Tera::STEP_SIZE, Y);
			Vector3f d(x + step_size, y, z);
			
			render->drawTriangle(a, b, c, Color4f(0.0f, 0.7f, 0.1f, 1.0f));
			render->drawTriangle(c, d, a, Color4f(0.0f, 0.7f, 0.1f, 1.0f));
			//render->drawQuad(a, b, c, d, Color4f(0.0f, 0.7f, 0.3f, 1.0f));
		}
}

void DrawPlane()
{
	Vector3f a(-500.0f, -500.0f, 0.0f);
	Vector3f b(-500.0f, 500.0f, 0.0f);
	Vector3f c(500.0f, 500.0f, 0.0f);
	Vector3f d(500.0f, -500.0f, 0.0f);
	Vector3f z(0.0f, 0.0f, 100.0f);
	Line A(a, a + z);
	Line B(b, b + z);
	Line C(c, c + z);
	Line D(d, d + z);

	Vector3f pa = plane * A;
	Vector3f pb = plane * B;
	Vector3f pc = plane * C;
	Vector3f pd = plane * D;

	render->drawTriangle(pa, pb, pc, Color4f(1.0f, 0.0f, 0.0f, 0.0f));
	render->drawTriangle(pc, pd, pa, Color4f(1.0f, 0.0f, 0.0f, 0.0f));

}

void Program::Draw()
{
	render->beginDraw();
	render->drawSphere(Vector3f(0.0f, 0.0f, 0.0f), 10.0f, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	render->drawSphere(Vector3f(50.0f, 0.0f, 0.0f), 10.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	render->drawSphere(Vector3f(0.0f, 50.0f, 0.0f), 10.0f, Color4f(0.0f, 1.0f, 0.0f, 1.0f));
	render->drawSphere(Vector3f(0.0f, 0.0f, 50.0f), 10.0f, Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	DrawTera();
	DrawPlane();
	render->drawSphere(ball.pos, ball.r, ball.q, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	if (drawDebugInfo)
	{
		render->print(-0.45f, 0.37f, "FPS: %d", FPS);
		render->print(-0.45f, 0.35f, "Ball Pos %f  %f  %f", ball.pos.x, ball.pos.y, ball.pos.z);
		render->print(-0.45f, 0.33f, "Ball Vel %f  %f  %f", ball.vel.x, ball.vel.y, ball.vel.z);
		render->print(-0.45f, 0.31f, contact ? "Contact: True" : "Contact: False");
	}
	render->endDraw();	
}
