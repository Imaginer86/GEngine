#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
	float	r;
	Ball() :Entity(), r(0.f) {}
	Ball(float m_, float r_, const Vector3f& pos_, const Quaternion& q_, const Vector3f& vel_)
		:Entity(m_,pos_, q_, vel_)
		,r(r_)
	{}
	virtual bool isBall() { return true; }
};