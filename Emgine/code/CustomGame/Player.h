#pragma once
//#include "main.h"
//#include <glfw3.h>

#include <ObjectManager.h>
#include <TextureManager.h>
#include <ColliderManager.h>
#include <RigidbodyManager.h>
#include <CameraManager.h>
#include <Time/Time.h>
#include <ShaderManager.h>


class Player
{
public:
	Player(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime);
	ShaderManager* aShaderManager;
	void InputMovement();

	
private:
	float movementSpeed;
	float jumpHeight;
	float dashStrength;
	GLFWwindow* window;
	Mesh* playerMesh;
	Texture* defaultTex;
	Collider* playerColl;
	Rigidbody* playerRB;
	Controller* playerController;
	Shader* getShader;
	Camera* playerCamera;
	Object* player;
	Time* getTime;

	
};

