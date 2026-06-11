#include <glfw3.h>
#include "Controller.h"

Controller::Controller()
{
	//window = getWindow;
	
	//}
}

bool Controller::W_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		
		return true;
		// 
	}
	return false;
}

bool Controller::A_KEY(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{

		return true;
		
	}
	return false;
}

bool Controller::S_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		return true;
		
	}
	return false;
}

bool Controller::D_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		return true;
		
	}
	return false;
}

bool Controller::W_KEY_RELEASE(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
	{
		return true;

	}
	return false;
}

bool Controller::A_KEY_RELEASE(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		return true;

	}
	return false;
}

bool Controller::S_KEY_RELEASE(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
	{
		return true;

	}
	return false;
}

bool Controller::D_KEY_RELEASE(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		return true;
		
	}
	return false;
}

bool Controller::SPACE_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		return true;
	
	}
	return false;
}

bool Controller::SPACE_KEY_RELEASE(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		return true;

	}
	return false;
}

bool Controller::ESCAPE_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		return true;
		//myPosition += cameraSpeed * myDirection;
	}
	return false;
}

bool Controller::SHIFT_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		return true;
		//myPosition += cameraSpeed * myDirection;
	}
	return false;
}

bool Controller::SHIFT_KEY_RELEASE(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		return true;
		//myPosition += cameraSpeed * myDirection;
	}
	return false;
}

bool Controller::TAB_KEY(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		return true;
		//myPosition += cameraSpeed * myDirection;
	}
	return false;
}

void Controller::glfwSetInputMode_normal(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Controller::glfwSetInputMode_cursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CENTER_CURSOR);
}

void Controller::glfwSetInputMode_disabled(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Controller::glfwSetInputMode_unavailable(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_UNAVAILABLE);
}

void Controller::Controller_glfwSetKeyCallBack(GLFWwindow* window)
{
	
	
}


