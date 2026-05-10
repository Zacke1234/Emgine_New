#pragma once
#include "Player.h"
#include "RecordTimes.h"
#include "Terrain.h"
#include "Levels.h"
#include "Interactable.h"
#include "Managers/ObjectManager.h"



class MainGameplay
{
public:
	void Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager);
	void Start();
	void Run();

protected:
	Player* player;
	GLFWwindow* getWindow;
};

