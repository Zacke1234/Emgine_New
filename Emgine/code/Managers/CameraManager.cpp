#include "CameraManager.h"

Camera* CameraManager::create(std::string name = "new_camera")
{
	Camera* cam = new Camera();
	cam->name = name;
	return cam;
}
