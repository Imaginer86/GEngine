#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
	float	r;
	virtual bool isBall() { return true; }
};