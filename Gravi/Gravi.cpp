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
	//Plane P1(Vector3f(2, 1, -1), -1);
	//Plane P2(Vector3f(1, 3, -2), 0);
	//Line L = P1 * P2;
 	
	Plane P(2, -3, 1, -2);
	Vector3f M(-2, 4, 4);

	Vector3f H = P * M;

	std::cout << H << std::endl;

	std::cout << (M - H).length() << std::endl;
	std::cout << P.distance(M) << std::endl;

	Line L; L.P = Vector3f(-1, 7, 2); L.L = Vector3f(4, -7, -3);
	Plane P2(1, 4, 1, -2);

	Vector3f M1 = P2 * L;
	std::cout << M1 << std::endl;

	GraviGame game;

	srandG();

	
	
	if (!game.Entityes.empty()) {
		std::cerr << "Can't Init - game.Entities not empty" << std::endl;
		return 1;
	}
	
	//size_t numE = Core::LoadEntitys("ElasticImpact.dat", game.Entityes);
	size_t numE = Core::LoadEntitys("SolarSystem.dat", game.Entityes);
	//size_t numE = Core::LoadEntitys("EarthMoon.dat", game.Entityes);
	//size_t numE = Core::LoadEntitys("Axics.dat", game.Entityes);

	
	/*
	game.Entityes.resize(1);
	Ball* entity = new Ball;
	entity->m = 5000.0f;
	entity->r = 250;// sqrtG(entity->m);
	entity->pos = Vector3f();
	entity->vel = Vector3f();
	entity->color = Color4f(0.5f, 0.5f, 0.5f, 1.0f);
	game.Entityes[0] = entity;

	size_t numE = Core::LoadRandomEntitys(400, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1000.0f, 1000.0f, 1000.0f), Vector3f(100.0f, 100.0f, 100.0f), 1.0f, 10.0f, game.Entityes);
	if (numE <= 1)
	{
		std::cerr << "Can't LoadEntity" << std::endl;
		return 1;
	}*/
	

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
