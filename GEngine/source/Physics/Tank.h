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

	Tank() {}
	~Tank() {}
	Tank(float m_, const Vector3f& pos_, const Vector3f& vel_, const Color4f& color_, const Quaternion& q_, const ModelOBJ& model_)
		:Entity(m_, pos_, vel_, color_, q_)
		, model(model_)
		, move(Stoped)
	{
	}

};
