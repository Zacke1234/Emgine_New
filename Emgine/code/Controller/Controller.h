#pragma once
class Controller
{
public:
	Controller();
	
	bool W_KEY(GLFWwindow* window);
	bool A_KEY(GLFWwindow* window);
	bool S_KEY(GLFWwindow* window);
	bool D_KEY(GLFWwindow* window);
	bool SPACE_KEY(GLFWwindow* window);
	bool ESCAPE_KEY(GLFWwindow* window);
	bool SHIFT_KEY(GLFWwindow* window);
	bool SHIFT_KEY_RELEASE(GLFWwindow* window);
	bool TAB_KEY(GLFWwindow* window);

	void glfwSetInputMode_normal(GLFWwindow* window);
	void glfwSetInputMode_cursor(GLFWwindow* window);
	void glfwSetInputMode_disabled(GLFWwindow* window);
	void glfwSetInputMode_unavailable(GLFWwindow* window);
	
private:
	//GLFWwindow* window;

};

