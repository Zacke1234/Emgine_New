#include "MainGameplay.h"



void MainGameplay::Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager) // runs once when initialising the game
{
	
	player = new Player(getWindow, myObjectManager, aMeshManager, aTextureManager, aColliderManager, aRigidbodyManager, aCamManager, aTime);
	player->aShaderManager = aShaderManager;
}

void MainGameplay::Start() // runs once in the update loop
{
	
	
	
}

void MainGameplay::Run() // repeatedly runs in the update loop
{
	player->InputMovement();
	

}
