#pragma once
#include <string>
#include "Math/Vector3f.h"
#include "Render/Color4f.h"
#include "Math/Quaternion.h"

class Entity
{
public:	
	Vector3f  pos;
	Quaternion	rot;
	Quaternion	rotvel;
	Vector3f  vel;
	Vector3f  force;
	Color4f   color;
	float	m;
	std::string texName;

	Entity() :m(1.0f), pos(), rot(), rotvel(), vel(), force(), color(), texName() {}
	
	Entity(float m_, const Vector3f& pos_, const Vector3f& vel_, const Color4f& color_, const Quaternion& q_, const Quaternion& rotvel_, const std::string& texName_)
		:m(m_), pos(pos_), vel(vel_), color(color_), rot(q_), rotvel(rotvel_), texName(texName_)
	{}

	// Explicitly define the copy constructor
	Entity(const Entity& other) : m(other.m), pos(other.pos), rot(other.rot), rotvel(other.rotvel), vel(other.vel) , force(other.force), color(other.color), texName(other.texName) {}

	// Explicitly define the copy assignment operator
	Entity& operator=(const Entity& other)	{
		if (this != &other) {
			m = other.m;
			pos = other.pos;
			rot = other.rot;
			rotvel = other.rotvel;
			vel = other.vel;
			force = other.force;
			color = other.color;
			texName = other.texName;	
		}
		return *this;
	}

	virtual ~Entity() {}

	void applyForce(Vector3f _force);

	void init();

	void simulate(float dt);

	void move(float dt);
	void rotate(float dt);

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
}

inline void Entity::simulate(float dt)
{
	vel += (force / m) * dt;
}

inline void Entity::move(float dt)
{
	pos += vel * dt;
}

inline void Entity::rotate(float dt)
{ 
	//Todo optimize  SLEPR?
	float angle;
	Vector3f axis;
	angle = rotvel.GetAngle();
	axis = rotvel.GetAxis();
	angle *= dt;
	Quaternion deltaRot;
	deltaRot.fromAngleAxis(angle, axis);
	rot *= deltaRot;
	rot.normalize();
}
