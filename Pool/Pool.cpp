#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include "PoolGame.h"

//#include "Math/GMath.h"
//#include "Math/Plane.h"
//#include "Math/Line.h"

int main()
{
	srandG();
	PoolGame game;
	//if (game.Init("2Balls.dat"))
	//if (game.Init("ElasticImpact5.dat"))	
	if (game.Init("pool.dat"))
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