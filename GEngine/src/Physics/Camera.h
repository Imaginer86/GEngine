#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"
struct Camera
{
	Vector3f	pos;
	Quaternion	q;
	void Move(const Vector3f& s);
	void Rotate(const Quaternion& r);
	void MoveQ(float s);
	Camera(const Vector3f& pos_, const Quaternion& q_) :pos(pos_), q(q_) {}
	~Camera() {};
};

inline void Camera::Move(const Vector3f& s)
{
	pos += s;
}

inline void Camera::Rotate(const Quaternion& r)
{
	q *= r;
}

inline void Camera::MoveQ(float s)
{
	Vector3f r = q.GetAxic();
	pos += r * s;
}

