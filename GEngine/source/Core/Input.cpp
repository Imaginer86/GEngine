/*
#include "Input.h"
#include "../Game.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (action == GLFW_PRESS)	Game::Input(key, true);
	//if (action == GLFW_RELEASE)	Game::Input(key, false);
	if (action == GLFW_PRESS && key == 256) Game::done = true;
	if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) Game::pause = !Game::pause;
	//Game::keys[key] = true;
//if (action == GLFW_RELEASE)
	//Game::keys[key] = false;
}


bool Input::Init(void* window_)
{
	GLFWwindow* window = (GLFWwindow*)window_;
	glfwSetKeyCallback(window, key_callback);
	return true;
}
*/