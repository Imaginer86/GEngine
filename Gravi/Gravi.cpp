#include "Game.h"
#include "Options.h"
#include "Math/Gmath.h"
#include "Core/Time.h"
#include "Core/FileReader.h"
#include "Math/Plane.h"
#include "Math/Line.h"

#include <iostream>

int main ()
{
	Plane P1(Vector3f(2, 1, -1), -1);
	Plane P2(Vector3f(1, 3, -2), 0);
	Line L = P1 * P2;
	//game;

	Game game;

	//Entity* Enityes = nullptr;
	size_t numE = Core::LoadEntitys("EarthMoon.dat", game.Enityes);
	if (!numE)
	{
		std::cerr << "Can't LoadEntity" << std::endl;
		return 1;
	}

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
