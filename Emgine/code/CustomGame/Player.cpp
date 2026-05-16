#include "Player.h"
#include <iostream>

using namespace std;



Player::Player(GLFWwindow* getWindow, ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager)
{
	window = getWindow;
	fish = aMeshManager->Create("Fish", "fish.obj");
	defaultTex = aTextureManager->Create("default", "Default 1.png");
	playerColl = aColliderManager->Create("Sphere");
	playerRB = aRigidbodyManager->Create("playerRB", 0.5, true, true);
	playerController = new Controller();

	aObjectManager->Create("Player", fish, defaultTex, playerColl, playerRB);
	dashStrength = 0.0f;
	jumpHeight = 0.0f;
	movementSpeed = 0.0f;

	playerCamera = new Camera(window, "PlayerCamera");
	
}

void Player::InputMovement()
{
	
	// 
	if(playerController->W_KEY(window))
	{
		playerRB->velocity += glm::vec3(0.0f, 0.0f, 1.0f * movementSpeed);
	}

	if (playerController->S_KEY(window))
	{
		playerRB->velocity += glm::vec3(0.0f, 0.0f, -1.0f * movementSpeed);
	}

	if (playerController->D_KEY(window))
	{
		playerRB->velocity += glm::vec3(1.0f * movementSpeed, 0.0f, 0.0f);
	}

	if (playerController->A_KEY(window))
	{
		playerRB->velocity += glm::vec3(-1.0f * movementSpeed, 0.0f, 0.0f);
	}

	if (playerController->SPACE_KEY(window))
	{
		playerRB->velocity += glm::vec3(0.0f, 5.0f * jumpHeight, 0.0f);
	}
}

 // opengl header already inluded error , remove previous include