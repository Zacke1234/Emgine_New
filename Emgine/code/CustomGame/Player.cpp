#include "Player.h"

Player::Player(GLFWwindow* aWindow)
{
	//Object* playerObject = new Object("player", mesh, texture)
	dashStrength = 0.0f;
	jumpHeight = 0.0f;
	movementSpeed = 0.0f;
	window = aWindow;
}

void Player::InputMovement()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// forward
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// backwards
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// right
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// left
	}
}
