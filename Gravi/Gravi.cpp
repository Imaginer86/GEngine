#include "Game.h"
#include "Options.h"
#include "Math/Gmath.h"
#include "Core/Time.h"
#include "Core/FileReader.h"
#include "Math/Plane.h"
#include "Math/Line.h"

//#include "Physics/Entity.h"

#include <iostream>


//bool keys[512];

int main ()
{
	Plane P1(Vector3f(2, 1, -1), -1);
	Plane P2(Vector3f(1, 3, -2), 0);
	Line L = P1 * P2;
	//game;

	Game game;

	//Entity* Planets = nullptr;
	size_t numE = Core::LoadEntitys("EarthMoon.dat", game.Planets);
	if (!numE) return 1;

	Options option;
	if (!Core::LoadOptions("options.ini", option)) return 2;

	if (!game.Init(numE, option)) return 3;

	game.Run();


	game.End();
	return 0;
}
