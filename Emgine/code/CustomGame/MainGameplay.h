
#include "Player.h"
#include "RecordTimes.h"
#include "Terrain.h"
#include "Levels.h"
#include "Interactable.h"
#pragma once
class MainGameplay
{
public:
	void Start(GLFWwindow* window);
	void Run();

protected:
	Player* player;
};

