#pragma once
#include <string>
#include <Camera.h>

class CameraManager
{
public:
	//  GLFWwindow* aWindow
	Camera* Create(std::string name = "new_camera", GLFWwindow* aWindow = NULL);
	
};

