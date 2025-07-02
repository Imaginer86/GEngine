#include "PoolGame.h"

void PoolGame::Draw()
{
	Game::Draw();
	render->endDraw();//!!!
}
void PoolGame::Update(float dt)
{
	Game::Update(dt);
}

void PoolGame::InputCheck()
{
	Game::InputCheck();
}