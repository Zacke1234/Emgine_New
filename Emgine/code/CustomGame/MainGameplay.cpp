#include "MainGameplay.h"



void MainGameplay::Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager, Physics* aPhysics) // runs once when initialising the game
{
	
	iSwitch = new Interactable(myObjectManager, aMeshManager, aTextureManager, aColliderManager, aPhysics);
	player = new Player(getWindow, myObjectManager, aMeshManager, aTextureManager, aColliderManager, aRigidbodyManager, aCamManager, aTime, aPhysics);

	CubeCollider* cubeColl = new CubeCollider(glm::vec3(1,1,1), glm::vec3(0));
	Texture* wall = aTextureManager->Create("wall", "wall.jpg");
	Mesh* cube = aMeshManager->Create("Cube", "cube.obj");
	Door = myObjectManager->Create("Door", cube, wall, cubeColl, NULL);
	
	theObjectManager = myObjectManager;
	player->aShaderManager = aShaderManager;
}

void MainGameplay::Start() // runs once in the update loop
{
	
	
	
}

void MainGameplay::Run() // repeatedly runs in the update loop
{
	player->InputMovement();

	player->CheckCollision();

	if (iSwitch->Collided(player->playerColl))  
	{
		
		//std::cout << " switch collided" << std::endl;
	}
	
	

}
