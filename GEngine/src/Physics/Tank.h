#pragma once
#include "Entity.h"
#include "../Math/Vector3f.h"
#include "../Math/Quaternion.h"
//#include "Model.h"
#include "../Render/ModelOBJ.h"

class Tank : public Entity
{
public:
	Vector3f pos;
	Quaternion q;
	ModelOBJ model;

	enum {Stoped, Left, Up, Right, Down} move;

	Tank();
	~Tank();
	Tank(const Vector3f& pos_, const Quaternion& q_, const ModelOBJ& model_);
};
