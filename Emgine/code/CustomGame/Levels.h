#pragma once
#include <string>
#include <vector>
#include "ObjectManager.h"
#include "ShaderManager.h"
class Levels
{
public:
	Levels(ShaderManager* aShaderManager = NULL);

	static std::vector<Levels*> levelList;

	int currentlevel = 0;

	ShaderManager* theShaderManager;

	std::vector<Object*> ObjectsInLevel;
	//static std::vector<Object*> Entities;
	std::string name = "placeHolder";

	void Load();

};

