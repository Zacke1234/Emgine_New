#include "Player.h"
#include <iostream>



using namespace std;



Player::Player(GLFWwindow* getWindow, ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime)
{
	
	//getShader = aShaderManager->DefaultShader;
	getTime = aTime;
	window = getWindow;
	fish = aMeshManager->Create("Fish", "fish.obj");
	defaultTex = aTextureManager->Create("default", "Default 1.png");
	playerColl = aColliderManager->Create("Sphere");
	playerRB = aRigidbodyManager->Create("playerRB", 0.5, true, true);
	playerController = new Controller();

	player = aObjectManager->Create("Player", fish, defaultTex, playerColl, playerRB);
	dashStrength = 1.0f;
	jumpHeight = 1.0f;
	movementSpeed = 1.0f;

	playerCamera = aCamManager->Create("PlayerCamera", window);

	playerCamera->fieldOfView = 80.0f;
	playerCamera->sensitivity = 0.1f;
	
	// How to get a functional camera for the player?
}

void Player::InputMovement()
{
	/*playerController->glfwSetInputMode_cursor(window);
	playerController->glfwSetInputMode_disabled(window);
	playerController->glfwSetInputMode_unavailable(window);*/
	// 
	if(playerController->W_KEY(window))
	{
		player->Position += glm::vec3(0.0f, 0.0f, 1.0f * movementSpeed);
	}

	if (playerController->S_KEY(window))
	{
		player->Position += glm::vec3(0.0f, 0.0f, -1.0f * movementSpeed);
	}

	if (playerController->D_KEY(window))
	{
		player->Position += glm::vec3(1.0f * movementSpeed, 0.0f, 0.0f);
	}

	if (playerController->A_KEY(window))
	{
		player->Position += glm::vec3(-1.0f * movementSpeed, 0.0f, 0.0f);
	}

	if (playerController->SPACE_KEY(window))
	{
		player->Position += glm::vec3(0.0f, 5.0f * jumpHeight, 0.0f);
	}

	
	getShader = aShaderManager->DefaultShader;
	
	playerCamera->myPosition = player->Position;
	playerCamera->direction = player->Rotation;

	playerCamera->CameraUpdate();
	playerCamera->CameraSendToShader(getShader);

	
}

 // opengl header already inluded error , remove previous include