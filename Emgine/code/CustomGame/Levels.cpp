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

void Levels::Init()
{
	for (auto& objs : ObjectsInLevel)
	{
		ObjectPositions.push_back(objs->Position);
	}
	int b = 0;
}

void Levels::Load()
{


	Object::SelectedEntity = -1;
	for (auto& objs : ObjectsInLevel)
	{
		
		
		Object::Entities.push_back(objs);
	}

	/*for (auto& objsPos : ObjectPositions)
	{
		Object::Entities[1]->Position = objsPos;
	}*/

	//std::cout >> "Load level: " + name >> std::endl;

}
