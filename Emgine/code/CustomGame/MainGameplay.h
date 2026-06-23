#pragma once
#include "Player.h"
#include "RecordTimes.h"
#include "Terrain.h"
#include "Levels.h"
#include "Interactable.h"
#include "Managers/ObjectManager.h"
//#include "Physics.h"



class MainGameplay
{
public:
	void Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager, Physics* aPhysics);
	void Start();
	void Run();


	Interactable* iSwitch;
	Player* player;
	GLFWwindow* getWindow;
	ObjectManager* theObjectManager;
	Object* Door;
	Levels* FirstLevels;
	Time* theTime;

	bool MainGameplayRunOnce = false;
};

