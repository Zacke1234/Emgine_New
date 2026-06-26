#pragma once
#include "Player.h"
#include "RecordTimes.h"
#include "Terrain.h"
#include "Levels.h"
#include "Interactable.h"
#include "BasicMenus.h"
#include "Managers/ObjectManager.h"

//#include "Physics.h"



class MainGameplay
{
public:
	void Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager, Physics* aPhysics, LightingManager* aLightingManager);
	void Start();
	void Run();


	Interactable* iSwitch;
	Player* player;
	GLFWwindow* getWindow;
	ObjectManager* theObjectManager;
	Object* Door;
	Levels* FirstLevel;
	Levels* SecondLevel;
	Levels* ThirdLevel;
	Time* theTime;
	BasicMenus* newMenu;

	bool MainGameplayRunOnce = false;
};

