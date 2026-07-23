#include "Levels.h"

std::vector<Levels*> Levels::levelList;

int Levels::SelectedLevel;
int id = -1;

Levels::Levels(ShaderManager* aShaderManager, Time* aTime, ObjectManager* objManager)
{
	theShaderManager = aShaderManager;
	tempTime = aTime;
	id += 1;
	levelID = id;
	objManager = theObjManager;
	levelList.push_back(this);

	/*for (auto& objs : Object::Entities)
	{
		ObjectsInLevel.push_back(objs);
	}*/
	
}

void Levels::GetTime()
{
	levelTime = tempTime->CurrentTime;
	
}

void Levels::Clear()
{
	
	for (auto& objs : Object::Entities)
	{
		if (Object::Entities.size() <= 0)
		{
			return;
		}
		Object::Entities.erase(Object::Entities.begin());
		
	}
	
}

void Levels::Load()
{
	for (auto& objs : ObjectsInLevel)
	{
		Object::Entities.push_back(objs);
	}

	//std::cout >> "Load level: " + name >> std::endl;

}
