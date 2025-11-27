#pragma once
#include "Camera.h"
#include <Shader.h>
class CameraManager
{
public:
	Camera* create(std::string name);
	
};

