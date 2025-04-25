#pragma once
#include "Game.h"
class PiratesGame :
    public Game
{
public:
	virtual bool Init(const char* filename);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void InputCheck();	
};

