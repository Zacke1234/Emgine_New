#include "CameraManager.h"
#include <iostream>
Camera* CameraManager::Create(std::string name)
{
	Camera* cam = new Camera();
	cam->name = name;
	return cam;
}
