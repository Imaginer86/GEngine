#include "PiratesGame.h"

void PiratesGame::Draw()
{
	Game::Draw();
	//render->beginDraw();
	Line l(Vector3f(0, 0, 0), Vector3f(2, 0, 0));
	render->drawLine(l, Color4f(1, 0, 0, 1));
	render->drawLineAB(Vector3f(0, 0, 0), Vector3f(25, 50, 0), Color4f(1, 0, 0, 1));
	render->endDraw();//!!!
}

void PiratesGame::Update(float dt)
{
	Game::Update(dt);
	Quaternion qt(1, Vector3f(0, 1, 1));
	Entityes[1]->q *= qt;
}

void PiratesGame::InputCheck()
{
	Game::InputCheck();
}

bool PiratesGame::Init(size_t numEntites_, Options option)
{
	return Game::Init(numEntites_, option);
}
