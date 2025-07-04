#pragma once
#include "Math/Vector3f.h"
#include "Render/Color4f.h"
#include "Math/Quaternion.h"

class Entity
{
public:	
	Vector3f  pos;
	Quaternion	q;//todo: Use Quaternion for orientation
	Vector3f  vel;
	Vector3f  force;
	Color4f   color;
	float	m;
	bool moved;

	Entity() :m(1.0f), pos(), q(), vel(), force(), color(), moved(false) {}
	
	Entity(float m_, const Vector3f& pos_, const Vector3f& vel_, const Color4f& color_, const Quaternion& q_)
		:m(m_), pos(pos_), vel(vel_), color(color_), q(q_), moved(false)
	{}

	// Explicitly define the copy constructor
	Entity(const Entity& other) : m(other.m), pos(other.pos), q(other.q), vel(other.vel) , force(other.force), color(other.color), moved(other.moved) {}

	// Explicitly define the copy assignment operator
	Entity& operator=(const Entity& other)	{
		if (this != &other) {
			m = other.m;
			pos = other.pos;
			q = other.q;
			vel = other.vel;
			force = other.force;
			color = other.color;
			moved = other.moved;
		}
		return *this;
	}

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
		vel += (force / m) * dt;  // ��������� � �������� ��������� � ������� ��������. ��������� ��������������� ��������� (����/�����) � ��������� �������	
		move(dt);
	}
}

inline void Entity::move(float dt)
{
	pos += vel * dt;          // ��������� � ��������� ��������� � �������� ���������. ��������� � ��������� ��������*�����
	moved = true;
}

