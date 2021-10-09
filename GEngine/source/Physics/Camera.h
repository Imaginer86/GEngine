#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"
struct Camera
{
	Vector3f	pos;
	Quaternion	q;

	Camera();
	~Camera();
	Camera(const Vector3f& pos_, const Quaternion& q_);
};

