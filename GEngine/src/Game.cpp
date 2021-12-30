#include "Game.h"

long long Game::lastTickCount = 0;
bool Game::pause = true;
bool Game::done = false;
float Game::timeScale = 1.0f;
bool Game::GraviForce = true;
bool Game::Collision = true;