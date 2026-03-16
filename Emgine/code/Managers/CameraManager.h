#pragma once
#include <string>
#include <Camera.h>

class CameraManager
{
public:
	Camera* Create(std::string name = "new_camera");
	
};

