#pragma once
#include "Game.h"
class GraviGame :	public Game
{
	virtual void Draw();
	virtual void Update(float dt);
	virtual void InputCheck();
};

