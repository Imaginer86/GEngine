#pragma once
#include "Game.h"
class GraviGame :
    public Game
{
	virtual void Draw();
	virtual void Update(float dt = 0.1f);
	virtual void InputCheck();
};

