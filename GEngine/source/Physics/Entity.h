#pragma once
#include "Math/Vector3f.h"
#include "Render/Color4f.h"
#include "Math/Quaternion.h"

class Entity
{
public:
	float	m;
	Vector3f  pos;
	Quaternion	q;
	Vector3f  vel;
	Vector3f  force;
	Color4f   color;
	bool moved;

	Entity() :m(1.0f), pos(), q(), vel(), force(), color(), moved(false) {}
	
	Entity(float m_, const Vector3f& pos_, const Quaternion& q_, const Vector3f& vel_)
		:m(m_), pos(pos_), q(q_), vel(vel_), moved(false) 
	{}

	virtual ~Entity() {}

	void applyForce(Vector3f _force);

	void init();

	void simulate(float dt);

	void move(float dt);

	virtual void draw() {}

	virtual bool isBall() {	return false; }
	virtual bool isModel() { return false; }
	virtual bool isRectangle() { return false; }

};

inline void Entity::applyForce(Vector3f _force) 
{
	force += _force;
}

inline void Entity::init()
{
	force = {0, 0, 0};
	moved = false;
}

inline void Entity::simulate(float dt)
{
	if (isNotZero(m))
	{
		vel += (force / m) * dt;  // Изменение в скорости добавляем к текущей скорости. Изменение пропорционально ускорению (сила/масса) и изменению времени	
		move(dt);
	}
}

inline void Entity::move(float dt)
{
	pos += vel * dt;          // Изменение в положении добавляем к текущему положению. Изменение в положении Скорость*время
	moved = true;
}

