#pragma once
#include "Game.h"
class PiratesGame :
    public Game
{
public:
	virtual bool Init(size_t numEntites_, Options option);
	virtual void Draw();
	//virtual void Update();
	virtual void InputCheck();	
};

