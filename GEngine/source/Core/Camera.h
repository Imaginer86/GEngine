#pragma once
#include "../Math/Vector3f.h"
//#include "../Math/Quaternion.h"
struct Camera
{
public:
	Vector3f	pos;
	float angle;
	Vector3f axic;
	//Quaternion	q;
public:
	Camera() {};
	~Camera() {};
	Camera(const Vector3f& pos_, float angle_, const Vector3f& axic_): pos(pos_), angle(angle_), axic(axic_) { }
};

