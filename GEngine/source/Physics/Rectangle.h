#pragma once
#include "Entity.h"
#include "Math/Vector3f.h"
#include "Math/Plane.h"


class Rectangle : public Entity
{
public:
	//Plane plane;
	float w;
	float h;
	virtual bool isRectangle() { return true; }
	Plane getPlane()  const;
};

inline Plane Rectangle::getPlane() const
{
	Vector3f N(0, 0, 1);
	N = q.rotate(N);
	float d = -N.x * pos.x - N.y * pos.y - N.z * pos.z;
	//Vector3f N = q * N;
	return Plane(N, d);
}