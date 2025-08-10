#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
	float	r;
	Ball() :Entity(), r(0.f) {}
	Ball(float m_, const Vector3f& pos_, const Vector3f& vel_, float r_, const Color4f& color_, const Quaternion& q_, const Quaternion& q_vel)
		:Entity(m_,pos_, vel_, color_, q_, q_vel )
		,r(r_)
	{}
	Ball(const Ball& other) :Entity(other), r(other.r) {}
	Ball& operator=(const Ball& other) {
		if (this != &other) {

			Entity::operator=(other);
			r = other.r;
		}
		return *this;
	}
	virtual bool isBall() { return true; }
};