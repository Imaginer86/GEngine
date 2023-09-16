#include "GraviGame.h"

void GraviGame::Draw()
{
	Game::Draw();
	render->endDraw();//!!!
}

void GraviGame::Update(float dt)
{
	Game::Update(dt);
}

void GraviGame::InputCheck()
{
	Game::InputCheck();
}
