#define _USE_MATH_DEFINES
#include <iostream>

#include "Game.h"
#include "Math/GMath.h"
#include "Core/FileReader.h"

#include "Math/Plane.h"
#include "Math/Line.h"

#include "GraviGame.h"

int main ()
{
	Plane P1(Vector3f(2, 1, -1), -1);
	Plane P2(Vector3f(1, 3, -2), 0);
	Line L = P1 * P2;
	//game;

	GraviGame game;

	srandG();

	//size_t numE = Core::LoadEntitys("EarthMoon.dat", game.Entityes);
	//size_t numE = Core::LoadEntitys("Axics.dat", game.Entityes);
	
	size_t numE = Core::LoadRandomEntitys(200, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1000.0f, 1000.0f, 1000.0f), Vector3f(100.0f, 100.0f, 100.0f), 25.0f, 50.0f, game.Entityes);
	if (!numE)
	{
		std::cerr << "Can't LoadEntity" << std::endl;
		return 1;
	}

	numE++;
	game.Entityes.resize(numE);
	Ball* entity = new Ball;
	entity->m = 5000.0f;
	entity->r = 1.5f;
	entity->pos = Vector3f();
	entity->vel = Vector3f();
	entity->color = Color4f(0.5f, 0.5f, 0.5f, 1.0f);
	game.Entityes[numE - 1] = entity;
	
	

	Options option;
	if (!Core::LoadOptions("options.ini", option))
	{
		std::cerr << "Can't LoadOptions" << std::endl;
		return 1;
	}

	if (game.Init(numE, option))
	{
		game.Run();
		game.End();
	}
	else
	{
		std::cerr << "Can't game.Init" << std::endl;
		return 1;
	}

	return 0;
}
