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
	//TestUpdate();
}

inline void Camera::MoveUD(float s)
{
	pos += q.GetAxis() * s;
	//TestUpdate();
}

inline void Camera::MoveLR(float s)
{
	pos += q.GetAxis() * Vector3f(0.0f, 1.0f, 0.0f) * s;
	//TestUpdate();
}

//inline void Camera::TestUpdate()
//{
	//angle = q.GetAngle();
	//if (!isEqual(angle)) axis = q.Getaxis();//!!!
	
//}
