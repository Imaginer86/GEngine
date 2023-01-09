#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"
#include "../Math/Quaternion.h"

class Entity
{
public:
	float	m;        // �������� �����.
	Vector3f  pos;      // ��������� � ������������.
	Quaternion	q;		// ��������� � ������������.
	Vector3f  vel;      // ��������.
	Vector3f  force;    // �������������� ����.
	Color4f   color;
	bool moved;

	void applyForce(Vector3f _force);

	void init();	// �������� ����� ����

	void simulate(float dt);

	void move(float dt);

	virtual void draw() {};

	virtual bool isBall() {	return false; }
	virtual bool isModel() { return false; }

};

inline void Entity::applyForce(Vector3f _force) 
{
	force += _force;    // ������� ���� ���������� � ������.
}

inline void Entity::init()          // �������� ����� ����
{
	force = {0, 0, 0};
	moved = false;
}

inline void Entity::simulate(float dt)
{
	vel += (force / m) * dt;  // ��������� � �������� ��������� � ������� ��������. ��������� ��������������� ��������� (����/�����) � ��������� �������	
	move(dt);
}

inline void Entity::move(float dt)
{
	pos += vel * dt;          // ��������� � ��������� ��������� � �������� ���������. ��������� � ��������� ��������*�����
	moved = true;
}

