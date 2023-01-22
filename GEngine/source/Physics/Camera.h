#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"
struct Camera
{
	Vector3f	pos;
	//float angle;
	//Vector3f	axis;
	Quaternion	q;
	void Move(const Vector3f& s);
	void Rotate(const Quaternion& r);
	void MoveUD(float s);
	void MoveLR(float s);
	void MoveNF(float s);
	//void TestUpdate();//!!!
	//Camera(const Vector3f& pos_, float angle_, const Vector3f& axis_) :pos(pos_), angle(angle_), axis(axis_), q(angle_, axis_) {}
	Camera(const Vector3f& pos_, float angle_, const Vector3f& axis_) :pos(pos_), q(angle_, axis_) {}
	~Camera() {};
};

inline void Camera::Move(const Vector3f& s)
{
	pos += s;
}

inline void Camera::Rotate(const Quaternion& q_)
{
	q *= q_;
}

inline void Camera::MoveUD(float s)
{
	Vector3f v(0.0f, 1.0f, 0.0f);
	Quaternion sq = q * v * q.conjugate();
	pos += sq.GetAxis() * s;
}

inline void Camera::MoveLR(float s)
{
	Vector3f v(1.0f, 0.0f, 0.0f);
	Quaternion sq = q * v * q.conjugate();
	pos += sq.GetAxis() * s;
}

inline void Camera::MoveNF(float s)
{
	Vector3f v(0.0f, 0.0f, 1.0f);
	Quaternion sq = q * v * q.conjugate();
	pos += sq.GetAxis() * s;
}