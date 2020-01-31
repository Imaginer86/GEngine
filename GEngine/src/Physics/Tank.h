#pragma once
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"
//#include "Model.h"
#include "../Render/ModelM.h"

class Tank
{
public:
	Vector3f pos;
	Quaternion q;
	ModelM model;

	enum {Stoped, Left, Up, Right, Down} move;

	Tank();
	~Tank();
	Tank(const Vector3f& pos_, const Quaternion& q_, const ModelM& model_);
};
