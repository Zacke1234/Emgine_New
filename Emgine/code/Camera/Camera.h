#pragma once
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Shader.h>

class Camera
{
private:
	glm::vec3 myDirection;

	glm::vec3 myUp;
	glm::vec3 myRight;
	glm::vec3 myFront;

	glm::vec3 myTarget;

	unsigned int ShaderProgram;

	double curx;
	double cury;

public:
	static Camera* Instance;

	Camera();
	~Camera();
	
	std::string name;
	glm::mat4 myView;
	glm::mat4 projection;

	float cameraSpeed;
	float cameraViewRange;
	float myWidth;
	float myHeight;
	float zoom = 0;

	float yaw = -90.0f;
	float pitch = 0;
	float fieldOfView = 70;
	float sensitivity = 0.1f;
	bool TabbedIn = true;
	glm::vec3 direction;
	glm::vec3 myPosition;

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(myPosition, myPosition + myDirection, myUp);
	}

	static void Mouse_Callback(GLFWwindow* window, double xpos, double ypos);

	static Camera* GetInstance();

	void CameraSendToShader(Shader* myShader);

	void CameraUpdate(GLFWwindow* window);

	void ProcessInput(GLFWwindow* window, float& deltatime);

	void mouse_callback(double xpos, double ypos);
};

