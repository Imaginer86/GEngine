#pragma once
#include "D:\Programming\GEngine\GEngine\source\Game.h"
class PiratesGame :
    public Game
{
	virtual void Draw();
	virtual void Update(float dt = 0.1f);
	virtual void InputCheck();
};

