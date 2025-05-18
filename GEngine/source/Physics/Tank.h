#pragma once
#include "Entity.h"
#include "Math/Vector3f.h"
#include "Math/Quaternion.h"
//#include "Model.h"
#include "Physics/ModelOBJ.h"

class Tank : public Entity
{
public:
	ModelOBJ model;

	enum {Stoped, Left, Up, Right, Down} move;

	Tank();
	~Tank();
	Tank(float m_, const Vector3f& pos_, const Quaternion& q_, const Vector3f& vel_, const ModelOBJ& model_);
};
