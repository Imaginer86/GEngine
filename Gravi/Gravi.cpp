#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include "GraviGame.h"
//#include "Math/GMath.h"
//#include "Math/Plane.h"
//#include "Math/Line.h"

int main ()
{
	/*
	//* Test code for Plane and Line classes
	//Plane P1(Vector3f(2, 1, -1), -1);
	//Plane P2(Vector3f(1, 3, -2), 0);
	//Line L = P1 * P2;
 	
	//Plane P(2, -3, 1, -2);
	//Vector3f M(-2, 4, 4);

	//Vector3f H = P * M;

	//std::cout << H << std::endl;

	//std::cout << (M - H).length() << std::endl;
	//std::cout << P.distance(M) << std::endl;

	//Line L; L.P = Vector3f(-1, 7, 2); L.L = Vector3f(4, -7, -3);
	//Plane P2(1, 4, 1, -2);

	//Vector3f M1 = P2 * L;
	//std::cout << M1 << std::endl;
	*/
	srandG();
	GraviGame game;	
	//if (game.Init("SolarSystem.dat"))
	//if (game.Init("ElasticImpact5.dat"))	
	if (game.Init("RANDOM"))
	{
		game.Run();
		game.End();
	}
	else
	{
#ifdef _DEBUG
		std::cerr << "Can't game.Init" << std::endl;
#endif	// _DEBUG
		return 1;
	}
	return 0;
}