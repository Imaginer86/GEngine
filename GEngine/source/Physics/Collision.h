#pragma once
#include "../Math/Vector3f.h"
#include "Entity.h"
#include "Ball.h"

inline bool ElasticImpact(Entity& A, Entity& B, float dt)
{
	if (A.isBall() && B.isBall())
	{
		Vector3f raxis = A.pos - B.pos;
		float dr = raxis.unitize();
		float r = static_cast<Ball&>(A).r + static_cast<Ball&>(B).r;
		Vector3f u1r = raxis * (raxis.dotProduct(A.vel));
		Vector3f u1p = A.vel - u1r;

		Vector3f u2r = raxis * (raxis.dotProduct(B.vel));
		Vector3f u2p = B.vel - u2r;

		Vector3f v1r = ((u1r * A.m) + (u2r * B.m) - (u1r - u2r) * B.m) / (A.m + B.m);
		Vector3f v2r = ((u1r * A.m) + (u2r * B.m) - (u2r - u1r) * A.m) / (A.m + B.m);

		float v = (A.vel - B.vel).Length();
		float dt0 = (dr - r) / v;
		A.move(dt0);
		B.move(dt0);
		A.move(dt + dt0);
		B.move(dt + dt0);
		A.vel = v1r + u1p;
		B.vel = v2r + u2p;
		return true;
	}
	return false;
}

inline bool InElasticImpact(Entity& A, Entity& B)
{
	if (A.isBall() && B.isBall())
	{
		Vector3f v = (A.vel * A.m + B.vel * B.m) / (A.m + B.m);
		A.vel = v;
		B.vel = v;
		return true;
	}
	return false;
}