#pragma once
#include "Game.h"
class PoolGame : public Game
{
	virtual void Draw();
	virtual void Update(float dt);
	virtual void InputCheck();
};