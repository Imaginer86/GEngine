#include "Input.h"

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../Game.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 512)
		if (action == GLFW_PRESS) Game::keys[key] = true;
		else if (action == GLFW_RELEASE) Game::keys[key] = false;
}


bool Input::Init(void* window_)
{
	GLFWwindow* window = (GLFWwindow*) window_;
	glfwSetKeyCallback(window, key_callback);
	if (window) return true; 
	else return false;
}
