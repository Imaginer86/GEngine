#pragma once
#include "Entity.h"
#include "Math/Vector3f.h"
#include "Math/Plane.h"


class Rectangle : public Entity
{
public:
	Rectangle() :Entity(), w(1.f), h(1.0f) {}
	Rectangle(float m_, float r_, const Vector3f& pos_, const Vector3f& vel_, const Color4f& color_, float w_, float h_, const Quaternion& q_, const Quaternion& q_vel)
		:Entity(m_, pos_, vel_, color_, q_, q_vel)
		, w(w_)
		, h(h_)
	{}
	//Plane plane;
	float w;
	float h;
	virtual bool isRectangle() { return true; }
	Plane getPlane()  const;
};

inline Plane Rectangle::getPlane() const
{
	Vector3f N(0, 0, 1);
	N = rot.rotate(N);
	float d = -N.x * pos.x - N.y * pos.y - N.z * pos.z;
	//Vector3f N = q * N;
	return Plane(N, d);
}