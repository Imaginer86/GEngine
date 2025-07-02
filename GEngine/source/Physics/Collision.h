#pragma once
#include "Math/Vector3f.h"
#include "Entity.h"
#include "Ball.h"
#include "Rectangle.h"

inline void ElasticImpactBalls(Ball* A, Ball* B)
{
	Vector3f raxis = A->pos - B->pos;
	float dr = raxis.unitize();
	float r = A->r + B->r;
	Vector3f u1r = raxis * (raxis.dotProduct(A->vel));
	Vector3f u1p = A->vel - u1r;

	Vector3f u2r = raxis * (raxis.dotProduct(B->vel));
	Vector3f u2p = B->vel - u2r;

	Vector3f v1r = ((u1r * A->m) + (u2r * B->m) - (u1r - u2r) * B->m) / (A->m + B->m);
	Vector3f v2r = ((u1r * A->m) + (u2r * B->m) - (u2r - u1r) * A->m) / (A->m + B->m);

	float v = (A->vel - B->vel).length();
	float dt0 = (dr - r) / v;
	A->move(dt0);
	B->move(dt0);
	A->vel = v1r + u1p;
	B->vel = v2r + u2p;
	A->move(-dt0);
	B->move(-dt0);


	//A->move(dt + dt0);
	//B->move(dt + dt0);
}
inline void ElasticImpactBallRec(Ball* ball, Rectangle* rec)
{	
	Plane P = rec->getPlane();
	Vector3f O = P * ball->vel;
	//float Dsc = (ball->pos - O).length();
	//float Dst = (ball->pos - (ball->pos - ball->vel * dt)).length();//TODO
	//float Tc = Dsc * dt / Dsc;
	//ball->pos = ball->pos - ball->vel * dt + ball->vel * Tc;
	#ifdef _DEBUG
	std::cout << "ElasticImpactBallRec:" << std::endl;
	std::cout << P.unit() << std::endl;
	std::cout << ball->vel << std::endl;
	std::cout << O << std::endl;
	#endif // _DEBUG
	ball->vel =  P.unit() * (((-ball->vel).dotProduct(P.unit())) * 2) + ball->vel;
	//ball->pos = ball->pos + ball->vel * (dt - Tc);
	#ifdef _DEBUG
	std::cout << ball->vel << std::endl;
	#endif // _DEBUG	
}

//inline void ElasticImpact(Entity* A, Entity* B, float dt)
//{
	//if (A->isBall() && B->isBall())	ElasticImpactBalls(static_cast<Ball*>(A), static_cast<Ball*>(B), dt);
	//if ((A->isBall() && B->isRectangle()) || (A->isRectangle() && B->isBall()))	ElasticImpactBallRec(A, B, dt);
//}

inline bool InElasticImpact(Entity* A, Entity* B)
{
	if (A->isBall() && B->isBall())
	{
		Vector3f v = (A->vel * A->m + B->vel * B->m) / (A->m + B->m);
		A->vel = v;
		B->vel = v;
		return true;
	}
	return false;
}