#include "Player.h"

Player::Player(GLFWwindow* aWindow)
{
	dashStrength = 0.0f;
	jumpHeight = 0.0f;
	movementSpeed = 0.0f;
	window = aWindow;
}

void Player::InputMovement()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// jump
	}
}
