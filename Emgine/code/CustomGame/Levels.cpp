#include "Levels.h"

std::vector<Levels*> Levels::levelList;

int Levels::SelectedLevel;

Levels::Levels(ShaderManager* aShaderManager, Time* aTime, ObjectManager* objManager)
{
	theShaderManager = aShaderManager;
	tempTime = aTime;
	this->levelID += 1;
	objManager = theObjManager;
	levelList.push_back(this);
}

void Levels::Load()
{
	levelTime = tempTime->CurrentTime;
}

void Levels::Clear()
{
	
	
}
