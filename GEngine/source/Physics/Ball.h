#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
	float	r;
	Ball() :Entity(), r(0.f) {}
	Ball(float m_, const Vector3f& pos_, const Vector3f& vel_, float r_, const Color4f& color_, const Quaternion& q_ )
		:Entity(m_,pos_, vel_, color_, q_ )
		,r(r_)
	{}
	virtual bool isBall() { return true; }
};