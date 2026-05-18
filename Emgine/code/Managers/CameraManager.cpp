#include "CameraManager.h"
#include <iostream>
Camera* CameraManager::Create(std::string name, GLFWwindow* aWindow)
{

	Camera* cam = new Camera(aWindow, name);
	cam->name = name;
	Camera::cameras.push_back(cam);
	return cam;
}
