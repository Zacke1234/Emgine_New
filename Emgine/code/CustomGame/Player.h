#pragma once
//#include "main.h"
//#include <glfw3.h>

#include "ObjectManager.h"
#include <TextureManager.h>
#include <ColliderManager.h>
#include <RigidbodyManager.h>



class Player
{
public:
	Player(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager);

	void InputMovement();
private:
	float movementSpeed;
	float jumpHeight;
	float dashStrength;
	GLFWwindow* window;
	Mesh* fish;
	Texture* defaultTex;
	Collider* playerColl;
	Rigidbody* playerRB;
	Controller* playerController;
	Camera* playerCamera;
	Object* player;
};

