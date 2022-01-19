#include "Game.h"
#include "Math/Gmath.h"
#include "Core/Time.h"
#include "Math/Plane.h"
#include "Math/Line.h"

//#include "Physics/Entity.h"

#include <iostream>


//bool keys[512];

Game game;





int main ()
{
	Plane P1(Vector3f(2, 1, -1), -1);
	Plane P2(Vector3f(1, 3, -2), 0);
	Line L = P1 * P2;
	game;

	if (!game.Init()) return 1;
	game.Draw();
	game.lastTickCount = Core::GetTickCount();
	while(!game.done)
	{
		//game.Input();
		long long tickCount = Core::GetTickCount();
		tickCount = tickCount - game.lastTickCount;
		float dt = static_cast<float>(tickCount);
		dt /= 1000000.0f;
		dt *= game.timeScale;
		if (!game.pause)	game.Update(dt);
		game.Draw();
	}
	game.End();
	return 0;
}
