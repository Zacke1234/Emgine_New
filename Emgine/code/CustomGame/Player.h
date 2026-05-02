#pragma once
#include <glfw3.h>



class Player
{
public:
	Player(GLFWwindow* aWindow);

	void InputMovement();
private:
	float movementSpeed;
	float jumpHeight;
	float dashStrength;
	GLFWwindow* window;
};

