#include "PiratesGame.h"

void PiratesGame::Draw()
{
	Game::Draw();
}

//void PiratesGame::Update()
//{
//	Game::Update();
//}

void PiratesGame::InputCheck()
{
	Game::InputCheck();
}

bool PiratesGame::Init(size_t numEntites_, Options option)
{
	return Game::Init(numEntites_, option);
}
